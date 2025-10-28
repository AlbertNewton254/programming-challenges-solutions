"""
the 3 * n + 1 problem
pc110101
uva100
"""

import sys
import time
from typing import Dict, Tuple

MAX_NUMBER = 1000000
memo: Dict[int, int] = {1: 1}

def is_valid_number(number: int) -> bool:
    return 0 < number < MAX_NUMBER

def next_collatz(number: int) -> int:
    if number & 1 == 0:  # even
        return number >> 1
    else:  # odd
        return number + (number << 1) + 1

def collatz_length(number: int) -> int:
    if number == 1:
        return 1
    
    if is_valid_number(number) and number in memo:
        return memo[number]
    
    length = 1 + collatz_length(next_collatz(number))
    
    if is_valid_number(number):
        memo[number] = length
    
    return length

def max_collatz_length(number1: int, number2: int) -> Tuple[int, int, int]:
    start = min(number1, number2)
    end = max(number1, number2)
    max_length = 0
    
    for number in range(start, end + 1):
        max_length = max(max_length, collatz_length(number))
    
    return number1, number2, max_length

def main():
    start_time = time.time()
    
    # Pre-calculate for maximum value
    collatz_length(MAX_NUMBER)
    
    try:
        for line in sys.stdin:
            try:
                number1, number2 = map(int, line.split())
                if not is_valid_number(number1) or not is_valid_number(number2):
                    continue
                
                result = max_collatz_length(number1, number2)
                print(f"{result[0]} {result[1]} {result[2]}")
            
            except ValueError:
                continue
    
    except KeyboardInterrupt:
        sys.exit(0)
    
    end_time = time.time()
    print(f"Time of execution: {end_time - start_time:.6f} seconds", 
          file=sys.stderr)

if __name__ == '__main__':
    main()