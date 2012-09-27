/*
To test the program:
    % ls /usr/include/cppunit/
    /usr/include/cppunit/extensions/
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
// -------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <list>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

using namespace std;
struct TestVoting : CppUnit::TestFixture {

//----------
//getMin
//----------

void test_getMin_1(){
  numCandidates = 4;
  totalVotes[0] = 30;
  totalVotes[1] = 20;
  totalVotes[2] = 10;
  totalVotes[3] = 1;
  assert(getMin() == 1);
}

void test_getMin_2(){
  numCandidates = 4;
  totalVotes[0] = 30;
  totalVotes[1] = 30;
  totalVotes[2] = 30;
  totalVotes[3] = 30;
  assert(getMin() == 30);
}

void test_getMin_3(){
  numCandidates = 1;
  totalVotes = {0};
  totalVotes[0] = 20;
  assert(getMin() == 20);
}


//----------
//hasMajorityWinner
//----------

void test_majority_winner_1(){
  totalBallots = 8.0;
  numCandidates = 5;

  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }

  totalVotes[0] = 1;
  totalVotes[1] = 1;
  totalVotes[2] = 1;
  totalVotes[3] = 1;
  totalVotes[4] = 10;
  candidates[0] = "Loser1";
  candidates[1] = "Loser1";
  candidates[2] = "Loser1";
  candidates[3] = "Loser1";
  candidates[4] = "Winner";
  string winner = "";
  winner.clear();
  majorityWinner(winner);
  assert(winner == "Winner\n"); 
}

void test_majority_winner_2() {
  totalBallots = 8.0;
  numCandidates = 5;

  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }

  totalVotes[0] = 1;
  totalVotes[1] = 1;
  totalVotes[2] = 1;
  totalVotes[3] = 1;
  totalVotes[4] = 2;
  candidates[0] = "Loser1";
  candidates[1] = "Loser1";
  candidates[2] = "Loser1";
  candidates[3] = "Loser1";
  candidates[4] = "Winner";
  string winner = "";
  winner.clear();
  majorityWinner(winner);
  assert(winner.empty());
}
void test_majority_winner_3() {
  totalBallots = 3.0;
  numCandidates = 3;

  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }

  totalVotes[0] = 1;
  totalVotes[1] = 1;
  totalVotes[2] = 3;
  candidates[0] = "Loser1";
  candidates[1] = "Loser1";
  candidates[2] = "Juinner";
  string winner = "";
  winner.clear();
  majorityWinner(winner);
  assert(winner == "Juinner\n");
}


//----------
//tie
//----------

void test_isTied_1(){
  bool result;
  int min = 0;
  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }
  totalVotes[0] = 3;
  totalVotes[1] = 4;
  totalVotes[2] = 2;
  totalVotes[3] = 0;
  totalVotes[4] = 1;
  result = isTied(min);
  assert(result == false); 
}

void test_isTied_2(){
  bool result;
  int min = 0;
  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }
  totalVotes[0] = 0;
  totalVotes[1] = 0;
  totalVotes[2] = 0;
  totalVotes[3] = 0;
  totalVotes[4] = 0;
  result = isTied(min);
  assert(result == true); 
}

void test_isTied_3(){
  bool result;
  int min = 0;
  for (int i = 0; i < 20; i++) {
    totalVotes[i] = 0;
    candidates[i] = "";
  }
  totalVotes[0] = 4;
  totalVotes[1] = 5;
  totalVotes[2] = 5;
  totalVotes[3] = 5;
  totalVotes[4] = 5;
  result = isTied(min);
  assert(result == false); 
}


//----------
//processLosers
//----------

void test_processLosers_1(){
  numCandidates = 3;
  for (int i = 0; i < 20; i++) {
    loserList[i] = false;
    totalVotes[i] = 0;
  }

  totalVotes[0] = 2;
  totalVotes[1] = 4;
  totalVotes[2] = 3;
  loserList[0] = true;
  int min = 2;
  vector<Pile> piles;
  piles[0] = { {0, 1, 2}, {0, 1, 2}};
  piles[1] = { {1, 0, 2}, {1, 0, 2}, {1, 0, 2}, {1, 0, 2} };
  piles[2] = { {2, 0, 1}, {2, 0, 1}, {2, 0, 1} };
  processLosers(piles, min);
  assert(totalVotes[1] == 6);
}

void test_processLosers_2(){
  numCandidates = 3;
  for (int i = 0; i < 20; i++) {
    loserList[i] = false;
    totalVotes[i] = 0;
  }

  totalVotes[0] = 3;
  totalVotes[1] = 2;
  totalVotes[2] = 1;
  loserList[0] = true;
  int min = 1;
  vector<Pile> piles;
  piles[0] = { {0, 1, 2}, {0, 1, 2}, {0, 1, 2}};
  piles[1] = { {1, 0, 2}, {1, 0, 2} };
  piles[2] = { {2, 0, 1} };
  processLosers(piles, min);
  assert(totalVotes[0] == 7);
}

void test_processLosers_3(){
  numCandidates = 2;
  for (int i = 0; i < 20; i++) {
    loserList[i] = false;
    totalVotes[i] = 0;
  }
  totalVotes[0] = 3;
  totalVotes[1] = 4;
  loserList[0] = true;
  int min = 3;
  vector<Pile> piles;
  piles[0] = { {0, 1}, {0, 1}, {0, 1}};
  piles[1] = { {1, 0}, {1, 0}, {1, 0}, {1, 0} };
  processLosers(piles, min);
  assert(totalVotes[1] == 7);

}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_majority_winner_1);
    CPPUNIT_TEST(test_majority_winner_2);
    CPPUNIT_TEST(test_majority_winner_3);
    CPPUNIT_TEST(test_isTied_1);
    CPPUNIT_TEST(test_isTied_2);
    CPPUNIT_TEST(test_isTied_3);
    //CPPUNIT_TEST(test_processLosers_1);
    //CPPUNIT_TEST(test_processLosers_2);
    //CPPUNIT_TEST(test_processLosers_3);
    CPPUNIT_TEST(test_getMin_1);
    CPPUNIT_TEST(test_getMin_2);
    CPPUNIT_TEST(test_getMin_3);
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

