#include "king.h"
#include "../../board.h"

bool IsValidKingMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    
    return (rowDiff <= 1 && colDiff <= 1);
}