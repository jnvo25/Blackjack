/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: jonathanvo
 * 
 * Created on October 26, 2018, 8:28 PM
 */

#include <list>
#include <vector> 
#include <fstream>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Node.h"
#include "Game.h"
#include "Player.h"
#include "TreeNode.h"

// Prototype Functions
void mergeSort(double[], int, int);
void connectNodes(TreeNode*, TreeNode*, double);
int minSpanning(TreeNode*);

// Constructor: Start each player off with 2 cards
Game::Game(float amount, std::string pName) {
    
    // Create deck
    Deck deck = Deck();

    // Create players
    player = new Player(amount);
    dealer = new Player();
    players.push_back(player);
    players.push_back(dealer);
    
    // Create Game Variables
    plyrName = pName;
    hPlayed = 0;
    gWon = 0;
    hWinStk = 0;
    cWinStk = 0;
    hiBet = 0;
    hiBank = amount;
    cont = true;

}

// Copy constructor
Game::Game(const Game& orig) {
}

// Destructor deletes pointers to player and dealer
Game::~Game() {
    delete player;
    delete dealer;
}

// Increase game won by 1 and games played and adjust statistics
void Game::win(float amount) {
    gWon++;
    hPlayed++;
    player->deposit(amount);
    if(amount > hiBet)
        hiBet = amount;
    if(player->getFunds() > hiBank) 
        hiBank = player->getFunds();
    cWinStk++;
}

// Increase games played
void Game::loss(float amount) {
    hPlayed++;
    player->withdraw(amount);
}

// Get bet value from user
bool Game::setBet(float min, float amount) {
    if(amount >= min && amount <= player->getFunds()) {
        player->withdraw(amount);
        bet = amount;
        return false;
    } else if(amount == 0) {
        cont = false;
        return false;
    } else return true;
}


// Deal 2 cards for each player
void Game::firstHand() {
    std::list<Player *> :: iterator iter;
    for(iter = players.begin(); iter != players.end(); iter++) {
        (*iter)->addCard(0, deck.dealCard());
        (*iter)->addCard(0, deck.dealCard());
    }
}


// Check whether dealer's first card is ace and offer insurance
bool Game::setInsurance(float amount) {
    if(amount <= bet * 0.5 && amount >= 1) {
        player->withdraw(amount);
        insBet = amount;
        insure = true;
        return false;
    } else return true;
}


// Hit gives one card
void Game::hit(int index) {
    player->addCard(index, deck.dealCard());
}


// Double Down doubles bet and gives one card
void Game::doubleDown(int index) {
    player->withdraw(bet);
    bet*=2;
    player->addCard(index, deck.dealCard());
}


// Split Action makes 2 hands with one of each in original
void Game::splitHand(int index) {
    player->withdraw(bet);
    std::vector<Card> temp = player->getHand(index);
    spltDx.push_back(index);
    player->createHand(temp.at(0));
    player->addCard(index+1, deck.dealCard());    
    player->createHand(temp.at(1));
    player->addCard(index+2, deck.dealCard());
}


// Removes decks that have been split
void Game::clearSplits() {
    for(int i = 0; i < spltDx.size(); i++) {
        player->removeHandAt(spltDx.at(i));
    }
}


// Dealer draw cards until hit above 17
void Game::dealerDraw() {
    while(dealer->getFHandValue() < 17) {
        dealer->addToFirst(deck.dealCard());
    }
}


// Compare hands with dealer
float Game::checkCards(int index) {
    hPlayed++;
    int plyrTot = player->getHandValue(index);
    int dealTot = dealer->getFHandValue();
    
    // If dealer has 21
    float win = bet*1.5;
    float loss = 0-bet;
    float tie = 0;
    if(dealTot == 21) {
        if(plyrTot == 21) { // If player has 21, tie
            player->deposit(bet);
            cWinStk = 0;
            return tie;
        } else if(insure) { // If player is insured, get back money
            player->deposit(insBet*=2);
            return insBet*=2;
        } else {            // If player has worst hand, lose bet
            cWinStk = 0;
            return loss;
        } 
    } else if(plyrTot == 21 || (dealTot > 21 && plyrTot < 21) || (plyrTot > dealTot && plyrTot < 21)) {
        player->deposit(bet*1.5);
        cWinStk++;
        gWon++;
        if(cWinStk > hWinStk)
            hWinStk = cWinStk;
        if(win > hiBet)
            hiBet = bet;
        if(player->getFunds() > hiBank)
            hiBank = player->getFunds();
        return win;
    } else if(plyrTot > 21 || dealTot > plyrTot) {
        player->withdraw(bet*1.5);
        cWinStk = 0;
        return loss;
    } else if(plyrTot == dealTot) {
        cWinStk = 0;
        player->deposit(bet);
        return tie;
    }
    return 0;
}

// Clear player and dealer hands
void Game::clearRound() {
    player->clearHands();
    dealer->clearHands();
    if(hPlayed%3 == 0) {
        deck.resetDeck();
    }
}

// Saves data into file
void Game::writeToFile() {
    std::ofstream out;
    out.open("GameStats.dat");
    out << "STATISTICS OF LAST GAME PLAYED" << "\n";
    out << "Number of hands won: " << gWon << "\n";
    out << "Number of hands played: " << hPlayed << "\n";
    out << "Highest win streak: " << hWinStk << "\n";
    out << "Highest bet won: " << hiBet << "\n";
    out << "Highest bank total achieved: " << hiBank << "\n";
    out.close();
    
    std::ifstream in;
    in.open("Highscores.dat");
    
    if(hiBank != 1000) {
        // Separate player and score and put scores into vector of integer
        std::vector< std::pair<std::string, double> > playerVector;
        std::string line;
        std::pair<std::string, double> temp;
        while(getline(in, line)) {
            if((int)line.at(0) >= 65) {
                temp.first = line;
            } else if((int)line.at(0) >= 48) {
                temp.second = atof(line.c_str());
                playerVector.push_back(temp);
            }
        }
        std::pair<std::string, double> plyrData;
        plyrData.first = plyrName;
        plyrData.second = hiBank;
        playerVector.push_back(plyrData);
        int fileSize = playerVector.size();

        // Transfer to array
        double array[fileSize];
        for(int i=0; i<fileSize; i++) {
            array[i] = playerVector.at(i).second;
        }

        mergeSort(array, 0, fileSize);
        std::vector< std::pair<std::string, double> > sortedVector;
        for(int i=0; i<fileSize; i++) {
            int j=0;
            while(array[i] != playerVector.at(j).second) {
                j++;
            }
            sortedVector.push_back(playerVector.at(j));
        }
        out.open("Highscores.dat");
        for(int i=0; i<fileSize; i++) {
            out << sortedVector.at(i).first << std::endl;
            out << sortedVector.at(i).second << std::endl;
        }
        out.close();
        in.close();

        // Start tree
        Node *start = new Node(array[fileSize/2]);
        // Fill tree
        for(int i=1; i<fileSize; i++) {
            if(i != fileSize/2) {
                Node *temp = new Node(array[i]);
                start->binaryIns(temp);
            }
        }

        while(start->getRight() != NULL) {
            start = start->getRight();
        }
        std::cout << "\nALL-TIME HIGHSCORE: " << start->getValue() << std::endl;
    }
}

// Return highest win streak
int Game::getHiWinStk() {
    return hWinStk;
}

// Return current win streak
int Game::getCuWinStk() {
    return cWinStk;
}

// Return highest bet made and won
int Game::getHiBet() {
    return hiBet;
}

// Return highest bank total
int Game::getHiBank() {
    return hiBank;
}

// Return games played
int Game::getGamesPlayed() {
    return hPlayed;
}

// Return games won
int Game::getGamesWon() {
    return gWon;
}

float Game::getBet() {
    return bet;
}

// Return player
Player* Game::getPlayer() {
    return player;
}

// Return dealer
Player* Game::getDealer() {
    return dealer;
}

// Return deck size
int Game::getDeckSize() {
    return deck.getSizeDeck();
}

// Return continue game?
bool Game::getCont() {
    return cont;
}

void connectNodes(TreeNode* a, TreeNode* b, double difference) {
    a->addNode(b, difference);
    b->addNode(a, difference);
    
}

void mergeSort(double array[], int beg, int end) {
    
    //Make left side size half of array
    //If array is 2 elements make size 1
    int lSize = end/2;
    if(lSize == 0) lSize = 1;
    
    //Make right side size of half array
    //If array is not even, add 1
    int rSize;
    rSize = end/2;
    if(end%2 != 0) rSize++;
    
    //Create array for left and right side
    double l[lSize], r[rSize];
    
    //Copy half arrays into side arrays
    for(int i = 0; i < end; i++) {
        if(i < end/2) l[i] = array[i];
        if(i >= end/2) r[i-end/2] = array[i];
    }
        
    //Check if base case (1 element array)
    if(lSize == 1 && rSize == 1) {
        if(l[0] > r[0]) {
            array[0] = r[0];
            array[1] = l[0];
        }
        //Returns sorted array
    } else {
        //Keep splitting array if > 1 element
        mergeSort(l, 0, lSize);
        mergeSort(r, 0, rSize);
        
        //Merge 2 arrays
        int rI = 0;
        int lI = 0;
        int i = 0;
        //Merge until one side reaches end
        while(rI < rSize && lI < lSize) {
            if(l[lI] < r[rI]) {
                array[i] = l[lI];
                lI++;
            } else {
                array[i] = r[rI];
                rI++;
            }
            i++;
        }
        //Add remainder elements into array
        for(int j = i; j < end; j++) {
            if(rI < rSize) {
                array[j] = r[rI];
                rI++;
            } else {
                array[j] = l[lI];
                lI++;
            }
        }
    }
}

int minSpanning(TreeNode* start) {
    std::vector<TreeNode*> visited;
    TreeNode* current = start;
    int total = 0;
    std::cout << "START -> ";
    while(current->getSize() > 0) {
        std::cout << current->getName() << " -> ";
        current->check(true);
        // Choose smallest 
        int smallest = NULL;
        int index = 0;
        for(int i=0; i<current->getSize(); i++) {
            if((current->getConnection(i).second < smallest || smallest == NULL) 
                    && !current->getConnection(i).first->isChecked()) {
                smallest = current->getConnection(i).second;
                index = i;
            }            
        }
        total += smallest;
        visited.push_back(current->getConnection(index).first);
        current = current->getConnection(index).first;
    }
    std::cout << "END";
    return total;
}
