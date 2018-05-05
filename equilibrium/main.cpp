#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>

class Tests {

public:




	class TestCase {

		std::vector<int> mElements;
		std::size_t mEquilibrium{ 0 };

	public:
		TestCase(std::string strLength, std::string elements) {

			std::stringstream sstr;

			int length = 0;
			sstr << strLength;
			sstr >> length;

			sstr.clear();
			sstr << elements;
			for (int i = 0; i < length; i++) {
				int element = 0;
				sstr >> element;
				mElements.push_back(element);
			}
		}
		void print() {

			std::cout << mElements.size() << " : ";
			std::for_each(mElements.begin(), mElements.end(), [](int e) {
				std::cout << e << ", ";
			});
		}
		void setEquilibrium(std::size_t e) { mEquilibrium = e; }
		std::size_t getEquilibrium() { return mEquilibrium; }

		std::vector<int>& getElements() { return mElements; }
	};


	typedef std::vector<TestCase > TestCases;


private:
	TestCases mTests;


public:
	void readTestCasesFromCmdLine(int argc, char** argv) {

		std::stringstream sstr;
		std::string path;
		sstr << argv[0];
		path.resize(255);

		sstr.getline(const_cast<char*>(path.c_str()), path.size(), '\n');

		sstr.clear();
		sstr << argv[1];
		int numTestCases = 0;
		sstr >> numTestCases;

		const int lengthOfTestCase = 2;
		int testCaseIndex = 0;

		for (int testCase = 0; testCase < numTestCases; testCase++)
			for (; testCaseIndex < numTestCases * lengthOfTestCase; testCaseIndex += lengthOfTestCase) {

				TestCase testCase(argv[testCaseIndex + 2], argv[testCaseIndex + 3]);
				mTests.push_back(testCase);
			}
	}
	void printTestCases() {
		std::cout << "cases: " << std::endl;
		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			testCase.print();
		});
		std::cout << std::endl;
	}
	void printResults() {
		std::cout << "\nresults: " << std::endl;
		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			std::cout << "equilibrium index: " << testCase.getEquilibrium() << "; ";
		});
		std::cout << std::endl;
	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase(int testCase) { return mTests[testCase]; }
};


void equilibrium(Tests::TestCase& testCase) {

	std::vector<int>& elements = testCase.getElements();

	std::size_t firstHalf = 0, secondHalf = 0;

	int sumFirst = elements[0];
	int sumSecond = elements.back();
	int examined = 2;

	std::size_t f = 1 , l = elements.size()-2;

	do{
		if (f >= elements.size() || l < 0) 
			break; // no solution

		if (sumFirst == sumSecond &&  examined == elements.size()-1) {

			//found it
			testCase.setEquilibrium( f );
			break;
		
		} 
		
		if (sumFirst <= sumSecond) {
			sumFirst += elements[f];
			f++;
			examined++;
		}
		else if (sumFirst > sumSecond) {
			sumSecond += elements[l];
			l--;
			examined++;
		}
	
	} while (examined < elements.size());


}

int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);

	tests.printTestCases();

	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		equilibrium(testCase);
	}



	tests.printResults();

	std::cin.get();


	return 0;
}