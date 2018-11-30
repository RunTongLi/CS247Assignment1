#include "Card.h"
#include <string>
#include <cassert>

Card::Card(Suit s, Rank r)
{
    suit_ = s;
    rank_ = r;
}

Suit Card::suit() const
{
    return suit_;
}

Rank Card::rank() const
{
    return rank_;
}

bool operator==(const Card& a, const Card& b)
{
    return a.suit() == b.suit() && a.rank() == b.rank();
}

std::ostream& operator<<(std::ostream& out, const Card& c)
{
    out << ranks[c.rank()] << suits[c.suit()];

    return out;
}

std::istream& operator>>(std::istream& in, Card& c)
{
    std::string suits = "CDHS", ranks = "A234567891JQK";

    std::string str;
    in >> str;
    assert(!in.fail());

    // Read in the rank, make sure it's valid
    c.rank_ = (Rank)ranks.find(str.at(0));
    assert(c.rank_ != std::string::npos);

    // If it's a 10, make sure the 2nd character is a 0
    if (c.rank_ == TEN) {
        assert(str.at(1) == '0');
        str.at(1) = str.at(2);
    }

    // Read in the suit, make sure it's valid
    c.suit_ = (Suit)suits.find(str.at(1));
    assert(c.suit_ != std::string::npos);

    return in;
}

std::ostream& operator<<(std::ostream& out, const std::vector<Card*>& cardList)
{
    // for each card in the card list, output it to ostream out
    for (auto card : cardList) {
        out << " " << *card;
    }
    return out;
}
