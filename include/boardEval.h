#ifndef BOARDEVAL_H
#define BOARDEVAL_H

#include <string>
#include <vector>

double eval(std::string aBoard[8][8],int moveNb);

std::pair<std::string, std::pair<int, int>> bestMove(std::vector<std::pair<std::string, std::pair<int, int>>> legalMoves,std::string aBoard[8][8],int moveNb);

std::pair<std::string, std::pair<int, int>> bestMove2(std::string aBoard[8][8],int moveNb);

std::pair<std::string, std::pair<int, int>> bestMove3(std::string aBoard[8][8],int moveNb, int maxIter);

#endif // BOARDEVAL_H
