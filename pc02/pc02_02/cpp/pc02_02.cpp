/**
 * Poker hands
 * pc110202
 * uva10315
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Card {
	int value;
	int suit;
};

int charToValue(char c) {
	string values = "23456789TJQKA";
	for (int i = 0; i < 13; i++) {
		if (values[i] == c) return i;
	}
	return -1;
}

int charToSuit(char c) {
	string suits = "CDHS";
	for (int i = 0; i < 4; i++) {
		if (suits[i] == c) return i;
	}
	return -1;
}

void parseInputs(const string& input, Card* black, Card* white) {
	for (int i = 0; i < 5; i++) {
		black[i].value = charToValue(input[i * 3]);
		black[i].suit = charToSuit(input[i * 3 + 1]);

		white[i].value = charToValue(input[15 + i * 3]);
		white[i].suit = charToSuit(input[15 + i * 3 + 1]);
	}
}

void sortHand(Card* hand) {
	sort(hand, hand + 5, [](const Card& a, const Card& b) {
		return a.value < b.value;
	});
}

bool isFlush(Card* hand) {
	int suit = hand[0].suit;
	for (int i = 1; i < 5; i++) {
		if (hand[i].suit != suit) return false;
	}
	return true;
}

bool isStraight(Card* hand) {
	for (int i = 1; i < 5; i++) {
		if (hand[i].value != hand[i - 1].value + 1) {
			if (i == 4 &&
				hand[0].value == 0 &&
				hand[1].value == 1 &&
				hand[2].value == 2 &&
				hand[3].value == 3 &&
				hand[4].value == 12) {
				return true;
			}
			return false;
		}
	}
	return true;
}

void getValueCounts(const Card* hand, int* counts) {
	for (int i = 0; i < 13; i++) {
		counts[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		counts[hand[i].value]++;
	}
}

int classifyHand(Card* hand, int* tiebreakers) {
	int counts[13];
	getValueCounts(hand, counts);

	int pairs = 0;
	int three = 0;
	int four = 0;

	int pairValues[2];
	int threeValue = -1;
	int fourValue = -1;

	for (int value = 0; value < 13; value++) {
		if (counts[value] == 4) {
			fourValue = value;
		} else if (counts[value] == 3) {
			threeValue = value;
		} else if (counts[value] == 2) {
			pairValues[pairs++] = value;
		}
	}

	bool flush = isFlush(hand);
	bool straight = isStraight(hand);
	int highest = hand[4].value;

	if (straight && flush) {
		tiebreakers[0] = highest;
		return 8;
	}

	if (fourValue != -1) {
		tiebreakers[0] = fourValue;
		return 7;
	}

	if (threeValue != -1 && pairs == 1) {
		tiebreakers[0] = threeValue;
		return 6;
	}

	if (flush) {
		for (int i = 0; i < 5; i++) {
			tiebreakers[i] = hand[4 - i].value;
		}
		return 5;
	}

	if (straight) {
		tiebreakers[0] = highest;
		return 4;
	}

	if (threeValue != -1) {
		tiebreakers[0] = threeValue;
		return 3;
	}

	if (pairs == 2) {
		if (pairValues[0] > pairValues[1]) {
			tiebreakers[0] = pairValues[0];
			tiebreakers[1] = pairValues[1];
		} else {
			tiebreakers[0] = pairValues[1];
			tiebreakers[1] = pairValues[0];
		}
		for (int i = 4; i >= 0; i--) {
			if (hand[i].value != pairValues[0] && hand[i].value != pairValues[1]) {
				tiebreakers[2] = hand[i].value;
				break;
			}
		}
		return 2;
	}

	if (pairs == 1) {
		tiebreakers[0] = pairValues[0];
		int idx = 1;
		for (int i = 4; i >= 0; i--) {
			if (hand[i].value != pairValues[0]) {
				tiebreakers[idx++] = hand[i].value;
			}
		}
		return 1;
	}

	for (int i = 0; i < 5; i++) {
		tiebreakers[i] = hand[4 - i].value;
	}
	return 0;
}

int compareHands(Card* black, Card* white) {
	int bTie[5] = {0};
	int wTie[5] = {0};

	int bRank = classifyHand(black, bTie);
	int wRank = classifyHand(white, wTie);

	if (bRank < wRank) {
		return 1;
	}

	if (bRank > wRank) {
		return -1;
	}

	for (int i = 0; i < 5; i++) {
		if (bTie[i] > wTie[i]) {
			return 1;
		}

		if (bTie[i] < wTie[i]) {
			return -1;
		}
	}

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string input;
	while (getline(cin, input)) {
		Card black[5];
		Card white[5];
		parseInputs(input, black, white);

		sortHand(black);
		sortHand(white);

		int result = compareHands(black, white);

		switch (result) {
			case 1:
				cout << "Black wins.\n";
				break;
			case -1:
				cout << "White wins.\n";
				break;
			default:
				cout << "Tie.\n";
		}
	}

	return 0;
}
