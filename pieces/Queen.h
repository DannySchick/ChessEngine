//
// Created by Danny on 4/19/2016.
//

#ifndef CHESSENGINE_QUEEN_H
#define CHESSENGINE_QUEEN_H

#include "../Piece.h"

class Queen: public Piece {
public:
    Queen(bool white, int x, int y): Piece(white, x, y){
        ID = 4;
        if(white) {
            name = "Q";
        } else {
            name = "q";
        }
        value = 975;
    }

    int legalMove(vector<int> newCoords, vector<vector<Piece*>> board);

};


#endif //CHESSENGINE_QUEEN_H
