/**
 * Yahtzee
 * pc0208
 * uva10149
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SCORING_CATEGORIES 13
#define TOTAL_ROUNDS 13
#define DICES_PER_ROUND 5
#define DICE_FACES 6
#define MAXIMUM_SCORE 105
#define INPUT_BUFFER_SIZE 1024
#define BITMASK_SIZE (1 << SCORING_CATEGORIES)

int calculate_scores(int dice[DICES_PER_ROUND], int category) {
	int count[DICE_FACES + 1] = {0};

	for (int i = 0; i < DICES_PER_ROUND; i++) {
		count[dice[i]]++;
	}

	switch (category) {
		case 0: /* Ones */
			return count[1] * 1;
		case 1: /* Twos */
			return count[2] * 2;
		case 2: /* Threes */
			return count[3] * 3;
		case 3: /* Fours */
			return count[4] * 4;
		case 4: /* Fives */
			return count[5] * 5;
		case 5: /* Sixes */
			return count[6] * 6;
		case 6: /* Chance */
			{
				int sum = 0;
				for (int i = 0; i < DICES_PER_ROUND; i++) sum += dice[i];
				return sum;
			}
		case 7: /* Three of a kind */
			for (int i = 1; i <= DICE_FACES; i++) {
				if (count[i] >= 3) {
					int sum = 0;
					for (int j = 0; j < DICES_PER_ROUND; j++) sum += dice[j];
					return sum;
				}
			}
			return 0;
		case 8: /* Four of a kind */
			for (int i = 1; i <= DICE_FACES; i++) {
				if (count[i] >= 4) {
					int sum = 0;
					for (int j = 0; j < DICES_PER_ROUND; j++) sum += dice[j];
					return sum;
				}
			}
			return 0;
		case 9: /* Five of a kind */
			for (int i = 1; i <= DICE_FACES; i++) {
				if (count[i] >= 5) {
					return 50;
				}
			}
			return 0;
		case 10: /* Short straight */
			for (int start = 1; start <= 3; start++) {
				if (count[start] >= 1 && count[start + 1] >= 1 && count[start + 2] >= 1 && count[start + 3] >= 1) {
					return 25;
				}
			}
			return 0;
		case 11: /* Long straight */
			if ((count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1) ||
				(count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1 && count[6] >= 1)) {
				return 35;
			}
			return 0;
		case 12: /* Full house */
			{
				int has_three = 0, has_two = 0;
				for (int i = 1; i <= DICE_FACES; i++) {
					if (count[i] == 3) has_three = 1;
					else if (count[i] == 2) has_two = 1;
				}
				return (has_three && has_two) ? 40 : 0;
			}
		default:
			return -1;
	}
}

int main(void) {
	char buf[INPUT_BUFFER_SIZE];
	char game_lines[TOTAL_ROUNDS][INPUT_BUFFER_SIZE];

	while (1) {
		/* Read all 13 lines for a game */
		int valid_game = 1;
		for (int i = 0; i < TOTAL_ROUNDS; i++) {
			if (fgets(buf, INPUT_BUFFER_SIZE, stdin) == NULL) {
				valid_game = 0;
				break;
			}
			strcpy(game_lines[i], buf);
		}
		if (!valid_game) break;

		/* Use dynamic allocation for large arrays */
		int (*dp)[MAXIMUM_SCORE] = malloc(BITMASK_SIZE * sizeof(*dp));
		int (*parent_mask)[MAXIMUM_SCORE] = malloc(BITMASK_SIZE * sizeof(*parent_mask));
		int (*parent_cat)[MAXIMUM_SCORE] = malloc(BITMASK_SIZE * sizeof(*parent_cat));
		int dices[TOTAL_ROUNDS][DICES_PER_ROUND];

		if (!dp || !parent_mask || !parent_cat) {
			fprintf(stderr, "Memory allocation failed\n");
			return 1;
		}

		/* Initialize dp and parent arrays */
		for (int i = 0; i < BITMASK_SIZE; i++) {
			for (int j = 0; j < MAXIMUM_SCORE; j++) {
				dp[i][j] = -1;
				parent_mask[i][j] = -1;
				parent_cat[i][j] = -1;
			}
		}
		dp[0][0] = 0;

		/* Parse dices from stored lines */
		for (int i = 0; i < TOTAL_ROUNDS; i++) {
			char *token = strtok(game_lines[i], " ");
			for (int j = 0; j < DICES_PER_ROUND && token != NULL; j++) {
				dices[i][j] = atoi(token);
				token = strtok(NULL, " ");
			}
		}

		/* Calculate scores */
		int scores[TOTAL_ROUNDS][SCORING_CATEGORIES];
		for (int round = 0; round < TOTAL_ROUNDS; round++) {
			for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
				scores[round][cat] = calculate_scores(dices[round], cat);
			}
		}

		/* Update logic for dp and track best policy */
		for (int mask = 0; mask < BITMASK_SIZE; mask++) {
			int rounds_done = 0;
			for (int i = 0; i < SCORING_CATEGORIES; i++) {
				if (mask & (1 << i)) rounds_done++;
			}

			for (int sum_upper = 0; sum_upper < MAXIMUM_SCORE; sum_upper++) {
				if (dp[mask][sum_upper] == -1) continue;

				for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
					if (mask & (1 << cat)) continue;

					int new_mask = mask | (1 << cat);
					int new_upper = sum_upper;

					if (cat < 6) {
						new_upper += scores[rounds_done][cat];
						if (new_upper >= MAXIMUM_SCORE) continue;
					}

					int new_score = dp[mask][sum_upper] + scores[rounds_done][cat];
					if (new_score > dp[new_mask][new_upper]) {
						dp[new_mask][new_upper] = new_score;
						parent_mask[new_mask][new_upper] = mask;
						parent_cat[new_mask][new_upper] = cat;
					}
				}
			}
		}

		/* Find best result */
		int best_total = 0;
		int best_upper = 0;
		int final_mask = BITMASK_SIZE - 1;

		for (int sum_upper = 0; sum_upper < MAXIMUM_SCORE; sum_upper++) {
			if (dp[final_mask][sum_upper] == -1) continue;

			int bonus = (sum_upper >= 63) ? 35 : 0;
			int total = dp[final_mask][sum_upper] + bonus;

			if (total > best_total) {
				best_total = total;
				best_upper = sum_upper;
			}
		}

		/* Find best policy */
		int category_scores[SCORING_CATEGORIES] = {0};

		int cur_mask = final_mask;
		int cur_upper = best_upper;
		for (int round = TOTAL_ROUNDS - 1; round >= 0; round--) {
			int cat = parent_cat[cur_mask][cur_upper];
			category_scores[cat] = scores[round][cat];

			cur_mask = parent_mask[cur_mask][cur_upper];
			if (cat < 6) {
				cur_upper -= scores[round][cat];
			}
		}

		/* Output */
		for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
			printf("%d ", category_scores[cat]);
		}
		int bonus = (best_upper >= 63) ? 35 : 0;
		printf("%d %d\n", bonus, best_total);

		/* Free memory */
		free(dp);
		free(parent_mask);
		free(parent_cat);
	}

	return 0;
}
