// --------------------------------
//Voting.c++
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
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read done
    // ----

    void test_read () {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20] = {""};
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        CPPUNIT_ASSERT(totalVotes > 0);}

    
    void test_read2 () {
        std::istringstream r("3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20];
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        CPPUNIT_ASSERT(totalVotes > 0);}

    
    void test_read3 () {
        std::istringstream r("3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 1 3\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20];
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        CPPUNIT_ASSERT(totalVotes > 0);}

    // ----
    // eval
    // ----

    void test_eval_1 () {
        
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20];
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        bool test = eval(numCandidates, candidates, vote, totalVotes, candVotes);
        CPPUNIT_ASSERT(test);}

    void test_eval_2 () {
        
        std::istringstream r("3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20];
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        bool test = eval(numCandidates, candidates, vote, totalVotes, candVotes);
        CPPUNIT_ASSERT(test);}

    void test_eval_3 () {
        
        std::istringstream r("3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 1 3\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        int numCandidates = 0;
        int totalVotes = 0;
        string candidates[20];
        int vote[20][1000][20] = {{{-1}}};
        int candVotes[20] = {0};
        totalVotes = read(r, numCandidates, candidates, vote, candVotes);
        bool test = eval(numCandidates, candidates, vote, totalVotes, candVotes);
        CPPUNIT_ASSERT(test);}
        
    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        bool test = solve(r);
        CPPUNIT_ASSERT(test == true);}
    void test_solve2 () {
        std::istringstream r("1\n\n3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 3 1\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        bool test = solve(r);
        CPPUNIT_ASSERT(test == true);}

    void test_solve3 () {
        std::istringstream r("1\n\n3\nBob Doe\nSane Jmith\nSirhan Sirhan\n2 1 3\n2 1 3\n3 2 1\n1 2 3\n3 1 2");
        bool test = solve(r);
        CPPUNIT_ASSERT(test == true);}

    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_solve);
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
