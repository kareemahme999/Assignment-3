#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "BoardGame_Classes.h"
#include <string>

class ObstaclesBoard : public Board<char> {
public:
    ObstaclesBoard();
    ~ObstaclesBoard() override;

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;   // لازم يكون موجود
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

private:
    void add_random_obstacles(int count);
    bool in_bounds(int r, int c) const;
};

class Obstacles_UI : public UI<char> {
public:
    Obstacles_UI();
    ~Obstacles_UI() override;

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

// declaration only (implementation in .cpp)
void run_obstacles_game();

#endif
