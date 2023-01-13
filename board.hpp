
#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP
#include <iostream>
#include <vector>
#include <random>
#include <cstdio>
#include "solver.hpp"
class new_board{
private:
    std::vector<std::vector<int>> board;
    int difficulty;
    std::vector<std::vector<int>> not_change;
    void reverse_rows_n_cols();
    void swap_colums_small();
    void swap_rows_small();
    void swap_rows_area();
    void swap_colums_area();
    int set_difficulty();
public:
    new_board();
    new_board(int given_board[9][9]);
    void print_board();
    void generate_random_base(int count=5);
    void delete_stones();
    bool make_move(int x, int y, int num);
    std::vector<std::vector<int>> get_board();
    bool get_empty();
    void set_difficult(int difficult);
    void saveGame();
    void loadGame();
    bool valid_move(int x, int y, int num);
    void set_solution(std::vector<std::vector<int>> table);
};

#endif //SUDOKU_BOARD_HPP
