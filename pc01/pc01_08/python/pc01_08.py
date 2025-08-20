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
