/**
 * The 3 * n + 1 problem
 * pc110101
 * uva100
 */

import java.util.Arrays;

public class CycleFinder {
    private static final int MAX_NUMBER = 1000000;
    private int[] memo;

    public CycleFinder() {
        memo = new int[MAX_NUMBER + 10];
        Arrays.fill(memo, 0);
        memo[1] = 1;
        collatzLength(MAX_NUMBER);
    }

    private boolean isValidNumber(int number) {
        return (number > 0) && (number < MAX_NUMBER);
    }

    private long nextCollatz(long number) {
        if ((number & 1) == 0) {
            return number >> 1;
        } else {
            return number + (number << 1) + 1;
        }
    }

    private int collatzLength(long number) {
        if (number == 1) {
            return 1;
        }

        if (isValidNumber((int) number) && memo[(int) number] != 0) {
            return memo[(int) number];
        }

        int length = 1 + collatzLength(nextCollatz(number));

        if (isValidNumber((int) number)) {
            memo[(int) number] = length;
        }

        return length;
    }

    public int maxCycleLength(int number1, int number2) {
        if (!isValidNumber(number1) || !isValidNumber(number2)) {
            throw new IllegalArgumentException("Numbers must be between 1 and " + (MAX_NUMBER - 1));
        }

        int start = Math.min(number1, number2);
        int end = Math.max(number1, number2);
        int maxLength = 0;

        for (int number = start; number <= end; number++) {
            maxLength = Math.max(maxLength, collatzLength(number));
        }

        return maxLength;
    }
}