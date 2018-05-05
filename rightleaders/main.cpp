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
		std::vector<int> mLeaderIndexes;

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
			std::cout << "; leaders = ";
			std::for_each(mLeaderIndexes.begin(), mLeaderIndexes.end(), [](std::size_t i) {
				std::cout << i << ", ";
			});

			std::cout << std::endl;
		}
		
		std::vector<int>& getLeaders() { return mLeaderIndexes; }
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

		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			testCase.print();
		});
	}
	void printResults() {
		std::for_each(mTests.begin(), mTests.end(), [](TestCase& testCase) {
			testCase.print();
		});

	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase(int testCase) { return mTests[testCase]; }
};


void rightLeaders(Tests::TestCase& testCase) {



	std::vector<int>& elements = testCase.getElements();
	std::vector<int>& leaders = testCase.getLeaders();

	int high = elements.back();
	leaders.push_back(high);

	for (std::size_t i = elements.size() - 2; i > 0; i--) {
		if (elements[i] > high) {
			leaders.push_back(elements[i]);
			high = elements[i];
		}
	}


}

int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);


	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		rightLeaders(testCase);
	}


	tests.printResults();

	std::cin.get();


	return 0;
}