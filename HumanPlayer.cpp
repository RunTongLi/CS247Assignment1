#include "HumanPlayer.h"
#include "iostream"

// Constructor for the human player
// sets id to a given ID using the base class constructor
HumanPlayer::HumanPlayer(const int id)
    : Player(id, false)
{
}

// Dummy turn function
const Command HumanPlayer::turn(const std::vector<Card*>&) const
{
    Command command;
    return command;
}
