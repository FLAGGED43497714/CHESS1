#include "initboard.h"
#include <string>

using namespace std;

typedef string (*pointer_to_arrays)[8];

void initBoard(string aBoard[8][8]){

    for(int i = 0 ; i<8 ; i++)
    {
        if(i == 0){
            aBoard[i][0] = "bR1";
            aBoard[i][1] = "bN1";
            aBoard[i][2] = "bB1";
            aBoard[i][3] = "bQ";
            aBoard[i][4] = "bK";
            aBoard[i][5] = "bB2";
            aBoard[i][6] = "bN2";
            aBoard[i][7] = "bR2";
        } else {
        if(i == 1){
            for(int j = 0 ; j<8 ; j++)
            {
                aBoard[i][j] = "bP"+to_string(j);
            }
        } else {
        if(i == 6){
            for(int j = 0 ; j<8 ; j++)
            {
                aBoard[i][j] = "wP"+to_string(j);
            }
        } else {
        if(i == 7){
            aBoard[i][0] = "wR1";
            aBoard[i][1] = "wN1";
            aBoard[i][2] = "wB1";
            aBoard[i][3] = "wQ";
            aBoard[i][4] = "wK";
            aBoard[i][5] = "wB2";
            aBoard[i][6] = "wN2";
            aBoard[i][7] = "wR2";
        } else {

            for(int j = 0 ; j<8 ; j++)
            {
                aBoard[i][j] = "*";
            }
        }
        }
        }
        }

    }
}
