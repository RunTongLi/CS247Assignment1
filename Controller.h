#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Game.h"

//Controller class of MVC model
class Controller
{
public:
    //Constructor with given game model.
    //ensures: a new model with the given model pointer is created
    Controller(Game* gameModel);
    
    //control function to start a new game 
    //modifies: gameModel_
    //ensures a new game is created when the button click event is detected on the newGameButton
    void newGameButtonClicked(const int seed, const bool* areHuman);
    
     //control function to end a game
    //modifies: gameModel_
    //ensures the game is ended when the button click event is detected on the endGameButton
    void endGameButtonClicked();
    
    //control function to process a card click
    //requires: 0<index<13
    //modifies: gameModel_
    //ensures: the gameModel_ will check whether the indexth card can be played/discarded by the player
    void cardClicked(const int index);
    
    //control function to process the rage quit button being clicked
    //modifies: gameModel_
    //ensures: the gameModel_ acknowledges a button click event on the ragequit button
    void rageQuitButtonClicked();
private:
    Game* gameModel_;
}; // Controller


#endif
