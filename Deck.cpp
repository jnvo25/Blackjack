/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.cpp
 * Author: jonathanvo
 * 
 * Created on October 26, 2018, 8:28 PM
 */

#include <deque>

#include "Deck.h"

// Constructor: Create deck of cards
Deck::Deck() {
    for(int suit = 1; suit < 5; suit++) {
        for(int rank = 1; rank < 14; rank++) {
            Card card(suit, rank);
            deck.push_back(card);
        }
    }
    this->shuffleDeck();
}

// Copy Constructor
Deck::Deck(const Deck& orig) {
    Deck temp = orig;
    for(int i = 0; i < temp.deck.size(); i++) {
        deck.push_back(temp.deck.front());
        temp.deck.pop_back();
    }
}

Deck::~Deck() {
}

// Shuffles deck random number of times
void Deck::shuffleDeck() {
    for(int i = 1; i < rand()%2500; i++) {
        random_shuffle(deck.begin(), deck.end());
    }
}

// Get a card and remove from deck
Card Deck::dealCard() {
    Card card = deck.front();
    deck.pop_front();
    return card;
}

// Return card at index
Card Deck::getCard(int index) {
    return deck.at(index);
}

// Create new shuffle deck
void Deck::resetDeck() {
    deck.clear();
    for(int suit = 1; suit < 5; suit++) {
        for(int rank = 1; rank < 14; rank++) {
            Card card(suit, rank);
            deck.push_back(card);
        }
    }
    this->shuffleDeck();
}

// Return size of deck
int Deck::getSizeDeck() {
    return deck.size();
}
