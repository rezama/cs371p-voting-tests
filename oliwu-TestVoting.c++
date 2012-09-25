// --------------------------------
// projects/collatz/TestVoting.c++
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

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_oneline () {
        std::istringstream r("1\nHello World\n");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == true);}
    
    void test_read_multiline () {
        std::istringstream r("3\nPsy\nGangnam\nStyle\n");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == true);}
    
    void test_read_fail () {
        std::istringstream r("");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == false);}
    
    // -----
    // solve
    // -----

    void test_solve_instawin () {
        std::istringstream r("3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
        std::string s = "";
        voting_read(r);
        voting_solve(s);
        CPPUNIT_ASSERT(s.compare("Psy"));}

    void test_solve_instatie () {
        std::istringstream r("3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n");
        std::string s = "";
        voting_read(r);
        voting_solve(s);
        CPPUNIT_ASSERT(s.compare("Psy\nGangnam\nStyle"));}
 
    void test_solve_eventual_tie () {
        std::istringstream r("3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n3 2 1\n3 1 2\n1 3 2\n2 1 3\n3 2 1\n");
        std::string s = "";
        voting_read(r);
        voting_solve(s);
        CPPUNIT_ASSERT(s.compare("Gangnam\nStyle"));}

    void test_solve_eventual_win () {
        std::istringstream r("3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::string s = "";
        voting_read(r);
        voting_solve(s);
        CPPUNIT_ASSERT(s.compare("Psy"));}

    // -----
    // print
    // -----

    void test_print_oneline () {
        std::ostringstream w;
        voting_print(w, "Hello World");
        CPPUNIT_ASSERT(w.str() == "Hello World\n");}

    void test_print_multiline () {
        std::ostringstream w;
        voting_print(w, "Hello\nWorld");
        CPPUNIT_ASSERT(w.str() == "Hello\nWorld\n");}

    void test_print_null () {
        std::ostringstream w;
        voting_print(w, "");
        CPPUNIT_ASSERT(w.str() == "\n");}

    // --
    // go
    // --

    void test_go_instawin () {
        std::istringstream r("1\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n1 3 2\n");
        std::ostringstream w;
        voting_go(r, w);
        CPPUNIT_ASSERT(w.str() == ("Psy\n"));}

    void test_go_instatie () {
        std::istringstream r("1\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n");
        std::ostringstream w;
        voting_go(r, w);
        CPPUNIT_ASSERT(w.str() == ("Psy\nGangnam\nStyle\n"));}
 
    void test_go_eventual_tie () {
        std::istringstream r("1\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n3 2 1\n3 1 2\n1 3 2\n2 1 3\n3 2 1");
        std::ostringstream w;
        voting_go(r, w);
        CPPUNIT_ASSERT(w.str() == ("Gangnam\nStyle\n"));}

    void test_go_eventual_win () {
        std::istringstream r("1\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_go(r, w);
        CPPUNIT_ASSERT(w.str() == ("Psy\n"));}

   void test_go_multi_instance () {
        std::istringstream r("3\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n3 2 1\n3 1 2\n1 3 2\n2 1 3\n3 2 1\n\n3\nPsy\nGangnam\nStyle\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 2 1\n");
        std::ostringstream w;
        voting_go(r, w);
        CPPUNIT_ASSERT(w.str() == ("Psy\n\nGangnam\nStyle\n\nPsy\nGangnam\nStyle\n"));}
 
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_oneline);
    CPPUNIT_TEST(test_read_multiline);
    CPPUNIT_TEST(test_read_fail);
    CPPUNIT_TEST(test_solve_instawin);
    CPPUNIT_TEST(test_solve_instatie);
    CPPUNIT_TEST(test_solve_eventual_tie);
    CPPUNIT_TEST(test_solve_eventual_win);
    CPPUNIT_TEST(test_print_oneline);
    CPPUNIT_TEST(test_print_multiline);
    CPPUNIT_TEST(test_print_null);
    CPPUNIT_TEST(test_go_instawin);
    CPPUNIT_TEST(test_go_instatie);
    CPPUNIT_TEST(test_go_eventual_tie);
    CPPUNIT_TEST(test_go_eventual_win);
    CPPUNIT_TEST(test_go_multi_instance);
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
