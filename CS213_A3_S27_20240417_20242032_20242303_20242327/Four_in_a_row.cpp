#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Four_in_a_row.h"
using namespace std;

/*──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
 * ───▄▄██▌█ beep beep--------------
 * ▄▄▄▌▐██▌█ -KAREEM_AHMED------------
 * ███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
 * ▀(@)▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀(@)▀-----------------------
 *
*/

bool check_four_in_a_row(const std::vector<std::vector<char>>& board, int r, int c, int dr, int dc, char symbol) {
    int rows = board.size();
    int cols = board[0].size();
    int count = 0;

    for (int i = 0; i < 4; ++i) {
        int nr = r + i * dr;
        int nc = c + i * dc;

        // التحقق من أن الإحداثيات داخل حدود اللوحة وأن الخلية تحتوي على رمز اللاعب
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == symbol) {
            count++;
        } else {
            // إذا خرجنا عن الحدود أو وجدنا رمز مختلف
            return false;
        }
    }
    return count == 4; // يجب أن يصل العد إلى 4
}


/*
 * Implementation for FourInARow_Board
 */

// bordered board constructor 6*7
FourInARow_Board::FourInARow_Board() : Board<char>(6, 7) {
    // 6 rows (0-5), 7 columns (0-6)
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}


// chack if the column is available or no
int FourInARow_Board::get_available_row(int y) const {
    // البحث من الأسفل إلى الأعلى
    for (int i = rows - 1; i >= 0; --i) {
        if (board[i][y] == blank_symbol) {
            return i;
        }
    }
    return -1; // كدا العمود اتملى
}

bool FourInARow_Board::update_board(Move<char>* move) {
    int y = move->get_y(); // y هو رقم العمود الذي اختاره اللاعب
    char symbol = move->get_symbol();

    // 1. التحقق من صلاحية العمود
    if (y < 0 || y >= columns) {
        return false;
    }

    // 2. تحديد الصف المتاح (س) لوضع العلامة
    int x = get_available_row(y);

    if (x != -1) {
        // تحديث إحداثي x (الصف) الذي تم تحديده
        // move->set_x(x);  <-- قم بحذف أو التعليق على هذا السطر!

        n_moves++;
        board[x][y] = symbol; // هذا هو الأهم، استخدام x لتحديث اللوحة
        return true;
    }
    // العمود ممتلئ
    return false;
}
bool FourInARow_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    int dr[] = {0, 1, 1, 1}; // تغير الصف
    int dc[] = {1, 0, 1, -1}; // تغير العمود

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] == symbol) {
                // التحقق من 4 اتجاهات بدءاً من (r, c)
                for (int i = 0; i < 4; ++i) {
                    if (check_four_in_a_row(board, r, c, dr[i], dc[i], symbol)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool FourInARow_Board::is_draw(Player<char>* player) {
    // الحد الأقصى للحركات هو 6 * 7 = 42
    return (n_moves == rows * columns && !is_win(player));
}

// game is over if is_win() or is_draw()
bool FourInARow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


FourInARow_UI::FourInARow_UI() : UI<char>("Four-in-a-row", 6) {
    // Constructor
}

// إعداد اللاعبين وتعيين الرموز (X و O)
Player<char>** FourInARow_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cout << "\n--- Setting up Player 1 (X) ---\n";
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);

    cout << "\n--- Setting up Player 2 (O) ---\n";
    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);

    // Player 1 is always 'X', Player 2 is always 'O'
    players[0] = create_player(name1, 'X', type1);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

// إنشاء لاعب جديد
Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

// مساعدة للحصول على عمود صالح من اللاعب
int FourInARow_UI::get_valid_column(Player<char>* player) {
    int column;
    int cols = player->get_board_ptr()->get_columns();
    FourInARow_Board* board_ptr = dynamic_cast<FourInARow_Board*>(player->get_board_ptr());

    while (true) {
        cout << "Enter column number (0 to " << cols - 1 << "): ";
        if (!(cin >> column)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (column >= 0 && column < cols) {
            // check if the column is available or not
            if (board_ptr->get_available_row(column) != -1) {
                return column;
            } else {
                cout << "Column " << column << " is full. Try another column.\n";
            }
        } else {
            cout << "Invalid column number. Must be between 0 and " << cols - 1 << ".\n";
        }
    }
}

// الحصول على حركة اللاعب (أخذ رقم العمود)
Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int y; // y هو رقم العمود
    char symbol = player->get_symbol();
    int cols = player->get_board_ptr()->get_columns();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlayer " << player->get_name() << " (" << symbol << ")'s turn.\n";

        // 1. الحصول على عمود صالح
        y = get_valid_column(player);

    } else if (player->get_type() == PlayerType::COMPUTER) {
        // ---  Simple Random AI ---
        FourInARow_Board* board_ptr = dynamic_cast<FourInARow_Board*>(player->get_board_ptr());

        do {
            y = rand() % cols;
        } while (board_ptr->get_available_row(y) == -1);

        cout << "\nComputer player " << player->get_name()
             << " (" << symbol << ") chose column " << y << "\n";
    }

    return new Move<char>(-1, y, symbol);
}