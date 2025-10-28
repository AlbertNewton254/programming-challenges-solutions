/**
 * Hartals
 * pc110203
 * uva10050
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int T = scanner.nextInt();
        while (T-- > 0) {
            int N = scanner.nextInt();
            int P = scanner.nextInt();

            int[] h = new int[P];
            for (int i = 0; i < P; i++) {
                h[i] = scanner.nextInt();
            }

            Hartals hartals = new Hartals(N, h);
            System.out.println(hartals.calculateHartalDays());
        }

        scanner.close();
    }
}
