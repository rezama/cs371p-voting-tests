// --------------------------------------
// josephsw/cs371p-voting/TestVoting.c++
// Copyright (C) 2012
// Joseph S. Wang
// Based on template by Glenn P. Downing
// --------------------------------------

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



    // ----
    // n_read
    // ----

    void test_n_read_1 () {
    	std::istringstream r("1\n");
    	int i;
    	const bool b = voting_n_read(r, i);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 1);
    }

    void test_n_read_2 () {
    	std::istringstream r("10\n");
    	int i;
    	const bool b = voting_n_read(r, i);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 10);
    }

    void test_n_read_3 () {
    	std::istringstream r("20\n");
    	int i;
    	const bool b = voting_n_read(r, i);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i == 20);
    }

    // ----
    // nline_read
    // ----

    void test_nline_read_1 () {
    	std::istringstream r("1 4 3 2\n");
    	int i[4];
    	const bool b = voting_nline_read(r, i);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i[0] == 1);
    	CPPUNIT_ASSERT(i[1] == 4);
    	CPPUNIT_ASSERT(i[2] == 3);
    	CPPUNIT_ASSERT(i[3] == 2);
    }

    void test_nline_read_2 () {
    	std::istringstream r("10 1 2 3 4 5 6 7 8 9\n");
    	int i[10];
    	const bool b = voting_nline_read(r, i);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(i[0] == 10);
    	CPPUNIT_ASSERT(i[1] == 1);
    	CPPUNIT_ASSERT(i[2] == 2);
    	CPPUNIT_ASSERT(i[3] == 3);
    	CPPUNIT_ASSERT(i[4] == 4);
    	CPPUNIT_ASSERT(i[5] == 5);
    	CPPUNIT_ASSERT(i[6] == 6);
    	CPPUNIT_ASSERT(i[7] == 7);
    	CPPUNIT_ASSERT(i[8] == 8);
    	CPPUNIT_ASSERT(i[9] == 9);
    }

    void test_nline_read_3 () {
    	std::istringstream r("\n");
    	int i;
    	const bool b = voting_nline_read(r, &i);
    	CPPUNIT_ASSERT(b == false);
    }

    // ----
    // str_read
    // ----

    void test_str_read_1 () {
    	std::istringstream r("John Doe\n");
    	std::string s;
    	const bool b = voting_str_read(r, s);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(s.compare("John Doe") == 0);
    }

    void test_str_read_2 () {
    	std::istringstream r("Bob Barker\n");
    	std::string s;
    	const bool b = voting_str_read(r, s);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(s.compare("Bob Barker") == 0);
    }

    void test_str_read_3 () {
    	std::istringstream r("Steve Jobs\n");
    	std::string s;
    	const bool b = voting_str_read(r, s);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(s.compare("Steve Jobs") == 0);
    }

    // ----
    // ballot_read
    // ----

    void test_ballot_read_1 () {
    	std::istringstream r("1 2 3 4\n");
    	int n_candidates = 4;
    	ballot bal;
    	const bool b = voting_ballot_read(r, n_candidates, bal);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(bal.position == 0);
    	CPPUNIT_ASSERT(bal.pref[0] == 0);
    	CPPUNIT_ASSERT(bal.pref[1] == 1);
    	CPPUNIT_ASSERT(bal.pref[2] == 2);
    	CPPUNIT_ASSERT(bal.pref[3] == 3);
    }

    void test_ballot_read_2 () {
    	std::istringstream r("3 6 4 1 2 5\n");
    	int n_candidates = 6;
    	ballot bal;
    	const bool b = voting_ballot_read(r, n_candidates, bal);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(bal.position == 0);
    	CPPUNIT_ASSERT(bal.pref[0] == 2);
    	CPPUNIT_ASSERT(bal.pref[1] == 5);
    	CPPUNIT_ASSERT(bal.pref[2] == 3);
    	CPPUNIT_ASSERT(bal.pref[3] == 0);
    	CPPUNIT_ASSERT(bal.pref[4] == 1);
		CPPUNIT_ASSERT(bal.pref[5] == 4);
    }


    void test_ballot_read_3 () {
    	std::istringstream r("12 4 17 7 1 9 8 15 14 19 2 10 6 20 13 11 18 3 16 5\n");
    	int n_candidates = 20;
    	ballot bal;
    	const bool b = voting_ballot_read(r, n_candidates, bal);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(bal.position == 0);
    	CPPUNIT_ASSERT(bal.pref[0] == 11);
    	CPPUNIT_ASSERT(bal.pref[1] == 3);
    	CPPUNIT_ASSERT(bal.pref[2] == 16);
    	CPPUNIT_ASSERT(bal.pref[3] == 6);
    	CPPUNIT_ASSERT(bal.pref[4] == 0);
    	CPPUNIT_ASSERT(bal.pref[5] == 8);
    	CPPUNIT_ASSERT(bal.pref[6] == 7);
    	CPPUNIT_ASSERT(bal.pref[7] == 14);
    	CPPUNIT_ASSERT(bal.pref[8] == 13);
    	CPPUNIT_ASSERT(bal.pref[9] == 18);
    	CPPUNIT_ASSERT(bal.pref[10] == 1);
    	CPPUNIT_ASSERT(bal.pref[11] == 9);
    	CPPUNIT_ASSERT(bal.pref[12] == 5);
    	CPPUNIT_ASSERT(bal.pref[13] == 19);
    	CPPUNIT_ASSERT(bal.pref[14] == 12);
    	CPPUNIT_ASSERT(bal.pref[15] == 10);
    	CPPUNIT_ASSERT(bal.pref[16] == 17);
    	CPPUNIT_ASSERT(bal.pref[17] == 2);
    	CPPUNIT_ASSERT(bal.pref[18] == 15);
    	CPPUNIT_ASSERT(bal.pref[19] == 4);

    }

	// ---------------
	// read_all
	// ---------------

    void test_read_all_1 () {
    	std::istringstream r("2\nApple Pie\nBanana Bob\n1 2\n1 2\n2 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[3];
    	std::string candidates[2];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 2);
    	CPPUNIT_ASSERT(n_ballots == 3);
    	CPPUNIT_ASSERT(candidates[0].compare("Apple Pie") == 0);
    	CPPUNIT_ASSERT(candidates[1].compare("Banana Bob") == 0);
    	CPPUNIT_ASSERT(ballot_array[0].position == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[0] == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[1] == 1);
    	CPPUNIT_ASSERT(ballot_array[1].position == 0);
    	CPPUNIT_ASSERT(ballot_array[1].pref[0] == 0);
    	CPPUNIT_ASSERT(ballot_array[1].pref[1] == 1);
    	CPPUNIT_ASSERT(ballot_array[2].position == 0);
    	CPPUNIT_ASSERT(ballot_array[2].pref[0] == 1);
    	CPPUNIT_ASSERT(ballot_array[2].pref[1] == 0);

    }

    void test_read_all_2 () { //2 person tie
    	std::istringstream r("2\nApple Pie\nBanana Bob\n1 2\n2 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[2];
    	std::string candidates[2];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 2);
    	CPPUNIT_ASSERT(n_ballots == 2);
    	CPPUNIT_ASSERT(candidates[0].compare("Apple Pie") == 0);
    	CPPUNIT_ASSERT(candidates[1].compare("Banana Bob") == 0);
    	CPPUNIT_ASSERT(ballot_array[0].position == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[0] == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[1] == 1);
    	CPPUNIT_ASSERT(ballot_array[1].position == 0);
    	CPPUNIT_ASSERT(ballot_array[1].pref[0] == 1);
    	CPPUNIT_ASSERT(ballot_array[1].pref[1] == 0);
    }


    void test_read_all_3 () { //3 people, 2 tie
    	std::istringstream r("3\nJake\nJim\nElain\n1 2 3\n1 3 2\n2 1 3\n2 3 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[4];
    	std::string candidates[3];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 3);
    	CPPUNIT_ASSERT(n_ballots == 4);
    	CPPUNIT_ASSERT(candidates[0].compare("Jake") == 0);
    	CPPUNIT_ASSERT(candidates[1].compare("Jim") == 0);
    	CPPUNIT_ASSERT(candidates[2].compare("Elain") == 0);
    	CPPUNIT_ASSERT(ballot_array[0].position == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[0] == 0);
    	CPPUNIT_ASSERT(ballot_array[0].pref[1] == 1);
    	CPPUNIT_ASSERT(ballot_array[0].pref[2] == 2);
    	CPPUNIT_ASSERT(ballot_array[1].position == 0);
    	CPPUNIT_ASSERT(ballot_array[1].pref[0] == 0);
    	CPPUNIT_ASSERT(ballot_array[1].pref[1] == 2);
    	CPPUNIT_ASSERT(ballot_array[1].pref[2] == 1);
    	CPPUNIT_ASSERT(ballot_array[2].position == 0);
    	CPPUNIT_ASSERT(ballot_array[2].pref[0] == 1);
    	CPPUNIT_ASSERT(ballot_array[2].pref[1] == 0);
    	CPPUNIT_ASSERT(ballot_array[2].pref[2] == 2);
    	CPPUNIT_ASSERT(ballot_array[3].position == 0);
    	CPPUNIT_ASSERT(ballot_array[3].pref[0] == 1);
    	CPPUNIT_ASSERT(ballot_array[3].pref[1] == 2);
    	CPPUNIT_ASSERT(ballot_array[3].pref[2] == 0);
    }

    // ----
	// print
	// ----

	void test_print_1 () {
        std::ostringstream w;
        voting_print(w, "Hello World");
        CPPUNIT_ASSERT(w.str() == "Hello World");
    }

    void test_print_2 () {
        std::ostringstream w;
        voting_print(w, "Bob Barker\nTed Two");
        CPPUNIT_ASSERT(w.str() == "Bob Barker\nTed Two");
    }

	void test_print_3 () {
        std::ostringstream w;
        voting_print(w, "A\nB\nC\nD\nE");
        CPPUNIT_ASSERT(w.str() == "A\nB\nC\nD\nE");
    }


	// ----
	// eval
	// ----

	void test_eval_1 () {
    	std::istringstream r("2\nApple Pie\nBanana Bob\n1 2\n1 2\n2 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[4];
    	std::string candidates[3];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 2);
    	CPPUNIT_ASSERT(n_ballots == 3);

    	std::string winner = "";
    	voting_eval(ballot_array, candidates, n_candidates, n_ballots, winner);
		assert(winner.compare("Apple Pie") == 0);
	}

    void test_eval_2 () { //2 person tie
    	std::istringstream r("2\nApple Pie\nBanana Bob\n1 2\n2 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[2];
    	std::string candidates[2];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 2);
    	CPPUNIT_ASSERT(n_ballots == 2);
    	
    	std::string winner = "";
    	voting_eval(ballot_array, candidates, n_candidates, n_ballots, winner);
		assert(winner.compare("Apple Pie\nBanana Bob") == 0);
    }

    void test_eval_3 () { //3 people, 2 tie
    	std::istringstream r("3\nJake\nJim\nElain\n1 2 3\n1 3 2\n2 1 3\n2 3 1");
    	int n_candidates, n_ballots;
    	ballot ballot_array[4];
    	std::string candidates[3];
    	const bool b = voting_read_all(r, n_candidates, n_ballots, candidates, ballot_array);
    	CPPUNIT_ASSERT(b == true);
    	CPPUNIT_ASSERT(n_candidates == 3);
    	CPPUNIT_ASSERT(n_ballots == 4);

    	std::string winner = "";
    	voting_eval(ballot_array, candidates, n_candidates, n_ballots, winner);
		assert(winner.compare("Jake\nJim") == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_n_read_1);
    CPPUNIT_TEST(test_n_read_2);
    CPPUNIT_TEST(test_n_read_3);
    CPPUNIT_TEST(test_nline_read_1);
    CPPUNIT_TEST(test_nline_read_2);
    CPPUNIT_TEST(test_nline_read_3);
    CPPUNIT_TEST(test_str_read_1);
    CPPUNIT_TEST(test_str_read_2);
    CPPUNIT_TEST(test_str_read_3);
    CPPUNIT_TEST(test_ballot_read_1);
    CPPUNIT_TEST(test_ballot_read_2);
    CPPUNIT_TEST(test_ballot_read_3);
    CPPUNIT_TEST(test_read_all_1);
    CPPUNIT_TEST(test_read_all_2);
    CPPUNIT_TEST(test_read_all_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
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