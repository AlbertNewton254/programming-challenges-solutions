"""
Shuffle
pc110205
uva10026
"""

import sys


def main():
    """Main function to process card shuffles."""
    lines = sys.stdin.readlines()

    T = int(lines[0].strip())
    line_idx = 1

    suit_names = ["Clubs", "Diamonds", "Hearts", "Spades"]
    value_names = ["2", "3", "4", "5", "6", "7", "8", "9", "10",
                   "Jack", "Queen", "King", "Ace"]

    first = True

    for _ in range(T):
        if not first:
            print()
        first = False

        n = int(lines[line_idx].strip())
        line_idx += 1

        shuffles = []
        for _ in range(n):
            shuffle = list(map(int, lines[line_idx].strip().split()))
            shuffles.append(shuffle)
            line_idx += 1

        old_deck = [(i // 13, i % 13) for i in range(52)]
        new_deck = old_deck[:]

        while line_idx < len(lines):
            line = lines[line_idx].strip()
            line_idx += 1

            if not line:
                break

            shuffle_indices = list(map(int, line.split()))
            for shuffle_idx in shuffle_indices:
                new_deck = []
                for i in range(52):
                    pos = shuffles[shuffle_idx - 1][i] - 1
                    new_deck.append(old_deck[pos])

                old_deck = new_deck

        for suit, value in old_deck:
            print(f"{value_names[value]} of {suit_names[suit]}")


if __name__ == '__main__':
    main()
