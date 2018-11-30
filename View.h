#ifndef VIEW_H
#define VIEW_H

#include <gtkmm.h>
#include "DeckGUI.h"
#include "Controller.h"
#include "Observer.h"
#include "Game.h"
#include "PlayerInfo.h"
#include "ImageButton.h"

class View : public Gtk::Window, public Observer
{
public:
    View(Controller*, Game*);
    virtual ~View();
    void update() override;  // Observer Pattern: concrete update() method

private:
    // Observer Pattern: to access Model accessors without having to downcast subject
    Game* gameModel_;

    // Strategy pattern
    Controller* controller_;

    // Card Images
    DeckGUI deck; //Can leave this in or put it with the view

    // The following boxes are based off of the GUI showed in specifications sheet
    Gtk::VBox mainBox;      // Main window used to contain all boxes
    Gtk::HBox menuBox;      // Box used to contain "start new game with seed" and "end game" buttons
    Gtk::Button newGameButton;  // starts a new game
    Gtk::SpinButton seedSpinBox; // a spin box to choose a valid integer seed
    Gtk::Button endGameButton; // end the game and close the application

    Gtk::Label roundLabel; // Label displaying the current round of the game
    Gtk::Frame tableFrame;//The one labeled "cards on table"
    Gtk::VBox tableBox;    //Used to contain 4 horizontal boxes to show cards on table
    Gtk::HBox cardsOfSuit[SUIT_COUNT];//contains one for each suit
    Gtk::Image tableCards[CARD_COUNT];

    Gtk::HBox playerBox;    //Used to store info on the 4 players
    PlayerInfo playerInfos[SUIT_COUNT]; // the information and controls of the 4 players

    Gtk::Frame handFrame; // Frame bounding the player's hand
    Gtk::VBox handBox; // Used to contain widgets corresponsding to the player's hand
    Gtk::Label handLabel; // label displaying whether the play is to PLAY a card or DISCARD one
    Gtk::HBox handCards; // Used to show cards in current player's hand
    ImageButton cardsInHand[RANK_COUNT]; // The 13 buttons at the bottom displaying cards from the hand

    //Add buttons and sub boxes

    // Signal Handlers
    void onNewGameButtonClicked(); // When the newGameButton is clicked
    void onEndGameButtonClicked(); // When the endGameButton is clicked

    // Updates the view for the current round
    // Ensures: all scores and discards are set correctly and the table is reset back to being empty
    void initializeRound();
    void setScoresAndDiscards(); // helper function to set the scores and discards appropriately for each player
    void resetTable(); // helper function to reset the table back to being empty
    void dialogHelper(const char* primary, const std::string& secondary); // shows a message dialog box with the given messsage
};

#endif

