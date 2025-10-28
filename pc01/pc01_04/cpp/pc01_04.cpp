/**
 * LCD display
 * pc110104
 * uva706
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_NUMBER = 99999999;
const int MAX_SCALE = 10;

const int SEG_TOP         = 0b0000001;
const int SEG_TOP_LEFT    = 0b0000010;
const int SEG_TOP_RIGHT   = 0b0000100;
const int SEG_MIDDLE      = 0b0001000;
const int SEG_BOTTOM_LEFT = 0b0010000;
const int SEG_BOTTOM_RIGHT = 0b0100000;
const int SEG_BOTTOM      = 0b1000000;

const int NUMBER[10] = {
	SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
	SEG_TOP_RIGHT | SEG_BOTTOM_RIGHT,
	SEG_TOP | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM,
	SEG_TOP | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
	SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT,
	SEG_TOP | SEG_TOP_LEFT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_TOP_LEFT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_TOP_RIGHT | SEG_BOTTOM_RIGHT,
	SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
	SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM
};

void printHorizontal(int digit, int scale, int segment) {
	cout << ' ';
	for (int i = 0; i < scale; i++) {
		cout << (NUMBER[digit] & segment ? '-' : ' ');
	}
	cout << ' ';
}

void printVertical(int digit, int scale, int leftSeg, int rightSeg) {
	cout << (NUMBER[digit] & leftSeg ? '|' : ' ');
	for (int i = 0; i < scale; i++) {
		cout << ' ';
	}
	cout << (NUMBER[digit] & rightSeg ? '|' : ' ');
}

void printDigits(int number, int scale) {
	vector<int> digits;

	if (number == 0) {
		digits.push_back(0);
	} else {
		while (number > 0) {
			digits.push_back(number % 10);
			number /= 10;
		}
	}

	for (int line = 0; line < 2 * scale + 3; line++) {
		for (int d = digits.size() - 1; d >= 0; d--) {
			int digit = digits[d];

			if (line == 0) {
				printHorizontal(digit, scale, SEG_TOP);
			} else if (line > 0 && line < scale + 1) {
				printVertical(digit, scale, SEG_TOP_LEFT, SEG_TOP_RIGHT);
			} else if (line == scale + 1) {
				printHorizontal(digit, scale, SEG_MIDDLE);
			} else if (line > scale + 1 && line < 2 * scale + 2) {
				printVertical(digit, scale, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
			} else if (line == 2 * scale + 2) {
				printHorizontal(digit, scale, SEG_BOTTOM);
			}

			if (d > 0) cout << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int scale, number;

	while (cin >> scale >> number && (scale != 0 || number != 0)) {
		if (number < 0 || number > MAX_NUMBER) continue;
		if (scale < 1 || scale > MAX_SCALE) continue;

		printDigits(number, scale);
		cout << '\n';
	}

	return 0;
}