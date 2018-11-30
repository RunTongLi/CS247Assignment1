/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "Controller.h"

//Contructs a new controller with the given game model
Controller::Controller(Game* gameModel) : gameModel_(gameModel) {}

//Proccesses a button click on the newGameButton by starting the game using the given seed
void Controller::newGameButtonClicked(const int seed, const bool* areHuman)
{
    gameModel_->start(seed, areHuman);
}

//Processes a button click on a card 
void Controller::cardClicked(const int index)
{
    //Do nothing if game is already over
    if (gameModel_->gameOver()) {
        return;
    }
    //Based on the legal plays of the current player, either process the turn with the DISCARD command or the PLAY command
    const Player* player = gameModel_->players()[gameModel_->currentPlayer()];
    gameModel_->processTurn({ gameModel_->legalPlays().size() == 0 ? DISCARD : PLAY, player->hand()[index] });
}

void Controller::rageQuitButtonClicked()
{
    //Ragequits the current player 
    gameModel_->rageQuit();
}
