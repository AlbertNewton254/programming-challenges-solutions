/**
 * Graphical editor
 * pc110105
 * uva10267
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 250

typedef struct {
	int width;
	int height;
	char pixels[MAX_SIZE][MAX_SIZE];
} image_t;

void init_image(image_t *image, int width, int height) {
	image->width = width;
	image->height = height;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			image->pixels[i][j] = 'O';
		}
	}
}

void clear_image(image_t *image) {
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			image->pixels[i][j] = 'O';
		}
	}
}

int is_valid_coordinate(const image_t *image, int x, int y) {
	return (x >= 0 && x < image->width && y >= 0 && y < image->height);
}

void color_pixel(image_t *image, int x, int y, char color) {
	if (is_valid_coordinate(image, x, y)) {
		image->pixels[y][x] = color;
	}
}

void draw_vertical_line(image_t *image, int x, int y1, int y2, char color) {
	int start = (y1 < y2) ? y1 : y2;
	int end = (y1 < y2) ? y2 : y1;

	for (int y = start; y <= end; y++) {
		color_pixel(image, x, y, color);
	}
}

void draw_horizontal_line(image_t *image, int x1, int x2, int y, char color) {
	int start = (x1 < x2) ? x1 : x2;
	int end = (x1 < x2) ? x2 : x1;

	for (int x = start; x <= end; x++) {
		color_pixel(image, x, y, color);
	}
}

void draw_rectangle(image_t *image, int x1, int y1, int x2, int y2, char color) {
	int start_x = (x1 < x2) ? x1 : x2;
	int end_x = (x1 < x2) ? x2 : x1;
	int start_y = (y1 < y2) ? y1 : y2;
	int end_y = (y1 < y2) ? y2 : y1;

	for (int y = start_y; y <= end_y; y++) {
		for (int x = start_x; x <= end_x; x++) {
			color_pixel(image, x, y, color);
		}
	}
}

void fill_region_recursive(image_t *image, int x, int y, char original_color, char new_color) {
	if (!is_valid_coordinate(image, x, y) ||
		image->pixels[y][x] != original_color ||
		original_color == new_color) {
		return;
	}

	image->pixels[y][x] = new_color;

	fill_region_recursive(image, x, y - 1, original_color, new_color);
	fill_region_recursive(image, x, y + 1, original_color, new_color);
	fill_region_recursive(image, x - 1, y, original_color, new_color);
	fill_region_recursive(image, x + 1, y, original_color, new_color);
}

void fill_region(image_t *image, int x, int y, char color) {
	if (!is_valid_coordinate(image, x, y)) {
		return;
	}

	char original_color = image->pixels[y][x];
	fill_region_recursive(image, x, y, original_color, color);
}

void print_image(const image_t *image, const char *filename) {
	printf("%s\n", filename);
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			printf("%c", image->pixels[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	image_t image;
	char command;
	int x, y, x1, y1, x2, y2;
	char color;
	char filename[MAX_SIZE];

	while (scanf(" %c", &command) == 1 && command != 'X') {
		switch (command) {
			case 'I':
				scanf("%d %d", &x, &y);
				init_image(&image, x, y);
				break;

			case 'C':
				clear_image(&image);
				break;

			case 'L':
				scanf("%d %d %c", &x, &y, &color);
				color_pixel(&image, x - 1, y - 1, color);
				break;

			case 'V':
				scanf("%d %d %d %c", &x, &y1, &y2, &color);
				draw_vertical_line(&image, x - 1, y1 - 1, y2 - 1, color);
				break;

			case 'H':
				scanf("%d %d %d %c", &x1, &x2, &y, &color);
				draw_horizontal_line(&image, x1 - 1, x2 - 1, y - 1, color);
				break;

			case 'K':
				scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &color);
				draw_rectangle(&image, x1 - 1, y1 - 1, x2 - 1, y2 - 1, color);
				break;

			case 'F':
				scanf("%d %d %c", &x, &y, &color);
				fill_region(&image, x - 1, y - 1, color);
				break;

			case 'S':
				scanf("%s", filename);
				print_image(&image, filename);
				break;
		}
	}

	return 0;
}