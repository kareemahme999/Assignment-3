
#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <string>
#include <vector>
using namespace std;

/*──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
 * ───▄▄██▌█ beep beep--------------
 * ▄▄▄▌▐██▌█ -KAREEM_AHMED------------
 * ███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
 * ▀(@)▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀(@)▀-----------------------
 *
*/

class FourInARow_Board : public Board<char> {
private:
    const char blank_symbol = ' ';

public:
    // الحجم 6 صفوف و 7 أعمدة
    FourInARow_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; }

    bool is_draw(Player<char>* player);

    bool game_is_over(Player<char>* player);
    // بيساعد انى الصف فاضى
    int get_available_row(int y) const;
};

// #############################################################
// 2. FourInARow_UI Class
// #############################################################

class FourInARow_UI : public UI<char> {
private:
// بيساعد انى العمود فاضى
 int get_valid_column(Player<char>* player);

public:
    // Constructor: حجم اللوحة 7*6
    FourInARow_UI();

    ~FourInARow_UI() {}

    // إنشاء لاعب جديد (X أو O)
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    //  حركة اللاعب (أخذ رقم العمود)
    virtual Move<char>* get_move(Player<char>* player);
    // إعداد اللاعبين وتعيين الرموز (X و O)
    virtual Player<char>** setup_players();
};



#endif //FOUR_IN_A_ROW_H
