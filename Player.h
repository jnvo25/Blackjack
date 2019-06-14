/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: jonathanvo
 *
 * Created on October 26, 2018, 9:41 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Card.h"

class Player {
public:
    
    // Constructors
    Player(float);
    Player();
    Player(const Player& orig);
    virtual ~Player();
    
    // Methods
    void createHand();
    void createHand(Card);
    void addCard(int, Card);
    void addToFirst(Card);
    void deposit(float);
    void withdraw(float);
    void removeHandAt(int);
    void clearHands();

    // Getters
    std::vector<Card> getHand(int);
    int getSizeHand(int);
    float getFunds();
    int getHandValue(int);
    int getFHandValue();
    int getNumHands();
    
private:
    
    // Variables
    std::vector<std::vector<Card> > hands;
    int handVal;
    float bank;
    bool dealer;

};

#endif /* PLAYER_H */