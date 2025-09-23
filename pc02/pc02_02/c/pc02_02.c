/* poker hands
 * pc110202
 * uva10315 */

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 40
#define NCARDS 52
#define NSUITS 4

/* structure to handle poker cards */
typedef struct {
	int value;
	int suit;
} Card;

/* input: char c as poker value
 * output: c increasing order between poker values */
int char_to_value(char c) {
	char *values = "23456789TJQKA";

	for (int i = 0; values[i] != '\0'; i++) {
		if (values[i] == c) {
			return i;
		}
	}

	return -1;
}

/* input: char c as poker suit
 * output: c increasing order between poker suits */
int char_to_suit(char c) {
	char *suits = "CDHS";

	for (int i = 0; suits[i] != '\0'; i++) {
		if (suits[i] == c) {
			return i;
		}
	}

	return -1;
}

/* input: char array input, card arrays black and white
 * parse input into black and white */
void parse_inputs(char *input, Card *black, Card *white) {
	for (int i = 0; i < 5; i++) {
		char value_char = input[i * 3];
		char suit_char = input[i * 3 + 1];

		black[i].value = char_to_value(value_char);
		black[i].suit = char_to_suit(suit_char);

		value_char = input[15 + i * 3];
		suit_char = input[15 + i * 3 + 1];

		white[i].value = char_to_value(value_char);
		white[i].suit = char_to_suit(suit_char);
	}
}

/* sort a card array */
void sort_hand(Card *hand) {
	/* Something */
	return;
}

int main(void) {
	char input[MAX_BUFFER_SIZE];

	while (fgets(input, MAX_BUFFER_SIZE, stdin) != NULL) {
		char *last = strchr(input, '\n');
		if (last != NULL) {
			*last = '\0';
		}

		Card black[5], white[5];

		parse_inputs(input, black, white);

		 /* sort black and white
		 * decide black and white hand types
		 * compare
		 * while still able to compare 
		 * if no tie somewhere break */
	}

	return 0;
}
