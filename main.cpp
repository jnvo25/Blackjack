/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jonathanvo
 *
 * Created on October 26, 2018, 8:25 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Game.h"
#include "GeneralHashFunctions.h"

using namespace std;

/*
 * 
 */

// Prototype Functions
void printPlayerHand(Game &, int);
void printDealerHand(Game &, bool);
void readStats();
void playGame(float, string);
void readScores();

int main(int argc, char** argv) {

    // Set random seed
    srand(static_cast<unsigned int> (time(0)));
    
    // Create flag to exit menu
    bool cont = true;
    
    string pName;
    
    // Create account
    string input;
    cout << "Enter your name for highscore records: ";
    cin >> pName;
    
    // Display menu
    while(cont) {
        cout << endl;
        cout << "Welcome to Blackjack, " << pName << endl;
        cout << "[1] Play Game" << endl;
        cout << "[2] Get Player Statistics" << endl;
        cout << "[3] Get Worst Profit Makers" << endl;
        cout << "[4] Exit" << endl;
        cout << "[5] Custom Game" << endl;
        cout << endl;
        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Variables for switch statement
        string input;
        double hash;
        ifstream in;
        string line;
        
        switch(choice) {
            // If 1 then play game
            case 1: playGame(1000, pName);
                break;
            // If 2 then open statistics from last game
            case 2: readStats();
                break;
            case 3: readScores();
                break;
            // If 4 then exit menu
            case 4: cont = false;
                break;
            case 5: cout << "ENTER PASSWORD: "; //holymackeral
                cin >> input;
                hash = RSHash(input);
                in.open("password.dat");                
                getline(in,line);
                if(atof(line.c_str()) == hash) {
                    cout << "Enter amount to start in game: ";
                    int amount;
                    cin >> amount;
                    playGame(amount, pName);
                } else {
                    cout << "WRONG PASSWORD" << endl;
                }
                in.close();
            default: break;
        }
    }
    return 0;
}

// Prints every card in player's hand
void printPlayerHand(Game &game, int index) {
    
    cout << "\nYour cards: " << endl;
    
    // Cycle through all the cards in hand and print
    for (int i = 0; i < game.getPlayer()->getSizeHand(index); i++) {
        cout << game.getPlayer()->getHand(index).at(i).getRank();
        cout << " of ";
        cout << game.getPlayer()->getHand(index).at(i).getSuit();
        cout << endl;
    }
    
    // Print value of hand
    cout << "Hand Value: " << game.getPlayer()->getHandValue(index) << endl;
}

// Prints either 1 card of dealer or all cards
void printDealerHand(Game &game, bool first) {
    
    int cycles;
    
    // Allow only one card to be shown if desired
    if (first) {
        cout << "\nDealer's first card: " << endl;
        cycles = 1;
    } else {
        cout << "Dealer cards: " << endl;
        cycles = game.getDealer()->getSizeHand(0);
    }
   
    // Cycle through hand until number of cycles reached
    for (int i = 0; i < cycles; i++) {
        cout << game.getDealer()->getHand(0).at(i).getRank();
        cout << " of ";
        cout << game.getDealer()->getHand(0).at(i).getSuit();
        cout << endl;
    }
    
    // Print hand value
    if(!first) cout << "Hand Value: " << game.getDealer()->getHandValue(0) << endl;
}

void playGame(float initVl, string pName) {
    float initFu = initVl;
    bool plyrMov = true;    // Used to skip player moves

    Game game = Game(initFu, pName);
    // Run game until player runs out of money or want out
    bool end = false;
    while(game.getPlayer()->getFunds() > 0 && !end && game.getCont()) {
        // Display statistics
        cout << endl;
        bool first = (game.getGamesPlayed() > 1) ? true : false;
        if (first == true) {
            if (game.getCuWinStk() > 1) 
                cout << "Your are on a " << game.getCuWinStk() 
                        << " game win streak!" << endl;
            cout << "You won " << game.getGamesWon() << " out of "
                    << game.getGamesPlayed() << " games!" << endl;
            if (game.getHiBet() > 0)
                cout << "Your highest bet win is $" << game.getHiBet() << endl;
            if (game.getHiBank() > initFu)
                cout << "Your highest fund value is $" << game.getHiBank() << endl;
        }
        cout << "Your current funds: $" << game.getPlayer()->getFunds() << endl;
        

        // Get bet value from user and validate
        float minBet = 15;
        cout << "Press [0] to exit to menu" << endl;
        float bet;
        do {
            cout << "Enter your bet ($" << minBet << "-$" 
                << game.getPlayer()->getFunds() <<  "): $";
            cin >> bet;
        } while(game.setBet(minBet, bet));
        if(game.getCont()) {
            cout << "You bet: $" << game.getBet() << endl;
            cout << "Your remaining funds: $" << game.getPlayer()->getFunds() 
                    << endl;
        
            
            // Create hands
            game.getPlayer()->createHand();
            game.getDealer()->createHand();

            // Deal Cards
            game.firstHand();

            // Show cards
            printDealerHand(game, true);

            
            // Check insurance
            if (game.getDealer()->getHand(0).at(0).isAce() && game.getPlayer()->getFunds() > game.getBet()/2) {
                printPlayerHand(game, 0);
                cout << "\nDealer has an ace." << endl;
                cout << "Your funds: $" << game.getPlayer()->getFunds() << endl;
                cout << "Do you want to bet insurance? [Y]Yes  [Any Key]No : $";
                char input;
                cin >> input;
                if (toupper(input) == 'Y') {
                    float bet;
                    cout << "Enter your bet ($1-$"
                            << game.getBet() / 2 << "): $";
                    cin >> bet;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while (game.setInsurance(bet)) {
                        cout << "Enter your bet ($1-$"
                                << game.getBet() / 2 << "): $";
                        cin >> bet;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                // Check if dealer has blackjack and skip player moves if so
                if(game.getDealer()->getFHandValue() == 21)
                    plyrMov = false;
            }

            
            // Check if player's hand can split
            bool spltbl = false;
            if(game.getPlayer()->getHand(0).at(0).getRank() == 
                    game.getPlayer()->getHand(0).at(1).getRank())
                spltbl = true;

            
            // Check if player's hand can double bet and can afford
            bool dubDown = false;
            if(game.getPlayer()->getFHandValue() >= 9 && 
                    game.getPlayer()->getFHandValue() <= 11 &&
                    game.getPlayer()->getFunds() >= game.getBet())
                dubDown = true;

            
            // Player moves for each hand
            if(plyrMov) {
                for(int hand = 0; hand < game.getPlayer()->getNumHands(); hand++) {
                    cout << endl;
                    if(hand == 0) cout << "Playing first hand..." << endl;
                    else if(hand%2 == 0) cout << "Playing second of split deck..." << endl;
                    else cout << "Playing first of split deck..." << endl;

                    // Play hand until bust or player chooses ending action
                    bool cont = true;
                    while(game.getPlayer()->getHandValue(hand) < 21 && cont) {
                        // Print hand currently playing
                        printPlayerHand(game, hand);

                        // Check available moves and receive input
                        cout << "Options -> [1] HIT  [2] STAND";
                        if(dubDown == true)
                            cout << "  [3] DOUBLE DOWN";
                        if(spltbl == true && dubDown == true)
                            cout << "  [4] SPLIT";
                        else if(spltbl == true)
                            cout << "  [3] SPLIT";
                        cout << ": ";
                        int choice;
                        cin >> choice;

                        if(choice == 1) {
                            cout << "You choose to hit" << endl;
                            game.hit(hand);
                        } else if(choice == 2) {
                            cout << "You choose to stand" << endl;
                            cont = false;
                        } else if(choice == 3 && dubDown == true) {
                            cout << "You choose to double your bet" << endl;
                            game.doubleDown(hand);
                            cont = false;
                        } else if(((choice == 3 && spltbl) || (choice == 4 && spltbl)) && 
                                game.getPlayer()->getSizeHand(hand) == 2) {
                            cout << "You choose to split your hand" << endl;
                            game.splitHand(hand);
                            cont = false;
                        } else {
                            cout << "INVALID CHOICE" << endl;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        spltbl = false;
                        dubDown = false;
                    }
                }
                // Remove original split hand if exists
                game.clearSplits();;
            }       

            // Deal cards to dealer
            if(game.getPlayer()->getFHandValue() <= 21) {
                game.dealerDraw();
            }

            // Check cards
            cout << endl << "CHECKING CARDS..." << endl;
            printDealerHand(game, false);
            for(int hand = 0; hand < game.getPlayer()->getNumHands(); hand++) {
                printPlayerHand(game, hand); 
                cout << endl;
                float amount = game.checkCards(hand);
                if(amount > 0)
                    cout << "You won $" << abs(amount) << "!" << endl;
                else if(amount == 0)
                    cout << "TIE! You get back your bet." << endl;
                else cout << "You lost $" << abs(amount) << "!" << endl;
            }
            game.clearRound();
        }
    }
    game.writeToFile();
}

// Open file and output data
void readStats() {
    string fileName = "GameStats.dat";
    ifstream in;
    in.open(fileName.c_str());
    string line;
    while(getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

// Open file and output highscores
void readScores() {
    string fileName = "Highscores.dat";
    ifstream in;
    in.open(fileName.c_str());
    string line;
    int counter = 1;
    while(getline(in, line)) {
        if((int)line.at(0) >= 65) {
            cout << counter++ << ". ";
            cout << line << " got ";
        } else if((int)line.at(0) >= 48) {
            cout << line << endl;
        }
        
    }
    in.close();
}