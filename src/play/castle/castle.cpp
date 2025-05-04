#include "castle.h"

Castle::Castle() {
    // Initialize castle-related variables if needed
}

bool Castle::canCastle(const Board& board, const Position& kingPos, const Position& rookPos) {
    // Kiểm tra nếu vua hoặc xe đã di chuyển
    if (board.hasMoved(kingPos) || board.hasMoved(rookPos)) {
        return false;
    }

    // Kiểm tra nếu có quân cờ giữa vua và xe
    int row = kingPos.row;
    int colStart = std::min(kingPos.col, rookPos.col) + 1;
    int colEnd = std::max(kingPos.col, rookPos.col);
    for (int col = colStart; col < colEnd; ++col) {
        if (board.getPiece({row, col}).type != EMPTY) {
            return false;
        }
    }

    // Kiểm tra nếu vua đang bị chiếu hoặc đi qua ô bị chiếu
    for (int col = std::min(kingPos.col, rookPos.col); col <= std::max(kingPos.col, rookPos.col); ++col) {
        if (board.isSquareUnderAttack({row, col}, board.getOpponentColor(kingPos.color))) {
            return false;
        }
    }

    return true; // Nhập thành hợp lệ
}

bool Castle::performCastle(Board& board, const Position& kingPos, const Position& rookPos) {
    if (!canCastle(board, kingPos, rookPos)) {
        return false; // Không thể nhập thành
    }

    // Di chuyển vua và xe
    int row = kingPos.row;
    if (kingPos.col < rookPos.col) {
        // Nhập thành cánh vua (King-side castle)
        board.movePiece(kingPos, {row, kingPos.col + 2}); // Vua di chuyển 2 ô
        board.movePiece(rookPos, {row, kingPos.col + 1}); // Xe di chuyển 1 ô
    } else {
        // Nhập thành cánh hậu (Queen-side castle)
        board.movePiece(kingPos, {row, kingPos.col - 2}); // Vua di chuyển 2 ô
        board.movePiece(rookPos, {row, kingPos.col - 1}); // Xe di chuyển 1 ô
    }

    return true; // Nhập thành thành công
}