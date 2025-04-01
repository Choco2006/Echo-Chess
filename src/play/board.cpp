#include "board.h"
#include <iostream>

Piece board[8][8];
SDL_Texture* pieceTextures[6][2];
PieceColor currentTurn = WHITE;
Move lastMove = {0, 0, 0, 0, {EMPTY, NONE}, {EMPTY, NONE}};

void InitBoard(){
    std::cout << "Dang khoi tao ban co..." << std::endl;
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
        std::cerr << "Khong the tai anh: " << path << " Loi: " << IMG_GetError() << std::endl;
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
    int startX = 50;
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

//check vua
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
            if (board[row][col].color == opponentColor && IsValidMove(row, col, kingRow, kingCol)) {
                return true;
            }
        }
    }
    return false;
}

void CleanupBoard() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (pieceTextures[i][j]) {
                SDL_DestroyTexture(pieceTextures[i][j]);
                pieceTextures[i][j] = nullptr;
            }
        }
    }
}