#include "ComputerPlayer.h"
#include <cmath>

// constructs computer player with given ID
ComputerPlayer::ComputerPlayer(const int id)
    : Player(id, true)
{
}

// Move constructs computer player using data from given player
ComputerPlayer::ComputerPlayer(Player&&  other)
    : Player(std::move(other), true)
{
}

// overrides play method from Player class
const Command ComputerPlayer::turn(const std::vector<Card*>& legalPlays) const
{
    int best = 0;
    if (legalPlays.size() == 0) {
        // if no legal plays (discard)
        for (size_t i = 1; i < hand_.size(); ++i) {
            if (hand_[i]->rank() < hand_[best]->rank()) {
                best = i;
            }
        }
        // find the smallest card and discard that
        return Command { DISCARD, hand_[best] };
    } else {
        for (size_t i = 1; i < legalPlays.size(); ++i) {
            if (hand_[i]->rank() > hand_[best]->rank()) {
                best = i;
            }
        }
        // play high cards, saving lower cards for discards
        return Command { PLAY, legalPlays[best] };
    }
}
