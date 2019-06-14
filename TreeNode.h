/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: jonathanvo
 *
 * Created on December 13, 2018, 6:15 PM
 */

#ifndef TREENODE_H
#define TREENODE_H


#include <string>
#include <vector>
#include <utility>
#include <limits>

class TreeNode {

private:
    std::string name;
    bool checked;
    int difference = std::numeric_limits<int>::max();
    TreeNode* origin;
    std::vector< std::pair<TreeNode*, int> > connections;

public:
    // Constructor
    TreeNode(std::string);

    // Add node to connections
    void addNode(TreeNode*, int);

    // Set checked
    void check(bool pBool) {checked = pBool;}

    // Get checked
    bool isChecked() {return checked;}

    // Get # of connections
    int getSize() {return (int)(connections.size());}

    // Get connection pair at index
    std::pair<TreeNode*, int> getConnection(int index) {return connections.at(index);}

    // Get name
    std::string getName() {return name;}

    // Get distance
    int getDifference() {return difference;}

    // Set distance
    void setDifference(int, TreeNode*);

    TreeNode* getOrigin() {return origin;}
};

#endif /* NODE_H */

