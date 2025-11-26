#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <queue>

using namespace std;

class Infinity_Board : public Board<char> {
private:
    queue<pair<int, int>> moveHistory;

public:
    Infinity_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void remove_oldest_move();
};

class Infinity_UI : public UI<char> {
public:
    Infinity_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

void play_infinity_game();

#endif