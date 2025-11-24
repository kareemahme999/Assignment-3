#ifndef _FIVE_X_O_H
#define _FIVE_X_O_H

#include "BoardGame_Classes.h"

/*
  FiveXOBoard for the variant:
  - 5x5 board
  - Players alternate placing X/O until 24 moves are done (1 cell remains empty)
  - Score is the count of all 3-in-a-row sequences (horizontal, vertical, diagonal)
  - Winner is player with higher score; tie => draw
*/

class FiveXOBoard : public Board<char> {
private:
    const int WIN_LENGTH = 3;      // for counting sequences of length 3
    const int BOARD_SIZE = 5;

    // helper: count number of 3-in-a-row sequences for a given symbol
    int count_three_in_a_row(char symbol) const;

public:
    FiveXOBoard();

    // basic overrides
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;

    // helper to fetch scores (convenience)
    int get_score_for(char symbol) const;
};

#endif // _FIVE_X_O_H
