#ifndef KNIGHT_H
#define KNIGHT_H

#include "../src/play/board.h"

bool IsValidKnightMove(int fromRow, int fromCol, int toRow, int toCol);
void HandleKnightMove(int fromRow, int fromCol, int toRow, int toCol);

#endif