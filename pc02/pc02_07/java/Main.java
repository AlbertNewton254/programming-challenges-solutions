/* contests scoreboard
 * pc110207
 * uva10258 */

import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        if (!sc.hasNextInt()) return;
        int T = sc.nextInt();
        sc.nextLine();

        while (T-- > 0) {
            Contestant[] teams = new Contestant[101];
            for (int i = 1; i <= 100; i++) teams[i] = new Contestant();

            while (sc.hasNextLine()) {
                String line = sc.nextLine().trim();
                if (line.isEmpty()) continue;

                String[] parts = line.split("\\s+");
                int t = Integer.parseInt(parts[0]);
                int p = Integer.parseInt(parts[1]);
                int time = Integer.parseInt(parts[2]);
                char verdict = parts[3].charAt(0);

                teams[t].submit(p, time, verdict);
            }

            List<int[]> scoreboard = new ArrayList<>();
            for (int i = 1; i <= 100; i++) {
                if (teams[i].participated) {
                    scoreboard.add(new int[]{i, teams[i].solved, teams[i].penalty});
                }
            }

            scoreboard.sort((a, b) -> {
                if (b[1] != a[1]) return b[1] - a[1];
                if (b[2] != a[2]) return a[2] - b[2];
                return a[0] - b[0];
            });

            for (int[] row: scoreboard) {
              System.out.printf("%d %d %d%n", row[0], row[1], row[2]);
            }

            if (T > 0) System.out.println();
        }

        sc.close();
    }
}
