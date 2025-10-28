/**
 * Jolly jumpers
 * pc110201
 * uva10038
 */

public class JollyJumpers {
    private int[] array;

    public JollyJumpers(int[] array) {
        this.array = array;
    }

    public boolean isJolly() {
        int size = array.length;
        boolean[] seenDifferences = new boolean[size - 1];

        for (int i = 0; i < size - 1; i++) {
            int difference = Math.abs(array[i + 1] - array[i]);

            if (difference < 1 || difference > size - 1) {
                return false;
            }

            if (seenDifferences[difference - 1]) {
                return false;
            }

            seenDifferences[difference - 1] = true;
        }

        return true;
    }
}
