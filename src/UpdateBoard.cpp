#include "UpdateBoard.h"
#include <string>
#include <cstring>
#include <cstdlib>

#include "MoveInstructions.h"
#include "iostream"
#include "unistd.h"


using namespace std;


void movePiece(int destInd1,int destInd2, int oldInd1, int oldInd2, string aBoard[8][8]){
    //cout << "moving" << endl;
    aBoard[destInd1][destInd2] = aBoard[oldInd1][oldInd2] ;
    aBoard[oldInd1][oldInd2] = "*";



}


void updateBoard1(string nextPiece,string nextDest,string aBoard[8][8]){

    /*if (nextPiece == "O-O"){
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
    } else {*/

    //find next dest indexes
    int line_index ;
    int col_index ;
    pair<int, int> destLoc ;
    destLoc = dest_conv(nextDest);

    //find piece position (and indexes)
    //pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;
    updateBoard2(nextPiece, destLoc.first, destLoc.second, aBoard) ;
    //movePiece(destLoc.first, destLoc.second, pieceLoc.first, pieceLoc.second, aBoard);
    //}}}}
}

void updateBoard2(string nextPiece, int line_index, int col_index, string aBoard[8][8]){
    //cout << nextPiece << line_index << col_index << endl ;
    //sleep(2);
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
    } else {

    if ((line_index == 0) && (nextPiece[0] == 'w') && (nextPiece[1] == 'P')){
        //cout << "in promotion" << endl ;
        //sleep(0.75) ;
        int randNb = rand() % 100 ;
        aBoard[0][col_index] = "wQ" + to_string(randNb) ;
        aBoard[1][col_index] = "*" ;
    } else {

    if ((line_index == 7) && (nextPiece[0] == 'b') && (nextPiece[1] == 'P')){
        int randNb = rand() % 100 ;
        aBoard[6][col_index] = "*" ;
        aBoard[7][col_index] = "bQ" + to_string(randNb) ;
    } else {


        //cout << "in else for "<< nextPiece <<line_index << col_index ;
        //string nothing ;
        //cin >> nothing;
        //find piece position (and indexes)
        pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;

        movePiece(line_index, col_index, pieceLoc.first, pieceLoc.second, aBoard);
    }}}}}}
}
