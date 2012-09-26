// --------------------------------
// Copyright (C) 2012
// Enrique Sada
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <map> 
#include <string.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----
    // read
    // ----

    void test_is_next_line_empty_1 () {
        std::istringstream r("12");
        const bool b = is_next_line_empty(r);
        CPPUNIT_ASSERT(b == false);}

    void test_is_next_line_empty_2 () {
        std::istringstream r("\n");
        const bool b = is_next_line_empty(r);
        CPPUNIT_ASSERT(b == true);}

    void test_get_num_cases_1 () {
        std::istringstream r("0\n");
        const int num_cases = get_num_cases(r);
        CPPUNIT_ASSERT(num_cases == 0);}

    void test_get_num_cases_2 () {
        std::istringstream r("10\n");
        const int num_cases = get_num_cases(r);
        CPPUNIT_ASSERT(num_cases == 10);}

    void test_read_case_1 () {
        std::istringstream r("3\nCand1\nCand2\nCand3\n1 2 3\n");
        std::vector<std::string> candidates;
        Votes votes;
        int num_votes;

        num_votes = read_case(r, candidates, votes);
        CPPUNIT_ASSERT(num_votes == 1);
        CPPUNIT_ASSERT(candidates[0] == "Cand1");
        CPPUNIT_ASSERT(candidates[1] == "Cand2");
        CPPUNIT_ASSERT(candidates[2] == "Cand3");

        std::vector<Ballot> list_ballots = votes[1];
        Ballot ballot = list_ballots[0];

        for (int i =0; (unsigned)i<ballot.size(); i++){
            CPPUNIT_ASSERT(ballot[i] == i+1);
        }
    }

    void test_read_case_2 () {
        std::istringstream r("3\nCand1\nCand2\nCand3\n1 2 3\n");
        std::vector<std::string> candidates;
        Votes votes;
        int num_votes;

        num_votes = read_case(r, candidates, votes);

        CPPUNIT_ASSERT(num_votes == 1);
        CPPUNIT_ASSERT(candidates.size() == 3);

        std::vector<Ballot> list_ballots = votes[1];
        CPPUNIT_ASSERT(list_ballots.size() == 1);
    }
    
    void test_read_case_3 () {
        std::istringstream r("3\nCand1\nCand2\nCand3\n1 2 3\n1 2 3\n1 3 2");
        std::vector<std::string> candidates;
        Votes votes;
        int num_votes;

        num_votes = read_case(r, candidates, votes);

        CPPUNIT_ASSERT(num_votes == 3);
        CPPUNIT_ASSERT(candidates.size() == 3);

        std::vector<Ballot> list_ballots = votes[1];
        CPPUNIT_ASSERT(list_ballots.size() == 3);
    }

    void test_read_case_4 () {
        std::istringstream r("3\nCand1\nCand2\nCand3\n2 3 1\n1 2 3\n2 3 1");
        std::vector<std::string> candidates;
        Votes votes;
        int num_votes;

        num_votes = read_case(r, candidates, votes);
        CPPUNIT_ASSERT(num_votes == 3);

        CPPUNIT_ASSERT(candidates.size() == 3);
        std::vector<Ballot> list_ballots = votes[1];
        CPPUNIT_ASSERT(list_ballots.size() == 1);

        list_ballots = votes[2];
        CPPUNIT_ASSERT(list_ballots.size() == 2);

        list_ballots = votes[3];
        CPPUNIT_ASSERT(list_ballots.size() == 0);

    }
    void test_read_case_5 () {
        std::istringstream r("2\nMia\nTuya\n1 2\n2 1");
        std::vector<std::string> candidates;
        Votes votes;
        int num_votes;

        num_votes = read_case(r, candidates, votes);
        CPPUNIT_ASSERT(num_votes == 2);

        CPPUNIT_ASSERT(candidates.size() == 2);
        CPPUNIT_ASSERT(candidates.at(0).compare("Mia") == 0);
        CPPUNIT_ASSERT(candidates.at(1).compare("Tuya") == 0);

        //Mia
        std::vector<Ballot> list_ballots = votes[1];
        CPPUNIT_ASSERT(list_ballots.size() == 1);
        //1st ballot
        CPPUNIT_ASSERT(list_ballots.at(0).size() == 2);
        CPPUNIT_ASSERT(list_ballots.at(0).at(0) == 1);
        CPPUNIT_ASSERT(list_ballots.at(0).at(1) == 2);

        //Tuya
        list_ballots = votes[2];
        CPPUNIT_ASSERT(list_ballots.size() == 1);
        //1st ballot
        CPPUNIT_ASSERT(list_ballots.at(0).size() == 2);
        CPPUNIT_ASSERT(list_ballots.at(0).at(0) == 2);
        CPPUNIT_ASSERT(list_ballots.at(0).at(1) == 1);


    }


    // ----
    // is_tied
    // ----

    void is_tied_1 () {
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {3, 2, 1};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[2].push_back(ballot_2);
        votes[3].push_back(ballot_3);

        int num_votes_tied;
        int num_candidates = 3;
        CPPUNIT_ASSERT(is_tied(votes, num_votes_tied, num_candidates) == true);
        CPPUNIT_ASSERT(num_votes_tied == 1);

    }

    void is_tied_2 () {
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {1, 2, 3};
        Ballot ballot_3 = {3, 2, 1};
        Ballot ballot_4 = {3, 2, 1};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_2);
        votes[3].push_back(ballot_3);
        votes[3].push_back(ballot_4);

        int num_votes_tied;
        int num_candidates = 3;
        CPPUNIT_ASSERT(is_tied(votes, num_votes_tied, num_candidates) == true);
        CPPUNIT_ASSERT(num_votes_tied == 2);

    }

    void is_tied_3 () {
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);

        int num_candidates = 3;
        int num_votes_tied;
        CPPUNIT_ASSERT(is_tied(votes, num_votes_tied, num_candidates) == false);
    }

    void is_tied_4 () {
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {2, 3, 1};
        Ballot ballot_4 = {1, 2, 3};
        Ballot ballot_5 = {3, 2, 1};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_4);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_3);
        votes[3].push_back(ballot_5);

        int num_votes_tied;
        int num_candidates = 3;
        CPPUNIT_ASSERT(is_tied(votes, num_votes_tied, num_candidates) == false);

    }

    void is_tied_5 () {
        Ballot ballot_1 = {1, 2};
        Ballot ballot_2 = {2, 1};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[2].push_back(ballot_2);

        int num_votes_tied;
        int num_candidates = 2;
        CPPUNIT_ASSERT(is_tied(votes, num_votes_tied, num_candidates) == true);
        CPPUNIT_ASSERT(num_votes_tied == 1);

    }

    // ----
    // have_winner
    // ----

    void have_winner_1 () {
        int num_votes = 3;
        int winner_num;
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {3, 2, 1};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[2].push_back(ballot_2);
        votes[3].push_back(ballot_3);

        CPPUNIT_ASSERT(have_winner(votes, num_votes, num_candidates, winner_num) == false);

    }

    void have_winner_2 () {
        int num_votes = 4;
        int winner_num;
        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {1, 2, 3};
        Ballot ballot_3 = {3, 2, 1};
        Ballot ballot_4 = {3, 2, 1};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_2);
        votes[3].push_back(ballot_3);
        votes[3].push_back(ballot_4);

       CPPUNIT_ASSERT(have_winner(votes, num_votes, num_candidates, winner_num) == false);

    }

    void have_winner_3 () {
        int num_votes = 5;
        int winner_num;

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);

       CPPUNIT_ASSERT(have_winner(votes, num_votes, num_candidates, winner_num) == false);

    }

    void have_winner_4 () {
        int num_votes = 5;
        int winner_num;

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};
        Ballot ballot_6 = {1, 2, 3};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[1].push_back(ballot_6);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);

       CPPUNIT_ASSERT(have_winner(votes, num_votes, num_candidates, winner_num) == true);

    }

    // -----
    // get_lowest_num_votes
    // -----

    void get_lowest_num_votes_1 () {

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};
        Ballot ballot_6 = {1, 2, 3};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[1].push_back(ballot_6);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);

       CPPUNIT_ASSERT(get_lowest_num_votes(votes, num_candidates) == 1);

    }

    void get_lowest_num_votes_2 () {

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};
        Ballot ballot_6 = {1, 2, 3};
        Ballot ballot_7 = {3, 2, 1};

        Votes votes;
        int num_candidates = 3;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[1].push_back(ballot_6);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);
        votes[3].push_back(ballot_7);

       CPPUNIT_ASSERT(get_lowest_num_votes(votes, num_candidates) == 2);
    }

    // -----
    // update_lowest_votes
    // -----

    void update_lowest_votes_1 () {

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 2, 1};
        Ballot ballot_6 = {1, 2, 3};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[1].push_back(ballot_6);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);
        
        int num_candidates = 3;
        update_lowest_votes(votes, num_candidates);
        using namespace std;
        CPPUNIT_ASSERT(votes[1].size() == 3);
        CPPUNIT_ASSERT(votes[2].size() == 3);
        CPPUNIT_ASSERT(votes[3].size() == 0);

    }

    void update_lowest_votes_2 () {

        Ballot ballot_1 = {1, 2, 3};
        Ballot ballot_2 = {2, 1, 3};
        Ballot ballot_3 = {1, 2, 3};
        Ballot ballot_4 = {2, 3, 1};
        Ballot ballot_5 = {3, 1, 2};
        Ballot ballot_6 = {1, 2, 3};

        Votes votes;
        votes[1].push_back(ballot_1);
        votes[1].push_back(ballot_3);
        votes[1].push_back(ballot_6);
        votes[2].push_back(ballot_2);
        votes[2].push_back(ballot_4);
        votes[3].push_back(ballot_5);
        
        int num_candidates = 3;
        update_lowest_votes(votes, num_candidates);
        CPPUNIT_ASSERT(votes[1].size() == 4);
        CPPUNIT_ASSERT(votes[2].size() == 2);
        CPPUNIT_ASSERT(votes[3].size() == 0);

    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_is_next_line_empty_1);
    CPPUNIT_TEST(test_is_next_line_empty_2);
    CPPUNIT_TEST(test_get_num_cases_1);
    CPPUNIT_TEST(test_get_num_cases_2);
    CPPUNIT_TEST(test_read_case_1);
    CPPUNIT_TEST(test_read_case_2);
    CPPUNIT_TEST(test_read_case_3);
    CPPUNIT_TEST(test_read_case_4);
    CPPUNIT_TEST(test_read_case_5);

    CPPUNIT_TEST(is_tied_1);
    CPPUNIT_TEST(is_tied_2);
    CPPUNIT_TEST(is_tied_3);
    CPPUNIT_TEST(is_tied_4);
    CPPUNIT_TEST(is_tied_5);

    CPPUNIT_TEST(have_winner_1);
    CPPUNIT_TEST(have_winner_2);
    CPPUNIT_TEST(have_winner_3);
    CPPUNIT_TEST(have_winner_4);

    CPPUNIT_TEST(get_lowest_num_votes_1);
    CPPUNIT_TEST(get_lowest_num_votes_2);

    CPPUNIT_TEST(update_lowest_votes_1);
    CPPUNIT_TEST(update_lowest_votes_2);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
