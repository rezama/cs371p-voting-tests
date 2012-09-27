// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <list>
#include <queue>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture {

	// ---------------
	// test_read_names
	// ---------------
	void test_read_names_1 () {
		std::istringstream r("Joe\nLarry\nMoe\n");
		vector<string> names (3);
		read_names(r, 3, names);
		CPPUNIT_ASSERT(names.size() == 3);
		CPPUNIT_ASSERT(names[0] == "Joe");
		CPPUNIT_ASSERT(names[1] == "Larry");
		CPPUNIT_ASSERT(names[2] == "Moe");
	}
	
	void test_read_names_2 () {
		std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan");
		vector<string> names (3);
		read_names(r, 3, names);
		CPPUNIT_ASSERT(names.size() == 3);
		CPPUNIT_ASSERT(names[0] == "John Doe");
		CPPUNIT_ASSERT(names[1] == "Jane Smith");
		CPPUNIT_ASSERT(names[2] == "Sirhan Sirhan");
	}
	
	void test_read_names_3 ()  {
		std::istringstream r("A\nB\nC\nD\nE\nF\nG\nH");
		vector<string> names (8);
		read_names(r, 8, names);
		CPPUNIT_ASSERT(names.size() == 8);
		CPPUNIT_ASSERT(names[0] == "A");
		CPPUNIT_ASSERT(names[1] == "B");
		CPPUNIT_ASSERT(names[2] == "C");
		CPPUNIT_ASSERT(names[3] == "D");
		CPPUNIT_ASSERT(names[4] == "E");
		CPPUNIT_ASSERT(names[5] == "F");
		CPPUNIT_ASSERT(names[6] == "G");
		CPPUNIT_ASSERT(names[7] == "H");
	}
	
	// ---------------
	// test_read_votes
	// ---------------
	void test_read_votes_1 () {
		std::istringstream r("5 3 6 8 9");
		vector< queue<int> > ballots = read_votes(r);
		CPPUNIT_ASSERT(ballots.size() == 1);
		
		queue<int> temp = ballots[0];
		CPPUNIT_ASSERT(temp.front() == 5); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 6); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 8); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 9); temp.pop(); 
	}
	
	void test_read_votes_2 () {
		std::istringstream r("1 2 3 4\n8 11 10 9\n12 6 7 5\n");
		vector< queue<int> > ballots = read_votes(r);
		CPPUNIT_ASSERT(ballots.size() == 3);
		
		queue<int> temp = ballots[0];
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 4); temp.pop();
		
		temp = ballots[1];
		CPPUNIT_ASSERT(temp.front() == 8); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 11); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 10); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 9); temp.pop();
		
		temp = ballots[2];
		CPPUNIT_ASSERT(temp.front() == 12); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 6); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 7); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 5); temp.pop();
	}
	
	void test_read_votes_3 () {
		std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		vector< queue<int> > ballots = read_votes(r);
		CPPUNIT_ASSERT(ballots.size() == 5);
		
		queue<int> temp = ballots[0];
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.size() == 0);
		
		temp = ballots[1];
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.size() == 0);
		
		temp = ballots[2];
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.size() == 0);
		
		temp = ballots[3];
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.size() == 0);
		
		temp = ballots[4];
		CPPUNIT_ASSERT(temp.front() == 3); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 1); temp.pop();
		CPPUNIT_ASSERT(temp.front() == 2); temp.pop();
		CPPUNIT_ASSERT(temp.size() == 0);
	}
	
	// ------------------
	// test_victory_check
	// ------------------
	void test_victory_check_1() {
		queue<int> q0;
		q0.push(1); q0.push(3); q0.push(4);
		queue<int> q1;
		q1.push(2); q1.push(5);
		
		vector< queue<int> > v(2);
		v[0] = q0; v[1] = q1;
		
		list<int> test = victory_check(v, 5);
		CPPUNIT_ASSERT(test.size() == 1);
		CPPUNIT_ASSERT(test.front() == 0);
	}
	
	void test_victory_check_2() {
		queue<int> q0;
		q0.push(1); q0.push(2); q0.push(3);
		queue<int> q1;
		q1.push(4); q1.push(7); q1.push(8);
		queue<int> q2;
		q2.push(5); q2.push(9); q2.push(6);
		
		vector< queue<int> > v(3);
		v[0] = q0; v[1] = q1; v[2] = q2;
		
		list<int> test = victory_check(v, 9);
		CPPUNIT_ASSERT(test.size() == 3);
		CPPUNIT_ASSERT(test.front() == 0); test.pop_front();
		CPPUNIT_ASSERT(test.front() == 1); test.pop_front();
		CPPUNIT_ASSERT(test.front() == 2);
	}
	
	void test_victory_check_3() {
		queue<int> q0;
		q0.push(1); q0.push(2); q0.push(3);
		queue<int> q1;
		q1.push(4); q1.push(7); q1.push(8);
		queue<int> q2;
		q2.push(5); q2.push(6);
		
		vector< queue<int> > v(3);
		v[0] = q0; v[1] = q1; v[2] = q2;
		
		list<int> test = victory_check(v, 8);
		CPPUNIT_ASSERT(test.size() == 0);
	}
	
	void test_victory_check_4() {
		queue<int> q0;
		queue<int> q1;
		q1.push(6); q1.push(1); q1.push(3); q1.push(4); q1.push(7);
		queue<int> q2;
		queue<int> q3;
		q3.push(5); q3.push(2); q3.push(8); q3.push(9); q3.push(10);
		queue<int> q4;
		
		vector< queue<int> > v(5);
		v[0] = q0; v[1] = q1; v[2] = q2; v[3] = q3; v[4] = q4;
		
		list<int> test = victory_check(v, 10);
		CPPUNIT_ASSERT(true);
		CPPUNIT_ASSERT(test.size() == 2);
	}
	
	// ---------------
	// test_get_losers
	// ---------------
	void test_get_losers_1() {
		queue<int> q0;
		q0.push(1); q0.push(3); q0.push(4);
		queue<int> q1;
		q1.push(2); q1.push(5);
		
		vector< queue<int> > v(2);
		v[0] = q0; v[1] = q1;
		
		list<int> test = get_losers(v);
		CPPUNIT_ASSERT(test.size() == 1);
		CPPUNIT_ASSERT(test.front() == 1);
	}
	
	void test_get_losers_2() {
		queue<int> q0;
		q0.push(1); q0.push(2); q0.push(3); q0.push(10);
		queue<int> q1;
		q1.push(4); q1.push(7); q1.push(8);
		queue<int> q2;
		q2.push(5); q2.push(9); q2.push(6);
		
		vector< queue<int> > v(3);
		v[0] = q0; v[1] = q1; v[2] = q2;
		
		list<int> test = get_losers(v);
		CPPUNIT_ASSERT(test.size() == 2);
		CPPUNIT_ASSERT(test.front() == 1); test.pop_front();
		CPPUNIT_ASSERT(test.front() == 2); test.pop_front();
	}
	
	void test_get_losers_3() {
		queue<int> q0;
		q0.push(1); q0.push(2); q0.push(3); q0.push(12);
		queue<int> q1;
		q1.push(4); q1.push(7); q1.push(8);
		queue<int> q2;
		q2.push(5); q2.push(9); q2.push(6); q2.push(16); q2.push(18);
		queue<int> q3;
		q3.push(10); q3.push(15); q3.push(19); q3.push(20);
		queue<int> q4;
		q4.push(11); q4.push(17); q4.push(21);
		queue<int> q5;
		q5.push(23); q5.push(24); q5.push(22); q5.push(25); q5.push(28);
		queue<int> q6;
		q6.push(28); q6.push(26); q6.push(27);
		
		
		vector< queue<int> > v(7);
		v[0] = q0; v[1] = q1; v[2] = q2; v[3] = q3; v[4] = q4; v[5] = q5; v[6] = q6;
		
		list<int> test = get_losers(v);
		CPPUNIT_ASSERT(test.size() == 3);
		CPPUNIT_ASSERT(test.front() == 1); test.pop_front();
		CPPUNIT_ASSERT(test.front() == 4); test.pop_front();
		CPPUNIT_ASSERT(test.front() == 6);
	}
	
	// -----------------------
	// test_reallocate_ballots
	// -----------------------
	void test_reallocate_ballots_1() {
		queue<int> b0;
		b0.push(1); b0.push(2); b0.push(3);
		queue<int> b1;
		b1.push(2); b1.push(1); b1.push(3);
		queue<int> b2;
		b2.push(3); b2.push(1); b2.push(2);
		queue<int> b3;
		b3.push(1); b3.push(2); b3.push(3);
		queue<int> b4;
		b4.push(2); b4.push(1); b4.push(3);
		
		vector< queue<int> > ballots(5);
		ballots[0]=b0; ballots[1]=b1; ballots[2]=b2; ballots[3]=b3; ballots[4]=b4;		
		
		queue<int> p0;
		p0.push(0); p0.push(3);
		queue<int> p1;
		p1.push(1); p1.push(4);
		queue<int> p2;
		p2.push(2);
		
		vector< queue<int> > votePile(3);
		votePile[0]=p0; votePile[1]=p1; votePile[2]=p2;
		
		reallocate_votes(votePile, ballots);

		CPPUNIT_ASSERT(votePile[2].size() == 0);
		CPPUNIT_ASSERT(ballots[2].size() == 2);
	}
	
	void test_reallocate_ballots_2() {
		queue<int> b0;
		b0.push(1); b0.push(2); b0.push(3); b0.push(4);
		queue<int> b1;
		b1.push(2); b1.push(1); b1.push(3); b1.push(4);
		queue<int> b2;
		b2.push(3); b2.push(1); b2.push(2); b2.push(4);
		queue<int> b3;
		b3.push(1); b3.push(2); b3.push(3); b3.push(4);
		queue<int> b4;
		b4.push(2); b4.push(1); b4.push(3); b4.push(4);
		queue<int> b5;
		b5.push(4); b5.push(3); b5.push(2); b5.push(1);
		
		vector< queue<int> > ballots(6);
		ballots[0]=b0; ballots[1]=b1; ballots[2]=b2; 
		ballots[3]=b3; ballots[4]=b4; ballots[5]=b5;	
		
		queue<int> p0;
		p0.push(0); p0.push(3);
		queue<int> p1;
		p1.push(1); p1.push(4);
		queue<int> p2;
		p2.push(2);
		queue<int> p3;
		p3.push(5);
		
		vector< queue<int> > votePile(4);
		votePile[0]=p0; votePile[1]=p1; votePile[2]=p2; votePile[3]=p3;
		
		reallocate_votes(votePile, ballots);

		CPPUNIT_ASSERT(votePile[2].size() == 0);
		CPPUNIT_ASSERT(votePile[3].size() == 0);
		CPPUNIT_ASSERT(ballots[2].size() == 3);
		CPPUNIT_ASSERT(ballots[5].size() == 2);
	}
	
	void test_reallocate_ballots_3() {
		queue<int> b0;
		b0.push(4); b0.push(2); b0.push(3); b0.push(1);
		queue<int> b1;
		b1.push(2); b1.push(3); b1.push(4); b1.push(1);
		queue<int> b2;
		b2.push(4); b2.push(2); b2.push(3); b2.push(1);
		queue<int> b3;
		b3.push(4); b3.push(3); b3.push(2); b3.push(1);
		queue<int> b4;
		b4.push(3); b4.push(2); b4.push(4); b4.push(1);
		queue<int> b5;
		b5.push(3); b5.push(4); b5.push(2); b5.push(1);
		
		vector< queue<int> > ballots(6);
		ballots[0]=b0; ballots[1]=b1; ballots[2]=b2; 
		ballots[3]=b3; ballots[4]=b4; ballots[5]=b5;	
		
		queue<int> p0;
		queue<int> p1;
		p1.push(1);
		queue<int> p2;
		p2.push(4); p2.push(5);
		queue<int> p3;
		p3.push(3); p3.push(2); p3.push(0);
		
		vector< queue<int> > votePile(4);
		votePile[0]=p0; votePile[1]=p1; votePile[2]=p2; votePile[3]=p3;
		
		reallocate_votes(votePile, ballots);
		
		CPPUNIT_ASSERT(votePile[0].size() == 0);
		CPPUNIT_ASSERT(votePile[1].size() == 0);
		CPPUNIT_ASSERT(votePile[2].size() == 3);
		CPPUNIT_ASSERT(votePile[3].size() == 3);
		
	}
	
	// -----------------
	// test_run_election
	// -----------------
	void test_run_election_1() {
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		std::ostringstream w;
		run_election(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}
	
	void test_run_election_2() {
		std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
		std::ostringstream w;
		run_election(r, w);
		CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
	}
	
	void test_run_election_3() {
		std::istringstream r("3\nCobra Commander\nDarth Vader\nMegatron\n1 2 3\n1 3 2\n2 1 3\n2 3 1\n3 1 2\n3 2 1\n1 2 3");
		std::ostringstream w;
		run_election(r, w);
		CPPUNIT_ASSERT(w.str() == "Cobra Commander\n");
	}
	
	// ---------------
	// test_run_voting
	// ---------------
	void test_run_voting_1() {
		std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
		std::ostringstream w;
		run_voting(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}
	
	void test_run_voting_2() {
		std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
		std::ostringstream w;
		run_voting(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n\nRed\nGreen\n");
	}
	void test_run_voting_3() {
		std::istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n\n3\nCobra Commander\nDarth Vader\nMegatron\n1 2 3\n1 3 2\n2 1 3\n2 3 1\n3 1 2\n3 2 1\n1 2 3\n");
		std::ostringstream w;
		run_voting(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n\nRed\nGreen\n\nCobra Commander\n");
	}
	
	// -----
	// suite
	// -----
	
	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read_names_1);
	CPPUNIT_TEST(test_read_names_2);
	CPPUNIT_TEST(test_read_names_3);
	
	CPPUNIT_TEST(test_read_votes_1);
	CPPUNIT_TEST(test_read_votes_2);
	CPPUNIT_TEST(test_read_votes_3);
	
	CPPUNIT_TEST(test_victory_check_1);
	CPPUNIT_TEST(test_victory_check_2);
	CPPUNIT_TEST(test_victory_check_3);
	CPPUNIT_TEST(test_victory_check_4);

	CPPUNIT_TEST(test_get_losers_1);
	CPPUNIT_TEST(test_get_losers_2);
	CPPUNIT_TEST(test_get_losers_3);
	
	CPPUNIT_TEST(test_reallocate_ballots_1);
	CPPUNIT_TEST(test_reallocate_ballots_2);
	CPPUNIT_TEST(test_reallocate_ballots_3);
	
	CPPUNIT_TEST(test_run_election_1);
	CPPUNIT_TEST(test_run_election_2);
	CPPUNIT_TEST(test_run_election_3);
	
	CPPUNIT_TEST(test_run_voting_1);
	CPPUNIT_TEST(test_run_voting_2);
	CPPUNIT_TEST(test_run_voting_3);
	CPPUNIT_TEST_SUITE_END();
};

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false);
	cout << "TestVoting.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}
