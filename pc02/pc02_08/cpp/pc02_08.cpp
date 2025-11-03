/**
 * Yahtzee
 * pc0208
 * uva10149
 */

#include <iostream>
#include <vector>
#include <bit>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;

const int SCORING_CATEGORIES = 13;
const int TOTAL_ROUNDS = 13;
const int DICES_PER_ROUND = 5;
const int DICE_FACES = 6;
const int MAXIMUM_SCORE = 105;
const int INPUT_BUFFER_SIZE = 1024;
const int BITMASK_SIZE = (1 << SCORING_CATEGORIES);

class YahtzeeSolver {
	private:
		vector<vector<int>> dp;
		vector<vector<int>> parent_mask;
		vector<vector<int>> parent_cat;
		vector<vector<int>> dices;
		vector<vector<int>> scores;

		int popcount(unsigned int x) {
			int count = 0;
			while (x) {
				count += x & 1;
				x >>= 1;
			}
			return count;
		}

		int calculate_score(const vector<int>& dice, int category) {
			vector<int> count(DICE_FACES + 1, 0);

			for (int value: dice) {
				count[value]++;
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
						for (int value : dice) sum += value;
						return sum;
					}
				case 7: /* Three of a kind */
					for (int i = 1; i <= DICE_FACES; i++) {
						if (count[i] >= 3) {
							int sum = 0;
							for (int value : dice) sum += value;
							return sum;
						}
					}
					return 0;
				case 8: /* Four of a kind */
					for (int i = 1; i <= DICE_FACES; i++) {
						if (count[i] >= 4) {
							int sum = 0;
							for (int value : dice) sum += value;
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
						bool has_three = false, has_two = false;
						for (int i = 1; i <= DICE_FACES; i++) {
							if (count[i] == 3) has_three = true;
							else if (count[i] == 2) has_two = true;
						}
						return (has_three && has_two) ? 40 : 0;
					}
				default:
					return -1;
			}
		}

		void initialize_arrays() {
			dp.assign(BITMASK_SIZE, vector<int>(MAXIMUM_SCORE, -1));
			parent_mask.assign(BITMASK_SIZE, vector<int>(MAXIMUM_SCORE, -1));
			parent_cat.assign(BITMASK_SIZE, vector<int>(MAXIMUM_SCORE, -1));
			dp[0][0] = 0;
		}

		void calculate_all_scores() {
			scores.assign(TOTAL_ROUNDS, vector<int>(SCORING_CATEGORIES));
			for (int round = 0; round < TOTAL_ROUNDS; round++) {
				for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
					scores[round][cat] = calculate_score(dices[round], cat);
				}
			}
		}

		void run_dp() {
			for (int mask = 0; mask < BITMASK_SIZE; mask++) {
				int rounds_done = popcount(mask);

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
		}

	public:
		vector<int> solve(const vector<vector<int>>& input_dices) {
			dices = input_dices;
			initialize_arrays();
			calculate_all_scores();
			run_dp();

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

			vector<int> category_scores(SCORING_CATEGORIES, 0);
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

			// Build result without copying to avoid bounds warnings
			vector<int> result;
			result.reserve(SCORING_CATEGORIES + 2); // Pre-allocate for 15 elements

			// Add category scores
			for (int score : category_scores) {
				result.push_back(score);
			}

			// Add bonus and total
			int bonus = (best_upper >= 63) ? 35 : 0;
			result.push_back(bonus);
			result.push_back(best_total);

			return result;
		}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	YahtzeeSolver solver;
	string line;

	while (true) {
		vector<vector<int>> game_dices;
		bool valid_game = true;

		for (int i = 0; i < TOTAL_ROUNDS; i++) {
			if (!getline(cin, line)) {
				valid_game = false;
				break;
			}

			vector<int> dice(DICES_PER_ROUND);
			stringstream ss(line);
			for (int j = 0; j < DICES_PER_ROUND; j++) {
				if (!(ss >> dice[j])) {
					valid_game = false;
					break;
				}
			}

			if (!valid_game) break;
			game_dices.push_back(dice);
		}

		if (!valid_game || game_dices.size() != TOTAL_ROUNDS) break;

		vector<int> result = solver.solve(game_dices);

		for (size_t i = 0; i < result.size(); i++) {
			cout << result[i];
			if (i < result.size() - 1) cout << " ";
		}
		cout << '\n';
	}

	return 0;
}
