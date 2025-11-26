#ifndef MISERE_TIC_TAC_TEO_H
#define MISERE_TIC_TAC_TEO_H
#include "BoardGame_Classes.h"
using namespace std;

class MiserBoard : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:

    MiserBoard();


    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*player);

    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};

class MiserUI : public UI<char> {
public:

    MiserUI();

    ~MiserUI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    virtual Move<char>* get_move(Player<char>* player);
};

#endif
