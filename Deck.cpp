#include "Deck.h"
#include <random>

Deck::Deck()
{
    // Create the standard 52 card deck, in the order of clubs, diamonds, hearts and spades (A to King)
    for (int i = 0; i < CARD_COUNT; i++) {
        cards_[i] = Card(static_cast<Suit>(i / RANK_COUNT), static_cast<Rank>(i % RANK_COUNT));
    }
}

void::Deck::reseed(const int seed)
{
    seed_ = seed;
}

void Deck::shuffle()
{
    static std::mt19937 rng(seed_);

    int n = CARD_COUNT;

    // for all 52 cards, swap the ith card with the jth card, where j is random integer, 0<=j<52
    while (n > 1) {
        int k = static_cast<int>(rng() % n);
        --n;
        std::swap(cards_[n], cards_[k]);
    }
}

const Card* Deck::cards()
{
    // returns the deck
    return cards_;
}

const void Deck::distribute(Player* players[PLAYER_COUNT])
{

    shuffle();

    // for all  players, shallow copy the players hands
    // set the player's discard pile to empty
    // fill the ith players' hands with the ith set of 13 cards
    for (int i = 0; i < PLAYER_COUNT; i++) {
        auto& hand = players[i]->hand();
        players[i]->emptyDiscards();
        hand.resize(RANK_COUNT);
        for (int j = 0; j < RANK_COUNT; j++) {
            hand[j] = &cards_[j + i * RANK_COUNT];
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Deck& deck)
{
    int i = 0;
    for (auto& card : deck.cards_) {
        if (i == RANK_COUNT) {
            i = 0;
            out << "\n";
        }
        if (i != 0) {
            out << " ";
        }
        std::cout << card;
        i++;
    }

    return out;
}
