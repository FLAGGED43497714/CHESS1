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

/*void ajouteDeuxRef(bool &a){
    a = false ;
}*/

int main()
{
    bool whiteHuman (false);
    bool blackHuman = 1 - whiteHuman;

    int moveNb = 0 ;
    string board[8][8] ;

    //string fen = "r2qk2r/ppp2pRp/5n2/2b5/2p1P3/N1P2P1b/PP3P1P/R1B1K3" ;
    //string fen = "rnb2rk1/pppp1ppp/5q2/1B2p3/1b2P3/2NP1N2/PPP2PPP/R2QK2R" ;
    //string fen = "rnbqk1nr/ppp1bppp/8/3pp3/8/2P5/PN1PPPPP/R1BQKBNR";
    //string fen = "r2qkbnr/ppp2ppp/2n1p3/3p1b2/2BP4/4P3/PPPB1PPP/RN1QK1NR" ;
    //string fen = "r4r2/ppp2pk1/8/8/P3q3/1P3nPP/2p2bR1/7K" ;
    //string fen = "r1bqkb1r/ppp1nppp/8/1B1P3Q/3n4/8/PPPP1PPP/RNB1K1NR" ;
    //string fen = "r1bqkbnr/pppp1ppp/8/4n3/4P3/8/PPP2PPP/RNBQKBNR";

    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" ;


    initFenBoard(board, fen);
    coutBoard(board);

    bool wC1 = true ;
    bool wC2 = true ;
    bool bC1 = true ;
    bool bC2 = true ;

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

            double boardEval = eval(board,moveNb, wC1, wC2, bC1, bC2);
            cout << "eval t0 : " << boardEval/100 << endl;

            //turn
            if (moveNb % 2 == 0){cout << "White";} else {cout << "Black";} cout << " to play" << endl ;

            if (moveNb % 2 == 0){
                //theBestMove = bestMove(legalMoves,board,moveNb);

                if(!whiteHuman){
                //auto start = high_resolution_clock::now();
                theBestMove = bestMove5(board,moveNb,wC1, wC2, bC1, bC2,2);
                //auto stop = high_resolution_clock::now();
                //auto duration = duration_cast<milliseconds>(stop - start);
                //cout << duration.count() << endl;
                //sleep(3);

                nextPiece = theBestMove.first ;
                nextLine = theBestMove.second.first;
                nextCol = theBestMove.second.second;

                isLegal = true ;
                } else {





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

                isLegal = IsLegal(nextPiece, nextDest, board, moveNb, wC1, wC2, bC2, bC2) ;
                }






            } else {
                //black turn, computer plays
                //legalMoves = LegalMoves(board, moveNb) ;
                /*int randint = rand() % legalMoves.size();
                nextPiece = legalMoves[randint].first ;
                nextLine = legalMoves[randint].second.first ;
                nextCol = legalMoves[randint].second.second ;
                */
                //theBestMove = bestMove(legalMoves,board,moveNb);


                if (!blackHuman){
                //auto start = high_resolution_clock::now();
                theBestMove = bestMove5(board, moveNb, wC1, wC2, bC1, bC2, 2);
                //auto stop = high_resolution_clock::now();
                //auto duration = duration_cast<milliseconds>(stop - start);
                //cout << duration.count() << endl;
                //sleep(3);
                nextPiece = theBestMove.first ;
                nextLine = theBestMove.second.first;
                nextCol = theBestMove.second.second;

                isLegal = true;
                }
                else {

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

                isLegal = IsLegal(nextPiece, nextDest, board, moveNb,wC1, wC2, bC1, bC2) ;
                }







            }


        }
        if (moveNb % 2 == 0) {
            if (whiteHuman){
                updateBoard1(nextPiece,nextDest, board);
            } else {
                updateBoard2(nextPiece, nextLine, nextCol, board) ;
            }
        } else {
            if (blackHuman){
                updateBoard1(nextPiece,nextDest, board);
            } else {
                updateBoard2(nextPiece, nextLine, nextCol, board) ;
            }
        }
        system("cls");
        coutBoard(board);
        //sleep(10);
        moveNb++;

        }

 return 0;
}
