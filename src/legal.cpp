#include "legal.h"
#include "MoveInstructions.h"
#include "Check.h"

#include "RookLegal.h"
#include "BishopLegal.h"
#include "KnightLegal.h"
#include "PawnLegal.h"
#include "KingLegal.h"

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std ;

bool PieceOnBoard(string aPiece, string aBoard[8][8]){
    if ((findPiece(aPiece,aBoard).first != 8) || (findPiece(aPiece,aBoard).second != 0)){
        return true;
    }
    return false;
}

bool RightColor(string aPiece, int moveNb){
    bool isRightColor = ((moveNb % 2 == 0) && aPiece[0] == 'w') || ((moveNb % 2 == 1) && aPiece[0] == 'b');
    return isRightColor;
}


vector<pair<string, pair<int, int>>> LegalMoves(string aBoard[8][8], int moveNb){

    vector<pair<string, pair<int, int>>> legalMoves ;
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    string pieces[32] = {"wP0","wP1","wP2","wP3","wP4","wP5","wP6","wP7",
                         "wR1","wN1","wB1","wK","wQ","wB2","wN2","wR2",
                         "bP0","bP1","bP2","bP3","bP4","bP5","bP6","bP7",
                         "bR1","bN1","bB1","bK","bQ","bB2","bN2","bR2"};

    //cout << "Pieces analysed to see all legal moves :" << endl;
    char colorAlly = 'w';
    char colorEnnemy = 'b';
    int k = 0;
    for(int i = 0; i < 16 ; i++){
        if ((!isWhiteTurn) && (i == 0)){
            k+=16;
            colorAlly = 'b';
            colorEnnemy = 'w';
        }
        string currentPiece = pieces[k];
        pair<int,int> locCurrentPiece ;
        locCurrentPiece = findPiece(currentPiece,aBoard);

        if (!((locCurrentPiece.first == 8) && (locCurrentPiece.second == 0)))
            {

                //cout << currentPiece;

                //Rooks
                if (currentPiece[1] == 'R'){
                    legalRook(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

                //Bishops
                if (currentPiece[1] == 'B'){
                    legalBishop(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

                //Queen
                if (currentPiece[1] == 'Q'){
                    legalBishop(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                    legalRook(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

                //Knight
                if (currentPiece[1] == 'N'){
                    legalKnight(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

                //Pawn
                if (currentPiece[1] == 'P'){
                    legalPawn(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

                //King
                if (currentPiece[1] == 'K'){
                    legalKing(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy, moveNb);
                }

            }/*else{
                cout << "Piece : **" << currentPiece << "not on board. Coord are  "
            << locCurrentPiece.first << locCurrentPiece.second << endl;}*/

    k+=1 ;
    }
    //for k in range legal move if MoveChecksAllyKing


    /*
    for (int k = 0 ; k < legalMoves.size() ; k++ ){
        if (MoveChecksAllyKing(aBoard,moveNb,legalMoves[k].first,legalMoves[k].second)){
            cout << "problematic move " << legalMoves[k].first << legalMoves[k].second.first << legalMoves[k].second.second << endl;
            legalMoves.erase(legalMoves.begin()+k);
        }
    }*/

    return legalMoves;
}

vector<pair<string, pair<int, int>>> RawLegalMoves(string aBoard[8][8], int moveNb){

    vector<pair<string, pair<int, int>>> legalMoves ;
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    string pieces[32] = {"wP0","wP1","wP2","wP3","wP4","wP5","wP6","wP7",
                         "wR1","wN1","wB1","wK","wQ","wB2","wN2","wR2",
                         "bP0","bP1","bP2","bP3","bP4","bP5","bP6","bP7",
                         "bR1","bN1","bB1","bK","bQ","bB2","bN2","bR2"};

    //cout << "Pieces analysed to see all legal moves :" << endl;
    char colorAlly = 'w';
    char colorEnnemy = 'b';
    int k = 0;
    for(int i = 0; i < 16 ; i++){
        if ((!isWhiteTurn) && (i == 0)){
            k+=16;
            colorAlly = 'b';
            colorEnnemy = 'w';
        }
        string currentPiece = pieces[k];
        pair<int,int> locCurrentPiece ;
        locCurrentPiece = findPiece(currentPiece,aBoard);

        if (!((locCurrentPiece.first == 8) && (locCurrentPiece.second == 0)))
            {

                //cout << currentPiece;

                //Rooks
                if (currentPiece[1] == 'R'){
                    legalRook2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

                //Bishops
                if (currentPiece[1] == 'B'){
                    legalBishop2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

                //Queen
                if (currentPiece[1] == 'Q'){
                    legalBishop2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                    legalRook2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

                //Knight
                if (currentPiece[1] == 'N'){
                    legalKnight2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

                //Pawn
                if (currentPiece[1] == 'P'){
                    legalPawn2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

                //King
                if (currentPiece[1] == 'K'){
                    legalKing2(currentPiece,locCurrentPiece, legalMoves, aBoard, colorAlly, colorEnnemy);
                }

            }

    k+=1 ;
    }

    return legalMoves;
}



bool IsLegal(string nextPiece, string nextDest, string aBoard[8][8], int moveNb){

    if (!PieceOnBoard(nextPiece, aBoard)){
        cout << "Piece not on board" <<endl;
        sleep(2);
        return false;
    }
    if (!RightColor(nextPiece, moveNb)){
        cout << "Wrong color" <<endl;
        sleep(2);
        return false;
    }

    pair<int, int> indNextDest = dest_conv(nextDest);

    pair<string, pair<int, int>> movePlayed ;
    movePlayed.first = nextPiece;
    movePlayed.second = indNextDest;

    vector<pair<string, pair<int, int>>> legalMoves ;
    legalMoves = LegalMoves(aBoard, moveNb);

    bool found = false ;
    for (int i = 0 ; i < legalMoves.size() ; i++ ){
        if (legalMoves[i] == movePlayed) {
            found = true ;
        }
    }

    if (!found){
        cout << "illegal move" <<endl;
        //sleep(2);
        return false;
    }



    return true;

}


