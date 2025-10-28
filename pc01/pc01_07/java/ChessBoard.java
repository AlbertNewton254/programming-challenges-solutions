/**
 * Check the check
 * pc110107
 * uva10196
 */

import java.util.Scanner;

class ChessBoard {
    private static final int SIZE = 8;

    private static final int[][] BLACK_PAWN_DIRS = {
        {-1, -1}, {-1, 1},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };

    private static final int[][] WHITE_PAWN_DIRS = {
        {1, -1}, {1, 1},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };

    private static final int[][] KNIGHT_DIRS = {
        {-2, -1}, {-2, 1},
        {2, -1}, {2, 1},
        {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}
    };

    private static final int[][] ROOK_DIRS = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };

    private static final int[][] BISHOP_DIRS = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1},
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };

    private static final int[][] QUEEN_DIRS = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    private char[][] board;
    private Position whiteKing;
    private Position blackKing;
    private Scanner scanner;
    
    private static class Position {
        int row, col;

        Position(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    public ChessBoard() {
        board = new char[SIZE][SIZE];
        scanner = new Scanner(System.in);
    }

    private boolean isValidPosition(int row, int col) {
        return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
    }

    private boolean readBoard() {
        boolean isEmpty = true;

        for (int i = 0; i < SIZE; i++) {
            String line = scanner.nextLine();
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = line.charAt(j);
                if (board[i][j] != '.') {
                    isEmpty = false;
                }
                if (board[i][j] == 'K') {
                    whiteKing = new Position(i, j);
                } else if (board[i][j] == 'k') {
                    blackKing = new Position(i, j);
                }
            }
        }

        return isEmpty;
    }

    private boolean isAttackedByPiece(Position kingPos, char pieceChar, int[][] dirs, boolean repeating) {
        for (int[] dir : dirs) {
            int rowDir = dir[0];
            int colDir = dir[1];

            if (rowDir == 0 && colDir == 0) continue;

            int row = kingPos.row;
            int col = kingPos.col;

            if (repeating) {
                row += rowDir;
                col += colDir;
                while (isValidPosition(row, col)) {
                    if (board[row][col] != '.') {
                        if (board[row][col] == pieceChar) {
                            return true;
                        }
                        break;
                    }
                    row += rowDir;
                    col += colDir;
                }
            } else {
                row += rowDir;
                col += colDir;
                if (isValidPosition(row, col) && board[row][col] == pieceChar) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean isInCheck(boolean isWhite) {
        Position kingPos = isWhite ? whiteKing : blackKing;
        char[] pieces = {
            isWhite ? 'p' : 'P',
            isWhite ? 'n' : 'N',
            isWhite ? 'r' : 'R',
            isWhite ? 'b' : 'B',
            isWhite ? 'q' : 'Q',
            isWhite ? 'k' : 'K'
        };

        int[][] pawnDirs = isWhite ? BLACK_PAWN_DIRS : WHITE_PAWN_DIRS;
        if (isAttackedByPiece(kingPos, pieces[0], pawnDirs, false)) return true;

        if (isAttackedByPiece(kingPos, pieces[1], KNIGHT_DIRS, false)) return true;

        if (isAttackedByPiece(kingPos, pieces[2], ROOK_DIRS, true)) return true;

        if (isAttackedByPiece(kingPos, pieces[3], BISHOP_DIRS, true)) return true;

        if (isAttackedByPiece(kingPos, pieces[4], QUEEN_DIRS, true)) return true;

        return false;
    }

    public void run() {
        int gameCount = 0;

        while (true) {
            if (readBoard()) break;

            gameCount++;
            boolean whiteInCheck = isInCheck(true);
            boolean blackInCheck = isInCheck(false);

            System.out.print("Game #" + gameCount + ": ");
            if (whiteInCheck) {
                System.out.println("white king is in check.");
            } else if (blackInCheck) {
                System.out.println("black king is in check.");
            } else {
                System.out.println("no king is in check.");
            }
        }

        scanner.close();
    }
}