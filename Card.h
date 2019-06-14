/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Card.h
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
// 2-1- = Pip
// 11   = Jack
// 12   = Queen
// 13   = King

#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    
    // Constructors
    Card(int, int);
    Card(const Card& orig);
    virtual ~Card();
    
    // Getters
    std::string getSuit() const;
    std::string getRank() const;
    int getRankValue();
    bool isAce();
    
private:
    
    // Variables
    int suit;
    int rank;
    bool ace;

};

#endif /* CARD_H */