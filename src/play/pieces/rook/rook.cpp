#include "rook.h"

bool IsValidRookMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow == toRow || fromCol == toCol) {
        int rowStep = (toRow - fromRow > 0) ? 1 : (toRow - fromRow < 0) ? -1 : 0;
        int colStep = (toCol - fromCol > 0) ? 1 : (toCol - fromCol < 0) ? -1 : 0;

        int r = fromRow + rowStep;
        int c = fromCol + colStep;

        while (r != toRow || c != toCol) {
            if (board[r][c].type != EMPTY) return false;
            r += rowStep;
            c += colStep;
        }

        return board[toRow][toCol].color != board[fromRow][fromCol].color;
    }
    return false;
}