#ifndef COMMAND_H
#define COMMAND_H

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD };

struct Command {
    Type type;
    Card* card;
};

#endif
