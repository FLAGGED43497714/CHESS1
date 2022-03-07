#include "UpdateBoard.h"
#include <string>
#include <cstring>
#include "MoveInstructions.h"
#include "iostream"
using namespace std;


void movePiece(int destInd1,int destInd2, int oldInd1, int oldInd2, string aBoard[8][8]){
    //cout << "moving" << endl;
    aBoard[destInd1][destInd2] = aBoard[oldInd1][oldInd2] ;
    aBoard[oldInd1][oldInd2] = "*";



}


void updateBoard1(string nextPiece,string nextDest,string aBoard[8][8]){

    if (nextPiece == "O-O"){
        cout << "found it" << endl;
        updateBoard2("wK",7,6,aBoard) ;
        updateBoard2("wR2", 7, 5, aBoard) ;
        cout << "done it" << endl;
    } else {
    if (nextPiece == "O-O-O"){
        updateBoard2("wK",7,2,aBoard) ;
        updateBoard2("wR1", 7, 3, aBoard) ;
    } else {
    if (nextPiece == "o-o"){
        updateBoard2("bK",0,6,aBoard) ;
        updateBoard2("bR2", 0, 5, aBoard) ;
    } else {
    if (nextPiece == "o-o-o"){
        updateBoard2("wK",0,2,aBoard) ;
        updateBoard2("wR1", 0, 3, aBoard) ;
    } else {

    //find next dest indexes
    int line_index ;
    int col_index ;
    pair<int, int> destLoc ;
    destLoc = dest_conv(nextDest);

    //find piece position (and indexes)
    pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;

    movePiece(destLoc.first, destLoc.second, pieceLoc.first, pieceLoc.second, aBoard);
    }}}}

}

void updateBoard2(string nextPiece, int line_index, int col_index, string aBoard[8][8]){
    //cout << nextPiece << endl;

    if (nextPiece == "O-O"){
        //cout << "found it" << endl ;
        updateBoard2("wK",7,6,aBoard) ;
        updateBoard2("wR2", 7, 5, aBoard) ;
        //cout << "done it" << endl ;
    } else {
    if (nextPiece == "O-O-O"){
        updateBoard2("wK",7,2,aBoard) ;
        updateBoard2("wR1", 7, 3, aBoard) ;
    } else {
    if (nextPiece == "o-o"){
        updateBoard2("bK",0,6,aBoard) ;
        updateBoard2("bR2", 0, 5, aBoard) ;
    } else {
    if (nextPiece == "o-o-o"){
        updateBoard2("bK",0,2,aBoard) ;
        updateBoard2("bR1", 0, 3, aBoard) ;
    }
    else {
        //cout << "in else for "<< nextPiece <<line_index << col_index ;
        //string nothing ;
        //cin >> nothing;
        //find piece position (and indexes)
        pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;

        movePiece(line_index, col_index, pieceLoc.first, pieceLoc.second, aBoard);
    }}}}
}
