
#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP
#include "board.hpp"

class game{
private:
    new_board board;
    bool quit;
    std::vector<int> nums;
    std::mutex mutex;
public:
    game();
    bool moving();
    int set_difficul();
    std::vector<int> getX();
    void initialize();
    bool get_quit() const {
        return quit;
    }
    void set_quit(const bool qq) {
        quit = qq;
    }
    bool print_board();
    bool validMove();
    bool endGame(){
        if(!board.get_empty()){
            return true;
        }
        return false;
    }
    new_board get_board(){
        return board;
    }
};
#endif //SUDOKU_GAME_HPP
