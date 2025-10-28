/**
 * Hartals
 * pc110203
 * uva10050
 */

public class Hartals {
    private int n;
    private int[] h;

    public Hartals(int n, int[] h) {
        this.n = n;
        this.h = h;
    }

    public int calculateHartalDays() {
        boolean[] days = new boolean[n + 1];
        int hartalDays = 0;

        for (int hartalParam : h) {
            for (int j = hartalParam; j <= n; j += hartalParam) {
                if (j % 7 != 0 && j % 7 != 6) {
                    days[j] = true;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (days[i]) {
                hartalDays++;
            }
        }

        return hartalDays;
    }
}
