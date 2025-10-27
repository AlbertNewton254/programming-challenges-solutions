import sys

class Contestant:
    def __init__(self, solved=0, penalty=0, participated=False):
        self.solved = solved
        self.penalty = penalty
        self.wrong = [0] * 10
        self.solved_flag = [False] * 10
        self.participated = participated
        return

    def submit(self, problem, time, verdict):
        self.participated = True

        if verdict == 'I':
            if not self.solved_flag[problem]:
                self.wrong[problem] += 1
            return

        elif verdict == 'C':
            if not self.solved_flag[problem]:
                self.solved_flag[problem] = True
                self.solved += 1
                self.penalty += time + 20 * self.wrong[problem]
            return
        return

def main():
    T = int(sys.stdin.readline())

    for _ in range(T):
        teams = [None] + [Contestant() for _ in range(100)]

        for line in sys.stdin:
            line = line.strip()
            if line == '':
                continue

            t, p, time, verdict = line.split()

            t = int(t)
            p = int(p)
            time = int(time)
            teams[t].submit(p, time, verdict)

            participating = [(i, team) for i, team in enumerate(teams[1:], start=1) if team.participated]

            sorted_teams = sorted(
                participating,
                key=lambda x: (-x[1].solved, x[1].penalty, x[0])
            )

        for team_id, team in sorted_teams:
            print(team_id, team.solved, team.penalty)
    return

if __name__ == '__main__':
    main()
