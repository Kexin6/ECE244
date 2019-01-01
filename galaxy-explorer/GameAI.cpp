#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>
#include <math.h>


#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt) {
    this->debug_rt = debug_rt;
    this->game_info = game_info;
    this->asteroid_observer = AsteroidsObserver(this);
    this->my_game_ai = new MyAIData();

    // customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
    debug_rt->clear(sf::Color::Transparent);

    if (customState().debug_on) {
            if (not asteroidsObserver().asteroids().isEmpty()) {
                    const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
                    sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
                    ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
                    ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
                    ast_rect.setOutlineColor(sf::Color::Yellow);
                    ast_rect.setFillColor(sf::Color::Transparent);
                    debug_rt->draw(ast_rect);
            }
    }

    // Shoot when a * t ^ 2 + b * t + c == 0: it will hit the hitbox.
    AsteroidListItem* test = asteroidsObserver().asteroids().begin();
    while (test != NULL) {
        test = test->getNext();
    }   

    AsteroidListItem* search = asteroidsObserver().asteroids().begin();
    AsteroidList dangerousList;
    while(search != nullptr) {
        if(isDanger(my_game_ai, search)) {
            dangerousList.pushFront(search->getData());
        }
        search = search->getNext();
    }

    //AsteroidListItem* ptr = asteroidsObserver().asteroids().beforeBegin();
    AsteroidListItem* ptr = dangerousList.begin();
    double angle = shootingAngle(my_game_ai, ptr);
    if (ptr == nullptr) {
        // if there is no dangerous asteroid, shoot everywhere.
        if(my_game_ai->count0_18000 == 1) {
            if (ship_state.millidegree_rotation >= 30000) {
                my_game_ai->count0_18000 = 0;
                my_game_ai->count18000_ = 1;
            }
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        } else if (my_game_ai->count18000_ == 1) {
            if (ship_state.millidegree_rotation < -30000) {
               my_game_ai->count0_18000 = 1;
               my_game_ai->count18000_ = 0;
            }
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }

    } else {
       if(my_game_ai->count0_18000 == 1) {
            if (ship_state.millidegree_rotation >= 35000) {
                my_game_ai->count0_18000 = 0;
                my_game_ai->count18000_ = 1;
            }
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        } else if (my_game_ai->count18000_ == 1) {
            if (ship_state.millidegree_rotation < -35000) {
               my_game_ai->count0_18000 = 1;
               my_game_ai->count18000_ = 0;
            }
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }

    }
        
}


