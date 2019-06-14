/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.h
 * Author: jonathanvo
 *
 * Created on October 26, 2018, 8:28 PM
 */

#ifndef DECK_H
#define DECK_H

#include <deque>

#include "Card.h"

class Deck {
public:
    
    // Constructors
    Deck();
    Deck(const Deck& orig);
    virtual ~Deck();
    
    // Methods
    void shuffleDeck();
    void resetDeck();
    Card dealCard();
    
    // Getters
    Card getCard(int);
    int getSizeDeck();
private:
    
    // Variables
    std::deque<Card> deck;

};

#endif /* DECK_H */