/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>

#include "Node.h"

// Constructor
Node::Node(double pValue) {
    value = pValue;
    left = NULL;
    right = NULL;
    parent = NULL;
}

// Copy Constructor
Node::Node(const Node& orig) {
    value = orig.value;
    left = orig.left;
    right = orig.right;
}

// Destructor
Node::~Node() {
    delete left;
    delete right;
}

// Returns the number of children on specified side of node
int Node::getChildren(bool isLeft) {
    
    // variables to hold number of children in right branch vs left branch
    int lChildren = 0, rChildren = 0;
    
    if(isLeft) {    // if user wants to look at left side of node
        
        // BASE CASE
        // if left node does not exist, return 0
        if(left == NULL) return 0;
        // if left node's left and right node does not exist, return 1
        if(left->left == NULL && left->right == NULL) return 1;
        
        // IF THERE ARE MORE LAYERS
        
        // - if left or right node exist, there is at least one child under current
        // node
        // - get number of children on both sides of current node and return
        // the biggest child side
        lChildren = 1 + left->getChildren(true);
        rChildren = 1 + left->getChildren(false);
        return (lChildren > rChildren) ? lChildren : rChildren;
        
    } else {
        // if right node does not exist, return 0
        if(right == NULL) return 0;
        
        // if right node's left and right node does not exist, return 1
        if(right->left == NULL && right->right == NULL) return 1;
        
        // if left or right exist, there is at least one child
        // get children of that one existing
        lChildren = 1 + right->getChildren(true);
        rChildren = 1 + right->getChildren(false);
        return (lChildren > rChildren) ? lChildren : rChildren;
    }
    
    return -999999; // UNEXPECTED CASE
    
    
}

void Node::insert(Node *pNode, bool isLeft) {
    if(isLeft) left = pNode;
    else right = pNode;
    pNode->parent = this;
}

void Node::rotate(int isLeft) {
    if(isLeft) {
        Node* temp = right;
        right = right->left;
        temp->left = this;
        if(parent != NULL) parent->left = temp;
        delete temp;
    } else {
        Node* temp = left;
        left = left->right;
        temp->right = this;
        if(parent != NULL) parent->right = temp;
        delete temp;
    }
    
}

void Node::binaryIns(Node* pNode) {
    for(int i=0; i<3; i++) {
        if(value > pNode->value) {
            if(left == NULL) {
                left = pNode;
                break;
            } else {
                left->binaryIns(pNode);
                break;
            }
        } else if(value < pNode->value) {
            if(right == NULL) {
                right = pNode;
                break;
            } else {
                right->binaryIns(pNode);
                break;
            }
        }
    }
}

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}

Node* Node::getParent() {
    return parent;
}

double Node::getValue() {
    return value;
}
