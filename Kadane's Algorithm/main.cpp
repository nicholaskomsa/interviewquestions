#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>


class Tests {

public:




	class TestCase {

		std::vector<int> mElements;
		int mResult{ 0 };

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
			std::cout << "; result= " << mResult;
			std::cout << std::endl;
		}
		void setResult(int result) {
			mResult = result;
		}
		int getResult() { return mResult; }
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

		sstr.getline( const_cast<char*>( path.c_str()) , path.size(), '\n');

		sstr.clear();
		sstr << argv[1];
		int numTestCases = 0;
		sstr >> numTestCases;

		const int lengthOfTestCase = 2;
		int testCaseIndex = 0;

		for( int testCase=0; testCase < numTestCases; testCase++)
			for (; testCaseIndex < numTestCases * lengthOfTestCase; testCaseIndex += lengthOfTestCase) {

				TestCase testCase(argv[testCaseIndex + 2], argv[testCaseIndex + 3]);
				mTests.push_back(testCase);
			}
	}
	void printTestCases() {
		
		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			testCase.print();
		});
	}
	void printResults() {
		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			std::cout << testCase.getResult() << std::endl;
		});

	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase( int testCase ) { return mTests[testCase]; }
};


int kadanesAlgorithm(Tests::TestCase& testCase) {
	/*
	Given an array containing both negative and positive integers. Find the contiguous sub-array with maximum sum.
	Print the maximum sum of the contiguous sub-array in a separate line for each test case.
	*/

	
	std::vector<int>& elements = testCase.getElements();


	/* first attempt
	int result = elements[0];
	int sum = 0;


	lets construct a list of all possible sub arrays first
	for (int c = 0; c < elements.size(); c++) {
		for (int offsetNeg = 0;  c - offsetNeg >= 0; offsetNeg++) {
			for (int offsetPos = 0; offsetPos + c < elements.size(); offsetPos++) {

				sum = 0;
				for (int i = c - offsetNeg; i <= c + offsetPos; i++) {
					sum += elements[i];
				}
			}
		}
		result = std::max(result, sum);
	}
	*/
	//modified internet code
	int sum = elements[0];
	int result = sum;
		
	for (int i = 1; i < elements.size(); i++) {
	
		if (sum > 0)
			sum += elements[i];
		else
			sum = elements[i];

		result = std::max(result, sum);
	}

	/*	
	//from internet
	int curMax = elements[0];
	result = curMax;
	for (int i = 1; i < elements.size(); i++) {
		//check if current sum ( curMax ) is going to be increased with this element, save whichever is larger

		curMax = std::max(elements[i], elements[i] + curMax);

		//
		result = std::max(curMax, result);
	}
	*/
	


	return result;
}

int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);


	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		int result = kadanesAlgorithm(testCase);
		testCase.setResult(result);
	}


	tests.printTestCases();
	tests.printResults();

	std::cin.get();


	return 0;
}