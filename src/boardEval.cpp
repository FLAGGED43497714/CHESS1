#include "boardEval.h"
#include "UpdateBoard.h"
#include "legal.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <cmath>

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

const double KnightSqTbW[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-20,-30,-30,-20,-40,-50}
};

const double KnightSqTbB[8][8] =
{
    {-50,-40,-20,-30,-30,-20,-40,-50},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
};

const double BishopSqTbW[8][8] =
{
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-40,-10,-10,-40,-10,-20}
};

const double BishopSqTbB[8][8] =
{
    {-20,-10,-40,-10,-10,-40,-10,-20},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}


};

const double KingSqTbW[8][8] =
{
  {-30, -40, -40, -50, -50, -40, -40, -30},
  {-30, -40, -40, -50, -50, -40, -40, -30},
  {-30, -40, -40, -50, -50, -40, -40, -30},
  {-30, -40, -40, -50, -50, -40, -40, -30},
  {-20, -30, -30, -40, -40, -30, -30, -20},
  {-10, -20, -20, -20, -20, -20, -20, -10},
   {20,  20,   0,   0,   0,   0,  20,  20},
   {20,  30,  10,   0,   0,  10,  30,  20}
};

const double KingSqTbB[8][8] =
{
{20,  30,  10,   0,   0,  10,  30,  20},
{20,  20,   0,   0,   0,   0,  20,  20},
{-10, -20, -20, -20, -20, -20, -20, -10},
{-20, -30, -30, -40, -40, -30, -30, -20},
{-30, -40, -40, -50, -50, -40, -40, -30},
{-30, -40, -40, -50, -50, -40, -40, -30},
{-30, -40, -40, -50, -50, -40, -40, -30},
{-30, -40, -40, -50, -50, -40, -40, -30}
};



bool isBetter(double eval1, double eval2, int moveNb){
    bool isWhiteTurn = (moveNb % 2 == 0) ;
    if (isWhiteTurn){
        return eval1 > eval2 ;
    } else {
        return eval1 < eval2 ;
    }

}

double evalMated(string aBoard[8][8],int moveNb){
    bool isWhiteTurn = (moveNb % 2 == 0) ; //not white turn
    vector<pair<string, pair<int, int>>> legalMovesPlayer ;
    vector<pair<string, pair<int, int>>> legalMovesWatcher ;
    legalMovesPlayer = LegalMoves(aBoard,moveNb) ;
    legalMovesWatcher = LegalMoves(aBoard,moveNb+1) ; //ke1 kf1

    if (legalMovesPlayer.size() == 0){
        cout << "I see player in mate  !" << endl ;
        sleep(1.5);
        if (isWhiteTurn){
            return -90000 ;
        } else {
            return 90000 ;
        }
    }
    return 0 ;
}

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
    //bool isWhiteTurn = (moveNb % 2 == 0) ;
    double eval (0) ;

    for (int i=0 ; i < 8 ; i ++)
    {
        for (int j=0 ; j < 8 ; j ++)
        {
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
                    if (aBoard[i][j][0] == 'w'){
                        eval += KnightSqTbW[i][j] ;
                    } else {
                        eval -= KnightSqTbB[i][j] ;
                    }
                    break;

                case 'B' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += BishopSqTbW[i][j] ;
                    } else {
                        eval -= BishopSqTbB[i][j] ;
                    }
                    break;

                case 'R' :
                    eval += 0;
                    break;

                case 'Q' :
                    eval += 0;
                    break;

                case 'K' :
                    if (aBoard[i][j][0] == 'w'){
                        eval += BishopSqTbW[i][j] ;
                    } else {
                        eval -= BishopSqTbB[i][j] ;
                    }
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
    double evalMate = evalMated(aBoard,moveNb) ;

    theEval += evalMate ;
    theEval = floor(theEval);

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


pair<string, pair<int, int>> bestMove2(string aBoard[8][8],int moveNb){
    vector<pair<string, pair<int, int>>> legalMovest0 ;
    vector<pair<string, pair<int, int>>> legalMovest1 ;
    vector<pair<int, double>> evals1 ;

    legalMovest0 = LegalMoves(aBoard,moveNb);
    double evals0[legalMovest0.size()] ;
    for (int k = 0 ; k < legalMovest0.size() ; k++){
        evals0[k] = (2 * (moveNb % 2 == 0) - 1) * 9000 ;
    }

    bool isWhiteTurn = (moveNb % 2 == 0) ;
    pair<string, pair<int, int>> bestMove ;

    string possibleBoardt1[8][8];
    string possibleBoardt2[8][8];


    pair<int,double> currentEvalsAndMove ;
    double currentEval ;

    for (int k = 0 ; k < legalMovest0.size() ; k++){
        for (int i=0; i < 8 ; i++){
            for (int j=0; j < 8 ; j++){
                possibleBoardt1[i][j] = aBoard[i][j] ;
            }
        }
        //new Board
        updateBoard2(legalMovest0[k].first,legalMovest0[k].second.first,legalMovest0[k].second.second,possibleBoardt1);
        //new Moves
        legalMovest1 = LegalMoves(possibleBoardt1,moveNb+1);
        //init new board
        //cout << "for move : " << legalMovest0[k].first << legalMovest0[k].second.first << legalMovest0[k].second.second << endl ;
        //cout << "legalMovess1 size :" << legalMovest1.size() << endl;

        if (legalMovest1.size() == 0){
            //cout << "can mate" << endl;
            //sleep(10) ;
            currentEvalsAndMove.first = k ;
            currentEvalsAndMove.second = (((moveNb) % 2 == 1)*2 - 1) * -9000 ;
            evals1.push_back(currentEvalsAndMove);
        }

        for (int kk = 0 ; kk < legalMovest1.size() ; kk++){

            //cout << "moves are : " << legalMovest1[kk].first ;
            //cout << legalMovest1[kk].second.first << legalMovest1[kk].second.second << endl;

            for (int ii=0; ii < 8 ; ii++){
                for (int jj=0; jj < 8 ; jj++){
                    possibleBoardt2[ii][jj] = possibleBoardt1[ii][jj] ;
                }
            }
            updateBoard2(legalMovest1[kk].first,legalMovest1[kk].second.first,legalMovest1[kk].second.second,possibleBoardt2);
            currentEval = eval(possibleBoardt2,moveNb+1) ;
            currentEvalsAndMove.first = k ;
            currentEvalsAndMove.second = currentEval ;
            evals1.push_back(currentEvalsAndMove);
        }

    }
    //sleep(300);
    for (int k = 0 ; k < legalMovest0.size() ; k++){
        for (int u = 0 ; u < evals1.size() ; u++){
            if ((evals1[u].first == k) && (isBetter(evals1[u].second,evals0[k], moveNb+1))){
                evals0[k] = evals1[u].second;
            }
        }
    }

    currentEval = evals0[0] ;
    bestMove = legalMovest0[0];
    for (int k = 1 ; k < legalMovest0.size() ; k++){
        if (isBetter(evals0[k],currentEval,moveNb)){
            bestMove = legalMovest0[k] ;
            currentEval = evals0[k];
        }
    }
    return bestMove ;
}
