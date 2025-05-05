#include "board.h"
#include "../src/play/promotion/promotion.h"
#include "../src/play/castle/castling.h"
#include <iostream>

Piece board[8][8];
SDL_Texture* pieceTextures[6][2];
PieceColor currentTurn = WHITE;
Move lastMove = {0, 0, 0, 0, {EMPTY, NONE}, {EMPTY, NONE}};

void InitBoard(){
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col] = {EMPTY, NONE};
        }
    }

    for (int col = 0; col < 8; ++col) {
        board[1][col] = {PAWN, BLACK};
        board[6][col] = {PAWN, WHITE};
    }

    PieceType backRow[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

    for (int col = 0; col < 8; ++col) {
        board[0][col] = {backRow[col], BLACK};
        board[7][col] = {backRow[col], WHITE};
    }
}

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void LoadPieceTextures(SDL_Renderer* renderer) {
    const char* pieceNames[6] = {"pawn", "rook", "knight", "bishop", "queen", "king"};
    const char* colors[2] = {"white", "black"};

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::string path = "resources/images/main/chess_pieces/" + std::string(pieceNames[i]) + "_" + colors[j] + ".png";
            pieceTextures[i][j] = LoadTexture(renderer, path.c_str());
        }
    }
}

void RenderPieces(SDL_Renderer* renderer) {
    int boardSize = 400;
    int cellSize = boardSize / 8;
    int startX = (960 - boardSize) / 2;
    int startY = (720 - boardSize) / 2;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = board[row][col];
            if (piece.type != EMPTY) {
                SDL_Texture* texture = pieceTextures[piece.type - 1][piece.color - 1];
                if (texture) {
                    SDL_Rect dstRect = {startX + col * cellSize, startY + row * cellSize, cellSize, cellSize};
                    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
                }
            }
        }
    }
}

bool IsValidMove(int fromRow, int fromCol, int toRow, int toCol){
    Piece piece = board[fromRow][fromCol];
    
    switch (piece.type) {
        case PAWN:
            return IsValidPawnMove(fromRow, fromCol, toRow, toCol);
        case ROOK:
            return IsValidRookMove(fromRow, fromCol, toRow, toCol);
        case KNIGHT:
            return IsValidKnightMove(fromRow, fromCol, toRow, toCol);
        case BISHOP:
            return IsValidBishopMove(fromRow, fromCol, toRow, toCol);
        case QUEEN:
            return IsValidQueenMove(fromRow, fromCol, toRow, toCol);
        case KING: 
            return IsValidKingMove(fromRow, fromCol, toRow, toCol);
        default:
            return false;
    }
}

std::pair<int, int> GetKingPosition(PieceColor kingColor) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].type == KING && board[row][col].color == kingColor) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

bool IsKingInCheck(PieceColor kingColor) {
    auto [kingRow, kingCol] = GetKingPosition(kingColor);
    if (kingRow == -1) return false;

    PieceColor opponentColor = (kingColor == WHITE) ? BLACK : WHITE;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col].color == opponentColor) {
                PieceType type = board[row][col].type;
                
                if (type == PAWN && IsValidPawnMove(row, col, kingRow, kingCol))
                    return true;
                if (type == KNIGHT && IsValidKnightMove(row, col, kingRow, kingCol))
                    return true;
                if (type == KING && IsValidKingMove(row, col, kingRow, kingCol))
                    return true;
                if ((type == BISHOP || type == QUEEN) && IsValidBishopMove(row, col, kingRow, kingCol) && IsClearDiagonal(row, col, kingRow, kingCol))
                    return true;
                if ((type == ROOK || type == QUEEN) && IsValidRookMove(row, col, kingRow, kingCol) && IsClearStraight(row, col, kingRow, kingCol))
                    return true;
            }
        }
    }
    return false;
}

bool IsClearStraight(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow == toRow) {
        int step = (toCol > fromCol) ? 1 : -1;
        for (int col = fromCol + step; col != toCol; col += step) {
            if (board[fromRow][col].type != EMPTY) return false;
        }
    } else if (fromCol == toCol) {
        int step = (toRow > fromRow) ? 1 : -1;
        for (int row = fromRow + step; row != toRow; row += step) {
            if (board[row][fromCol].type != EMPTY) return false;
        }
    }
    return true;
}

bool IsClearDiagonal(int fromRow, int fromCol, int toRow, int toCol){
    if (abs(toRow - fromRow) != abs(toCol - fromCol)) return false;

    int rowStep = (toRow > fromRow) ? 1 : -1;
    int colStep = (toCol > fromCol) ? 1 : -1;
    int row = fromRow + rowStep, col = fromCol + colStep;

    while (row != toRow && col != toCol) {
        if (board[row][col].type != EMPTY) return false;
        row += rowStep;
        col += colStep;
    }
    return true;
}

bool DoesMovePutKingInCheck(int fromRow, int fromCol, int toRow, int toCol) {
    Piece tempPiece = board[toRow][toCol];
    Piece movingPiece = board[fromRow][fromCol];

    board[toRow][toCol] = movingPiece;
    board[fromRow][fromCol] = {EMPTY, NONE};

    bool kingInCheck = IsKingInCheck(movingPiece.color);

    board[fromRow][fromCol] = movingPiece;
    board[toRow][toCol] = tempPiece;

    return kingInCheck;
}

void MovePiece(int fromRow, int fromCol, int toRow, int toCol) {
    Piece piece = board[fromRow][fromCol];

    //kiem tra nuoc di nhap thanh
    if (piece.type == KING && abs(fromCol - toCol) == 2) {
        if (PerformCastle(fromRow, fromCol, (toCol > fromCol) ? 7 : 0, piece.color)) {
            lastMove = {fromRow, fromCol, toRow, toCol, piece, {EMPTY, NONE}};
            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
            return;
        }
    }

    //xu ly nuoc di binh thuong
    Piece tempPiece = board[toRow][toCol];
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = {EMPTY, NONE};

    if (DoesMovePutKingInCheck(fromRow, fromCol, toRow, toCol)) {
        board[fromRow][fromCol] = piece;
        board[toRow][toCol] = tempPiece;
    } else {
        lastMove = {fromRow, fromCol, toRow, toCol, piece, tempPiece};
        currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

    //phong hau
    PromotePawn(toRow, toCol);

    }
}

void CleanupBoard(){
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (pieceTextures[i][j]) {
                SDL_DestroyTexture(pieceTextures[i][j]);
                pieceTextures[i][j] = nullptr;
            }
        }
    }
}