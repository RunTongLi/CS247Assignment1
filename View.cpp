/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "Observer.h"
#include "View.h"
#include "Controller.h"
#include "DeckGUI.h"
#include <string>

// Creates buttons with labels. Sets butBox elements to have the same size,
// with 10 pixels between widgets
View::View(Controller* c, Game* g) : gameModel_(g), controller_(c)
{
    // Set some properties of the window.
    set_title("STRAIGHTS");
    set_border_width(10);

    // Add panels to the window
    add(mainBox);

    newGameButton.set_label("Start new game with seed");
    newGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onNewGameButtonClicked));

    seedSpinBox.set_range(0, __INT_MAX__);
    seedSpinBox.set_increments(1, -1);

    endGameButton.set_label("End current game");
    endGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onEndGameButtonClicked));

    // set_homogeneous equally spaces out our widgets (in this case to thrids of the width) to make it look neater
    menuBox.set_homogeneous();

    menuBox.add(newGameButton);
    menuBox.add(seedSpinBox);
    menuBox.add(endGameButton);

    mainBox.add(menuBox);

    // Add the table
    mainBox.add(tableFrame);
    tableFrame.set_label("Cards on the table");
    tableFrame.add(tableBox);
    tableBox.set_spacing(1); // so cards don't touch each other
    resetTable();

    for (int i = 0; i < SUIT_COUNT; ++i) {
        tableBox.add(cardsOfSuit[i]);
        cardsOfSuit[i].set_spacing(1);
        for (int j = 0; j < RANK_COUNT; ++j) {
            cardsOfSuit[i].add(tableCards[i * RANK_COUNT + j]);
        }
    }

    // Add round label
    mainBox.add(roundLabel);

    // Add the players
    mainBox.add(playerBox);
    playerBox.set_homogeneous();
    for (int a = 0; a < SUIT_COUNT; ++a) {
        playerBox.add(playerInfos[a].frame);
        playerInfos[a].controller_ = controller_;
        //initialize text
        playerInfos[a].setId(a + 1);
        playerInfos[a].setPoints(0);
        playerInfos[a].setDiscards(0);
    }

    // Add hand
    mainBox.add(handFrame);

    handFrame.set_label("Current Player's Hand:");
    handFrame.add(handBox);
    handBox.add(handLabel);
    handBox.add(handCards);
    handCards.set_homogeneous();
    for (int b = 0; b < RANK_COUNT; ++b) {
        cardsInHand[b].index = b;
        cardsInHand[b].controller_ = controller_;
        cardsInHand[b].image.set(deck.null());
        handCards.add(cardsInHand[b].button);
    }

    // The final step is to display the buttons (they display themselves)
    show_all();

    // Register view as observer of model
    gameModel_->subscribe(this);

} // View::View

void View::initializeRound()
{
    roundLabel.set_text("Round " + std::to_string(gameModel_->currentRound()));
    setScoresAndDiscards();
    resetTable();
}

void View::setScoresAndDiscards()
{
    auto players = gameModel_->players();
    for (int i = 0; i < PLAYER_COUNT; i++) {
        auto player = players[i];
        playerInfos[i].setPoints(player->totalPoints());
        playerInfos[i].setDiscards(player->discards().size());
    }
}

void View::onEndGameButtonClicked()
{
    Gtk::Main::quit();
}

void View::resetTable()
{
    for (int i = 0; i < CARD_COUNT; i++) {
        tableCards[i].set(deck.null());
    }
}

void View::onNewGameButtonClicked()
{
    bool areHuman[PLAYER_COUNT];
    for (int i = 0; i < PLAYER_COUNT; i++) {
        areHuman[i] = playerInfos[i].isHuman;
    }

    for (auto& playerInfo : playerInfos) {
        playerInfo.setStarted();
    }

    // get values from the UI widgets and pass on to the controller
    controller_->newGameButtonClicked(static_cast<int>(seedSpinBox.get_value()), areHuman);
}

View::~View() {}

void View::dialogHelper(const char* primary, const std::string& secondary)
{
    Gtk::MessageDialog dialog(*this, primary);
    dialog.set_secondary_text(secondary);
    dialog.run();
}

void View::update()
{
    // if the message stream buffer is not empty
    if (!gameModel_->out().tellp() == std::streampos(0)) {
        // Make an "info" message box with the contents
        dialogHelper("Info", gameModel_->out().str());
        gameModel_->out().str("");
        gameModel_->out().clear();
    } else if (gameModel_->winnerPlayerId() != -1) {
        // if there's a winner
        setScoresAndDiscards();
        dialogHelper("Game Over!", "Player " + std::to_string(gameModel_->winnerPlayerId()) + " wins!");

        for (auto& playerInfo : playerInfos) {
            playerInfo.setNotStarted();
        }
        return;
    }

    if (gameModel_->newRoundDidStart()) {
        initializeRound();
    }

    const int currentPlayerIndex = gameModel_->currentPlayer();
    const int previousPlayerIndex = currentPlayerIndex == 0 ? 3 : currentPlayerIndex - 1;
    const Player* previousPlayer = gameModel_->players()[previousPlayerIndex];

    playerInfos[previousPlayerIndex].setDiscards(previousPlayer->discards().size());

    const Player* player = gameModel_->players()[currentPlayerIndex];

    if (player->isBot()) {
        // disable player related controls (ragequit)
        for (int i = 0; i < PLAYER_COUNT; i++) {
            playerInfos[i].disable();
        }
    } else {
        // only enable controls for the current player, disable the rest
        for (int i = 0; i < PLAYER_COUNT; i++) {
            if (i == currentPlayerIndex) {
                playerInfos[i].enable();
            } else {
                playerInfos[i].disable();
            }
        }
        const auto& hand = player->hand();
        size_t i;

        // set the first cards to be from the hand, set the rest to null
        for (i = 0; i < hand.size(); i++) {
            cardsInHand[i].image.set(deck.image(hand[i]->suit() * RANK_COUNT + hand[i]->rank()));
        }
        while (i < RANK_COUNT) {
            cardsInHand[i].image.set(deck.null());
            i++;
        }

        // disable all illegal plays
        const auto& legalPlays = gameModel_->legalPlays();
        if (legalPlays.size() == 0) {
            // in case of discard, all plays are legal
            handLabel.set_text("Choose a card to discard");
            size_t i;
            for (i = 0; i < hand.size(); i++) {
                cardsInHand[i].enable();
            }
            while (i < RANK_COUNT) {
                cardsInHand[i].disable();
                i++;
            }
        } else {
            // if there are legal plays, enable only them
            handLabel.set_text("Choose a card to play");
            int k = 0;
            for (int i = 0; i < RANK_COUNT; i++) {
                std::cout << legalPlays[k] << ", " << hand[i] << std::endl;
                if (k != legalPlays.size() && *legalPlays[k] == *hand[i]) {
                    k++;
                    cardsInHand[i].enable();
                } else {
                    cardsInHand[i].disable();
                }
            }
        }
    }
    const auto previous = gameModel_->previousCommand();
    if (previous) {
        const int index = previous->card->suit() * RANK_COUNT + previous->card->rank();
        tableCards[index].set(deck.image(index));
    }
}
