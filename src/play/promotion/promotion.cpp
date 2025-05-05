#include "promotion.h"
#include <iostream>

void PromotePawn(int row, int col) {
    //kiem tra neu quan tot o hang cuoi cung
    if (board[row][col].type == PAWN) {
        if ((board[row][col].color == WHITE && row == 0) || 
            (board[row][col].color == BLACK && row == 7)) {
            board[row][col].type = QUEEN;
        }
    }
}