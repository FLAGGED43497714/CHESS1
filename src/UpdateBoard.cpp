#include "UpdateBoard.h"
#include <string>
#include <cstring>
#include "MoveInstructions.h"

using namespace std;


void movePiece(int destInd1,int destInd2, int oldInd1, int oldInd2, string aBoard[8][8]){
    aBoard[destInd1][destInd2] = aBoard[oldInd1][oldInd2] ;
    aBoard[oldInd1][oldInd2] = "*";



}


void updateBoard1(string nextPiece,string nextDest,string aBoard[8][8]){

    //find next dest indexes
    int line_index ;
    int col_index ;
    pair<int, int> destLoc ;
    destLoc = dest_conv(nextDest);

    //find piece position (and indexes)
    pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;


    movePiece(destLoc.first, destLoc.second, pieceLoc.first, pieceLoc.second, aBoard);

}

void updateBoard2(string nextPiece, int line_index, int col_index, string aBoard[8][8]){

    //find piece position (and indexes)
    pair<int, int> pieceLoc = findPiece(nextPiece, aBoard) ;


    movePiece(line_index, col_index, pieceLoc.first, pieceLoc.second, aBoard);
}
