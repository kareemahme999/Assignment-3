#include "Obstacles.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

static mt19937& rng() {
    static mt19937 gen((unsigned)
        chrono::high_resolution_clock::now().time_since_epoch().count());
    return gen;
}

ObstaclesBoard::ObstaclesBoard() : Board<char>(6, 6) {
    board.assign(rows, vector<char>(columns, '-'));
    n_moves = 0;
}

// الأفضل :
ObstaclesBoard::~ObstaclesBoard() = default;

bool ObstaclesBoard::in_bounds(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < columns;
}

bool ObstaclesBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (!in_bounds(r, c)) {
        cout << "Invalid position.\n";
        delete move;
        return false;
    }
    if (board[r][c] == '#') {
        cout << "Cell is blocked.\n";
        delete move;
        return false;
    }
    if (board[r][c] != '-') {
        cout << "Cell is already taken.\n";
        delete move;
        return false;
    }

    board[r][c] = s;
    n_moves++;
    delete move;

    if (n_moves % 2 == 0) {
        add_random_obstacles(2);
        cout << "[System] 2 obstacles added.\n";
    }

    return true;
}

void ObstaclesBoard::add_random_obstacles(int count) {
    vector<pair<int,int>> empty;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == '-')
                empty.emplace_back(i, j);

    shuffle(empty.begin(), empty.end(), rng());

    count = min(count, (int)empty.size());
    for (int i = 0; i < count; i++)
        board[empty[i].first][empty[i].second] = '#';
}

bool ObstaclesBoard::is_win(Player<char>* p) {
    char s = p->get_symbol();
    int dr[4] = {0, 1, 1, -1};
    int dc[4] = {1, 0, 1, 1};

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (board[r][c] == s)
                for (int d = 0; d < 4; d++) {
                    int cnt = 1;
                    int rr = r + dr[d], cc = c + dc[d];

                    while (in_bounds(rr, cc) && board[rr][cc] == s) {
                        cnt++;
                        if (cnt == 4)
                            return true;
                        rr += dr[d];
                        cc += dc[d];
                    }
                }
    return false;
}

bool ObstaclesBoard::is_lose(Player<char>* p) {
    // اللعبة لا تدعم حالة "خسارة مباشرة"
    // لازم ترجع قيمة، وإلا ال linker هيفشل
    return false;
}

bool ObstaclesBoard::is_draw(Player<char>* p) {
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (board[r][c] == '-')
                return false;
    return true;
}

bool ObstaclesBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

Obstacles_UI::Obstacles_UI() : UI<char>("Obstacles Tic Tac Toe", 2) {}

Obstacles_UI::~Obstacles_UI() = default;

Move<char>* Obstacles_UI::get_move(Player<char>* p) {

    // لو اللاعب Human
    if (p->get_type() == PlayerType::HUMAN) {
        int r, c;
        cout << p->get_name() << " (" << p->get_symbol()
             << ") enter row and col: ";
        cin >> r >> c;
        return new Move<char>(r, c, p->get_symbol());
    }

    // لو اللاعب Computer → يلعب تلقائيًا
    Board<char>* b = p->get_board_ptr();
    auto mat = b->get_board_matrix();

    for (int i = 0; i < b->get_rows(); i++) {
        for (int j = 0; j < b->get_columns(); j++) {
            if (mat[i][j] == '-') {
                cout << "[Computer] " << p->get_name()
                     << " played at (" << i << ", " << j << ")\n";
                return new Move<char>(i, j, p->get_symbol());
            }
        }
    }

    return new Move<char>(0, 0, p->get_symbol());
}


Player<char>* Obstacles_UI::create_player(string& n, char s, PlayerType t) {
    return new Player<char>(n, s, t);
}
