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

		int mGivenSum{ 0 };
		std::vector<int> mElements;
		std::size_t mStart{ 0 }, mEnd{ 0 };
		bool mFound{ false };
	public:
		TestCase(std::string strLength, std::string elements) {

			std::stringstream sstr;

			int length = 0;
			sstr << strLength;
			sstr >> length >> mGivenSum;

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
			std::cout << "; start= " << mStart << ", end= " << mEnd;
			std::cout << std::endl;
		}
		

		typedef std::tuple< bool, std::size_t, std::size_t > ResultTuple;

		void setResult(std::size_t start, std::size_t end) {

			mStart = start;
			mEnd = end;
		}
		ResultTuple getResult() {

			return std::make_tuple(mFound, mStart, mEnd );
		}

		bool found() { return mFound; }
		void setFound(bool found) { mFound = found; }

		int getGivenSum() { return mGivenSum; }
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

			auto [ found, first, second ] = testCase.getResult();
			//add one to first and second to make the indexes 1 based
			std::cout << "found= " << (found?"true":"false") << " givenSum= " << testCase.getGivenSum() << "; ( " << (first +1 )<< ", " << (second+1) << " )" <<  std::endl;
		});

	}
	int getNumTestCases() { return mTests.size(); }
	TestCase& getTestCase(int testCase) { return mTests[testCase]; }
};


void findSubArrayWithGivenSum(Tests::TestCase& testCase) {

	std::vector<int>& elements = testCase.getElements();



	//code i wrote
	int sum = 0, givenSum = testCase.getGivenSum();

	std::size_t start = 0, end = 0;
	/*fist attempt
	bool found = false;
	while (start < elements.size()){
		sum = 0;
		for (std::size_t i = start; i < elements.size(); i++) {

			sum += elements[i];
			if (sum == givenSum) {
				end = i;
				found = true;
				break;
			}
		}
		if (found) break;
		start++;
	} 
	*/
	start = end = 0;
	sum = 0;
	while (start < elements.size() ) {

		while (sum > givenSum) {
			sum -= elements[start];
			start++;
			if (start > end ) end = start;
		}

		if (sum == givenSum) {
			testCase.setFound(true);
			testCase.setResult(start, end);
			break;
		}else {
			if (end < elements.size()) {
				sum += elements[end];
				if (sum != givenSum && end < elements.size() -1 ) end++;
			}
			else
				break;
		}
	}
/*	from forum, does not work in all cases
	start = end = 0;
	sum = 0;
	int counter = 0;
	while (counter < elements.size())
	{
		sum += elements[ counter];
		end = counter;

		if (sum > givenSum)
		{
			sum -= elements[ start];
			start++;
		}
		if (sum == givenSum)
			break;
		counter++;
	}
	*/
}

int main(int argc, char**argv) {

	Tests tests;
	tests.readTestCasesFromCmdLine(argc, argv);


	for (int i = 0; i < tests.getNumTestCases(); i++) {

		Tests::TestCase& testCase = tests.getTestCase(i);

		findSubArrayWithGivenSum(testCase);
	}


	tests.printTestCases();
	tests.printResults();

	std::cin.get();


	return 0;
}