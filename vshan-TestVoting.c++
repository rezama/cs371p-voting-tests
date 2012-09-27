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

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <algorithm>
#include <map>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

using namespace std::tr1;
struct TestVoting : CppUnit::TestFixture {

	// Add tests.

	void test_read_1 () {
		std::istringstream r("3\nJohn\nJoe\nJill\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i.size() == 3);
		CPPUNIT_ASSERT(j.size() == 3);
		CPPUNIT_ASSERT(j[0].size() == 2);
		CPPUNIT_ASSERT(j[1].size() == 2);
		CPPUNIT_ASSERT(j[2].size() == 0);
	}

	void test_read_2 () {
		std::istringstream r("1\nJohn\n1\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i.size() == 1);
		CPPUNIT_ASSERT(j.size() == 1);
		CPPUNIT_ASSERT(j[0].size() == 1);
	}

	void test_read_3 () {
		std::istringstream r("1\nJohn\n2\n2\n2\n2\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		CPPUNIT_ASSERT(b == false);
	}

	void test_eval_1 () {
		std::istringstream r("3\nJohn\nJoe\nJill\n1 2 3\n2 1 3\n2 1 3\n2 1 3\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		vector<string> w;
		voting_eval(&i,&j,&w);
		CPPUNIT_ASSERT(w.size() == 1);
		CPPUNIT_ASSERT(w[0] == "Joe");
	}

	void test_eval_2 () {
		std::istringstream r("3\nJohn\nJoe\nJill\n3 2 1\n3 1 2\n3 2 1\n1 2 3\n2 1 3\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		vector<string> w;
		voting_eval(&i,&j,&w);
		CPPUNIT_ASSERT(w.size() == 1);
		CPPUNIT_ASSERT(w[0] == "Jill");;
	}

	void test_eval_3 () {
		std::istringstream r("3\nJohn\nJoe\nJill\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n");
		vector<string> i;
		map<int,vector<list<int> > > j;
		const bool b = voting_read(r, &i, &j);
		vector<string> w;
		voting_eval(&i,&j,&w);
		CPPUNIT_ASSERT(w.size() == 2);
		CPPUNIT_ASSERT(find(w.begin(), w.end(), "John") != w.end());
		CPPUNIT_ASSERT(find(w.begin(), w.end(), "Joe") != w.end());
	}

	void test_print_1() {
		vector<string> v(3);
		v[0] = "John";
		v[1] = "Joe";
		v[2] = "Jill";
		std::ostringstream w;
		voting_print(w, &v);
		CPPUNIT_ASSERT(w.str() == "John\nJoe\nJill\n");
	}

	void test_print_2() {
		vector<string> v(1);
		std::ostringstream w;
		voting_print(w, &v);
		CPPUNIT_ASSERT(w.str() == "\n");
	}

	void test_print_3() {
		vector<string> v(1);
		v[0] = "John";
		std::ostringstream w;
		voting_print(w, &v);
		CPPUNIT_ASSERT(w.str() == "John\n");
	}

	void test_solve_1 () {
		std::istringstream r("1\n\n3\nJohn\nJoe\nJill\n1 2 3\n2 1 3\n2 1 3\n2 1 3\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Joe\n");
	}

	void test_solve_2 () {
		std::istringstream r("2\n\n3\nJohn\nJoe\nJill\n1 2 3\n2 1 3\n2 1 3\n2 1 3\n\n3\nJohn\nJoe\nJill\n1 2 3\n2 1 3\n2 1 3\n2 1 3\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Joe\n\nJoe\n");
	}

	void test_solve_3 () {
		std::istringstream r("0");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "");
	}

	void test_solve_4 () {
		std::istringstream r("1\n\n3\nRed\nBlue\nGreen\n1 2 3\n 1 2 3\n 1 2 3\n\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Red\n");
	}

	void test_solve_5 () {
		std::istringstream r("1\n\n3\nRed\nBlue\nGreen\n1 2 3\n2 1 3\n 3 1 2\n\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Red\nBlue\nGreen\n");
	}

	void test_solve_6 () {
		std::istringstream r("1\n\n5\nGlenn\nRed\nBlue\nGreen\nOrange\n1 2 3 4 5\n1 2 3 4 5\n3 2 1 5 4\n3 2 1 4 5\n2 3 1 4 5\n4 1 3 2 5\n\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Glenn\nBlue\n");
	}

	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_4);
	CPPUNIT_TEST(test_solve_5);
	CPPUNIT_TEST(test_solve_6);
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
