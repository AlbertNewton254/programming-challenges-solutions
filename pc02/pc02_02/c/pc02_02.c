/**
 * Poker hands
 * pc110202
 * uva10315
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 40

typedef struct {
	int value;
	int suit;
} card_t;

int char_to_value(char c) {
	static char *values = "23456789TJQKA";
	for (int i = 0; values[i] != '\0'; i++) {
		if (values[i] == c) {
			return i;
		}
	}
	return -1;
}

int char_to_suit(char c) {
	static char *suits = "CDHS";
	for (int i = 0; suits[i] != '\0'; i++) {
		if (suits[i] == c) {
			return i;
		}
	}
	return -1;
}

/* Parse 10 cards from input line into black[5] and white[5] */
void parse_inputs(const char *input, card_t *black, card_t *white) {
	/* Each i is a value for a card, black or white */
	for (int i = 0; i < 5; i++) {
		int value_char;
		int suit_char;

		/* First the black cards */
		value_char = input[i * 3];
		suit_char = input[i * 3 + 1];

		black[i].value = char_to_value(value_char);
		black[i].suit = char_to_suit(suit_char);

		/* Then white cards */
		value_char = input[15 + i * 3];
		suit_char = input[15 + i * 3 + 1];

		white[i].value = char_to_value(value_char);
		white[i].suit = char_to_suit(suit_char);
	}
}

/* Bubble sort with early stopping */
void sort_hand(card_t *hand) {
	int changed;

	while (1) {
		changed = 0;

		for (int i = 0; i < 4; i++) {
			if (hand[i].value > hand[i + 1].value) {
				card_t tmp = hand[i];
				hand[i] = hand[i + 1];
				hand[i + 1] = tmp;
				changed = 1;
			}
		}

		if (!changed) {
			break;
		}
	}
}

int is_flush(card_t *hand) {
	int suit = hand[0].suit;
	for (int i = 1; i < 5; i++) {
		if (hand[i].suit != suit) {
			return 0;
		}
	}
	return 1;
}

int is_straight(card_t *hand) {
	for (int i = 1; i < 5; i++) {
		if (hand[i].value != hand[i - 1].value + 1) {
			if (i == 4 &&
				hand[0].value == 0 &&
				hand[1].value == 1 &&
				hand[2].value == 2 &&
				hand[3].value == 3 &&
				hand[4].value == 12) {
				return 1;
			}
			return 0;
		}
	}
	return 1;
}


void get_value_counts(const card_t *hand, int *counts) {
	for (int i = 0; i < 13; i++) {
		counts[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		counts[hand[i].value]++;
	}
}

/* Classify sorted rank, fill tiebreakers */
int classify_hand(card_t *hand, int *tiebreakers) {
	int counts[13];
	get_value_counts(hand, counts);

	int pairs = 0;
	int three = 0;
	int four = 0;

	int pair_values[2];
	int three_value = -1;
	int four_value = -1;

	for (int value = 0; value < 13; value++) {
		if (counts[value] == 4) {
			four_value = value;
		} else if (counts[value] == 3) {
			three_value = value;
		} else if (counts[value] == 2) {
			pair_values[pairs++] = value;
		}
	}

	int flush = is_flush(hand);
	int straight = is_straight(hand);
	int highest = hand[4].value;	/* This assumes sorted hand */

	if (straight && flush) {
		tiebreakers[0] = highest;
		return 8;
	}

	if (four_value != -1) {
		tiebreakers[0] = four_value;
		return 7;
	}

	if (three_value != -1 && pairs == 1) {
		tiebreakers[0] = three_value;
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

	if (three_value != -1) {
		tiebreakers[0] = three_value;
		return 3;
	}

	if (pairs == 2) {
		if (pair_values[0] > pair_values[1]) {
			tiebreakers[0] = pair_values[0];
			tiebreakers[1] = pair_values[1];
		} else {
			tiebreakers[0] = pair_values[1];
			tiebreakers[1] = pair_values[0];
		}
		for (int i = 4; i >= 0; i--) {
			if (hand[i].value != pair_values[0] && hand[i].value != pair_values[1]) {
				tiebreakers[2] = hand[i].value;
				break;
			}
		}
		return 2;
	}

	if (pairs == 1) {
		tiebreakers[0] = pair_values[0];
		int idx = 1;
		for (int i = 4; i >= 0; i--) {
			if (hand[i].value != pair_values[0]) {
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

int compare_hands(card_t *black, card_t *white) {
	int b_tie[5] = {0};
	int w_tie[5] = {0};

	int b_rank = classify_hand(black, b_tie);
	int w_rank = classify_hand(white, w_tie);

	if (b_rank < w_rank) {
		return 1;
	}

	if (b_rank > w_rank) {
		return -1;
	}

	for (int i = 0; i < 5; i++) {
		if (b_tie[i] > w_tie[i]) {
			return 1;
		}

		if (b_tie[i] < w_tie[i]) {
			return -1;
		}
	}

	return 0;
}

int main(void) {
	char input[BUFSIZE];

	while (fgets(input, BUFSIZE, stdin) != NULL) {
		char *last = strchr(input, '\n');
		if (last != NULL) {
			*last = '\0';
		}

		card_t black[5];
		card_t white[5];
		parse_inputs(input, black, white);

		sort_hand(black);
		sort_hand(white);

		int result = compare_hands(black, white);

		switch (result) {
			case 1:
				printf("Black wins.\n");
				break;
			case -1:
				printf("White wins.\n");
				break;
			default:
				printf("Tie.\n");
		}
	}

	return 0;
}
