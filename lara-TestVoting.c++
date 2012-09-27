// --------------------------------
// Modeled after 
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

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_candidates() {
        std::istringstream r("Pikachu\nFlipper\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        const bool b = voting_read_candidates(r, 2, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);}

    void test_read_candidates1() {
        std::istringstream r("Pikachu\nFlipper\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        const bool b = voting_read_candidates(r, 0, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 1);
        CPPUNIT_ASSERT(ballots.size() == 1);}
    
    void test_read_candidates2() {
        std::istringstream r("Flash\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        const bool b = voting_read_candidates(r, 2, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);}

    void test_read_candidates3() {
        std::istringstream r("Pikachu\nFlipper\nSpiderman");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        const bool b = voting_read_candidates(r, 3, names, ballots);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(names.size() == 4);
        CPPUNIT_ASSERT(ballots.size() == 4);}

   void test_read_ballots() {
        std::istringstream r("1 2 3 4\n\n");
        std::vector< std::list < Ballot > > ballots;
        std::list< Ballot > ballot;
        int num;
        ballots.resize(3+1);
        const bool b = voting_read_ballots(r, 3, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].size() == 0);
        CPPUNIT_ASSERT(ballots[1].size() == 1);
        CPPUNIT_ASSERT(num == 1);}
 
    void test_read_ballots1() {
        std::istringstream r("1\n2\n3\n4\n\n");
        std::vector< std::list < Ballot > > ballots;
        std::list< Ballot > ballot;
        int num;
        ballots.resize(2+1);
        const bool b = voting_read_ballots(r, 2, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].size() == 0);
        CPPUNIT_ASSERT(ballots[1].size() == 1);
        CPPUNIT_ASSERT(ballots[2].size() == 1);
        CPPUNIT_ASSERT(ballots.size() == 3);
        CPPUNIT_ASSERT(num == 2);}
 
  void test_read_ballots2() {
        std::istringstream r("1 2\n3 4\n\n");
        std::vector< std::list < Ballot > > ballots;
        std::list< Ballot > ballot;
        int num;
        ballots.resize(3+1);
        const bool b = voting_read_ballots(r, 3, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].size() == 0);
        CPPUNIT_ASSERT(ballots[1].size() == 1);
        CPPUNIT_ASSERT(ballots[2].size() == 0);
        CPPUNIT_ASSERT(ballots[3].size() == 1);
        CPPUNIT_ASSERT(ballots.size() == 4);
        CPPUNIT_ASSERT(num == 2);}

  void test_read_ballots3() {
        std::istringstream r("1 2\n1 4\n\n");
        std::vector< std::list < Ballot > > ballots;
        std::list< Ballot > ballot;
        int num;
        ballots.resize(3+1);
        const bool b = voting_read_ballots(r, 3, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballots[0].size() == 0);
        CPPUNIT_ASSERT(ballots[1].size() == 2);
        CPPUNIT_ASSERT(ballots[2].size() == 0);
        CPPUNIT_ASSERT(ballots.size() == 4);
        CPPUNIT_ASSERT(num == 2);}

    void test_read () {
        std::istringstream r("\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        int num = 0;
        const bool b = voting_read(r, names, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num == 0);
        CPPUNIT_ASSERT(names.size() == 0);
        CPPUNIT_ASSERT(ballots.size() == 0);}

    void test_read1 () {
        std::istringstream r("2\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        int num = 0;
        const bool b = voting_read(r, names, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num == 0);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);}

    void test_read2 () {
        std::istringstream r("2\nSeg Fault\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        int num = 0;
        const bool b = voting_read(r, names, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num == 0);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);}

    void test_read3 () {
        std::istringstream r("2\nSeg Fault\nEncapsulator\n");
        std::vector< std::string > names;
        std::vector< std::list < Ballot > > ballots;
        int num = 0;
        const bool b = voting_read(r, names, ballots, num);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(num == 0);
        CPPUNIT_ASSERT(names.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);}

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        std::vector< std::string > arr;
        arr.push_back("A");
        arr.push_back("B");
        arr.push_back("C");
        voting_print(w, arr);
        CPPUNIT_ASSERT(w.str() == "A\nB\nC\n");}

    void test_print1 () {
        std::ostringstream w;
        std::vector< std::string > arr;
        arr.push_back("\n");
        voting_print(w, arr);
        CPPUNIT_ASSERT(w.str() == "\n\n");}

    void test_print2 () {
        std::ostringstream w;
        std::vector< std::string > arr;
        voting_print(w, arr);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_print3 () {
        std::ostringstream w;
        std::vector< std::string > arr;
        arr.push_back("A CAT AND A DOG");
        arr.push_back("B");
        arr.push_back("C");
        voting_print(w, arr);
        CPPUNIT_ASSERT(w.str() == "A CAT AND A DOG\nB\nC\n");}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n2\nMonkey\nBlitzen\n1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Monkey\n");}


    void test_solve1 () {
        std::istringstream r("");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_solve2 () {
        std::istringstream r("1\n\n0\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "");}

    void test_solve3 () {
        std::istringstream r("2\n\n0\n\n0\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_candidates);
    CPPUNIT_TEST(test_read_candidates1);
    CPPUNIT_TEST(test_read_candidates2);
    CPPUNIT_TEST(test_read_candidates3);

    CPPUNIT_TEST(test_read_ballots);
    CPPUNIT_TEST(test_read_ballots1);
    CPPUNIT_TEST(test_read_ballots2);
    CPPUNIT_TEST(test_read_ballots3);

    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);

    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);

    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
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
