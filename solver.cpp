#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "solver.hpp"

solver::solver(std::vector<std::vector<int>> board): table(9, std::vector<int>(9, 0)), solution(), empty_visited(9, std::vector<int>(9, -1)){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]!=0){
                table[i][j] = board[i][j];
            }
            else if(board[i][j]==0){
                empty_visited[i][j] = 0;
                solution[std::make_pair(i, j)];
            }
        }
    }
};

solver::solver(int board[9][9]): table(9, std::vector<int>(9, 0)), solution(), empty_visited(9, std::vector<int>(9, -1)){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]!=0){
                table[i][j] = board[i][j];
            }
            else if(board[i][j]==0){
                empty_visited[i][j] = 0;
                solution[std::make_pair(i, j)];
            }
        }
    }
};

bool solver::is_in_row(int x, int num){
    for(int i=0; i<9; i++){
        if(table[x][i]==num){
            return true;
        }
    }
    return false;
}

bool solver::is_in_col(int y, int num){
    for(int i=0; i<9; i++){
        if(table[i][y]==num){
            return true;
        }
    }
    return false;
}

bool solver::is_in_box(int x, int y, int num){
    int StartBoxX, StartBoxY =0;
    StartBoxX = x-x%3;
    StartBoxY = y-y%3;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(table[i+StartBoxX][j+StartBoxY]==num){
                return true;
            }
        }
    }
    return false;
}

bool solver::is_valid_stone(int x, int y, int num){
    return !is_in_row(x, num) && !is_in_col(y, num) && !is_in_box(x, y, num);
}

bool solver::findEmptyPlace(int &row, int &col){
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (table[row][col] == 0)
                return true;
    return false;
}

bool solver::solve(){
    int row, col;
    if (!findEmptyPlace(row, col))
        return true;
    for(int num=1; num<=9; num++){
        if(is_valid_stone(row, col, num)){
            table[row][col] = num;
            for(auto &item:solution){
                if(item.first.first==row && item.first.second==col){
                    if(std::find(item.second.begin(), item.second.end(), num)==item.second.end()) {
                        item.second.push_back(num);
                        break;
                    }else{
                        break;
                    }
                }
            }
            if (this->solve())
                return true;
            table[row][col] = 0;
        }
    }
    return false;
}

std::vector<std::vector<int>> solver::get_table(){
    return table;
}

void solver::print_board(){
    std::cout << std::endl;
    std::cout << "      0 1 2   3 4 5   6 7 8" << std::endl;
    std::cout << "      ---------------------" << std::endl;
    std::cout << std::endl;
    for (int row = 0; row < 9; row++){
        std::cout << row << " :   ";
        for (int col = 0; col < 9; col++){
            if(col == 3 || col == 6)
                std::cout << "| ";
            if(table[row][col]==0) {
                std::cout << ". ";
            }else{
                std::cout << table[row][col] <<" ";
            }

        }
        if(row == 2 || row == 5){
            std::cout << std::endl;
            std::cout << "      ";
            for(int i = 0; i<7; i++)
                std::cout << "---";
//            std::cout << "-";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




