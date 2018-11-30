#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

#include <iostream>
#include <algorithm>

Game::Game()
:
    //create a new game modelling a game that hasn't started yet
    gameOver_(true),
    winnerPlayerId_(-1),
    sevenOfSpades_(Card(SPADE, SEVEN)),
    previousCommand_(nullptr)
{
}

void Game::start(const int seed, const bool* areHuman)
{
    //Create a new game by seeding and shuffling deck.
    //Initializing the 4 players to the proper types based on input bool array
    deck_.reseed(seed);
    gameOver_ = false;
    currentRound_ = 0;
    for (int i = 0; i < PLAYER_COUNT; i++) {
        int id = i + 1;
        delete players_[i];
        if (areHuman[i]) {
            players_[i] = new HumanPlayer(id);
        } else {
            players_[i] = new ComputerPlayer(id);
        }
    }

    newRound();
}

const std::vector<Card*> Game::calculateLegalPlays(const std::vector<Card*>& hand, const Table& table, bool onlyFirstResult) const
{
    std::vector<Card*> allPlays;
    // iterate through cards in hand
    for (auto card : hand) {
        bool found = false;
        for (int i = 0; i < SUIT_COUNT; i++) {
            const auto currentSuit = static_cast<Suit>(i);
            // iterate through cards on the table
            for (int j = 0; j < RANK_COUNT; j++) {
                if (!table.state[i][j]) {
                    continue;
                }

                if (currentSuit == card->suit()) {
                    const int rankDiff = j - card->rank();
                    // the suit matches, rank must be adjacent
                    if (rankDiff == 1 || rankDiff == -1) {
                        allPlays.push_back(card);
                        if (onlyFirstResult) {
                            return allPlays;
                        }
                        found = true;
                        break;
                    }
                } else if (card->rank() == SEVEN) {
                    // otherwise if the card is a SEVEN
                    allPlays.push_back(card);
                    if (onlyFirstResult) {
                        return allPlays;
                    }
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
    }
    return allPlays;
}

void Game::newRound()
{
    currentRound_++;
    table_.reset();
    usedCards_ = 0;
    firstPlay_ = true;
    previousCommand_ = nullptr;
    // shuffle and deal out the deck to the players
    deck_.distribute(players_);

    // Find the player with the seven of spades and set that player as the starting player
    int i;
    for (i = 0; i < PLAYER_COUNT; i++) {
        if (players_[i]->hasCard(sevenOfSpades_)) {
            break;
        }
    }
    currentPlayer_ = i;
    setLegalPlays();
    out_ << "A new round begins. It's player " << currentPlayer_ + 1 << "'s turn to play." << std::endl;

    notify();

    if (players_[currentPlayer_]->isBot()) {
        botTurn();
    }
}

void Game::setLegalPlays()
{
    //calculate and store all legal plays of the current player
    auto player = players_[currentPlayer_];
    legalPlays_ = firstPlay_ ? std::vector<Card*>(1, &sevenOfSpades_) : calculateLegalPlays(player->hand(), table_, player->isBot());
}

void Game::botTurn()
{
    //process a computer turn
    auto player = players_[currentPlayer_];
    processTurn(player->playTurn(legalPlays_));
}

void Game::processTurn(const Command& choice)
{
    auto player = players_[currentPlayer_];
    switch (choice.type) {
    // If the player chooses to play a card, iterate through the legal plays to see that card is legal
    // If the card isn't legal, respond to the action as an illegal move
    // Otherwise, remove that hard from the players hand, add it to the table of played cards
    // Print appropriate message
    case PLAY: {
        const auto& hand = player->hand();
        const auto it = std::find_if(hand.begin(), hand.end(), [&choice](Card* card) {
            return *card == *choice.card;
        });
        table_.state[choice.card->suit()][(*it)->rank()] = true;
        player->playCard(it);
        usedCards_++;
        previousCommand_ = &choice;
        break;
    }

    // If the player discards a card, find that card in the players hand
    // Remove it from the players hand and add it to their discard pile
    case DISCARD: {
        auto& hand = player->hand();
        auto it = std::find_if(hand.begin(), hand.end(), [&choice](Card * card) {
            return card == choice.card;
        });
        player->discard(it);
        usedCards_++;
        previousCommand_ = nullptr;
    }
    default:
        break;
    }
    if (firstPlay_) {
        firstPlay_ = false;
    }
    currentPlayer_ = (currentPlayer_ + 1) % PLAYER_COUNT;
    setLegalPlays();
    notify();
    if (usedCards_ == CARD_COUNT) {
        roundOver();
    } else if (players_[currentPlayer_]->isBot()) {
        botTurn();
    }
}

void Game::rageQuit()
{
    auto& player = players_[currentPlayer_];
    // If the player chooses to rage quit, swap them into a computer player
    out_ << "Player " << player->id() << " ragequits. A computer will now take over." << std::endl;
    ComputerPlayer* replacementPlayer = new ComputerPlayer(std::move(*player));
    delete player;
    player = replacementPlayer;
    botTurn();
}

void Game::roundOver()
{
    printRoundLog();

    // After each round, keep track of the player with the lowest score
    int lowestTotalPoints = players_[0]->totalPoints();
    bool over80 = lowestTotalPoints >= 80;
    // Keep track of the player with the lowest points
    // Keep track if any player has over 80 points
    for (int i = 1; i < PLAYER_COUNT; i++) {
        auto player = players_[i];
        const int points = player->totalPoints();
        if (!over80 && points >= 80) {
            over80 = true;
        }
        if (points < lowestTotalPoints) {
            lowestTotalPoints = points;
        }
    }

    // Declare the winner if any player exeeded 80 points
    // Otherwise reshuffle the deck and begin a new round
    if (over80) {
        for (auto player : players_) {
            if (player->totalPoints() == lowestTotalPoints) {
                winnerPlayerId_ = player->id();
                std::cout << "Player " << winnerPlayerId_ << " wins!" << std::endl;
                notify();
            }
        }
        winnerPlayerId_ = -1;
        gameOver_ = true;
    } else {
        newRound();
    }
}

// Print out the discards and scores of each player
void Game::printRoundLog()
{
    for (auto player : players_) {
        out_ << "Player " << player->id() << "'s discards:" << player->discards() << std::endl;
        out_ << "Player " << player->id() << "'s score: " << player->totalPoints() << " + " << player->currentPoints();
        player->addPoints();
        out_ << " = " << player->totalPoints() << std::endl;
    }
    notify();
}

// Destructor deallocates memory
Game::~Game()
{
    for (int i = 0; i < PLAYER_COUNT; i++) {
        delete players_[i];
    }
}

const int Game::currentPlayer() const
{
    return currentPlayer_;
}

const std::vector<Card *> & Game::legalPlays()
{
    return legalPlays_;
}

const Player* const* Game::players() const
{
    return players_;
}

const int Game::currentRound() const
{
    return currentRound_;
}

const bool Game::gameOver() const
{
    return gameOver_;
}

const int Game::winnerPlayerId() const
{
    return winnerPlayerId_;
}

const Command* Game::previousCommand() const
{
    return previousCommand_;
}

std::stringstream & Game::out()
{
    return out_;
}

const bool Game::newRoundDidStart() const
{
    return firstPlay_;
}
