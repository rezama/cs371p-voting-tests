// --------------------------------
// cs371p-voting/TestVoting.c++
// Copyright (C) 2012
// Collin T. Sykora
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

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {

	// -----
    // read_instances
    // -----
    
	void test_read_instances () {
        std::istringstream r("1\n");
        int i;
        const bool b = voting_read_instances(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);}
		
	void test_read_instances_max () {
        std::istringstream r("32767\n");
        int i;
        const bool b = voting_read_instances(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 32767);}
	
	void test_read_instances_false () {
        std::istringstream r("");	
        int i;
        const bool b = voting_read_instances(r, i);
        CPPUNIT_ASSERT(b == false);}

	// -----
    // read_candidates
    // -----
	void test_read_candidates () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirha");
      	vector<string> names;
        const bool b = voting_read_candidates(r, names);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 3);		
        CPPUNIT_ASSERT(names[0] 	== "John Doe");		
        CPPUNIT_ASSERT(names[1] 	== "Jane Smith");	
        CPPUNIT_ASSERT(names[2] 	== "Sirhan Sirha");}	

	void test_read_candidates_one () {
        std::istringstream r("1\n1");
      	vector<string> names;
        const bool b = voting_read_candidates(r, names);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 1);		
        CPPUNIT_ASSERT(names[0] 	== "1");}	

	void test_read_candidates_mult_lines () {
        std::istringstream r("1\n1\n189237189jdj89jjiaojfw\n\n\n\nijworij\n\n");
      	vector<string> names;
        const bool b = voting_read_candidates(r, names);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 1);		
        CPPUNIT_ASSERT(names[0] 	== "1");}	

	// -----
    // read_ballots
    // -----

	void test_read_ballots () {
		std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		vector<Ballot> v;
		int numCands = 3;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		
		int totalBallots;
		voting_read_ballots(r, votesPerCandidate, totalBallots);
		CPPUNIT_ASSERT(totalBallots == 5);
		CPPUNIT_ASSERT(votesPerCandidate[0].size() == 0);
		CPPUNIT_ASSERT(votesPerCandidate[1].size() == 2);
		CPPUNIT_ASSERT(votesPerCandidate[2].size() == 2);
		CPPUNIT_ASSERT(votesPerCandidate[3].size() == 1);}

	void test_read_ballots_one () {
		std::istringstream r("1");
		vector<Ballot> v;
		int numCands = 1;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		
		int totalBallots;
		voting_read_ballots(r, votesPerCandidate, totalBallots);
		CPPUNIT_ASSERT(totalBallots == 1);
		CPPUNIT_ASSERT(votesPerCandidate[0].size() == 0);
		CPPUNIT_ASSERT(votesPerCandidate[1].size() == 1);}

	void test_read_ballots_mult_lines () {
		std::istringstream r("1\n\n2\nCollin\nSykora\n");
		vector<Ballot> v;
		int numCands = 1;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		
		int totalBallots;
		voting_read_ballots(r, votesPerCandidate, totalBallots);
		CPPUNIT_ASSERT(totalBallots == 1);
		CPPUNIT_ASSERT(votesPerCandidate[0].size() == 0);
		CPPUNIT_ASSERT(votesPerCandidate[1].size() == 1);}


	// -----
    // eval
    // -----
		
	void test_eval () {
		vector<Ballot> v;
		int numCands = 3;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		vector<Ballot> oneVotes;
		vector<Ballot> twoVotes;
		vector<Ballot> threeVotes;

		Ballot ballot1;
		ballot1.voteList.push_back(1);
		ballot1.voteList.push_back(2);
		ballot1.voteList.push_back(3);
		ballot1.voteListIdx = 0;
		oneVotes.push_back(ballot1);
		
		Ballot ballot2;
		ballot2.voteList.push_back(2);
		ballot2.voteList.push_back(1);
		ballot2.voteList.push_back(3);
		ballot2.voteListIdx = 0;
		twoVotes.push_back(ballot2);

		Ballot ballot3;
		ballot3.voteList.push_back(2);
		ballot3.voteList.push_back(3);
		ballot3.voteList.push_back(1);
		ballot3.voteListIdx = 0;
		twoVotes.push_back(ballot3);
		
		Ballot ballot4;
		ballot4.voteList.push_back(1);
		ballot4.voteList.push_back(2);
		ballot4.voteList.push_back(3);
		ballot4.voteListIdx = 0;
		oneVotes.push_back(ballot4);

		Ballot ballot5;
		ballot5.voteList.push_back(3);
		ballot5.voteList.push_back(1);
		ballot5.voteList.push_back(2);
		ballot5.voteListIdx = 0;
		threeVotes.push_back(ballot5);

		votesPerCandidate[1] = oneVotes;
		votesPerCandidate[2] = twoVotes;
		votesPerCandidate[3] = threeVotes;

		int t = 5;
		vector<int> w;
		voting_eval(t , votesPerCandidate, w);
		CPPUNIT_ASSERT(w.size() == 1);
		CPPUNIT_ASSERT(w[0] == 1);}

	void test_eval_one_ballot () {
		vector<Ballot> v;
		int numCands = 3;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		vector<Ballot> oneVotes;

		Ballot ballot1;
		ballot1.voteList.push_back(1);
		ballot1.voteList.push_back(2);
		ballot1.voteList.push_back(3);
		ballot1.voteListIdx = 0;
		oneVotes.push_back(ballot1);
		
		votesPerCandidate[1] = oneVotes;

		int t = 1;
		vector<int> w;
		voting_eval(t , votesPerCandidate, w);
		CPPUNIT_ASSERT(w.size() == 1);
		CPPUNIT_ASSERT(w[0] == 1);}

	void test_eval_one_cand () {
		vector<Ballot> v;
		int numCands = 1;
		vector<vector<Ballot> > votesPerCandidate(numCands + 1, v);
		vector<Ballot> oneVotes;

		Ballot ballot1;
		ballot1.voteList.push_back(1);
		ballot1.voteListIdx = 0;
		oneVotes.push_back(ballot1);
		
		votesPerCandidate[1] = oneVotes;

		int t = 1;
		vector<int> w;
		voting_eval(t , votesPerCandidate, w);
		CPPUNIT_ASSERT(w.size() == 1);
		CPPUNIT_ASSERT(w[0] == 1);}

	// -----
    // print
    // -----

	void test_print () {
        std::ostringstream w;
		std::vector<string> v;
		v.push_back("Collin Sykora");
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Collin Sykora\n");}

	void test_print_two () {
        std::ostringstream w;
		std::vector<string> v;
		v.push_back("Collin");
		v.push_back("Sykora");
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Collin\nSykora\n");}

	void test_print_mult () {
        std::ostringstream w;
		std::vector<string> v;
		v.push_back("Collin");
		v.push_back("Sykora");
		v.push_back("is");
		v.push_back("in");
		v.push_back("OOP");
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Collin\nSykora\nis\nin\nOOP\n");}
	// -----
    // solve
    // -----
    
	void test_solve () {
		std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirha\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
		voting_solve (r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");}

	void test_solve_two_winners () {
		std::istringstream r("1\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1");
        std::ostringstream w;
		voting_solve (r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\n");}

	void test_solve_two_runs () {
		std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirha\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nJohn Doe\nJane Smith\n1 2\n2 1");
        std::ostringstream w;
		voting_solve (r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\n");}
		
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_instances);
	CPPUNIT_TEST(test_read_instances_max);
	CPPUNIT_TEST(test_read_instances_false);
	CPPUNIT_TEST(test_read_candidates);
	CPPUNIT_TEST(test_read_candidates_one);
	CPPUNIT_TEST(test_read_candidates_mult_lines);
	CPPUNIT_TEST(test_read_ballots);
	CPPUNIT_TEST(test_read_ballots_one);
	CPPUNIT_TEST(test_read_ballots_mult_lines);
	CPPUNIT_TEST(test_eval);
	CPPUNIT_TEST(test_eval_one_ballot);
	CPPUNIT_TEST(test_eval_one_cand);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_two);
	CPPUNIT_TEST(test_print_mult);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_two_winners);
	CPPUNIT_TEST(test_solve_two_runs);
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
