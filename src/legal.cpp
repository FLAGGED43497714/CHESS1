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
#include <algorithm>

using namespace std ;

int getPieceValue(char label) ;

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


vector<pair<string, pair<int, int>>> sortLegal(vector<pair<string, pair<int, int>>> legalMoves, string aBoard[8][8]){

    if (legalMoves.size() == 0) {
        return legalMoves ;
    }

    vector<pair<string, pair<int, int>>> sortedLegal ;

    int moveScoreGuesses[legalMoves.size()] ;

    vector<int> moveScoreGuessesSorted ;
    for (int k = 0 ; k < legalMoves.size() ; k++){
            moveScoreGuessesSorted.push_back(0) ;
            moveScoreGuesses[k] = 0 ;
    }

    //cout << "legalMoves.size() = " << legalMoves.size() << endl ;
    //cout << "moveScoreGuessesSorted.size() = " << moveScoreGuessesSorted.size() << endl ;

    //string nothing ;
    //cin >> nothing ;

    char destinationType ;
    string yourPiece ;

    int yourPieceValue ;
    int capturedPieceValue ;

    int dest0 ;
    int dest1 ;

    char colorEnemy ;
    char colorAlly = legalMoves[0].first[0] ;
    //cout << "colorAlly = " << colorAlly ;
    if (colorAlly == 'w') {
        colorEnemy = 'b';
        //cout << "colorEnemy = " << colorEnemy ;
    } else {
        colorEnemy = 'w' ;
        //cout << "colorEnemy = " << colorEnemy ;
    }




    for (int k = 0 ; k < legalMoves.size() ; k++){

        //cout << legalMoves[k].first << legalMoves[k].second.first << legalMoves[k].second.first << endl;


        yourPiece = legalMoves[k].first ;
        dest0 = legalMoves[k].second.first ;
        dest1 = legalMoves[k].second.second ;
        //cout << "yourPiece =" << yourPiece ;
        yourPieceValue = getPieceValue(yourPiece[1]) ;
        //cout << "yourPieceValue =" << yourPieceValue ;

        if (aBoard[dest0][dest1][0] != '*') {
            destinationType = aBoard[dest0][dest1][1] ;
            capturedPieceValue = getPieceValue(destinationType) ;
            moveScoreGuesses[k] = - (10 * capturedPieceValue - yourPieceValue) ;
            //cout << "assigning " << 10 * ( capturedPieceValue - yourPieceValue ) ;
        }

        //cout << "start danger   " ;

        if (colorEnemy == 'w'){
            if ( dest0 <= 6 ){
                if (dest1 <=6 ){
                    if (aBoard[dest0+1][dest1+1][0] == colorEnemy){
                        if(aBoard[dest0+1][dest1+1][1] == 'P'){
                            //cout << "subbing" << dest0+1 << dest1+1 << endl;
                            moveScoreGuesses[k] -= -(yourPieceValue - 100)  ;
                            //cout << "passed, is now " << moveScoreGuesses[k] << endl;
                        }
                    }
                }
                //cout << "a";
                if (dest1 >= 1){
                    if (aBoard[dest0+1][dest1-1][0] == colorEnemy){
                        if (aBoard[dest0+1][dest1-1][1] == 'P'){
                            //cout << "subbing" << dest0+1 << dest1-1 << endl;
                            moveScoreGuesses[k] -= -(yourPieceValue - 100) ;
                        }
                    }
                }
                //cout << "b";
            }
        }


        if (colorEnemy == 'b'){
            if ( dest0 >= 1 ){
                if (dest1 <= 6 ){
                    if (aBoard[dest0-1][dest1+1][0] == colorEnemy){
                        if (aBoard[dest0-1][dest1+1][1] == 'P'){
                            moveScoreGuesses[k] -= -(yourPieceValue - 100) ;
                        }
                    }
                }
                if (dest1 >= 1){
                    if (aBoard[dest0-1][dest1-1][0] == colorEnemy){
                        if (aBoard[dest0-1][dest1-1][1] == 'P'){
                            moveScoreGuesses[k] -= -(yourPieceValue - 100) ;
                        }
                    }
                }
            }
        }

        //cout << "end danger   " ;


    }

    //cout << "c";

    for (int k = 0 ; k < legalMoves.size() ; k++){
        moveScoreGuessesSorted[k] = moveScoreGuesses[k] ;
    }
    //cout << "d";

    /*
    cout << "printing" ;
    for (int k = 0 ; k < legalMoves.size() ; k++){
        cout << moveScoreGuessesSorted[k] << endl;
    }

    cout << "///" << endl;
    */

    sort(moveScoreGuessesSorted.begin(), moveScoreGuessesSorted.end()) ;

    /*
    for (int k = 0 ; k < legalMoves.size() ; k++){
        cout << moveScoreGuessesSorted[k] << endl;
    }
    */

    //cout << "e";



    for (int indSorted = 0 ; indSorted < legalMoves.size() ; indSorted ++){
        for (int indLegal = 0 ; indLegal < legalMoves.size() ; indLegal++){
            //cout << "moveScoreGuesses["<<indLegal<<"] " << moveScoreGuesses[indLegal] ;
            //cout << "moveScoreGuessesSorted["<<indSorted<<"] " << moveScoreGuessesSorted[indSorted]<< endl;
            if (moveScoreGuesses[indLegal] == moveScoreGuessesSorted[indSorted]){ // si le move correspond � la k-i�me valeur
                //cout << "in first if" << endl ;
                if (!(count(sortedLegal.begin(), sortedLegal.end(), legalMoves[indLegal]))){ // si le move n'est pas dans sorted legal
                    //cout << "adding move";
                    sortedLegal.push_back(legalMoves[indLegal]) ;
                }
            }
        }
    }


        //On peut prioriser les promotions

        //On peut �viter les cases controll�es par des pions

        //cout << "sortedLegal.size() = " << sortedLegal.size() << endl;

        /*
        for (int k = 0 ; k < sortedLegal.size() ; k++){
            cout << sortedLegal[k].first << sortedLegal[k].second.first << sortedLegal[k].second.second << endl;
        }
        */

        return sortedLegal ;
}


vector<pair<string, pair<int, int>>> LegalMoves(string aBoard[8][8], int moveNb){//, bool wC1, bool wC2, bool bC1, bool bC2){

    vector<pair<string, pair<int, int>>> legalMoves ;
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    string pieces[32] = {"wP1","wP2","wP3","wP4","wP5","wP6","wP7","wP8",
                         "wR1","wN1","wB1","wK","wQ","wB2","wN2","wR2",
                         "bP1","bP2","bP3","bP4","bP5","bP6","bP7","bP8",
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
    return sortLegal(legalMoves, aBoard);
    //return legalMoves;
}

vector<pair<string, pair<int, int>>> unSortedLegalMoves(string aBoard[8][8], int moveNb){//, bool wC1, bool wC2, bool bC1, bool bC2){

    vector<pair<string, pair<int, int>>> legalMoves ;
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    string pieces[32] = {"wP1","wP2","wP3","wP4","wP5","wP6","wP7","wP8",
                         "wR1","wN1","wB1","wK","wQ","wB2","wN2","wR2",
                         "bP1","bP2","bP3","bP4","bP5","bP6","bP7","bP8",
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
    //return sortLegal(legalMoves, aBoard);
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

int getPieceValue(char label){
    switch (label)
    {

    case 'Q' :
        return 900 ;
        break ;

    case 'R' :
        return 500 ;
        break ;

    case 'B' :
        return 300 ;
        break ;

    case 'N' :
        return 300 ;
        break ;

    case 'P' :
        return 100 ;
        break ;

    }
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
        cout << "illegal move *" <<endl;
        sleep(2);
        return false;
    }



    return true;

}


