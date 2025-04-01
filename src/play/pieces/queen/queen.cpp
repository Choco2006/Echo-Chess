#include "queen.h"
#include "../../board.h"
#include "../rook/rook.h"
#include "../bishop/bishop.h"

bool IsValidQueenMove(int fromRow, int fromCol, int toRow, int toCol) {
    return IsValidRookMove(fromRow, fromCol, toRow, toCol) || 
           IsValidBishopMove(fromRow, fromCol, toRow, toCol);
}