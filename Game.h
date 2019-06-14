/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: jonathanvo
 *
 * Created on October 26, 2018, 8:28 PM
 */

#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>

#include "Player.h"
#include "Deck.h"

class Game {
public:
    // Constructors
    Game(float, std::string);
    Game(const Game&);
    virtual ~Game();
    void win(float);
    void loss(float);
    
    // Methods
    bool setBet(float, float);
    void firstHand();
    bool setInsurance(float);
    void hit(int);
    void doubleDown(int);
    void splitHand(int);  
    void clearSplits();
    void dealerDraw();
    float checkCards(int);
    void clearRound();
    void writeToFile();
    
    // Getters
    int getHiWinStk();
    int getCuWinStk();
    int getHiBet();
    int getHiBank();
    int getGamesPlayed();
    int getGamesWon();
    float getBet();
    Player* getPlayer();
    Player* getDealer();
    int getDeckSize();
    bool getCont();
    
    
private:
    
    // Game variables
    Deck deck;
    float bet;
    bool insure;
    int insBet;
    bool cont;
    std::vector<int> spltDx;
    
    
   
    // Player statistic variables
    std::string plyrName;
    int gWon;
    int hPlayed;
    int hWinStk;
    int cWinStk;
    float hiBet;
    float hiBank;

    
    // Player variables
    Player *player;
    Player *dealer;
    std::list<Player *> players;

};

#endif /* GAME_H */