#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"
#include <iostream>

//
// Created by Kexin Li on 2018-11-18.
//


// the default constructor, creates an empty database.
TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB() {
    clear();
}

// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry) {
    if(root == nullptr) {
        root = new TreeNode(newEntry);
        root->setLeft(nullptr);
        root->setRight(nullptr);
        return true;
    }

    if(newEntry->getName() == root->getEntry()->getName()) {
        delete newEntry;
        return false;
    }

    TreeNode* ptr = root;
    TreeNode* pptr = nullptr;
    while(ptr != nullptr) {
        if (ptr->getEntry()->getName() == newEntry->getName()) {
            delete newEntry;
            return false;
        } else if (newEntry->getName() > ptr->getEntry()->getName()) {
            pptr = ptr;
            ptr = ptr->getRight();
        } else {
            pptr = ptr;
            ptr = ptr->getLeft();
        }
    }

    if(newEntry->getName() > pptr->getEntry()->getName()) {
        pptr->setRight(new TreeNode(newEntry));
        pptr->getRight()->setLeft(nullptr);
        pptr->getRight()->setRight(nullptr);
    } else {
        pptr->setLeft(new TreeNode(newEntry));
        pptr->getLeft()->setLeft(nullptr);
        pptr->getLeft()->setRight(nullptr);
    }
    return true;

}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name) {
    TreeNode* ptr = root;
    int count = 1;
    while (ptr != nullptr) {
        if(ptr->getEntry()->getName() == name) {
            probesCount =  count;
            return ptr->getEntry();
        } else if (name > ptr->getEntry()->getName()) {
            ptr = ptr->getRight();
        } else if (name < ptr->getEntry()->getName()) {
            ptr = ptr->getLeft();
        }
        count ++;
    }
    return nullptr;
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name) {
    bool result = false;
    if (root == nullptr) {
        return false;
    }

    if (name == root->getEntry()->getName() && root->getRight() == nullptr  &&  root->getLeft() == nullptr) {
        delete root;
        root = nullptr;
        return true;
    }

    root = removOne(root, name, result);
    return result;

}

// deletes all the entries in the database.
void TreeDB::clear() {
    TreeNode* ptr = root;
    if(ptr == nullptr) return;
    delete_tree(ptr);
    root = nullptr;
}

// prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const {
    int activeEntry = 0;
    int& active = activeEntry;
    TreeNode* ptr = root;
    printActive(ptr, active);
    cout << activeEntry << endl;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs) {
    rhs.inorder(out, rhs.root);
    return out;
}

// counts the status recursively
void TreeDB::printActive(TreeNode* ptr, int& activeEntry) const {
    if(ptr != nullptr) {
        if(ptr->getEntry()->getActive() == true) {
            activeEntry += 1;
        }
        printActive(ptr->getLeft(), activeEntry);
        printActive(ptr->getRight(), activeEntry);
    }
}

// prints out the tree in order
void TreeDB::inorder(ostream& out, TreeNode* ptr) const {
    if (ptr != nullptr) {
        inorder(out, ptr->getLeft());
        string whetherActive = ptr->getEntry()->getActive() ? "active" : "inactive";
        out << ptr->getEntry()->getName() << " : " << ptr->getEntry()->getIPaddress() << " : " << whetherActive << endl;
        inorder(out, ptr->getRight());
    }
}

// helper function to delete the tree nodes
void TreeDB::delete_tree(TreeNode* ptr) {
    if (ptr == nullptr) return;
    if (ptr->getLeft() != nullptr) {
        delete_tree(ptr->getLeft());
    }

    if(ptr->getRight() != nullptr) {
        delete_tree(ptr->getRight());
    }

    delete ptr;
}

// helper function to remove one node considering different scenarios
TreeNode* TreeDB::removOne(TreeNode* ptr, string name, bool& result) {
    TreeNode* ptrParent = nullptr;
    TreeNode* leftMaxParent = nullptr;
    TreeNode* leftMax = nullptr;

    while (ptr!= nullptr) {
        if(name == ptr->getEntry()->getName()) {
            result = true;ytgffdz
            // If the node is a leaf
            if(ptr->getLeft() == nullptr && ptr->getRight() == nullptr && ptr != root) {
                if (ptr == ptrParent->getRight()) {
                    delete ptrParent->getRight();
                    ptrParent->setRight(nullptr);
                } else if (ptr == ptrParent->getLeft()) {
                    delete ptrParent->getLeft();
                    ptrParent->setLeft(nullptr);
                }
                ptr = nullptr;
                return root;

                // if the node to delete is a root
            } else if (ptr->getEntry()->getName() == root->getEntry()->getName()) {

                TreeNode* temp = ptr;
                if (root->getLeft() ==  nullptr) {
                    TreeNode* last = root;
                    root = root->getRight();
                    delete last;
                    last = nullptr;
                } else {7
                    leftMax = findLeftMax(temp);

                    leftMaxParent = findParent(root, leftMax);
                    this->root->getEntry()->setName(leftMax->getEntry()->getName());
                    this->root->getEntry()->setIPaddress(leftMax->getEntry()->getIPaddress());
                    this->root->getEntry()->setActive(leftMax->getEntry()->getActive());
                    if (leftMax == leftMaxParent->getLeft()) {
                        if (leftMax->getRight() == nullptr && leftMax->getLeft() == nullptr) {
                            delete leftMaxParent->getLeft();
                            leftMaxParent->setLeft(nullptr);
                        } else {
                            TreeNode *temp = leftMax->getLeft();
                            delete leftMaxParent->getLeft();
                            leftMaxParent->setLeft(temp);
                        }

                    } else if (leftMax == leftMaxParent->getRight()) {
                        if (leftMax->getRight() == nullptr && leftMax->getLeft() == nullptr) {
                            delete leftMaxParent->getRight();
                            leftMaxParent->setRight(nullptr);
                        } else {
                            TreeNode *temp = leftMax->getLeft();
                            delete leftMaxParent->getRight();
                            leftMaxParent->setRight(temp);
                        }

                    }
                }
                return root;

                // If the  node is  the  second  last node with no left child
            } else if (ptr->getLeft() == nullptr &&  ptr->getRight() != nullptr){
                if (ptr == ptrParent->getRight()) {
                    TreeNode*  temp = ptr-> getRight();
                    delete  ptrParent->getRight();
                    ptrParent->setRight(temp);
                } else if (ptr == ptrParent->getLeft()) {
                    TreeNode*  temp = ptr-> getRight();
                    delete ptrParent->getLeft();
                    ptrParent->setLeft(temp);
                }

                ptr = nullptr;
                return root;

                //  If the  node is  the second  last node with no right child
            } else  if (ptr->getRight() == nullptr && ptr->getLeft() != nullptr) {
                if (ptr == ptrParent->getLeft()){
                    TreeNode* temp = ptr->getLeft();
                    delete ptrParent->getLeft();
                    ptrParent->setLeft(temp);
                } else  {
                    TreeNode *temp =  ptr->getLeft();
                    delete  ptrParent->getRight();
                    ptrParent->setRight(temp);
                }
                return root;

                // for all the other normal cases
            } else {
                TreeNode* temp = ptr;
                if (ptr->getLeft() ==  nullptr) {
                    TreeNode* last = ptr;
                    ptr =  ptr->getRight();
                    delete last;
                    last = nullptr;
                } else  {
                    leftMax = findLeftMax(temp);

                    leftMaxParent = findParent(root, leftMax);
                    ptr->getEntry()->setName(leftMax->getEntry()->getName());
                    ptr->getEntry()->setIPaddress(leftMax->getEntry()->getIPaddress());
                    ptr->getEntry()->setActive(leftMax->getEntry()->getActive());
                    if (leftMax == leftMaxParent->getLeft()) {
                        if (leftMax->getRight() == nullptr && leftMax->getLeft() == nullptr) {
                            delete leftMaxParent->getLeft();
                            leftMaxParent->setLeft(nullptr);
                        } else {
                            TreeNode* temp = leftMax->getLeft();
                            delete leftMaxParent->getLeft();
                            leftMaxParent->setLeft(temp);
                        }

                    } else if (leftMax == leftMaxParent->getRight())  {
                        if (leftMax->getRight() == nullptr && leftMax->getLeft() == nullptr) {
                            delete leftMaxParent->getRight();
                            leftMaxParent->setRight(nullptr);
                        } else {
                            TreeNode* temp = leftMax->getLeft();
                            delete leftMaxParent->getRight();
                            leftMaxParent->setRight(temp);
                        }

                    }
                }
                return root;
            }

            // not find name matched
        } else if(name < ptr->getEntry()->getName()) {
            ptrParent = ptr;
            ptr = ptr->getLeft();
        } else if (name > ptr->getEntry()->getName()) {
            ptrParent = ptr;
            ptr = ptr->getRight();
        }
    }
    return root;

}

// function to find the max node on the left subtress of the node to delete
TreeNode* TreeDB::findLeftMax(TreeNode* ptr) {
    TreeNode* max =  nullptr;
    if(ptr == nullptr) {
        return ptr;
    }

    max = ptr->getLeft();
    while(max->getRight() != nullptr) {
        max = max->getRight();
    }

    return max;
}

// find the parent of the specified node
TreeNode* TreeDB::findParent(TreeNode* root, TreeNode* child) {
    TreeNode* rootParent = nullptr;
    while (root!= nullptr)  {
        if(child->getEntry()->getName() > root->getEntry()->getName())  {
            rootParent = root;
            root = root->getRight();
        } else if (child->getEntry()->getName() < root->getEntry()->getName()) {
            rootParent = root;
            root = root->getLeft();
        } else  {
            return rootParent;
        }
    }
}
