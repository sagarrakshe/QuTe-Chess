#include "tile.h"
#include "validation.h"
 #include <QMessageBox>
#include <QSound>
#include <QDebug>
#include <QListWidget>


validation *valid = new validation();

extern int count,turn,W,B;
extern QWidget *myWidget;
extern Tile *click1;
extern Tile *tile[8][8];
int var;
void validate(Tile *temp,int c);
void disOrange();
extern QListWidget *moves;

void displayMove(Tile *test, Tile *test2);

void Tile::mousePressEvent(QMouseEvent *event)
{
    validate(this,++count);
}

void Tile::display(char elem)
{
    this->pieceName=elem;

    if(this->pieceColor && this->piece)
    {
        switch(elem)
        {
            case 'P': this->setPixmap(QPixmap(":/Images/pawn_white.svg"));
                      break;
            case 'R': this->setPixmap(QPixmap(":/Images/rook_white.svg"));
                      break;
            case 'H': this->setPixmap(QPixmap(":/Images/knight_white.svg"));
                      break;
            case 'K': this->setPixmap(QPixmap(":/Images/king_white.svg"));
                      break;
            case 'Q': this->setPixmap(QPixmap(":/Images/queen_white.svg"));
                      break;
            case 'B': this->setPixmap(QPixmap(":/Images/bishop_white.svg"));
                      break;
        }
    }

    else if(this->piece)
    {
        switch(elem)
        {
        case 'P': this->setPixmap(QPixmap(":/Images/pawn_black.svg"));
                  break;
        case 'R': this->setPixmap(QPixmap(":/Images/rook_black.svg"));
                  break;
        case 'H': this->setPixmap(QPixmap(":/Images/knight_black.svg"));
                  break;
        case 'K': this->setPixmap(QPixmap(":/Images/king_black.svg"));
                  break;
        case 'Q': this->setPixmap(QPixmap(":/Images/queen_black.svg"));
                  break;
        case 'B': this->setPixmap(QPixmap(":/Images/bishop_black.svg"));
                  break;
        }
    }
    else
        this->clear();
}

void validate(Tile *temp, int c)
{
    int restore_color=0;
    int restore_piece=0;
    char restore_pieceName=NULL;
    int retValue,i;
    int last_check=0;
    if(c==1)    //first click
    {
        if(temp->piece && (temp->pieceColor==turn)) //if piece is der and color matches
        {
            //exp[max++]=temp->tileNum;
            retValue=valid->chooser(temp);
             valid->orange();
            if(retValue)
            {
                tile[W/8][W%8]->tileDisplay();
                tile[B/8][B%8]->tileDisplay();

                click1= new Tile();
                temp->setStyleSheet("QLabel {background-color: green;}");
                click1=temp;                
            }
            else
            {
                //temp->setStyleSheet("QLabel {background-color: red;}");
                //not his turn
                count=0;
            }
        }
        else
        {
            //qDebug()<<"Rascel, clicking anywhere";
            count=0;
        }
    }

    else
    {
        restore_piece=temp->piece;
        restore_color=temp->pieceColor;
        restore_pieceName=temp->pieceName;
        //if user clicks on same box second time
        if(temp->tileNum==click1->tileNum)  //click1=temp (prev temp :first click, pointer)
        {
            click1->tileDisplay();
            disOrange();
            max=0;
            count=0;
        }

        for(i=0;i<max;i++)
        {            
            if(temp->tileNum==exp[i])
            {
                disOrange();

                click1->piece=0;    //clears present status of box
                temp->piece=1;       //marks present to new box where piece is moved

                temp->pieceColor=click1->pieceColor;
                temp->pieceName=click1->pieceName;

                click1->display(click1->pieceName);
                temp->display(temp->pieceName);

                click1->tileDisplay();
                temp->tileDisplay();

               max=0;
               var=0;
               //if piece is king then update position of king in W & B Respt.
               if(temp->pieceName=='K' && temp->pieceColor)
               {
                   W=temp->row*8+temp->col;

                   if(valid->Do_W_castling)
                   {
                       if(valid->Do_NQ_castling  && W==62)
                       {
                           tile[7][5]->piece=1;
                           tile[7][5]->pieceColor=1;
                           tile[7][5]->pieceName='R';
                           tile[7][7]->piece=0;
                           tile[7][7]->pieceName=NULL;
                           tile[7][5]->display('R');
                           tile[7][5]->tileDisplay();
                           tile[7][7]->display('R');
                           tile[7][7]->tileDisplay();
                           tile[7][6]->tileDisplay();
                           valid->Do_NQ_castling=0;
                           valid->Do_W_castling=0;
                           //valid->allow_castling=0;
                       }
                       else if(!valid->Do_NQ_castling  && W==58)
                       {
                           tile[7][3]->piece=1;
                           tile[7][3]->pieceColor=1;
                           tile[7][3]->pieceName='R';
                           tile[7][0]->piece=0;
                           tile[7][0]->pieceName=NULL;
                           tile[7][3]->display('R');
                           tile[7][3]->tileDisplay();
                           tile[7][0]->display('R');
                           tile[7][0]->tileDisplay();
                           valid->Do_NQ_castling=0;
                           valid->Do_W_castling=0;
                            //valid->allow_castling=0;
                       }
                   }

               }

               if(temp->pieceName=='K' && !temp->pieceColor)
               {
                   B=temp->row*8+temp->col;

                   if(valid->Do_B_castling)
                   {
                       if(valid->Do_NQ_castling && B==6)
                       {
                           tile[0][5]->piece=1;
                           tile[0][5]->pieceColor=0;
                           tile[0][5]->pieceName='R';
                           tile[0][7]->piece=0;
                           tile[0][7]->pieceName=NULL;
                           tile[0][5]->display('R');
                           tile[0][5]->tileDisplay();
                           tile[0][7]->display('R');
                           tile[0][7]->tileDisplay();
                           tile[0][6]->tileDisplay();

                           valid->Do_NQ_castling=0;
                           valid->Do_B_castling=0;
                           //valid->allow_castling=0;
                       }
                       else if(!valid->Do_NQ_castling && B==2)
                       {
                           tile[0][3]->piece=1;
                           tile[0][3]->pieceColor=0;
                           tile[0][3]->pieceName='R';
                           tile[0][0]->piece=0;
                           tile[0][0]->pieceName=NULL;
                           tile[0][3]->display('R');
                           tile[0][3]->tileDisplay();
                           tile[0][0]->display('R');
                           tile[0][0]->tileDisplay();
                           valid->Do_NQ_castling=0;
                           valid->Do_B_castling=0;

                       }
                   }

               }//check Wheter moving this object causes check to crnt king
               var=valid->AmIInCheck();
               if(var)
               {
                //undo the move
                   if(click1->pieceName=='K' && click1->pieceColor)
                       W=click1->row*8+click1->col;

                   if(click1->pieceName=='K' && !click1->pieceColor)
                       B=click1->row*8+click1->col;

                   click1->piece=1;    //clears present status of box
                   click1->pieceColor=temp->pieceColor;
                   click1->pieceName=temp->pieceName;
                   temp->pieceColor=restore_color;
                   temp->pieceName=restore_pieceName;
                   temp->piece=restore_piece;

                   click1->display(click1->pieceName);
                   temp->display(temp->pieceName);

                   click1->tileDisplay();
                   temp->tileDisplay();

                   max=0;
                   count=0;

               }

               else
               {

               //after moving the object check if opposite king is in check
               var=0;
               var=valid->IsInCheck();

               //---------------------
               if(var)    //displays red block if check
                {
                    if(turn)
                        tile[B/8][B%8]->setStyleSheet("QLabel {background-color: red;}");
                    else
                        tile[W/8][W%8]->setStyleSheet("QLabel {background-color: red;}");
                }
                retValue=0;

                displayMove(click1,temp);
                turn=(turn+1)%2;    //alternate turn               
                //check if game is over
                if(var)
                    last_check=valid->IsGameOver();
                if(last_check)
                {

                    QMessageBox msgBox;

                     if(turn)
                         msgBox.setText("Check and mate Black player Wins");
                     else
                         msgBox.setText("Check and mate White player Wins");

                    msgBox.exec();
                }
                count=0;
                max=0;

                break;

               }

            }
            else
                count=1;
        }
    }


}
int Tile::CanMove()
{

    int i,j;
    int TileNum=0;
    int Copy_exp[30]={0};
    int Copy_max=0;
    int canMove=0;
    int rflag=0;
    int restore_color=0;
    char restore_pieceName=NULL;

    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
                if (tile[Row][Col]->piece != 0)
                {

                    if (tile[Row][Col]->pieceColor ==turn)
                        {
                            max=0;
                           //get the expected move

                           if(valid->chooser(tile[Row][Col]))
                           {
                               for(j=0;j<max;j++)
                                   Copy_exp[j]=exp[j];
                               Copy_max=max;
                               for(i=0;i<Copy_max;i++)
                               {//actually move
                                   TileNum=Copy_exp[i];
                                  // tile[TileNum/8][TileNum%8]=tile[Row][Col];
                                   if(tile[TileNum/8][TileNum%8]->piece==1)
                                   {
                                       rflag=1;
                                       restore_color=tile[TileNum/8][TileNum%8]->pieceColor;
                                       restore_pieceName=tile[TileNum/8][TileNum%8]->pieceName;

                                   }
                                   tile[TileNum/8][TileNum%8]->piece=1;
                                   tile[Row][Col]->piece=0;
                                   tile[TileNum/8][TileNum%8]->pieceColor=tile[Row][Col]->pieceColor;
                                   tile[TileNum/8][TileNum%8]->pieceName=tile[Row][Col]->pieceName;
                                   if(tile[TileNum/8][TileNum%8]->pieceName=='K' &&  tile[TileNum/8][TileNum%8]->pieceColor)
                                       W=(TileNum/8)*8 +(TileNum%8);

                                   if(tile[TileNum/8][TileNum%8]->pieceName=='K' && !tile[TileNum/8][TileNum%8]->pieceColor)
                                       B=(TileNum/8)*8 +(TileNum%8);

                                   canMove=!valid->AmIInCheck();
                                //restore
                                   tile[TileNum/8][TileNum%8]->piece=0;
                                   tile[Row][Col]->piece=1;
                                   tile[Row][Col]->pieceColor=tile[TileNum/8][TileNum%8]->pieceColor;
                                   tile[Row][Col]->pieceName=tile[TileNum/8][TileNum%8]->pieceName;
                                   tile[TileNum/8][TileNum%8]->pieceColor=NULL;
                                   if(tile[Row][Col]->pieceName=='K' &&  tile[Row][Col]->pieceColor)
                                       W=(Row*8)+Col;
                                   if( tile[Row][Col]->pieceName=='K' && !tile[Row][Col]->pieceColor)
                                       B=(Row*8)+Col;
                                   if(rflag)
                                   {
                                       rflag=0;
                                       tile[TileNum/8][TileNum%8]->piece=1;
                                       tile[TileNum/8][TileNum%8]->pieceColor=restore_color;
                                       tile[TileNum/8][TileNum%8]->pieceName=restore_pieceName;
                                   }

                                   if(canMove)
                                       return 1;

                               }
                           }

                        }
                }
        }
    }
    return 0;

}


void Tile::tileDisplay()
{

    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,95,127);}");
}

void disOrange()
{
    int i;

    for(i=0;i<max;i++)
        tile[exp[i]/8][exp[i]%8]->tileDisplay();

}

void displayMove(Tile *test,Tile *test2)
   {
       QString myMove;
       QByteArray arr;
       const char *piece;
       int i;

       qDebug()<<test->pieceColor<<turn;
       if(turn==test->pieceColor)
       {
           qDebug()<<"Entered at least func";

           if(turn)
               myMove=" W    ";
           else
               myMove=" B    ";

           myMove.append(test->pieceName);
           myMove.append("     ");
           myMove.append(56-test->row);
           myMove.append(test->col+65);
           myMove.append("     ");
           myMove.append(56-test2->row);
           myMove.append(test2->col+65);

           moves->addItem(myMove);
           qDebug()<<"Entered!!";

       }
}
