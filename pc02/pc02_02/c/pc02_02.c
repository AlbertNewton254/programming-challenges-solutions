/* poker hands
 * pc110202
 * uva10315 */

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 40
#define NCARDS 52
#define NSUITS 4

int char_to_value(char c) {
	char *values = "23456789TJQKA";

	for (int i = 0; values[i] != '\0'; i++) {
		if (values[i] == c) {
			return i;
		}
	}

	return -1;
}

int char_to_suit(char c) {
	char *suits = "CDHS";

	for (int i = 0; suits[i] != '\0'; i++) {
		if (suits[i] == c) {
			return i;
		}
	}

	return -1;
}

void count(char *input, int *values_count, int *suits_count) {
	for (int i = 0; i < NCARDS / NSUITS; i++) {
		values_count[i] = 0;
	}
	for (int i = 0; i < NSUITS; i++) {
		suits_count[i] = 0;
	}

	for (int i = 0; i < 15; i += 3) {
		char v = input[i];
		char s = input[i + 1];

		int val = char_to_value(v);
		int suit = char_to_suit(s);

		if (val != -1) {
			values_count[val]++;
		}
		if (suit != -1) {
			suits_count[suit]++;
		}
	}
}

/* Something */

int main(void) {
	char input[MAX_BUFFER_SIZE];

	while (fgets(input, MAX_BUFFER_SIZE, stdin) != NULL) {
		char *last = strchr(input, '\n');
		if (last != NULL) {
			*last = '\0';
		}

		int black_values[NCARDS / NSUITS], black_suits[NSUITS];
		int white_values[NCARDS / NSUITS], white_suits[NSUITS];

		count(input, black_values, black_suits);
		count(input + 15, white_values, white_suits);

		/* Something */
	}

	return 0;
}
