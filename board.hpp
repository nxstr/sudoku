
#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP
#include <iostream>
#include <vector>
#include <random>
#include <cstdio>
#include "solver.hpp"
class new_board{
private:
    std::vector<std::vector<int>> board; //hlavni deska cele hry
    int difficulty; //slozitost hry
    std::vector<std::vector<int>> not_change; //pole "kamenu" ktere hrac nemuze zmenit behem hry
    void reverse_rows_n_cols(); //pomocna funkce pro generovani desky pro novou hru
    void swap_colums_small(); //pomocna funkce pro generovani desky pro novou hru
    void swap_rows_small(); //pomocna funkce pro generovani desky pro novou hru
    void swap_rows_area(); //pomocna funkce pro generovani desky pro novou hru
    void swap_colums_area(); //pomocna funkce pro generovani desky pro novou hru
    int set_difficulty();
public:
    new_board(); // zakladni konstruktor tridy
    new_board(int given_board[9][9]);
    void print_board(); //vypis desky
    void generate_random_base(int count=5); //denerator desky
    void delete_stones(); //odstrani z desky kameny podle slozitosti
    bool make_move(int x, int y, int num); //zafixuje tah hrace a prida cislice do desky
    std::vector<std::vector<int>> get_board();
    bool get_empty();
    void set_difficult(int difficult);
    void saveGame(); //ulozi hru do souboru
    void loadGame(); //nacte predem ulozenou hru ze souboru
    bool valid_move(int x, int y, int num); //kontrola validace tahu
    void set_solution(std::vector<std::vector<int>> table); //automaticke vyreseni desky
};

#endif //SUDOKU_BOARD_HPP
