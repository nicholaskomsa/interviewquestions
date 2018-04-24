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
			testCase.print();
		});
		std::cout << std::endl;
	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase(int testCase) { return mTests[testCase]; }
};


void sort012Ascending(Tests::TestCase& testCase) {

	std::vector<int>& elements = testCase.getElements();
	/*
	int zero=0, one=0, two=0;

	for (std::size_t i = 0; i < elements.size(); i++) {
		if (elements[i] == 0) zero++;
		else if (elements[i] == 1) one++;
		else two++;
	}

	elements.clear();

	for (int z = 0; z < zero; z++)
		elements.push_back(0);
	for (int o = 0; o < one; o++)
		elements.push_back(1);
	for (int t = 0; t < two; t++)
		elements.push_back(2);
	*/

	//dutch national flag problem solution

	const int top = 2, mid = 1, bot = 0;
	int ibot = 0, itop = elements.size() - 1;

	int i = 0;
	while( i <= itop ){

		if (elements[i] == top) {
			std::swap(elements[i], elements[itop]);
			itop--;

		}else if (elements[i] == bot) {
			std::swap(elements[i], elements[ibot]);
			ibot++;
			i++;

		}else
			i++;
	}






}

int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);

	tests.printTestCases();

	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		sort012Ascending(testCase);
	}



	tests.printResults();

	std::cin.get();


	return 0;
}