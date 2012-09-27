#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <stdio.h>
#include <string.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read int
    //
    void test_read_int1 () {
        std::istringstream r("5");
        int i;
        const bool b = voting_read_int(r,i );
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5);}

    void test_read_int2 () {
        std::istringstream r("376");
        int i ;
        const bool b = voting_read_int(r,i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==  376);}
   
    void test_read_int3 () {
        std::istringstream r("");
        int i;
        const bool b = voting_read_int(r,i );
        CPPUNIT_ASSERT(b == false);}
    //-----
    //read name
    //-----

    void test_read_name1 (){
        std::istringstream r("Jake Tenberg");
        char l[80];
        const bool b = voting_read_runner(r,l);
	CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(strcmp(l,"Jake Tenberg")==0);
    }

    void test_read_name2 (){
        std::istringstream r("JakeTenberg");
        char l[80];
        const bool b = voting_read_runner(r,l);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(strcmp(l,"JakeTenberg")==0);
    }

    void test_read_name3 (){
        std::istringstream r("Jake Tenberg 123475");
        char l[80];
        const bool b = voting_read_runner(r,l);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(strcmp(l,"Jake Tenberg 123475")==0);
    }

    //-----
    //read ballot
    //
    void test_read_ballot1 (){
        std::istringstream r("1 2 3 4");
        unsigned long long ballot[4];
        const bool b = voting_read_ballot(r,4,ballot);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballot[0] == 1);
        CPPUNIT_ASSERT(ballot[1] == 2);
        CPPUNIT_ASSERT(ballot[2] == 3);
        CPPUNIT_ASSERT(ballot[3] == 4);
    }

    void test_read_ballot2 (){
        std::istringstream r("1 2 3 4 5 6 7 8");
        unsigned long long ballot[8];
        const bool b = voting_read_ballot(r,8,ballot);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballot[0] == 1);
        CPPUNIT_ASSERT(ballot[1] == 2);
        CPPUNIT_ASSERT(ballot[2] == 3);
        CPPUNIT_ASSERT(ballot[3] == 4);
        CPPUNIT_ASSERT(ballot[4] == 5);
        CPPUNIT_ASSERT(ballot[5] == 6);
        CPPUNIT_ASSERT(ballot[6] == 7);
        CPPUNIT_ASSERT(ballot[7] == 8);
    }

    void test_read_ballot3 (){
        std::istringstream r("1 2");
        unsigned long long ballot[2];
        const bool b = voting_read_ballot(r,2,ballot);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(ballot[0] == 1);
        CPPUNIT_ASSERT(ballot[1] == 2);
    }

    //-------
    // load small ballot tests
    // ------
    void test_load_small_ballot1 (){
        smallBallot myBallot;
        unsigned long long ranks[5] = {1,2,3,4,5};
        const bool b = load_small_ballot(ranks,myBallot,5);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.ballot == 274960);
    }

    void test_load_small_ballot2 (){
        smallBallot myBallot;
        unsigned long long a = 4886718345LL;
        unsigned long long ranks[10] = {10,9,8,7,6,5,4,3,2,1};
        const bool b = load_small_ballot(ranks,myBallot,10);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.ballot == a);
    }

    void test_load_small_ballot3 (){
        smallBallot myBallot;
        unsigned long long a = 1070935975390360080LL;
        unsigned long long ranks[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        const bool b = load_small_ballot(ranks,myBallot,15);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.ballot == a);
    }

    void test_load_small_ballot4 (){
        smallBallot myBallot;
        unsigned long long a = 18364758544493064720LL;
        unsigned long long ranks[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        const bool b = load_small_ballot(ranks,myBallot,16);
        
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.ballot == a);
    }


    //------
    //load big ballots
    //------

    void test_load_big_ballot1 () {
        bigBallot myBallot;
        unsigned long long ranks[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        const bool b = load_big_ballot(ranks,myBallot,16);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.bottomBallot == 407901468851537952LL);
        CPPUNIT_ASSERT(myBallot.topBallot == 0);
        CPPUNIT_ASSERT(myBallot.middleBallot == 506284LL);
    }


    void test_load_big_ballot2 () {
        bigBallot myBallot;
        unsigned long long ranks[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        const bool b = load_big_ballot(ranks,myBallot,20);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.bottomBallot == 407901468851537952LL);
        CPPUNIT_ASSERT(myBallot.middleBallot == 587708844LL);
        CPPUNIT_ASSERT(myBallot.topBallot == 626LL);
    }

    void test_load_big_ballot3 () {
        bigBallot myBallot;
        unsigned long long ranks[19] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
        const bool b = load_big_ballot(ranks,myBallot,19);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(myBallot.bottomBallot == 407901468851537952LL);
        CPPUNIT_ASSERT(myBallot.middleBallot == 587708844LL);
        CPPUNIT_ASSERT(myBallot.topBallot == 18LL);
    }


    void test_peek_top_vote1 () {
        smallBallot myBallot1;
        bigBallot myBallot2;
        unsigned long long ranks[1] = {1};
        load_big_ballot(ranks,myBallot2,1);
        load_small_ballot(ranks,myBallot1,1);
        int i,j;
        const bool b1 = peek_top_small_vote(i,myBallot1);
        const bool b2 = peek_top_big_vote(j, myBallot2);
        CPPUNIT_ASSERT(b1 == true);
        CPPUNIT_ASSERT(b2 == true);
        CPPUNIT_ASSERT(i == 0);
        CPPUNIT_ASSERT(j == 0);
    }

    void test_peek_top_vote2 () {
        smallBallot myBallot1;
        bigBallot myBallot2;
        unsigned long long ranks[7] = {6,5,4,1,2,3,7};
        load_big_ballot(ranks,myBallot2,7);
        load_small_ballot(ranks,myBallot1,7);
        int i,j;
        const bool b1 = peek_top_small_vote(i,myBallot1);
        const bool b2 = peek_top_big_vote(j, myBallot2);
        CPPUNIT_ASSERT(b1 == true);
        CPPUNIT_ASSERT(b2 == true);
        CPPUNIT_ASSERT(i == 5);
        CPPUNIT_ASSERT(j == 5);
    }

    void test_peek_top_vote3 () {
        smallBallot myBallot1;
        bigBallot myBallot2;
        unsigned long long ranks[15] = {9,1,2,3,4,5,6,7,8,10,11,12,13,14,15};
        load_big_ballot(ranks,myBallot2,15);
        load_small_ballot(ranks,myBallot1,15);
        int i,j;
        const bool b1 = peek_top_small_vote(i,myBallot1);
        const bool b2 = peek_top_big_vote(j,myBallot2);
        CPPUNIT_ASSERT(b1 == true);
        CPPUNIT_ASSERT(b2 == true);
        CPPUNIT_ASSERT(i == 8);
        CPPUNIT_ASSERT(j == 8);
    }
    
    //DISCARD VOTES
    
    void test_discard_top1(){
    	smallBallot myBallot1;
    	bigBallot myBallot2;
    	unsigned long long ranks[10] = {1,2,3,4,5,6,7,8,9,10};
    	load_big_ballot(ranks,myBallot2,10);
    	load_small_ballot(ranks,myBallot1,10);
    	int i,j;
    	const bool b1 = discard_top_small_vote(myBallot1);
    	const bool b2 = discard_top_big_vote(myBallot2);
    	peek_top_small_vote(i,myBallot1);
    	peek_top_big_vote(j,myBallot2);
    	CPPUNIT_ASSERT(b1 == true);
    	CPPUNIT_ASSERT(b2 == true);
    	CPPUNIT_ASSERT(i == 1);
    	CPPUNIT_ASSERT(j == 1);   	
    }
    
    void test_discard_top2(){
    	smallBallot myBallot1;
    	bigBallot myBallot2;
    	unsigned long long ranks[11] = {7,2,3,4,5,6,4,8,9,10,11};
    	load_big_ballot(ranks,myBallot2,11);
    	load_small_ballot(ranks,myBallot1,11);
    	int i,j;
    	const bool b1 = discard_top_small_vote(myBallot1);
    	const bool b2 = discard_top_big_vote(myBallot2);
    	peek_top_small_vote(i,myBallot1);
    	peek_top_big_vote(j,myBallot2);
    	CPPUNIT_ASSERT(b1 == true);
    	CPPUNIT_ASSERT(b2 == true);
    	CPPUNIT_ASSERT(i == 1);
    	CPPUNIT_ASSERT(j == 1);   	
    }
    
    void test_discard_top3(){
    	smallBallot myBallot1;
    	bigBallot myBallot2;
    	unsigned long long ranks[3] = {3,2,1};
    	load_big_ballot(ranks,myBallot2,10);
    	load_small_ballot(ranks,myBallot1,15);
    	int i,j;
    	const bool b1 = discard_top_small_vote(myBallot1);
    	const bool b2 = discard_top_big_vote(myBallot2);
    	peek_top_small_vote(i,myBallot1);
    	peek_top_big_vote(j,myBallot2);
    	CPPUNIT_ASSERT(b1 == true);
    	CPPUNIT_ASSERT(b2 == true);
    	CPPUNIT_ASSERT(i == 1);
    	CPPUNIT_ASSERT(j == 1);   	
    }
    
    //eval
    
    void test_read_eval1(){
    	 std::istringstream r("2\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n3 2 1\n\n2\nA\nB\n");
    	 std::ostringstream w;
    	 read_eval(r, w);
    	 CPPUNIT_ASSERT(w.str() == "A\n\nA\nB\n");
    }
    
    void test_read_eval2(){
         std::istringstream r("3\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n3 2 1\n\n2\nA\nB\n\n2\nA\nB\n1 2\n");
         std::ostringstream w;
         read_eval(r, w);
         CPPUNIT_ASSERT(w.str() == "A\n\nA\nB\n\nA\n");
    }
    
    void test_read_eval3(){
         std::istringstream r("3\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n3 2 1\n\n2\nA\nB\n\n1\nA\n1\n1\n");
         std::ostringstream w;
         read_eval(r, w);
         CPPUNIT_ASSERT(w.str() == "A\n\nA\nB\n\nA\n");
    }  
    // ----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_int1);
    CPPUNIT_TEST(test_read_int2);
    CPPUNIT_TEST(test_read_int3);
    CPPUNIT_TEST(test_read_name1);
    CPPUNIT_TEST(test_read_name2);
    CPPUNIT_TEST(test_read_name3);
    CPPUNIT_TEST(test_read_ballot1);
    CPPUNIT_TEST(test_read_ballot2);
    CPPUNIT_TEST(test_read_ballot3);
    CPPUNIT_TEST(test_load_small_ballot1);
    CPPUNIT_TEST(test_load_small_ballot2);
    CPPUNIT_TEST(test_load_small_ballot3);
    CPPUNIT_TEST(test_load_small_ballot4);
    CPPUNIT_TEST(test_load_big_ballot1);
    CPPUNIT_TEST(test_load_big_ballot2);
    CPPUNIT_TEST(test_load_big_ballot3);
    CPPUNIT_TEST(test_peek_top_vote1);
    CPPUNIT_TEST(test_peek_top_vote2);
    CPPUNIT_TEST(test_peek_top_vote3);
    CPPUNIT_TEST(test_discard_top1);
    CPPUNIT_TEST(test_discard_top2);
    CPPUNIT_TEST(test_discard_top3);
    CPPUNIT_TEST(test_read_eval1);
    CPPUNIT_TEST(test_read_eval2);
    CPPUNIT_TEST(test_read_eval3);
    CPPUNIT_TEST_SUITE_END();};


int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
