//TestVoting.c++

//g++ -pedantic -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
//valgrind TestVoting.c++.app >& TestVoting.c++.out


#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <algorithm>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"


struct TestVoting : CppUnit::TestFixture {

  // Test Ballot
  void test_ballot_1 () {
    vector<int> test = vector<int>();
    test.push_back(1);
    Ballot btest(test);
    CPPUNIT_ASSERT(btest.current_winner() == 1);
  }
  
  void test_ballot_2 () {
    vector<int> test = vector<int>();
    vector<int> loser= vector<int>();
    for(int i = 1; i < 3; i++) {
      test.push_back(i);
    }
    Ballot btest(test);
    CPPUNIT_ASSERT(btest.current_winner() == 1);
    loser.push_back(1);
    int res = btest.next_candid(loser);
    CPPUNIT_ASSERT(res == 2);
    CPPUNIT_ASSERT(btest.current_winner() == 2);
  }
  
  void test_ballot_3 () {
    vector<int> test = vector<int>();
    vector<int> loser= vector<int>();
    for(int i = 1; i < 6; i++) {
      test.push_back(i);
    }
    Ballot btest(test);
    CPPUNIT_ASSERT(btest.current_winner() == 1);
    loser.push_back(1);
    loser.push_back(3);
    int res = btest.next_candid(loser);
    CPPUNIT_ASSERT(res == 2);
    CPPUNIT_ASSERT(btest.current_winner() == 2);
    loser.push_back(2);
    res = btest.next_candid(loser);
    CPPUNIT_ASSERT(res == 4);
    CPPUNIT_ASSERT(btest.current_winner() == 4);
  }
  
  //Test Candidate
  void test_candidate_1 () {
    string name = "jake";
    
    Candidate ctest(name);
    CPPUNIT_ASSERT(ctest.name.compare("jake") == 0);
    CPPUNIT_ASSERT(ctest.num_votes() == 0);
  }
  
  void test_candidate_2() {
    string name = "jake";
    
    Candidate ctest(name);
    CPPUNIT_ASSERT(ctest.name.compare("jake") == 0);
    CPPUNIT_ASSERT(ctest.num_votes() == 0);
    
    vector<int> test = vector<int>();
    for(int i = 1; i < 6; i++) {
      test.push_back(i);
    }
    Ballot btest(test);
    ctest.add_ballot(btest);
    CPPUNIT_ASSERT(ctest.num_votes() == 1);
  }
  
  void test_candidate_3() {
    string name = "jake";
    
    Candidate ctest(name);
    CPPUNIT_ASSERT(ctest.name.compare("jake") == 0);
    CPPUNIT_ASSERT(ctest.num_votes() == 0);
    
    vector<int> test = vector<int>();
    for(int i = 1; i < 6; i++) {
      test.push_back(i);
    }
    Ballot btest(test);
    ctest.add_ballot(btest);
    CPPUNIT_ASSERT(ctest.num_votes() == 1);
    
    Ballot btest2 = ctest.rem_ballot();
    CPPUNIT_ASSERT(ctest.num_votes() == 0);
    CPPUNIT_ASSERT(btest2.current_winner() == btest.current_winner());
  }
  
  
  //Test PollManager
  void test_pollmanager_1 () {
    vector<string> names = vector<string>();
    names.push_back("jake");
    names.push_back("santa");
    names.push_back("obama");
    
    PollManager pm = PollManager(names);
    
    CPPUNIT_ASSERT(pm.numVotes == 0);
    CPPUNIT_ASSERT((int) pm.candids.size() == 3);
  }
  
  void test_pollmanager_2 () {
    vector<string> names = vector<string>();
    names.push_back("jake");
    names.push_back("santa");
    names.push_back("obama");
    
    PollManager pm = PollManager(names);
    
    CPPUNIT_ASSERT(pm.numVotes == 0);
    CPPUNIT_ASSERT((int) pm.candids.size() == 3);
    
    vector<int> test = vector<int>();
    for(int i = 0; i < 3; i++) {
      test.push_back(i);
    }
    Ballot btest(test);
    
    pm.vote(btest);
    assert(pm.numVotes == 1);
    CPPUNIT_ASSERT(pm.candids[0].num_votes() == 1);
    vector<int> test2 = vector<int>();
    test2.push_back(1);
    test2.push_back(0);
    test2.push_back(2);
    Ballot btest2(test2);
    pm.vote(btest2);
  }
  
  void test_pollmanager_3 () { //helper functions
    vector<string> names = vector<string>();
    names.push_back("jake");
    names.push_back("santa");
    names.push_back("obama");
    
    PollManager pm = PollManager(names);
    
    CPPUNIT_ASSERT(pm.numVotes == 0);
    CPPUNIT_ASSERT((int) pm.candids.size() == 3);
    
    vector<int> test = vector<int>();
    for(int i = 0; i < 3; i++) {
      test.push_back(i);
    }
    CPPUNIT_ASSERT(pm.inVect(1, test));
    CPPUNIT_ASSERT(pm.inVect(2, test));
    CPPUNIT_ASSERT(!pm.inVect(3, test));
    CPPUNIT_ASSERT(!pm.inVect(4, test));
    Ballot btest(test);
    
    pm.vote(btest);
    assert(pm.numVotes == 1);
    assert(!pm.is_tie());
    assert(pm.winner() == 0);
  }
  
  //Test Solve
  void test_solve_1 () {
    istringstream r("1\n\n2\nGood\nEvil\n1 2\n2 1\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Good\nEvil");
  }
  
  void test_solve_2 () {
    istringstream r("1\n\n5\nGlenn\nRed\nBlue\nGreen\nOrange\n1 2 3 4 5\n1 2 3 4 5\n3 2 1 5 4\n3 2 1 4 5\n2 1 3 4 5\n4 1 3 2 5\n5 1 3 2 4\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Glenn");
  }
  
  void test_solve_3 () {
    istringstream r("1\n\n2\nJake\nSanta\n\n");
    ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Jake\nSanta");
  }




  CPPUNIT_TEST_SUITE(TestVoting); // I tested 3 tests per class as some of the methods are just helpers.
  CPPUNIT_TEST(test_ballot_1);
  CPPUNIT_TEST(test_ballot_2);
  CPPUNIT_TEST(test_ballot_3);
  CPPUNIT_TEST(test_candidate_1);
  CPPUNIT_TEST(test_candidate_2);
  CPPUNIT_TEST(test_candidate_3);
  CPPUNIT_TEST(test_pollmanager_1);
  CPPUNIT_TEST(test_pollmanager_2);
  CPPUNIT_TEST(test_pollmanager_3);
  CPPUNIT_TEST(test_ballot_1);
  CPPUNIT_TEST(test_ballot_2);
  CPPUNIT_TEST(test_ballot_3);
  CPPUNIT_TEST_SUITE_END();
};


int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
