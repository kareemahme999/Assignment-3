#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr
#include <limits> // Required for clearing input buffer
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "SUS.h"
#include "Numerical_Tic_Tac_Toe.h"
using namespace std;

/*──────▄▌▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
 * ───▄▄██▌█ beep beep--------------
 * ▄▄▄▌▐██▌█ -KAREEM_AHMED------------
 * ███████▌█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
 * ▀(@)▀▀▀▀(@)(@)▀▀▀▀▀▀▀▀▀▀▀(@)▀-----------------------
 *
*/
/*
*******# Name of Team Member:  #*******

Name:Kareem Ahmed>>>>ID:20240417:
>>Task_1:
>>Task_2:

Name:Arwa Amin>>>>ID:20242032:
>>Task_3:
>>Task_4:

Name:Mohamed Mortada>>>>ID:20242303
>>Task_5:
>>Task_6:

Name:Maryam Sayed>>>>ID:20242327:
>>Task_7:
>>Task_8:

###ALL Task of Group:###
>>Task_9:
>>Task_10:
>>Task_11:
>>Task_12:

###Bonus Task of Group:###
>>Task_13:
*/













void clear_cin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}



void menu() {
    cout << "-------------------------------------------\n";
    cout << "\n--- 🎮 Welcome to the FCAI Game Center 🎮 ---\n";
    cout << "Individual Games:\n";
    cout << "0: Play Classic X-O Game\n";
    cout << "1: Play SUS\n";
    cout << "2: Play Four-in-a-row\n";//Next update
    cout << "3: 5 x 5 Tic Tac Toe\n";//Next update
    cout << "4: Play Word Tic-tac-toe\n";//Next update
    cout << "5: Play Misère Tic Tac Toe\n";//Next update
    cout << "6: Play Diamond Tic-Tac-Toe\n";//Next update
    cout << "7: Play 4 x 4 Tic-Tac-Toe\n";//Next update
    cout << "8: Play Pyramid Tic-Tac-Toe\n";//Next update
    cout << "-------------------------------------------\n";
    cout << "Group Games:\n";
    cout << "9: Play Numerical Tic-Tac-Toe\n";
    cout << "10: Play Obstacles Tic-Tac-Toe\n";//Next update
    cout << "11: Play Infinity Tic-Tac-Toe\n";//Next update
    cout << "12: Play Ultimate Tic Tac Toe\n";//Next update
    cout << "-------------------------------------------\n";
    cout <<"Bonus Games:\n";
    cout <<"13: Play Memory Tic-Tac-Toe\n";//Next update
    cout <<"14: Exit\n";
    cout << "-------------------------------------------\n";
    cout <<"please enter your choice from the menu(0>>>>14):";
}

void xo_game() {
    cout << "\n===============================\n";
    cout << "  Starting Classic X-O Game  \n";
    cout << "===============================\n" ;

    // Create an instance of the specific UI for X-O using a pointer 
    UI<char>* game_ui = new XO_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char>* xo_board = new X_O_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char>** players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);

    // Run the game loop.
    x_o_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete xo_board;
    delete game_ui;
    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;

cout << "\n--- X-O Game Over ---\n";
}

void run_numerical_game() {
    cout << "\n=====================================\n";
    cout << "  Starting Numerical Tic-Tac-Toe  \n";
    cout << "=====================================\n";

    // Create an instance of the specific UI for X-O using a pointer
    UI<int>* game_ui = new Numerical_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<int>* num_board = new Numerical_Board();



    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<int>** players = game_ui->setup_players();



    // Create the game manager with the board and the array of players.
    GameManager<int> num_game(num_board, players, game_ui);

    // Run the game loop.
    num_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete num_board;
    delete game_ui;
    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;

    cout << "\n--- Numerical Game Over ---\n";

}
void run_sus_game() {
    cout << "\n=====================================\n";
    cout << "       Starting SUS Game  \n";
    cout << "  Goal: Create S-U-S sequences!  \n";
    cout << "=====================================\n";

    UI<char>* game_ui = new SUS_UI();
    SUS_Board* sus_board = new SUS_Board();
    Player<char>** players = game_ui->setup_players();

    // 2. Create and Run Game Manager
    GameManager<char> sus_game(sus_board, players, game_ui);
    sus_game.run();

    // 3. Display Final Results
    cout << "\n--- Final Board State ---\n";
    sus_board->display_board();

    // Display final scores
    cout << "\n--- Final SUS Count ---\n";
    cout << players[0]->get_name() << ">>>Player1 : "
         << sus_board->get_player1_score() << " total SUS sequences\n";
    cout << players[1]->get_name() << ">>>Player2 : "
         << sus_board->get_player2_score() << " total SUS sequences\n";

    if (sus_board->get_player1_score() > sus_board->get_player2_score()) {
        cout << "\n WINNER: " << players[0]->get_name() << " \n";
    } else if (sus_board->get_player2_score() > sus_board->get_player1_score()) {
        cout << "\n WINNER: " << players[1]->get_name() << " \n";
    } else {
        cout << "\nIt's a TIE in score!\n";
        cout << " DRAW! No winner declared. \n";
    }

    // 4. Cleanup
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    delete sus_board;
    delete game_ui;

    cout << "\n--- SUS Game Over ---\n";
}

void run_5x5_tic_tac_toe() {
    cout << "\n=== Starting 5x5 Tic Tac Toe (4 in a row) ===\n";
    UI<char>* game_ui = new XO_UI();
    Board<char>* five_board = new FiveXOBoard();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(five_board, players, game_ui);
    game.run();
    delete five_board;
    delete game_ui;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    cout << "\n--- Game Over ---\n";
}

// ====================================================================
int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

bool run_games=true;
while (run_games) {
    int choice=-1;
    menu();
    cin >> choice;
    if (cin.fail()) {
        cout << "Invalid input. Please enter a number.\n";
        clear_cin();
        continue;
    }
    switch (choice) {
        /*******Individual Games***********/

        case 0: {
            xo_game();
            break;
        }
            /******************/
        case 1: {
            run_sus_game();
            break;
        }
            /******************/

        case 2: {



            break;
        }
            /******************/

        case 3: {
            run_5x5_tic_tac_toe();
            break;
        }
            /******************/

        case 4: {



            break;
        }
            /******************/

        case 5: {



            break;
        }
            /******************/
        case 6: {



            break;
        }
            /******************/

        case 7: {



            break;
        }
            /******************/

        case 8: {



            break;
        }
            /*******Group Games***********/

        case 9: {
            run_numerical_game();
            break;
        }
            /******************/

        case 10: {



            break;
        }
            /******************/

        case 11: {



            break;
        }
            /******************/
        case 12: {



            break;
        }
            /******************/
        case 13: {



            break;
        }
            /******************/
        case 14: {
            run_games = false;
            cout << "Thank you for playing. Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please select from the menu options.\n";
            break;
        }
    }
}





return 0;
}
