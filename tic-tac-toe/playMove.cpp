//
//  playMove.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <tic-tac-toe/playMove.h>

using namespace std;

// Function prototypes for operations on the board, gameOver flag, and validMove flag
void updateBoard(int board[3][3], int row, int col, bool& turn);
void isOver(int board[3][3], bool& gameOver, int& winCode);
void isValid(int board[3][3], bool& validMove, int row, int col);

void playMove(int board[3][3], int row, int col, bool& turn, bool& validMove, bool& gameOver, int& winCode) {

    // If the game is over, do nothing
    if (gameOver) return;

    // Insert your code here
    //Check whether the move is valid first before doing any operation
    isValid(board, validMove, row, col);
    if (validMove) {
        
        updateBoard(board, row, col, turn);
        
        // reverse the order of the player
        if (turn) {
            turn = false;
        } else if (!turn) {
            turn = true;
        }
        
        //To determine win code
        if ((board[0][0] + board[0][1] + board[0][2] == 3) || (board[0][0] + board[0][1] + board[0][2] == -3)) {
            winCode = 1;
        }
        if ((board[1][0] + board[1][1] + board[1][2] == 3) || (board[1][0] + board[1][1] + board[1][2] == -3)) {
            winCode = 2;
        }
        if ((board[2][0] + board[2][1] + board[2][2] == 3) || (board[2][0] + board[2][1] + board[2][2] == -3)) {
            winCode = 3;
        }
        if ((board[0][0] + board[1][0] + board[2][0] == 3) || (board[0][0] + board[1][0] + board[2][0] == -3)) {
            winCode = 4;
        }
        if ((board[0][1] + board[1][1] + board[2][1] == 3) || (board[0][1] + board[1][1] + board[2][1] == -3)) {
            winCode = 5;
        }
        if ((board[0][2] + board[1][2] + board[2][2] == 3) || (board[0][2] + board[1][2] + board[2][2] == -3)) {
            winCode = 6;
        }
        if ((board[0][0] + board[1][1] + board[2][2] == 3) || (board[0][0] + board[1][1] + board[2][2] == -3)) {
            winCode = 7;
        }
        if ((board[2][0] + board[1][1] + board[0][2] == 3 ) || (board[2][0] + board[1][1] + board[0][2] == -3)) {
            winCode = 8;
        }
    }

    // The function must always print the output specified in the handout before it exits
    // Use the standard output (i.e., cout) to print the output

    // Insert code to print the output below
    // Print out the board
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            cout << board[i][j] << " ";  
        }
    }
    
    // Determine whether the game is over
    isOver(board, gameOver, winCode);
    
    cout << row << " " << col << " " << turn << " " << validMove << " " << gameOver << " " << winCode << endl;

}

// Function to update board every time there is a valid move and turn
void updateBoard(int board[3][3], int row, int col, bool& turn) {
    if(turn) {
        //It is X's turn
        board[row][col] = 1;
    } else if(!turn) {
        //It is O's turn
        board[row][col] = -1;
    }
}

// Function to determine whether the game is over by changing gameOver flag
void isOver(int board[3][3], bool& gameOver, int &winCode) {
    if(winCode != 0) {
        gameOver = true;
    }
    
    //Set gameOver to true so that it is only false when there is blank spaces when win code is 0
    gameOver = true;
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            if (board[i][j] == Empty && winCode == 0) {
                gameOver = false;
            } 
        }
    }

    
}

// Function to determine whether a move is valid
void isValid(int board[3][3], bool& validMove, int row, int col) {
    if (board[row][col] == Empty) {
        validMove = true;
    } else {
        validMove = false;
    }
}

