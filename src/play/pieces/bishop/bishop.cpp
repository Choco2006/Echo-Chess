#include "bishop.h"

bool IsValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) {
    return abs(toRow - fromRow) == abs(toCol - fromCol);
}