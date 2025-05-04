#include "play.h"
#include "board.h"
#include "../play/castle/castle.h"
#include <iostream>

bool isPlaying = false;
SDL_Texture* playBackgroundTexture = nullptr;
int selectedRow = -1;
int selectedCol = -1;
Piece selectedPiece = {EMPTY, NONE};

void InitPlay(SDL_Renderer* renderer) {
    std::cout << "Dang khoi tao gameplay" << std::endl;

    SDL_Surface* bgSurface = IMG_Load("resources/images/main/play_background.png");
    if (!bgSurface) {
        std::cerr << "Khong the tai background! Loi: " << IMG_GetError() << std::endl;
    } else {
        playBackgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
    }

    InitBoard();
    LoadPieceTextures(renderer);

    std::cout << "Khoi tao gameplay thanh cong!" << std::endl;
}

void HandlePlayEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        int boardSize = 400;
        int cellSize = boardSize / 8;
        int startX = (960 - boardSize) / 2;
        int startY = (720 - boardSize) / 2;

        int col = (mouseX - startX) / cellSize;
        int row = (mouseY - startY) / cellSize;

        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            Piece clickedPiece = board[row][col];

            if (selectedPiece.type == EMPTY) {
                if (clickedPiece.type != EMPTY && clickedPiece.color == currentTurn) {
                    selectedPiece = clickedPiece;
                    selectedRow = row;
                    selectedCol = col;
                }
            } else {
                if (row == selectedRow && col == selectedCol) {
                    selectedPiece = {EMPTY, NONE};
                    selectedRow = -1;
                    selectedCol = -1;
                    return;
                }

                if (clickedPiece.type != EMPTY && clickedPiece.color == selectedPiece.color) {
                    return;
                }

                // Kiểm tra nhập thành
                if (selectedPiece.type == KING && abs(selectedCol - col) == 2) {
                    Castle castle;
                    Position kingPos = {selectedRow, selectedCol};
                    Position rookPos = (col > selectedCol) ? Position{selectedRow, 7} : Position{selectedRow, 0};

                    if (castle.performCastle(board, kingPos, rookPos)) {
                        selectedPiece = {EMPTY, NONE};
                        selectedRow = -1;
                        selectedCol = -1;
                        currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
                        return; // Kết thúc vì nhập thành đã được thực hiện
                    }
                }

                // Di chuyển thông thường
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
        } else {
            std::cerr << "Texture background gameplay bi null!" << std::endl;
        }

        int boardSize = 400;
        int cellSize = boardSize / 8;

        int startX = (960 - boardSize) / 2;
        int startY = (720 - boardSize) / 2;

        //ve vien mau den
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
    std::cout << "Da don dep tai nguyen gameplay" << std::endl;
}