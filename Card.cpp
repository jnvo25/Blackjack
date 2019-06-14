/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Card.cpp
 * Author: jonathanvo
 * 
 * Created on October 26, 2018, 8:28 PM
 */

// Variable Legend
// SUIT:
// 1 = Clubs
// 2 = Diamonds
// 3 = Hearts
// 4 = Spades

// RANK:
// 1    = Ace
// 2-10 = Pip
// 11   = Jack
// 12   = Queen
// 13   = King

#include <string>

#include "Card.h"

// Constructor: Create card with passed suit and rank
Card::Card(int pSuit, int pRank) {
    suit = pSuit;
    rank = pRank;
    if(rank == 1)
        ace = true;
    else
        ace = false;
}

// Copy Constructor
Card::Card(const Card& orig) {
    suit = orig.suit;
    rank = orig.rank;
    ace = orig.ace;
}

Card::~Card() {
}

// Return the suit name of the card
std::string Card::getSuit() const {
    if(suit == 1)
        return "clubs";
    else if(suit == 2)
        return "diamonds";
    else if(suit == 3)
        return "hearts";
    else if(suit == 4)
        return "spades";
    else
        return "ERROR";
}

// Return the rank name of the card
std::string Card::getRank() const {
    if(rank == 1)
        return "Ace";
    else if(rank >= 2 && rank <= 10)
        return std::to_string(rank);
    else if(rank == 11)
        return "Jack";
    else if(rank == 12)
        return "Queen";
    else if(rank == 13)
        return "King";
    else
        return "ERROR";
}

// Read rank and output value of card in terms of blackjack
int Card::getRankValue() {
    if(rank == 1) 
        return 0;
    else if(rank >= 11 && rank <= 13)
        return 10;
    else 
        return rank;
}

// Return whether card is an ace
bool Card::isAce() {
    return ace;
}
