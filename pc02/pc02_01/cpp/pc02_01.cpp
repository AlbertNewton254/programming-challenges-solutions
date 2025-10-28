/**
 * Jolly jumpers
 * pc110201
 * uva10038
 */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

const int MAX_SIZE = 3000;

bool isJolly(vector<int>& array, int size) {
	vector<bool> seenDifferences(size - 1, false);

	for (int i = 0; i < size - 1; i++) {
		int difference = abs(array[i + 1] - array[i]);

		if (difference < 1 || difference > size - 1) {
			return false;
		}

		if (seenDifferences[difference - 1]) {
			return false;
		}

		seenDifferences[difference - 1] = true;
	}

	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int size;
	while (cin >> size) {
		vector<int> array(size);
		for (int i = 0; i < size; i++) {
			cin >> array[i];
		}

		if (isJolly(array, size)) {
			cout << "Jolly\n";
		} else {
			cout << "Not jolly\n";
		}
	}

	return 0;
}
