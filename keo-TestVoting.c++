// includes
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			// TestFixture
#include "cppunit/TextTestRunner.h"			// TextTestRunner

#include "Voting.h"

using std::istringstream;


// -----------
// TestVoting
struct TestVoting : CppUnit::TestFixture {
	// ----
	// read
	void test_ballot0 () {
		istringstream r("8 9 5 11 20\n");
		Ballot b(5);
		
		CPPUNIT_ASSERT(Ballot::total == 1);
	}
	
	void test_ballot1 () {
		istringstream r("8 9 5 11 20\n");
		
		Ballot b(5);
		
		CPPUNIT_ASSERT(Ballot::total == 2);
	}
	
	void test_ballot2 () {
		istringstream r("8 9 5 11 20\n");
		Ballot b(5);
		b.input(r);
		
		CPPUNIT_ASSERT(Ballot::total == 3);
		CPPUNIT_ASSERT(b.choices.size() == 5);
	}
	
	void test_candidate0 () {
		Candidate c;
		
		CPPUNIT_ASSERT(c.votes.size() == 0);
	}
	
	void test_candidate1() {
		Candidate c;
		c.name = "ME";
		
		CPPUNIT_ASSERT(c.name.compare("ME") == 0);
	}
	
	void test_candidate2() {
		Candidate c;
		c.name = "Odin";
		
		CPPUNIT_ASSERT(c.name.compare("Odin") == 0);
	}
	
	void test_election0() {
		istringstream r("1\nFSM\n1\n");
		Election e(r);
		e.input();
		
		CPPUNIT_ASSERT(e.numCan == 1);
		CPPUNIT_ASSERT(e.candidates.size() == 1);
	}
	
	void test_election1() {
		istringstream r("2\nFSM\nJebus\n1 2\n");
		Election e(r);
		e.input();
		
		CPPUNIT_ASSERT(e.numCan == 2);
		CPPUNIT_ASSERT(e.candidates.size() == 2);
		CPPUNIT_ASSERT(e.candidates.front().name.compare("FSM") == 0);
	}
	
	void test_election2() {
		istringstream r("2\nFSM\nJebus\n1 2\n1 2\n2 1\n");
		Election e(r);
		e.input();
		
		CPPUNIT_ASSERT(e.numCan == 2);
		CPPUNIT_ASSERT(e.candidates.size() == 2);
		CPPUNIT_ASSERT(e.candidates.front().name.compare("FSM") == 0);
		CPPUNIT_ASSERT(e.candidates.front().votes.size() == 2);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestVoting);
	
	CPPUNIT_TEST(test_ballot0);
	CPPUNIT_TEST(test_ballot1);
	CPPUNIT_TEST(test_ballot2);
	CPPUNIT_TEST(test_candidate0);
	CPPUNIT_TEST(test_candidate1);
	CPPUNIT_TEST(test_candidate2);
	CPPUNIT_TEST(test_election0);
	CPPUNIT_TEST(test_election1);
	CPPUNIT_TEST(test_election2);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	//using namespace std;
	//ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestVoting.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();

	cout << "Unit tests done." << endl;
	return 0;
}
