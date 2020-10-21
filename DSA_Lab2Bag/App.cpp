#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();
	cout << "All test over" << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Tests took "<<duration.count() << " seconds" <<endl;
    return 0;
}