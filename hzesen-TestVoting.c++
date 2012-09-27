// --------------------------------
// projects/collatz/TestVoting.c++
// Copyright (C) 2012
// Glenn P. Downing
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"
using namespace std;

// -----------
// TestVoting
// -----------




istringstream f("1 2 3 4 5");
istringstream f2("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
istringstream f3("");
Ballot b(f);
Ballot b2(f2);
Ballot b3(f3);
Candidate cand = Candidate("Michael Jordan");
Candidate cand2 = Candidate("Zesen Huang");
Candidate cand3 = Candidate("");

struct TestVoting : CppUnit::TestFixture {
    // --------------
    // Test Candidate
    // --------------


    void test_getName1 () {
        CPPUNIT_ASSERT(cand.getName() == "Michael Jordan");}

    void test_getName2 () {
        CPPUNIT_ASSERT(cand2.getName() == "Zesen Huang");}

    void test_getName3 () {
        CPPUNIT_ASSERT(cand3.getName() == "");}

    void test_setVote1 () {
        cand.setVote(100);
        CPPUNIT_ASSERT(cand.getVotes() == 100);}

    void test_setVote2 () {
        cand2.setVote(0);
        CPPUNIT_ASSERT(cand2.getVotes() == 0);}

    void test_setVote3 () {
        cand3.setVote(9000000);
        CPPUNIT_ASSERT(cand3.getVotes() == 9000000);}

    void test_addOneVote1 () {
        cand.addOneVote();
        CPPUNIT_ASSERT(cand.getVotes() == 101);}

    void test_addOneVote2 () {
        cand2.addOneVote();
        CPPUNIT_ASSERT(cand2.getVotes() == 1);}

    void test_addOneVote3 () {
        cand3.addOneVote();
        CPPUNIT_ASSERT(cand3.getVotes() == 9000001);}

    // -----------
    // Test Ballot
    // -----------

    void test_getList1 () {
		list<int> l;
		l = b.getList();
		for (int i = 1; i <= 5; i++) {
			CPPUNIT_ASSERT(l.front() == i);
			l.pop_front();	
		};}

    void test_getList2 () {
		list<int> l;
		l = b2.getList();
		for (int i = 1; i <= 20; i++) {
			CPPUNIT_ASSERT(l.front() == i);
			l.pop_front();	
		};}

    void test_getList3 () {
		list<int> l;
		l = b3.getList();
		CPPUNIT_ASSERT(l.size() == 0);;}
	
 
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_getName1);
    CPPUNIT_TEST(test_getName2);
    CPPUNIT_TEST(test_getName3);
    CPPUNIT_TEST(test_setVote1);
    CPPUNIT_TEST(test_setVote2);
    CPPUNIT_TEST(test_setVote3);
    CPPUNIT_TEST(test_addOneVote1);
    CPPUNIT_TEST(test_addOneVote2);
    CPPUNIT_TEST(test_addOneVote3);
    CPPUNIT_TEST(test_getList1);
    CPPUNIT_TEST(test_getList2);
    CPPUNIT_TEST(test_getList3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
