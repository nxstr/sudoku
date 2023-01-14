
#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP
#include "board.hpp"

class game{
private:
    new_board board; //aktualni deska
    bool quit; //promenna pro oznaceni ukonceni hry
    std::vector<int> nums; //pole vstupnich hodnot
    std::mutex mutex;
public:
    game();
    bool moving(); //fixuje tah hrace
    int set_difficul();
    std::vector<int> getX(); //zpracovani inputu
    void initialize(); //inicializacni funkce, slouzi pro vyber nove nebo ulozene hry
    bool get_quit() const {
        return quit;
    }
    void set_quit(const bool qq) {
        quit = qq;
    }
    bool print_board();
    bool validMove(); //validace tahu
    bool endGame(){ //kontrola jestli deska ma prazdna mista
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
