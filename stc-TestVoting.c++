//---------------------
// TestingVoting.c++
// Stephen Cook
//---------------------


/*
Run the program:
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
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>
#include <algorithm>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {


    // -----
    // voting_solve
    // -----

    void test_voting_solve () {
        std::istringstream r("1\n\n1\nTricky Solo\n1\n");
        std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Tricky Solo\n");
	}

	void test_voting_solve2(){
        std::istringstream r("1\n\n1\nTrickier Solo\n1\n1\n1\n1\n1\n");
        std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Trickier Solo\n");
	}

	void test_voting_solve3(){
        std::istringstream r("2\n\n1\nTricky Solo\n1\n\n2\nMamma\nMia\n1 2\n2 1\n");
        std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Tricky Solo\n\nMamma\nMia\n");
	}


	void test_voting_solve4(){
        std::istringstream r("1\n\n3\nTye Dye\nTye Gibson\nTyler Perry\n1 2 3\n2 3 1\n3 2 1");
        std::ostringstream w;
		voting_solve(r, w);
		CPPUNIT_ASSERT(w.str() == "Tye Dye\nTye Gibson\nTyler Perry\n");
	}

	//find_winner ----------------------------------

	void test_find_winner(){
		vector<vector<int> > all;

		//Create the ballots
		int pref[] = {0};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		
		//Store all the ballots together
		all.push_back(ballot);
		
		//Create the solution
		int sol[] = {0};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		int num_candidates = 1;

		vector<int> solution = find_winner(&all, num_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}

	void test_find_winner2(){
		vector<vector<int> > all;

		//Create the ballots
		int pref[] = {0, 1};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot);		

		pref = {0, 1};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot2);
		
		pref = {1, 0};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot3);
		
		//Create the solution
		int sol[] = {0};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		int num_candidates = 2;

		vector<int> solution = find_winner(&all, num_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}
    
	void test_find_winner3(){
		vector<vector<int> > all;

		//Create the ballots
		int pref[] = {0, 1};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot);		

		pref = {0, 1};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot2);
		
		pref = {1, 0};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot3);
		
		pref = {1, 0};
  		vector<int> ballot4 (pref, pref + sizeof(pref) / sizeof(int) );
		all.push_back(ballot4);

		//Create the solution
		int sol[] = {0, 1};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		int num_candidates = 2;

		vector<int> solution = find_winner(&all, num_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}


	//remove_losers ------------------------------------------------

	void test_remove_losers(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {0};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		
		//Store all the ballots together
		pile.push_back(ballot);
		
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the solution
		int sol[] = {0};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		vector<int> loser_candidates;

		vector<int> solution = remove_losers(&all, loser_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}


	void test_remove_losers2(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {1, 0};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {0, 1};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot2);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the solution
		int sol[] = {0, 1};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		vector<int> loser_candidates;

		vector<int> solution = remove_losers(&all, loser_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}


	void test_remove_losers3(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {1, 0};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {0, 1};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot2);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {0, 1};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot3);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the solution
		int sol[] = {0};
		vector<int> wins (sol, sol + sizeof(sol) / sizeof(int) );

		vector<int> loser_candidates;

		vector<int> solution = remove_losers(&all, loser_candidates);
		CPPUNIT_ASSERT(equal(wins.begin(), wins.end(), solution.begin()));
	}


	//redistribute_loser_ballots ----------------------------------------

	void test_redistribute_loser_ballots(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {0, 1, 2, 3, 4};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot2);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot4);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {2, 1, 4, 3, 0};
  		vector<int> ballot5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot5);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		vector<int> empt3;
		pile.push_back(empt3);
		all.push_back(pile);
		pile.clear();

		vector<int> empt4;
		pile.push_back(empt4);
		all.push_back(pile);
		pile.clear();

		//SOLUTION------------------------------------------------------
		vector<vector<vector<int> > > sol;		

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b2);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b4);

		//Create the ballots
		pref = {1, 4, 3, 0};
  		vector<int> b5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b5);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		vector<int> emp2;
		pile.push_back(emp2);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp3;
		pile.push_back(emp3);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp4;
		pile.push_back(emp4);
		sol.push_back(pile);
		pile.clear();

		vector<int> loser_candidates;
			loser_candidates.push_back(2);
			loser_candidates.push_back(3);
			loser_candidates.push_back(4);

		int loser_number = 2;
		redistribute_loser_ballots(all, loser_number, loser_candidates);

		//print_all(&all);
		//print_all(&sol);
		
		for(int i = 0; i< (int)all.size(); i++)
		{
			vector<vector<int> > pile1 = all[i];
			vector<vector<int> > pile2 = sol[i];

			for(int j = 0; j < (int)pile1.size(); j++)
			{
				vector<int> bal1 = pile1[j];
				vector<int> bal2 = pile2[j];
				CPPUNIT_ASSERT(equal(bal1.begin(), bal1.end(), bal2.begin()));
			}	
		}
	}




	void test_redistribute_loser_ballots2(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {0, 1, 2, 3, 4};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot2);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot4);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {2, 4, 3, 1, 0};
  		vector<int> ballot5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot5);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();


		vector<int> empt3;
		pile.push_back(empt3);
		all.push_back(pile);
		pile.clear();

		vector<int> empt4;
		pile.push_back(empt4);
		all.push_back(pile);
		pile.clear();

		//SOLUTION------------------------------------------------------
		vector<vector<vector<int> > > sol;		

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b2);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b4);

		//Create the ballots
		pref = {1, 0};
  		vector<int> b5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b5);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		vector<int> emp2;
		pile.push_back(emp2);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp3;
		pile.push_back(emp3);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp4;
		pile.push_back(emp4);
		sol.push_back(pile);
		pile.clear();

		vector<int> loser_candidates;
			loser_candidates.push_back(2);
			loser_candidates.push_back(3);
			loser_candidates.push_back(4);

		int loser_number = 2;
		redistribute_loser_ballots(all, loser_number, loser_candidates);

		//print_all(&all);
		//print_all(&sol);
		
		for(int i = 0; i< (int)all.size(); i++)
		{
			vector<vector<int> > pile1 = all[i];
			vector<vector<int> > pile2 = sol[i];

			for(int j = 0; j < (int)pile1.size(); j++)
			{
				vector<int> bal1 = pile1[j];
				vector<int> bal2 = pile2[j];
				CPPUNIT_ASSERT(equal(bal1.begin(), bal1.end(), bal2.begin()));
			}	
		}
	}


	void test_redistribute_loser_ballots3(){
		vector<vector<vector<int> > > all;
		vector<vector<int> > pile;

		//Create the ballots
		int pref[] = {0, 1, 2, 3, 4};
  		vector<int> ballot (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> ballot2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot2);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> ballot4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot4);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();

		//Create the ballots
		pref = {2, 1, 4, 3, 0};
  		vector<int> ballot5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot5);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();


		//Create the ballots
		pref = {3, 0, 4, 2, 1};
  		vector<int> ballot6 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(ballot6);
		//Push all piles onto the sorted container
		all.push_back(pile);
		pile.clear();


		vector<int> empt4;
		pile.push_back(empt4);
		all.push_back(pile);
		pile.clear();

		//SOLUTION------------------------------------------------------
		vector<vector<vector<int> > > sol;		

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b);

		//Create the ballots
		pref = {0, 1, 2, 3, 4};
  		vector<int> b2 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b2);

		//Create the ballots
		pref = {0, 4, 2, 1};
  		vector<int> b6 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b6);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		//Create the ballots
		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b3 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b3);

		//Create the ballots
		pref = {1, 0, 2, 3, 4};
  		vector<int> b4 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b4);

		//Create the ballots
		pref = {1, 4, 3, 0};
  		vector<int> b5 (pref, pref + sizeof(pref) / sizeof(int) );
		//Store all the ballots together
		pile.push_back(b5);
		//Push all piles onto the sorted container
		sol.push_back(pile);
		pile.clear();

		vector<int> emp3;
		pile.push_back(emp3);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp4;
		pile.push_back(emp4);
		sol.push_back(pile);
		pile.clear();

		vector<int> emp2;
		pile.push_back(emp2);
		sol.push_back(pile);
		pile.clear();

		vector<int> loser_candidates;
			loser_candidates.push_back(2);
			loser_candidates.push_back(3);
			loser_candidates.push_back(4);

		int loser_number = 2;
		redistribute_loser_ballots(all, loser_number, loser_candidates);
		redistribute_loser_ballots(all, 3, loser_candidates);
		//print_all(&all);
		//print_all(&sol);
		
		for(int i = 0; i< (int)all.size(); i++)
		{
			vector<vector<int> > pile1 = all[i];
			vector<vector<int> > pile2 = sol[i];

			for(int j = 0; j < (int)pile1.size(); j++)
			{
				vector<int> bal1 = pile1[j];
				vector<int> bal2 = pile2[j];
				CPPUNIT_ASSERT(equal(bal1.begin(), bal1.end(), bal2.begin()));
			}	
		}
	}


	// -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
	CPPUNIT_TEST(test_voting_solve);
    CPPUNIT_TEST(test_voting_solve2);
    CPPUNIT_TEST(test_voting_solve3);
    CPPUNIT_TEST(test_voting_solve4);
	CPPUNIT_TEST(test_find_winner);
	CPPUNIT_TEST(test_find_winner2);
	CPPUNIT_TEST(test_find_winner3);
	CPPUNIT_TEST(test_remove_losers);
	CPPUNIT_TEST(test_remove_losers2);
	CPPUNIT_TEST(test_remove_losers3);
	CPPUNIT_TEST(test_redistribute_loser_ballots);
	CPPUNIT_TEST(test_redistribute_loser_ballots2);
	CPPUNIT_TEST(test_redistribute_loser_ballots3);
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
    return 0;
}
