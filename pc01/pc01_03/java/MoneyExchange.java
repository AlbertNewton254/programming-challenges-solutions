/**
 * The trip
 * pc110103
 * uva10137
 */

public class MoneyExchange {
    private static final int MAX_STUDENTS = 1000;
    private static final double MAX_MONEY = 10000.00;
    private final double[] money;
    private final int students;

    public MoneyExchange(int students) {
        if (students <= 0 || students > MAX_STUDENTS) {
            throw new IllegalArgumentException("Number of students must be between 1 and " + MAX_STUDENTS);
        }
        this.students = students;
        this.money = new double[MAX_STUDENTS];
    }

    public void setMoney(int student, double amount) {
        if (student < 0 || student >= students) {
            throw new IllegalArgumentException("Invalid student index");
        }
        if (amount < 0 || amount > MAX_MONEY) {
            throw new IllegalArgumentException("Amount must be between 0 and " + MAX_MONEY);
        }
        money[student] = roundToCent(amount);
    }

    private static double roundToCent(double value) {
        return Math.round(value * 100.0) / 100.0;
    }

    public double calculateMinimumExchange() {
        double total = 0.0;
        for (int i = 0; i < students; i++) {
            total += money[i];
        }

        double avg = total / students;
        double avgRounded = roundToCent(avg);

        double positiveDiff = 0.0;
        double negativeDiff = 0.0;

        for (int i = 0; i < students; i++) {
            double diff = money[i] - avgRounded;
            diff = roundToCent(diff);
            if (diff > 0) {
                positiveDiff += diff;
            } else {
                negativeDiff += -diff;
            }
        }

        return Math.min(positiveDiff, negativeDiff);
    }
}