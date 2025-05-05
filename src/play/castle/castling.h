#ifndef CASTLING_H
#define CASTLING_H

#include "../board.h"

bool CanCastle(int kingRow, int kingCol, int rookCol, PieceColor color);
bool PerformCastle(int kingRow, int kingCol, int rookCol, PieceColor color);

#endif // CASTLING_H