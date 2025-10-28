/**
 * Hartals
 * pc110203
 * uva10050
 */

#include <iostream>
#include <vector>
using namespace std;

int calculateHartalDays(int n, vector<int>& h) {
	vector<bool> days(n + 1, false);
	int hartalDays = 0;

	for (int hartalParam : h) {
		for (int j = hartalParam; j <= n; j += hartalParam) {
			if (j % 7 != 0 && j % 7 != 6) {
				days[j] = true;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (days[i]) {
			hartalDays++;
		}
	}

	return hartalDays;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int N, P;
		cin >> N >> P;

		vector<int> h(P);
		for (int i = 0; i < P; i++) {
			cin >> h[i];
		}

		cout << calculateHartalDays(N, h) << '\n';
	}

	return 0;
}
