#ifndef VALIDATION_H
#define VALIDATION_H
#include "tile.h"

extern Tile *tile[8][8];
extern int exp[60],max,turn;
extern int W,B;

class validation
{
    int flag,retVal;
   public:
    int Do_W_castling;
    int Do_B_castling;
    int Do_NQ_castling;


public:
    validation();
    int chooser(Tile *temp);
    int validateBishop(Tile *temp);
    int validateQueen(Tile *temp);
    int validateKing(Tile *temp);
    int validateHorse(Tile *temp);
    int validateRook(Tile *temp);
    int validatePawn(Tile *temp);
    void orange();
    int check();
    int IsInCheck();
    int AmIInCheck();
    int IsGameOver();
};

#endif // VALIDATION_H
