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

using namespace std::chrono ;

using namespace std;

int main()
{
    int moveNb = 0 ;
    string board[8][8] ;

    //string fen = "r1b1kb1r/ppp2ppp/2p5/4N3/4n2q/5PP1/PPPP3P/RNBQK2R";
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;
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
            cout << "eval t0 : " << boardEval/100 << endl;

            //turn
            if (moveNb % 2 == 0){cout << "White";} else {cout << "Black";} cout << " to play" << endl ;

            if (moveNb % 2 == 0){
                //theBestMove = bestMove(legalMoves,board,moveNb);


                auto start = high_resolution_clock::now();
                theBestMove = bestMove5(board,moveNb,2);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << duration.count() << endl;
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
                //legalMoves = LegalMoves(board, moveNb) ;
                /*int randint = rand() % legalMoves.size();
                nextPiece = legalMoves[randint].first ;
                nextLine = legalMoves[randint].second.first ;
                nextCol = legalMoves[randint].second.second ;
                */
                //theBestMove = bestMove(legalMoves,board,moveNb);


                //auto start = high_resolution_clock::now();
                theBestMove = bestMove5(board,moveNb,2);
                //auto stop = high_resolution_clock::now();
                //auto duration = duration_cast<milliseconds>(stop - start);
                //cout << duration.count() << endl;
                //sleep(3);
                nextPiece = theBestMove.first ;
                nextLine = theBestMove.second.first;
                nextCol = theBestMove.second.second;

                isLegal = true;





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
            //updateBoard1(nextPiece,nextDest, board);
            updateBoard2(nextPiece, nextLine, nextCol, board) ;
        } else {
            updateBoard1(nextPiece,nextDest, board);
            //updateBoard2(nextPiece, nextLine, nextCol, board) ;
        }
        system("cls");
        coutBoard(board);
        //sleep(10);
        moveNb++;

        }

 return 0;
}
