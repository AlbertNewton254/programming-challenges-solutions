/**
 * LCD display
 * pc110104
 * uva706
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            int scale = scanner.nextInt();
            int number = scanner.nextInt();

            if (scale == 0 && number == 0) break;

            try {
                LCDDisplay display = new LCDDisplay(number, scale);
                System.out.print(display.toString());
                System.out.println();
            } catch (IllegalArgumentException e) {
                continue;
            }
        }

        scanner.close();
    }
}