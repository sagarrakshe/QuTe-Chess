#include "validation.h"
int i;
int Do_W_castling=0;
int Do_B_castling=0;
int Do_NQ_castling=0;

int zero=0;
validation::validation()
{
    //Nothing here
}

int validation::chooser(Tile *temp)
{
    switch(temp->pieceName)
    {
    case 'P': flag=validatePawn(temp);
              break;

    case 'R': flag=validateRook(temp);
              break;

    case 'H': flag=validateHorse(temp);
              break;

    case 'K': flag=validateKing(temp);
              break;

    case 'Q': flag=validateQueen(temp);
              break;

    case 'B': flag=validateBishop(temp);
              break;

    }


    return flag;
}

//PAWN
int validation::validatePawn(Tile *temp)
{
    int row,col;

    row=temp->row;
    col=temp->col;
    retVal=0;

    //White Pawn
    if(temp->pieceColor)
    {
        if(row-1>=0 && !tile[row-1][col]->piece)
        {
            exp[max++]=tile[row-1][col]->tileNum;
            retVal=1;
        }

        if(row==6 && !tile[5][col]->piece && !tile[4][col]->piece)
        {
            exp[max++]=tile[row-2][col]->tileNum;
            retVal=1;
        }

        if(row-1>=0 && col-1>=0)
        {
            if(tile[row-1][col-1]->pieceColor!=temp->pieceColor && tile[row-1][col-1]->piece)
            {
            exp[max++]=tile[row-1][col-1]->tileNum;
            retVal=1;
            }
        }

        if(row-1>=0 && col+1<=7)
        {
            if(tile[row-1][col+1]->pieceColor!=temp->pieceColor && tile[row-1][col+1]->piece)
            {
                exp[max++]=tile[row-1][col+1]->tileNum;
                retVal=1;
            }
        }
    }
    else
    {
        if(row+1<=7 && !tile[row+1][col]->piece)
        {
            exp[max++]=tile[row+1][col]->tileNum;
            retVal=1;
        }

        if(row==1 && !tile[2][col]->piece && !tile[3][col]->piece)
        {
            exp[max++]=tile[row+2][col]->tileNum;
            retVal=1;
        }

        if(row+1<=7 && col-1>=0)
        {
            if(tile[row+1][col-1]->pieceColor!=temp->pieceColor && tile[row+1][col-1]->piece)
            {
                exp[max++]=tile[row+1][col-1]->tileNum;
                retVal=1;
            }
        }

        if(row+1<=7 && col+1<=7)
        {
            if(tile[row+1][col+1]->pieceColor!=temp->pieceColor && tile[row+1][col+1]->piece)
            {
                exp[max++]=tile[row+1][col+1]->tileNum;
                retVal=1;
            }
        }
    }

    return retVal;
}


//ROOK
int validation::validateRook(Tile *temp)
{
    int r,c;

    retVal=0;

    r=temp->row;
    c=temp->col;
    while(r-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }


    return retVal;
}


//HORSE
int validation::validateHorse(Tile *temp)
{
    int r,c;
    retVal=0;

    r=temp->row;
    c=temp->col;

    if(r-2>=0 && c-1>=0)
    {
        if(tile[r-2][c-1]->pieceColor!=temp->pieceColor || !tile[r-2][c-1]->piece)
        {
            exp[max++]=tile[r-2][c-1]->tileNum;
            retVal=1;
        }
    }

    if(r-2>=0 && c+1<=7)
    {
        if(tile[r-2][c+1]->pieceColor!=temp->pieceColor || !tile[r-2][c+1]->piece)
        {
            exp[max++]=tile[r-2][c+1]->tileNum;
            retVal=1;
        }
    }

    if(r-1>=0 && c-2>=0)
    {
        if(tile[r-1][c-2]->pieceColor!=temp->pieceColor || !tile[r-1][c-2]->piece)
        {
            exp[max++]=tile[r-1][c-2]->tileNum;
            retVal=1;
        }
    }

    if(r-1>=0 && c+2<=7)
    {
        if(tile[r-1][c+2]->pieceColor!=temp->pieceColor || !tile[r-1][c+2]->piece)
        {
            exp[max++]=tile[r-1][c+2]->tileNum;
            retVal=1;
        }
    }

    if(r+2<=7 && c+1<=7)
    {
        if(tile[r+2][c+1]->pieceColor!=temp->pieceColor || !tile[r+2][c+1]->piece)
        {
            exp[max++]=tile[r+2][c+1]->tileNum;
            retVal=1;
        }
    }

    if(r+2<=7 && c-1>=0)
    {
        if(tile[r+2][c-1]->pieceColor!=temp->pieceColor || !tile[r+2][c-1]->piece)
        {
            exp[max++]=tile[r+2][c-1]->tileNum;
            retVal=1;
        }
    }

    if(r+1<=7 && c-2>=0)
    {
        if(tile[r+1][c-2]->pieceColor!=temp->pieceColor || !tile[r+1][c-2]->piece)
        {
            exp[max++]=tile[r+1][c-2]->tileNum;
            retVal=1;
        }
    }

    if(r+1<=7 && c+2<=7)
    {
        if(tile[r+1][c+2]->pieceColor!=temp->pieceColor || !tile[r+1][c+2]->piece)
        {
            exp[max++]=tile[r+1][c+2]->tileNum;
            retVal=1;
        }
    }

    return retVal;
}


//KING
int validation::validateKing(Tile *temp)
{
    int r,c;
    retVal=0;

    r=temp->row;
    c=temp->col;

    if(r-1>=0)

    {
        if(!tile[r-1][c]->piece || tile[r-1][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r-1][c]->tileNum;
            retVal=1;
        }
    }

    if(r+1<=7)
    {
        if(!tile[r+1][c]->piece || tile[r+1][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r+1][c]->tileNum;
            retVal=1;
        }
    }

    if(c-1>=0)
    {
        if(!tile[r][c-1]->piece || tile[r][c-1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c-1]->tileNum;
            retVal=1;
        }
    }

    if(c+1<=7)
    {
        if(!tile[r][c+1]->piece || tile[r][c+1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c+1]->tileNum;
            retVal=1;
        }
    }

    if(r-1>=0 && c-1>=0)
    {
        if(!tile[r-1][c-1]->piece || tile[r-1][c-1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r-1][c-1]->tileNum;
            retVal=1;
        }
    }

    if(r-1>=0 && c+1<=7)
    {
        if(!tile[r-1][c+1]->piece || tile[r-1][c+1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r-1][c+1]->tileNum;
            retVal=1;
        }
    }

    if(r+1<=7 && c-1>=0)
    {
        if(!tile[r+1][c-1]->piece || tile[r+1][c-1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r+1][c-1]->tileNum;
            retVal=1;
        }
    }

    if(r+1<=7 && c+1<=7)
    {
        if(!tile[r+1][c+1]->piece || tile[r+1][c+1]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r+1][c+1]->tileNum;
            retVal=1;
        }
    }
    //castling for white non queenside
    if(temp->pieceColor && temp->tileNum==60 && tile[7][7]->piece && tile[7][7]->pieceColor && tile[7][7]->pieceName=='R' && !tile[7][5]->piece && !tile[7][6]->piece)
    {
        exp[max++]=62;
        Do_W_castling=1;
        Do_NQ_castling=1;
        retVal=1;
    }
    //castling for white queen side
    if(temp->pieceColor && temp->tileNum==60 && tile[7][0]->piece && tile[7][0]->pieceColor && tile[7][0]->pieceName=='R' && !tile[7][1]->piece && !tile[7][2]->piece && !tile[7][3]->piece)
    {
        exp[max++]=58;
        Do_W_castling=1;
        Do_NQ_castling=0;
        retVal=1;
    }
    if(!temp->pieceColor && temp->tileNum==4 && tile[0][7]->piece && !tile[0][7]->pieceColor && tile[0][7]->pieceName=='R' && !tile[0][5]->piece && !tile[0][6]->piece)
    {
        exp[max++]=6;
        Do_B_castling=1;
        Do_W_castling=0;
        Do_NQ_castling=1;
        retVal=1;

    }
    if(!temp->pieceColor && temp->tileNum==4 && tile[0][0]->piece && !tile[0][0]->pieceColor && tile[0][0]->pieceName=='R' && !tile[0][1]->piece && !tile[0][2]->piece && !tile[0][3]->piece)
    {
        exp[max++]=2;
        Do_B_castling=1;
        Do_W_castling=0;
        Do_NQ_castling=0;
        retVal=1;

    }

    return retVal;
}


//QUEEN
int validation::validateQueen(Tile *temp)
{
    int r,c;

    retVal=0;

    r=temp->row;
    c=temp->col;
    while(r-->0)
    {
        if(!tile[r][c]->piece)//if no piece
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r-->0 && c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r-->0 && c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7 && c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7 && c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }


    return retVal;
}

//BISHOP
int validation::validateBishop(Tile *temp)
{
    int r,c;
    retVal=0;

    r=temp->row;
    c=temp->col;
    while(r-->0 && c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r-->0 && c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7 && c++<7)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    r=temp->row;
    c=temp->col;
    while(r++<7 && c-->0)
    {
        if(!tile[r][c]->piece)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
        }

        else if(tile[r][c]->pieceColor==temp->pieceColor)
            break;

        else if(tile[r][c]->pieceColor!=temp->pieceColor)
        {
            exp[max++]=tile[r][c]->tileNum;
            retVal=1;
            break;
        }
    }

    return retVal;
}




//--------------------------------------
//checks if opposite king is in check
int validation :: IsInCheck()
{
    // Find the king
    Tile *temp1 = new Tile();
    int kingrow;
    int kingcol;
    int KtileNum;
    if(turn)    //turn==1 means white
    {
        kingrow=B/8;
        kingcol=B%8;
        temp1=tile[kingrow][kingcol];
        KtileNum=temp1->tileNum;
    }
    else    //turn==0 means black
    {
        kingrow=W/8;
        kingcol=W%8;
        temp1=tile[kingrow][kingcol];
        KtileNum=temp1->tileNum;
    }
    // Run through the current turn player pieces and see if any can take the king
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
                if (tile[Row][Col]->piece != 0)
                {
                        if (tile[Row][Col]->pieceColor ==turn)
                        {
                            zero=0;
                            max=0;
                            while(zero<30)
                                exp[zero++]=0;
                            if(chooser(tile[Row][Col]))
                                {
                                    for(i=0;i<max;i++)
                                    {
                                        if(KtileNum==exp[i])
                                                return 1;
                                    }
                                }
                        }
                }
        }
    }
        return 0;


}

//---------------------------------------
//checks if current king is in check
int validation :: AmIInCheck()
{

    //turn=1 white
    // Find the king
    Tile *temp1 = new Tile();
    int kingrow;
    int kingcol;
    int KtileNum;
    if(!turn)    //turn==1 means white
    {
        kingrow=B/8;
        kingcol=B%8;
        temp1=tile[kingrow][kingcol];
        KtileNum=temp1->tileNum;
    }
    else    //turn==0 means black
    {
        kingrow=W/8;
        kingcol=W%8;
        temp1=tile[kingrow][kingcol];
        KtileNum=temp1->tileNum;
    }
    //run through opps players pieces and check if I'm(turn) is in check
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
                if (tile[Row][Col]->piece != 0)
                {
                        if (tile[Row][Col]->pieceColor !=turn)
                        {
                            zero=0;
                            max=0;
                            while(zero<30)
                               exp[zero++]=0;

                            if(chooser(tile[Row][Col]))
                                {
                                    for(i=0;i<max;i++)
                                    {
                                        if(KtileNum==exp[i])
                                                return 1;
                                    }
                                }
                        }
                }
        }
    }
        return 0;


}
//--------------
int validation::IsGameOver()
{
    Tile *obj=new Tile();
   int is_game_over=0;
   is_game_over=obj->CanMove();
    if(is_game_over)
        return 0;
    else
        return 1;


}
//-----------------------------------------
//Expected Position
void validation::orange()
{
    int i,n;

    for(i=0;i<max;i++)
        tile[exp[i]/8][exp[i]%8]->setStyleSheet("QLabel {background-color: orange;}");
}
