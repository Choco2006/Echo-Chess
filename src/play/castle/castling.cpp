#include "castling.h"
#include <iostream>

//ham check nhap thanh hop le
bool CanCastle(int kingRow, int kingCol, int rookCol, PieceColor color) {
    //kiem tra neu vua & xe di chuyen
    if (board[kingRow][kingCol].type != KING || board[kingRow][kingCol].color != color) return false;
    if (board[kingRow][rookCol].type != ROOK || board[kingRow][rookCol].color != color) return false;

    //kiem tra neu co quan co giua vua va xe
    int colStart = std::min(kingCol, rookCol) + 1;
    int colEnd = std::max(kingCol, rookCol);
    for (int col = colStart; col < colEnd; ++col) {
        if (board[kingRow][col].type != EMPTY) return false;
    }

    //kiem tra neu vua bi chieu hoac di qua o bi chieu
    for (int col = std::min(kingCol, rookCol); col <= std::max(kingCol, rookCol); ++col) {
        if (DoesMovePutKingInCheck(kingRow, kingCol, kingRow, col)) return false;
    }

    return true; // Nhập thành hợp lệ
}

//ham thuc hien nhap thanh
bool PerformCastle(int kingRow, int kingCol, int rookCol, PieceColor color) {
    if (!CanCastle(kingRow, kingCol, rookCol, color)) return false;

    //di chuyen vua va xe
    if (rookCol > kingCol) {
        //nhap thanh canh vua
        board[kingRow][kingCol + 2] = board[kingRow][kingCol];
        board[kingRow][kingCol] = {EMPTY, NONE};
        board[kingRow][kingCol + 1] = board[kingRow][rookCol];
        board[kingRow][rookCol] = {EMPTY, NONE};
    } else {
        //nhap thanh canh hau
        board[kingRow][kingCol - 2] = board[kingRow][kingCol];
        board[kingRow][kingCol] = {EMPTY, NONE};
        board[kingRow][kingCol - 1] = board[kingRow][rookCol];
        board[kingRow][rookCol] = {EMPTY, NONE};
    }

    return true;
}