#include <iostream>
#include <sstream>
#include <string>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"
using namespace std;

int main() {
    string line;
    string command;
    TreeDB obj;

    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while(!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;

            // creates a new entry
        if (command == "insert") {
            string n;
            unsigned int ip;
            string status;
            bool active;
            lineStream >> n >> ip >> status;

            if (status == "active") {
                active = true;
            } else if (status == "inactive") {
                active = false;
            }

            DBentry* entPtr = new DBentry (n, ip, active);
            if (obj.insert(entPtr)) {
                cout << "Success" << endl;
            } else {
                cout << "Error: entry already exists" << endl;
            }

            // finds the entry with the key name in the DB
        } else if (command == "find") {
            string n;
            lineStream >> n;
            DBentry* ptr = obj.find(n);
            if(ptr == nullptr) {
                cout << "Error: entry does not exist" << endl;
            } else {
                operator<<(cout, *ptr);
            }

            // this command finds the entry with the key name in the DB
        } else if (command == "remove") {
            string n;
            lineStream >> n;
            if(obj.remove(n)) {
                cout << "Success" << endl;
            } else {
                cout << "Error: entry does not exists" << endl;
            }

            // this command deletes the entry with the key name from the DB
        } else if (command == "printall") {
            operator<<(cout, obj);

            // this command finds the entry with the key name in the DB
        } else if (command == "printprobes") {
            string n;
            lineStream >> n;
            DBentry* ptr = obj.find(n);
            if(ptr == nullptr) {
                cout << "Error: entry does not exist" << endl;
            } else {
                // print out the number of probes
                obj.printProbes();
            }

            // this command deletes all the entries in the DB
        } else if (command == "removeall") {
            obj.clear();
            cout << "Success" << endl;

            // this command counts the number of entries in the DB
        } else if (command == "countactive") {
            obj.countActive();

            // this command updates the status of the entry with the given name
        } else if (command == "updatestatus") {
            string n, status;
            lineStream >> n >> status;
            DBentry* ptr = obj.find(n);
            if(ptr == nullptr) {
                cout << "Error: entry does not exist" << endl;
            } else {
                if(status == "active") {
                    ptr->setActive(true);
                } else {
                    ptr->setActive(false);
                }
                cout << "Success" << endl;
            }
        }

        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
    }

    return 0;
}