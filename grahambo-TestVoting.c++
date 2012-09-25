// --------------------------------
// Graham Benevelli
// EID: grambo
// CSID: grahambo
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
    // voting_solve (std::istream& r, std::ostream& w)
    // ----
    
    void test_solve_1 () {
        string s = "1\n\n";
        s += "1\n";
        s += "Graham Benevelli\n";
        s += "1";
        std::istringstream r(s);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\n");
    }

    void test_solve_2 () {
        string s = "1\n\n";
        s += "2\n";
        s += "Graham Benevelli\nTahira Benevelli\n";
        s += "1 2\n2 1";
        std::istringstream r(s);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\nTahira Benevelli\n");
    }
    
    void test_solve_3 () {
        string s = "1\n\n";
        s += "3\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "Big Willie\n";
        s += "1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2";
        std::istringstream r(s);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\n");
    }
    
    void test_solve_4 () {
        string s = "2\n\n";
        s += "3\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "Big Willie\n";
        s += "1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n";
        s += "\n2\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "1 2\n2 1";
        std::istringstream r(s);
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\n\nGraham Benevelli\nTahira Benevelli\n");
    }

  void test_solve_5 () {
    string s = "1\n\n";
    s += "4\n";
    s += "George W. Bush\n";
    s += "Al Gore\n";
    s += "Ralph Nader\n";
    s += "Ron Paul";
    s += "Santa Claus\n";
    s += "3 2 5 4 1\n";
    std::istringstream r(s);
    std::ostringstream w;
    voting_solve(r, w);
    CPPUNIT_ASSERT(w.str() == "Ralph Nader\n");
  }
      
    // ----
    // voting_read (std::istream& scan)
    // ----
    
    void test_read_1 () {
        string s = "1\n\n";
        s += "1\n";
        s += "Graham Benevelli\n";
        s += "1";
        std::istringstream r(s);
        string result = voting_read(r);
        CPPUNIT_ASSERT(result == "Graham Benevelli\n");
    }
    
    void test_read_2 () {
        string s = "1\n\n";
        s += "2\n";
        s += "Graham Benevelli\nTahira Benevelli\n";
        s += "1 2\n2 1";
        std::istringstream r(s);
        string result = voting_read(r);
        CPPUNIT_ASSERT(result == "Graham Benevelli\nTahira Benevelli\n");
    }
    
    void test_read_3 () {
        string s = "1\n\n";
        s += "3\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "Big Willie\n";
        s += "1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2";
        std::istringstream r(s);
        string result = voting_read(r);
        CPPUNIT_ASSERT(result == "Graham Benevelli\n");
    }
    
    void test_read_4 () {
        string s = "2\n\n";
        s += "3\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "Big Willie\n";
        s += "1 2 3\n1 2 3\n2 1 3\n2 1 3\n3 1 2\n";
        s += "\n2\n";
        s += "Graham Benevelli\n";
        s += "Tahira Benevelli\n";
        s += "1 2\n2 1";
        std::istringstream r(s);
        string result = voting_read(r);
        CPPUNIT_ASSERT(result == "Graham Benevelli\n\nGraham Benevelli\nTahira Benevelli\n");
    }
      
    // ----
    // voting_print
    // ----
    
    void test_print_1 () {
        std::ostringstream w;
        voting_print("Graham Benevelli", w );
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli");
    }

    void test_print_2 () {
        std::ostringstream w;
        voting_print("Graham Benevelli\nTahira Benevelli", w );
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\nTahira Benevelli");
    }
    
    void test_print_3 () {
        std::ostringstream w;
        voting_print("Graham Benevelli\n\nTahira Benevelli\n", w );
        CPPUNIT_ASSERT(w.str() == "Graham Benevelli\n\nTahira Benevelli\n");
    }
    
    // ----
    // Ballot::Ballot(string ballot)
    // ----
    
    void test_Ballot_constructor_1 () {
        Ballot b("1 2 3");
        CPPUNIT_ASSERT(b.ordering.size() == 3);
        CPPUNIT_ASSERT(b.curCanidate == 0);
    }
    
    void test_Ballot_constructor_2 () {
        Ballot b("3 2 1");
        CPPUNIT_ASSERT(b.ordering.size() == 3);
        CPPUNIT_ASSERT(b.curCanidate == 0);
    }
    
    void test_Ballot_constructor_3 () {
        Ballot b("1 2 3 4 5 6");
        CPPUNIT_ASSERT(b.ordering.size() == 6);
        CPPUNIT_ASSERT(b.curCanidate == 0);
    }
    
    // ----
    // Ballot::getTop()
    // ----
    
    void test_getTop_1 () {
        Ballot b("1 2 3 4 5 6");
        CPPUNIT_ASSERT(b.getTop() == 1);
    }
    
    void test_getTop_2 () {
        Ballot b("7 3 4 5 6 2 1");
        CPPUNIT_ASSERT(b.getTop() == 7);
    }
    
    void test_getTop_3 () {
        Ballot b("2 1");
        CPPUNIT_ASSERT(b.getTop() == 2);
    }
    
    // ----
    // Ballot::eliminateCanidates(set<int> elc)
    // ----
    
    void test_eliminateCanidates_1 () {
        Ballot b("1 2 3");
        set<int> elc;
        elc.insert(1);
        b.eliminateCanidates(elc);
        CPPUNIT_ASSERT(b.getTop() == 2);
        CPPUNIT_ASSERT(b.curCanidate == 1);
    }
    
    void test_eliminateCanidates_2 () {
        Ballot b("1 2 3");
        set<int> elc;
        elc.insert(1);
        elc.insert(2);
        b.eliminateCanidates(elc);
        CPPUNIT_ASSERT(b.getTop() == 3);
        CPPUNIT_ASSERT(b.curCanidate == 2);
    }
    
    void test_eliminateCanidates_3 () {
        Ballot b("1 2 3");
        set<int> elc;
        elc.insert(2);
        elc.insert(3);
        b.eliminateCanidates(elc);
        CPPUNIT_ASSERT(b.getTop() == 1);
        CPPUNIT_ASSERT(b.curCanidate == 0);
    }

  void test_eliminateCanidates_4 () {
    Ballot b("1 2 3");
    set<int> elc;
    elc.insert(1);
    elc.insert(2);
    elc.insert(3);
    b.eliminateCanidates(elc);
    CPPUNIT_ASSERT(b.getTop() == -1);
    CPPUNIT_ASSERT(b.curCanidate == 3);
  }
    
    // ----
    // Election::Election()
    // ----
    
    void test_Election_constructor_1 () {
        e.clear(1);
        CPPUNIT_ASSERT(e.totalBallots == 0);
        CPPUNIT_ASSERT(e.canidates.size() == 2);
        CPPUNIT_ASSERT(e.ballots.size() == 2);
        CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 0);
    }
    
    void test_Election_constructor_2 () {
        e.clear(10);
        CPPUNIT_ASSERT(e.totalBallots == 0);
        CPPUNIT_ASSERT(e.canidates.size() == 11);
        CPPUNIT_ASSERT(e.ballots.size() == 11);
        CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 0);
    }
    
    void test_Election_constructor_3 () {
        e.clear(19);
        CPPUNIT_ASSERT(e.totalBallots == 0);
        CPPUNIT_ASSERT(e.canidates.size() == 20);
        CPPUNIT_ASSERT(e.ballots.size() == 20);
        CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 0);
    }
    
    // ----
    // Election::addBallot(string s)
    // ----
    
    void test_addBallot_1 () {
        e.clear(2);
	e.addCanidate(1, "Graham Benevelli");
	e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        CPPUNIT_ASSERT(e.ballots[1].size() == 1);
        CPPUNIT_ASSERT(e.totalBallots == 1);
    }
    
    void test_addBallot_2 () {
        e.clear(2);
	e.addCanidate(1, "Graham Benevelli");
	e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        e.addBallot("1 2");
        CPPUNIT_ASSERT(e.ballots[1].size() == 2);
        CPPUNIT_ASSERT(e.totalBallots == 2);
    }
    
    void test_addBallot_3 () {
        e.clear(2);
	e.addCanidate(1, "Graham Benevelli");
	e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        e.addBallot("1 2");
        e.addBallot("2 1");
        CPPUNIT_ASSERT(e.ballots[1].size() == 2);
        CPPUNIT_ASSERT(e.totalBallots == 3);
    }
    
    // ----
    // Election::addCanidate(int key, string name)
    // ----
    
    void test_addCanidate_1 () {
        e.clear(1);
        e.addCanidate(1, "Graham Benevelli");
        CPPUNIT_ASSERT(e.ballots.size() == 2);
	CPPUNIT_ASSERT(e.canidates[1] == "Graham Benevelli");
    }
    
    void test_addCanidate_2 () {
        e.clear(19);
        e.addCanidate(19, "Tahira Benevelli");
        CPPUNIT_ASSERT(e.ballots.size() == 20);
	CPPUNIT_ASSERT(e.canidates[19] == "Tahira Benevelli");
    }
    
    void test_addCanidate_3 () {
        e.clear(21);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(21, "Tahira Benevelli");
        CPPUNIT_ASSERT(e.ballots.size() == 22);
	CPPUNIT_ASSERT(e.canidates[1] == "Graham Benevelli");
	CPPUNIT_ASSERT(e.canidates[21] == "Tahira Benevelli");
    }
    
    void test_addCanidate_4 () {
        e.clear(1);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(1, "Graham Benevelli");
        CPPUNIT_ASSERT(e.ballots.size() == 2);
	CPPUNIT_ASSERT(e.canidates[1] == "Graham Benevelli");
    }

  // ---------------------
  // Election::prepBallots
  // ---------------------

  void test_prepBallots_1 () {
    e.clear(2);
    e.addCanidate(1, "Graham Benevelli");
    e.addCanidate(2, "Tahira Benevelli");
    e.addBallot("1 2");
    e.prepBallots();
    CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 1);
  }

  void test_prepBallots_2 () {
    e.clear(2);
    e.addCanidate(1, "Graham Benevelli");
    e.addCanidate(2, "Tahira Benevelli");
    e.addBallot("1 2");
    e.addBallot("2 1");
    e.prepBallots();
    CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 0);
  }

  void test_prepBallots_3 () {
    e.clear(4);
    e.addCanidate(1, "Graham Benevelli");
    e.addCanidate(2, "Tahira Benevelli");
    e.addCanidate(2, "Big Willie");
    e.addCanidate(2, "A fourth person");
    e.addBallot("1 2");
    e.prepBallots();
    CPPUNIT_ASSERT(e.eliminatedCanidates.size() == 3);
  }
    
    // ----
    // Election::eval()
    // ----
    
    void test_eval_1 () {
        e.clear(2);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        CPPUNIT_ASSERT(e.eval() == "Graham Benevelli\n");
    }
    
    void test_eval_2 () {
        e.clear(2);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        e.addBallot("2 1");
        CPPUNIT_ASSERT(e.eval() == "Graham Benevelli\nTahira Benevelli\n");
    }
    
    void test_eval_3 () {
        e.clear(3);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addCanidate(3, "Big Willie");
        e.addBallot("1 2 3");
        e.addBallot("2 1 3");
	e.addBallot("1 2 3");
        e.addBallot("2 1 3");
        e.addBallot("3 1 2");
        CPPUNIT_ASSERT(e.eval() == "Graham Benevelli\n");
    }
    
    // ----
    // Election::findWinner()
    // ----
    
    void test_findWinner_1 () {
        e.clear(2);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        CPPUNIT_ASSERT(e.findWinner() == "Graham Benevelli\n");
    }
    
    void test_findWinner_2 () {
        e.clear(2);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addBallot("1 2");
        e.addBallot("2 1");
        CPPUNIT_ASSERT(e.findWinner() == "Graham Benevelli\nTahira Benevelli\n");
    }
   
    void test_findWinner_3 () {
        e.clear(3);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addCanidate(3, "Big Willie");
        e.addBallot("1 2 3");
	e.addBallot("1 2 3");
        e.addBallot("2 1 3");
	e.addBallot("2 1 3");
        e.addBallot("3 1 2");
        CPPUNIT_ASSERT(e.findWinner() == "");
    }

  void test_findWinner_4 () {
    e.clear(10);
    e.addCanidate(1, "Graham Benevelli");
    e.addCanidate(2, "Tahira Benevelli");
    e.addCanidate(3, "Big Willie");
    e.addCanidate(4, "4");
    e.addCanidate(5, "5");
    e.addCanidate(6, "6");
    e.addCanidate(7, "7");
    e.addCanidate(8, "8");
    e.addCanidate(9, "9");
    e.addCanidate(10, "10");
    int i;
    for(i = 0; i < 109; i++) {
      e.addBallot("4 1 2 3 5 6 7 8 9 10");
    }
    for(i = 0; i < 91; i++) {
      e.addBallot("5 1 2 3 4 6 7 8 9 10");
    }
    e.eliminatedCanidates.insert(1);
    e.eliminatedCanidates.insert(2);
    e.eliminatedCanidates.insert(3);
    e.eliminatedCanidates.insert(6);
    e.eliminatedCanidates.insert(7);
    e.eliminatedCanidates.insert(8);
    e.eliminatedCanidates.insert(9);
    e.eliminatedCanidates.insert(10);
    //cout << "Answer: " << e.findWinner();
    CPPUNIT_ASSERT(e.findWinner() == "4\n");
  }

  void test_findWinner_5 () {
    e.clear(10);
    e.addCanidate(1, "1");
    e.addCanidate(2, "2");
    e.addCanidate(3, "3");
    e.addCanidate(4, "4");
    e.addCanidate(5, "5");
    e.addCanidate(6, "6");
    e.addCanidate(7, "7");
    e.addCanidate(8, "8");
    e.addCanidate(9, "9");
    e.addCanidate(10, "10");
    int i;
    for(i = 0; i < 30; i++) {
      e.addBallot("1 4 2 3 5 6 7 8 9 10");
    }
    for(i = 0; i < 30; i++) {
      e.addBallot("2 1 3 4 5 6 7 8 9 10");
    }
    e.eliminatedCanidates.insert(3);
    e.eliminatedCanidates.insert(4);
    e.eliminatedCanidates.insert(5);
    e.eliminatedCanidates.insert(6);
    e.eliminatedCanidates.insert(7);
    e.eliminatedCanidates.insert(8);
    e.eliminatedCanidates.insert(9);
    e.eliminatedCanidates.insert(10);
    CPPUNIT_ASSERT(e.findWinner() == "1\n2\n");
  }
    // ----
    // Election::eliminateLowest()
    // ----
                       
    void test_eliminateLowest_1() {
        e.clear(3);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addCanidate(3, "Big Willie");
        e.addBallot("1 2 3");
        e.addBallot("1 2 3");
        e.addBallot("2 1 3");
        e.addBallot("2 1 3");
        e.addBallot("3 1 2");
        e.eliminateLowest();
        CPPUNIT_ASSERT(e.ballots[1].size() == 3);
        CPPUNIT_ASSERT(e.ballots[2].size() == 2);
        CPPUNIT_ASSERT(e.ballots[3].size() == 0);
    }
    
    void test_eliminateLowest_2() {
        e.clear(3);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addCanidate(3, "Big Willie");
        e.addBallot("1 2 3");
        e.addBallot("1 2 3");
        e.addBallot("2 1 3");
        e.addBallot("3 1 2");
        e.eliminateLowest();
        CPPUNIT_ASSERT(e.ballots[1].size() == 4);
        CPPUNIT_ASSERT(e.ballots[2].size() == 0);
        CPPUNIT_ASSERT(e.ballots[3].size() == 0);
    }
    
    void test_eliminateLowest_3() {
        e.clear(3);
        e.addCanidate(1, "Graham Benevelli");
        e.addCanidate(2, "Tahira Benevelli");
        e.addCanidate(3, "Big Willie");
        e.addBallot("1 2 3");
        e.addBallot("1 2 3");
        e.addBallot("2 3 1");
        e.addBallot("3 2 1");
        e.eliminateLowest();
        CPPUNIT_ASSERT(e.ballots[1].size() == 4);
        CPPUNIT_ASSERT(e.ballots[2].size() == 0);
        CPPUNIT_ASSERT(e.ballots[3].size() == 0);
    }

    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestVoting);
  
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_solve_4);
    CPPUNIT_TEST(test_solve_5);
    CPPUNIT_TEST(test_read_1);
    CPPUNIT_TEST(test_read_2);
    CPPUNIT_TEST(test_read_3);
    CPPUNIT_TEST(test_read_4);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_Ballot_constructor_1);
    CPPUNIT_TEST(test_Ballot_constructor_2);
    CPPUNIT_TEST(test_Ballot_constructor_3);
    CPPUNIT_TEST(test_getTop_1);
    CPPUNIT_TEST(test_getTop_2);
    CPPUNIT_TEST(test_getTop_3);
    CPPUNIT_TEST(test_eliminateCanidates_1);
    CPPUNIT_TEST(test_eliminateCanidates_2);
    CPPUNIT_TEST(test_eliminateCanidates_3);
    CPPUNIT_TEST(test_eliminateCanidates_4);
    CPPUNIT_TEST(test_Election_constructor_1);
    CPPUNIT_TEST(test_Election_constructor_2);
    CPPUNIT_TEST(test_Election_constructor_3);
    CPPUNIT_TEST(test_addBallot_1);
    CPPUNIT_TEST(test_addBallot_2);
    CPPUNIT_TEST(test_addBallot_3);
    CPPUNIT_TEST(test_addCanidate_1);
    CPPUNIT_TEST(test_addCanidate_2);
    CPPUNIT_TEST(test_addCanidate_3);
    CPPUNIT_TEST(test_addCanidate_4);
    CPPUNIT_TEST(test_prepBallots_1);
    CPPUNIT_TEST(test_prepBallots_2);
    CPPUNIT_TEST(test_prepBallots_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_findWinner_1);
    CPPUNIT_TEST(test_findWinner_2);
    CPPUNIT_TEST(test_findWinner_3);
    CPPUNIT_TEST(test_findWinner_4);
    CPPUNIT_TEST(test_findWinner_5);
    CPPUNIT_TEST(test_eliminateLowest_1);
    CPPUNIT_TEST(test_eliminateLowest_2);
    CPPUNIT_TEST(test_eliminateLowest_3);
   
    CPPUNIT_TEST_SUITE_END();
};
// ----
// main
// ----

int main () {
    using namespace std;
    cout << "Start Testing\n";
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();
    
    cout << "Done." << endl;
    return 0;}
