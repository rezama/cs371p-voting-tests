
/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <algorithm>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------


struct TestVoting : CppUnit::TestFixture {
    // ----
    // voting_print
    // ----


    void test_print () {
	std::vector<std::string> names;
	names.push_back("howard");
	names.push_back("fu");
	std::vector< std::vector<ballot> > dummy;
        int p = voting_print(0, names, dummy);
        CPPUNIT_ASSERT(p == 0);}
   
    void test_print_2 () {
	std::vector<std::string> names;
	names.push_back("howard");
	names.push_back("fu");
	std::vector< std::vector<ballot> > dummy;
        int p = voting_print(1, names, dummy);
        CPPUNIT_ASSERT(p == 1);}

    void test_print_3 () {
	std::vector<std::string> names;
	names.push_back("howard");
	names.push_back("fu");
	std::vector< std::vector<ballot> > dummy;
        int p = voting_print(-1, names, dummy);
        CPPUNIT_ASSERT(p == -1);}


    // -----
    // doLogic
    // -----

   void test_logic() {
        std::string a("howard");
	std::string b("fu");
	std::vector<std::string> name;
	name.push_back(a);
	name.push_back(b);
	std::vector< std::vector<ballot> > dummy(2);
	doLogic(dummy, name, 1);
	CPPUNIT_ASSERT(true);
	}

    void test_logic_2() {
        std::string a("howard");
	std::string b("fu");
	std::string c("me");
	std::vector<std::string> name;
	name.push_back(a);
	name.push_back(b);
	name.push_back(c);
	std::vector< std::vector<ballot> > dummy(3);
	doLogic(dummy, name, 1);
	CPPUNIT_ASSERT(true);
	}

    void test_logic_3() {
        std::string a("howard");
	std::vector<std::string> name;
	name.push_back(a);
	std::vector< std::vector<ballot> > dummy(1);
	doLogic(dummy, name, 1);
	CPPUNIT_ASSERT(true);
	}

    // -----
    // voting_solve
    // -----

    void test_solve () {
        std::istringstream r("0");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(true);}

    void test_solve_2() {
        std::istringstream r("1\n\n5\nHoward\nBob\nRyan\nRachel\nAdam\n1 2 3 4 5\n2 3 1 4 5\n1 2 3 5 4\n3 2 1 5 4");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(true);
	}

    void test_solve_3() {
        std::istringstream r("2\n\n3\nHoward\nBob\nRyan\n1 2 3\n2 3 1\n1 2 3\n3 2 1\n\n3\nHoward\nBob\nRyan\n1 2 3\n2 3 1\n1 2 3\n3 2 1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(true);
	}




    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_logic);
    CPPUNIT_TEST(test_logic_2);
    CPPUNIT_TEST(test_logic_3);
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
