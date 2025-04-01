#include "pawn.h"

bool IsValidPawnMove(int fromRow, int fromCol, int toRow, int toCol) {
    Piece piece = board[fromRow][fromCol];
    int direction = (piece.color == WHITE) ? -1 : 1;

    if (fromCol == toCol && board[toRow][toCol].type == EMPTY) {
        if (toRow == fromRow + direction) return true;
        if ((fromRow == 1 && piece.color == BLACK) || (fromRow == 6 && piece.color == WHITE)) {
            if (toRow == fromRow + 2 * direction && board[fromRow + direction][fromCol].type == EMPTY) {
                return true;
            }
        }
    }

    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol].type != EMPTY && board[toRow][toCol].color != piece.color) {
            return true;
        }
    }

    return false;
}

void HandlePawnMove(int fromRow, int fromCol, int toRow, int toCol) {
    Piece piece = board[fromRow][fromCol];
    int direction = (piece.color == WHITE) ? -1 : 1;

    if (abs(fromCol - toCol) == 1 && toRow == fromRow + direction && board[toRow][toCol].type == EMPTY) {
        int capturedRow = toRow - direction;
        if (board[capturedRow][toCol].type == PAWN &&
            board[capturedRow][toCol].color != piece.color &&
            lastMove.toRow == capturedRow &&
            lastMove.toCol == toCol &&
            lastMove.fromRow == capturedRow - 2 * direction &&
            lastMove.pieceMoved.type == PAWN) {
            
            board[capturedRow][toCol] = {EMPTY, NONE};
        }
    }

    lastMove = {fromRow, fromCol, toRow, toCol, piece, board[toRow][toCol]};
    board[fromRow][fromCol] = {EMPTY, NONE};
    board[toRow][toCol] = piece;
}
