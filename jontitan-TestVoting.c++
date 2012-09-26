// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2012
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <queue>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // readCandidates
    // ----

    void test_readCandidates_1 () {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
        std::vector<string> candidates;
        voting_readCandidates(r, candidates, 3);
        CPPUNIT_ASSERT(candidates.size() == 3);
        CPPUNIT_ASSERT(candidates[0] == "John Doe");
        CPPUNIT_ASSERT(candidates[1] == "Jane Smith");
        CPPUNIT_ASSERT(candidates[2] == "Sirhan Sirhan");
    }
    
    void test_readCandidates_2 () {
        std::istringstream r("");
        std::vector<string> candidates;
        voting_readCandidates(r, candidates, 0);
        CPPUNIT_ASSERT(candidates.size() == 0);
    }
    
    void test_readCandidates_3 () {
        std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\nAbe Lincoln");
        std::vector<string> candidates;
        voting_readCandidates(r, candidates, 4);
        CPPUNIT_ASSERT(candidates.size() == 4);
        CPPUNIT_ASSERT(candidates[0] == "John Doe");
        CPPUNIT_ASSERT(candidates[1] == "Jane Smith");
        CPPUNIT_ASSERT(candidates[2] == "Sirhan Sirhan");
        CPPUNIT_ASSERT(candidates[3] == "Abe Lincoln");
    }
    
    void test_readBallots_1 () {
        std::istringstream r("1 2 3\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(ballots[0].size() == 3);
        for(unsigned int i=0; i<3; ++i){
            CPPUNIT_ASSERT(ballots[0].front() == i+1);
            ballots[0].pop();
        }
    }
    
    void test_readBallots_2 () {
        std::istringstream r("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 19);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(ballots[0].size() == 19);
        for(unsigned int i=0; i<19; ++i){
            CPPUNIT_ASSERT(ballots[0].front() == i+1);
            ballots[0].pop();
        }
    }
    
    void test_readBallots_3 () {
        std::istringstream r("1 2 3\n1 2 3\n1 2 3\n1 2 3\n1 2 3\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        CPPUNIT_ASSERT(ballots.size() == 5);
        for(unsigned int x=0; x< ballots.size(); ++x){
            CPPUNIT_ASSERT(ballots[x].size() == 3);
            for(unsigned int i=0; i<3; ++i){
                CPPUNIT_ASSERT(ballots[x].front() == i+1);
                ballots[x].pop();
            }
        }
    }
    
    void test_readBallots_4 () {
        std::istringstream r("1 2 3 4 5 6 7 8 9 10\n1 2 3 4 5 6 7 8 9 10\n1 2 3 4 5 6 7 8 9 10\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 10);
        CPPUNIT_ASSERT(ballots.size() == 3);
        for(unsigned int x=0; x< ballots.size(); ++x){
            CPPUNIT_ASSERT(ballots[x].size() == 10);
            for(unsigned int i=0; i<10; ++i){
                CPPUNIT_ASSERT(ballots[x].front() == i+1);
                ballots[x].pop();
            }
        }
    }
    
    void test_readBallots_5 () {
        std::istringstream r("\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 0);
        CPPUNIT_ASSERT(ballots.size() == 0);
    }
    
    void test_evictCandidate_1(){
        std::vector<int> losers;
        std::istringstream r("1 2 3\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        voting_evictCandidate(ballots, losers, 1, 0);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(ballots[0].size() == 2);
        CPPUNIT_ASSERT(ballots[0].front() == 2);
    }
    
    void test_evictCandidate_2(){
        std::vector<int> losers;
        losers.push_back(2);
        std::istringstream r("1 2 3\n2 1 3\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        voting_evictCandidate(ballots, losers, 1, 0);
        CPPUNIT_ASSERT(ballots.size() == 2);
        CPPUNIT_ASSERT(ballots[0].size() == 1);
        CPPUNIT_ASSERT(ballots[0].front() == 3);
        CPPUNIT_ASSERT(ballots[1].size() == 3);
        CPPUNIT_ASSERT(ballots[1].front() == 2);
    }
    
    void test_evictCandidate_3(){
        std::vector<int> losers;
        losers.push_back(2);
        losers.push_back(3);
        std::istringstream r("1 2 3\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        voting_evictCandidate(ballots, losers, 1, 0);
        CPPUNIT_ASSERT(ballots.size() == 1);
        CPPUNIT_ASSERT(ballots[0].size() == 0);
        CPPUNIT_ASSERT(ballots[0].empty());
    }
    
    void test_eval_1(){
        std::istringstream r("1 2 3\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        vector<int> winners = voting_eval(ballots, 3);
        CPPUNIT_ASSERT(winners.size() == 1);
        CPPUNIT_ASSERT(winners[0] == 1);
    }
    
    void test_eval_2(){
        std::istringstream r("1 2 3\n2 1 3\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        vector<int> winners = voting_eval(ballots, 3);
        CPPUNIT_ASSERT(winners.size() == 2);
        CPPUNIT_ASSERT(winners[0] == 1);
        CPPUNIT_ASSERT(winners[1] == 2);
    }
    
    void test_eval_3(){
        std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        vector<int> winners = voting_eval(ballots, 3);
        CPPUNIT_ASSERT(winners.size() == 1);
        CPPUNIT_ASSERT(winners[0] == 1);
    }
    
    void test_eval_4(){
        std::istringstream r("1 2 3\n2 1 3\n3 2 1\n\n");
        std::vector<std::queue<unsigned int> > ballots;
        voting_readBallots(r, ballots, 3);
        vector<int> winners = voting_eval(ballots, 3);
        CPPUNIT_ASSERT(winners.size() == 3);
        CPPUNIT_ASSERT(winners[0] == 1);
        CPPUNIT_ASSERT(winners[1] == 2);
        CPPUNIT_ASSERT(winners[2] == 3);
    }
    
    void test_print_1(){
        std::ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe");
        vector<int> winners;
        winners.push_back(1);
        voting_print(candidates, winners, w, true);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    void test_print_2(){
        std::ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe1");
        candidates.push_back("John Doe2");
        candidates.push_back("John Doe3");
        vector<int> winners;
        winners.push_back(1);
        voting_print(candidates, winners, w, true);        
        CPPUNIT_ASSERT(w.str() == "John Doe1\n");
    }
    
    void test_print_3(){
        std::ostringstream w;
        vector<string> candidates;
        candidates.push_back("John Doe1");
        candidates.push_back("John Doe2");
        candidates.push_back("John Doe3");
        vector<int> winners;
        winners.push_back(3);
        winners.push_back(2);
        voting_print(candidates, winners, w, true);
        CPPUNIT_ASSERT(w.str() == "John Doe3\nJohn Doe2\n");
    }
    
    void test_solve_1 () {
        std::istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    void test_solve_2 () {
        std::istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");
    }
    
    void test_solve_3 () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSomeone Else\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
    }
    
    
    
    

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_readCandidates_1);
    CPPUNIT_TEST(test_readCandidates_2);
    CPPUNIT_TEST(test_readCandidates_3);
    CPPUNIT_TEST(test_readBallots_1);
    CPPUNIT_TEST(test_readBallots_2);
    CPPUNIT_TEST(test_readBallots_3);
    CPPUNIT_TEST(test_readBallots_4);
    CPPUNIT_TEST(test_readBallots_5);
    CPPUNIT_TEST(test_evictCandidate_1);
    CPPUNIT_TEST(test_evictCandidate_2);
    CPPUNIT_TEST(test_evictCandidate_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();
    };
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