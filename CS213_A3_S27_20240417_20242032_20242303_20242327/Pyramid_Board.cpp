#include "Pyramid_Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

Pyramid_Board::Pyramid_Board() : Board(3, 5) {
    pyramid = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };
    board = pyramid;
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (!is_empty(x, y)) {
        cout << "Invalid move! Try again.\n";
        return false;
    }

    pyramid[x][y] = symbol;
    board = pyramid;
    n_moves++;
    return true;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    char symbol = player->get_symbol();

    vector<vector<pair<int,int>>> wins = {
        {{1,1}, {1,2}, {1,3}},
        {{2,0}, {2,1}, {2,2}},
        {{2,1}, {2,2}, {2,3}},
        {{2,2}, {2,3}, {2,4}},
        {{0,2}, {1,2}, {2,2}},
        {{0,2}, {1,1}, {2,0}},
        {{0,2}, {1,3}, {2,4}}
    };

    for (auto& line : wins) {
        bool win = true;
        for (auto& cell : line) {
            if (pyramid[cell.first][cell.second] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    return false;
}

bool Pyramid_Board::is_lose(Player<char>* player) {
    char opponent_sym = (player->get_symbol() == 'X') ? 'O' : 'X';
    Player<char> opponent("opponent", opponent_sym, PlayerType::HUMAN);
    return is_win(&opponent);
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves >= 9 && !is_win(player) && !is_lose(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

bool Pyramid_Board::is_empty(int x, int y) {
    if (x < 0 || x >= 3 || y < 0 || y >= 5) return false;
    if (x == 0 && y != 2) return false;
    if (x == 1 && (y < 1 || y > 3)) return false;
    return pyramid[x][y] == ' ';
}

vector<pair<int, int>> Pyramid_Board::get_valid_moves() {
    vector<pair<int, int>> moves;
    if (is_empty(0, 2)) moves.push_back({0, 2});
    for (int y = 1; y <= 3; y++) {
        if (is_empty(1, y)) moves.push_back({1, y});
    }
    for (int y = 0; y < 5; y++) {
        if (is_empty(2, y)) moves.push_back({2, y});
    }
    return moves;
}

void Pyramid_Board::display_pyramid() const {
    cout << "\n    Pyramid Tic-Tac-Toe Board\n";
    cout << "    -------------------------\n\n";

    cout << "        ";
    cout << "[" << pyramid[0][2] << "]";
    cout << "  <- (0,2)";
    cout << endl;

    cout << "      ";
    cout << "[" << pyramid[1][1] << "]  ";
    cout << "[" << pyramid[1][2] << "]  ";
    cout << "[" << pyramid[1][3] << "]";
    cout << "  <- (1,1) (1,2) (1,3)";
    cout << endl;

    cout << "    ";
    cout << "[" << pyramid[2][0] << "]  ";
    cout << "[" << pyramid[2][1] << "]  ";
    cout << "[" << pyramid[2][2] << "]  ";
    cout << "[" << pyramid[2][3] << "]  ";
    cout << "[" << pyramid[2][4] << "]";
    cout << "  <- (2,0) (2,1) (2,2) (2,3) (2,4)";
    cout << endl << endl;
}

Pyramid_UI::Pyramid_UI() : UI("Pyramid Tic-Tac-Toe", 3) {}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        Pyramid_Board* boardPtr = (Pyramid_Board*)player->get_board_ptr();
        boardPtr->display_pyramid();

        cout << player->get_name() << " (" << player->get_symbol() << "), enter move (row column): ";
        cin >> x >> y;
    } else {
        Pyramid_Board* boardPtr = (Pyramid_Board*)player->get_board_ptr();
        vector<pair<int, int>> valid_moves = boardPtr->get_valid_moves();

        if (valid_moves.empty()) {
            x = 0; y = 2;
        } else {
            srand(time(0));
            int index = rand() % valid_moves.size();
            x = valid_moves[index].first;
            y = valid_moves[index].second;
        }
        cout << "Computer chooses: (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

