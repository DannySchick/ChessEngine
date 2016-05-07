//
// Created by Danny on 4/21/2016.
//

#include <iostream>
#include <algorithm>
#include "Board.h"

Board::Board() {
    // populate with the 2nd dimension vector
    for(int i=0;i<8;i++) {
        board[i] = vector<Piece>(8);
    }
    /** ------------ FIRST ROW -------------- */
    board[0][0] = Piece(5, true, 0, 0);
    board[1][0] = Piece(2, true, 1, 0);
    board[2][0] = Piece(0, true, 2, 0);
    board[3][0] = Piece(4, true, 3, 0);
    board[4][0] = Piece(1, true, 4, 0);
    board[5][0] = Piece(0, true, 5, 0);
    board[6][0] = Piece(2, true, 6, 0);
    board[7][0] = Piece(5, true, 7, 0);

    /** ------------ SECOND ROW -------------- */
    for(int i=0;i<8;i++){
        board[i][1] = Piece(3, true, i, 1);
    }


    /** ------------ SIXTH ROW -------------- */
    for(int i=0;i<8;i++){
        board[i][6] = Piece(3, false, i, 6);
    }

    /** ------------ SEVENTH ROW -------------- */
    board[0][7] = Piece(5, false, 0, 7);
    board[1][7] = Piece(2, false, 1, 7);
    board[2][7] = Piece(0, false, 2, 7);
    board[3][7] = Piece(4, false, 3, 7);
    board[4][7] = Piece(1, false, 4, 7);
    board[5][7] = Piece(0, false, 5, 7);
    board[6][7] = Piece(2, false, 6, 7);
    board[7][7] = Piece(5, false, 7, 7);
}

Board::Board(const Board &given) {
    blackCheckmated = given.blackCheckmated;
    whiteCheckmated = given.whiteCheckmated;
    blackInCheck = given.blackInCheck;
    whiteInCheck = given.whiteInCheck;
    whitesTurn = given.whitesTurn;
    whiteCaptured = given.whiteCaptured;
    blackCaptured = given.blackCaptured;
    for(int i=0;i<8;i++) {
        board[i] = vector<Piece>(8);
    }


    // loop through each real game square for a deep copy
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            Piece curPiece = given.board[i][j];
            if(&curPiece == NULL){
                board[i][j] = NULL;
            } else {
                board[i][j] = Piece(curPiece.getID(), curPiece.isWhite, curPiece.getX(), curPiece.getY());
            }
        }
    }
}


void Board::print() {
    cout << "   A B C D E F G H " << endl;
    cout << "   --------------- " << endl;
    for(int i=7;i>=0;i--){
        cout << i+1 << "| ";
        for(int j=0;j<8;j++){
            if(&board[j][i] == NULL){
                    cout << '-' << ' ';
            } else {
                cout << board[j][i].getName() << ' ';
            }
        }
        cout << "|" << i+1 << endl;
    }
    cout << "   --------------- " << endl;
    cout << "   A B C D E F G H " << endl;

    if(!whiteCaptured.empty()){
        cout << "Captured White Pieces: ";
        for(Piece p : whiteCaptured){
            cout << p.getName();
        }
        cout << endl;
    }
    if(!blackCaptured.empty()){
        cout << "Captured Black Pieces: ";
        for(Piece p : blackCaptured){
            cout << p.getName();
        }
        cout << endl;
    }
}

int Board::move(vector<int> from, vector<int> to, bool verifyOnly) {
    //TODO: make sure move can't be made in a check
    Piece movePiece = board[from[0]][from[1]];
    if(&movePiece == NULL){
//        cout << "Invalid Piece specified" << endl;
        return 1;
    }
    if(movePiece.isWhite != whitesTurn){
//        cout << "It's not that piece's turn!" << endl;
        return 4;
    }
    int moveStatus = movePiece.legalMove(to, board);
    if(moveStatus == 1){
//        cout << "Invalid destination" << endl;
        return 1;
    } else if(moveStatus == 2){
//        cout << "a piece is blocking the way";
        return 1;
    }

    if(moveStatus == 0){
        // we move the piece
        // check if there's a capture
        movePiece.setPos(to);
        if(&board[to[0]][to[1]] != NULL && movePiece.isWhite != board[to[0]][to[1]].isWhite){
            Piece captured = board[to[0]][to[1]];
            // there's a capture
            if(captured.isWhite){
                whiteCaptured.insert(whiteCaptured.end(), captured);
                captured.capture();
                whiteCount -= 1;
            } else {
                blackCaptured.insert(blackCaptured.end(), captured);
                captured.capture();
                blackCount -= 1;
            }


//            for(int i=0;i<pieceList.size();i++){
//                if(pieceList[i] == captured){
//                    pieceList.erase(pieceList.begin() + i);
//                }
//
//            }

            board[to[0]][to[1]] = movePiece;
            board[from[0]][from[1]] = NULL;
            return 0;

        } else {
            board[to[0]][to[1]] = movePiece;
            board[from[0]][from[1]] = NULL;
            return 0;
        }
    }

    else{
        return 1;
    }

}





int Board::inputMove(string input) {
    vector<int> firstCoords = vector<int>(2);
    vector<int> secondCoords = vector<int>(2);

    vector<int> curStr = vector<int>();

    // will change to false after we take the first square from user
    bool firstPos = true;


    for(char c : input){
        if (curStr.size() < 2) {
            if(c != '-') {
                if(isdigit(c)){
                    // we need to convert from the ASCII value of the int to the actual int
                    int g;
                    g = c-48; // this gives us the actual number
                    g = g - 1; // then we subtract one, because our board starts at 0 not 1
                    curStr.insert(curStr.end(), g);
                } else {
                    int i;
                    i = getIntValFromChar(c);
                    curStr.insert(curStr.end(), i);
                }
            }
        } else {
            if (firstPos) {
                firstCoords[0] = curStr[0];
                firstCoords[1] = curStr[1];
                firstPos = false;
            }
            curStr.clear();
        }

    }

    secondCoords[0] = curStr[0];
    secondCoords[1] = curStr[1];

    // make a move and return the validity of move to the game loop
    int status;
    status = move(firstCoords, secondCoords, false);
    if(status == 0){
        return 0;
    } else {
        return 1;
    }
}





int Board::getIntValFromChar(char c) {
    // simple switch to get the right board value from the char
    switch(c){
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default: return -1;
    }
}

Board::~Board() {

    for(int i = 0; i < board.size(); ++i){
        for(int j = 0; j < board[i].size(); ++j){
            delete board[i][j];
        }
        board[i].clear();
    }
}