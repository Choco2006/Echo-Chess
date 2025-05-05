#include "play.h"
#include "board.h"
#include "../src/play/castle/castling.h"
#include <iostream>

bool isPlaying = false;
SDL_Texture* playBackgroundTexture = nullptr;
int selectedRow = -1;
int selectedCol = -1;
Piece selectedPiece = {EMPTY, NONE};

void InitPlay(SDL_Renderer* renderer) {
    SDL_Surface* bgSurface = IMG_Load("resources/images/main/play_background.png");
    if (!bgSurface) {
        std::cerr << "Khong the tai background! Loi: " << IMG_GetError() << std::endl;
    } else {
        playBackgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
    }

    InitBoard();
    LoadPieceTextures(renderer);
}

void HandlePlayEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        //nut replay
        SDL_Rect replayButton = {280 + 400 / 2 - 50, 160 + 400 + 20, 100, 50};
        if (mouseX >= replayButton.x && mouseX <= replayButton.x + replayButton.w &&
            mouseY >= replayButton.y && mouseY <= replayButton.y + replayButton.h) {
            // Reset game
            InitBoard();
            selectedPiece = {EMPTY, NONE};
            selectedRow = -1;
            selectedCol = -1;
            currentTurn = WHITE;
            return;
        }
        
        int boardSize = 400;
        int cellSize = boardSize / 8;
        int startX = (960 - boardSize) / 2;
        int startY = (720 - boardSize) / 2;

        int col = (mouseX - startX) / cellSize;
        int row = (mouseY - startY) / cellSize;

        //kiem tra chon quan co
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            Piece clickedPiece = board[row][col];

            if (selectedPiece.type == EMPTY) {
                if (clickedPiece.type != EMPTY && clickedPiece.color == currentTurn) {
                    selectedPiece = clickedPiece;
                    selectedRow = row;
                    selectedCol = col;
                }
            } else {
                //chon vua + bam vao xe -> nhap thanh
                if (selectedPiece.type == KING && clickedPiece.type == ROOK && clickedPiece.color == currentTurn) {
                    if (CanCastle(selectedRow, selectedCol, col, currentTurn)) {
                        if (PerformCastle(selectedRow, selectedCol, col, currentTurn)) {
                            selectedPiece = {EMPTY, NONE};
                            selectedRow = -1;
                            selectedCol = -1;
                            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
                            return; // Kết thúc vì nhập thành đã được thực hiện
                        }
                    }
                }
                if (row == selectedRow && col == selectedCol) {
                    selectedPiece = {EMPTY, NONE};
                    selectedRow = -1;
                    selectedCol = -1;
                    return;
                }

                if (clickedPiece.type != EMPTY && clickedPiece.color == selectedPiece.color) {
                    return;
                }

                //di chuyen thong thuong
                if (IsValidMove(selectedRow, selectedCol, row, col) &&
                    !DoesMovePutKingInCheck(selectedRow, selectedCol, row, col)) {
                    MovePiece(selectedRow, selectedCol, row, col);
                    selectedPiece = {EMPTY, NONE};
                    selectedRow = -1;
                    selectedCol = -1;
                }
            }
        }
    }
}

void RenderPlay(SDL_Renderer* renderer) {
    if (isPlaying){
        if (playBackgroundTexture) {
            SDL_RenderCopy(renderer, playBackgroundTexture, NULL, NULL);
        }

        int boardSize = 400;
        int cellSize = boardSize / 8;

        int startX = (960 - boardSize) / 2;
        int startY = (720 - boardSize) / 2;

        //ve nut replay
        SDL_Rect replayButton = {startX + boardSize / 2 - 50, startY + boardSize + 20, 100, 50};
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderFillRect(renderer, &replayButton);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &replayButton);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect borderRect = {startX - 5, startY - 5, boardSize + 10, boardSize + 10};
        SDL_RenderFillRect(renderer, &borderRect);

        //khai bien check vua
        auto [whiteKingRow, whiteKingCol] = GetKingPosition(WHITE);
        auto [blackKingRow, blackKingCol] = GetKingPosition(BLACK);
        bool whiteInCheck = IsKingInCheck(WHITE);
        bool blackInCheck = IsKingInCheck(BLACK);

        //ve ban co
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);
                }

                SDL_Rect cellRect = {startX + col * cellSize, startY + row * cellSize, cellSize, cellSize};
                SDL_RenderFillRect(renderer, &cellRect);

                if ((whiteInCheck && row == whiteKingRow && col == whiteKingCol) ||
                (blackInCheck && row == blackKingRow && col == blackKingCol)) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
                SDL_RenderFillRect(renderer, &cellRect);
                }
            }
        }

        //chon quan co
        if (selectedPiece.type != EMPTY) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
            SDL_Rect highlightRect = {
                startX + selectedCol * cellSize,
                startY + selectedRow * cellSize,
                cellSize, cellSize
            };
            SDL_RenderFillRect(renderer, &highlightRect);
        }

        //ve quan co
        RenderPieces(renderer);

    }
}

void CleanupPlay() {
    if (playBackgroundTexture) {
        SDL_DestroyTexture(playBackgroundTexture);
        playBackgroundTexture = nullptr;
    }
}