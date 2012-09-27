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

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture 
{

    void test_vote_solve_0()
    {
        std::istringstream r("1\n\n2\nBob Marley\nJustin Beiber\n1 2\n\n");
        std::ostringstream w;
        vote_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Bob Marley\n");
    }

    void test_vote_solve_1()
    {
        std::istringstream r("\n\n");
        std::ostringstream w;
        vote_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");
    }

    void test_vote_solve_2()
    {
        std::istringstream r("1\n\n3\nBob Marley\nJustin Beiber\nNobody Cares\n1 3 2\n\n");
        std::ostringstream w;
        vote_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Bob Marley\n");
    }

    void test_calculate_winner_0()
    {
        vector<candidate> candidates;
        candidate a;
        a.name = "My Name";
        a.num_of_votes = 1;
        vector<ballot> ballots;
        ballot b;
        vector<int> i;
        i.push_back(1);
        b.index = 0;
        ballots.push_back(b);
        candidates.push_back(a);
        calculate_winner(candidates);
        CPPUNIT_ASSERT(winner == "My Name\n");
    }

    void test_calculate_winner_1()
    {
        vector<candidate> candidates;
        candidate a;
        a.name = "Hello There";
        a.num_of_votes = 0;
        vector<ballot> ballots;
        ballot b;
        vector<int> i;
        b.index = 0;
        ballots.push_back(b);
        a.voting_for_me = ballots;
        candidates.push_back(a);

        candidate c;
        c.name = "Whats Up";
        c.num_of_votes = 1;
        i.push_back(1);
        i.push_back(2);
        b.index = 0;
        ballots.clear();
        ballots.push_back(b);
        c.voting_for_me = ballots;
        candidates.push_back(c);

        calculate_winner(candidates);
        CPPUNIT_ASSERT(winner == "Whats Up\n");
    }

    void test_calculate_winner_2()
    {
        vector<candidate> candidates;
        candidate a;
        a.name = "This Work";
        a.num_of_votes = 0;
        vector<ballot> ballots;
        ballot b;
        vector<int> i;
        b.index = 0;
        ballots.push_back(b);
        a.voting_for_me = ballots;
        candidates.push_back(a);

        candidate c;
        c.name = "Hope So";
        c.num_of_votes = 1;
        i.push_back(1);
        i.push_back(2);
        b.index = 0;
        ballots.clear();
        ballots.push_back(b);
        c.voting_for_me = ballots;
        candidates.push_back(c);

        calculate_winner(candidates);
        CPPUNIT_ASSERT(winner == "Hope So\n");
    }

    void test_read_candidates_0()
    {
        std::istringstream r("\n2\nBob Marley\nJustin Beiber\n1 2\n\n");
        vector<candidate> candidates;
        int i = read_candidates(r, candidates);
        CPPUNIT_ASSERT(i == 2);
    }

    void test_read_candidates_1()
    {
        std::istringstream r("\n1\nBob Marley\n1\n\n");
        vector<candidate> candidates;
        int i = read_candidates(r, candidates);
        CPPUNIT_ASSERT(i == 1);
    }

    void test_read_candidates_2()
    {
        std::istringstream r("\n3\nBob Marley\nJustin Beiber\nMy Name\n3 1 2\n\n");
        vector<candidate> candidates;
        int i = read_candidates(r, candidates);
        CPPUNIT_ASSERT(i == 3);
    }

    void test_read_ballots_0()
    {
        std::istringstream r("");
        vector<candidate> candidates;
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(number_of_ballots == 0);
    }

    void test_read_ballots_1()
    {
        std::istringstream r("\n");
        vector<candidate> candidates;
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(number_of_ballots == 0);
    }

    void test_read_ballots_2()
    {
        std::istringstream r("\n\n");
        vector<candidate> candidates;
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(number_of_ballots == 0);
    }

    void test_redistribute_loser_votes_0()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nJoe Schmoe\n2 3 1\n1 2 3\n3 2 1\n2 3 1\n3 2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        redistribute_loser_votes(candidates);

        CPPUNIT_ASSERT(candidates[0].num_of_votes == 0);
        CPPUNIT_ASSERT(candidates[1].num_of_votes == 3);
        CPPUNIT_ASSERT(candidates[2].num_of_votes == 2);
    }


    void test_redistribute_loser_votes_1()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nJoe Schmoe\n1 2 3\n1 2 3\n3 2 1\n2 3 1\n3 2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        redistribute_loser_votes(candidates);

        CPPUNIT_ASSERT(candidates[0].num_of_votes == 2);
        CPPUNIT_ASSERT(candidates[1].num_of_votes == 0);
        CPPUNIT_ASSERT(candidates[2].num_of_votes == 3);
    }
 

    void test_redistribute_loser_votes_2()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nSchmoe\n1 2 3\n1 2 3\n2 3 1\n2 3 1\n3 2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        redistribute_loser_votes(candidates);

        CPPUNIT_ASSERT(candidates[0].num_of_votes == 2);
        CPPUNIT_ASSERT(candidates[1].num_of_votes == 3);
        CPPUNIT_ASSERT(candidates[2].num_of_votes == 0);
    }

    void test_get_losers_0()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n1 2\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(get_losers(candidates)[0] == 0);
    }

    void test_get_losers_1()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(get_losers(candidates)[0] == 1);
    }

    void test_get_losers_2()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n1 2\n2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(get_losers(candidates)[0] == 0);
        CPPUNIT_ASSERT(get_losers(candidates)[1] == 1);
    }

    void test_contains_0()
    {
        vector<int> i;
        i.push_back(1);
        i.push_back(2);
        i.push_back(3);
        i.push_back(4);
        i.push_back(5);
        i.push_back(6);
        CPPUNIT_ASSERT(contains(i, 5));
    }

    void test_contains_1()
    {
        vector<int> i;
        i.push_back(1);
        i.push_back(2);
        i.push_back(3);
        i.push_back(4);
        i.push_back(5);
        i.push_back(6);
        CPPUNIT_ASSERT(contains(i, 1));
    }

    void test_contains_2()
    {
        vector<int> i;
        i.push_back(1);
        i.push_back(2);
        i.push_back(3);
        i.push_back(4);
        i.push_back(5);
        i.push_back(6);
        CPPUNIT_ASSERT(!contains(i, 0));
    }

    void test_check_for_winner_0()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n1 2\n2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(!check_for_winner(candidates));
    }

    void test_check_for_winner_1()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n1 2\n2 1\n1 2\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(check_for_winner(candidates));
    }

    void test_check_for_winner_2()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nJoe Schmoe\n1 2 3\n2 1 3\n1 2 3\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(check_for_winner(candidates));
    }

    void test_check_for_tie_0()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nJoe Schmoe\n1 2 3\n2 1 3\n1 2 3\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(!check_for_tie(candidates));
    }

    void test_check_for_tie_1()
    {
        std::istringstream r("3\nBob Marley\nJustin Beiber\nJoe Schmoe\n1 2 3\n2 1 3\n3 2 1\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(check_for_tie(candidates));
    }

    void test_check_for_tie_2()
    {
        std::istringstream r("2\nBob Marley\nJustin Beiber\n2 1\n1 2\n\n");
        vector<candidate> candidates;
        read_candidates(r, candidates);
        read_ballots(r, candidates);
        CPPUNIT_ASSERT(check_for_tie(candidates));
    }

    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_vote_solve_0);
    CPPUNIT_TEST(test_vote_solve_1);
    CPPUNIT_TEST(test_vote_solve_2);
    CPPUNIT_TEST(test_calculate_winner_0);
    CPPUNIT_TEST(test_calculate_winner_1);
    CPPUNIT_TEST(test_calculate_winner_2);
    CPPUNIT_TEST(test_read_candidates_0);
    CPPUNIT_TEST(test_read_candidates_1);
    CPPUNIT_TEST(test_read_candidates_2);
    CPPUNIT_TEST(test_read_ballots_0);
    CPPUNIT_TEST(test_read_ballots_1);
    CPPUNIT_TEST(test_read_ballots_2);
    CPPUNIT_TEST(test_get_losers_0);
    CPPUNIT_TEST(test_get_losers_1);
    CPPUNIT_TEST(test_get_losers_2);
    CPPUNIT_TEST(test_redistribute_loser_votes_0);
    CPPUNIT_TEST(test_redistribute_loser_votes_1);
    CPPUNIT_TEST(test_redistribute_loser_votes_2);
    CPPUNIT_TEST(test_contains_0);
    CPPUNIT_TEST(test_contains_1);
    CPPUNIT_TEST(test_contains_2);
    CPPUNIT_TEST(test_check_for_winner_0);
    CPPUNIT_TEST(test_check_for_winner_1);
    CPPUNIT_TEST(test_check_for_winner_2);
    CPPUNIT_TEST(test_check_for_tie_0);
    CPPUNIT_TEST(test_check_for_tie_1);
    CPPUNIT_TEST(test_check_for_tie_2);

    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;
}

