/*
To test the program:
  % ls /usr/include/cppunit/
  ...
  HelperMacros.h
  ...
  % Locate libcppunit.a
  /usr/lib/libcppunit.a
  % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
  % valgrind TestVoting.c++.app >& TestVoting
*/

// ---------
// includes
// ---------

#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture {
  // ----
  // read
  // ----
  
  void test_read_1 () {
    using namespace std;
    istringstream r("3\nRed\nBlue\nGreen\n1 2 3\n3 2 1\n2 1 3\n");
    int num_candidates;
    string candidates[21];
    vector<string> ballots;
    const bool b = voting_read(r, num_candidates, candidates, ballots);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(num_candidates == 3);
    CPPUNIT_ASSERT(candidates[1] == "Red");
    CPPUNIT_ASSERT(candidates[2] == "Blue");
    CPPUNIT_ASSERT(candidates[3] == "Green");
    CPPUNIT_ASSERT(ballots[0] == "1 2 3");
    CPPUNIT_ASSERT(ballots[1] == "3 2 1");
    CPPUNIT_ASSERT(ballots[2] == "2 1 3");
  }

  void test_read_2 () {
    using namespace std;
    istringstream r("4\nTrey\nAT\nMC\nLP\n1 2 3 4\n4 3 2 1\n3 2 4 1\n\n");
    int num_candidates;
    string candidates[21];
    vector<string> ballots;
    const bool b = voting_read(r, num_candidates, candidates, ballots);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(num_candidates = 4);
    CPPUNIT_ASSERT(candidates[1] == "Trey");
    CPPUNIT_ASSERT(candidates[2] == "AT");
    CPPUNIT_ASSERT(candidates[3] == "MC");
    CPPUNIT_ASSERT(candidates[4] == "LP");
    CPPUNIT_ASSERT(ballots.size() == 3);
    CPPUNIT_ASSERT(ballots[0] == "1 2 3 4");
    CPPUNIT_ASSERT(ballots[1] == "4 3 2 1");
    CPPUNIT_ASSERT(ballots[2] == "3 2 4 1");
  }

  void test_read_3 () {
    using namespace std;
    istringstream r("2\nTrey\nBarack\n1 2\n2 1\n");
    int num_candidates;
    string candidates[21];
    vector<string> ballots;
    const bool b = voting_read(r, num_candidates, candidates, ballots);
    CPPUNIT_ASSERT(b == true);
    CPPUNIT_ASSERT(num_candidates == 2);
    CPPUNIT_ASSERT(candidates[1] == "Trey");
    CPPUNIT_ASSERT(candidates[2] == "Barack");
    CPPUNIT_ASSERT(ballots.size() == 2);
    CPPUNIT_ASSERT(ballots[0] == "1 2");
    CPPUNIT_ASSERT(ballots[1] == "2 1");
  }

    // -------------------
    // voting_read_ballots
    // -------------------

  void test_read_ballots_1 () {
    using namespace std;
    string ballot = "1 2 3";
    int num_candidates = 3;
    vector<int> votes = voting_read_ballots(ballot, num_candidates);
    CPPUNIT_ASSERT(votes[0] == 1);
    CPPUNIT_ASSERT(votes[1] == 2);
    CPPUNIT_ASSERT(votes[2] == 3);
  }

  void test_read_ballots_2 () {
    using namespace std;
    string ballot = "1 3 4 5 2";
    int num_candidates = 5;
    vector<int> votes = voting_read_ballots(ballot, num_candidates);
    CPPUNIT_ASSERT(votes[0] == 1);
    CPPUNIT_ASSERT(votes[1] == 3);
    CPPUNIT_ASSERT(votes[2] == 4);
    CPPUNIT_ASSERT(votes[3] == 5);
    CPPUNIT_ASSERT(votes[4] == 2);
  }

  void test_read_ballots_3 () {
    using namespace std;
    string ballot = "3 2 1\n";
    int num_candidates = 3;
    vector<int> votes = voting_read_ballots(ballot, num_candidates);
    CPPUNIT_ASSERT(votes[0] == 3);
    CPPUNIT_ASSERT(votes[1] == 2);
    CPPUNIT_ASSERT(votes[2] == 1);
  }

  void test_get_all_votes_1 () {
    using namespace std;
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("2 1 3");
    int num_candidates = 3;
    vector<vector<int> > all_votes = get_all_votes(ballots, num_candidates);
    CPPUNIT_ASSERT( all_votes.at(0).at(0) == 1);
    CPPUNIT_ASSERT( all_votes.at(0).at(1)== 2);
    CPPUNIT_ASSERT( all_votes.at(0).at(2) == 3);
    CPPUNIT_ASSERT( all_votes.at(1).at(0) == 3);
    CPPUNIT_ASSERT( all_votes.at(1).at(1) == 2);
    CPPUNIT_ASSERT( all_votes.at(1).at(2) == 1);
    CPPUNIT_ASSERT( all_votes.at(2).at(0) == 2);
    CPPUNIT_ASSERT( all_votes.at(2).at(1) == 1);
    CPPUNIT_ASSERT( all_votes.at(2).at(2) == 3);
  }


  void test_get_all_votes_2 () {
    using namespace std;
    vector<string> ballots;
    ballots.push_back("3 4");
    ballots.push_back("5 6");
    int num_candidates = 2;
    vector<vector<int> > all_votes = get_all_votes(ballots, num_candidates);
    CPPUNIT_ASSERT( all_votes.at(0).at(0) == 3);
    CPPUNIT_ASSERT( all_votes.at(0).at(1) == 4);
    CPPUNIT_ASSERT( all_votes.at(1).at(0) == 5);
    CPPUNIT_ASSERT( all_votes.at(1).at(1) == 6);
  }

  void test_get_all_votes_3 () {
    using namespace std;
    vector<string> ballots;
    ballots.push_back("1 2 3");
    int num_candidates = 3;
    vector<vector<int> > all_votes = get_all_votes(ballots, num_candidates);
    CPPUNIT_ASSERT( all_votes.at(0).at(0) == 1);
    CPPUNIT_ASSERT( all_votes.at(0).at(1) == 2);
    CPPUNIT_ASSERT( all_votes.at(0).at(2) == 3);
  }

  //--------------------
  // first_ballot_split
  //--------------------

  void test_first_ballot_split_1 () {
    vector<string> ballots;
    ballots.push_back("1 2 3 4");
    ballots.push_back("1 3 2 4");
    ballots.push_back("2 3 1 4");
    ballots.push_back("4 3 2 1");
    map<int, vector<vector<int> > > candidates_and_ballots;
    candidates_and_ballots = first_ballot_split(ballots, 4);
    vector<vector<int> > cand_1 = candidates_and_ballots[1];
    vector<vector<int> > cand_2 = candidates_and_ballots[2];
    vector<vector<int> > cand_4 = candidates_and_ballots[4];
    CPPUNIT_ASSERT(cand_1.at(0).at(0) == 1);
    CPPUNIT_ASSERT(cand_1.at(0).at(1) == 2);
    CPPUNIT_ASSERT(cand_1.at(0).at(2) == 3);
    CPPUNIT_ASSERT(cand_1.at(0).at(3) == 4);
    CPPUNIT_ASSERT(cand_2.at(0).at(1) == 3);
    CPPUNIT_ASSERT(cand_4.at(0).at(0) == 4);
  }

  void test_first_ballot_split_2 () {
    vector<string> ballots;
    ballots.push_back("3 2 1 4");
    ballots.push_back("1 2 3 4");
    map<int, vector<vector<int> > > candidates_and_ballots;
    candidates_and_ballots = first_ballot_split(ballots, 4);
    vector<vector<int> > cand_1 = candidates_and_ballots[1];
    vector<vector<int> > cand_3 = candidates_and_ballots[3];
    CPPUNIT_ASSERT(cand_1.at(0).at(0) == 1);
    CPPUNIT_ASSERT(cand_1.at(0).at(2) == 3);
    CPPUNIT_ASSERT(cand_3.at(0).at(0) == 3);
    CPPUNIT_ASSERT(cand_3.at(0).at(3) == 4);
  }

  void test_first_ballot_split_3 () {
    vector<string> ballots;
    ballots.push_back("1 3 2");
    ballots.push_back("2 1 3");
    map<int, vector<vector<int> > > c_and_b;
    c_and_b = first_ballot_split(ballots, 3);
    vector<vector<int> > cand_1 = c_and_b[1];
    vector<vector<int> > cand_2 = c_and_b[2];
    CPPUNIT_ASSERT(cand_1.at(0).at(1) == 3);
    CPPUNIT_ASSERT(cand_2.at(0).at(2) == 3);
  }
  
  //------------
  // get_winners
  // ------------

  void test_get_winners_1 () {
    vector<string> ballots;
    ballots.push_back("1 2 3 4");
    ballots.push_back("4 3 2 1");
    ballots.push_back("1 2 3 4");
    ballots.push_back("1 2 3 4");
    ballots.push_back("2 3 4 1");
    map<int, vector<vector<int> > > c_and_b;
    c_and_b = first_ballot_split(ballots, 4);
    vector<int> winners;
    winners = get_winners(c_and_b);
    CPPUNIT_ASSERT( winners.size() == 1);
    CPPUNIT_ASSERT( winners.at(0) == 1);
  }

  void test_get_winners_2 () {
    vector<string> ballots;
    ballots.push_back("1 2 3 4");
    ballots.push_back("2 3 4 1");
    ballots.push_back("1 2 3 4");
    ballots.push_back("2 3 4 1");
    map<int, vector<vector<int> > > c_and_b;
    c_and_b = first_ballot_split(ballots, 4);
    vector<int> winners = get_winners(c_and_b);
    CPPUNIT_ASSERT( winners.size() == 2 );
    CPPUNIT_ASSERT( winners.at(0) == 1);
    CPPUNIT_ASSERT( winners.at(1) == 2);
  }

  void test_get_winners_3 () {
    vector<string> ballots;
    ballots.push_back("1 2 3 4");
    ballots.push_back("1 2 3 4");
    ballots.push_back("2 3 4 1");
    ballots.push_back("3 4 2 1");
    ballots.push_back("4 3 2 1");
    map<int, vector<vector<int> > > c_and_b;
    c_and_b = first_ballot_split(ballots, 4);
    vector<int> winners = get_winners(c_and_b); 
    CPPUNIT_ASSERT( winners.size() == 0);
  }

  void test_reassign_losers_1 () {
    vector<string> ballots;
    ballots.push_back("1 2 3 4");
    ballots.push_back("1 2 3 4");
    ballots.push_back("2 3 4 1");
    ballots.push_back("2 4 3 1");
    ballots.push_back("4 3 2 1");
    map<int, vector<vector<int> > > c_and_b;
    c_and_b = first_ballot_split(ballots, 4);
    c_and_b = reassign_losers(c_and_b);
    vector<vector<int> > cand_1 = c_and_b[1];
    vector<vector<int> > cand_2 = c_and_b[2];
    CPPUNIT_ASSERT( cand_1.size() == 2 );
    CPPUNIT_ASSERT( cand_2.size() == 3 );
  }

  //------------
  // voting_eval
  //------------

  void test_voting_eval_1 () {
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("2 1 3");
    ballots.push_back("2 3 1");
    ballots.push_back("1 2 3");
    ballots.push_back("3 1 2");
    vector<int> winners = voting_eval(ballots, 3);
    CPPUNIT_ASSERT(winners.size() == 1);
    CPPUNIT_ASSERT(winners.at(0) == 1);
  }

  void test_voting_eval_2 () {
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("1 2 3");
    vector<int> winners = voting_eval(ballots, 3);
    CPPUNIT_ASSERT(winners.size() == 1);
    CPPUNIT_ASSERT(winners.at(0) == 1);
  }

  void test_voting_eval_3 () {
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("2 1 3");
    ballots.push_back("1 3 2");
    vector<int> winners = voting_eval(ballots, 3);
    CPPUNIT_ASSERT(winners.size() == 1);
    CPPUNIT_ASSERT(winners.at(0) == 1);
  }

  void test_first_ballot_split_4 () {
    vector<string> ballots; 
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("2 1 3");
    ballots.push_back("1 3 2");
    map<int, vector<vector<int> > > c_and_b = first_ballot_split(ballots, 3);
    CPPUNIT_ASSERT(c_and_b.size() == 3);
    vector<vector<int> > cand_1 = c_and_b[1];
    vector<vector<int> > cand_2 = c_and_b[2];
    vector<vector<int> > cand_3 = c_and_b[3];
    CPPUNIT_ASSERT( cand_1.size() == 2);
    CPPUNIT_ASSERT( cand_2.size() == 1);
    CPPUNIT_ASSERT( cand_2.size() == 1);
  }

  void test_get_winners_4() {
    vector<string> ballots; 
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("2 1 3");
    ballots.push_back("1 3 2");
    map<int, vector<vector<int> > > c_and_b = first_ballot_split(ballots, 3);
    vector<int> winners = get_winners(c_and_b);
    CPPUNIT_ASSERT( winners.size() == 0 );
  }

  void test_reassign_losers_2() {
    vector<string> ballots; 
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("2 1 3");
    ballots.push_back("1 3 2");
    map<int, vector<vector<int> > > c_and_b = first_ballot_split(ballots, 3);
    c_and_b = reassign_losers(c_and_b);
    CPPUNIT_ASSERT(c_and_b.size() == 1);
    vector<vector<int> > cand_1 = c_and_b[1];
    CPPUNIT_ASSERT(cand_1.size() == 4);
  }

  void test_reassign_losers_3() {
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("1 2 3");
    ballots.push_back("1 2 3");
    ballots.push_back("2 1 3");
    map<int, vector<vector<int> > > c_and_b = first_ballot_split(ballots, 3);
    c_and_b = reassign_losers(c_and_b);
    CPPUNIT_ASSERT(c_and_b.size() == 1);
    vector<vector<int> > cand_1 = c_and_b[1];
    CPPUNIT_ASSERT(cand_1.size() == 5);
  }

  void test_get_winners_5 () {
    vector<string> ballots;
    ballots.push_back("1 2 3");
    ballots.push_back("3 2 1");
    ballots.push_back("1 2 3");
    ballots.push_back("1 2 3");
    ballots.push_back("2 1 3");
    map<int, vector<vector<int> > > c_and_b = first_ballot_split(ballots, 3);
    c_and_b = reassign_losers(c_and_b);
    vector<int> winners = get_winners(c_and_b);
    CPPUNIT_ASSERT(winners.size() == 1);
    CPPUNIT_ASSERT(winners.at(0) == 1);
  }
  //------
  // solve
  //------

  void test_solve_1 () {
    istringstream r("1\n\n3\nTrey\nBarack\nMitt\n1 2 3\n1 2 3\n1 2 3\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Trey\n");
  }

  void test_solve_2 () {
    istringstream r("1\n\n3\nTrey\nBarack\nMitt\n1 2 3\n1 2 3\n2 1 3\n2 1 3\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Trey\nBarack\n");
  }

  void test_solve_3 () {
    istringstream r("1\n\n2\nTrey\nBarack\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Trey\nBarack\n");
  }

    // ------
    // Suite
    // ------
    
    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_ballots_1);
    CPPUNIT_TEST(test_read_ballots_2);
    CPPUNIT_TEST(test_read_ballots_3);
    CPPUNIT_TEST(test_get_all_votes_1);
    CPPUNIT_TEST(test_get_all_votes_2);
    CPPUNIT_TEST(test_get_all_votes_3);
    CPPUNIT_TEST(test_first_ballot_split_1);
    CPPUNIT_TEST(test_first_ballot_split_2);
    CPPUNIT_TEST(test_first_ballot_split_3);
    CPPUNIT_TEST(test_get_winners_1);
    CPPUNIT_TEST(test_get_winners_2);
    CPPUNIT_TEST(test_get_winners_3);
    CPPUNIT_TEST(test_get_winners_5);
    CPPUNIT_TEST(test_reassign_losers_1);
    CPPUNIT_TEST(test_reassign_losers_2);
    CPPUNIT_TEST(test_reassign_losers_3);
    CPPUNIT_TEST(test_voting_eval_1);
    CPPUNIT_TEST(test_voting_eval_2);
    CPPUNIT_TEST(test_voting_eval_3);
    CPPUNIT_TEST(test_first_ballot_split_4);
    CPPUNIT_TEST(test_get_winners_4);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST_SUITE_END();
    };



int main() {
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
  cout << "TestVoting.c++" << endl;
  
  CppUnit::TextTestRunner tr;
  tr.addTest(TestVoting::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}

