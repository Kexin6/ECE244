//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes = 0;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool invalidShapeName(string output, stringstream &stream);
bool shapeNameExist(string name, stringstream &stream);
bool shapeNameNotFound(string name, stringstream &stream);
bool invalidShapeType(string output, stringstream &stream);
bool invalidValueLocate(int value, stringstream  &stream);
bool invalidValueAngle(int value, stringstream &stream);
bool tooManyArgument(stringstream &stream);
bool tooFewArgument(stringstream &stream);
bool shapeArrayFull(int shapeCount, int max_shapes);
int indexOfShape(string name);


int main() {

    string line;
    string command;

    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);


        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;



        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        //Check whether the command is valid
        if (lineStream.fail()) {
            cout << "Error: invalid command" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            //Case of maxShapes

        } else if (command == keyWordsList[1]) {
            lineStream >> max_shapes;
            bool valid = true;

           if (!tooFewArgument(lineStream)) {
               if (lineStream.peek() != 32 && lineStream.peek() != -1) {
                   valid = false;
                   cout << "Error: invalid argument" << endl;
               } else if (max_shapes < 0) {
                   valid = false;
                   cout << "Error: invalid value" << endl;
               }

               if (!tooManyArgument(lineStream) && valid) {
                   shapesArray = new shape* [max_shapes];
                   cout << "New database: max shapes is " << max_shapes << endl;
               }

           }


            // Case of create
        } else if (command == keyWordsList[2]) {
            string n, t;
            int x_loc, y_loc, x_sz, y_sz;
            if (!tooFewArgument(lineStream)) {
                lineStream >> n;
                if (!invalidShapeName(n, lineStream) && !shapeNameExist(n, lineStream) && !tooFewArgument(lineStream)
                    && !shapeArrayFull(shapeCount, max_shapes)) {
                    lineStream >> t;
                    if (!invalidShapeType(t, lineStream) && !tooFewArgument(lineStream)) {
                        lineStream >> x_loc;
                        if (!invalidValueLocate(x_loc, lineStream) && !tooFewArgument(lineStream)) {
                            lineStream >> y_loc;
                            if (!invalidValueLocate(y_loc, lineStream) && !tooFewArgument(lineStream)) {
                                lineStream >> x_sz;
                                if (!invalidValueAngle(x_sz, lineStream) && !tooFewArgument(lineStream)) {
                                    lineStream >> y_sz;
                                    if (!invalidValueAngle(y_sz, lineStream) && !tooManyArgument(lineStream)) {
                                        shapesArray[shapeCount] = new shape(n, t, x_loc, y_loc, x_sz, y_sz);
                                        cout << "Created ";
                                        shapesArray[shapeCount] -> draw();
                                        shapeCount ++;

                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Case of move
        } else if (command == keyWordsList[3]) {
            string n;
            int x_loc, y_loc, index;
            if (!tooFewArgument(lineStream)) {
                lineStream >> n;
                if (!invalidShapeName(n, lineStream) && !shapeNameNotFound(n, lineStream) &&
                    !tooFewArgument(lineStream)) {
                    lineStream >> x_loc;
                    if (!invalidValueLocate(x_loc, lineStream) && !tooFewArgument(lineStream)) {
                        lineStream >> y_loc;
                        if (!invalidValueLocate(y_loc, lineStream) && !tooManyArgument(lineStream)) {
                            index = indexOfShape(n);
                            shapesArray[index]->setXlocation(x_loc);
                            shapesArray[index]->setYlocation(y_loc);
                            cout << "Moved " << shapesArray[index]->getName() << " to ";
                            cout << shapesArray[index]->getXlocation() << " " << shapesArray[index]->getYlocation()
                                 << endl;
                        }
                    }


                }
            }

            // Case of rotate
        } else if (command == keyWordsList[4]) {
            string n;
            int angle, index;
            lineStream >> n;
            if (!tooFewArgument(lineStream) && !invalidShapeName(n, lineStream) && !shapeNameNotFound(n, lineStream)) {
                lineStream >> angle;
                if (!invalidValueAngle(angle, lineStream) && !tooManyArgument(lineStream)) {
                    index = indexOfShape(n);
                    shapesArray[index] -> setRotate(angle);
                    cout << "Rotated " << shapesArray[index] -> getName() << " by " << angle << " degrees" << endl;

                }

            }

            // Case of draw
        } else if (command == keyWordsList[5]) {
            string n;
            if (!tooFewArgument(lineStream)) {
                lineStream >> n;
                if (( n == keyWordsList[0] || !invalidShapeName(n, lineStream)) &&
                    ( n == keyWordsList[0] || !shapeNameNotFound(n, lineStream))
                    && !tooManyArgument(lineStream)) {

                    // Case for draw all
                    if (n == keyWordsList[0]) {
                        cout << "Drew all shapes " << endl;
                        for (int i = 0; i < shapeCount; i ++) {
                            if (shapesArray[i] != NULL) {
                                shapesArray[i] -> draw();
                            }
                        }

                        // Case for drawing one single shape
                    } else {
                        for (int i = 0; i < shapeCount; i ++) {
                            if (shapesArray[i] != NULL) {
                                if (shapesArray[i] -> getName() == n) {

                                    cout << "Drew " << n << endl;
                                    shapesArray[i] -> draw();
                                }

                            }
                        }
                    }
                }
            }


            // Case of delete
        } else if (command == keyWordsList[6]) {
            string n;
            if (!tooFewArgument(lineStream)) {
                lineStream >> n;
                if ((n == keyWordsList[0] || !invalidShapeName(n, lineStream))
                    && (n == keyWordsList[0] ||!shapeNameNotFound(n, lineStream))
                    && !tooManyArgument(lineStream)) {
                    // Case for delete all
                    if (n == keyWordsList[0]) {
                        cout << "Deleted: all shapes" << endl;
                        for (int i = 0; i < shapeCount; i ++) {
                            delete shapesArray[i];
                            shapesArray[i] = NULL;
                        }

                        // Case for deleting one shape name
                    } else {
                        for (int i = 0; i < shapeCount; i ++) {
                            if (shapesArray[i] != NULL) {
                                if (shapesArray[i] -> getName() == n) {
                                    cout << "Deleted shape " << shapesArray[i] -> getName() << endl;
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;
                                }
                            }

                        }
                    }
                }
            }
            // invalid command if the command is not in the keyWordsList
        } else {
            cout << "Error: invalid command" << endl;
            lineStream.clear();
            lineStream.ignore(1000, '\n');
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line

    }  // End input loop until EOF.

    return 0;
}

// Check if the shape name is a key word
bool invalidShapeName(string output, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }



    for (int i = 0; i < 7; i ++) {
        if (output == globals_h::keyWordsList[i]) {
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    for (int i = 0; i < 3; i ++) {
        if (output == globals_h::shapeTypesList[i]) {
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    return false;


}

// Check whether the shape name that is about to create has the same name as others
bool shapeNameExist(string name, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }

    for (int i = 0; i < shapeCount; i ++) {
        if (shapesArray[i] != NULL) {
            if (name == shapesArray[i] -> getName()) {
                stream.ignore(1000, '\n');
                cout << "Error: shape " << name << " exists" << endl;
                return true;
            }
        }

    }
    return false;

}

// Check whether the shape name exists when doing operations on that
bool shapeNameNotFound(string name, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }

    for (int i = 0; i < shapeCount; i ++) {
        if (shapesArray[i] != NULL) {
            if (name == shapesArray[i] -> getName() || name == keyWordsList[0]) {
                //Shape name is found
                return false;
            }
        }

    }

    cout << "Error: shape "<< name  << " not found" << endl;
    stream.ignore(1000, '\n');
    return true;
}

//Check whether the shape type is in the shapeTypeList
bool invalidShapeType(string output, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }

    if (output != shapeTypesList[0] && output != shapeTypesList[1] && output != shapeTypesList[2]) {
        cout << "Error: invalid shape type" << endl;
        return true;
    }
    return false;
}

// Check for invalid value in location
bool invalidValueLocate(int value, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }

    // Use peek to check whether the integer is valid
    if(stream.peek() != ' ' && stream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    if (value < 0) {
        cout << "Error: invalid value" << endl;
        return true;
    }
    return false;
}

// Check for invalid value in angle
bool invalidValueAngle(int value, stringstream &stream) {
    if (tooFewArgument(stream)) {
        return true;
    }

    // Use peek to check whether the integer is valid
    if(stream.peek() != ' ' && stream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return true;
    }
    if (value > 360 || value < 0) {
        cout << "Error: invalid value" << endl;
        return true;
    }
    return false;
}

// Check if the argument exceeds need
bool tooManyArgument(stringstream &stream) {
    char consume;
    int peek = stream.peek();

    //Using peek to check whether the next character is a space (safe) or another character (too many)
    if (!stream.eof()) {
        while (peek == 32) {
            stream >> consume;
            peek = stream.peek();
            if (consume != NULL) {
                cout << "Error: too many arguments" << endl;
                stream.ignore(1000, '\n');
                return true;
            }
        }

    }
    return false;
}

// Check if the input value matches the type of input wanted or
// the number of arguments is not enough
bool tooFewArgument(stringstream &stream) {
    if(stream.fail()) {
        if (stream.eof()) {
            cout << "Error: too few arguments" << endl;
            return true;

        } else {
            cout << "Error: invalid argument" << endl;
            stream.clear();
            stream.ignore(1000, '\n');
            return true;
        }
    }
    return false;
}

// Check whether the array is full and reach the max shapes
bool shapeArrayFull(int shapeCount, int max_shapes) {
    if (shapeCount == max_shapes) {
        cout << "Error: shape array is full" << endl;
        return true;
    }
    return false;
}


// Check for the index i for supplmentory use
int indexOfShape(string name) {
    int index;
    for (int i = 0; i < shapeCount; i ++) {
        if ((shapesArray[i]  != NULL) && (shapesArray[i] -> getName() == name)) {
            index = i;
        }
    }
    return index;
}
