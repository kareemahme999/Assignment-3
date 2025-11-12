/**
 * @file Numerical_Tic_Tac_Toe.h
 * @brief Defines the Numerical Tic-Tac-Toe specific classes.
 *
 * This file provides:
 * - `Numerical_Board`: A specialized board class for the Numerical Tic-Tac-Toe game.
 * - `Numerical_UI`: A user interface class tailored to this game's setup and player interaction.
 */

#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>   // We need vector to store available numbers
#include <string>

using namespace std;

// #############################################################
// 1. Numerical_Board Class
// #############################################################

class Numerical_Board : public Board<int> {
private:

    int blank_symbol = 0;//علشان ال 0 زلا زوجي زلا فردى

public:

    Numerical_Board();

    bool update_board(Move<int>* move);//update the board all of time
    bool is_win(Player<int>* player);//check winer
    bool is_lose(Player<int>*) { return false; };//check loser
    bool is_draw(Player<int>* player);//painting
    bool game_is_over(Player<int>* player);// stop gaming
};


// #############################################################
//2. Numerical_UI Class
// #############################################################

class Numerical_UI : public UI<int> {
private:
    vector<int> odd_nums; ///(1, 3, 5, 7, 9)
    vector<int> even_nums; /// (2, 4, 6, 8)


    void display_available_nums(Player<int>* player);


    int get_valid_num(Player<int>* player);

public:

    Numerical_UI();


    ~Numerical_UI() {};


    Player<int>* create_player(string& name, int symbol, PlayerType type);


    virtual Move<int>* get_move(Player<int>* player);
    virtual Player<int>** setup_players();//set up players الى ارقام  x,o علشان اعرف اغير من
};

#endif //NUMERICAL_TIC_TAC_TOE_H