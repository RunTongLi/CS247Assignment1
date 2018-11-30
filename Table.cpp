#include "Table.h"

Table::Table()
{
}

void Table::reset()
{
    // set every boolean to false to clear the table
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            state[i][j] = false;
        }
    }
}

std::ostream & operator<<(std::ostream& out, const Table& table)
{
    // for each card on the table, output the suit and rank of the card
    out << "Cards on the table:\n";

    for (int i = 0; i < SUIT_COUNT; i++) {
        out << suitsFull[i] << ":";
        for (int j = 0; j < RANK_COUNT; j++) {
            if (table.state[i][j]) {
                out << " " << ranks[j];
            }
        }
        out << "\n";
    }
    return out;
}
