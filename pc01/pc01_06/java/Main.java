import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int testCases = Integer.parseInt(scanner.nextLine());
		scanner.nextLine();

		for (int i = 0; i < testCases; i++) {
			Interpreter interpreter = new Interpreter();
			interpreter.loadProgram(scanner);
			interpreter.executeProgram();

			System.out.println(interpreter.instructionsExecuted);

			if (i < testCases - 1) {
				System.out.println();
			}
		}

		scanner.close();
	}
}
