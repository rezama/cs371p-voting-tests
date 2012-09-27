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
#include <string>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

/*

const int MAX_CHARS = 80;
const int MAX_CANDIDATES = 20;
const int MAX_BALLOTS = 1000;

*/

struct TestVoting : CppUnit::TestFixture 
{
    // --------
    // getCases
    // --------
    void test_getCases_1()
    {
	    std::istringstream r("1\n");
	    int i = getCases(r);
	    CPPUNIT_ASSERT_EQUAL(1, i);
    }
    void test_getCases_2()
    {
	    std::istringstream r("10\n");
	    int i = getCases(r);
	    CPPUNIT_ASSERT_EQUAL(10, i);
    }
    void test_getCases_3()
    {
	    std::istringstream r("1000000000\n");
	    int i = getCases(r);
	    CPPUNIT_ASSERT_EQUAL(1000000000, i);
    }

    // --------
    // getNames
    // --------
    void test_getNames_1()
    {
	    std::istringstream r("Ridwan Hoq\n");
	    int numCandidates = 1;
	    char names[MAX_CANDIDATES][MAX_CHARS];
	    getNames(r, names, numCandidates);
	    std::string expected[] = {"", "Ridwan Hoq"};
	    int i;
	    for (i = 1; i <= numCandidates; i++) {
		 
            CPPUNIT_ASSERT(names[i] == expected[i]);
	    }
    }
    void test_getNames_2()
    {
	    std::istringstream r("Ridwan Hoq\nGuy Hawkins\nBarack Obama\nSarah Palin\n");
	    int numCandidates = 4;
	    char names[MAX_CANDIDATES][MAX_CHARS];
	    getNames(r, names, numCandidates);
	    std::string expected[] = {"", "Ridwan Hoq", "Guy Hawkins", "Barack Obama", "Sarah Palin"};
	    int i;
	    for (i = 1; i <= numCandidates; i++) {

		    CPPUNIT_ASSERT(names[i] == expected[i]);
	    }
    }
    void test_getNames_3()
    {
	    std::istringstream r("EIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MAN\n");
	    int numCandidates = 1;
	    char names[MAX_CANDIDATES][MAX_CHARS];
	    getNames(r, names, numCandidates);
	    std::string expected[] = {"", "EIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MANEIGHTY MAN"};
	    int i;
	    for (i = 1; i <= numCandidates; i++) {

		    CPPUNIT_ASSERT(names[i] == expected[i]);
	    }
    }

    // ----------
    // getBallots
    // ----------
    void test_getBallots_1()
    {
	    std::istringstream r("1 2 3\n");
	    const int numBallots = 1;
	    const int numCandidates = 3;
	    int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	    CPPUNIT_ASSERT(numBallots == getBallots(r, ballots));
	    int expected[numBallots][numCandidates] = {{1, 2, 3}};
	    int i, j;
	    for (i = 0; i < numBallots; i++) {
		    for (j = 0; j < numCandidates; j++) {
			    //printf("%d\n", ballots[i][j]);
			    CPPUNIT_ASSERT(ballots[i][j] == expected[i][j]);
		    }
	    }
    }

    void test_getBallots_2()
    {
	    std::istringstream r("1 2 3\n2 3 1\n3 2 1\n");
	    const int numBallots = 3;
	    const int numCandidates = 3;
	    int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	    CPPUNIT_ASSERT(numBallots == getBallots(r, ballots));
	    int expected[numBallots][numCandidates] = {{1, 2, 3}, {2, 3, 1}, {3, 2, 1}};
	    int i, j;
	    for (i = 0; i < numBallots; i++) {
		    for (j = 0; j < numCandidates; j++) {
			    //printf("%d\n", ballots[i][j]);
			    CPPUNIT_ASSERT(ballots[i][j] == expected[i][j]);
		    }
	    }
    }

    void test_getBallots_3()
    {
	    std::istringstream r("6 3 1 2 4 5\n5 1 3 4 2 6\n6 2 4 3 1 5\n1 5 2 6 4 3\n2 6 3 4 1 5\n6 5 4 3 2 1\n");
	    const int numBallots = 6;
	    const int numCandidates = 6;
	    int ballots[MAX_BALLOTS][MAX_CANDIDATES];
	    CPPUNIT_ASSERT(numBallots == getBallots(r, ballots));
	    int expected[numBallots][numCandidates] = {
												    {6, 3, 1, 2, 4, 5}, 
												    {5, 1, 3, 4, 2, 6}, 
												    {6, 2, 4, 3, 1, 5}, 
												    {1, 5, 2, 6, 4, 3}, 
												    {2, 6, 3, 4, 1, 5}, 
												    {6, 5, 4, 3, 2, 1}};
	    int i, j;
	    for (i = 0; i < numBallots; i++) {
		    for (j = 0; j < numCandidates; j++) {
			    //printf("%d\n", ballots[i][j]);
			    CPPUNIT_ASSERT(ballots[i][j] == expected[i][j]);
		    }
	    }
    }

    // --------
    // getInput
    // --------
    void test_getInput_1()
    {
        std::istringstream r("3\nBiggie Smalls\nKanye West\nTupac Shakur\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");	    
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
	    int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        const int numCandidates = 3;
        const int numBallots = 5;
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(numArr[0] == numCandidates);
        CPPUNIT_ASSERT(numArr[1] == numBallots);
	    std::string expectedName[] = {"", "Biggie Smalls", "Kanye West", "Tupac Shakur"};
	    int expectedBallot[numBallots][numCandidates] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}};
	    int i, j, k;
	    for (k = 1; k <= numCandidates; k++) {
            //cout << "Expected: " << expectedName[k] << " Actual: " << candidateName[k] << endl; 
		    CPPUNIT_ASSERT(expectedName[k] == candidateName[k]);
	    }
	    for (i = 0; i < numBallots; i++) {
		    for (j = 0; j < numCandidates; j++) {
			    CPPUNIT_ASSERT(expectedBallot[i][j] == omegaBallot[i][j]);
		    }
	    }
    }
    void test_getInput_2()
    {
        std::istringstream r("1\nBangarang\n10\n10\n10\n");
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
        int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        const int numCandidates = 1;
        const int numBallots = 3;
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(numArr[0] == numCandidates);
        CPPUNIT_ASSERT(numArr[1] == numBallots);
        std::string expectedName[] = {"", "Bangarang"};
        int expectedBallot[numBallots][numCandidates] = {{10}, {10}, {10}};
        int i, j, k;
        for (k = 1; k <= numCandidates; k++) {
            //cout << "Expected: " << expectedName[k] << " Actual: " << candidateName[k] << endl; 
	        CPPUNIT_ASSERT(expectedName[k] == candidateName[k]);
        }
        for (i = 0; i < numBallots; i++) {
	        for (j = 0; j < numCandidates; j++) {
		        CPPUNIT_ASSERT(expectedBallot[i][j] == omegaBallot[i][j]);
	        }
        }

    }

    void test_getInput_3()
    {
        std::istringstream r(
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 1 3 4\n"
                        "2 3 1 4\n"
                        "1 2 3 4\n");
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
        int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        const int numCandidates = 4;
        const int numBallots = 4;
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(numArr[0] == numCandidates);
        CPPUNIT_ASSERT(numArr[1] == numBallots);
        std::string expectedName[] = {"", "Red", "Green", "Blue", "Orange"};
        int expectedBallot[numBallots][numCandidates] = {{1, 2, 3, 4}, {2, 1, 3, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}};
        int i, j, k;
        for (k = 1; k <= numCandidates; k++) {
            //cout << "Expected: " << expectedName[k] << " Actual: " << candidateName[k] << endl; 
	        CPPUNIT_ASSERT(expectedName[k] == candidateName[k]);
        }
        for (i = 0; i < numBallots; i++) {
	        for (j = 0; j < numCandidates; j++) {
		        CPPUNIT_ASSERT(expectedBallot[i][j] == omegaBallot[i][j]);
	        }
        }

    }

    void test_evalBallots_1()
    {
        std::istringstream r(
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 1 3 4\n"
                        "2 3 1 4\n"
                        "1 2 3 4\n");
        std::ostringstream w;
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
        int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        evalBallots(w, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\n");
    }

    void test_evalBallots_2()
    {
        istringstream r(
                        "4\n"
                        "Red\nGreen\nBlue\nOrange\n"
                        "1 2 3 4\n"
                        "2 1 3 4\n"
                        "2 3 1 4\n"
                        "3 4 1 2\n"
                        "4 3 2 1\n");
        std::ostringstream w;
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
        int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        evalBallots(w, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(w.str() == "Green\n");
    }

    void test_evalBallots_3()
    {
        istringstream r(
                        "4\n"
                        "George W. Bush\n"
                        "Al Gore\n"
                        "Ralph Nader\n"
                        "Ron Paul"
                        "Santa Claus\n"
                        "3 2 5 4 1\n");
        std::ostringstream w;
        char candidateName[MAX_CANDIDATES][MAX_CHARS];
        int omegaBallot[MAX_BALLOTS][MAX_CANDIDATES];
        int numArr[2];
        getInput(r, omegaBallot, candidateName, numArr);
        evalBallots(w, omegaBallot, candidateName, numArr);
        CPPUNIT_ASSERT(w.str() == "Ralph Nader\n");
    }


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_getCases_1);
    CPPUNIT_TEST(test_getCases_2);
    CPPUNIT_TEST(test_getCases_3);
    CPPUNIT_TEST(test_getNames_1);
    CPPUNIT_TEST(test_getNames_2);
    CPPUNIT_TEST(test_getNames_3);
    CPPUNIT_TEST(test_getBallots_1);
    CPPUNIT_TEST(test_getBallots_2);
    CPPUNIT_TEST(test_getBallots_3);
    CPPUNIT_TEST(test_getInput_1);
    CPPUNIT_TEST(test_getInput_2);
    CPPUNIT_TEST(test_getInput_3);
    CPPUNIT_TEST(test_evalBallots_1);
    CPPUNIT_TEST(test_evalBallots_2);
    CPPUNIT_TEST(test_evalBallots_3);
    CPPUNIT_TEST_SUITE_END();

};

int main() 
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

