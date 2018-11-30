#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

// The human player class extends the base player class
class HumanPlayer : public Player
{
    // Dummy turn function overriden to make this a concrete class, unused
    const Command turn(const std::vector<Card*>& legalPlays) const override;

public:
    // ensures: a new human player is created using the given ID, isBot_ is set to false, points_=0 and hands_/discard_ intitally set to be empty
    HumanPlayer(const int id);
};

#endif // HUMANPLAYER_H
