/**
 * The trip
 * pc110103
 * uva10137
 */

import java.util.Scanner;
import java.util.Locale;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        scanner.useLocale(Locale.US);

        while (true) {
            int students = scanner.nextInt();
            if (students == 0) break;

            MoneyExchange exchange = new MoneyExchange(students);
            for (int i = 0; i < students; i++) {
                exchange.setMoney(i, scanner.nextDouble());
            }

            System.out.printf("$%.2f%n", exchange.calculateMinimumExchange());
        }

        scanner.close();
    }
}