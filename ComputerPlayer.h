#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"

class ComputerPlayer : public Player
{
    // Override play method from base Player class
    // requires: a table showing the all the cards that have been played
    // modifies: hand_, discards_
    // ensures: one card is removed from hand_ and placed on the table or discarded
    // returns: PLAY command if player has a legal play, DISCARD command otherwise
    const Command turn(const std::vector<Card*>& cardList) const override;
public:
    ComputerPlayer(const int id);
    // Contructor for ComputerPlayer given an ID
    // requires: 1<=id<=4
    // ensures: a computer player with ID=id and 0 total points to be created


    ComputerPlayer(Player&& other);
    // Move Constructor for ComputerPlayer given another player
    // ensures: a computer player is created with matching data of the given player
};

#endif // COMPUTERPLAYER_H
