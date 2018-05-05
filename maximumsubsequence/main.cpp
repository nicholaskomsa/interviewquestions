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
		std::vector<int> mSubsequence;
		int mSubsequenceSum{ 0 };
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
		void setSubsequenceSum(int sum) {
			mSubsequenceSum = sum;
		}
		int getSubsequenceSum() {
			return mSubsequenceSum;
		}
		void moveSubsequence(std::vector<int>&& sequence) {
			mSubsequence = sequence;
		}
		void printSubsequence() {
			std::cout << "[ ";
			for (std::size_t i = 0; i < mSubsequence.size(); i++) {
				std::cout << mSubsequence[i] << ", ";
			}
			std::cout << " ]";
		}
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
			std::cout << "subsequence sum: " << testCase.getSubsequenceSum() << std::endl;
			testCase.printSubsequence();
		});
		std::cout << std::endl;
	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase(int testCase) { return mTests[testCase]; }
};


void maximumSubsequence(Tests::TestCase& testCase) {
	//in a given array, find a subsequence of values that add to the highest sum.
	//such that a subsequence not be continuous in the array, but that it must ascend in value and have the greatest sum of such ascensions
	//
	std::vector<int>& elements = testCase.getElements();

}


int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);

	tests.printTestCases();

	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		maximumSubsequence(testCase);
	}



	tests.printResults();

	std::cin.get();


	return 0;
}