"""
Hartals
pc110203
uva10050
"""

import sys


def calculate_hartal_days(n, h):
    """Calculate number of hartal days (excluding weekends)."""
    days = [False] * (n + 1)
    hartal_days = 0

    for hartal_param in h:
        for j in range(hartal_param, n + 1, hartal_param):
            if j % 7 != 0 and j % 7 != 6:
                days[j] = True

    for i in range(1, n + 1):
        if days[i]:
            hartal_days += 1

    return hartal_days


def main():
    T = int(input())

    for _ in range(T):
        N = int(input())
        P = int(input())

        h = []
        for _ in range(P):
            h.append(int(input()))

        print(calculate_hartal_days(N, h))


if __name__ == '__main__':
    main()
