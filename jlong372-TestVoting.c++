//g++ -lcppunit -wall TestVoting.c++ -o TestVoting.c++.app
//
#include <iostream> 
#include <sstream>  
#include <string>   
#include <vector>

#include "cppunit/extensions/HelperMacros.h" 
#include "cppunit/TestFixture.h"             
#include "cppunit/TextTestRunner.h"          

#include "Voting.h"
using namespace std;

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void testReadCandidateName ()
     {
        istringstream r("freddy");
        string str = string();
        const bool b = votingRead(r, str);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(str == "freddy");
    }
    
    void testReadCandidateNameWithWhitSpace ()
     {
        istringstream r("freddy Rumsen\n");
        string str = string();
        const bool b = votingRead(r, str);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(str == "freddy Rumsen");
    }
    
    void testReadBlankLine ()
     {
        istringstream r("");
        string str = string();
        const bool b = votingRead(r, str);
//        cout<<str<<endl;
        CPPUNIT_ASSERT(b == false);
        CPPUNIT_ASSERT(str == "");
    }
    
    // -----------------------------
    // votingPrint
    // -----------------------------
    
    void testPrintEmpty()
    {
        ostringstream writer;
        votingPrint(writer, "");
        CPPUNIT_ASSERT(writer.str() == "\n");
    }
    
    void testPrintNotEmpty()
    {
        ostringstream writer;
        votingPrint(writer, "Mississippi");
        CPPUNIT_ASSERT(writer.str() == "Mississippi\n");
    }
    
    void testPrintTwoWords()
    {
        ostringstream writer;
        votingPrint(writer, "Freddy Crugar");
        CPPUNIT_ASSERT(writer.str() == "Freddy Crugar\n");
    }
    // -----------------------------
    //countVotesDetermineLosers tests
    // -----------------------------
    void testCountVotesDetermineLosers()
    {
    	vector<string> loser;
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
  
    	vector<string> notLoserOne;
        notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
        
        vector<string>notLoserTwo;
        notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(notLoserOne);
    	votes.push_back(loser);
    	votes.push_back(notLoserTwo);
    	
    	vector<int> answer = votingCountVotesDetermineLosers(votes);
    	
    	CPPUNIT_ASSERT((int)answer.size() == 1);
    	CPPUNIT_ASSERT(answer[0] == 1);
    }
    
    
    void testCountVotesDetermineLosersZeroVotes()
    {
    	vector<string> loser;
  
    	vector<string> notLoserOne;
        notLoserOne.push_back("1 2 3 4");
        
        vector<string>notLoserTwo;
        notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(notLoserOne);
    	votes.push_back(loser);
    	votes.push_back(notLoserTwo);
    	
    	vector<int> answer = votingCountVotesDetermineLosers(votes);
    	
    	CPPUNIT_ASSERT((int)answer.size() == 1);
    	CPPUNIT_ASSERT(answer[0] == 0);
    }
    
    void testCountVotesDetermineLosersMultiples()
    {
    	vector<string> loser;
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
  
    	vector<string> notLoserOne;
        notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
        
        vector<string>notLoserTwo;
        notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(notLoserOne);
    	votes.push_back(loser);
    	votes.push_back(notLoserTwo);
    	
    	vector<int> answer = votingCountVotesDetermineLosers(votes);
    	
    	CPPUNIT_ASSERT((int)answer.size() == 2);
    	CPPUNIT_ASSERT(answer[0] == 0);
    	CPPUNIT_ASSERT(answer[1] == 1);
    }
    
    void testCountVotesDetermineLosersAll()
    {
    	vector<string> loser;
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
  
    	vector<string> notLoserOne;
        notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
    	notLoserOne.push_back("1 2 3 4");
        
        vector<string>notLoserTwo;
        notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
    	notLoserTwo.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(notLoserOne);
    	votes.push_back(loser);
    	votes.push_back(notLoserTwo);
    	
    	vector<int> answer = votingCountVotesDetermineLosers(votes);
    	
    	CPPUNIT_ASSERT((int)answer.size() == 3);
    	CPPUNIT_ASSERT(answer[0] == 0);
    	CPPUNIT_ASSERT(answer[1] == 1);
    	CPPUNIT_ASSERT(answer[2] == 2);
    }
    // -----------------------------
    //countVotesDetermineWinners tests
    // -----------------------------
    void testCountVotesDetermineWinners()
    {
    	vector<string> loser;
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
  
    	vector<string> loserOne;
        loserOne.push_back("1 2 3 4");
    	loserOne.push_back("1 2 3 4");
    	loserOne.push_back("1 2 3 4");
        
        vector<string>winner;
        winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(loserOne);
    	votes.push_back(loser);
    	votes.push_back(winner);
    	
    	int answer = votingCountVotesDetermineWinners(votes, 13);
    	
    	CPPUNIT_ASSERT(answer == 2);
    	
    }
    
    void testCountVotesDetermineWinnersNone()
    {
    	vector<string> loser;
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
    	loser.push_back("1 2 3 4");
  
    	vector<string> loserOne;
        loserOne.push_back("1 2 3 4");
    	loserOne.push_back("1 2 3 4");
    	loserOne.push_back("1 2 3 4");
        
        vector<string>winner;
        winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
    	winner.push_back("1 2 3 4");
        
    	vector<vector<string> > votes;
    	votes.push_back(loserOne);
    	votes.push_back(loser);
    	votes.push_back(winner);
    	
    	int answer = votingCountVotesDetermineWinners(votes, 12);
    	
    	CPPUNIT_ASSERT(answer == -1);
    	
    }
    
        void testCountVotesDetermineWinnersNoVotes()
    {
    	vector<vector<string> > votes;
    	
    	int answer = votingCountVotesDetermineWinners(votes, 0);
    	
    	CPPUNIT_ASSERT(answer == -1);
    	
    }
    // -----------------------------
    //DataInsert tests
    // -----------------------------
	void testDataInsert()
	{
	    istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
	    vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JaneSmith.push_back("2 1 3");
	    JaneSmith.push_back("2 3 1");
	    Sirhan.push_back("3 1 2");
		string names[3];
	    vector<vector<string> > result = dataInsert(r,names);
		
	    CPPUNIT_ASSERT(result.at(0) == JohnDoe);
	    CPPUNIT_ASSERT(result.at(1) == JaneSmith);
	    CPPUNIT_ASSERT(result.at(2) == Sirhan);
		CPPUNIT_ASSERT(names[0] == "John Doe");
		CPPUNIT_ASSERT(names[1] == "Jane Smith");
		CPPUNIT_ASSERT(names[2] == "Sirhan Sirhan");
		
	}

	void testDataInsertOneCandidate()
	{
	    istringstream r("1\nJohn Doe\n1 3 2");
	    vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 3 2");
	  	string names[1];
	    vector<vector<string> > result = dataInsert(r,names);
		
	    CPPUNIT_ASSERT(result.at(0) == JohnDoe);
		CPPUNIT_ASSERT(names[0] == "John Doe");
		
	}

	void testDataInsertTwentyCandidates()
	{
	    istringstream r("10\nJohn Doe1\nJohn Doe2\nJohn Doe3\nJohn Doe4\nJohn Doe5\nJohn Doe6\nJohn Doe7\nJohn Doe8\nJohn Doe9\nJohn Doe10\n1 2 3 4 5 6\n2 3 4 5\n3 4 5 6");
	    vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		string names[10];
	    vector<vector<string> > result = dataInsert(r,names);

	    CPPUNIT_ASSERT(result.at(0) == JohnDoe);
	    CPPUNIT_ASSERT(result.at(1) == JaneSmith);
	    CPPUNIT_ASSERT(result.at(2) == Sirhan);

		CPPUNIT_ASSERT(names[0] == "John Doe1");
		CPPUNIT_ASSERT(names[1] == "John Doe2");
		CPPUNIT_ASSERT(names[2] == "John Doe3");
		CPPUNIT_ASSERT(names[3] == "John Doe4");
		CPPUNIT_ASSERT(names[4] == "John Doe5");
		CPPUNIT_ASSERT(names[5] == "John Doe6");
		CPPUNIT_ASSERT(names[6] == "John Doe7");
		CPPUNIT_ASSERT(names[7] == "John Doe8");
		CPPUNIT_ASSERT(names[8] == "John Doe9");
		CPPUNIT_ASSERT(names[9] == "John Doe10");
		
	}
    // -----------------------------
    //numberOfBallots tests
    // -----------------------------
	void testNumberOfBallots()
	{
		int i;
		
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		i = numberOfBallots(result);
		
		CPPUNIT_ASSERT(i == 3);

	}
	void testNumberOfBallotsTen()
	{
		int i;
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		i = numberOfBallots(result);
		
		CPPUNIT_ASSERT(i == 10);
	}
	void testNumberOfBallotsZero()
	{
		int i;
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		i = numberOfBallots(result);
		
		CPPUNIT_ASSERT(i == 0);	
	}
	// -----------------------------
    //isEveryoneTied tests
    // -----------------------------
	void testIsEveryoneTiedFalse()
	{
		bool i;
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		Sirhan.push_back("3 4 5 6");
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		i = isEveryoneTied(result);
		
		CPPUNIT_ASSERT(i == false);
	}
	
	void testIsEveryoneTiedTrue()
	{
		bool i;
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");

		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		i = isEveryoneTied(result);
		
		CPPUNIT_ASSERT(i);
	}
	
	void testIsEveryoneTiedTrueLots()
	{
		bool i;
		vector<vector<string> > result;
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JohnDoe.push_back("1 2 3 4 5 6");
	    JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");
		JaneSmith.push_back("2 3 4 5");
		Sirhan.push_back("3 4 5 6");

		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		i = isEveryoneTied(result);
		
		CPPUNIT_ASSERT(i);
	}
    // -----------------------------
    //redistribution tests
	// -----------------------------
	void testRedistributeVotes()
	{
		vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    
	    JaneSmith.push_back("2 1 3");
	    
		Sirhan.push_back("3 1 2");
		Sirhan.push_back("3 2 1");
		Sirhan.push_back("3 1 2");
		Sirhan.push_back("3 2 1");

		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		redistributeVotes(result);
		
		CPPUNIT_ASSERT(result.at(0).size() == 11);
		CPPUNIT_ASSERT(result.at(1).size() == 0);
		CPPUNIT_ASSERT(result.at(2).size() == 4);
		
	}
	
	void testRedistributeVotesTwoLosers()
	{
		vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    
	    JaneSmith.push_back("2 1 3");
	    
		Sirhan.push_back("3 1 2");

		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		redistributeVotes(result);
		
		CPPUNIT_ASSERT(result.at(0).size() == 12);
		CPPUNIT_ASSERT(result.at(1).size() == 0);
		CPPUNIT_ASSERT(result.at(2).size() == 0);
		
	}
	
	void testRedistributeVotesOneLoserOneEliminated()
	{
		vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    
	    
		Sirhan.push_back("3 1 2");

		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
		
		redistributeVotes(result);
		
		CPPUNIT_ASSERT(result.at(0).size() == 11);
		CPPUNIT_ASSERT(result.at(1).size() == 0);
		CPPUNIT_ASSERT(result.at(2).size() == 0);
		
	}
    // -----------------------------
    // splitStringOnSpace
    // -----------------------------
    
    void testSplitStringOnSpace()
    {
        vector<string> result;
        result = splitStringOnSpace("1 2 3 4");
        
        CPPUNIT_ASSERT(result.at(0) == "1");
        CPPUNIT_ASSERT(result.at(1) == "2");
        CPPUNIT_ASSERT(result.at(2) == "3");
        CPPUNIT_ASSERT(result.at(3) == "4");
    }
    
    void testSplitStringOnEndInSpace()
    {
        vector<string> result;
        result = splitStringOnSpace("1 2 3 4 ");
        
        CPPUNIT_ASSERT(result.at(0) == "1");
        CPPUNIT_ASSERT(result.at(1) == "2");
        CPPUNIT_ASSERT(result.at(2) == "3");
        CPPUNIT_ASSERT(result.at(3) == "4");
    }
    
    void testSplitStringOnDoubleDigits()
    {
        vector<string> result;
        result = splitStringOnSpace("11 12 13 14");
        
        CPPUNIT_ASSERT(result.at(0) == "11");
        CPPUNIT_ASSERT(result.at(1) == "12");
        CPPUNIT_ASSERT(result.at(2) == "13");
        CPPUNIT_ASSERT(result.at(3) == "14");
    }
    
    void testSplitStringOnSinglesAndDoubleDigits()
    {
        vector<string> result;
        result = splitStringOnSpace("11 12 13 14 1 2 3");
        
        CPPUNIT_ASSERT(result.at(0) == "11");
        CPPUNIT_ASSERT(result.at(1) == "12");
        CPPUNIT_ASSERT(result.at(2) == "13");
        CPPUNIT_ASSERT(result.at(3) == "14");
        CPPUNIT_ASSERT(result.at(4) == "1");
        CPPUNIT_ASSERT(result.at(5) == "2");
        CPPUNIT_ASSERT(result.at(6) == "3");
    }
    // -----------------------------
    // getMaxCandidates
    // -----------------------------
    
    void testGetMaxCandidatesSingle()
    {
        vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    
	    JaneSmith.push_back("2 1 3");
	    
		Sirhan.push_back("3 1 2");
        
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
        
        vector<int> answer;
        answer = getMaxCandidates(result);
        CPPUNIT_ASSERT(answer.at(0) == 0);
    }
    
    void testGetMaxCandidatesEveryone()
    {
        vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    
	    JaneSmith.push_back("2 1 3");
	    
		Sirhan.push_back("3 1 2");
        
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
        
        vector<int> answer;
        answer = getMaxCandidates(result);
        CPPUNIT_ASSERT(answer.at(0) == 0);
        CPPUNIT_ASSERT(answer.at(1) == 1);
        CPPUNIT_ASSERT(answer.at(2) == 2);
    }
    
    void testGetMaxCandidatesTwoVotes()
    {
        vector<vector<string> > result;
		
		vector<string> JohnDoe;
	    vector<string> JaneSmith;
	    vector<string> Sirhan;
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    JohnDoe.push_back("1 2 3");
	    
	    JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        JaneSmith.push_back("2 1 3");
        
	    
		Sirhan.push_back("3 1 2");
        
		
		result.push_back(JohnDoe);
		result.push_back(JaneSmith);
		result.push_back(Sirhan);
        vector<int> answer;
        answer = getMaxCandidates(result);
        
        CPPUNIT_ASSERT(answer.at(0) == 0);
        CPPUNIT_ASSERT(answer.at(1) == 1);
    }
    // -----------------------------
    // runVoting tests
    // -----------------------------
    
    void testRunVotingOneCase()
    {
        istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        ostringstream w;
        
        runVoting(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n");
        
        
    }
    
    void testRunVotingTwoCases()
    {
        istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n3 1 2\n");
        ostringstream w;
        
        runVoting(r, w);
        CPPUNIT_ASSERT(w.str() == "John Doe\n\nJohn Doe\nJane Smith\nSirhan Sirhan\n");
        
        
    }
    
    void testRunVotingGreaterThanTwelve()
    {
        istringstream r("1\n\n15\nFelton Aubin\nBruce Hodak\nYoshiko Marone\nLonnie Nock\nKandy Domenick\nCindi Shafer\nAlex Vanvliet\nMarquis Kunkle\nJoetta Pinero\nDarrel Philipps\nAurora Bond\nTyron Kernan\nSheri Salvas\nQuyen Armistead\nCathrine Kucera\n13 8 14 7 5 2 12 1 3 9 11 15 10 6 4\n4 6 9 2 12 14 1 8 5 3 7 10 15 11 13\n9 5 3 2 6 7 11 10 13 12 1 4 15 8 14\n10 15 9 2 1 12 3 14 8 5 6 7 4 13 11\n12 9 11 14 8 7 1 15 3 6 2 13 5 4 10\n13 2 14 3 7 10 1 5 4 15 6 11 8 12 9\n14 2 5 12 15 6 8 11 9 7 3 10 4 1 13");
        ostringstream w;
        
        runVoting(r, w);
        CPPUNIT_ASSERT(w.str() == "Sheri Salvas\n");
        
        
    }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    //read
    CPPUNIT_TEST(testReadCandidateName);
    CPPUNIT_TEST(testReadCandidateNameWithWhitSpace);
     CPPUNIT_TEST(testReadBlankLine);
    
    //print
    CPPUNIT_TEST(testPrintEmpty);
    CPPUNIT_TEST(testPrintNotEmpty);
    CPPUNIT_TEST(testPrintTwoWords);
     
     //determineLosers
    CPPUNIT_TEST(testCountVotesDetermineLosers);
    CPPUNIT_TEST(testCountVotesDetermineLosersMultiples);
    CPPUNIT_TEST(testCountVotesDetermineLosersAll);
    CPPUNIT_TEST(testCountVotesDetermineLosersZeroVotes);
    
    //determineWinner
    CPPUNIT_TEST(testCountVotesDetermineWinners);
    CPPUNIT_TEST(testCountVotesDetermineWinnersNone);
    CPPUNIT_TEST(testCountVotesDetermineWinnersNoVotes);
	
     
    //dataInsert
    CPPUNIT_TEST(testDataInsert);
	CPPUNIT_TEST(testDataInsertOneCandidate);
	CPPUNIT_TEST(testDataInsertTwentyCandidates);
	
	//numberOfBallots
	CPPUNIT_TEST(testNumberOfBallots);
	CPPUNIT_TEST(testNumberOfBallotsTen);
	CPPUNIT_TEST(testNumberOfBallotsZero);
	
	//isEveryoneTied
	CPPUNIT_TEST(testIsEveryoneTiedFalse);
	CPPUNIT_TEST(testIsEveryoneTiedTrue);
	CPPUNIT_TEST(testIsEveryoneTiedTrueLots);
	
	//redistributeTest
	CPPUNIT_TEST(testRedistributeVotes);
	CPPUNIT_TEST(testRedistributeVotesTwoLosers);
	CPPUNIT_TEST(testRedistributeVotesOneLoserOneEliminated);
    
    //splitOnString
    CPPUNIT_TEST(testSplitStringOnSpace);
    CPPUNIT_TEST(testSplitStringOnEndInSpace);
    CPPUNIT_TEST(testSplitStringOnDoubleDigits);
    CPPUNIT_TEST(testSplitStringOnSinglesAndDoubleDigits);
    
    //getMaxCandidates
    CPPUNIT_TEST(testGetMaxCandidatesSingle);
    CPPUNIT_TEST(testGetMaxCandidatesTwoVotes);
    CPPUNIT_TEST(testGetMaxCandidatesEveryone);
    
    //runVotingTest
    CPPUNIT_TEST(testRunVotingOneCase);
    CPPUNIT_TEST(testRunVotingTwoCases);
    CPPUNIT_TEST(testRunVotingGreaterThanTwelve);
	    
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
