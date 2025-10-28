"""
lcd display
pc110104
uva706
"""

from typing import List
import sys

MAX_NUMBER = 99999999
MAX_SCALE = 10

# LCD segments as bit flags
SEG_TOP          = 0b0000001
SEG_TOP_LEFT     = 0b0000010
SEG_TOP_RIGHT    = 0b0000100
SEG_MIDDLE       = 0b0001000
SEG_BOTTOM_LEFT  = 0b0010000
SEG_BOTTOM_RIGHT = 0b0100000
SEG_BOTTOM       = 0b1000000

NUMBER = [
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
]

def print_horizontal(digit: int, scale: int, segment: int) -> str:
    return ' ' + ('-' if NUMBER[digit] & segment else ' ') * scale + ' '

def print_vertical(digit: int, scale: int, left_seg: int, right_seg: int) -> str:
    return ('|' if NUMBER[digit] & left_seg else ' ') + ' ' * scale + ('|' if NUMBER[digit] & right_seg else ' ')

def get_digits(number: int) -> List[int]:
    if number == 0:
        return [0]
    
    digits = []
    while number > 0:
        digits.append(number % 10)
        number //= 10
    return digits[::-1]

def print_digits(number: int, scale: int) -> None:
    digits = get_digits(number)
    
    for line in range(2 * scale + 3):
        parts = []
        for digit in digits:
            if line == 0:
                parts.append(print_horizontal(digit, scale, SEG_TOP))
            elif 0 < line < scale + 1:
                parts.append(print_vertical(digit, scale, SEG_TOP_LEFT, SEG_TOP_RIGHT))
            elif line == scale + 1:
                parts.append(print_horizontal(digit, scale, SEG_MIDDLE))
            elif scale + 1 < line < 2 * scale + 2:
                parts.append(print_vertical(digit, scale, SEG_BOTTOM_LEFT, SEG_BOTTOM_RIGHT))
            elif line == 2 * scale + 2:
                parts.append(print_horizontal(digit, scale, SEG_BOTTOM))
        
        print(' '.join(parts))

def main():
    while True:
        try:
            scale, number = map(int, input().split())
            if scale == number == 0:
                break
            
            if not (0 <= number <= MAX_NUMBER and 1 <= scale <= MAX_SCALE):
                continue
                
            print_digits(number, scale)
            print()
            
        except EOFError:
            break

if __name__ == '__main__':
    main()