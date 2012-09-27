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
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n");
        std::vector<std::string> c;
        voting_read_candidates(r, c);
        CPPUNIT_ASSERT(c.size() == 3);
        CPPUNIT_ASSERT(c[0] == "John Doe");
        CPPUNIT_ASSERT(c[1] == "Jane Smith");
        CPPUNIT_ASSERT(c[2] == "Sirhan Sirhan");}

    void test_read_one_candidate() {
        std::istringstream r("1\nJohn Doe\n");
        std::vector<std::string> c;
        voting_read_candidates(r, c);
        CPPUNIT_ASSERT(c.size() == 1);
        CPPUNIT_ASSERT(c[0] == "John Doe");}

    void test_read_candidates_with_fluff() {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\nthis is stuff that should not be read");
        std::vector<std::string> c;
        voting_read_candidates(r, c);
        CPPUNIT_ASSERT(c.size() == 3);
        CPPUNIT_ASSERT(c[0] == "John Doe");
        CPPUNIT_ASSERT(c[1] == "Jane Smith");
        CPPUNIT_ASSERT(c[2] == "Sirhan Sirhan");}

    void test_read_ballots() {
        std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::vector<std::vector<int>> b;
        voting_read_ballots(r, b, 3);
        CPPUNIT_ASSERT(b.size() == 5);
        CPPUNIT_ASSERT(b[0][0] == 0);
        CPPUNIT_ASSERT(b[0][1] == 1);
        CPPUNIT_ASSERT(b[0][2] == 2);
        CPPUNIT_ASSERT(b[1][0] == 1);
        CPPUNIT_ASSERT(b[1][1] == 0);
        CPPUNIT_ASSERT(b[1][2] == 2);
        CPPUNIT_ASSERT(b[2][0] == 1);
        CPPUNIT_ASSERT(b[2][1] == 2);
        CPPUNIT_ASSERT(b[2][2] == 0);
        CPPUNIT_ASSERT(b[3][0] == 0);
        CPPUNIT_ASSERT(b[3][1] == 1);
        CPPUNIT_ASSERT(b[3][2] == 2);
        CPPUNIT_ASSERT(b[4][0] == 2);
        CPPUNIT_ASSERT(b[4][1] == 0);
        CPPUNIT_ASSERT(b[4][2] == 1);}

    void test_read_one_ballot() {
        std::istringstream r("1 2 3\n");
        std::vector<std::vector<int>> b;
        voting_read_ballots(r, b, 3);
        CPPUNIT_ASSERT(b.size() == 1);
        CPPUNIT_ASSERT(b[0][0] == 0);
        CPPUNIT_ASSERT(b[0][1] == 1);
        CPPUNIT_ASSERT(b[0][2] == 2);}

    void test_read_ballots_with_fluff() {
        std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\nwe all live in a yellow submarine");
        std::vector<std::vector<int>> b;
        voting_read_ballots(r, b, 3);
        CPPUNIT_ASSERT(b.size() == 5);
        CPPUNIT_ASSERT(b[0][0] == 0);
        CPPUNIT_ASSERT(b[0][1] == 1);
        CPPUNIT_ASSERT(b[0][2] == 2);
        CPPUNIT_ASSERT(b[1][0] == 1);
        CPPUNIT_ASSERT(b[1][1] == 0);
        CPPUNIT_ASSERT(b[1][2] == 2);
        CPPUNIT_ASSERT(b[2][0] == 1);
        CPPUNIT_ASSERT(b[2][1] == 2);
        CPPUNIT_ASSERT(b[2][2] == 0);
        CPPUNIT_ASSERT(b[3][0] == 0);
        CPPUNIT_ASSERT(b[3][1] == 1);
        CPPUNIT_ASSERT(b[3][2] == 2);
        CPPUNIT_ASSERT(b[4][0] == 2);
        CPPUNIT_ASSERT(b[4][1] == 0);
        CPPUNIT_ASSERT(b[4][2] == 1);}

    // ----
    // eval
    // ----

    void test_eval() {
        std::vector<std::vector<int>> b;
        std::vector<int> ballot1;
        std::vector<int> ballot2;
        std::vector<int> ballot3;
        std::vector<int> ballot4;
        std::vector<int> ballot5;
        ballot1.push_back(0);
        ballot1.push_back(1);
        ballot1.push_back(2);
        ballot2.push_back(1);
        ballot2.push_back(0);
        ballot2.push_back(2);
        ballot3.push_back(1);
        ballot3.push_back(2);
        ballot3.push_back(0);
        ballot4.push_back(0);
        ballot4.push_back(1);
        ballot4.push_back(2);
        ballot5.push_back(2);
        ballot5.push_back(0);
        ballot5.push_back(1);
        b.push_back(ballot1);
        b.push_back(ballot2);
        b.push_back(ballot3);
        b.push_back(ballot4);
        b.push_back(ballot5);
        std::vector<int> win;
        voting_eval(b, win, 3);
        CPPUNIT_ASSERT(win.size() == 1);
        CPPUNIT_ASSERT(win[0] == 0);}

    void test_eval_one_ballot() {
        std::vector<std::vector<int>> b;
        std::vector<int> ballot;
        ballot.push_back(0);
        ballot.push_back(1);
        ballot.push_back(2);
        b.push_back(ballot);
        std::vector<int> win;
        voting_eval(b, win, 3);
        CPPUNIT_ASSERT(win.size() == 1);
        CPPUNIT_ASSERT(win[0] == 0);}

    void test_eval_tie() {
        std::vector<std::vector<int>> b;
        std::vector<int> ballot1;
        std::vector<int> ballot2;
        ballot1.push_back(0);
        ballot1.push_back(1);
        ballot2.push_back(1);
        ballot2.push_back(0);
        b.push_back(ballot1);
        b.push_back(ballot2);
        std::vector<int> win;
        voting_eval(b, win, 3);
        CPPUNIT_ASSERT(win.size() == 2);
        CPPUNIT_ASSERT(win[0] == 0);
        CPPUNIT_ASSERT(win[1] == 1);}

    // -----
    // print
    // -----

    void test_print() {
        std::ostringstream w;
        std::vector<std::string> c = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
        std::vector<int> win = {0};
        voting_print(w, c, win);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_print_tie() {
        std::ostringstream w;
        std::vector<std::string> c = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
        std::vector<int> win = {0,1,2};
        voting_print(w, c, win);
        CPPUNIT_ASSERT(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}

    void test_print_numbers() {
        std::ostringstream w;
        std::vector<std::string> c = {"1 2 3", "4 5 6", "7 8 9"};
        std::vector<int> win = {0};
        voting_print(w, c, win);
        CPPUNIT_ASSERT(w.str() == "1 2 3\n");}

    // -----
    // solve
    // -----

    void test_solve() {
        std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    void test_solve_twice() {
        std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\n");}

    void test_solve_one_ballot() {
        std::istringstream r("1\n\n1\nJohn Doe\n1\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_candidates);
    CPPUNIT_TEST(test_read_one_candidate);
    CPPUNIT_TEST(test_read_candidates_with_fluff);
    CPPUNIT_TEST(test_read_ballots);
    CPPUNIT_TEST(test_read_one_ballot);
    CPPUNIT_TEST(test_read_ballots_with_fluff);
    CPPUNIT_TEST(test_eval);
    CPPUNIT_TEST(test_eval_one_ballot);
    CPPUNIT_TEST(test_eval_tie);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print_tie);
    CPPUNIT_TEST(test_print_numbers);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST(test_solve_twice);
    CPPUNIT_TEST(test_solve_one_ballot);
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
