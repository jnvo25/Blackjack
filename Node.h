/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: jonathanvo
 *
 * Created on December 7, 2018, 12:40 PM
 */

#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
    
private:
    double value;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(double);
    Node(const Node&);
    virtual ~Node();
    int getChildren(bool);
    void insert(Node *, bool);
    void print(int);
    void rotate(int);
    void binaryIns(Node*);
    
    // Getters
    Node* getLeft();
    Node* getRight();
    Node* getParent();
    double getValue();
};


#endif /* NODE_H */

