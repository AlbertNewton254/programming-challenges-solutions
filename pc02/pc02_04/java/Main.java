/**
 * Crypt kicker
 * pc110204
 * uva843
 */

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        scanner.nextLine();

        List<String> dict = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            dict.add(scanner.nextLine());
        }

        while (scanner.hasNextLine()) {
            String crypt = scanner.nextLine();
            if (crypt.isEmpty()) continue;

            CryptKicker kicker = new CryptKicker(dict);
            System.out.println(kicker.solve(crypt));
        }

        scanner.close();
    }
}
