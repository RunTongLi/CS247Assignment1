#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Table.h"
#include "Card.h"
#include "Command.h"

// Abstract base player class
// encapsulates a player's hand and discard pile
// contains logic for determining legal plays
class Player
{
    // Data members to store player ID, points, hand and discard piles
    int id_;
    bool isBot_; // keeps track if player is a bot

    // Determines the next move of the player given an input
    // returns: a command given by the user
    virtual const Command turn(const std::vector<Card*>& legalPlays) const = 0;
protected:
    int currentPoints_;
    int totalPoints_;
    std::vector<Card*> hand_;
    std::vector<Card*> discards_;
public:
    // Constructs a player using given ID and type
    // modifies: id_, isBot_, points_
    // ensures a player with the given type and ID and total points of 0 is created
    Player(const int id, bool isBot);

    // Move Constructs a player using given player
    // modifies: id_, isBot_, points_, hand_, discards_
    // ensures: a player is created with the same data as the other player
    Player(Player && other, bool isBot);

    // virtual destructor to be extended
    virtual ~Player();

    // Determines the next move of the player by calling private play function
    // returns: a command given by the user
    const Command playTurn(const std::vector<Card*>& legalPlays) const;

    // returns: id_
    const int id() const;

    // returns: isBot_
    const bool isBot() const;

    // returns: hand_ (const variant)
    const std::vector<Card*>& hand() const;

    // returns: hand_
    std::vector<Card*>& hand();

    // removes a card from the player's hand using the given iterator
    // modifies hand_
    // ensures card at given position is removed
    void playCard(const std::vector<Card *>::const_iterator& it);

    // returns discards_
    const std::vector<Card*>& discards() const;

    // returns_ points_

    // empties the discard pile
    // modifies: discards_
    // ensures: discards_ is empty
    void emptyDiscards();

    // adds points from current round into the total score
    // modifies: currentPoints_, totalPoints_
    void addPoints();

    // returns currrentPoints_
    const int currentPoints() const;

    // returns totalPoints_
    const int totalPoints() const;

    // discards a given set of cards from hand
    // requires: set of given cards to be in hand
    // modifies: discards_, hand_, points_
    // ensures:given cards are removed from hand and placed in discard pile, update points of player
    void discard(const std::vector<Card *>::const_iterator& it);

    // Finds if given card is in hand
    // returns : if the card given is present in hand_
    const bool hasCard(Card& givenCard) const;
};

#endif // PLAYER_H
