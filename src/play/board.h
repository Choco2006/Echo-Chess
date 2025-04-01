#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "../play/pieces/pawn/pawn.h"
#include "../play/pieces/knight/knight.h"
#include "../play/pieces/rook/rook.h"
#include "../play/pieces/bishop/bishop.h"
#include "../play/pieces/king/king.h"
#include "../play/pieces/queen/queen.h"

enum PieceType {EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
enum PieceColor {NONE, WHITE, BLACK};

struct Piece {
    PieceType type;
    PieceColor color;
};

extern Piece board[8][8];
extern SDL_Texture* pieceTextures[6][2];
extern PieceColor currentTurn;

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
    Piece pieceMoved;
    Piece pieceCaptured;
};

extern Move lastMove;

//bien di chuyen cac quan co
bool IsValidMove(int fromRow, int fromCol, int toRow, int toCol);

//check vua
bool IsKingInCheck(PieceColor kingColor);
std::pair<int, int> GetKingPosition(PieceColor kingColor);

void InitBoard();
void LoadPieceTextures(SDL_Renderer* renderer);
void RenderPieces(SDL_Renderer* renderer);
void CleanupBoard();

#endif
