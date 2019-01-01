//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include <tic-tac-toe/playMove.h>

using namespace std;
using namespace sf;


int main() {

    /************************************************************************************************************/
    /* The following variables define the state of the game                                                     */
    /************************************************************************************************************/

    // You should complete the following declarations
    // Make sure to initialize the variables

    // The game board array
    int gameBoard[3][3] = {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty};

    // An boolean that represents the turn in the game
    bool is_turn = true;
    // A boolean to represent if the move is valid
    bool is_valid = true;
    // A boolean to represent if the game is over
    bool is_game_over = false;

    // An integer that represents the default win code
    int winCode = 0;
    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* The loading of the X image is shown. Repeat for the rest of the images                                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);

    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture blank_texture;
    if (!blank_texture.loadFromFile("blank.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite blank_sprite(blank_texture);

    
    /************************************************************************************************************/
    /* Insert code that creates the window and displays it                                                      */
    /************************************************************************************************************/

    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them

    // The tile size is the size of the images
    const int tileSize = X_texture.getSize().x;

    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 cell sizes plus 2 barWidth's
    const int barWidth = tileSize / 20;
    const int barHeight = boardSize * tileSize + (boardSize - 1) * barWidth;

    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize * tileSize + (boardSize-1) * barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "ECE244 Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);

    // Set the Icon that appears in the task bar when the window is minimized
    // Insert you code here, see the lab handout
    sf::Image myFirstWindowIcon;
    if (!myFirstWindowIcon.loadFromFile("icon.jpg")) {
        return EXIT_FAILURE;
    }
    
    window.setIcon(myFirstWindowIcon.getSize().x,
        myFirstWindowIcon.getSize().y,
        myFirstWindowIcon.getPixelsPtr());

    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // Insert your code here
    sf::RectangleShape verticalBar(sf::Vector2f(barWidth, windowSize));
    sf::RectangleShape horizontalBar(sf::Vector2f(windowSize, barWidth));


    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/

    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // This is the handling of the close window event
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Left mouse button pressed: get the click position and play the move
            // is_game_over is a variable you should define above
            int xPosition;
            int yPosition;
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // left mouse button is pressed: get the coordinates in pixels
                // Insert your code to get the coordinates here
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    // left mouse button is pressed
                    // Get the coordinates in pixels.
                    sf::Vector2i localPosition = Mouse::getPosition(window);
                    
                    xPosition = localPosition.x;
                    yPosition = localPosition.y;
                }
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // Insert your code below
                int col = xPosition / tileSize;
                int row = yPosition / tileSize;
               
                // Play the move by calling the playMove function
                // Insert your code below
                playMove(gameBoard, row, col, is_turn, is_valid, is_game_over, winCode);
            }
        }

        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // Insert your code here
        
        // 
        // For the first horizontal bar
        horizontalBar.setPosition(0, tileSize);
        horizontalBar.setFillColor(sf::Color::Black);
        window.draw(horizontalBar);

        // For the second horizontal bar
        horizontalBar.setPosition(0, 2 * tileSize + barWidth);
        horizontalBar.setFillColor(sf::Color::Black);
        window.draw(horizontalBar);

        // For the first vertical bar
        verticalBar.setPosition(tileSize, 0);
        verticalBar.setFillColor(sf::Color::Black);
        window.draw(verticalBar);

        // For the second vertical bar
        verticalBar.setPosition(windowSize - tileSize - barWidth, 0);
        verticalBar.setFillColor(sf::Color::Black);
        window.draw(verticalBar);

        //initialize and draw 9 blank sprites
        for (int i = 0; i < 3; i ++) {
            for (int j = 0; j < 3; j ++) {
                blank_sprite.setPosition(j * (tileSize + barWidth), i * (tileSize + barWidth));
                window.draw(blank_sprite);
            }
        }
    
        // Print X or O sprite according to the turn flag
        for (int i = 0; i < 3; i ++) {
            for (int j = 0; j < 3; j ++) {
                if (gameBoard[j][i] == 1) {
                    X_sprite.setPosition(i * (tileSize + barWidth), j * (tileSize + barWidth));
                    window.draw(X_sprite);
                } else if (gameBoard[j][i] == -1) {
                    O_sprite.setPosition(i * (tileSize + barWidth), j * (tileSize + barWidth));
                    window.draw(O_sprite);
                }
                
            }
        }
       
        
        // Print the winning bar for win codes 1-3
        if (winCode == 1 || winCode == 2 || winCode == 3) {
            sf::RectangleShape winHorBar(sf::Vector2f(windowSize, 10));
            winHorBar.setPosition(0, 0.5 * tileSize + (winCode - 1) * tileSize );
            winHorBar.setFillColor(sf::Color::White);
            window.draw(winHorBar);
            
        // Print the winning bar for win codes 4-6
        } else if (winCode == 4 || winCode == 5 || winCode == 6) {
            sf::RectangleShape winVerBar(sf::Vector2f(10, windowSize));
            winVerBar.setPosition(0.5 * tileSize + (winCode - 4) * tileSize, 0);
            winVerBar.setFillColor(sf::Color::White);
            window.draw(winVerBar);
            
        // Print the winning bar for win codes 7&8
        } else if (winCode == 7 || winCode == 8) {
            sf::RectangleShape winSlantBar(sf::Vector2f(10, windowSize * sqrt(2)));
            
            if (winCode == 7) {
                winSlantBar.setPosition(0, 0);
                winSlantBar.rotate(-45);
                winSlantBar.setFillColor(sf::Color::White);
                window.draw(winSlantBar); 
            } else {
                winSlantBar.setPosition(0, windowSize);
                winSlantBar.rotate(-135);
                winSlantBar.setFillColor(sf::Color::White);
                window.draw(winSlantBar); 
            }
        }
            

        // Display to the window
        window.display();
    }
    

    return EXIT_SUCCESS;
}
