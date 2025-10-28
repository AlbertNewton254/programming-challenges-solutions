/**
 * LCD display
 * pc110104
 * uva706
 */

import java.util.ArrayList;

public class LCDDisplay {
    private static final int MAX_NUMBER = 99999999;
    private static final int MAX_SCALE = 10;

    private static final int SEG_TOP          = 0b0000001;
    private static final int SEG_TOP_LEFT     = 0b0000010;
    private static final int SEG_TOP_RIGHT    = 0b0000100;
    private static final int SEG_MIDDLE       = 0b0001000;
    private static final int SEG_BOTTOM_LEFT  = 0b0010000;
    private static final int SEG_BOTTOM_RIGHT = 0b0100000;
    private static final int SEG_BOTTOM       = 0b1000000;

    private static final int[] NUMBER = {
        SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
        SEG_TOP_RIGHT | SEG_BOTTOM_RIGHT,
        SEG_TOP | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM,
        SEG_TOP | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
        SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT,
        SEG_TOP | SEG_TOP_LEFT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_TOP_LEFT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_TOP_RIGHT | SEG_BOTTOM_RIGHT,
        SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_LEFT | SEG_BOTTOM_RIGHT | SEG_BOTTOM,
        SEG_TOP | SEG_TOP_LEFT | SEG_TOP_RIGHT | SEG_MIDDLE | SEG_BOTTOM_RIGHT | SEG_BOTTOM
    };

    private final int number;
    private final int scale;

    public LCDDisplay(int number, int scale) {
        if (number < 0 || number > MAX_NUMBER) {
            throw new IllegalArgumentException("Number must be between 0 and " + MAX_NUMBER);
        }
        if (scale < 1 || scale > MAX_SCALE) {
            throw new IllegalArgumentException("Scale must be between 1 and " + MAX_SCALE);
        }
        this.number = number;
        this.scale = scale;
    }

    private void printHorizontal(StringBuilder sb, int digit, int segment) {
        sb.append(' ');
        for (int i = 0; i < scale; i++) {
            sb.append((NUMBER[digit] & segment) != 0 ? '-' : ' ');
        }
        sb.append(' ');
    }

    private void printVertical(StringBuilder sb, int digit, int leftSeg, int rightSeg) {
        sb.append((NUMBER[digit] & leftSeg) != 0 ? '|' : ' ');
        for (int i = 0; i < scale; i++) {
            sb.append(' ');
        }
        sb.append((NUMBER[digit] & rightSeg) != 0 ? '|' : ' ');
    }

    public String toString() {
        ArrayList<Integer> digits = new ArrayList<>();
        int n = number;

        if (n == 0) {
            digits.add(0);
        } else {
            while (n > 0) {
                digits.add(0, n % 10);
                n /= 10;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int line = 0; line < 2 * scale + 3; line++) {
            for (int d = 0; d < digits.size(); d++) {
                int digit = digits.get(d);

                if (line == 0) {
                    printHorizontal(sb, digit, SEG_TOP);
                } else if (line > 0 && line < scale + 1) {
                    printVertical(sb, digit, SEG_TOP_LEFT, SEG_TOP_RIGHT);
                } else if (line == scale + 1) {
                    printHorizontal(sb, digit, SEG_MIDDLE);
                } else if (line > scale + 1 && line < 2 * scale + 2) {
                    printVertical(sb, digit, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
                } else if (line == 2 * scale + 2) {
                    printHorizontal(sb, digit, SEG_BOTTOM);
                }

                if (d < digits.size() - 1) {
                    sb.append(' ');
                }
            }
            sb.append('\n');
        }
        return sb.toString();
    }
}