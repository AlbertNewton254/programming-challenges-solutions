/**
 * Shuffle
 * pc110205
 * uva10026
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#define NSUITS 4
#define NCARDS 13

enum Suit {
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

enum Value {
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

string suitName[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
string valueName[] = {
	"2", "3", "4", "5", "6", "7", "8", "9", "10",
	"Jack", "Queen", "King", "Ace"
};


struct Card {
	Suit suit;
	Value value;
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<Card> oldDeck(NSUITS * NCARDS);
	vector<Card> newDeck(NSUITS * NCARDS);
	vector<vector<int>> shuffles(100, vector<int>(52));

	for (int i = 0; i < NSUITS * NCARDS; i++) {
		oldDeck[i].suit = static_cast<Suit>(i / NCARDS);
		oldDeck[i].value = static_cast<Value>(i % NCARDS);
	}

	newDeck = oldDeck;

	int T;

	cin >> T;

	bool isFirst = true;

	while (T--) {
		if (!isFirst) {
			cout << '\n';
		}

		isFirst = false;

		int n;
		cin >> n;

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < NSUITS * NCARDS; i++) {
				cin >> shuffles[k][i];
			}
		}

		cin.ignore();

		string line;
		while (getline(cin, line) && !line.empty()) {
			stringstream ss(line);
			int shuffleIdx;

			while (ss >> shuffleIdx) {
				for (int i = 0; i < NSUITS * NCARDS; i++) {
					newDeck[i] = oldDeck[shuffles[shuffleIdx - 1][i] - 1];
				}

				oldDeck.swap(newDeck);
			}
		}

		for (int i = 0; i < NSUITS * NCARDS; i++) {
			cout << valueName[oldDeck[i].value] << " of "
				<< suitName[oldDeck[i].suit] << '\n';
		}
	}

	return 0;
}
