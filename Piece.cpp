//
// Created by Danny on 4/19/2016.
//

#include <iostream>
#include "Piece.h"

Piece::Piece() {}


Piece::Piece(bool white, int x, int y) {
    isWhite = white;
    coords[0] = x;
    coords[1] = y;
}


string Piece::getName() {
    return name;
}

int Piece::getID() {
    return ID;
}

int Piece::getVal() {
    return value;
}

int Piece::getX() {
    return coords[0];
}

int Piece::getY() {
    return coords[1];
}


vector<int> Piece::getPos() {
    return coords;
}

void Piece::setPos(vector<int> newPos) {
    coords = newPos;
}

void Piece::capture() {
    captured = true;
}

bool Piece::isCaptured() {
    return captured;
}

Piece::~Piece() {
}



