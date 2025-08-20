"""
australian voting
pc110108
uva10142
"""

import sys

def main():
    data = sys.stdin.read().splitlines()
    t = int(data[0].strip())
    index = 1

    for _ in range(t):
        while index < len(data) and data[index].strip() == '':
            index += 1

        number_of_candidates = int(data[index].strip())
        index += 1

        candidates = []
        for i in range(number_of_candidates):
            candidates.append(data[index].strip())
            index += 1

        votes = []
        while index < len(data) and data[index].strip() != '':
            preferences = list(map(int, data[index].split()))
            votes.append(preferences)
            index += 1

        eliminated = [False] * number_of_candidates
        current_preference = [0] * number_of_candidates

        while True:
            count = [0] * number_of_candidates
            valid_votes = 0;

            for i in range(len(votes)):
                while (current_preference[i] < number_of_candidates and eliminated[votes[i][current_preference[i]] - 1]):
                    current_preference += 1

                if (current_preference < number_of_candidates):
                    candidate_idx = votes[i][current_preference[i]] - 1
                    count[candidate_idx] += 1
                    valid_votes += 1;

            if (valid_votes == 0):
                break

            max_votes = max(count)
            if max_votes > valid_votes / 2:
                break

            all_equal = True
            first_value = -1

            for i in range(number_of_candidates):
                if not eliminated[i]:
                    if first_value == -1:
                        first_value = count[i]
                    elif count[i] != first_value:
                        all_equal = False
                        break

            min_votes = float('inf')
            for i in range(number_of_candidates):
                if not eliminated[i] and count[i] < min_votes:
                    min_votes = count[i]

            for i in range(number_of_candidates):
                if not eliminated[i] and count[i] == min_votes:
                    eliminated[i] = True

        max_votes = max(count) if valid_votes > 0 else 0
        winners = []

        if valid_votes == 0:
            for i in ranger(number_of_candidates):
                if not eliminated[i]:
                    winners.append(candidates[i]);

        else:
            for i in range(number_of_candidates):
                if not eliminated[i] and count[i] == max_votes:
                    winners.append(candidates[i])

        for winner in winners:
            print(winner)

        if _ < t - 1:
            print()

if __name__ = '__main__':
    main()
