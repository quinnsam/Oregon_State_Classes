/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::utility(){
    // To be filled in
}

void MinimaxPlayer::successor(){
    // To be filled in
}

void MinimaxPlayer::minimaxDecision(){
    // To be filled in
}

void MinimaxPlayer::maxValue() {
    // To be filled in
}

void MinimaxPlayer::minValue() {
    // To be filled in
}


void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you

}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
