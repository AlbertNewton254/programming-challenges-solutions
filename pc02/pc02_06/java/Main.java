/**
 * Erdos numbers
 * pc110206
 * uva10044
 */

import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.LinkedList;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int T = scanner.nextInt();
        scanner.nextLine();

        boolean isFirst = true;

        while (T-- > 0) {
            if (!isFirst) {
                System.out.println();
            }
            isFirst = false;

            System.out.println("Scenario " + (T + 1));

            int P = scanner.nextInt();
            int N = scanner.nextInt();
            scanner.nextLine();

            ErdosCalculator calculator = new ErdosCalculator();

            for (int i = 0; i < P; i++) {
                String paper = scanner.nextLine();
                calculator.addPaper(paper);
            }

            calculator.calculateDistances();

            for (int i = 0; i < N; i++) {
                String query = scanner.nextLine();
                int distance = calculator.getDistance(query);

                if (distance == -1) {
                    System.out.println(query + " infinity");
                } else {
                    System.out.println(query + " " + distance);
                }
            }
        }

        scanner.close();
    }
}
