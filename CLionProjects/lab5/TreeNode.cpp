#include "TreeNode.h"
#include "DBentry.h"
//
// Created by Kexin Li on 2018-11-18.
//
// A useful constructor
TreeNode::TreeNode(DBentry* _entryPtr) {
    entryPtr = _entryPtr;
}

// the destructor
// Since TreeNode class has three pointer members, so it needs deep destructor
TreeNode::~TreeNode() {
    delete entryPtr;
    left = nullptr;
    right = nullptr;
}

// sets the left child of the TreeNode.
void TreeNode::setLeft(TreeNode* newLeft) {
    left = newLeft;
}

// sets the right child of the TreeNode
void TreeNode::setRight(TreeNode* newRight) {
    right = newRight;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const {
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const {
    return right;
}

// returns a pointer to the DBentry the TreeNode contains.
DBentry* TreeNode::getEntry() const {
    return entryPtr;
}

