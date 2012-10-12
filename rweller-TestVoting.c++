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
    
    void test_voting_solve () {
        using namespace std;
        std::istringstream r("1\n\n2\nJohny\nDonny\n1 2\n1 2\n\n");
        cout << "1\n\n2\nJohny\nDonny\n1 2\n1 2\n\n";
        std::ostringstream w;
		voting_eval(r, w);
		CPPUNIT_ASSERT(w.str() == "Johny");
        
	}
    
   CPPUNIT_TEST_SUITE(TestVoting);
 //   CPPUNIT_TEST(test_voting_solve);
    
   CPPUNIT_TEST_SUITE_END();};


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