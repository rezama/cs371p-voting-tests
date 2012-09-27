// --------------------------------
// projects/collatz/TestCollatz.c++
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

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture 
{

	// -----
    // Next Candidate
    // -----
	void test_next_candidate_1 () 
	{
	    std::istringstream r("Moises Hermosillo\n");
	    std::string name;
	    next_candidate(r,name);
		CPPUNIT_ASSERT(name.compare("Moises Hermosillo")==0);
	}
	void test_next_candidate_2 () 
	{
		std::istringstream r("Hello Moto\n");
	    std::string name;
	    next_candidate(r,name);
		CPPUNIT_ASSERT(name.compare("Hello Moto")==0);
	}
	void test_next_candidate_3 () 
	{
		std::istringstream r("Final Fantasy\n");
	    std::string name;
	    next_candidate(r,name);
		CPPUNIT_ASSERT(name.compare("Final Fantasy")==0);
	}
	
	
    // ----
    // read_candidates
    // ----
    void test_read_candidates_1 () 
	{
	    std::istringstream r("Hello Moto\nMoises Hermosillo\nFinal Fantasy");
        std::vector<candidate> candidates;
        int x=3;
        read_candidates(r,x,candidates);
        CPPUNIT_ASSERT(candidates[0].name.compare("Hello Moto") == 0);
	}
	
	void test_read_candidates_2 () 
	{
	    int x=3;
	    std::istringstream r("Hello Moto\nMoises Hermosillo\nFinal Fantasy");
        std::vector<candidate> candidates;
        read_candidates(r,x,candidates);
        CPPUNIT_ASSERT(candidates[1].name.compare("Moises Hermosillo") == 0);
	}
	
	void test_read_candidates_3 () 
	{
	    int x=3;
	    std::istringstream r("Hello Moto\nMoises Hermosillo\nFinal Fantasy");
        std::vector<candidate> candidates;
        read_candidates(r,x,candidates);
        CPPUNIT_ASSERT(candidates[2].name.compare("Final Fantasy") == 0);
	}

    // ----
    // read_ballots
    // ----
    
    void test_read_ballots_1 () 
	{
	    int total=5;
	    std::ostringstream w;
	    std::vector<candidate> candidates;
	    std::istringstream d("2 3 1\n1 2 3\n3 2 1\n2 1 3\n3 2 1\n\n");
	    int x=3;
        read_ballots(d,x,w,candidates,total);
        CPPUNIT_ASSERT(candidates[0].votes==1);
	}

    void test_read_ballots_2 () 
	{
	    int total=5;
	    std::ostringstream w;
	    std::vector<candidate> candidates;
	    std::istringstream d("2 3 1\n1 2 3\n3 2 1\n2 1 3\n3 2 1\n\n");
	    int x=3;
        read_ballots(d,x,w,candidates,total);
        CPPUNIT_ASSERT(candidates[1].votes==2);
	}

    void test_read_ballots_3 () 
	{
	    int total=5;
	    std::ostringstream w;
	    std::vector<candidate> candidates;
	    std::istringstream d("2 3 1\n1 2 3\n3 2 1\n2 1 3\n3 2 1\n\n");
	    int x=3;
        read_ballots(d,x,w,candidates,total);
        CPPUNIT_ASSERT(candidates[2].votes==2);
    }

    // -----
    // print
    // -----

    void test_print () 
	{
	    std::istringstream r("Hello Moto\nMoises Hermosillo\nFinal Fantasy");
        std::vector<candidate> candidates;
        int x=3;
        read_candidates(r,x,candidates);
        std::ostringstream w;
        print_candidates(w,candidates,x);
        CPPUNIT_ASSERT(w.str() == "Hello Moto\nMoises Hermosillo\nFinal Fantasy");
	}

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_next_candidate_1);
	CPPUNIT_TEST(test_next_candidate_2);
	CPPUNIT_TEST(test_next_candidate_3);
	
	CPPUNIT_TEST(test_read_candidates_1);
	CPPUNIT_TEST(test_read_candidates_2);
	CPPUNIT_TEST(test_read_candidates_3);
	
	CPPUNIT_TEST(test_read_ballots_1);
	CPPUNIT_TEST(test_read_ballots_2);
	CPPUNIT_TEST(test_read_ballots_3);
	
	CPPUNIT_TEST(test_print);
	
    CPPUNIT_TEST_SUITE_END();};

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
