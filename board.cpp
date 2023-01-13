#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "board.hpp"
#include <sstream>

#define ANSI_CLEAR "\x1B[2J\x1B[H"  // mazani terminalu
#define ANSI_COLOR_RESET "\x1B[m"   // reset barev
#define COLOR_GREEN "\x1B[92m"      // zelena barva pro kolecko
new_board::new_board(int given_board[9][9]): board(9, std::vector<int>(9, 0)), difficulty(), not_change(9, std::vector<int>(9, 0)){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            board[i][j] = given_board[i][j];
        }
    }
};
new_board::new_board(): board(9, std::vector<int>(9, 0)), difficulty(0), not_change(9, std::vector<int>(9, 0)){
    std::vector<int> tmp_board;
    int iter = 1;
    int main_iter = 1;
    for(int j=0; j<9; j++){
        if(main_iter>3){
            break;
        }
        int item = iter;
        for(int i=0; i<9; i++){
            tmp_board.push_back(item);
            item++;
            if(item==10){
                item = 1;
            }
        }
        this->board[j] = tmp_board;
        tmp_board.clear();
        iter = iter+3;
        if(iter>9){
            main_iter++;
            iter = main_iter;
        }
    }
}



void new_board::reverse_rows_n_cols(){
    for (int i = 0; i < 9; i++){
        for (int j = i; j < 9; j++) {
            int tmp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = tmp;
        }
    }
}

void new_board::swap_rows_small(){
    srand(time(NULL));
    int area_idx = rand()%3;
    int line1_idx = rand()%3;
    int idx = area_idx*3+line1_idx;
    std::vector<int> line1 = board[idx];

    int line2_idx = rand()%3;
    std::vector<int> line2 = board[area_idx*3+line2_idx];
    while(line1==line2){
        line2_idx = rand()%3;
        line2 = board[area_idx*3+line2_idx];
    }
    board[idx] = line2;
    board[area_idx*3+line2_idx] = line1;
}

void new_board::swap_colums_small(){
    reverse_rows_n_cols();
    swap_rows_small();
    reverse_rows_n_cols();
}

void new_board::swap_rows_area(){
    srand(time(NULL));
    int area1_idx = rand()%3;
    int area2_idx = rand()%3;
    while(area1_idx==area2_idx){
        area2_idx = rand()%3;
    }
    for(int i=0;i<3;i++){
        std::vector<int> tmp = board[area1_idx*3+i];
        board[area1_idx*3+i] = board[area2_idx*3+i];
        board[area2_idx*3+i] = tmp;
    }
}

void new_board::swap_colums_area(){
    reverse_rows_n_cols();
    swap_rows_area();
    reverse_rows_n_cols();
}

void new_board::generate_random_base(int count){
    srand(time(NULL));
    for(int i=0; i<count; i++){
        int r = rand()%4;
        switch(r){
            case 0:
                reverse_rows_n_cols();
                break;
            case 1:
                swap_rows_small();
                break;
            case 2:
                swap_colums_small();
                break;
            case 3:
                swap_rows_area();
                break;
            default:
                swap_colums_area();
        }
    }
}

int new_board::set_difficulty(){
    int easy;
    if (difficulty==0){
        easy = 35;
    }else if(difficulty==1){
        easy = 30;
    }else if(difficulty==2){
        easy = 25;
    }
    return easy;
}

void new_board::delete_stones(){
    std::vector<std::vector<int>> visited(9, std::vector<int>(9, 0));
    int iterator = 0;
    int i, j;
    int easy = set_difficulty();
    srand(time(NULL));
    int dif = easy;
    while (iterator<81-dif){
        i = rand()%9;
        j = rand()%9;
        if (visited[i][j]==0){
            iterator++;
            visited[i][j] = 1;

            int tmp = board[i][j];
            board[i][j] = 0;

            solver s = solver(board);
            if(!s.solve()){
                board[i][j]=tmp;
                iterator--;
            }
            if(iterator==81-dif){
                break;
            }
        }
    }
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(board[i][j]!=0){
                not_change[i][j]=1;
            }
        }
    }
}

void new_board::set_solution(std::vector<std::vector<int>> table){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            if(board[row][col]==0){
                board[row][col] = table[row][col];
            }
        }
    }
}


bool new_board::make_move(int x, int y, int num){
        if(valid_move(x, y, num)){
            board[x][y]=num;
            return true;
        }else{
            return false;
        }
}

bool new_board::valid_move(int x, int y, int num){
    if(not_change[x][y]==0) {
        solver s = solver(board);
        if(s.is_valid_stone(x, y, num)){
            return true;
        }else{
            std::cout << "This move is not valid! Please make another one!" << std::endl;
        }
    }else{
        std::cout << "This stone is not allowed to change, please make another move!" << std::endl;
    }
    return false;
}

std::vector<std::vector<int>> new_board::get_board(){
    return board;
}

bool new_board::get_empty(){
    for(int i=0 ;i<9; i++){
        if(std::find(board[i].begin(), board[i].end(), 0)!=board[i].end()){
            return true;
        }
    }
    return false;
}

void new_board::print_board() {
//    for(auto item:board){
//        for(auto jtem:item){
//            std::cout << "| " << jtem << " ";
//        }
//        std::cout << "|" << std::endl << "-------------------------------------" << std::endl;
//    }
    std::stringstream buffer;
    std::cout << ANSI_CLEAR << ANSI_COLOR_RESET;
    std::cout << "\r";
    std::cout << std::endl;
    std::cout << "      1 2 3   4 5 6   7 8 9" << std::endl;
    std::cout << "      ---------------------" << std::endl;
    std::cout << std::endl;
    for (int row = 0; row < 9; row++){
        std::cout << row+1 << " :   ";
        for (int col = 0; col < 9; col++){
            if(col == 3 || col == 6)
                std::cout << "| ";
            if(board[row][col]==0) {
                std::cout << ". ";
            }else{
                if(not_change[row][col]!=0){
                    std::cout <<  board[row][col]  << " ";
                }else{
                    std::cout << COLOR_GREEN << board[row][col]  << ANSI_COLOR_RESET <<" ";
                }

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

void new_board::set_difficult(int difficult) {
    this->difficulty = difficult;
}

void new_board::saveGame(){
    std::ofstream output_file("saved.txt");
    std::vector<std::string> b;
    for(int i=0; i<9;i++){
        for(int j=0; j<9;j++){
            std::string s= std::to_string(i)+ std::to_string(j) + std::to_string(board[i][j]);
            b.push_back(s);
        }
    }
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(b.begin(), b.end(), output_iterator);
    output_file.close();
}

void new_board::loadGame(){
    std::ifstream file("saved.txt");
    std::string s;

    while(getline(file, s)){
        if(std::isdigit(s[0]) && std::isdigit(s[1]) && std::isdigit(s[2])){
            board[s[0]-'0'][s[1]-'0'] = s[2]-'0';
        }
    }

    file.close();
}