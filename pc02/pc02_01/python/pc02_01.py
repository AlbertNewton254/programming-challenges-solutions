"""
Jolly jumpers
pc110201
uva10038
"""

import sys


def is_jolly(array):
    """
    Check if array is jolly (all consecutive differences are distinct and in [1, n-1])
    """
    size = len(array)
    seen_differences = [False] * (size - 1)

    for i in range(size - 1):
        difference = abs(array[i + 1] - array[i])

        if difference < 1 or difference > size - 1:
            return False

        if seen_differences[difference - 1]:
            return False

        seen_differences[difference - 1] = True

    return True


def main():
    for line in sys.stdin:
        parts = line.strip().split()
        if not parts:
            continue

        size = int(parts[0])
        if size == 0:
            continue

        array = list(map(int, parts[1:]))

        if is_jolly(array):
            print("Jolly")
        else:
            print("Not jolly")


if __name__ == '__main__':
    main()
