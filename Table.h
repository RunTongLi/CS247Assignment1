#ifndef TABLE_H
#define TABLE_H

#include "Card.h"
#include <vector>

// Keeps track of the cards played on the table
struct Table
{
    // a 2D array of whether a card has already been played
    bool state[SUIT_COUNT][RANK_COUNT];

    // constructor that sets up a clear table
    Table();

    // helper function to clean up the table
    void reset();
};

// overload output operator
// returns ostream object containing the cards to be printed
std::ostream& operator<<(std::ostream& out, const Table& table);
#endif // TABLE_H
