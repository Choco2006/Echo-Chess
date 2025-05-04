#ifndef CASTLE_H
#define CASTLE_H

#include "../play/board.h"

// Forward declarations for Board and Position if not included in board.h
class Board;
struct Position;

class Castle {
public:
    Castle();

    // Kiểm tra nếu nhập thành hợp lệ
    bool canCastle(const Board& board, const Position& kingPos, const Position& rookPos);

    // Thực hiện nhập thành
    bool performCastle(Board& board, const Position& kingPos, const Position& rookPos);
};

#endif // CASTLE_H