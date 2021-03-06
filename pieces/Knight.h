//
// Created by Danny on 4/19/2016.
//

#ifndef CHESSENGINE_KNIGHT_H
#define CHESSENGINE_KNIGHT_H


#include "../Piece.h"

class Knight: public Piece {
public:
    Knight(bool white, int x, int y): Piece(white, x, y){
        ID = 2;
        if(white) {
            name = "N";
        } else {
            name = "n";
        }
        value = 320;
    }

    int legalMove(vector<int> newCoords, vector<vector<Piece*>> board);

};


#endif //CHESSENGINE_KNIGHT_H
