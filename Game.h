#ifndef GAME_H
#define GAME_H

#include <sstream>

#include "Table.h"
#include "Deck.h"
#include "Subject.h"
#include "Observer.h"

// The game class acts as a Facade to all the inner composed classes, and acts as a Model in the MVC pattern
// by keeping track and processsing the game state. Contains the table of cards already played, the 4 players, and the deck
// The Game starts upon creation of an instance, and a particular game repeatedly plays out rounds until a player exeeds 80 points
class Game : public Subject
{
    // The table of played cards
    Table table_;

    // Whether it is the first play in the current round
    bool firstPlay_;

    // If the game is in an ended state
    bool gameOver_;

    // Total number of cards on the played / discarded this turn
    int usedCards_;

    // The current round number
    int currentRound_;

    // The Id of the player who currently won, takes multiple values one-by-one in case of a tie
    int winnerPlayerId_;

    // The card we start off with, used to pass around as a pointer in other functions
    Card sevenOfSpades_;

    // The last command executed, useful for performing appropriate updates in the View
    const Command* previousCommand_;

    // Buffer used to store messages to be displayed in a gtk MessageDialog box
    std::stringstream out_;

    // The players of the game
    Player* players_[PLAYER_COUNT];

    // The index of the current player in players_
    int currentPlayer_;

    // A vector of all legal plays
    std::vector<Card*> legalPlays_;

    // Deck containing shuffled cards for the current round
    Deck deck_;

    // Given a table of cards already been played, determine all the legal plays of the current hand
    // returns: a list of cards consisting of the legal plays out of the cards in hand_
    const std::vector<Card*> calculateLegalPlays(const std::vector<Card*>& hand, const Table& table, bool onlyFirstResult = false) const;

    // Print out the discards and scores of each player
    void printRoundLog();

    // Starts a new round in the game
    // Requires: a game to have started
    // Modifies: firstPlay_, currentRound_, usedCards_, previousCommand_, table_, deck_, currentPlayer_, out_
    // Ensures: a new round is started in the game
    void newRound();

    // Sets legalPlays_ to the list of legal plays according to the current table_ state
    // Modifies: legalPlays_
    // Ensures: legalPlays_ is set to the correct value
    void setLegalPlays();

    // Plays the currentPlayer_ assuming it is a ComputerPlayer
    // Requires: players_[currentPlayer_] is of underlying type ComputerPlayer
    // Ensures: a bot player has finished playing their turn
    void botTurn();

    // Cleans up after the end of a round a tallies the scores, and triggers either a new round or Game Over
    void roundOver();
public:

    // processes a Command or either PLAY or DISCARD, and performs appropriate changes
    // Modifies: table_, players_, usedCards_, previousCommand_
    void processTurn(const Command& choice);

    // Replaces current (Human) Player with a Computer Player identical in state, and triggers the ComputerPlayer to take over the turn
    void rageQuit();

    // Main game function, creates an instance of the whole game
    // modifies: players_, deck_
    // Ensures:4 human/computer players are created, deck of 52 cards is created, game is played out and if a player reaches 80 points, a winner is declared
    Game();

    // Starts the game
    void start(const int seed, const bool* areHuman);

    // a bunch of getters used by View to update itself
    const Player* const* players() const;
    const int currentRound() const;
    const int winnerPlayerId() const;
    const Command* previousCommand() const;
    std::stringstream& out();
    const int currentPlayer() const;
    const std::vector<Card*>& legalPlays();
    const bool gameOver() const;
    const bool newRoundDidStart() const;

    // Destructor
    // modifies players_
    // Ensures: memory used to store the 4 players gets deallocated
    ~Game();
};

#endif // GAME_H
