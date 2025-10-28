/**
 * Graphical editor
 * pc110105
 * uva10267
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Image {
private:
	int width;
	int height;
	vector<vector<char>> pixels;

	bool isValidCoordinate(int x, int y) const {
		return x >= 0 && x < width && y >= 0 && y < height;
	}

	void fillRegionRecursive(int x, int y, char originalColor, char newColor) {
		if (!isValidCoordinate(x, y) ||
			pixels[y][x] != originalColor ||
			originalColor == newColor) {
			return;
		}

		pixels[y][x] = newColor;

		fillRegionRecursive(x, y - 1, originalColor, newColor);
		fillRegionRecursive(x, y + 1, originalColor, newColor);
		fillRegionRecursive(x - 1, y, originalColor, newColor);
		fillRegionRecursive(x + 1, y, originalColor, newColor);
	}

public:
	Image(int w, int h) : width(w), height(h) {
		pixels.resize(height, vector<char>(width, 'O'));
	}

	void clear() {
		for (auto &row : pixels) {
			fill(row.begin(), row.end(), 'O');
		}
	}

	void colorPixel(int x, int y, char color) {
		if (isValidCoordinate(x, y)) {
			pixels[y][x] = color;
		}
	}

	void drawVerticalLine(int x, int y1, int y2, char color) {
		int start = min(y1, y2);
		int end = max(y1, y2);

		for (int y = start; y <= end; y++) {
			colorPixel(x, y, color);
		}
	}

	void drawHorizontalLine(int x1, int x2, int y, char color) {
		int start = min(x1, x2);
		int end = max(x1, x2);

		for (int x = start; x <= end; x++) {
			colorPixel(x, y, color);
		}
	}

	void drawRectangle(int x1, int y1, int x2, int y2, char color) {
		int startX = min(x1, x2);
		int endX = max(x1, x2);
		int startY = min(y1, y2);
		int endY = max(y1, y2);

		for (int y = startY; y <= endY; y++) {
			for (int x = startX; x <= endX; x++) {
				colorPixel(x, y, color);
			}
		}
	}

	void fillRegion(int x, int y, char color) {
		if (!isValidCoordinate(x, y)) {
			return;
		}

		char originalColor = pixels[y][x];
		fillRegionRecursive(x, y, originalColor, color);
	}

	void print(const string &filename) const {
		cout << filename << '\n';
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << pixels[i][j];
			}
			cout << '\n';
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	char command;
	Image *image = nullptr;

	while (cin >> command && command != 'X') {
		switch (command) {
			case 'I': {
				int width, height;
				cin >> width >> height;
				delete image;
				image = new Image(width, height);
				break;
			}

			case 'C':
				if (image) {
					image->clear();
				}
				break;

			case 'L': {
				int x, y;
				char color;
				cin >> x >> y >> color;
				if (image) {
					image->colorPixel(x - 1, y - 1, color);
				}
				break;
			}

			case 'V': {
				int x, y1, y2;
				char color;
				cin >> x >> y1 >> y2 >> color;
				if (image) {
					image->drawVerticalLine(x - 1, y1 - 1, y2 - 1, color);
				}
				break;
			}

			case 'H': {
				int x1, x2, y;
				char color;
				cin >> x1 >> x2 >> y >> color;
				if (image) {
					image->drawHorizontalLine(x1 - 1, x2 - 1, y - 1, color);
				}
				break;
			}

			case 'K': {
				int x1, y1, x2, y2;
				char color;
				cin >> x1 >> y1 >> x2 >> y2 >> color;
				if (image) {
					image->drawRectangle(x1 - 1, y1 - 1, x2 - 1, y2 - 1, color);
				}
				break;
			}

			case 'F': {
				int x, y;
				char color;
				cin >> x >> y >> color;
				if (image) {
					image->fillRegion(x - 1, y - 1, color);
				}
				break;
			}

			case 'S': {
				string filename;
				cin >> filename;
				if (image) {
					image->print(filename);
				}
				break;
			}
		}
	}

	delete image;
	return 0;
}