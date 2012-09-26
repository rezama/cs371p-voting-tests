// --------------------------------
// projects/Voting/TestVoting.c++
// Copyright (C) 2012
// Glenn P. Downing
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
#include <iostream>                           // cout, endl
#include <sstream>                            // istringtstream, ostringstream
#include <string>                             // ==
#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TextTestRunner
#include "./Voting.h"

// ------
// macros
// ------

#define TEST(b) CPPUNIT_ASSERT((b))

// -----------
// TestBallot
// -----------

// Frequently used ballots
Ballot BALS[3] = { Ballot(3, "1 2 3"), Ballot(5, "1 5 3 4 2"), Ballot(
        7, "5 2 3 7 4 1 6") };

/*
 * Return a copy pre-generated ballot
 */
Ballot balGen(int index) {
    return Ballot(BALS[index]);
}

// Frequently using Candidates:
Candidate CANDIDATE[] { Candidate("Tri Nguyen"), Candidate("Doug Iljev"),
        Candidate("John Doe"), Candidate("Jane Smith"), Candidate("Joe"),
        Candidate(":(")};
/*
 * return a candidate
 */
Candidate canGen(int index) {
    return CANDIDATE[index];
}

struct TestBallot : CppUnit::TestFixture {
    // ------------------
    // Ballot Constructor
    // ------------------
    void test_ballot_ctor_int_string_1() {
        Ballot a = balGen(0);
        TEST(a.getIndex() == 0);
        int numVotes = a.getNumVotes();
        TEST(numVotes == 3);
        for (int i = 0; i < numVotes; ++i) {
            TEST(a.getVote(i) == i+1);
        }
    }

    void test_ballot_ctor_int_string_2() {
        Ballot b = balGen(1);
        TEST(b.getIndex() == 0);
        TEST(b.getNumVotes() == 5);
        istringstream lineStream("1 5 3 4 2");
        int vote;
        for (int i = 0; i < b.getNumVotes(); ++i) {
            lineStream >> vote;
            TEST(b.getVote(i) == vote);
        }
    }

    void test_ballot_ctor_int_string_3() {
        Ballot b = balGen(2);
        TEST(b.getIndex() == 0);

        int numVotes = b.getNumVotes();
        TEST(numVotes == 7);

        istringstream lineStream("5 2 3 7 4 1 6");
        int vote;
        for (int i = 0; i < numVotes; ++i) {
            lineStream >> vote;
            TEST(b.getVote(i) == vote);
        }
    }

    void test_ballot_copy_ctor_1() {
        Ballot a = balGen(1);
        Ballot c = balGen(1);
        Ballot b = Ballot(a);
        TEST(b == c);
        TEST(b == a);
        a = balGen(2);
        TEST(!(b == a));
    }

    void test_ballot_copy_ctor_2() {
        Ballot a = balGen(0);
        Ballot b = Ballot(a);
        TEST(b == a);
        a = balGen(2);
        TEST(!(a == b));
    }

    void test_ballot_copy_ctor_3() {
        Ballot a = balGen(2);
        Ballot b = Ballot(a);
        TEST(b == a);
    }

    void test_ballot_operator_1() {
        Ballot a = balGen(1);
        Ballot c = balGen(1);
        Ballot b = Ballot(a);
        TEST(b == c);
        TEST(b == a);
        a = balGen(2);
        TEST(!(b == a));
    }

    void test_ballot_operator_2() {
        Ballot a = balGen(0);
        Ballot b = Ballot(a);
        TEST(b == a);
        a = balGen(2);
        TEST(!(a == b));
    }

    void test_ballot_operator_3() {
        Ballot a = balGen(2);
        Ballot b = Ballot(a);
        TEST(b == a);
    }

    /*
     * Test Ballot get_index
     */

    void test_ballot_get_index_1() {
        Ballot b = balGen(0);
        TEST(b.getIndex() == 0);
        // TODO: try to remove candidate and check
    }
    void test_ballot_get_index_2() {
        Ballot b = balGen(1);
        TEST(b.getIndex() == 0);
        // TODO: try to remove and check
    }
    void test_ballot_get_index_3() {
        Ballot b = balGen(2);
        TEST(b.getIndex() == 0);
        // TODO: try to remove candidate and check
    }

    /*
     * Test Ballot getNumVotes
     */

    void test_ballot_get_num_votes_1() {
        Ballot b = balGen(0);
        TEST(b.getNumVotes() == 3);
    }
    void test_ballot_get_num_votes_2() {
        Ballot b = balGen(1);
        TEST(b.getNumVotes() == 5);
    }
    void test_ballot_get_num_votes_3() {
        Ballot b = balGen(2);
        TEST(b.getNumVotes() == 7);
    }

    /*
     * Test getVote
     */

    void test_ballot_get_vote_1() {
        Ballot b = balGen(0);
        TEST(b.getVote(0) == 1);
        TEST(b.getVote(1) == 2);
        TEST(b.getVote(2) == 3);
    }

    void test_ballot_get_vote_2() {
        Ballot b = balGen(1);
        TEST(b.getVote(0) == 1);
        TEST(b.getVote(1) == 5);
        TEST(b.getVote(2) == 3);
        TEST(b.getVote(3) == 4);
        TEST(b.getVote(4) == 2);
    }

    void test_ballot_get_vote_3() {
        Ballot b = balGen(2);
        TEST(b.getVote(0) == 5);
        TEST(b.getVote(1) == 2);
        TEST(b.getVote(2) == 3);
        TEST(b.getVote(3) == 7);
        TEST(b.getVote(4) == 4);
        TEST(b.getVote(5) == 1);
        TEST(b.getVote(6) == 6);
    }

    void test_ballot_move_index_1() {
        Ballot b = balGen(0);
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));
        candidates[0].giveUp();
        int newIndex = b.moveIndex();
        TEST(newIndex == 1);
        candidates[1].giveUp();
        newIndex = b.moveIndex();
        TEST(newIndex == 2);
    }

    void test_ballot_move_index_2() {
        Ballot b = balGen(0);
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));
        candidates[0].giveUp();
        candidates[1].giveUp();
        int newIndex = b.moveIndex();
        TEST(newIndex == 2);
    }

    void test_ballot_move_index_3() {
        Ballot b = balGen(0);
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));
        candidates[1].giveUp();
        int newIndex = b.moveIndex();
        TEST(newIndex == 0);
        candidates[0].giveUp();
        newIndex = b.moveIndex();
        TEST(newIndex == 2);
    }

    void test_ballot_move_index_4() {
        Ballot b = balGen(1);
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));
        candidates.push_back(canGen(3));
        candidates.push_back(canGen(4));
        candidates.push_back(canGen(5));
        count_ballot(b);
        candidates[0].giveUp();
        int newIndex = b.moveIndex();
        TEST(newIndex == 1);
        candidates[4].giveUp();
        newIndex = b.moveIndex();
        TEST(newIndex == 2);
    }

    // ----
    // read
    // ----

CPPUNIT_TEST_SUITE(TestBallot);
        CPPUNIT_TEST(test_ballot_ctor_int_string_1);
        CPPUNIT_TEST(test_ballot_ctor_int_string_2);
        CPPUNIT_TEST(test_ballot_ctor_int_string_3);
        CPPUNIT_TEST(test_ballot_operator_1);
        CPPUNIT_TEST(test_ballot_operator_2);
        CPPUNIT_TEST(test_ballot_operator_3);
        CPPUNIT_TEST(test_ballot_copy_ctor_1);
        CPPUNIT_TEST(test_ballot_copy_ctor_2);
        CPPUNIT_TEST(test_ballot_copy_ctor_3);
        CPPUNIT_TEST(test_ballot_get_index_1);
        CPPUNIT_TEST(test_ballot_get_index_2);
        CPPUNIT_TEST(test_ballot_get_index_3);
        CPPUNIT_TEST(test_ballot_get_num_votes_1);
        CPPUNIT_TEST(test_ballot_get_num_votes_2);
        CPPUNIT_TEST(test_ballot_get_num_votes_3);
        CPPUNIT_TEST(test_ballot_get_vote_1);
        CPPUNIT_TEST(test_ballot_get_vote_2);
        CPPUNIT_TEST(test_ballot_get_vote_3);
        CPPUNIT_TEST(test_ballot_move_index_1);
        CPPUNIT_TEST(test_ballot_move_index_2);
        CPPUNIT_TEST(test_ballot_move_index_3);
        CPPUNIT_TEST(test_ballot_move_index_4);
    CPPUNIT_TEST_SUITE_END();
};


struct TestCandidate : CppUnit::TestFixture {
    void test_candidate_get_name_1() {
        Candidate c = canGen(1);
        TEST(c.getName() == "Doug Iljev");
    }
    void test_candidate_get_name_2() {
        Candidate c = canGen(0);
        TEST(c.getName() == "Tri Nguyen");
    }
    void test_candidate_get_name_3() {
        Candidate c = canGen(2);
        TEST(c.getName() == "John Doe");
    }

    void test_candidate_is_eligible_1() {
        Candidate c = canGen(0);
        TEST(c.isEligible());
        c.giveUp();
        TEST(!c.isEligible());
    }

    void test_candidate_is_eligible_2() {
        Candidate c = canGen(1);
        TEST(c.isEligible());
        c.giveUp();
        TEST(!c.isEligible());
    }

    void test_candidate_is_eligible_3() {
        Candidate c = canGen(2);
        TEST(c.isEligible());
        c.giveUp();
        TEST(!c.isEligible());
    }

    void test_candidate_is_running_1() {
        Candidate a = canGen(0);
        TEST(a.isEligible());
    }

    void test_candidate_is_running_2() {
        Candidate a = canGen(1);
        TEST(a.isEligible());
        a.giveUp();
        TEST(!a.isEligible());
    }

    void test_candidate_is_running_3() {
        Candidate a = canGen(2);
        TEST(a.isEligible());
        TEST(a.isEligible());
        a.giveUp();
        TEST(!a.isEligible());
    }

    void test_candidate_give_up_1() {
        Candidate a = canGen(0);
        TEST(a.isEligible());
    }

    void test_candidate_give_up_2() {
        Candidate a = canGen(1);
        TEST(a.isEligible());
        a.giveUp();
        TEST(!a.isEligible());
    }

    void test_candidate_give_up_3() {
        Candidate a = canGen(2);
        TEST(a.isEligible());
        TEST(a.isEligible());
        a.giveUp();
        TEST(!a.isEligible());
    }

    void test_candidate_add_ballot_1() {
        Ballot b = balGen(0);
        Candidate c = canGen(0);
        c.addBallot(b);
        TEST(c.getNumVotes() == 1);
    }

    void test_candidate_add_ballot_2() {
        Ballot b = balGen(1);
        Candidate c = canGen(1);
        c.addBallot(b);
        c.addBallot(b);
        TEST(c.getNumVotes() == 2);
    }

    void test_candidate_add_ballot_3() {
        Ballot b = balGen(1);
        Candidate c = canGen(1);
        c.addBallot(b);
        c.addBallot(b);
        c.addBallot(balGen(0));
        TEST(c.getNumVotes() == 3);
    }

    void test_candidate_get_num_votes_1() {
        Ballot b = balGen(1);
        Candidate c = canGen(1);
        c.addBallot(b);
        c.addBallot(b);
        c.addBallot(balGen(0));
        TEST(c.getNumVotes() == 3);
    }

    void test_candidate_get_num_votes_2() {
        Ballot b = balGen(1);
        Candidate c = canGen(1);
        c.addBallot(b);
        c.addBallot(b);
        c.addBallot(balGen(0));
        TEST(c.getNumVotes() == 3);
    }
    void test_candidate_get_num_votes_3() {
        Ballot b = balGen(1);
        Candidate c = canGen(1);
        c.addBallot(b);
        c.addBallot(b);
        c.addBallot(balGen(0));
        TEST(c.getNumVotes() == 3);
    }

    void test_candidate_move_ballots_1() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));

        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "2 1"));

        TEST(candidates[0].getNumVotes() == 2);
        TEST(candidates[1].getNumVotes() == 1);

        candidates[1].giveUp();
        candidates[1].moveBallots();

        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 0);

        // TODO make sure the total # votes in system doesn't change
    }

    void test_candidate_move_ballots_2() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        count_ballot(Ballot(3, "1 2 3"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "3 1 2"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));

        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 3);
        TEST(candidates[2].getNumVotes() == 4);

        candidates[0].giveUp();
        candidates[0].moveBallots();

        TEST(candidates[0].getNumVotes() == 0);
        TEST(candidates[1].getNumVotes() == 4);
        TEST(candidates[2].getNumVotes() == 6);

        candidates[1].giveUp();
        candidates[1].moveBallots();

        TEST(candidates[0].getNumVotes() == 0);
        TEST(candidates[1].getNumVotes() == 0);
        TEST(candidates[2].getNumVotes() == 10);
    }

    void test_candidate_move_ballots_3() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        count_ballot(Ballot(3, "1 2 3"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "3 1 2"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));

        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 3);
        TEST(candidates[2].getNumVotes() == 4);

        candidates[2].giveUp();
        candidates[2].moveBallots();

        TEST(candidates[0].getNumVotes() == 4);
        TEST(candidates[1].getNumVotes() == 6);
        TEST(candidates[2].getNumVotes() == 0);

        candidates[1].giveUp();
        candidates[1].moveBallots();

        TEST(candidates[0].getNumVotes() == 10);
        TEST(candidates[1].getNumVotes() == 0);
        TEST(candidates[2].getNumVotes() == 0);
    }

CPPUNIT_TEST_SUITE(TestCandidate);
        CPPUNIT_TEST(test_candidate_get_name_1);
        CPPUNIT_TEST(test_candidate_get_name_2);
        CPPUNIT_TEST(test_candidate_get_name_3);
        CPPUNIT_TEST(test_candidate_is_eligible_1);
        CPPUNIT_TEST(test_candidate_is_eligible_2);
        CPPUNIT_TEST(test_candidate_is_eligible_3);
        CPPUNIT_TEST(test_candidate_add_ballot_1);
        CPPUNIT_TEST(test_candidate_add_ballot_2);
        CPPUNIT_TEST(test_candidate_add_ballot_3);
        CPPUNIT_TEST(test_candidate_get_num_votes_1);
        CPPUNIT_TEST(test_candidate_get_num_votes_2);
        CPPUNIT_TEST(test_candidate_get_num_votes_3);
        CPPUNIT_TEST(test_candidate_give_up_1);
        CPPUNIT_TEST(test_candidate_give_up_2);
        CPPUNIT_TEST(test_candidate_give_up_3);
        CPPUNIT_TEST(test_candidate_is_running_1);
        CPPUNIT_TEST(test_candidate_is_running_2);
        CPPUNIT_TEST(test_candidate_is_running_3);
        CPPUNIT_TEST(test_candidate_move_ballots_1);
        CPPUNIT_TEST(test_candidate_move_ballots_2);
        CPPUNIT_TEST(test_candidate_move_ballots_3);
    CPPUNIT_TEST_SUITE_END();
};

struct TestVoting : CppUnit::TestFixture {
    void test_count_ballot_1() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        Ballot b = balGen(0);
        count_ballot(b);

        TEST(candidates[0].getNumVotes() == 1);
        TEST(candidates[1].getNumVotes() == 0);
        TEST(candidates[2].getNumVotes() == 0);
    }

    void test_count_ballot_2() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        Ballot b = Ballot(3, "2 1 3");
        count_ballot(b);

        TEST(candidates[0].getNumVotes() == 0);
        TEST(candidates[1].getNumVotes() == 1);
        TEST(candidates[2].getNumVotes() == 0);
    }

    void test_count_ballot_3() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "1 2 3"));
        count_ballot(Ballot(3, "1 3 2"));

        TEST(candidates[0].getNumVotes() == 2);
        TEST(candidates[1].getNumVotes() == 1);
        TEST(candidates[2].getNumVotes() == 0);
    }

    void test_read_1() {
        string s = "1\nabc\n1\n1\n1\n\n";
        std::istringstream r(s);
        const bool b = voting_read(r);

        TEST(b == 0);
        TEST(candidates[0].getName() == "abc");
        TEST(candidates[0].getNumVotes() == 3);
    }

    void test_read_2() {
        string s = "3\n"
                "a\n"
                "b\n"
                "c\n"
                "1 2 3\n"
                "1 3 2\n"
                "2 3 1\n"
                "3 2 1\n\n";
        std::istringstream r(s);
        const bool b = voting_read(r);

        TEST(b == 0);

        TEST(candidates[0].getName() == "a");
        TEST(candidates[1].getName() == "b");
        TEST(candidates[2].getName() == "c");

        TEST(candidates[0].getNumVotes() == 2);
        TEST(candidates[1].getNumVotes() == 1);
        TEST(candidates[2].getNumVotes() == 1);
    }

    void test_read_3() {
        string s = "2\n"
                "t\n"
                "doug\n"
                "1 2\n"
                "2 1\n"
                "1 2\n"
                "1 2\n"
                "1 2\n\n";
        std::istringstream r(s);
        const bool b = voting_read(r);

        TEST(b == 0);

        TEST(candidates[0].getName() == "t");
        TEST(candidates[1].getName() == "doug");

        TEST(candidates[0].getNumVotes() == 4);
        TEST(candidates[1].getNumVotes() == 1);
    }

    void test_voting_count_running_1() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));
        TEST(voting_count_running() == 3);
        candidates[1].giveUp();
        TEST(voting_count_running() == 2);
        candidates[0].giveUp();
        TEST(voting_count_running() == 1);
        candidates[2].giveUp();
        TEST(voting_count_running() == 0);
    }

    void test_voting_count_running_2() {
        candidates.clear();
        for (int i = 0; i < 5; ++i) {
            candidates.push_back(canGen(i));
        }
        for (int i = 4; i >= 0; --i) {
            candidates[i].giveUp();
            TEST(voting_count_running() == i);
        }
    }
    void test_voting_count_running_3() {
        candidates.clear();
        for (int i = 0; i < 5; ++i) {
            candidates.push_back(canGen(i));
            TEST(voting_count_running() == i+1);
        }
        for (int i = 4; i >= 0; --i) {
            candidates[i].giveUp();
            TEST(voting_count_running() == i);
        }
    }

    void test_voting_iteration_1() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));

        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "2 1"));
        TEST(voting_iteration() == false);
        TEST(voting_count_running() == 1);
        TEST(candidates[0].getNumVotes() == 3);
        TEST(voting_iteration());
        TEST(voting_count_running() == 1);
    }

    void test_voting_iteration_2() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        count_ballot(Ballot(3, "1 2 3"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "3 1 2"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));

        TEST(voting_count_running() == 3);
        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 3);
        TEST(candidates[2].getNumVotes() == 4);

        TEST(!voting_iteration());
        TEST(voting_count_running() == 1);
        TEST(candidates[0].getNumVotes() == 0);
        TEST(candidates[1].getNumVotes() == 0);
        TEST(candidates[2].getNumVotes() == 10);

        TEST(voting_iteration());
        TEST(voting_count_running() == 1);
        TEST(candidates[0].getNumVotes() == 0);
        TEST(candidates[1].getNumVotes() == 0);
        TEST(candidates[2].getNumVotes() == 10);
    }

    void test_voting_iteration_3() {
        candidates.clear();

        candidates.push_back(Candidate("Red"));
        candidates.push_back(Candidate("Green"));
        candidates.push_back(Candidate("Blue"));
        candidates.push_back(Candidate("Orange"));

        count_ballot(Ballot(4, "1 2 3 4"));
        count_ballot(Ballot(4, "2 1 3 4"));
        count_ballot(Ballot(4, "2 3 1 4"));
        count_ballot(Ballot(4, "1 2 3 4"));
        count_ballot(Ballot(4, "3 4 1 2"));
        count_ballot(Ballot(4, "4 3 2 1"));

        TEST(voting_count_running() == 4);
        TEST(candidates[0].getNumVotes() == 2);
        TEST(candidates[1].getNumVotes() == 2);
        TEST(candidates[2].getNumVotes() == 1);
        TEST(candidates[3].getNumVotes() == 1);

        TEST(!voting_iteration());

        TEST(voting_count_running() == 2);
        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 3);
        TEST(candidates[2].getNumVotes() == 0);
        TEST(candidates[3].getNumVotes() == 0);

        TEST(voting_iteration());

        TEST(voting_count_running() == 2);
        TEST(candidates[0].getNumVotes() == 3);
        TEST(candidates[1].getNumVotes() == 3);
        TEST(candidates[2].getNumVotes() == 0);
        TEST(candidates[3].getNumVotes() == 0);
    }

    void test_voting_print_1() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));

        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "1 2"));
        count_ballot(Ballot(2, "2 1"));

        ostringstream w;
        voting_print(w);
        TEST(w.str() == "Tri Nguyen\n");
    }

    void test_voting_print_2() {
        candidates.clear();
        candidates.push_back(canGen(0));
        candidates.push_back(canGen(1));
        candidates.push_back(canGen(2));

        count_ballot(Ballot(3, "1 2 3"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "1 3 2"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "2 1 3"));
        count_ballot(Ballot(3, "3 1 2"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));
        count_ballot(Ballot(3, "3 2 1"));

        ostringstream w;
        voting_print(w);
        TEST(w.str() == "John Doe\n");
    }

    void test_voting_print_3() {
        candidates.clear();

        candidates.push_back(Candidate("Red"));
        candidates.push_back(Candidate("Green"));
        candidates.push_back(Candidate("Blue"));
        candidates.push_back(Candidate("Orange"));

        count_ballot(Ballot(4, "1 2 3 4"));
        count_ballot(Ballot(4, "2 1 3 4"));
        count_ballot(Ballot(4, "2 3 1 4"));
        count_ballot(Ballot(4, "1 2 3 4"));
        count_ballot(Ballot(4, "3 4 1 2"));
        count_ballot(Ballot(4, "4 3 2 1"));

        ostringstream w;
        voting_print(w);
        TEST(w.str() == "Red\nGreen\n");
    }

    void test_voting_solve_1() {
        istringstream r("1\n\n"
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 1 3 4\n"
                        "2 3 1 4\n"
                        "1 2 3 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n\n");
        ostringstream w;
        voting_solve(r, w);
        TEST(w.str() == "Red\nGreen\n");
    }

    void test_voting_solve_2() {
        istringstream r("1\n\n"
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 1 3 4\n"
                        "2 3 1 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n\n");
        ostringstream w;
        voting_solve(r, w);
        TEST(w.str() == "Green\n");
    }

    void test_voting_solve_3() {
        istringstream r("2\n\n"
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 3 1 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n\n"
                        "2\n"
                        "Tri\nDoug\n"
                        "1 2\n"
                        "2 1\n"
                        "1 2\n"
                        "2 1\n\n");
        ostringstream w;
        voting_solve(r, w);
        TEST(w.str() == "Red\nGreen\nBlue\nOrange\n\n"
        "Tri\nDoug\n");
    }

    void test_voting_solve_4() {
        istringstream r("1\n\n"
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 3 1 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n\n");
        ostringstream w;
        voting_solve(r, w);
        TEST(w.str() == "Red\nGreen\nBlue\nOrange\n");
    }

    void test_voting_solve_5() {
        istringstream r("2\n\n"
                        "1\n"
                        "Tri\n"
                        "1\n"
                        "1\n"
                        "1\n"
                        "1\n\n"
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 3 1 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n\n");
        ostringstream w;
        voting_solve(r, w);
        TEST(w.str() == "Tri\n\nRed\nGreen\nBlue\nOrange\n");
    }

    // -----
    // suite
    // -----

CPPUNIT_TEST_SUITE(TestVoting);
        CPPUNIT_TEST(test_count_ballot_1);
        CPPUNIT_TEST(test_count_ballot_2);
        CPPUNIT_TEST(test_count_ballot_3);
        CPPUNIT_TEST(test_read_1);
        CPPUNIT_TEST(test_read_2);
        CPPUNIT_TEST(test_read_3);
        CPPUNIT_TEST(test_voting_count_running_1);
        CPPUNIT_TEST(test_voting_count_running_2);
        CPPUNIT_TEST(test_voting_count_running_3);
        CPPUNIT_TEST(test_voting_iteration_1);
        CPPUNIT_TEST(test_voting_iteration_2);
        CPPUNIT_TEST(test_voting_iteration_3);
        CPPUNIT_TEST(test_voting_print_1);
        CPPUNIT_TEST(test_voting_print_2);
        CPPUNIT_TEST(test_voting_print_3);
        CPPUNIT_TEST(test_voting_solve_1);
        CPPUNIT_TEST(test_voting_solve_2);
        CPPUNIT_TEST(test_voting_solve_3);
        CPPUNIT_TEST(test_voting_solve_4);
        CPPUNIT_TEST(test_voting_solve_5);
    CPPUNIT_TEST_SUITE_END();
};
// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestCandidate::suite());
    tr.addTest(TestBallot::suite());
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
