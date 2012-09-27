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

struct TestVoting : CppUnit::TestFixture
{
	// ----
	// read
	// ----
	void test_read()
	{
		std::istringstream r(
		"1\n"
		"A\n"
		"1\n"
		"1\n"
		);
		bool b = voting_read(r);
		CPPUNIT_ASSERT(b == true);
		
		CPPUNIT_ASSERT(results.size() == 1);
		CPPUNIT_ASSERT(uncounted.size() == 2);
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		CPPUNIT_ASSERT(results[0].eliminated == false);
		
		CPPUNIT_ASSERT(uncounted[0].choices.size() == 1);
		CPPUNIT_ASSERT(uncounted[0].choices[0] == 0);
	}
	void test_read2()
	{
		std::istringstream r(
		"2\n"
		"A\n"
		"B\n"
		"1 2\n"
		"1 2\n"
		"2 1\n"
		"1 2\n"
		"2 1\n"
		"2 1\n"
		);
		bool b = voting_read(r);
		CPPUNIT_ASSERT(b == true);
		
		CPPUNIT_ASSERT(results.size() == 2);
		CPPUNIT_ASSERT(uncounted.size() == 6);
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		CPPUNIT_ASSERT(results[0].eliminated == false);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].votes.size() == 0);
		CPPUNIT_ASSERT(results[1].eliminated == false);
		
		CPPUNIT_ASSERT(uncounted[0].choices.size() == 2);
		CPPUNIT_ASSERT(uncounted[0].choices[0] == 0);
		CPPUNIT_ASSERT(uncounted[0].choices[1] == 1);
		
		CPPUNIT_ASSERT(uncounted[2].choices.size() == 2);
		CPPUNIT_ASSERT(uncounted[2].choices[0] == 1);
		CPPUNIT_ASSERT(uncounted[2].choices[1] == 0);
		
		CPPUNIT_ASSERT(uncounted[5].choices.size() == 2);
		CPPUNIT_ASSERT(uncounted[5].choices[0] == 1);
		CPPUNIT_ASSERT(uncounted[5].choices[1] == 0);
	}
	void test_read3()
	{
		std::istringstream r(
		"4\n"
		"A\n"
		"B\n"
		"D\n"
		"C\n"
		"1 2 3 4\n"
		"1 2 4 3\n"
		"2 3 4 1\n"
		"4 3 1 2\n"
		"3 4 2 1\n"
		"4 2 3 1\n"
		"2 3 4 1\n"
		"4 3 1 2\n"
		"3 4 2 1\n"
		"4 2 3 1\n"
		);
		bool b = voting_read(r);
		CPPUNIT_ASSERT(b == true);
		
		CPPUNIT_ASSERT(results.size() == 4);
		CPPUNIT_ASSERT(uncounted.size() == 10);
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		CPPUNIT_ASSERT(results[0].eliminated == false);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].votes.size() == 0);
		CPPUNIT_ASSERT(results[1].eliminated == false);
		
		CPPUNIT_ASSERT(results[2].name == "D");
		CPPUNIT_ASSERT(results[2].votes.size() == 0);
		CPPUNIT_ASSERT(results[2].eliminated == false);
		
		CPPUNIT_ASSERT(results[3].name == "C");
		CPPUNIT_ASSERT(results[3].votes.size() == 0);
		CPPUNIT_ASSERT(results[3].eliminated == false);
		
		CPPUNIT_ASSERT(uncounted[0].choices.size() == 4);
		CPPUNIT_ASSERT(uncounted[0].choices[0] == 0);
		CPPUNIT_ASSERT(uncounted[0].choices[1] == 1);
		CPPUNIT_ASSERT(uncounted[0].choices[2] == 2);
		CPPUNIT_ASSERT(uncounted[0].choices[3] == 3);
		
		CPPUNIT_ASSERT(uncounted[7].choices.size() == 4);
		CPPUNIT_ASSERT(uncounted[7].choices[0] == 3);
		CPPUNIT_ASSERT(uncounted[7].choices[1] == 2);
		CPPUNIT_ASSERT(uncounted[7].choices[2] == 0);
		CPPUNIT_ASSERT(uncounted[7].choices[3] == 1);
	}
	void test_read4()
	{
		std::istringstream r(
		"3\n"
		"A\n"
		"B\n"
		"D\n"
		"1 2 3\n"
		"1 3 2\n"
		"2 3 A\n"
		"2 3 1\n"
		);
		bool b = voting_read(r);
		CPPUNIT_ASSERT(b == false);
		
		CPPUNIT_ASSERT(results.size() == 3);
		CPPUNIT_ASSERT(uncounted.size() == 2);
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		CPPUNIT_ASSERT(results[0].eliminated == false);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].votes.size() == 0);
		CPPUNIT_ASSERT(results[1].eliminated == false);
		
		CPPUNIT_ASSERT(results[2].name == "D");
		CPPUNIT_ASSERT(results[2].votes.size() == 0);
		CPPUNIT_ASSERT(results[2].eliminated == false);
		
		CPPUNIT_ASSERT(uncounted[0].choices.size() == 3);
		CPPUNIT_ASSERT(uncounted[0].choices[0] == 0);
		CPPUNIT_ASSERT(uncounted[0].choices[1] == 1);
		CPPUNIT_ASSERT(uncounted[0].choices[2] == 2);
		
		CPPUNIT_ASSERT(uncounted[1].choices.size() == 3);
		CPPUNIT_ASSERT(uncounted[1].choices[0] == 0);
		CPPUNIT_ASSERT(uncounted[1].choices[1] == 2);
		CPPUNIT_ASSERT(uncounted[1].choices[2] == 1);
	}
	
	// ----
	// eval
	// ----
	void test_eval()
	{
		results.clear();
		uncounted.clear();
		total_num_votes = 3;
		Candidate c;
		Ballot b;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		uncounted.push_back(b);
		b.choices.clear();
		
		voting_eval();
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].eliminated == true);
		CPPUNIT_ASSERT(results[0].votes.size() == 1);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].eliminated == false);
		CPPUNIT_ASSERT(results[1].votes.size() == 2);
		
		CPPUNIT_ASSERT(uncounted.size() == 0);
	}
	void test_eval2()
	{
		results.clear();
		uncounted.clear();
		total_num_votes = 4;
		Candidate c;
		Ballot b;
		
		c.name = "A";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "F";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "Q";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "Z";
		c.eliminated = false;
		results.push_back(c);
		
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(3);
		b.choices.push_back(2);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(3);
		b.choices.push_back(2);
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		voting_eval();
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].eliminated == true);
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		
		CPPUNIT_ASSERT(results[1].name == "F");
		CPPUNIT_ASSERT(results[1].eliminated == false);
		CPPUNIT_ASSERT(results[1].votes.size() == 2);
		
		CPPUNIT_ASSERT(results[2].name == "Q");
		CPPUNIT_ASSERT(results[2].eliminated == true);
		CPPUNIT_ASSERT(results[2].votes.size() == 0);
		
		CPPUNIT_ASSERT(results[3].name == "Z");
		CPPUNIT_ASSERT(results[3].eliminated == false);
		CPPUNIT_ASSERT(results[3].votes.size() == 2);
		
		CPPUNIT_ASSERT(uncounted.size() == 0);
	}
	void test_eval3()
	{
		results.clear();
		uncounted.clear();
		total_num_votes = 8;
		Candidate c;
		Ballot b;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "C";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "D";
		c.eliminated = false;
		results.push_back(c);
		
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(3);
		b.choices.push_back(2);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(3);
		b.choices.push_back(2);
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(3);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(2);
		b.choices.push_back(3);
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(3);
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(3);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		voting_eval();
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].eliminated == false);
		CPPUNIT_ASSERT(results[0].votes.size() == 5);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].eliminated == true);
		CPPUNIT_ASSERT(results[1].votes.size() == 0);
		
		CPPUNIT_ASSERT(results[2].name == "C");
		CPPUNIT_ASSERT(results[2].eliminated == true);
		CPPUNIT_ASSERT(results[2].votes.size() == 0);
		
		CPPUNIT_ASSERT(results[3].name == "D");
		CPPUNIT_ASSERT(results[3].eliminated == true);
		CPPUNIT_ASSERT(results[3].votes.size() == 3);
		
		CPPUNIT_ASSERT(uncounted.size() == 0);
	}
	void test_eval4()
	{
		results.clear();
		uncounted.clear();
		total_num_votes = 9;
		Candidate c;
		Ballot b;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "C";
		c.eliminated = false;
		results.push_back(c);
		
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(2);
		b.choices.push_back(0);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(2);
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(2);
		b.choices.push_back(0);
		b.choices.push_back(1);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		voting_eval();
		
		CPPUNIT_ASSERT(results[0].name == "A");
		CPPUNIT_ASSERT(results[0].eliminated == false);
		CPPUNIT_ASSERT(results[0].votes.size() == 6);
		
		CPPUNIT_ASSERT(results[1].name == "B");
		CPPUNIT_ASSERT(results[1].eliminated == true);
		CPPUNIT_ASSERT(results[1].votes.size() == 3);
		
		CPPUNIT_ASSERT(results[2].name == "C");
		CPPUNIT_ASSERT(results[2].eliminated == true);
		CPPUNIT_ASSERT(results[2].votes.size() == 0);
		
		CPPUNIT_ASSERT(uncounted.size() == 0);
	}
	
	void test_eval5()
	{
		results.clear();
		uncounted.clear();
		total_num_votes = 5;
		Candidate c;
		Ballot b;
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "N";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "E";
		c.eliminated = false;
		results.push_back(c);
		
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(2);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(2);
		b.choices.push_back(3);
		b.choices.push_back(1);
		b.choices.push_back(0);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(3);
		b.choices.push_back(0);
		b.choices.push_back(1);
		b.choices.push_back(2);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(1);
		b.choices.push_back(3);
		b.choices.push_back(2);
		b.choices.push_back(0);
		uncounted.push_back(b);
		b.choices.clear();
		
		b.choices.push_back(2);
		b.choices.push_back(1);
		b.choices.push_back(0);
		b.choices.push_back(3);
		uncounted.push_back(b);
		b.choices.clear();
		
		voting_eval();
		
		CPPUNIT_ASSERT(results[0].name == "B");
		CPPUNIT_ASSERT(results[0].eliminated == true);
		CPPUNIT_ASSERT(results[0].votes.size() == 0);
		
		CPPUNIT_ASSERT(results[1].name == "A");
		CPPUNIT_ASSERT(results[1].eliminated == false);
		CPPUNIT_ASSERT(results[1].votes.size() == 3);
		
		CPPUNIT_ASSERT(results[2].name == "N");
		CPPUNIT_ASSERT(results[2].eliminated == true);
		CPPUNIT_ASSERT(results[2].votes.size() == 2);
		
		CPPUNIT_ASSERT(results[3].name == "E");
		CPPUNIT_ASSERT(results[3].eliminated == true);
		CPPUNIT_ASSERT(results[3].votes.size() == 0);
	}
	
	// -----
	// print
	// -----
	void test_print()
	{
		std::ostringstream w;
		results.clear();
		Candidate c;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		voting_print(w);
		CPPUNIT_ASSERT(w.str() == "A\n");
	}
	void test_print2()
	{
		std::ostringstream w;
		results.clear();
		Candidate c;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "C";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		voting_print(w);
		CPPUNIT_ASSERT(w.str() == "A\nB\n");
	}
	void test_print3()
	{
		std::ostringstream w;
		results.clear();
		Candidate c;
		
		c.name = "A";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "C";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = false;
		results.push_back(c);
		
		c.name = "F";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "X";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "Y";
		c.eliminated = false;
		results.push_back(c);
		
		voting_print(w);
		CPPUNIT_ASSERT(w.str() == "A\nB\nY\n");
	}
	void test_print4()
	{
		std::ostringstream w;
		results.clear();
		Candidate c;
		
		c.name = "A";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "C";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "B";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "F";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "X";
		c.eliminated = true;
		results.push_back(c);
		
		c.name = "Y";
		c.eliminated = true;
		results.push_back(c);
		
		voting_print(w);
		CPPUNIT_ASSERT(w.str() == "");
	}
	
	// -----
	// solve
	// -----
	void test_solve()
	{
		std::string input =
		"1\n"
		"\n"
		"1\n"
		"A\n"
		"1\n"
		"1\n"
		;
		std::string output =
		"A\n"
		""
		;
		std::istringstream r(input);
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == output);
	}
	void test_solve2()
	{
		std::string input =
		"1\n"
		"\n"
		"3\n"
		"A\n"
		"X\n"
		"E\n"
		"1 2 3\n"
		"2 3 1\n"
		"2 1 3\n"
		"3 2 1\n"
		"1 2 3\n"
		"2 3 1\n"
		"2 1 3\n"
		"3 2 1\n"
		"2 1 3\n"
		;
		std::string output =
		"X\n"
		;
		std::istringstream r(input);
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == output);
	}
	void test_solve3()
	{
		std::string input =
		"2\n"
		"\n"
		"4\n"
		"A\n"
		"X\n"
		"E\n"
		"S\n"
		"1 2 4 3\n"
		"2 4 3 1\n"
		"2 1 3 4\n"
		"4 3 2 1\n"
		"4 1 2 3\n"
		"2 4 3 1\n"
		"4 2 1 3\n"
		"3 2 4 1\n"
		"3 1 2 4\n"
		"\n"
		"2\n"
		"H\n"
		"O\n"
		"1 2\n"
		"2 1\n"
		"2 1\n"
		"1 2\n"
		;
		std::string output =
		"X\n"
		"\n"
		"H\n"
		"O\n"
		;
		std::istringstream r(input);
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == output);
	}
	void test_solve4()
	{
		std::string input =
		"3\n"
		"\n"
		"10\n"
		"C\n"
		"I\n"
		"Y\n"
		"S\n"
		"P\n"
		"E\n"
		"Q\n"
		"A\n"
		"T\n"
		"H\n"
		"1 4 9 6 2 3 10 7 8 5\n"
		"1 4 8 10 9 3 2 5 7 6\n"
		"1 10 2 7 3 9 5 6 4 8\n"
		"5 1 4 9 10 2 8 3 7 6\n"
		"5 9 3 1 2 8 6 7 10 4\n"
		"5 2 9 8 10 1 3 4 6 7\n"
		"7 1 4 9 2 5 3 10 6 8\n"
		"7 10 2 8 9 3 1 6 4 5\n"
		"7 4 9 8 1 6 3 7 10 2\n"
		"7 5 8 2 1 9 3 10 6 4\n"
		"7 1 2 4 9 10 5 8 3 6\n"
		"9 2 8 5 3 4 6 10 7 1\n"
		"9 3 10 1 4 5 8 6 7 2\n"
		"3 1 1 1 1 1 1 1 1 1\n" //numbers after first
		"3 1 1 1 1 1 1 1 1 1\n" //don't matter
		"3 1 1 1 1 1 1 1 1 1\n"
		"3 1 1 1 1 1 1 1 1 1\n"
		"3 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"6 1 1 1 1 1 1 1 1 1\n"
		"8 1 1 1 1 1 1 1 1 1\n"
		"8 1 1 1 1 1 1 1 1 1\n"
		"8 1 1 1 1 1 1 1 1 1\n"
		"10 1 1 1 1 1 1 1 1 1\n"
		"10 1 1 1 1 1 1 1 1 1\n"
		"10 1 1 1 1 1 1 1 1 1\n"
		"10 1 1 1 1 1 1 1 1 1\n"
		"\n"
		"1\n"
		"A\n"
		"1\n"
		"1\n"
		"1\n"
		"1\n"
		"1\n"
		"\n"
		"3\n"
		"D\n"
		"U\n"
		"N\n"
		"1 3 2\n"
		"3 2 1\n"
		"2 1 3\n"
		;
		std::string output =
		"Y\n"
		"E\n"
		"A\n"
		"H\n"
		"\n"
		"A\n"
		"\n"
		"D\n"
		"U\n"
		"N\n"
		;
		std::istringstream r(input);
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == output);
	}
	
	void test_solve5()
	{
		std::string input =
			"5\n"
			"\n"
			"4\n"
			"John\n"
			"Rick\n"
			"Barry\n"
			"Sarah\n"
			"1 2 3 4\n"
			"2 1 3 4\n"
			"\n"
			"3\n"
			"Harry\n"
			"Ron\n"
			"Hermoine\n"
			"1 3 2\n"
			"3 1 2\n"
			"1 2 3\n"
			"3 1 2\n"
			"\n"
			"7\n"
			"Jeff\n"
			"Troy\n"
			"Annie\n"
			"Shirley\n"
			"Britta\n"
			"Abed\n"
			"Pierce\n"
			"1 2 3 4 5 6 7\n"
			"1 2 3 4 5 6 7\n"
			"6 2 3 4 5 1 7\n"
			"1 2 3 4 5 6 7\n"
			"1 2 3 4 5 6 7\n"
			"1 2 3 4 5 6 7\n"
			"2 3 1 4 5 6 7\n"
			"2 2 3 1 5 6 7"
			;
		std::string output =
		"John\n"
		"Rick\n"
		"\n"
		"Harry\n"
		"Hermoine\n"
		"\n"
		"Jeff\n"
		;
	}
	
	
	// -----
	// suite
	// -----
	
	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read2);
	CPPUNIT_TEST(test_read3);
	CPPUNIT_TEST(test_read4);
	CPPUNIT_TEST(test_eval);
	CPPUNIT_TEST(test_eval2);
	CPPUNIT_TEST(test_eval3);
	CPPUNIT_TEST(test_eval4);
	CPPUNIT_TEST(test_eval5);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print2);
	CPPUNIT_TEST(test_print3);
	CPPUNIT_TEST(test_print4);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve2);
	CPPUNIT_TEST(test_solve3);
	CPPUNIT_TEST(test_solve4);
	CPPUNIT_TEST(test_solve5);
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main ()
{
	using namespace std;
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestVoting.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}