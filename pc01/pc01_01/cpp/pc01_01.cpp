/**
 * The 3 * n + 1 problem
 * pc110101
 * uva100
 */

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

const int MAX_NUMBER = 1000000;
vector<int> memo;

bool isValidNumber(int number) {
	return (number > 0) && (number < MAX_NUMBER);
}

long long nextCollatz(long long number) {
	return (number & 1) ? number + (number << 1) + 1 : number >> 1;
}

int collatzLength(long long number) {
	if (number == 1) return 1;

	if (isValidNumber(number) && memo[number] != 0) {
		return memo[number];
	}

	int length = 1 + collatzLength(nextCollatz(number));

	if (isValidNumber(number)) {
		memo[number] = length;
	}

	return length;
}

int maxCollatzLength(int firstNumber, int secondNumber) {
	int start = min(firstNumber, secondNumber);
	int end = max(firstNumber, secondNumber);
	int maxLength = 0;

	for (int number = start; number <= end; number++) {
		maxLength = max(maxLength, collatzLength(number));
	}

	return maxLength;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto startTime = chrono::high_resolution_clock::now();

	memo.assign(MAX_NUMBER + 10, 0);
	memo[1] = 1;
	collatzLength(MAX_NUMBER);

	int firstNumber, secondNumber;
	while (cin >> firstNumber >> secondNumber) {
		if (!isValidNumber(firstNumber) || !isValidNumber(secondNumber)) {
			continue;
		}

		cout << firstNumber << " " << secondNumber << " "
		     << maxCollatzLength(firstNumber, secondNumber) << '\n';
	}

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> timeTaken = endTime - startTime;
	cerr << "Time of execution: " << timeTaken.count() << " seconds\n";

	return 0;
}