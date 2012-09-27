// --------------------------------
// projects/voting/TestVoting.c++
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

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"
#include <vector>
#include <map>
#include <queue>

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
		
// ----
// Test voting_solve
// ----    

		void test_solve () {
            std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		    std::ostringstream w;
            voting_solve(r, w);

            CPPUNIT_ASSERT(w.str().compare("John Doe") == 1);        
		}
        
		void test_solve_multicase() {
            std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		    std::ostringstream w;
            voting_solve(r, w);
            CPPUNIT_ASSERT(w.str().compare("John Doe\n\nJohn Doe") == 1);        
		}

        void test_solve_multicase2() {
            std::istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		    std::ostringstream w;
            voting_solve(r, w);
            CPPUNIT_ASSERT(w.str().compare("John Doe\n\nJohn Doe\n\nJohn Doe") == 1);        
		}

// ----
// Test candidateCompare
// ----   
        void test_candidate_compare () {
            Candidate candidate;
            candidate.setPosition(1);
            candidate.setNumVotes(9001);
            
            Candidate candidate2;
            candidate2.setPosition(2);
            candidate2.setNumVotes(9000);

            CPPUNIT_ASSERT(candidateCompare(candidate, candidate2) == 1);        
		}
        
        void test_candidate_compare_tieVotes () {
            Candidate candidate;
            candidate.setPosition(1);
            candidate.setNumVotes(9001);
            
            Candidate candidate2;
            candidate2.setPosition(2);
            candidate2.setNumVotes(9001);

            CPPUNIT_ASSERT(candidateCompare(candidate2, candidate) == 0);        
		}

        void test_candidate_compare_lessvotes () {
            Candidate candidate;
            candidate.setPosition(1);
            candidate.setNumVotes(9001);
            
            Candidate candidate2;
            candidate2.setPosition(2);
            candidate2.setNumVotes(9000);

            CPPUNIT_ASSERT(candidateCompare(candidate2, candidate) == 0);
		}

// ----
// Test read
// ---- 

        void test_read () {
            std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		    
            int numCases = 0;
            r >> numCases;
            vector<Candidate> candidates;
            map<int, queue<queue<int>>> ballotsMap;
            int numBallots;
            voting_read(r, candidates, ballotsMap, numBallots);

            CPPUNIT_ASSERT(numBallots == 5);

            CPPUNIT_ASSERT( candidates[0].getName() == "John Doe"); 
            CPPUNIT_ASSERT( candidates[0].getNumVotes() == 2);
            CPPUNIT_ASSERT( candidates[0].getPosition() == 1);

            CPPUNIT_ASSERT( candidates[1].getName() == "Jane Smith"); 
            CPPUNIT_ASSERT( candidates[1].getNumVotes() == 2);
            CPPUNIT_ASSERT( candidates[1].getPosition() == 2);

            CPPUNIT_ASSERT( candidates[2].getName() == "Sirhan Sirhan"); 
            CPPUNIT_ASSERT( candidates[2].getNumVotes() == 1);
            CPPUNIT_ASSERT( candidates[2].getPosition() == 3);
            
       
		}

        void test_read_2 () {
            std::istringstream r("1\n\n4\nJohn Doe\nJane Smith\nSirhan Sirhan\nDowning\n1 2 3 4\n4 2 1 3\n2 4 3 1\n1 2 4 3\n4 3 1 2");
		    
            int numCases = 0;
            r >> numCases;
            vector<Candidate> candidates;
            map<int, queue<queue<int>>> ballotsMap;
            int numBallots;
            voting_read(r, candidates, ballotsMap, numBallots);

            CPPUNIT_ASSERT(numBallots == 5);

            CPPUNIT_ASSERT( candidates[1].getName() == "Downing"); 
            CPPUNIT_ASSERT( candidates[1].getNumVotes() == 2);
            CPPUNIT_ASSERT( candidates[1].getPosition() == 4);

            CPPUNIT_ASSERT( candidates[0].getName() == "John Doe"); 
            CPPUNIT_ASSERT( candidates[0].getNumVotes() == 2);
            CPPUNIT_ASSERT( candidates[0].getPosition() == 1);

            CPPUNIT_ASSERT( candidates[2].getName() == "Jane Smith"); 
            CPPUNIT_ASSERT( candidates[2].getNumVotes() == 1);
            CPPUNIT_ASSERT( candidates[2].getPosition() == 2);

            CPPUNIT_ASSERT( candidates[3].getName() == "Sirhan Sirhan"); 
            CPPUNIT_ASSERT( candidates[3].getNumVotes() == 0);
            CPPUNIT_ASSERT( candidates[3].getPosition() == 3);
            
       
		}

        void test_read_3 () {
            std::istringstream r("1\n\n1\nJohn Doe\n1\n1\n1\n1\n1");
		    
            int numCases = 0;
            r >> numCases;
            vector<Candidate> candidates;
            map<int, queue<queue<int>>> ballotsMap;
            int numBallots;
            voting_read(r, candidates, ballotsMap, numBallots);

            CPPUNIT_ASSERT(numBallots == 5);

            CPPUNIT_ASSERT( candidates[0].getName() == "John Doe"); 
            CPPUNIT_ASSERT( candidates[0].getNumVotes() == 5);
            CPPUNIT_ASSERT( candidates[0].getPosition() == 1);           
		}

// ----
// Test eval
// ---- 

        void test_eval_transfer() {
            vector<Candidate> candidates;
            Candidate c;
            c.setName("John Doe");
            c.setPosition(1);
            c.setNumVotes(2);

            Candidate c2;
            c2.setName("Jane Smith");
            c2.setPosition(2);
            c2.setNumVotes(2);
            
            Candidate c3;
            c3.setName("Sirhan Sirhan");
            c3.setPosition(3);
            c3.setNumVotes(1);
            candidates.push_back(c);
            candidates.push_back(c2);
            candidates.push_back(c3);

            map<int, queue<queue<int>>> ballotsMap;
            
            queue<queue<int>> ballotHolder1;
            queue<queue<int>> ballotHolder2;
            queue<queue<int>> ballotHolder3;

            queue<int> ballot1a;
            ballot1a.push(2);
            ballot1a.push(3);

            ballotHolder1.push(ballot1a);

            queue<int> ballot1b;
            ballot1b.push(2);
            ballot1b.push(3);

            ballotHolder1.push(ballot1b);

            ballotsMap[1] = ballotHolder1;

            queue<int> ballot2a;
            ballot2a.push(1);
            ballot2a.push(3);

            ballotHolder2.push(ballot2a);

            queue<int> ballot2b;
            ballot2b.push(1);
            ballot2b.push(3);

            ballotHolder2.push(ballot2b);

            ballotsMap[2] = ballotHolder2;

            queue<int> ballot3a;
            ballot3a.push(1);
            ballot3a.push(2);

            ballotHolder3.push(ballot3a);

            ballotsMap[3] = ballotHolder3;
            
            int numBallots = 5;
            CPPUNIT_ASSERT(voting_eval(candidates,ballotsMap, numBallots) == "John Doe");

        }

        void test_eval_tie() {
            vector<Candidate> candidates;
            Candidate c;
            c.setName("John Doe");
            c.setPosition(1);
            c.setNumVotes(2);

            Candidate c2;
            c2.setName("Jane Smith");
            c2.setPosition(2);
            c2.setNumVotes(2);
            
            Candidate c3;
            c3.setName("Sirhan Sirhan");
            c3.setPosition(3);
            c3.setNumVotes(2);
            candidates.push_back(c);
            candidates.push_back(c2);
            candidates.push_back(c3);

            map<int, queue<queue<int>>> ballotsMap;
            
            queue<queue<int>> ballotHolder1;
            queue<queue<int>> ballotHolder2;
            queue<queue<int>> ballotHolder3;

            queue<int> ballot1a;
            ballot1a.push(2);
            ballot1a.push(3);

            ballotHolder1.push(ballot1a);

            queue<int> ballot1b;
            ballot1b.push(2);
            ballot1b.push(3);

            ballotHolder1.push(ballot1b);

            ballotsMap[1] = ballotHolder1;

            queue<int> ballot2a;
            ballot2a.push(1);
            ballot2a.push(3);

            ballotHolder2.push(ballot2a);

            queue<int> ballot2b;
            ballot2b.push(1);
            ballot2b.push(3);

            ballotHolder2.push(ballot2b);

            ballotsMap[2] = ballotHolder2;

            queue<int> ballot3a;
            ballot3a.push(1);
            ballot3a.push(2);

            ballotHolder3.push(ballot3a);

            queue<int> ballot3b;
            ballot3b.push(1);
            ballot3b.push(2);

            ballotHolder3.push(ballot3b);

            ballotsMap[3] = ballotHolder3;
            
            int numBallots = 6;
            CPPUNIT_ASSERT(voting_eval(candidates,ballotsMap, numBallots) == "John Doe\nJane Smith\nSirhan Sirhan");

        }

        void test_eval_outright_winner() {
            vector<Candidate> candidates;
            Candidate c;
            c.setName("John Doe");
            c.setPosition(1);
            c.setNumVotes(0);

            Candidate c2;
            c2.setName("Jane Smith");
            c2.setPosition(2);
            c2.setNumVotes(0);
            
            Candidate c3;
            c3.setName("Sirhan Sirhan");
            c3.setPosition(3);
            c3.setNumVotes(2);
            candidates.push_back(c3);
            candidates.push_back(c);
            candidates.push_back(c2);

            map<int, queue<queue<int>>> ballotsMap;
            
            queue<queue<int>> ballotHolder1;
            queue<queue<int>> ballotHolder2;
            queue<queue<int>> ballotHolder3;

            queue<int> ballot3a;
            ballot3a.push(2);
            ballot3a.push(1);

            ballotHolder3.push(ballot3a);

            queue<int> ballot3b;
            ballot3b.push(2);
            ballot3b.push(1);

            ballotHolder3.push(ballot3b);

            ballotsMap[1] = ballotHolder1;

            ballotsMap[2] = ballotHolder2;

            ballotsMap[3] = ballotHolder3;
            
            int numBallots = 2;
            CPPUNIT_ASSERT(voting_eval(candidates,ballotsMap, numBallots) == "Sirhan Sirhan");

        }

// -----
// print
// -----

        void test_print () {
            std::ostringstream w;
            voting_print(w, "John Doe\nJane Smith\nSirhan Sirhan");
            CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}

        void test_print2 () {
            std::ostringstream w;
            voting_print(w, "John Doe");
            CPPUNIT_ASSERT(w.str() == "John Doe\n");}

        void test_print3 () {
            std::ostringstream w;
            voting_print(w, "");
            CPPUNIT_ASSERT(w.str() == "\n");}

	    CPPUNIT_TEST_SUITE(TestVoting);
        CPPUNIT_TEST(test_solve);
	    CPPUNIT_TEST(test_solve_multicase);
	    CPPUNIT_TEST(test_solve_multicase2);

        CPPUNIT_TEST(test_candidate_compare);
        CPPUNIT_TEST(test_candidate_compare_tieVotes);
        CPPUNIT_TEST(test_candidate_compare_lessvotes);

        CPPUNIT_TEST(test_read);
        CPPUNIT_TEST(test_read_2);
        CPPUNIT_TEST(test_read_3);

        CPPUNIT_TEST(test_eval_transfer);
        CPPUNIT_TEST(test_eval_tie);
        CPPUNIT_TEST(test_eval_outright_winner);

        CPPUNIT_TEST(test_print);
        CPPUNIT_TEST(test_print2);
        CPPUNIT_TEST(test_print3);

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
    return 0;
}
