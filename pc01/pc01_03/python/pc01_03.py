"""
the trip
pc110103
uva10137
"""

import sys
from decimal import Decimal, ROUND_HALF_UP
from typing import List

MAX_STUDENTS = 1000
MAX_MONEY = Decimal('10000.00')

def round_to_cent(value: Decimal) -> Decimal:
    """Round to nearest cent using banker's rounding"""
    return value.quantize(Decimal('0.01'), rounding=ROUND_HALF_UP)

def calculate_exchange(money: List[Decimal], students: int) -> Decimal:
    total = sum(money)
    avg = total / students
    avg_rounded = round_to_cent(avg)
    
    # Amount to be transferred from those who have more
    positive_diff = Decimal('0.00')
    # Amount to be received by those who have less
    negative_diff = Decimal('0.00')
    
    for amount in money:
        diff = round_to_cent(amount - avg_rounded)
        if diff > 0:
            positive_diff += diff
        else:
            negative_diff += -diff
    
    # Cannot generate money, must use minimum amount of transfers
    return min(positive_diff, negative_diff)

def main():
    while True:
        try:
            students = int(input())
            if students == 0:
                break
            
            money = []
            for _ in range(students):
                amount = Decimal(input())
                money.append(round_to_cent(amount))
            
            exchange = calculate_exchange(money, students)
            print(f"${exchange:.2f}")
        
        except (EOFError, ValueError):
            break

if __name__ == '__main__':
    main()