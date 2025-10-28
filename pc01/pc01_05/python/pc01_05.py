"""
graphical editor
pc110105
uva10267
"""

from typing import List, Tuple
import sys

class Image:
    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.pixels = [['O'] * width for _ in range(height)]
    
    def is_valid_coordinate(self, x: int, y: int) -> bool:
        return 0 <= x < self.width and 0 <= y < self.height
    
    def clear(self) -> None:
        for y in range(self.height):
            for x in range(self.width):
                self.pixels[y][x] = 'O'
    
    def color_pixel(self, x: int, y: int, color: str) -> None:
        if self.is_valid_coordinate(x, y):
            self.pixels[y][x] = color
    
    def draw_vertical_line(self, x: int, y1: int, y2: int, color: str) -> None:
        start = min(y1, y2)
        end = max(y1, y2)
        
        for y in range(start, end + 1):
            self.color_pixel(x, y, color)
    
    def draw_horizontal_line(self, x1: int, x2: int, y: int, color: str) -> None:
        start = min(x1, x2)
        end = max(x1, x2)
        
        for x in range(start, end + 1):
            self.color_pixel(x, y, color)
    
    def draw_rectangle(self, x1: int, y1: int, x2: int, y2: int, color: str) -> None:
        start_x = min(x1, x2)
        end_x = max(x1, x2)
        start_y = min(y1, y2)
        end_y = max(y1, y2)
        
        for y in range(start_y, end_y + 1):
            for x in range(start_x, end_x + 1):
                self.color_pixel(x, y, color)
    
    def _fill_region_recursive(self, x: int, y: int, original_color: str, new_color: str) -> None:
        if (not self.is_valid_coordinate(x, y) or 
            self.pixels[y][x] != original_color or 
            original_color == new_color):
            return
        
        self.pixels[y][x] = new_color
        
        # Fill in all four directions
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            self._fill_region_recursive(x + dx, y + dy, original_color, new_color)
    
    def fill_region(self, x: int, y: int, color: str) -> None:
        if not self.is_valid_coordinate(x, y):
            return
        
        original_color = self.pixels[y][x]
        self._fill_region_recursive(x, y, original_color, color)
    
    def print(self, filename: str) -> None:
        print(filename)
        for row in self.pixels:
            print(''.join(row))

def main():
    image = None
    
    for line in sys.stdin:
        command = line.strip()
        if not command:
            continue
        
        parts = command.split()
        cmd = parts[0]
        
        if cmd == 'X':
            break
        
        elif cmd == 'I':
            width, height = map(int, parts[1:])
            image = Image(width, height)
        
        elif cmd == 'C':
            if image:
                image.clear()
        
        elif cmd == 'L':
            if image:
                x, y = map(int, parts[1:3])
                color = parts[3]
                image.color_pixel(x - 1, y - 1, color)
        
        elif cmd == 'V':
            if image:
                x, y1, y2 = map(int, parts[1:4])
                color = parts[4]
                image.draw_vertical_line(x - 1, y1 - 1, y2 - 1, color)
        
        elif cmd == 'H':
            if image:
                x1, x2, y = map(int, parts[1:4])
                color = parts[4]
                image.draw_horizontal_line(x1 - 1, x2 - 1, y - 1, color)
        
        elif cmd == 'K':
            if image:
                x1, y1, x2, y2 = map(int, parts[1:5])
                color = parts[5]
                image.draw_rectangle(x1 - 1, y1 - 1, x2 - 1, y2 - 1, color)
        
        elif cmd == 'F':
            if image:
                x, y = map(int, parts[1:3])
                color = parts[3]
                image.fill_region(x - 1, y - 1, color)
        
        elif cmd == 'S':
            if image:
                filename = parts[1]
                image.print(filename)

if __name__ == '__main__':
    main()