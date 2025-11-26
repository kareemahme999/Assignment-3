#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

using namespace std;

class Pyramid_Board : public Board<char> {
private:
    vector<vector<char>> pyramid;

public:
    Pyramid_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_empty(int x, int y);
    vector<pair<int, int>> get_valid_moves();
    void display_pyramid() const;
};

class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

void play_pyramid_game();

#endif