#include "boardEval.h"
#include "UpdateBoard.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

const double PawnSqTbW[8][8] = {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5,  5, 10, 27, 27, 10,  5,  5},
    {0,  0,  0, 25, 25,  0,  0,  0},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {5, 10, 10,-25,-25, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}
    };

const double PawnSqTbB[8][8] = {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {5, 10, 10,-25,-25, 10, 10,  5},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {0,  0,  0, 25, 25,  0,  0,  0},
    {5,  5, 10, 27, 27, 10,  5,  5},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {0,  0,  0,  0,  0,  0,  0,  0},

};



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
                        eval += 100 ;
                    } else {
                        eval -= 100 ;
                    }
                    break;

                case 'N' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 300 ;
                    } else {
                        eval -= 300 ;
                    }
                    break;

                case 'B' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 300 ;
                    } else {
                        eval -= 300 ;
                    }
                    break;

                case 'R' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 500 ;
                    } else {
                        eval -= 500 ;
                    }
                    break;

                case 'Q' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 900 ;
                    } else {
                        eval -= 900 ;
                    }
                    break;

                case 'K' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += 10000 ;
                    } else {
                        eval -= 10000 ;
                    }
                    break;
            }
        }
    }

    return eval;
}

double EvalSqPcTable(string aBoard[8][8], int moveNb){
    //cout << "exec EvalSqPcTable" << endl;
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    double eval (0) ;

    for (int i=0 ; i < 8 ; i ++)
    {
        for (int j=0 ; j < 8 ; j ++)
        {
            //cout << "treating a " << aBoard[i][j][1] << endl;
            switch(aBoard[i][j][1])
            {
                case 'P' :
                    if (aBoard[i][j][0] == 'w'){
                        //cout << "pawn " << aBoard[i][j] << " add " << PawnSqTbW[i][j] << endl;
                        eval += PawnSqTbW[i][j] ;
                    } else {
                        //cout << "pawn " << aBoard[i][j] << " sub " << PawnSqTbB[i][j] << endl;
                        eval -= PawnSqTbB[i][j] ;
                    }
                    break;

                case 'N' :
                    eval += 0;
                    break;

                case 'B' :
                    eval += 0;
                    break;

                case 'R' :
                    eval += 0;
                    break;

                case 'Q' :
                    eval += 0;
                    break;

                case 'K' :
                    eval += 0;
                    break;
            }
        }
    }
    return eval ;
}




double eval(string aBoard[8][8],int moveNb)
{
    double theEval (0);

    theEval = evalPieces(aBoard);
    //cout << "piece eval is " << theEval << endl;
    double evalSqPcTable = EvalSqPcTable(aBoard,moveNb) ;
    //cout << "square table eval is " << evalSqPcTable << endl;
    theEval += evalSqPcTable ;
    //cout << "total eval is " << theEval << endl;

    return theEval ;

}

pair<string, pair<int, int>> bestMove(vector<pair<string, pair<int, int>>> legalMoves,string aBoard[8][8],int moveNb){
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    pair<string, pair<int, int>> bestMove ;

    string possibleBoard[8][8];
    double currentEval ;

    double bestEval = -90000.5 ;
    if (!isWhiteTurn){
        bestEval = 90000.5 ;
    }

    for (int k = 0 ; k < legalMoves.size() ; k++){
        for (int i=0; i < 8 ; i++){
            for (int j=0; j < 8 ; j++){
                possibleBoard[i][j] = aBoard[i][j] ;
            }
        }
        updateBoard2(legalMoves[k].first,legalMoves[k].second.first,legalMoves[k].second.second,possibleBoard);
        currentEval = eval(possibleBoard,moveNb) ;
        //cout << "move " << legalMoves[k].first << legalMoves[k].second.first << legalMoves[k].second.second ;
        //cout << " gives eval : " << currentEval << endl ;
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
    //sleep(10);
    return bestMove ;
}
