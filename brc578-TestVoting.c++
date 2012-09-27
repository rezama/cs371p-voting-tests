
/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall Testvoting.c++ -o Testvoting.c++.app
% valgrind Testvoting.c++.app >& Testvoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == true);}

     void test_read2 () {
        std::istringstream r("1\n\n3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == true);}

    void test_read3 () {
        std::istringstream r("100 500\n");
        const bool b = voting_read(r);
        CPPUNIT_ASSERT(b == false);}
    


    //-----
    //eval
    //-----
    void test_eval_1 () {
        const int v = voting_eval(10000, 50000);
        CPPUNIT_ASSERT(v == 324);}

    void test_eval_2 () {
        const int v = voting_eval(9, 9);
        CPPUNIT_ASSERT(v == 20);}

    void test_eval_3 () {
        const int v = voting_eval(2000, 100000);
        CPPUNIT_ASSERT(v == 351);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        voting_print(w, "John Doe");
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_print2 () {
        std::ostringstream w;
        voting_print(w, "Testing Print");
        CPPUNIT_ASSERT(w.str() == "Testing Print\n");}

    void test_print3 () {
        std::ostringstream w;
        voting_print(w, "Hello World");
        CPPUNIT_ASSERT(w.str() == "Hello World\n");}


    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe");}

    void test_solve2 () {
        std::istringstream r("1\n\n3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Sane Jmith");}
    
    void test_solve3 () {
        std::istringstream r("1\n\n3\nBob Doe\nSane Jmith\nSirhan Sirhan\n1 3 1\n2 1 3\n3 2 1");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Bob Doe Sane Jmith Sirhan Sirhan");}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(Testvoting);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
