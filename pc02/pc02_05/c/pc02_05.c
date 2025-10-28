/**
 * Shuffle
 * pc110205
 * uva10026
 */

#include <stdio.h>

#define NSUITS 4
#define NCARDS 13
#define DECK_SIZE (NSUITS * NCARDS)

typedef struct {
	int suit;
	int value;
} card_t;

const char *suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const char *value_names[] = {
	"2", "3", "4", "5", "6", "7", "8", "9", "10",
	"Jack", "Queen", "King", "Ace"
};

int main(void) {
	card_t old_deck[DECK_SIZE];
	card_t new_deck[DECK_SIZE];
	int shuffles[100][DECK_SIZE];

	for (int i = 0; i < DECK_SIZE; i++) {
		old_deck[i].suit = i / NCARDS;
		old_deck[i].value = i % NCARDS;
	}

	int T;
	scanf("%d", &T);

	int is_first = 1;

	while (T--) {
		if (!is_first) {
			printf("\n");
		}
		is_first = 0;

		int n;
		scanf("%d", &n);

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < DECK_SIZE; i++) {
				scanf("%d", &shuffles[k][i]);
			}
		}

		char line[1000];
		fgets(line, sizeof(line), stdin);

		while (fgets(line, sizeof(line), stdin) && line[0] != '\n') {
			int shuffle_idx;
			int offset = 0;

			while (sscanf(line + offset, "%d%n", &shuffle_idx, &offset) == 1) {
				for (int i = 0; i < DECK_SIZE; i++) {
					new_deck[i] = old_deck[shuffles[shuffle_idx - 1][i] - 1];
				}

				for (int i = 0; i < DECK_SIZE; i++) {
					old_deck[i] = new_deck[i];
				}
			}
		}

		for (int i = 0; i < DECK_SIZE; i++) {
			printf("%s of %s\n", value_names[old_deck[i].value],
				suit_names[old_deck[i].suit]);
		}
	}

	return 0;
}
