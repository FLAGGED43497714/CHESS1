#include <iostream>
#include <string>
#include <coutBoard.h>
#include <initboard.h>
#include <UpdateBoard.h>
#include <legal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <chrono>


//pour test
#include "boardEval.h"
#include "Check.h"
#include <MoveInstructions.h>

//using namespace std::chrono ;

using namespace std;

int main()
{
    int moveNb = 0 ;
    string board[8][8] ;

    string fen = "rnbqkb1r/ppp1pppp/5n2/3p4/3P4/2N5/PPP1PPPP/R1BQKBNR" ;
    //string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;
    initFenBoard(board, fen);
    coutBoard(board);

    string nextPiece ;
    string nextDest ;

    int nextLine ;
    int nextCol ;

    //bool isWhiteTurn(moveNb % 2 == 0) ;

    string possibleBoard[8][8];
    vector<pair<string, pair<int, int>>> legalMoves;
    pair<string, pair<int, int>> theBestMove ;

    while(true){
        //string nothing ;
        //cin >> nothing ;
        bool isLegal (false);

        bool isCheck = IsCheck(board,moveNb) ;
        //cout << "Is check : " << isCheck << endl ;
        //sleep(0.5) ;

        while(!isLegal){
            //update board on console
            system("cls");
            coutBoard(board);

            double boardEval = eval(board,moveNb);
            cout << "eval : " << boardEval/100 << endl;

            //turn
            if (moveNb % 2 == 0){cout << "White";} else {cout << "Black";} cout << " to play" << endl ;

            if (moveNb % 2 == 0){
                //theBestMove = bestMove(legalMoves,board,moveNb);


                //auto start = high_resolution_clock::now();
                theBestMove = bestMove4(board,moveNb,2);
                //auto stop = high_resolution_clock::now();
                //auto duration = duration_cast<milliseconds>(stop - start);
                //cout << duration.count() << endl;
                //sleep(3);
                nextPiece = theBestMove.first ;
                nextLine = theBestMove.second.first;
                nextCol = theBestMove.second.second;

                isLegal = true ;


                /*
                //next move

                cout << "next piece ? " ;
                cin >> nextPiece;
                cin.ignore();

                //pos of next piece
                pair<int,int> pLoc ;
                pLoc = findPiece(nextPiece,board);
                cout << pLoc.first << endl;
                cout << pLoc.second << endl;

                //ask dest
                cout << "Destination ? " ;
                cin >> nextDest;
                cin.ignore();

                isLegal = IsLegal(nextPiece, nextDest, board, moveNb) ;
                */
            } else {
                //black turn, computer plays
                legalMoves = LegalMoves(board, moveNb) ;
                /*int randint = rand() % legalMoves.size();
                nextPiece = legalMoves[randint].first ;
                nextLine = legalMoves[randint].second.first ;
                nextCol = legalMoves[randint].second.second ;
                */
                //theBestMove = bestMove(legalMoves,board,moveNb);

                /*
                theBestMove = bestMove4(board,moveNb,3);
                nextPiece = theBestMove.first ;
                nextLine = theBestMove.second.first;
                nextCol = theBestMove.second.second;

                isLegal = true;
                */

                //next move

                cout << "next piece ? " ;
                cin >> nextPiece;
                cin.ignore();

                //pos of next piece
                pair<int,int> pLoc ;
                pLoc = findPiece(nextPiece,board);
                cout << pLoc.first << endl;
                cout << pLoc.second << endl;

                //ask dest
                cout << "Destination ? " ;
                cin >> nextDest;
                cin.ignore();

                isLegal = IsLegal(nextPiece, nextDest, board, moveNb) ;


            }


        }
        if (moveNb % 2 == 0) {
            //create a parallel board to test a move
            //updateBoard1(nextPiece,nextDest, board);
            updateBoard2(nextPiece, nextLine, nextCol, board) ;
        } else {
            //possible moves
            /*
            for (int k=0 ; k < legalMoves.size() ; k++){
                for (int i=0; i < 8 ; i++){
                    for (int j=0; j < 8 ; j++){
                        possibleBoard[i][j] = board[i][j] ;
                    }
                }
                system("cls");
                updateBoard2(legalMoves[k].first,legalMoves[k].second.first,legalMoves[k].second.second,possibleBoard);
                coutBoard(possibleBoard) ;
                sleep(0.5);
            }
            */
            updateBoard1(nextPiece,nextDest, board);
            //updateBoard2(nextPiece, nextLine, nextCol, board) ;
        }
        system("cls");
        coutBoard(board);
        moveNb++;

        }

 return 0;
}
