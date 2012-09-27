// ----------------------------
// cs371p-voting/TestVoting.c++
// Copyright (C) 2012
// Christopher Boerner
// ----------------------------

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

// ----------
// TestVoting
// ----------

struct TestVoting : CppUnit::TestFixture {
  // ----
  // read
  // ----

  void test_read_1 () {
    std::istringstream r("1 2 3\n");
    std::deque<int> ballot;
    voting_read(r, ballot);
    CPPUNIT_ASSERT(!ballot.empty());
    int size = ballot.size();
    CPPUNIT_ASSERT(3 == size);
    std::ostringstream w;
    while (ballot.front() != ballot.back()) {
      w << ballot.front() << " ";
      ballot.pop_front();}
    w << ballot.front() << std::endl;
    CPPUNIT_ASSERT(r.str() == w.str());}
    
  void test_read_2 () {
    std::istringstream r("6\n");
    std::deque<int> ballot;
    voting_read(r, ballot);
    CPPUNIT_ASSERT(!ballot.empty());
    int size = ballot.size();
    CPPUNIT_ASSERT(1 == size);
    std::ostringstream w;
    while (ballot.front() != ballot.back()) {
      w << ballot.front() << " ";
      ballot.pop_front();}
    w << ballot.front() << std::endl;
    CPPUNIT_ASSERT(r.str() == w.str());}
    
  void test_read_3 () {
    std::istringstream r("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n");
    std::deque<int> ballot;
    voting_read(r, ballot);
    CPPUNIT_ASSERT(!ballot.empty());
    int size = ballot.size();
    CPPUNIT_ASSERT(20 == size);
    std::ostringstream w;
    while (ballot.front() != ballot.back()) {
      w << ballot.front() << " ";
      ballot.pop_front();}
    w << ballot.front() << std::endl;
    CPPUNIT_ASSERT(r.str() == w.str());}

  void test_read_4 () {
    std::istringstream r("20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1\n");
    std::deque<int> ballot;
    voting_read(r, ballot);
    CPPUNIT_ASSERT(!ballot.empty());
    int size = ballot.size();
    CPPUNIT_ASSERT(20 == size);    
    std::ostringstream w;
    while (ballot.front() != ballot.back()) {
      w << ballot.front() << " ";
      ballot.pop_front();}
    w << ballot.front() << std::endl;
    CPPUNIT_ASSERT(r.str() == w.str());}

  // ----
  // eval
  // ----
  void test_eval_1() {
    std::istringstream r("4\nHimself\nThe Sad Stork\nThe Mad Stork\nJames O. Incandenza\n1 2 3 4\n4 3 2 1\n1  2 3    4\n2 4 3 1\n4 2 3 1\n");
    std::ostringstream w;
    voting_eval(r, w);
    CPPUNIT_ASSERT(w.str() == "James O. Incandenza\n");
  }
  
  void test_eval_2() {
    std::istringstream r("2\nWild Turkey\nJames O. Incandenza\n2 1\n1 2\n");
    std::ostringstream w;
    voting_eval(r, w);
    CPPUNIT_ASSERT(w.str() == "Wild Turkey\nJames O. Incandenza\n");
  }
    
  void test_eval_3() {
    std::istringstream r("3\nEntertainment\nU.S.O.U.S.\nA.F.R.\n1 2 3\n1 3 2\n3 2 1\n3 1 2\n2 3 1\n2 1 3\n");
    std::ostringstream w;
    voting_eval(r, w);
    CPPUNIT_ASSERT(w.str() == "Entertainment\nU.S.O.U.S.\nA.F.R.\n");
  }
  
  void test_eval_4() {
    std::istringstream r("1\nWayne\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n");
    std::ostringstream w;
    voting_eval(r, w);
    CPPUNIT_ASSERT(w.str() == "Wayne\n");
  }
  
  // -----
  // solve
  // -----
  void test_solve_1() {
    std::istringstream r("1\n\n4\nHimself\nThe Sad Stork\nThe Mad Stork\nJames O. Incandenza\n1 2 3 4\n4 3 2 1\n1  2 3    4\n2 4 3 1\n4 2 3 1\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "James O. Incandenza\n");
  }
  
  void test_solve_2() {
    std::istringstream r("2\n\n3\nEntertainment\nU.S.O.U.S.\nA.F.R.\n1 2 3\n1 3 2\n3 2 1\n3 1 2\n2 3 1\n2 1 3\n\n2\nWild Turkey\nJames O. Incandenza\n2 1\n1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Entertainment\nU.S.O.U.S.\nA.F.R.\n\nWild Turkey\nJames O. Incandenza\n");
  }
  
  void test_solve_3() {
    std::istringstream r("1\n\n1\nNope\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Nope\n");
  }
  
  void test_solve_4() {
    std::istringstream r("1\n\n1\nWayne\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Wayne\n");
  }
  
  // -----
  // suite
  // -----
	
  CPPUNIT_TEST_SUITE(TestVoting);
  CPPUNIT_TEST(test_read_1);
  CPPUNIT_TEST(test_read_2);
  CPPUNIT_TEST(test_read_3);
  CPPUNIT_TEST(test_read_4);
  CPPUNIT_TEST(test_eval_1);
  CPPUNIT_TEST(test_eval_2);
  CPPUNIT_TEST(test_eval_3);
  CPPUNIT_TEST(test_eval_4);  
  CPPUNIT_TEST(test_solve_1);
  CPPUNIT_TEST(test_solve_2);
  CPPUNIT_TEST(test_solve_3);
  CPPUNIT_TEST(test_solve_4);
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