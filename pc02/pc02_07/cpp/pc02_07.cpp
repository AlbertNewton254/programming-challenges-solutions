/**
 * Contests scoreboard
 * pc110207
 * uva10258
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct Contestant {
	int solved;
	int penalty;
	bool participated;
	vector<int> wrong;
	vector<bool> solvedFlag;

	Contestant() : solved(0), penalty(0), participated(false),
		wrong(10, 0), solvedFlag(10, false) {}

	void submit(int problem, int time, char verdict) {
		participated = true;
		int idx = problem - 1;

		if (verdict == 'I') {
			if (!solvedFlag[idx]) {
				wrong[idx]++;
			}
		} else if (verdict == 'C') {
			if (!solvedFlag[idx]) {
				solvedFlag[idx] = true;
				solved++;
				penalty += time + 20 * wrong[idx];
			}
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	cin.ignore();

	while (T-- > 0) {
		vector<Contestant> teams(101);

		string line;
		while (getline(cin, line)) {
			if (line.empty()) break;

			istringstream iss(line);
			int t, p, time;
			char verdict;

			iss >> t >> p >> time >> verdict;

			teams[t].submit(p, time, verdict);
		}

		vector<tuple<int, int, int>> scoreboard;
		for (int i = 1; i <= 100; i++) {
			if (teams[i].participated) {
				scoreboard.push_back(make_tuple(i, teams[i].solved, teams[i].penalty));
			}
		}

		sort(scoreboard.begin(), scoreboard.end(),
			[](const auto& a, const auto& b) {
				if (get<1>(b) != get<1>(a)) return get<1>(b) < get<1>(a);
				if (get<2>(a) != get<2>(b)) return get<2>(a) < get<2>(b);
				return get<0>(a) < get<0>(b);
			});

		for (const auto& row : scoreboard) {
			cout << get<0>(row) << " " << get<1>(row) << " " << get<2>(row) << '\n';
		}

		if (T > 0) cout << '\n';
	}

	return 0;
}
