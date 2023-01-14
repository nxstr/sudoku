#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <future>
#include "game.hpp"
#include "solver.hpp"


game::game():board(), quit(false), nums(){

};

/*
 * funkce yepta se hrace jestli chce zacit novou hru nebo nacist ulozenou
 */
void game::initialize(){
    std::cout << "Do you want to start new game(n) or load saved(l)? n/l" << std::endl;
    std::string choice;
    std::cin >> choice;
    if(choice=="n"){
        board = new_board();
        board.set_difficult(set_difficul());
        board.generate_random_base();
        board.delete_stones();
        std::cout << "----------NEW GAME----------" << std::endl;
    }
    else if(choice=="l"){
        board.loadGame();
        std::cout << "----------LAST SAVED GAME----------" << std::endl;
    }
}
/*
 * zavola pridani tahu z tridy board pro konkretni vstupni data
 */
bool game::moving(){
    while(true){
        if(!board.get_empty()){
            std::cout << "---------Congratulations!---------" << std::endl;
            return true;
        }
        int x = nums[0]-1;
        int y = nums[1]-1;
        int num = nums[2];
        if(board.make_move(x, y, num)){
            nums.clear();
            return true;
        }else{
            return false;
        }

    }
}
/*
 * doplnkova validace tahu
 */
bool game::validMove(){
    if(nums.size()==3) {
        if (board.valid_move(nums[0] - 1, nums[1] - 1, nums[2])) {
            return true;
        }
    }
    nums.clear();
    return false;
}

bool game::print_board(){
    board.print_board();
    return true;
}
/*
 * funkce zpracovava vstupni hodnoty a royhoduje v jakem smeru
 * program ma pokracovat
 */
std::vector<int> game::getX(){
    std::unique_lock<std::mutex> lg(mutex);
    std::string str;
    std::cout << "Enter left side coord, up coord and number: ";
    while(nums.size()!=3){
        std::getline(std::cin, str);
        if(std::isdigit(str[0]) && std::isdigit(str[2]) && std::isdigit(str[4])){
            for(int i=0; i<str.length(); i++){
                std::string s = "";
                s = str[i];
                if(i==0 || i==2 || i==4){
                    if(std::stoi(s)>0 && std::stoi(s)<10){
                        nums.push_back(std::stoi(s));
                    }
                }
            }
        }
        else if (str == "quit") {
            set_quit(true);
            return nums;
        }
        else if (str == "save") {
            board.saveGame();
            std::cout << "Game successfully saved\n";
            std::cout << "Enter left side coord, up coord and number: ";
        }else if (str == "solve") {
            solver s = solver(board.get_board());
            if(s.solve()) {
                std::vector<std::vector<int>> table = s.get_table();
                board.set_solution(table);
                print_board();
                std::cout << "Game solving\n";
            }else{
                std::cout << "Board can not be solved\n";
            }
            nums.clear();
            set_quit(true);
            return nums;
        }
        else if(str!=""){
            std::cout << "Enter left side coord, up coord and number: ";
            nums.clear();
        }else{
            nums.clear();
        }
    }
    return nums;
}


/*
 * urceni slozitosti hry
 */
int game::set_difficul() {
    std::cout << "Do you want to choose difficult of game? (Default is EASY) y/n" << std::endl;
    std::string choice;
    std::cin >> choice;
    int difficult;
    if(choice=="y"){
        std::cout << "-------------CHOOSE DIFFICULT--------------" << std::endl;
        std::cout << "Game has 3 levels: easy, medium, hard" << std::endl;
        std::cout << "Set 0 for EASY, 1 - MEDIUM, 2 - HARD" << std::endl;
        std::cin >> difficult;
    }else{
        difficult = 0;
    }
    return difficult;

}

void set_raw(bool set) {
    if (set) {
        system("stty raw");  // enable raw
    } else {
        system("stty -raw"); // disable raw
    }
}

int main() {

    auto inputThread = [](game& player) {
        bool q = false;
        std::vector<int> nums;
        while (!q && !player.validMove()) {
            nums = player.getX();
            q = player.get_quit();
        }
    };




    auto computeThread = [](game& player) {
        bool q = false;
        bool move = false;
        while (!q && !move) {
            move = player.moving();
            q = player.get_quit();
        }
    };




    auto outputThread = [&inputThread, &computeThread](game& player) {
        bool q = false;
        while (!q && !player.endGame()) {
            player.print_board();
            std::thread t2(inputThread, std::ref(player));
            t2.join();
            if(!player.get_quit()){
                std::thread t3(computeThread, std::ref(player));
                t3.join();
            }
            q = player.get_quit();
        }
        std::cout << "\r------------Game ended------------\n";
    };

    game PP;
    PP.initialize();

    std::thread t1(outputThread, std::ref(PP));
    t1.join();

    return 0;
}
