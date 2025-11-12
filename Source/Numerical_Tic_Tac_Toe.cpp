#include <bits/stdc++.h>
#include "Numerical_Tic_Tac_Toe.h"

/*──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
 * ───▄▄██▌█ beep beep--------------
 * ▄▄▄▌▐██▌█ -KAREEM_AHMED------------
 * ███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
 * ▀(@)▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀(@)▀-----------------------
 *
*/
using namespace std;

// draw the board
Numerical_Board::Numerical_Board() : Board(3, 3) {

for (auto& row : board)
    for (auto& cell : row)
        cell = blank_symbol;//blank_symbol>>0
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number_Place = move->get_symbol();// the number that the player wants to place on the board
    // check if the move is valid or not
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
            (board[x][y] == blank_symbol )) {
        n_moves++;
        board[x][y] = number_Place;
        return true;
    }
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) && number_Place == 0) {
        n_moves--;
        board[x][y] = blank_symbol;
        return true;

    }

    return false;
}

// chack if the sum of the three numbers is equal to 15 or no
bool check_win(int x , int y , int number_Place) {
    return (x != 0 && y != 0 && number_Place != 0) && ((x + y + number_Place) == 15);
}
bool Numerical_Board::is_win(Player<int>* player) {
    for (int i = 0; i < rows; ++i) {
        if (check_win(board[i][0], board[i][1], board[i][2]))return true;//row of win
        if (check_win(board[0][i], board[1][i], board[2][i]))return true;// column of win

    }
    if (check_win(board[0][0], board[1][1], board[2][2]))return true;// positive diagonal of win
    if (check_win(board[0][2], board[1][1], board[2][0]))return true;// negative diagonal of win
    return false;


}
bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}
bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}


Numerical_UI::Numerical_UI() : UI<int>( "",3) {
    // Constructor: Initialize the lists of available numbers
    odd_nums = {1, 3, 5, 7, 9};
    even_nums = {2, 4, 6, 8};
}




/*******************************************************************/



Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cout << "\n--- Setting up Player 1 ---\n";
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);

    cout << "\n--- Setting up Player 2 ---\n";
    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);

    // rand() % 2 هترجع يا 0 يا 1
    int random_assignment = rand() % 2;

    if (random_assignment == 0) {
        // name1:Odd Number

        players[0] = create_player(name1, 1, type1);
        players[1] = create_player(name2, 2, type2);

    } else {
        // name1:Even Number

        players[0] = create_player(name1, 2, type1);
        players[1] = create_player(name2, 1, type2);
    }

    return players;
}
/*******************************************************************/
//  هنا نوع الاعب و هو خد زوجى ولا فردى بيتم تحدي
Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    // symbol is 1 for Player 1>> Odd and 2 for Player 2>> Even
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " ("
         << (symbol == 1 ? "Odd Nums" : "Even Nums") << ")\n";

    return new Player<int>(name, symbol, type);
}

void Numerical_UI::display_available_nums(Player<int>* player) {
    if (player->get_symbol() == 1) { // Player 1 (Odd)
        cout << "Available odd numbers: ";
        for (int num : odd_nums) cout << num << " ";
        cout << "\n";
    } else { // Player 2 (Even)
        cout << "Available even numbers: ";
        for (int num : even_nums) cout << num << " ";
        cout << "\n";
    }
}



int Numerical_UI::get_valid_num(Player<int>* player) {
    // Helper function to get a valid number from the user and remove it
    vector<int>& num_list = (player->get_symbol() == 1) ? odd_nums : even_nums;

    int chosen_num;
    bool valid_choice = false;

    while (!valid_choice) {
        cout << "Please choose one of the available numbers: ";
        cin >> chosen_num;

        // Search for the chosen number in the correct list
        auto it = std::find(num_list.begin(), num_list.end(), chosen_num);

        if (it != num_list.end()) { // Found it!
            valid_choice = true;
            num_list.erase(it); // Remove the number so it can't be used again
        } else {
            cout << "Invalid choice. That number is not available. Try again.\n";
        }
    }
    return chosen_num;
}




Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y;
    int chosen_num;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlayer " << player->get_name() << "'s turn.\n";

        // 1. Show and get a valid number
        display_available_nums(player);
        chosen_num = get_valid_num(player);

        // 2. Get coordinates
        cout << "Enter coordinates (x y) to place " << chosen_num << " (0 to 2): ";
        cout<<"\n Enter x  : ";
        cin >> x;
        cout<<"\n Enter y  : ";
        cin>> y;

    }

    else if (player->get_type() == PlayerType::COMPUTER) {
        // ---  Simple Random AI ---

        // 1. Get the correct number list
        vector<int>& num_list = (player->get_symbol() == 1) ? odd_nums : even_nums;

        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != 0); // 0 هو الـ blank_symbol


        if (num_list.empty()) {
            chosen_num = -1;
        } else {
            int rand_index = rand() % num_list.size();
            chosen_num = num_list[rand_index];
            num_list.erase(num_list.begin() + rand_index); // Remove it from the list
        }

        cout << "\nComputer player " << player->get_name()
             << " chose " << chosen_num << " and placed it at (" << x << ", " << y << ")\n";
    }
    return new Move<int>(x, y, chosen_num);
}

