#include "knight.h"

bool IsValidKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (board[toRow][toCol].type == EMPTY || board[toRow][toCol].color != board[fromRow][fromCol].color) {
            return true;
        }
    }
    return false;
}