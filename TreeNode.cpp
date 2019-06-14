/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "TreeNode.h"

TreeNode::TreeNode(std::string pName) {
    name = pName;
    checked = false;
}

void TreeNode::addNode(TreeNode* pNode, int pInt) {
    std::pair <TreeNode *, int> temp;
    temp.first = pNode;
    temp.second = pInt;
    connections.push_back(temp);
}

void TreeNode::setDifference(int pValue, TreeNode* pOrigin) {
    origin = pOrigin;
    difference = pValue;
}