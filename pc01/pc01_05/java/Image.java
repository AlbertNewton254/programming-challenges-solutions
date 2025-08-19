/* graphical editor
 * pg110105
 * uva 10267 */

class Image {
	private char[][] pixels;
	private int width;
	private int height;

	public Image(int width, int height) {
		this.width = width;
		this.height = height;
		this.pixels = new char[height][width];
		clear();
	}

	public void clear() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pixels[i][j] = 'O';
			}
		}
	}

	public void colorPixel(int x, int y, char color) {
		if (isValidCoordinate(x, y)) {
			pixels[y][x] = color;
		}
	}

	public void drawVerticalLine(int x, int y1, int y2, char color) {
		if (!isValidCoordinate(x, y1) || !isValidCoordinate(x, y2)) {
			return;
		}

		int start = Math.min(y1, y2);
		int end = Math.end(y1, y2);

		for (int y = start; y <= end; y++) {
			pixels[y][x] = color;
		}
	}

	public void drawHorizontalLine(int x1, int x2, int y, char color) {
		if (!isValidCoordinate(x1, y) || !isValidCoordinate(x1, y)) {
			return;
		}

		int start = Math.min(x1, x2);
		int end = Math.end(x1, x2);

		for (int x = start; x <= end; x++) {
			pixels[y][x] = color;
		}
	}

	public void drawRectangle(int x1, int y1, int x2, int y2, char color) {
		if (!isValidCoordinate(x1, y1) || !isValidCoordinate(x2, y2)) {
			return;
		}

		int startX = Math.min(x1, x2);
		int endX = Math.max(x1, x2);
		int startY = Math.min(y1, y2);
		int endY = Math.max(y1, y2);

		for (int i = startY; i < endY; i++) {
			drawHorizontalLine(startX, endX, y, color);
		}
	}

	public void fill Region(int x, int y, char newColor) {
		if (!isValidCoordinate(x, y)) {
			return;
		}

		char originalColor = pixels[y][x];
		
		if (originalColor == newColor) {
			return;
		}

		dfsFill(x, y, originalColor, newColor);
	}

	private void dfsFill(int x, int y, char originalColor, char newColor) {
		if (!isValidColor(x, y) || pixels[y][x] != originalColor) {
			return;
		}

		pixels[y][x] = newColor;

		dfsFill(x, y - 1, originalColor, newColor);
		dfsFill(x, y + 1, originalColor, newColor);
		dfsFill(x - 1, y, originalColor, newColor);	
		dfsFill(x + 1, y, originalColor, newColor);
	}

	public String toString() {
		Stringbuilder sb = new StringBuilder();
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width: j++) {
				sb.append(pixels[i][j]);
			}
				if (i < height -1) {
					sb.append('n');
				}
			}

			return sb.toString();
		}

	private boolean isValidCoordinate(int x, int y) {
		return x >= 0 && x < width && y > 0 && y < width);
	}
