import java.util.Scanner;

public class Main {
	private static Image image;

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		while (scanner.hasNext()) {
			String command = scanner.next();

			if (command.equals("X")) {
				break;
			}

			switch (command) {
				case "I":
					int cols = scanner.nextInt();
					int rows = scanner.nextInt();

					image = new Image(rows, cols);
					break;

				case "C":
					if (image != null) {
						image.clear();
					}
					break;

				case "L":
					if (image != null) {
						int x = scanner.nextInt() - 1;
						int y = scanner.nextInt() - 1;
						char color = scanner.next().charAt(0);

						image.colorPixel(x, y, color);
					}
					break;

				case "V":
					if (image != null) {
						int x = scanner.nextInt() - 1;
						int y1 = scanner.nextInt() - 1;
						int y2 = scanner.nextInt() - 1;
						char color = scanner.next().charAt(0);

						image.drawVerticalLine(x, y1, y2, color);
					}
					break;

				case "H":
					if (image != null) {
						int x1 = scanner.nextInt() - 1;
						int x2 = scanner.nextInt() - 1;
						int y = scanner.nextInt() - 1;
						char color = scanner.next().charAt(0);

						image.drawVerticalLine(x1, x2, y, color);
					}
					break;

				case "K":
					if (image != null) {
						int x1 = scanner.nextInt() - 1;
						int x2 = scanner.nextInt() - 1;
						int y1 = scanner.nextInt() - 1;
						int y2 = scanner.nextInt() - 1;
						char color = scanner.next().charAt(0);

						image.drawRectangle(x1, x2, y1, y2, color);
					}
					break;

				case "F":
					if (image != null) {
						int x = scanner.nextInt() - 1;
						int y = scanner.nextInt() - 1;
						char color = scanner.next().charAt(0);

						image.fillRegion(x, y, color);
					}
					break;
			}
		}
	}
}
