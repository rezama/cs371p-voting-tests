/*
To test the program:
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
    % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <algorithm>

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

    void test_read_1 () {
        std::istringstream r("2\nbob\nkate\n 1 2\n 2 1\n");
        int numberOfCandidates = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfCandidates);
        CPPUNIT_ASSERT(numberOfCandidates == 2);
        CPPUNIT_ASSERT(candidates[0].name.compare("bob") == 0);
        CPPUNIT_ASSERT(candidates[1].name.compare("kate") == 0);
        
    }
    
    void test_read_2 () {
        std::istringstream r("2\nbob\nkate\n 1 2\n 2 1\n");
        int numberOfCandidates = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfCandidates);
        CPPUNIT_ASSERT(numberOfCandidates == 2);
        CPPUNIT_ASSERT(candidates[0].name.compare("bob") == 0);
        CPPUNIT_ASSERT(candidates[1].name.compare("kate") == 0);
        int testArray[] = {1,2};
        std::vector<int> test(testArray, testArray + 2);
        CPPUNIT_ASSERT(std::equal(candidates[0].ballots[0].data.begin(), candidates[0].ballots[0].data.end(), test.begin()));}
    
    void test_read_3 () {
        std::istringstream r("3\nbob bob\nkate kate\nnate bob\n 1 2 3\n 2 1 3\n");
        int numberOfCandidates = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfCandidates);
        CPPUNIT_ASSERT(candidates[0].name.compare("bob bob") == 0);
        CPPUNIT_ASSERT(candidates[1].name.compare("kate kate") == 0);
        CPPUNIT_ASSERT(candidates[2].name.compare("nate bob") == 0);}
    
    // ----
    // eval
    // ----

    void test_eval_1 () {
        std::ostringstream w;
        std::istringstream r("2\nbob\nkate\n 1 2\n 1 2\n");
        int numberOfBallots = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfBallots);
        voting_eval (candidates, numberOfBallots, w);
        CPPUNIT_ASSERT(w.str().compare("bob\n") == 0);
        }

    void test_eval_2 () {
        std::ostringstream w;
        std::istringstream r("3\nbob bob\nkate kate\nnate bob\n 1 2 3\n 2 1 3\n");
        int numberOfBallots = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfBallots);
        voting_eval (candidates, numberOfBallots, w);
        CPPUNIT_ASSERT(w.str().compare("bob bob\nkate kate\n") == 0);
        }

    void test_eval_3 () {
        std::ostringstream w;
        std::istringstream r("3\nbob bob\nkate kate\nnatebob\n 1 2 3\n 2 1 3\n 2 1 3\n 2 1 3\n");
        int numberOfBallots = 0;
        std::vector< candidate > candidates;
        voting_read(r, candidates, numberOfBallots);
        voting_eval (candidates, numberOfBallots, w);
        CPPUNIT_ASSERT(w.str().compare("kate kate\n") == 0);
        }  

    // -----
    // solve
    // -----
    
    void test_solve_1 () {
        std::istringstream r("1\n \n 2\nbob\nkate\n 1 2\n 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("bob\n") == 0);}
    
    void test_solve_2 () {
        std::istringstream r("1\n \n 3\nbob bob\nkate kate\nnate bob\n 1 2 3\n 2 1 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("bob bob\nkate kate\n") == 0);}
    
    void test_solve_3 () {
        std::istringstream r("1\n \n 3\nbob bob\nkate kate\nnatebob\n 1 2 3\n 2 1 3\n 2 1 3\n 2 1 3\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str().compare("kate kate\n") == 0);}

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
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
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
