////#include <iostream>
////#include <functional>
////#include <thread>
////#include <mutex>
////#include "game.hpp"
////
////#define PERIOD_COUNTER 300
////
////void set_raw(bool set) {
////    if (set) {
////        system("stty raw");  // enable raw
////    } else {
////        system("stty -raw"); // disable raw
////    }
////}
////
////class tic_tac_toe {
////public:
////    explicit tic_tac_toe() : quit(false), counter(0) {};
////    void input() {
////        std::unique_lock<std::mutex> lg(mutex);
//////        lg.unlock();
////        char c;
////        std::cin >> c;
////        if (c == 'q') {
////            set_quit(true);
////        }
////    }
////    void output_area() {
////        std::unique_lock<std::mutex> lg(mutex);
////        std::cout << "\rCounter: " << counter << std::endl;
////    }
////    void take() {
////        std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_COUNTER));
////        std::unique_lock<std::mutex> lg(mutex);
////        ++counter;
////    }
////    bool get_quit() const {
////        return quit;
////    }
////    void set_quit(const bool qq) {
////        quit = qq;
////    }
////private:
////    bool quit;
////    int counter;
////    std::mutex mutex;
////};
////
////int main() {
//////    int grid[9][9] = {
//////            {3, 1, 6, 5, 7, 8, 4, 9, 2},
//////            {5, 2, 9, 1, 3, 4, 7, 6, 8},
//////            {4, 8, 7, 6, 2, 9, 5, 3, 1},
//////            {2, 6, 3, 4, 1, 5, 9, 8, 7},
//////            {9, 7, 4, 8, 6, 3, 1, 2, 5},
//////            {8, 5, 1, 7, 9, 2, 6, 4, 3},
//////            {1, 3, 8, 9, 4, 7, 2, 5, 6},
//////            {6, 9, 2, 3, 5, 1, 8, 7, 4},
//////            {7, 4, 5, 2, 8, 6, 3, 1, 9}
//////    };
////
//////    solver s(grid);
////////    s.print_board();
//////    std::cout << "-------------REVERSE-------------" << std::endl;
//////    s.solve();
//////    s.print_board();
//////    new_board b = new_board();
//////    b.generate_random_base();
//////    b.print_board();
//////    std::cout << "-------------REVERSE-------------" << std::endl;
//////    b.delete_stones();
//////    b.print_board();
////    auto inputThread = [](tic_tac_toe& player) {
////        std::cout << "\rStart input thread\n";
////        bool q = false;
////        while (!q) {
////            player.input();
////            q = player.get_quit();
////        }
////        std::cout << "\rExit input thread\n";
////    };
////    auto computeThread = [](tic_tac_toe& player) {
////        std::cout << "\rStart compute thread\n";
////        bool q = false;
////        while (!q) {
////            player.take();
////            q = player.get_quit();
////        }
////        std::cout << "\rExit compute thread\n";
////    };
////    auto outputThread = [](tic_tac_toe& player) {
////        std::cout << "\rStart output thread\n";
////        bool q = false;
////        while (!q) {
////            player.output_area();
////            q = player.get_quit();
////        }
////        std::cout << "\rExit output thread\n";
////    };
////
////    set_raw(true);
////
////    tic_tac_toe PP;
////    std::thread t1(inputThread, std::ref(PP));
////    std::thread t2(computeThread, std::ref(PP));
////    std::thread t3(outputThread, std::ref(PP));
////
////    t1.join();
////    t2.join();
////    t3.join();
////
////    set_raw(false);
//////    game g = game();
//////    g.initialize();
////    return 0;
////}
//
//#include "game.hpp"
//
//int main(){
//    game g = game();
//    g.initialize();
//    return 0;
//}
