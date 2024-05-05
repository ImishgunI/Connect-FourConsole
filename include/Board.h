#pragma once
#include <array>
#include <ios>
#include <iostream>
#include <limits>
#include <random>

class Board{
private:
    std::array<std::array<int, 7>, 6> board;
    int choose_row;
    int choose_col;
    bool gameLoop = false;
public:
    Board() : board {{
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0},
        }} {}

    
    bool getGameLoop() const {
        return gameLoop;
    }

    void setGameLoop(bool game){
        this->gameLoop = game;
    }

    void draw(){
        std::cout << "-----------------";
        for(int i = 0; i < 6; ++i){
            std::cout << "\n| ";
            for(int j = 0; j < 7; ++j){
                std::cout << board[i][j] << " ";
                if(j == 7){
                    std::cout << '\n';
                }
            }
            std::cout << "|";
        }
        std::cout << "\n-----------------\n";
    }


    void input(){
        std::cout << "You should choose place where your chip will lie\n";
        std::cout << "Choose the place: ";
        std::cin >> choose_row >> choose_col;
        while(true){
            if(choose_row < 0 || choose_row >= 6 || choose_col < 0 || choose_col >= 7){
                std::cout << "Invalid input\n";
                break;
            }else if(board[choose_row][choose_col] != 0){
                std::cout << "This place already occupied!\n";
            }else {
                break;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Choose the place: ";
            std::cin >> choose_row >> choose_col;
        }
        board[choose_row][choose_col] = 1;
        draw();
    }

    void secondPlayer(){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> random_number_for_second_player(0,6);

        int row = random_number_for_second_player(rng);
        int col = random_number_for_second_player(rng);

        if(board[row][col] == 0){
            board[row][col] = 2;
        }
    }

    bool checkResult(int player){
        for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == player && board[row][col+1] == player && 
                board[row][col+2] == player && board[row][col+3] == player) {
                return !gameLoop;
            }
        }
    }

    // Проверка вертикальных линий
    for (int col = 0; col < 7; ++col) {
        for (int row = 0; row < 3; ++row) {
            if (board[row][col] == player && board[row+1][col] == player && 
                board[row+2][col] == player && board[row+3][col] == player) {
                return !gameLoop;
            }
        }
    }

    // Проверка диагональных линий (\)
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == player && board[row+1][col+1] == player && 
                board[row+2][col+2] == player && board[row+3][col+3] == player) {
                return !gameLoop;
            }
        }
    }

    // Проверка диагональных линий (/)
    for (int row = 0; row < 3; ++row) {
        for (int col = 3; col < 7; ++col) {
            if (board[row][col] == player && board[row+1][col-1] == player && 
                board[row+2][col-2] == player && board[row+3][col-3] == player) {
                return !gameLoop;
            }
        }
    }

    return gameLoop;
    }
};