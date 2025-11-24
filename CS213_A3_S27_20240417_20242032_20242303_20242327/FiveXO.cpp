#include "FiveXO.h"
#include <vector>

using namespace std;

FiveXOBoard::FiveXOBoard() : Board<char>(5, 5) {
    // initialize board with spaces
    board.assign(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    n_moves = 0;
}

// Update board: uses Move.get_x(), get_y(), get_symbol()
bool FiveXOBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char v = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) {
        // invalid coordinate
        return false;
    }
    if (board[r][c] != ' ') return false;

    board[r][c] = v;
    ++n_moves;
    return true;
}

// count all distinct length-3 contiguous sequences for 'symbol'
int FiveXOBoard::count_three_in_a_row(char symbol) const {
    int count = 0;

    // Horizontal sequences
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - WIN_LENGTH; ++j) {
            bool ok = true;
            for (int k = 0; k < WIN_LENGTH; ++k)
                if (board[i][j + k] != symbol) { ok = false; break; }
            if (ok) ++count;
        }
    }

    // Vertical sequences
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - WIN_LENGTH; ++i) {
            bool ok = true;
            for (int k = 0; k < WIN_LENGTH; ++k)
                if (board[i + k][j] != symbol) { ok = false; break; }
            if (ok) ++count;
        }
    }

    // Main diagonals (top-left -> bottom-right)
    for (int i = 0; i <= rows - WIN_LENGTH; ++i) {
        for (int j = 0; j <= columns - WIN_LENGTH; ++j) {
            bool ok = true;
            for (int k = 0; k < WIN_LENGTH; ++k)
                if (board[i + k][j + k] != symbol) { ok = false; break; }
            if (ok) ++count;
        }
    }

    // Anti-diagonals (top-right -> bottom-left)
    for (int i = 0; i <= rows - WIN_LENGTH; ++i) {
        for (int j = WIN_LENGTH - 1; j < columns; ++j) {
            bool ok = true;
            for (int k = 0; k < WIN_LENGTH; ++k)
                if (board[i + k][j - k] != symbol) { ok = false; break; }
            if (ok) ++count;
        }
    }

    return count;
}

int FiveXOBoard::get_score_for(char symbol) const {
    return count_three_in_a_row(symbol);
}

// game logic wrappers:
// We want the game to end when 24 moves have been played (one cell left).
// When n_moves < 24: none of is_win/is_lose/is_draw should return true.
// When n_moves == 24: compare scores and return accordingly.

bool FiveXOBoard::is_win(Player<char>* p) {
    if (n_moves < BOARD_SIZE * BOARD_SIZE - 1) return false; // wait until 24 moves
    char sym = p->get_symbol();
    // opponent symbol:
    char opp = (sym == 'X') ? 'O' : 'X';
    int s = get_score_for(sym);
    int o = get_score_for(opp);
    return s > o;
}

bool FiveXOBoard::is_lose(Player<char>* p) {
    if (n_moves < BOARD_SIZE * BOARD_SIZE - 1) return false;
    char sym = p->get_symbol();
    char opp = (sym == 'X') ? 'O' : 'X';
    int s = get_score_for(sym);
    int o = get_score_for(opp);
    return o > s;
}

bool FiveXOBoard::is_draw(Player<char>* p) {
    if (n_moves < BOARD_SIZE * BOARD_SIZE - 1) return false;
    char sym = p->get_symbol();
    char opp = (sym == 'X') ? 'O' : 'X';
    int s = get_score_for(sym);
    int o = get_score_for(opp);
    return s == o;
}

bool FiveXOBoard::game_is_over(Player<char>* p) {
    // optional: mirror is_draw/is_win/is_lose behavior
    return n_moves >= BOARD_SIZE * BOARD_SIZE - 1;
}
