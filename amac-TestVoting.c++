// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2012
// Adrian Maceiras and Glenn Downing
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
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
// -----------

struct TestVoting : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read_names_1 () {
        std::istringstream r("Adrian Maceiras\n");
        std::vector<std::string> s;
        const bool b = voting_read_names(r, 1, s);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(s.size() == 1);
        CPPUNIT_ASSERT(s[0] == "Adrian Maceiras");
      }

    void test_read_names_2 () {
        std::istringstream r("Glenn Downing\nAdrian Maceiras\n");
        std::vector<std::string> s;
        const bool b = voting_read_names(r, 2, s);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(s[0] == "Glenn Downing");
        CPPUNIT_ASSERT(s[1] == "Adrian Maceiras");
      }

    void test_read_names_3 () {
        std::istringstream r("Red\nGreen\nBlue\nOrange\nPurple\n");
        std::vector<std::string> s;
        const bool b = voting_read_names(r, 5, s);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(s[0] == "Red");
        CPPUNIT_ASSERT(s[1] == "Green");
        CPPUNIT_ASSERT(s[2] == "Blue");
        CPPUNIT_ASSERT(s[3] == "Orange");
        CPPUNIT_ASSERT(s[4] == "Purple");
      }



    void test_read_ints_1 () {
        std::istringstream r("1 2\n");
        std::deque<int> v;
        const bool b = voting_read_ints(r, 2, v);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v[0] ==    1);
        CPPUNIT_ASSERT(v[1] ==   2);}

    void test_read_ints_2 () {
        std::istringstream r("78\n");
        int i;
        const bool b = voting_read_ints(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 78);
    }

    void test_read_ints_3 () {
        std::istringstream r("1 2\n");
        std::deque<int> v;
        const bool b = voting_read_ints(r, 2, v);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v[0] ==    1);
        CPPUNIT_ASSERT(v[1] ==   2);
      }

    void test_read_ints_4 () {
        std::istringstream r("4 5 6 7 1 2 3\n");
        std::deque<int> v;
        const bool b = voting_read_ints(r, 7, v);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v[0] ==    4);
        CPPUNIT_ASSERT(v[1] ==    5);
        CPPUNIT_ASSERT(v[2] ==    6);
        CPPUNIT_ASSERT(v[3] ==    7);
        CPPUNIT_ASSERT(v[4] ==    1);
        CPPUNIT_ASSERT(v[5] ==    2);
        CPPUNIT_ASSERT(v[6] ==    3);
      }

    void test_read_ints_5 () {
        std::istringstream r("3 5 8 2 4 9 1 7 6\n");
        std::deque<int> v;
        const bool b = voting_read_ints(r, 9, v);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v[0] ==    3);
        CPPUNIT_ASSERT(v[1] ==    5);
        CPPUNIT_ASSERT(v[2] ==    8);
        CPPUNIT_ASSERT(v[3] ==    2);
        CPPUNIT_ASSERT(v[4] ==    4);
        CPPUNIT_ASSERT(v[5] ==    9);
        CPPUNIT_ASSERT(v[6] ==    1);
        CPPUNIT_ASSERT(v[7] ==    7);
        CPPUNIT_ASSERT(v[8] ==    6);
      }


    void test_read_ints_6 () {
        std::istringstream r("17 7 2 14 12 19 4 5 16 11 13 15 18 20 9 6 8 1 3 10\n");
        std::deque<int> v;
        const bool b = voting_read_ints(r, 20, v);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(v[0] ==    17);
        CPPUNIT_ASSERT(v[19] ==    10);
      }


    void test_read_ballots_1 () {
        std::istringstream r("1 2 3\n 1 2 3\n 1 2 3\n\n");
        std::vector<std::vector<std::deque<int> > > election;
        const bool b = voting_read_ballots(r, 3, election);
        std::vector<std::deque<int> > ballots = election[0];
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.size() == 3);
        CPPUNIT_ASSERT(ballots.size() == 3);
        int result[] = {1 ,2 ,3};

        for(unsigned int i = 0; i < ballots.size(); i++) {
            std::deque<int> ballot = ballots[i];
            for(unsigned int j = 0; j < ballot.size(); j++) {
                CPPUNIT_ASSERT(ballot.size() == 3);
                CPPUNIT_ASSERT(ballot[j] == result[j]);
            }   
        }
    }

    void test_read_ballots_2 () {
        std::istringstream r("9 8 7 6 5 4 3 2 1\n9 8 7 6 5 4 3 2 1\n9 8 7 6 5 4 3 2 1\n\n");
        std::vector<std::vector<std::deque<int> > > election;
        const bool b = voting_read_ballots(r, 9, election);
        std::vector<std::deque<int> > ballots = election[8];
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.size() == 9);
        CPPUNIT_ASSERT(ballots.size() == 3);
        int result[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

        for(unsigned int i = 0; i < ballots.size(); i++) {
            std::deque<int> ballot = ballots[i];
            for(unsigned int j = 0; j < ballot.size(); j++) {
                CPPUNIT_ASSERT(ballot.size() == 9);
                CPPUNIT_ASSERT(ballot[j] == result[j]);
            }
        }      
    }

    void test_read_ballots_3 () {
        std::istringstream r("5 2 3 1 4\n5 2 3 1 4\n5 2 3 1 4\n\n");
        std::vector<std::vector<std::deque<int> > > election;
        const bool b = voting_read_ballots(r, 5, election);
        std::vector<std::deque<int> > ballots = election[4];
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(election.size() == 5);
        CPPUNIT_ASSERT(ballots.size() == 3);
        int result[] = {5, 2, 3, 1, 4};

        for(unsigned int i = 0; i < ballots.size(); i++) {
            std::deque<int> ballot = ballots[i];
            for(unsigned int j = 0; j < ballot.size(); j++) {
                CPPUNIT_ASSERT(ballot.size() == 5);
                CPPUNIT_ASSERT(ballot[j] == result[j]);
            }            
        }        
    }



    void test_skip_line_1 () {
        std::istringstream r("78\nblah\n");
        const bool b = voting_skip_line(r);
        std::string s;
        std::getline(r, s);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(s == "blah");
    }

    void test_skip_line_2 () {
        std::istringstream r("\nblah\n");
        const bool b = voting_skip_line(r);
        std::string s;
        std::getline(r, s);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(s == "blah");
    }

    void test_skip_line_3 () {
        std::istringstream r("skipped\n100\n");
        int i;
        const bool b = voting_skip_line(r);
        const bool bb = voting_read_ints(r,i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(bb == true);      
        CPPUNIT_ASSERT(i == 100);
    }
    // -----
    // print
    // -----

    void test_print_1 () {
        std::ostringstream w;
        std::vector<std::string> v;
        v.push_back("Adrian Maceiras");
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Adrian Maceiras\n");
      }

    void test_print_2 () {
        std::ostringstream w;
        std::vector<std::string> v;
        v.push_back("Red");
        v.push_back("Green");
        v.push_back("Blue");                
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "Red\nGreen\nBlue\n");
      }   

    void test_print_3 () {
        std::ostringstream w;
        std::vector<std::string> v;
        v.push_back("This");
        v.push_back("test");
        v.push_back("of");
        v.push_back("print");
        v.push_back("works!"); 
        voting_print(w, v);
        CPPUNIT_ASSERT(w.str() == "This\ntest\nof\nprint\nworks!\n");
      }

    //test >50%
    void test_find_winner_1 () {
      std::deque<int> losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot;
      ballot.push_back(2);
      ballot.push_back(1);

      std::vector<std::deque<int> > ballots;
      election.push_back(ballots);
      ballots.push_back(ballot);
      election.push_back(ballots);

      canidates.push_back("Red");
      canidates.push_back("Blue");

      int total = 0;

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      int threshold = (total / 2);
      const bool b = voting_find_winner(election, losers, canidates, results, threshold);
      CPPUNIT_ASSERT(b == false);
    }

    //test tie
    void test_find_winner_2 () {
      std::deque<int> losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot;
      ballot.push_back(1);
      ballot.push_back(2);

      std::vector<std::deque<int> > ballots;
      ballots.push_back(ballot);
      election.push_back(ballots);
      ballots.clear();
      ballot.clear();
      ballot.push_back(2);
      ballot.push_back(1);
      ballots.push_back(ballot);
      election.push_back(ballots);

      canidates.push_back("Red");
      canidates.push_back("Blue");

      int total = 0;

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      int threshold = (total / 2);
      const bool b = voting_find_winner(election, losers, canidates, results, threshold);
      CPPUNIT_ASSERT(b == false);
    }

    //test need to redistribute
    void test_find_winner_3 () {
      std::deque<int> losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot1;
      ballot1.push_back(1);
      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(4);

      std::deque<int> ballot2;
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(4);

      std::vector<std::deque<int> > ballots;
      ballots.push_back(ballot1);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();

      ballot1.push_back(2);
      ballot1.push_back(1);
      ballot1.push_back(4);
      ballot1.push_back(3);
      ballots.push_back(ballot1);
      election.push_back(ballots);
      ballots.clear();
      election.push_back(ballots);
      ballot2.push_back(4);
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballots.push_back(ballot2);
      election.push_back(ballots);

      canidates.push_back("Burnt Orange");
      canidates.push_back("Blue");
      canidates.push_back("Red");
      canidates.push_back("Green");

      int total = 0;

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      int threshold = (total / 2);
      const bool b = voting_find_winner(election, losers, canidates, results, threshold);
      CPPUNIT_ASSERT(b == true);
    }

    //test need to redistribute
    void test_redistribute_1 () {
      std::deque<int> losers;
      std::deque<int> cur_losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot1;
      ballot1.push_back(1);
      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(4);

      std::deque<int> ballot2;
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(4);

      std::vector<std::deque<int> > ballots;
      ballots.push_back(ballot1);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();

      ballot1.push_back(2);
      ballot1.push_back(1);
      ballot1.push_back(4);
      ballot1.push_back(3);
      ballots.push_back(ballot1);
      election.push_back(ballots);
      ballots.clear();
      election.push_back(ballots);
      ballot2.push_back(4);
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballots.push_back(ballot2);
      election.push_back(ballots);

      canidates.push_back("Burnt Orange");
      canidates.push_back("Blue");
      canidates.push_back("Red");
      canidates.push_back("Green");

      int total = 0;

      cur_losers.push_back(1);
      cur_losers.push_back(3);

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      losers.push_back(1);
      losers.push_back(3);
      std::sort(losers.begin(), losers.end());

      bool const b = voting_redistribute(election, cur_losers, losers);
      CPPUNIT_ASSERT( b == true);
      CPPUNIT_ASSERT( (election[0]).size() == 4);
      CPPUNIT_ASSERT( losers.size() == 3);
    }

    void test_redistribute_2 () {
      std::deque<int> losers;
      std::deque<int> cur_losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot1;
      ballot1.push_back(1);
      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(4);

      std::deque<int> ballot2;
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(4);

      std::vector<std::deque<int> > ballots;
      ballots.push_back(ballot1);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();

      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(2);
      ballot1.push_back(1);
      ballots.push_back(ballot1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(2);
      ballot2.push_back(1);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();
      ballot1.push_back(3);
      ballot1.push_back(2);
      ballot1.push_back(1);
      ballot1.push_back(4);
      ballots.push_back(ballot1);
      election.push_back(ballots);
      ballots.clear();
      ballot2.push_back(4);
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballots.push_back(ballot2);
      election.push_back(ballots);

      canidates.push_back("Burnt Orange");
      canidates.push_back("Blue");
      canidates.push_back("Red");
      canidates.push_back("Green");

      int total = 0;

      cur_losers.push_back(2);
      cur_losers.push_back(3);

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      losers.push_back(2);
      losers.push_back(3);
      std::sort(losers.begin(), losers.end());

      bool const b = voting_redistribute(election, cur_losers, losers);
      CPPUNIT_ASSERT( b == true);
      CPPUNIT_ASSERT( (election[0]).size() == 3);
      CPPUNIT_ASSERT( (election[1]).size() == 3);
      CPPUNIT_ASSERT( losers.size() == 2);
    }

    void test_redistribute_3 () {
      std::deque<int> losers;
      std::deque<int> cur_losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot1;
      ballot1.push_back(1);
      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(4);
      ballot1.push_back(5);

      std::deque<int> ballot2;
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(4);
      ballot2.push_back(5);

      std::vector<std::deque<int> > ballots;
      ballots.push_back(ballot1);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();

      ballot1.push_back(2);
      ballot1.push_back(3);
      ballot1.push_back(4);
      ballot1.push_back(1);
      ballot1.push_back(5);

      ballots.push_back(ballot1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(4);
      ballot2.push_back(1);
      ballot2.push_back(5);

      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot1.clear();
      ballot2.clear();
      ballot1.push_back(3);
      ballot1.push_back(2);
      ballot1.push_back(1);
      ballot1.push_back(4);
      ballot1.push_back(5);
      ballots.push_back(ballot1);
      election.push_back(ballots);
      ballots.clear();
      ballot2.clear();
      ballot2.push_back(4);
      ballot2.push_back(1);
      ballot2.push_back(2);
      ballot2.push_back(3);
      ballot2.push_back(5);
      ballots.push_back(ballot2);
      election.push_back(ballots);
      ballots.clear();
      ballot2.clear();
      ballot2.push_back(5);
      ballot2.push_back(2);
      ballot2.push_back(1);
      ballot2.push_back(3);
      ballot2.push_back(4);
      ballots.push_back(ballot2);
      election.push_back(ballots);

      canidates.push_back("Burnt Orange");
      canidates.push_back("Blue");
      canidates.push_back("Red");
      canidates.push_back("Green");
      canidates.push_back("Yellow");

      int total = 0;

      cur_losers.push_back(2);
      cur_losers.push_back(3);
      cur_losers.push_back(4);

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }

      losers.push_back(2);
      losers.push_back(3);
      losers.push_back(4);
      std::sort(losers.begin(), losers.end());

      bool const b = voting_redistribute(election, cur_losers, losers);
      CPPUNIT_ASSERT( b == true);
      CPPUNIT_ASSERT( (election[0]).size() == 3);
      CPPUNIT_ASSERT( (election[1]).size() == 4);
      CPPUNIT_ASSERT( losers.size() == 3);
    }

    // -----
    // results
    // -----

    void test_determine_results_1 () {
        std::vector<std::string> canidates;
        canidates.push_back("Adrian Maceiras");
        canidates.push_back("Glenn Downing");
        std::vector<std::vector<std::deque<int> > > election;
        for(int i = 0; i < 2; i ++) {
            std::vector<std::deque<int> > ballots;
            election.push_back(ballots);
        }
        std::vector<std::deque<int> >& ballots = election[0];

        for(int i = 0; i < 4; ++i) {
            std::deque<int> ballot;
            for(int j = 1; j < 3; ++j)
                ballot.push_back(j);
            
            ballots.push_back(ballot);
        }

        std::vector<std::string> results;
        const bool b = voting_determine_results(election, canidates, results);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(results[0] == "Adrian Maceiras");
      }


        void test_determine_results_2 () {
        std::deque<int> losers;
        std::vector<std::string> canidates;
        std::vector<std::string> results;
        std::vector<std::vector<std::deque<int> > > election;

        std::deque<int> ballot;
        ballot.push_back(1);
        ballot.push_back(2);

        std::vector<std::deque<int> > ballots;
        ballots.push_back(ballot);
        election.push_back(ballots);
        ballots.clear();
        ballot.clear();
        ballot.push_back(2);
        ballot.push_back(1);
        ballots.push_back(ballot);
        election.push_back(ballots);

        canidates.push_back("Red");
        canidates.push_back("Blue");

        const bool b = voting_determine_results(election, canidates, results);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(results[0] == "Red");
        CPPUNIT_ASSERT(results[1] == "Blue");
      }


    void test_determine_results_3 () {

      std::deque<int> losers;
      std::vector<std::string> canidates;
      std::vector<std::string> results;
      std::vector<std::vector<std::deque<int> > > election;

      std::deque<int> ballot;
      ballot.push_back(2);
      ballot.push_back(1);

      std::vector<std::deque<int> > ballots;
      election.push_back(ballots);
      ballots.push_back(ballot);
      election.push_back(ballots);

      canidates.push_back("Red");
      canidates.push_back("Blue");

      int total = 0;

      for(unsigned int i = 0; i < election.size(); ++i) {
        if((election[i]).size() == 0)
          losers.push_back(i);
        else
          total += (election[i]).size();
      }
        const bool b = voting_determine_results(election, canidates, results);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(results[0] == "Blue");
      }

    void test_results_1 () {
        std::istringstream r("1\n\n3\nRed\nBlue\nGreen\n1 2 3\n 1 2 3\n 1 2 3\n\n");
        std::ostringstream w;
        voting_results(r, w);
        CPPUNIT_ASSERT(w.str() == "Red\n");
      }

    void test_results_2 () {
        std::istringstream r("1\n\n3\nGlenn\nRed\nBlue\n1 2 3\n1 2 3\n3 2 1\n3 2 1\n2 1 3\n\n");
        std::ostringstream w;
        voting_results(r, w);
        CPPUNIT_ASSERT(w.str() == "Glenn\n");
      }

      void test_results_3 () {
        std::istringstream r("1\n\n2\nGood\nEvil\n1 2\n2 1\n\n");
        std::ostringstream w;
        voting_results(r, w);
        CPPUNIT_ASSERT(w.str() == "Good\nEvil\n");
      }

    void test_results_4 () {
        std::istringstream r("1\n\n5\nGlenn\nRed\nBlue\nGreen\nOrange\n1 2 3 4 5\n1 2 3 4 5\n3 2 1 5 4\n3 2 1 4 5\n2 1 3 4 5\n4 1 3 2 5\n5 1 3 2 4\n\n");
        std::ostringstream w;
        voting_results(r, w);
        CPPUNIT_ASSERT(w.str() == "Glenn\n");
      }

    void test_results_5 () {
        std::istringstream r("1\n\n5\nGlenn\nRed\nBlue\nGreen\nOrange\n1 2 3 4 5\n1 2 3 4 5\n3 2 1 5 4\n3 2 1 4 5\n2 3 1 4 5\n4 1 3 2 5\n\n");
        std::ostringstream w;
        voting_results(r, w);
        CPPUNIT_ASSERT(w.str() == "Glenn\nBlue\n");
      }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_read_names_1);
    CPPUNIT_TEST(test_read_names_2);
    CPPUNIT_TEST(test_read_names_3);
    CPPUNIT_TEST(test_read_ints_1);
    CPPUNIT_TEST(test_read_ints_2);
    CPPUNIT_TEST(test_read_ints_3);
    CPPUNIT_TEST(test_read_ints_4);
    CPPUNIT_TEST(test_read_ints_5);
    CPPUNIT_TEST(test_read_ints_6);
    CPPUNIT_TEST(test_read_ballots_1);
    CPPUNIT_TEST(test_read_ballots_2);
    CPPUNIT_TEST(test_read_ballots_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_determine_results_1);
    CPPUNIT_TEST(test_determine_results_2);
    CPPUNIT_TEST(test_determine_results_3);
    CPPUNIT_TEST(test_redistribute_1);
    CPPUNIT_TEST(test_redistribute_2);
    CPPUNIT_TEST(test_redistribute_3);
    CPPUNIT_TEST(test_results_1);
    CPPUNIT_TEST(test_results_2);
    CPPUNIT_TEST(test_results_3);
    CPPUNIT_TEST(test_results_4);
    CPPUNIT_TEST(test_results_5);
    CPPUNIT_TEST(test_find_winner_1);
    CPPUNIT_TEST(test_find_winner_2);
    CPPUNIT_TEST(test_find_winner_3);
    CPPUNIT_TEST_SUITE_END();
  };

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
  }
