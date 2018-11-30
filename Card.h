#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
            EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT
          };
static constexpr int CARD_COUNT = 52;
static const char* suits[] = {"C", "D", "H", "S"};
static const char* suitsFull[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
static const char* ranks[] = {"A", "2", "3", "4", "5", "6",
                              "7", "8", "9", "10", "J", "Q", "K"
                             };
class Card
{
    friend std::istream& operator>>(std::istream&, Card&);

public:
    Card(Suit = CLUB, Rank = THREE);
    Suit suit() const;
    Rank rank() const;

private:
    Suit suit_;
    Rank rank_;
}; // Card

bool operator==(const Card&, const Card&);

// output/input Card in the format <rank><suit>
std::ostream& operator<<(std::ostream&, const Card&);
// perform the above action repeatedly for all elements in the vector
std::ostream& operator<<(std::ostream& out, const std::vector<Card*>& cardList);

#endif // CARD_H
