/* lcd display
 * pc110104
 * uva706 */

#include <stdio.h>

#define MAX_NUMBER 99999999
#define MAX_SCALE 10

#define SEG_TOP        0b0000001
#define SEG_TOP_LEFT   0b0000010
#define SEG_TOP_RIGHT  0b0000100
#define SEG_MIDDLE     0b0001000
#define SEG_BOTTOM_LEFT  0b0010000
#define SEG_BOTTOM_RIGHT 0b0100000
#define SEG_BOTTOM     0b1000000

const int NUMBER[10] = {
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

void print_horizontal(int digit, int scale, int segment) {
	putchar(' ');
	for (int i = 0; i < scale; i++) {
		putchar((NUMBER[digit] & segment) ? '-' : ' ');
	}
	putchar(' ');
}

void print_vertical(int digit, int scale, int left_seg, int right_seg) {
	putchar((NUMBER[digit] & left_seg) ? '|' : ' ');
	for (int i = 0; i < scale; i++) {
		putchar(' ');
	}
	putchar((NUMBER[digit] & right_seg) ? '|' : ' ');
}

void print_digits(int number, int scale) {
	int digits[20];
	int length = 0;
	
	if (number == 0) {
		digits[length++] = 0;
	} else {
		while (number > 0) {
			digits[length++] = number % 10;
			number /= 10;
		}
	}
	
	for (int line = 0; line < 2 * scale + 3; line++) {
		for (int d = length-1; d >= 0; d--) {
			int digit = digits[d];
			
			if (line == 0) {
				print_horizontal(digit, scale, SEG_TOP);
			} 
			else if (line > 0 && line < scale + 1) {
				print_vertical(digit, scale, SEG_TOP_LEFT, SEG_TOP_RIGHT);
			}
			else if (line == scale + 1) {
				print_horizontal(digit, scale, SEG_MIDDLE);
			}
			else if (line > scale + 1 && line < 2 * scale + 2) {
				print_vertical(digit, scale, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT);
			}
			else if (line == 2 * scale + 2) {
				print_horizontal(digit, scale, SEG_BOTTOM);
			}
			
			if (d > 0) putchar(' ');
		}
		putchar('\n');
	}
}

int main(void) {
	int scale, number;
	
	while (1) {
		if (scanf("%d %d", &number, &scale) != 2 || (number == 0 && scale == 0)) {
			break;
		}

		if (number < 0 || number > (int) MAX_NUMBER) continue;
		if (scale < 1 || scale > MAX_SCALE) continue;
		
		print_digits(number, scale);
		putchar('\n');
	}
	
	return 0;
}
