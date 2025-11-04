import java.util.*;

public class YahtzeeSolver {
    private static final int SCORING_CATEGORIES = 13;
    private static final int TOTAL_ROUNDS = 13;
    private static final int DICES_PER_ROUND = 5;
    private static final int DICE_FACES = 6;
    private static final int MAXIMUM_SCORE = 105;
    private static final int BITMASK_SIZE = (1 << SCORING_CATEGORIES);

    private int[][] dp;
    private int[][] parent_mask;
    private int[][] parent_cat;
    private List<List<Integer>> dices;
    private List<List<Integer>> scores;

    public YahtzeeSolver() {
    }

    private int popcount(int x) {
        return Integer.bitCount(x);
    }

    private int calculate_score(List<Integer> dice, int category) {
        int[] count = new int[DICE_FACES + 1];

        for (int value : dice) {
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
                int sum = 0;
                for (int value : dice) sum += value;
                return sum;
            case 7: /* Three of a kind */
                for (int i = 1; i <= DICE_FACES; i++) {
                    if (count[i] >= 3) {
                        sum = 0;
                        for (int value : dice) sum += value;
                        return sum;
                    }
                }
                return 0;
            case 8: /* Four of a kind */
                for (int i = 1; i <= DICE_FACES; i++) {
                    if (count[i] >= 4) {
                        sum = 0;
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
                    if (count[start] >= 1 && count[start + 1] >= 1 &&
                        count[start + 2] >= 1 && count[start + 3] >= 1) {
                        return 25;
                    }
                }
                return 0;
            case 11: /* Long straight */
                if ((count[1] >= 1 && count[2] >= 1 && count[3] >= 1 &&
                    count[4] >= 1 && count[5] >= 1) ||
                    (count[2] >= 1 && count[3] >= 1 && count[4] >= 1 &&
                    count[5] >= 1 && count[6] >= 1)) {
                    return 35;
                }
                return 0;
            case 12: /* Full house */
                boolean has_three = false, has_two = false;
                for (int i = 1; i <= DICE_FACES; i++) {
                    if (count[i] == 3) has_three = true;
                    else if (count[i] == 2) has_two = true;
                }
                return (has_three && has_two) ? 40 : 0;
            default:
                return -1;
        }
    }

    private void initialize_arrays() {
        dp = new int[BITMASK_SIZE][MAXIMUM_SCORE];
        parent_mask = new int[BITMASK_SIZE][MAXIMUM_SCORE];
        parent_cat = new int[BITMASK_SIZE][MAXIMUM_SCORE];

        for (int i = 0; i < BITMASK_SIZE; i++) {
            Arrays.fill(dp[i], -1);
            Arrays.fill(parent_mask[i], -1);
            Arrays.fill(parent_cat[i], -1);
        }
        dp[0][0] = 0;
    }

    private void calculate_all_scores() {
        scores = new ArrayList<>(TOTAL_ROUNDS);
        for (int round = 0; round < TOTAL_ROUNDS; round++) {
            List<Integer> roundScores = new ArrayList<>(SCORING_CATEGORIES);
            for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
                roundScores.add(calculate_score(dices.get(round), cat));
            }
            scores.add(roundScores);
        }
    }

    private void run_dp() {
        for (int mask = 0; mask < BITMASK_SIZE; mask++) {
            int rounds_done = popcount(mask);

            for (int sum_upper = 0; sum_upper < MAXIMUM_SCORE; sum_upper++) {
                if (dp[mask][sum_upper] == -1) continue;

                for (int cat = 0; cat < SCORING_CATEGORIES; cat++) {
                    if ((mask & (1 << cat)) != 0) continue;

                    int new_mask = mask | (1 << cat);
                    int new_upper = sum_upper;

                    if (cat < 6) {
                        new_upper += scores.get(rounds_done).get(cat);
                        if (new_upper >= MAXIMUM_SCORE) continue;
                    }

                    int new_score = dp[mask][sum_upper] + scores.get(rounds_done).get(cat);
                    if (new_score > dp[new_mask][new_upper]) {
                        dp[new_mask][new_upper] = new_score;
                        parent_mask[new_mask][new_upper] = mask;
                        parent_cat[new_mask][new_upper] = cat;
                    }
                }
            }
        }
    }

    public List<Integer> solve(List<List<Integer>> input_dices) {
        this.dices = input_dices;
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

        List<Integer> category_scores = new ArrayList<>(Collections.nCopies(SCORING_CATEGORIES, 0));
        int cur_mask = final_mask;
        int cur_upper = best_upper;

        for (int round = TOTAL_ROUNDS - 1; round >= 0; round--) {
            int cat = parent_cat[cur_mask][cur_upper];
            category_scores.set(cat, scores.get(round).get(cat));
            cur_mask = parent_mask[cur_mask][cur_upper];
            if (cat < 6) {
                cur_upper -= scores.get(round).get(cat);
            }
        }

        /* Build result */
        List<Integer> result = new ArrayList<>();
        result.addAll(category_scores);

        /* Add bonus and total */
        int bonus = (best_upper >= 63) ? 35 : 0;
        result.add(bonus);
        result.add(best_total);

        return result;
    }

}
