#include <iostream>
#include <sstream>
#include <string>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

struct TestVoting : CppUnit::TestFixture{
	void test_Vote_front(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.front() == 1);
	}

	void test_Vote_front_1(){
		string vote = "1337 1338";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.front() == 1337);
	}

	void test_Vote_front_2(){
		string vote = "10 9 8 7 6 5 4 3 2 1";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.front() == 10);
	}

	void test_Vote_getNextValid(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		bool active[] = {false, false, true, false, false, true, false, true, true, true};
		CPPUNIT_ASSERT(newVote.getNextValid(active) == 3);
	}

	void test_Vote_getNextValid_1(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		bool active[] = {true, false, false, false, false, true, false, true, true, true};
		CPPUNIT_ASSERT(newVote.getNextValid(active) == 1);
	}
	void test_Vote_getNextValid_2(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		bool active[] = {false, false, false, false, false, false, false, false, false, true};
		CPPUNIT_ASSERT(newVote.getNextValid(active) == 10);
	}

	void test_Vote_getWeight(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 3;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.getWeight() == 3);
	}

	void test_Vote_getWeight_1(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 42;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.getWeight() == 42);
	}
	
	void test_Vote_getWeight_2(){
		string vote = "1 2 3 4 5 6 7 8 9 10";
		int weight = 1337;
		int numCandidates = 10;
		Vote newVote (vote, weight, numCandidates);
		CPPUNIT_ASSERT(newVote.getWeight() == 1337);
	}
	void test_read(){
		std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		vector<string> candidates;
		map<string, int> votes;
		voting_read(r, candidates, votes);
		CPPUNIT_ASSERT(candidates[0] == "John Doe");
		CPPUNIT_ASSERT(candidates[1] == "Jane Smith");
		CPPUNIT_ASSERT(candidates[2] == "Sirhan Sirhan");
		CPPUNIT_ASSERT(votes["1 2 3"] == 2);
		CPPUNIT_ASSERT(votes["2 1 3"] == 1);
		CPPUNIT_ASSERT(votes["2 3 1"] == 1);
		CPPUNIT_ASSERT(votes["3 1 2"] == 1);
	}

	void test_read_1(){
		std::istringstream r("2\nPSY\nHyunA\n");
		vector<string> candidates;
		map<string, int> votes;
		voting_read(r, candidates, votes);
		CPPUNIT_ASSERT(candidates[0] == "PSY");
		CPPUNIT_ASSERT(candidates[1] == "HyunA");
		CPPUNIT_ASSERT(votes.empty());
	}

	void test_read_2(){
		std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
		vector<string> candidates;
		map<string, int> votes;
		voting_read(r, candidates, votes);
		CPPUNIT_ASSERT(candidates[0] == "Red");
		CPPUNIT_ASSERT(candidates[1] == "Green");
		CPPUNIT_ASSERT(candidates[2] == "Blue");
		CPPUNIT_ASSERT(candidates[3] == "Orange");
		CPPUNIT_ASSERT(votes["1 2 3 4"] == 2);
		CPPUNIT_ASSERT(votes["2 1 3 4"] == 1);
		CPPUNIT_ASSERT(votes["2 3 1 4"] == 1);
		CPPUNIT_ASSERT(votes["3 4 1 2"] == 1);
		CPPUNIT_ASSERT(votes["4 3 2 1"] == 1);
	}

	void test_eval(){
		map<string, int> votes;
		vector<string> candidates;
		votes["1 2 3"] = 2;
		votes["2 1 3"] = 1;
		votes["2 3 1"] = 1;
		votes["3 1 2"] = 1;
		candidates.push_back("John Doe");
		candidates.push_back("Jane Smith");
		candidates.push_back("Sirhan Sirhan");
		list<string> results = voting_eval(votes, candidates);
		CPPUNIT_ASSERT(results.size() == 1);
		CPPUNIT_ASSERT(results.front() == "John Doe");
	}

	void test_eval_1(){
		map<string, int> votes;
		vector<string> candidates;
		votes["1 2 3 4"] = 2;
		votes["2 1 3 4"] = 1;
		votes["2 3 1 4"] = 1;
		votes["3 4 1 2"] = 1;
		votes["4 3 2 1"] = 1;
		candidates.push_back("Red");
		candidates.push_back("Green");
		candidates.push_back("Blue");
		candidates.push_back("Orange");
		list<string> results = voting_eval(votes, candidates);
		CPPUNIT_ASSERT(results.size() == 2);
		CPPUNIT_ASSERT(results.back() == "Red");
		CPPUNIT_ASSERT(results.front() == "Green");
	}

	void test_eval_2(){
		map<string, int> votes;
		vector<string> candidates;
		candidates.push_back("PSY");
		candidates.push_back("HyunA");
		list<string> results = voting_eval(votes, candidates);
		CPPUNIT_ASSERT(results.size() == 2);
		CPPUNIT_ASSERT(results.back() == "PSY");
		CPPUNIT_ASSERT(results.front() == "HyunA");
	}

	void test_print(){
		std::ostringstream w;
		list<string> results;
		results.push_back("John Doe");
		voting_print(w, results);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}

	void test_print_1(){
		std::ostringstream w;
		list<string> results;
		results.push_back("HyunA");
		results.push_back("PSY");
		voting_print(w, results);
		CPPUNIT_ASSERT(w.str() == "PSY\nHyunA\n");
	}

	void test_print_2(){
		std::ostringstream w;
		list<string> results;
		results.push_back("Green");
		results.push_back("Red");
		voting_print(w, results);
		CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
	}

	void test_solve(){	
		std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}

	void test_solve_1(){	
		std::istringstream r("1\n\n2\nPSY\nHyunA\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "PSY\nHyunA\n");
	}

	void test_solve_2(){
		std::istringstream r("3\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n2\nPSY\nHyunA\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\nPSY\nHyunA\nRed\nGreen\n");
	}

	CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_Vote_front);
	CPPUNIT_TEST(test_Vote_front_1);
	CPPUNIT_TEST(test_Vote_front_2);
	CPPUNIT_TEST(test_Vote_getNextValid);
	CPPUNIT_TEST(test_Vote_getNextValid_1);
	CPPUNIT_TEST(test_Vote_getNextValid_2);
	CPPUNIT_TEST(test_Vote_getWeight);
	CPPUNIT_TEST(test_Vote_getWeight_1);
	CPPUNIT_TEST(test_Vote_getWeight_2);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_eval);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_print);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_solve);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST_SUITE_END();
};

int main(){
	using namespace std;
	ios_base::sync_with_stdio(false);
	cout << "TestVoting.c++" << endl;
	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
