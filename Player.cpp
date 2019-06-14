/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: jonathanvo
 * 
 * Created on October 26, 2018, 9:41 PM
 */

#include <vector>

#include "Player.h"

// Constructor: Start player with amount passed
Player::Player(float amount) {
    bank = amount;
    dealer = false;
}

// Empty constructor for dealer
Player::Player() {
    dealer = true;
}

// Copy constructor
Player::Player(const Player& orig) {
    bank = orig.bank;
}

Player::~Player() {
}

// Create new empty hand
void Player::createHand() {
    std::vector<Card> hand;
    hands.push_back(hand);
}

// Create hand from card
void Player::createHand(Card card) {
    std::vector<Card> hand;
    hand.push_back(card);
    hands.push_back(hand);
}

// Return player's hand
std::vector<Card> Player::getHand(int index) {
    return hands[index];
}

// Add card to player's hand
void Player::addCard(int index, Card pCard) {
    hands[index].push_back(pCard);
}

// Overload of add card to player's hand for dealer
void Player::addToFirst(Card pCard) {
    hands[0].push_back(pCard);
}


// Return size of hand
int Player::getSizeHand(int index) {
    return (int)hands[index].size();
}

// Put money into player's bank
void Player::deposit(float amount) {
    bank += amount;
}

// Take money from player's bank
void Player::withdraw(float amount) {
    bank -= amount;
}

// Return amount in player's bank
float Player::getFunds() {
    return bank;
}

// Return hand value
int Player::getHandValue(int index) {
    int total = 0;
    int aces = 0;
    for(int i = 0; i < hands[index].size(); i++) {
        if(hands[index].at(i).isAce())
            aces++;
        else
            total += hands[index].at(i).getRankValue();
    }
    for(int ace = 0; ace < aces; ace++) {
        if(total + 11 < 21)
            total += 11;
        else
            total += 1;
    }
    return total;
}

// Overload of return hand value for dealer
int Player::getFHandValue() {
    int total = 0;
    int aces = 0;
    for(int i = 0; i < hands[0].size(); i++) {
        if(hands[0].at(i).isAce())
            aces++;
        else
            total += hands[0].at(i).getRankValue();
    }
    for(int ace = 0; ace < aces; ace++) {
        if(total + 11 < 21)
            total += 11;
        else
            total += 1;
    }
    return total;
}

// Return number of hands player has
int Player::getNumHands() {
    return (int)hands.size();
}

// Remove hand
void Player::removeHandAt(int index) {
    hands.erase(hands.begin() + index);
}

// Remove all hands
void Player::clearHands() {
    for(int i = 0; i < hands.size(); i++)
        hands.pop_back();
    
}
