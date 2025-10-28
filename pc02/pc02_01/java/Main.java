/**
 * Jolly jumpers
 * pc110201
 * uva10038
 */

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextInt()) {
            int size = scanner.nextInt();
            int[] array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = scanner.nextInt();
            }

            JollyJumpers jumpers = new JollyJumpers(array);
            if (jumpers.isJolly()) {
                System.out.println("Jolly");
            } else {
                System.out.println("Not jolly");
            }
        }

        scanner.close();
    }
}
