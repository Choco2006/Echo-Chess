#ifndef PAWN_H
#define PAWN_H

#include "../src/play/board.h"

bool IsValidPawnMove(int fromRow, int fromCol, int toRow, int toCol);
void HandlePawnMove(int fromRow, int fromCol, int toRow, int toCol);

#endif