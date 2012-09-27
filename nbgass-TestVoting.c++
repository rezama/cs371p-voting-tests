/*
 To test the program:
 % ls /usr/include/cppunit/
 ...
 HelperMacros.h
 ...
 % locate libcppunit.a
 /usr/lib/libcppunit.a
 % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
 % valgrind TestVoting.c++.app >& TestVoting.out
 */

// --------
// includes
// --------
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <queue>
#include <map>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner
#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting: CppUnit::TestFixture {

	// -----
	// clearWinner
	// -----

	void test_clearWinner_1() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 10.0;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_clearWinner(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 3);
	}

	void test_clearWinner_2() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 1.0;
		ballot emptyBallot;

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_clearWinner(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 20);
	}

	void test_clearWinner_3() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 3.0;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_clearWinner(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 0);
	}

	// -----
	// clearWinner
	// -----

	void test_deadLockedCandidates_1() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_deadLockedCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 3);
		CPPUNIT_ASSERT(result.front() == 2);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 3);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 20);
		result.pop();
	}

	void test_deadLockedCandidates_2() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_deadLockedCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 20);
	}

	void test_deadLockedCandidates_3() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_deadLockedCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 0);
	}

	// -----
	// clearWinner
	// -----

	void test_getLowestCandidates_1() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_getLowestCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 3);
		CPPUNIT_ASSERT(result.front() == 2);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 3);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 20);
		result.pop();
	}

	void test_getLowestCandidates_2() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_getLowestCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 20);
	}

	void test_getLowestCandidates_3() {
		ballotWarehouse currentBallotWarehouse;
		ballot emptyBallot;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(emptyBallot);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(emptyBallot);
		box3.containedBallots.push(emptyBallot);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(emptyBallot);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		std::queue<int> result = voting_getLowestCandidates(
				currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 2);
		CPPUNIT_ASSERT(result.front() == 2);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 20);
		result.pop();
	}

	// -----
	// removeCandidate
	// -----

	void test_removeCandidate_1() {
		ballotWarehouse currentBallotWarehouse;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		voting_removeCandidate(currentBallotWarehouse, 3);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[2].containedBallots.size() == 8);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[3].containedBallots.size() == 0);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[20].containedBallots.size() == 4);
	}

	void test_removeCandidate_2() {
		ballotWarehouse currentBallotWarehouse;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		voting_removeCandidate(currentBallotWarehouse, 20);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[2].containedBallots.size() == 4);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[3].containedBallots.size() == 8);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[20].containedBallots.size() == 0);
	}

	void test_removeCandidate_3() {
		ballotWarehouse currentBallotWarehouse;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;
		voting_removeCandidate(currentBallotWarehouse, 3);
		voting_removeCandidate(currentBallotWarehouse, 2);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[2].containedBallots.size() == 0);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[3].containedBallots.size() == 0);
		CPPUNIT_ASSERT(
				currentBallotWarehouse.ballotBoxes[20].containedBallots.size() == 12);
	}

	// -----
	// eval
	// -----

	void test_eval_1() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 7.0;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;

		std::queue<int> result = voting_eval(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 20);
		result.pop();
	}

	void test_eval_2() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 10.0;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;

		std::queue<int> result = voting_eval(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 1);
		CPPUNIT_ASSERT(result.front() == 2);
		result.pop();
	}

	void test_eval_3() {
		ballotWarehouse currentBallotWarehouse;
		currentBallotWarehouse.totalNumberVotes = 12.0;
		ballot ballotA;
		ballot ballotB;
		ballot ballotC;
		ballotA.voteOrder[0] = 2;
		ballotA.voteOrder[1] = 3;
		ballotA.voteOrder[2] = 20;
		ballotB.voteOrder[0] = 3;
		ballotB.voteOrder[1] = 2;
		ballotB.voteOrder[2] = 20;
		ballotC.voteOrder[0] = 20;
		ballotC.voteOrder[1] = 3;
		ballotC.voteOrder[2] = 2;
		ballotA.currentPosition = 0;
		ballotB.currentPosition = 0;
		ballotC.currentPosition = 0;

		ballotBox box2;
		box2.candidateNumber = 2;
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);
		box2.containedBallots.push(ballotA);

		ballotBox box3;
		box3.candidateNumber = 3;
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);
		box3.containedBallots.push(ballotB);

		ballotBox box20;
		box20.candidateNumber = 20;
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);
		box20.containedBallots.push(ballotC);

		currentBallotWarehouse.ballotBoxes[2] = box2;
		currentBallotWarehouse.ballotBoxes[3] = box3;
		currentBallotWarehouse.ballotBoxes[20] = box20;

		std::queue<int> result = voting_eval(currentBallotWarehouse);
		CPPUNIT_ASSERT(result.size() == 3);
		CPPUNIT_ASSERT(result.front() == 2);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 3);
		result.pop();
		CPPUNIT_ASSERT(result.front() == 20);
		result.pop();
	}

	// -----
	// print
	// -----

	void test_print_1() {
		std::ostringstream w;
		std::queue<int> numberQueue;
		std::map<int, std::string> nameMap;
		nameMap[1] = "Billy Bob";
		nameMap[2] = "John Joel";
		nameMap[3] = "Phil Phoney";
		numberQueue.push(2);
		voting_print(w, numberQueue, nameMap);
		CPPUNIT_ASSERT(w.str() == "John Joel\n");
	}

	void test_print_2() {
		std::ostringstream w;
		std::queue<int> numberQueue;
		std::map<int, std::string> nameMap;
		nameMap[1] = "Billy Bob";
		nameMap[2] = "John Joel";
		nameMap[3] = "Phil Phoney";
		numberQueue.push(3);
		numberQueue.push(1);
		voting_print(w, numberQueue, nameMap);
		CPPUNIT_ASSERT(w.str() != "Billy Bob\nPhil Phoney\n");
		CPPUNIT_ASSERT(w.str() == "Phil Phoney\nBilly Bob\n");
	}

	void test_print_3() {
		std::ostringstream w;
		std::queue<int> numberQueue;
		std::map<int, std::string> nameMap;
		nameMap[1] = "Billy Bob";
		nameMap[2] = "John Joel";
		nameMap[3] = "Phil Phoney";
		numberQueue.push(1);
		numberQueue.push(2);
		numberQueue.push(3);
		voting_print(w, numberQueue, nameMap);
		CPPUNIT_ASSERT(w.str() == "Billy Bob\nJohn Joel\nPhil Phoney\n");
	}

	void test_read_1() {
		std::istringstream w(
				"2\n\n2\nPhil\nBilly\n1 2\n2 1\n1 2\n\n1\nWally\n1\n1\n1\n1\n\n");
		std::queue<ballotWarehouse> result = voting_read(w);

		CPPUNIT_ASSERT(result.size() == 2);
		ballotWarehouse w1 = result.front();
		result.pop();
		ballotWarehouse w2 = result.front();
		CPPUNIT_ASSERT(w1.ballotBoxes[1].containedBallots.size() == 2);
		CPPUNIT_ASSERT(w1.ballotBoxes[2].containedBallots.size() == 1);
		CPPUNIT_ASSERT(w2.ballotBoxes[1].containedBallots.size() == 4);
		
		CPPUNIT_ASSERT(w1.ballotBoxes[1].containedBallots.front().voteOrder[0] == 1);
		CPPUNIT_ASSERT(w1.ballotBoxes[1].containedBallots.front().voteOrder[1] == 2);
	}

	void test_read_2() {
		std::istringstream w(
				"3\n\n1\nPhil\n1\n\n1\nBilly\n1\n\n1\nWally\n1\n1\n1\n\n\n1\n");
		std::queue<ballotWarehouse> result = voting_read(w);

		CPPUNIT_ASSERT(result.size() == 3);
		result.pop();
		result.pop();
		ballotWarehouse w3 = result.front();
		CPPUNIT_ASSERT(w3.ballotBoxes[1].containedBallots.size() == 3);
		
		CPPUNIT_ASSERT(w3.ballotBoxes[1].containedBallots.front().voteOrder[0] == 1);
	}

	void test_read_3() {
		std::istringstream w(
				"2\n\n2\nPhil\nThomas\n1 2\n\n1\nBilly\n1\n");
		std::queue<ballotWarehouse> result = voting_read(w);

		CPPUNIT_ASSERT(result.size() == 2);
		
		ballotWarehouse w1 = result.front();
		result.pop();
		ballotWarehouse w2 = result.front();
		result.pop();
		
		CPPUNIT_ASSERT(w1.candidateNameMap[1].compare("Phil") == 0);
		CPPUNIT_ASSERT(w1.candidateNameMap[2].compare("Thomas") == 0);
		CPPUNIT_ASSERT(w2.candidateNameMap[1].compare("Billy") == 0);
	}

	void test_solve_1() {
		std::istringstream r(
				"1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "John Doe\n");
	}

	void test_solve_2() {
		std::istringstream r(
				"2\n\n3\nPhil\nBilly\nTim\n1 2 3\n3 2 1\n3 1 2\n3 1 2\n\n1\nWally\n1\n1\n\1n\n1\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Tim\n\nWally\n");	
	}

	void test_solve_3() {
		std::istringstream r(
				"2\n\n3\nPhil\nBilly\nTim\n3 2 1\n2 3 1\n1 2 3\n\n1\nWally\n1\n1\n\1n\n1\n");
		std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Phil\nBilly\nTim\n\nWally\n");	
	}

	// -----
	// suite
	// -----

CPPUNIT_TEST_SUITE(TestVoting);
		// print tests
		CPPUNIT_TEST(test_print_1);
		CPPUNIT_TEST(test_print_2);
		CPPUNIT_TEST(test_print_3);
		// clearWinner tests
		CPPUNIT_TEST(test_clearWinner_1);
		CPPUNIT_TEST(test_clearWinner_2);
		CPPUNIT_TEST(test_clearWinner_3);
		// deadLockedCandidates tests
		CPPUNIT_TEST(test_deadLockedCandidates_1);
		CPPUNIT_TEST(test_deadLockedCandidates_2);
		CPPUNIT_TEST(test_deadLockedCandidates_3);
		// getLowestCandidates tests
		CPPUNIT_TEST(test_getLowestCandidates_1);
		CPPUNIT_TEST(test_getLowestCandidates_2);
		CPPUNIT_TEST(test_getLowestCandidates_3);
		// removeCandidate tests
		CPPUNIT_TEST(test_removeCandidate_1);
		CPPUNIT_TEST(test_removeCandidate_2);
		CPPUNIT_TEST(test_removeCandidate_3);
		// eval tests
		CPPUNIT_TEST(test_eval_1);
		CPPUNIT_TEST(test_eval_2);
		CPPUNIT_TEST(test_eval_3);
		// read tests
		CPPUNIT_TEST(test_read_1);
		CPPUNIT_TEST(test_read_2);
		CPPUNIT_TEST(test_read_3);
		// solve tests
		CPPUNIT_TEST(test_solve_1);
		CPPUNIT_TEST(test_solve_2);
		CPPUNIT_TEST(test_solve_3);
		// end test suite
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

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
