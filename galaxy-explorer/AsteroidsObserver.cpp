/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

// called whenever a new asteroid appears on the field
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.pushFront(asteroid);
}

// called when an asteroid has moved
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    //beforeBegin is the head
   AsteroidListItem* currentItem = asteroid_list.begin();
    while(currentItem != nullptr) {
        if(currentItem->getData().getID() == asteroid.getID()) {
            currentItem->getData() = asteroid;
            break; // Get out of the loop
        } else {
            currentItem = currentItem->getNext();
        }
    }
}

// called when an asteroid leaves the field without being destroyed
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* currentItem = asteroid_list.begin();
    while(currentItem != nullptr) {
        if(currentItem->getNext() != nullptr &&
                currentItem->getNext()->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(currentItem);
        } else {
            currentItem = currentItem->getNext();
        }
        
    }
}

// called when an asteroid is destroyed by a phaser shot
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    onAsteroidOutOfRange(asteroid);
}
