#include "Player.h"

#include <algorithm>
#include <iostream>

// constructs player with given ID and type
Player::Player(const int id, bool isBot)
    : id_(id),
      isBot_(isBot),
      currentPoints_(0),
      totalPoints_(0)
{
}

// Move constructs player with data from other player
Player::Player(Player&&  other, bool isBot)
    : id_(other.id_),
      isBot_(isBot),
      currentPoints_(0),
      totalPoints_(0),
      hand_(std::move(other.hand_)),
      discards_(std::move(other.discards_))
{
}

// returns id_
const int Player::id() const
{
    return id_;
}

// returns type of player
const bool Player::isBot() const
{
    return isBot_;
}

const std::vector<Card*>& Player::hand() const
{
    return hand_;
}

std::vector<Card*>& Player::hand()
{
    return hand_;
}

// removes a card from the player's hand
void Player::playCard(const std::vector<Card *>::const_iterator& it)
{
    hand_.erase(it);
}

// returns discard pile
const std::vector<Card*>& Player::discards() const
{
    return discards_;
}

void Player::emptyDiscards()
{
    discards_.resize(0);
}

void Player::addPoints()
{
    totalPoints_ += currentPoints_;
    currentPoints_ = 0;
}

const int Player::currentPoints() const
{
    return currentPoints_;
}

const int Player::totalPoints() const
{
    return totalPoints_;
}

void Player::discard(const std::vector<Card *>::const_iterator& it)
{
    // for each card discarded, add it to the discard pile
    // remove from hand
    // total up the points
    Card* card = *it;
    currentPoints_ += card->rank() + 1;
    discards_.push_back(card);
    hand_.erase(it);
}

Player::~Player()
{
}

const Command Player::playTurn(const std::vector<Card*>& legalPlays) const
{
    return turn(legalPlays);
}

// iterate through hand_ and return whether the player has the given card in their hand_
const bool Player::hasCard(Card& givenCard) const
{
    return std::find_if(hand_.begin(), hand_.end(), [&givenCard](Card * card) {
        return *card == givenCard;
    }) != hand_.end();
}
