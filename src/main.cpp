//#include <iostream>
#include "../include/Board.h"

int main(){
    Board board;

    board.draw();

    
    while(!board.getGameLoop()){
        board.input();
        board.secondPlayer();

        if(board.checkResult(1)){
            board.setGameLoop(true);
            std::cout << "First player won game!\n";
        }else if(board.checkResult(2)){
            board.setGameLoop(true);
            std::cout << "Second player won game!\n";
        }
    }
    return 0;
}