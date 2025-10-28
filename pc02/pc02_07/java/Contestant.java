/**
 * Contests scoreboard
 * pc110207
 * uva10258
 */

public class Contestant {
    int solved;
    int penalty;
    boolean participated;
    int[] wrong;
    boolean[] solvedFlag;

    public Contestant() {
        this.solved = 0;
        this.penalty = 0;
        this.participated = false;
        this.wrong = new int[10];
        this.solvedFlag = new boolean[10];
    }

    public void submit(int problem, int time, char verdict) {
        this.participated = true;
        int idx = problem - 1;

        if (verdict == 'I') {
            if (!solvedFlag[idx]) {
                wrong[idx]++;
            }
        } else if (verdict == 'C') {
            if (!solvedFlag[idx]) {
                solvedFlag[idx] = true;
                solved++;
                penalty += time + 20 * wrong[idx];
            }
        }
    }
}
