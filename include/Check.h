#ifndef CHECK_H
#define CHECK_H

#include <string>
#include <iostream>

bool IsCheck(std::string aBoard[8][8], int moveNb);

bool MoveChecksAllyKing(std::string aBoard[8][8], int moveNb, std::string thePiece, std::pair<int, int> theDest);



#endif // CHECK_H
