/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 * Supervised by: Tarek Abdelrahman
 */

#ifndef ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP
#define ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP


/**
 * Student editable struct for storing their ai state
 * Yes, you may change this header.
 * Maybe you want to remember the last asteroid Id you shot at?
 */
#include <galaxy-explorer/AsteroidsObserver.hpp>
#include <galaxy-explorer/AsteroidList.hpp>
#include <galaxy-explorer/GameAI.hpp>
#include <math.h>
#include  <iostream>
using namespace std;

// function for determining whether an asteroid would hit the ship or not
bool isDanger(MyAIData* my_game_ai, AsteroidListItem* search);

// functions for finding the center of the targeted asteroid
int asteroidCenterX(AsteroidListItem* asteroid);
int asteroidCenterY(AsteroidListItem* asteroid);

// function for locating the asteroid
void asteroidLocate(MyAIData* my_game_ai, AsteroidListItem* ptr);

// function for determining the angle of shooting the bullet
double shootingAngle(MyAIData* my_game_ai, AsteroidListItem* ptr);

struct MyAIData {
    bool debug_on = true;
    int bullet_velocity = 10;
    int height = 2000;// y
    int width = 2000;  //x
    int left = 9000; //xi
    int top = 17999; //length //yi
    int count0_18000 = 1; 
    int count18000_ = 0;

    // parameters for locating the asteroid
    double a, b, c, timeCandidate1, timeCandidate2, time; // time is the time when the bullet hits the asteroid
    double asteroidHorV, asteroidVerV;
    double asteroidPosx, asteroidPosy;
    double asteroidPosxFinal, asteroidPosyFinal;
    double shootingAngle;
        
        
};
// function for determining whether an asteroid would hit the ship or not
bool isDanger(MyAIData* my_game_ai, AsteroidListItem* search) {
    if (search == nullptr) {
        return false;
    }
    
    // position  of the asteroid
    double posX = asteroidCenterX(search);
    double posY = asteroidCenterY(search);
     
    double ahorVi = search->getData().getVelocity().x;
    double averVi = search->getData().getVelocity().y;
    
    //double ahorPosleft = search->getData()->getCurrentHitbox().left + ahorVi * hittimeleft;
    // final position  assumption of the asteriod to see whether it will hit the ship or not
    // x is fixed for ship in this scenario
    double hittimeleft = (my_game_ai->left  - search->getData().getCurrentHitbox().left) / ahorVi;
    double averPosleft = posY + averVi * hittimeleft;
    
    if (averPosleft <= (my_game_ai->top + my_game_ai->height) && averPosleft >= my_game_ai->top) {
        return true;
    }
    
    //double averPostop = search->getData()->getCurrentHitbox().top + averVi * hittimetop;
    // final position  assumption of the asteriod to see whether it will hit the ship or not
    // y is fixed for ship in this scenario
    double hittimetop = (my_game_ai->top - posY) / averVi;
    double ahorPostop =  posX + ahorVi * hittimetop;
    if(ahorPostop <= (my_game_ai->left + my_game_ai->width) &&  ahorPostop >= my_game_ai->left) {
        return true;
    }
    
    // final position  assumption of the asteriod to see whether it will hit the ship or not
    // x is fixed for ship in this scenario
    double hittimerig = (my_game_ai->left + my_game_ai->width - posX) / ahorVi;
    double averPosrig = posY + averVi * hittimerig;
    if (averPosrig <= (my_game_ai->top + my_game_ai->height) && averPosrig >= my_game_ai->top) {
        return true;
    }
    
    // final position  assumption of the asteriod to see whether it will hit the ship or not
    // y is fixed for ship in this scenario
    double hittimebot = (my_game_ai->top + my_game_ai->height - posY) / averVi;
    double ahorPosbot  = posX + ahorVi  * hittimebot;
    if(ahorPosbot <= (my_game_ai->left + my_game_ai->width) &&  ahorPosbot >= my_game_ai->left) {
        return true;
    }
    
    // After testing for sides of the ship, if the asteroid will not hit the ship in any direction,
    // the asteroid is safe
    return false;
}

// function for locating the asteroid
void asteroidLocate(MyAIData* my_game_ai, AsteroidListItem* ptr){
    if (ptr == nullptr) {
        return;
    }
    
    my_game_ai->asteroidHorV = ptr->getData().getVelocity().x;
    my_game_ai->asteroidVerV = ptr->getData().getVelocity().y;
    my_game_ai->asteroidPosx = asteroidCenterX(ptr);
    my_game_ai->asteroidPosy = asteroidCenterY(ptr);
    my_game_ai->a = my_game_ai->asteroidHorV * my_game_ai->asteroidHorV 
            + my_game_ai->asteroidVerV * my_game_ai->asteroidVerV 
            - my_game_ai->bullet_velocity * my_game_ai->bullet_velocity;
    my_game_ai->b = 2 * (my_game_ai->asteroidHorV * (my_game_ai->asteroidPosx - my_game_ai->left) 
            + my_game_ai->asteroidVerV * (my_game_ai->asteroidPosy - my_game_ai->top));
    my_game_ai->c = (my_game_ai->asteroidPosx - my_game_ai->left) * (my_game_ai->asteroidPosx - my_game_ai->left) 
            + my_game_ai->asteroidVerV * (my_game_ai->asteroidPosy - my_game_ai->top) 
            * my_game_ai->asteroidVerV * (my_game_ai->asteroidPosy - my_game_ai->top);
    my_game_ai->timeCandidate1 = (-my_game_ai->b + sqrt(my_game_ai->b * my_game_ai->b - 4 * my_game_ai->a * my_game_ai->c)) 
            / (2 * my_game_ai->a);
    my_game_ai->timeCandidate2 = (-my_game_ai->b - sqrt(my_game_ai->b * my_game_ai->b - 4 * my_game_ai->a * my_game_ai->c)) 
            / (2 * my_game_ai->a);
    
    if (my_game_ai->timeCandidate1 >= 0) {
        my_game_ai->time = my_game_ai->timeCandidate1;
    } else if (my_game_ai->timeCandidate2 >= 0) {
        my_game_ai->time = my_game_ai->timeCandidate2;
    }
    
    my_game_ai->asteroidPosxFinal = my_game_ai->asteroidPosx + my_game_ai->asteroidVerV * my_game_ai->time;
    my_game_ai->asteroidPosyFinal = my_game_ai->asteroidPosy + my_game_ai->asteroidVerV * my_game_ai->time;
    
}

// Find the x coordinate of the center of asteroid
int asteroidCenterX(AsteroidListItem* asteroid) {
    if (asteroid == nullptr) {
        return 0;
    }
    
    int left = asteroid->getData().getCurrentHitbox().left;
    int width = asteroid->getData().getCurrentHitbox().width;
    int center = left + (width / 2);
    return center;
}

//Find the y coordinate of the center of asteroid
int asteroidCenterY(AsteroidListItem* asteroid) {
    if (asteroid == nullptr) {
        return 0;
    }
    
    int top = asteroid->getData().getCurrentHitbox().top; // y's top is smaller than bottom due to scale
    int height = asteroid->getData().getCurrentHitbox().height;
    int center = top + (height / 2) ;
    return center; 
}

//Determine the shooting angle of the ship
double shootingAngle(MyAIData* my_game_ai, AsteroidListItem* ptr) {
    asteroidLocate(my_game_ai, ptr);
    double upper = ((my_game_ai->left + my_game_ai->width / 2 ) - my_game_ai->asteroidPosxFinal);
    double lower = ((my_game_ai->top + my_game_ai->height / 2) - my_game_ai->asteroidPosyFinal);
    my_game_ai-> shootingAngle = atan(upper / lower) * (180 / 3.1415926535898) * 1000;
    
    return my_game_ai-> shootingAngle;
}


#endif /* ECE244_GALAXY_EXPLORER_STUDENT_AI_DATA_HPP */
