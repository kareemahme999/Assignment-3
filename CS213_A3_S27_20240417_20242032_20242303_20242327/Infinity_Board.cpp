#include "Infinity_Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

using namespace std;

Infinity_Board::Infinity_Board() : Board(3, 3) {
    n_moves = 0;
    // Initialize board with spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if move is valid
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid position! Use 0-2 for row and column.\n";
        return false;
    }

    if (board[x][y] != ' ') {
        cout << "Cell (" << x << "," << y << ") is already occupied by '" << board[x][y] << "'! Choose another one.\n";
        return false;
    }

    // Make the move
    board[x][y] = symbol;
    moveHistory.push({x, y});
    n_moves++;

    cout << "✅ Move " << n_moves << " made at (" << x << "," << y << ")\n";

    // Remove oldest move after every 3 moves
    if (n_moves % 3 == 0 && n_moves > 0) {
        remove_oldest_move();
    }

    return true;
}

void Infinity_Board::remove_oldest_move() {
    if (!moveHistory.empty()) {
        pair<int, int> oldest = moveHistory.front();
        moveHistory.pop();

        cout << "🗑️ Oldest move at (" << oldest.first << "," << oldest.second
             << ") has been removed!\n";
        board[oldest.first][oldest.second] = ' ';
    }
}

bool Infinity_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
            return true;
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

bool Infinity_Board::is_lose(Player<char>* player) {
    char opponent_sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("opponent", opponent_sym, PlayerType::HUMAN);
    return is_win(&opponent);
}

bool Infinity_Board::is_draw(Player<char>* player) {
    if (n_moves >= 15 && !is_win(player) && !is_lose(player)) {
        return true;
    }
    return false;
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

Infinity_UI::Infinity_UI() : UI("Infinity Tic-Tac-Toe - Moves disappear every 3 turns!", 3) {}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter move (row column): ";
        cin >> x >> y;
    } else {
        // Computer player - use the board directly to find empty cells
        Infinity_Board* boardPtr = dynamic_cast<Infinity_Board*>(player->get_board_ptr());

        // Find all empty cells
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (boardPtr->get_board_matrix()[i][j] == ' ') {
                    emptyCells.push_back({i, j});
                }
            }
        }

        if (emptyCells.empty()) {

            x = 0; y = 0;
        } else {
            srand(time(0));
            int index = rand() % emptyCells.size();
            x = emptyCells[index].first;
            y = emptyCells[index].second;
        }

        cout << "Computer chooses: (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

