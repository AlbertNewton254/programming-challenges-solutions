/**
 * Australian voting
 * pc110108
 * uva10142
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_CANDIDATES = 20;
const int MAX_VOTERS = 1000;

struct Candidate {
	string name;
	bool eliminated;

	Candidate() : eliminated(false) {}
};

struct Voter {
	vector<int> preferences;
	int currentPreference;

	Voter(int numCandidates) : preferences(numCandidates), currentPreference(0) {}
};

void readCandidates(vector<Candidate>& candidates, int n) {
	string line;
	getline(cin, line);

	for (int i = 0; i < n; i++) {
		getline(cin, line);
		candidates[i].name = line;
	}
}

void readVotes(vector<Voter>& voters, int numCandidates) {
	string line;

	while (getline(cin, line) && !line.empty()) {
		Voter voter(numCandidates);
		stringstream ss(line);

		for (int i = 0; i < numCandidates; i++) {
			int pref;
			ss >> pref;
			voter.preferences[i] = pref - 1;
		}
		voters.push_back(voter);
	}
}

void countVotes(const vector<Voter>& voters, const vector<Candidate>& candidates,
		vector<int>& counts) {
	fill(counts.begin(), counts.end(), 0);

	for (const Voter& voter : voters) {
		int pref = voter.currentPreference;

		while (pref < candidates.size() && candidates[voter.preferences[pref]].eliminated) {
			pref++;
		}
		if (pref < candidates.size()) {
			counts[voter.preferences[pref]]++;
		}
	}
}

void eliminateCandidates(vector<Candidate>& candidates, const vector<int>& counts,
		int minVotes) {
	for (size_t i = 0; i < candidates.size(); i++) {
		if (!candidates[i].eliminated && counts[i] == minVotes) {
			candidates[i].eliminated = true;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int cases;
	cin >> cases;
	cin.ignore();

	for (int c = 0; c < cases; c++) {
		if (c > 0)
			cout << '\n';

		int numCandidates;
		cin >> numCandidates;
		cin.ignore();

		vector<Candidate> candidates(numCandidates);
		readCandidates(candidates, numCandidates);

		vector<Voter> voters;
		readVotes(voters, numCandidates);

		while (true) {
			vector<int> counts(numCandidates);
			countVotes(voters, candidates, counts);

			int maxVotes = 0, minVotes = voters.size() + 1;
			int remaining = 0;

			for (int i = 0; i < numCandidates; i++) {
				if (!candidates[i].eliminated) {
					remaining++;
					maxVotes = max(maxVotes, counts[i]);
					minVotes = min(minVotes, counts[i]);
				}
			}

			if (maxVotes > voters.size() / 2 || remaining <= 1) {
				for (int i = 0; i < numCandidates; i++) {
					if (!candidates[i].eliminated && counts[i] == maxVotes) {
						cout << candidates[i].name << '\n';
					}
				}
				break;
			}

			eliminateCandidates(candidates, counts, minVotes);
		}
	}

	return 0;
}