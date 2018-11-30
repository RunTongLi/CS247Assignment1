#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "Player.h"

static constexpr int PLAYER_COUNT = 4;
// Deck struct keeping track of all 52 Card objects of the deck
struct Deck {
    Card cards_[CARD_COUNT]; // Array of Cards of the deck
    int seed_;

    // Shuffles the deck
    // requires: deck should consist of 52 cards (regular poker cards without joker)
    // modifies: cards_
    // ensures: card[i]=card[i]@pre, given a random i, 0<=i<52
    void shuffle();

    // Creates a standard 52 card deck
    // modifies: cards_
    // ensures: a regular deck of 52 cards is created, in the given order specified in the assignment
    Deck();

    void reseed(const int seed);

    // returns: cards_
    const Card* cards();

    // Given 4 players, deals the cards of this deck to the players
    // modifies: players[i], 0<=i<4
    // ensures: player i is dealth with the ith set of 13 cards
    const void distribute(Player* players[PLAYER_COUNT]);
};

// output/input Card in the format <rank><suit>
std::ostream& operator<<(std::ostream& out, const Deck& deck);
#endif // DECK_H
