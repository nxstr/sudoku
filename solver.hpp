//
// Created by Ira on 18.12.2022.
//


#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <iostream>
#include <map>
#include <vector>
class solver {
private:
    std::vector<std::vector<int>> table;
    std::map<std::pair<int, int>, std::vector<int>> solution;
    std::vector<std::vector<int>> empty_visited;
public:
    solver(std::vector<std::vector<int>> board);
    solver(int board[9][9]);
    bool is_in_row(int x, int num);
    bool is_in_col(int y, int num);
    bool is_in_box(int x, int y, int num);
    bool is_valid_stone(int x, int y, int num);
    bool findEmptyPlace(int &row, int &col);
    bool solve();
    void print_board();
    std::vector<std::vector<int>> get_table();
};


#endif //SUDOKU_SOLVER_HPP
