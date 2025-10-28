/**
 * Erdos numbers
 * pc110206
 * uva10044
 */

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

vector<int> getAuthors(const string& paper, map<string, int>& authorIndex, int& nextIndex) {
	vector<int> authorIds;
	size_t colonPos = paper.find(':');
	string authorPart = (colonPos != string::npos) ? paper.substr(0, colonPos) : paper;

	stringstream ss(authorPart);
	string part;

	vector<string> parts;
	while (getline(ss, part, ',')) {
		size_t start = part.find_first_not_of(" \t");
		size_t end = part.find_last_not_of(" \t");
		if (start != string::npos) {
			parts.push_back(part.substr(start, end - start + 1));
		}
	}

	for (size_t i = 0; i + 1 < parts.size(); i += 2) {
		string author = parts[i] + ", " + parts[i + 1];

		if (authorIndex.find(author) == authorIndex.end()) {
			authorIndex[author] = nextIndex++;
		}
		authorIds.push_back(authorIndex[author]);
	}

	return authorIds;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	cin.ignore();

	bool isFirst = true;

	while (T-- > 0) {
		if (!isFirst) cout << '\n';
		isFirst = false;

		cout << "Scenario " << (T + 1) << '\n';

		int P, N;
		cin >> P >> N;
		cin.ignore();

		map<string, int> authorIndex;
		int nextIndex = 0;

		vector<vector<int>> graph(10000);

		string line;
		for (int i = 0; i < P; i++) {
			getline(cin, line);
			vector<int> authorIds = getAuthors(line, authorIndex, nextIndex);

			for (size_t j = 0; j < authorIds.size(); j++) {
				for (size_t k = j + 1; k < authorIds.size(); k++) {
					graph[authorIds[j]].push_back(authorIds[k]);
					graph[authorIds[k]].push_back(authorIds[j]);
				}
			}
		}

		vector<int> dist(nextIndex, -1);

		if (authorIndex.find("Erdos, P.") != authorIndex.end()) {
			int erdosId = authorIndex["Erdos, P."];
			queue<int> q;
			q.push(erdosId);
			dist[erdosId] = 0;

			while (!q.empty()) {
				int u = q.front();
				q.pop();

				for (int v : graph[u]) {
					if (dist[v] == -1) {
						dist[v] = dist[u] + 1;
						q.push(v);
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			getline(cin, line);

			if (authorIndex.find(line) == authorIndex.end() || dist[authorIndex[line]] == -1) {
				cout << line << " infinity\n";
			} else {
				cout << line << " " << dist[authorIndex[line]] << '\n';
			}
		}
	}

	return 0;
}
