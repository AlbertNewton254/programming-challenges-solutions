"""
Contests scoreboard
pc110207
uva10258
"""

import sys


class Contestant:
    """Represents a contest contestant."""

    def __init__(self):
        self.solved = 0
        self.penalty = 0
        self.participated = False
        self.wrong = [0] * 10
        self.solvedFlag = [False] * 10

    def submit(self, problem, time, verdict):
        """Process a submission."""
        self.participated = True

        if verdict == 'I':
            if not self.solvedFlag[problem]:
                self.wrong[problem] += 1
        elif verdict == 'C':
            if not self.solvedFlag[problem]:
                self.solvedFlag[problem] = True
                self.solved += 1
                self.penalty += time + 20 * self.wrong[problem]


def main():
    T = int(sys.stdin.readline())

    first = True

    for _ in range(T):
        if not first:
            print()
        first = False

        teams = [Contestant() for _ in range(101)]

        for line in sys.stdin:
            line = line.strip()
            if not line:
                break

            parts = line.split()
            t = int(parts[0])
            p = int(parts[1])
            time = int(parts[2])
            verdict = parts[3]

            teams[t].submit(p, time, verdict)

        scoreboard = []
        for i in range(1, 101):
            if teams[i].participated:
                scoreboard.append((i, teams[i].solved, teams[i].penalty))

        scoreboard.sort(key=lambda x: (-x[1], x[2], x[0]))

        for team_id, solved, penalty in scoreboard:
            print(f"{team_id} {solved} {penalty}")


if __name__ == '__main__':
    main()
