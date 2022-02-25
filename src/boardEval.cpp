#include "boardEval.h"
#include "UpdateBoard.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;


double evalPieces(string aBoard[8][8])
{
    double eval (0);
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            switch(aBoard[i][j][1])
            {
                case 'P' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 10 ;
                    } else {
                        eval -= 10 ;
                    }
                    break;

                case 'N' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 30 ;
                    } else {
                        eval -= 30 ;
                    }
                    break;

                case 'B' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 30 ;
                    } else {
                        eval -= 30 ;
                    }
                    break;

                case 'R' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 50 ;
                    } else {
                        eval -= 50 ;
                    }
                    break;

                case 'Q' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 90 ;
                    } else {
                        eval -= 90 ;
                    }
                    break;

                case 'K' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 1000 ;
                    } else {
                        eval -= 1000 ;
                    }
                    break;
            }
        }
    }

    return eval;
}



double eval(string aBoard[8][8],int moveNb)
{
    double theEval (0);

    theEval = evalPieces(aBoard);

    return theEval ;

}

pair<string, pair<int, int>> bestMove(vector<pair<string, pair<int, int>>> legalMoves,string aBoard[8][8],int moveNb){
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    pair<string, pair<int, int>> bestMove ;

    string possibleBoard[8][8];
    double currentEval ;

    double bestEval = -9000.5 ;
    if (!isWhiteTurn){
        bestEval = 9000.5 ;
    }

    for (int k = 0 ; k < legalMoves.size() ; k++){
        for (int i=0; i < 8 ; i++){
            for (int j=0; j < 8 ; j++){
                possibleBoard[i][j] = aBoard[i][j] ;
            }
        }
        updateBoard2(legalMoves[k].first,legalMoves[k].second.first,legalMoves[k].second.second,possibleBoard);
        currentEval = eval(possibleBoard,moveNb) ;
        if (isWhiteTurn){
            if (currentEval > bestEval){
                bestMove = legalMoves[k] ;
                bestEval = currentEval ;
            }
        } else {
            if (currentEval < bestEval){
                bestMove = legalMoves[k] ;
                bestEval = currentEval ;
            }
        }
    }
    return bestMove ;
}
