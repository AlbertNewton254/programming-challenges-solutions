"""
Yahtzee
pc110208
uva10149
"""

class YahtzeeSolver:
    def __init__(self):
        self.SCORING_CATEGORIES = 13
        self.TOTAL_ROUNDS = 13
        self.DICES_PER_ROUND = 5
        self.DICE_FACES = 6
        self.MAXIMUM_SCORE = 105
        self.BITMASK_SIZE = (1 << self.SCORING_CATEGORIES)

        self.dp = None
        self.parent_mask = None
        self.parent_cat = None
        self.dices = None
        self.scores = None

    def popcount(self, x):
        return bin(x).count('1')

    def calculate_score(self, dice, category):
        count = [0] * (self.DICE_FACES + 1)

        for value in dice:
            count[value] += 1

        if category == 0:  # Ones
            return count[1] * 1
        elif category == 1:  # Twos
            return count[2] * 2
        elif category == 2:  # Threes
            return count[3] * 3
        elif category == 3:  # Fours
            return count[4] * 4
        elif category == 4:  # Fives
            return count[5] * 5
        elif category == 5:  # Sixes
            return count[6] * 6
        elif category == 6:  # Chance
            return sum(dice)
        elif category == 7:  # Three of a kind
            for i in range(1, self.DICE_FACES + 1):
                if count[i] >= 3:
                    return sum(dice)
            return 0
        elif category == 8:  # Four of a kind
            for i in range(1, self.DICE_FACES + 1):
                if count[i] >= 4:
                    return sum(dice)
            return 0
        elif category == 9:  # Five of a kind
            for i in range(1, self.DICE_FACES + 1):
                if count[i] >= 5:
                    return 50
            return 0
        elif category == 10:  # Short straight
            for start in range(1, 4):
                if all(count[start + i] >= 1 for i in range(4)):
                    return 25
            return 0
        elif category == 11:  # Long straight
            if (all(count[i] >= 1 for i in range(1, 6)) or
                all(count[i] >= 1 for i in range(2, 7))):
                return 35
            return 0
        elif category == 12:  # Full house
            has_three = any(count[i] == 3 for i in range(1, self.DICE_FACES + 1))
            has_two = any(count[i] == 2 for i in range(1, self.DICE_FACES + 1))
            return 40 if (has_three and has_two) else 0
        else:
            return -1

    def initialize_arrays(self):
        # Inicializar arrays 2D com -1
        self.dp = [[-1] * self.MAXIMUM_SCORE for _ in range(self.BITMASK_SIZE)]
        self.parent_mask = [[-1] * self.MAXIMUM_SCORE for _ in range(self.BITMASK_SIZE)]
        self.parent_cat = [[-1] * self.MAXIMUM_SCORE for _ in range(self.BITMASK_SIZE)]
        self.dp[0][0] = 0

    def calculate_all_scores(self):
        self.scores = []
        for round_num in range(self.TOTAL_ROUNDS):
            round_scores = []
            for cat in range(self.SCORING_CATEGORIES):
                round_scores.append(self.calculate_score(self.dices[round_num], cat))
            self.scores.append(round_scores)

    def run_dp(self):
        for mask in range(self.BITMASK_SIZE):
            rounds_done = self.popcount(mask)

            for sum_upper in range(self.MAXIMUM_SCORE):
                if self.dp[mask][sum_upper] == -1:
                    continue

                for cat in range(self.SCORING_CATEGORIES):
                    if mask & (1 << cat):
                        continue

                    new_mask = mask | (1 << cat)
                    new_upper = sum_upper

                    if cat < 6:
                        new_upper += self.scores[rounds_done][cat]
                        if new_upper >= self.MAXIMUM_SCORE:
                            continue

                    new_score = self.dp[mask][sum_upper] + self.scores[rounds_done][cat]
                    if new_score > self.dp[new_mask][new_upper]:
                        self.dp[new_mask][new_upper] = new_score
                        self.parent_mask[new_mask][new_upper] = mask
                        self.parent_cat[new_mask][new_upper] = cat

    def solve(self, input_dices):
        self.dices = input_dices
        self.initialize_arrays()
        self.calculate_all_scores()
        self.run_dp()

        # Find best result
        best_total = 0
        best_upper = 0
        final_mask = self.BITMASK_SIZE - 1

        for sum_upper in range(self.MAXIMUM_SCORE):
            if self.dp[final_mask][sum_upper] == -1:
                continue

            bonus = 35 if sum_upper >= 63 else 0
            total = self.dp[final_mask][sum_upper] + bonus

            if total > best_total:
                best_total = total
                best_upper = sum_upper

        category_scores = [0] * self.SCORING_CATEGORIES
        cur_mask = final_mask
        cur_upper = best_upper

        for round_num in range(self.TOTAL_ROUNDS - 1, -1, -1):
            cat = self.parent_cat[cur_mask][cur_upper]
            category_scores[cat] = self.scores[round_num][cat]
            cur_mask = self.parent_mask[cur_mask][cur_upper]
            if cat < 6:
                cur_upper -= self.scores[round_num][cat]

        # Build result
        result = category_scores.copy()
        bonus = 35 if best_upper >= 63 else 0
        result.append(bonus)
        result.append(best_total)

        return result


def main():
    solver = YahtzeeSolver()

    while True:
        game_dices = []
        valid_game = True

        try:
            for i in range(solver.TOTAL_ROUNDS):
                line = input().strip()
                if not line:
                    valid_game = False
                    break

                dice = list(map(int, line.split()))
                if len(dice) != solver.DICES_PER_ROUND:
                    valid_game = False
                    break

                game_dices.append(dice)

            if not valid_game or len(game_dices) != solver.TOTAL_ROUNDS:
                break

            result = solver.solve(game_dices)
            print(' '.join(map(str, result)))

        except EOFError:
            break


if __name__ == '__main__':
    main()
