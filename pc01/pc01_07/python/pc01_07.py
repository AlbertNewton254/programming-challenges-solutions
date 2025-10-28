"""
check the check
pc110107
uva10196
"""

from typing import List, Tuple, Set
import sys

SIZE = 8  # Board dimension (8x8)

# Movement directions
BLACK_PAWN_DIRS = [(-1, -1), (-1, 1)] + [(0, 0)] * 6
WHITE_PAWN_DIRS = [(1, -1), (1, 1)] + [(0, 0)] * 6
KNIGHT_DIRS = [(-2, -1), (-2, 1), (2, -1), (2, 1),
               (-1, -2), (-1, 2), (1, -2), (1, 2)]
ROOK_DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)] + [(0, 0)] * 4
BISHOP_DIRS = [(-1, -1), (-1, 1), (1, -1), (1, 1)] + [(0, 0)] * 4
QUEEN_DIRS = [(-1, -1), (-1, 0), (-1, 1),
              (0, -1), (0, 1),
              (1, -1), (1, 0), (1, 1)]

class ChessBoard:
    def __init__(self):
        self.board = [['.' for _ in range(SIZE)] for _ in range(SIZE)]
        self.white_king = (-1, -1)
        self.black_king = (-1, -1)
    
    def read_board(self) -> bool:
        is_empty = True
        for i in range(SIZE):
            row = input().strip()
            for j, piece in enumerate(row):
                self.board[i][j] = piece
                if piece != '.':
                    is_empty = False
                if piece == 'K':
                    self.white_king = (i, j)
                elif piece == 'k':
                    self.black_king = (i, j)
        return is_empty
    
    def is_valid_position(self, row: int, col: int) -> bool:
        return 0 <= row < SIZE and 0 <= col < SIZE
    
    def is_attacked_by_piece(self, king_pos: Tuple[int, int], piece_char: str, 
                           directions: List[Tuple[int, int]], repeating: bool) -> bool:
        king_row, king_col = king_pos
        
        for row_dir, col_dir in directions:
            if (row_dir, col_dir) == (0, 0):
                continue
                
            row, col = king_row, king_col
            
            if repeating:
                row += row_dir
                col += col_dir
                while self.is_valid_position(row, col):
                    if self.board[row][col] != '.':
                        if self.board[row][col] == piece_char:
                            return True
                        break
                    row += row_dir
                    col += col_dir
            else:
                row += row_dir
                col += col_dir
                if self.is_valid_position(row, col) and self.board[row][col] == piece_char:
                    return True
        
        return False
    
    def is_in_check(self, is_white: bool) -> bool:
        king_pos = self.white_king if is_white else self.black_king
        pieces = ['p' if is_white else 'P',  # Pawn
                 'n' if is_white else 'N',  # Knight
                 'r' if is_white else 'R',  # Rook
                 'b' if is_white else 'B',  # Bishop
                 'q' if is_white else 'Q',  # Queen
                 'k' if is_white else 'K']  # King
        
        # Check for pawn attacks
        pawn_dirs = BLACK_PAWN_DIRS if is_white else WHITE_PAWN_DIRS
        if self.is_attacked_by_piece(king_pos, pieces[0], pawn_dirs, False):
            return True
        
        # Check for knight attacks
        if self.is_attacked_by_piece(king_pos, pieces[1], KNIGHT_DIRS, False):
            return True
        
        # Check for rook attacks
        if self.is_attacked_by_piece(king_pos, pieces[2], ROOK_DIRS, True):
            return True
        
        # Check for bishop attacks
        if self.is_attacked_by_piece(king_pos, pieces[3], BISHOP_DIRS, True):
            return True
        
        # Check for queen attacks
        if self.is_attacked_by_piece(king_pos, pieces[4], QUEEN_DIRS, True):
            return True
        
        return False

def main():
    game_count = 0
    
    while True:
        chess = ChessBoard()
        if chess.read_board():
            break
        
        game_count += 1
        white_in_check = chess.is_in_check(True)
        black_in_check = chess.is_in_check(False)
        
        print(f"Game #{game_count}:", end=" ")
        if white_in_check:
            print("white king is in check.")
        elif black_in_check:
            print("black king is in check.")
        else:
            print("no king is in check.")

if __name__ == '__main__':
    main()