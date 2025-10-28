/**
 * The trip
 * pc110103
 * uva10137
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 1000;
const double MAX_MONEY = 10000.00;

double roundToCent(double value) {
	return round(value * 100.0) / 100.0;
}

double calculateExchange(vector<double>& money, int students) {
	double total = 0.0;
	for (int i = 0; i < students; i++) {
		total += money[i];
	}

	double avg = total / students;
	double avgRounded = roundToCent(avg);

	double positiveDiff = 0.0;
	double negativeDiff = 0.0;

	for (int i = 0; i < students; i++) {
		double diff = money[i] - avgRounded;
		diff = roundToCent(diff);
		if (diff > 0) {
			positiveDiff += diff;
		} else {
			negativeDiff += -diff;
		}
	}

	return min(positiveDiff, negativeDiff);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << fixed << setprecision(2);

	int students;
	vector<double> money(MAX_STUDENTS);

	while (cin >> students && students != 0) {
		for (int i = 0; i < students; i++) {
			cin >> money[i];
			money[i] = roundToCent(money[i]);
		}

		double exchange = calculateExchange(money, students);
		cout << '$' << exchange << '\n';
	}

	return 0;
}