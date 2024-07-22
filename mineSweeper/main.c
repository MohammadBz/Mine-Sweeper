#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

struct user
{
    char name[100];
    char password[100];
    int allGamesPlayed;
    int win;
    int lose;
};

struct user arruser[1000];
int userCount=0;

int checkPass(int userpath) // return 1 for true and -1 for false
{

    printf("please enter the password of %s or return to menu by typing -1:\n",arruser[userpath-1].name);
    char *pass=(char*)malloc(1000*sizeof(char));
    gets(pass);
    while(strlen(pass)>100||strstr(pass," ")!=0)
    {
        printf("Please enter a valid password To check\n");
        gets(pass);
    }
    if(strcmp("-1",pass)==0)
    {
        free(pass);
        return -1;
    }
    if(strcmp(pass,arruser[userpath-1].password)==0)
    {
        free(pass);
        return 1;
    }
    else // else pass
    {
        while(1)
        {
            printf("Password incorrect. enter a new password or return to menu by selecting -1");
            gets(pass);
            while(strlen(pass)>100||strstr(pass," ")!=0)
            {
                printf("Please enter a valid password To check\n");
                gets(pass);
            }
            if(strcmp("-1",pass)==0)
            {
                return -1;
            }
            else if(strcmp(pass,arruser[userpath-1].password)==0)
            {
                return 1;
            }

            // return userpath-1;
        }
    }

}

int login(int userId)
{
    printf("Which account do you want to log in to?\n");
    for(int i=0; i<userCount; i++)
    {
        printf("----------%d-%s\n",i+1,arruser[i].name);

    }
    char *input=(char*)malloc(1000*sizeof(char));
    gets(input);
    int userpath=0;
    userpath=atoi(input);
    while(strlen(input)>3||userpath>userCount)
    {
        printf("Invalid Choice!\n");
        gets(input);
        userpath=atoi(input);
    }
    free(input);
    if(userId==userpath-1)
    {
        printf("This is your current account!\n");
        return userId;
    }
    if(userpath>0&&userpath<=userCount+1)
    {
        int temp=checkPass(userpath);
        if(temp==-1)
        {
            return userId;
        }
        else
        {
            return userpath-1;
        }
    }
    else
    {
        while (1)
        {
            printf("We don't have that profile please choose another one or return to menu by typing -1\n");
            scanf("%d",&userpath);
            if(userpath==-1)
            {
                return userId;
            }
            else if(userpath>0&&userpath<=userCount+1)
            {
                int temp;
                temp=checkPass(userpath);
                if(temp==-1)
                {
                    return userId;
                }
                else
                {
                    return userpath-1;
                }
            }
        }
    }


}

int createUser()
{
    struct user temp;
    char *name=(char*)malloc(1000*sizeof(char));
    printf("Please enter your profile name :\n");

    gets(name);
    while(strlen(name)>100||strstr(name," ")!=0)
    {
        printf("Too much character or space!\nTry again pls\n");
        gets(name);
    }
    strcpy(temp.name,name);
    free(name);
    printf("Please enter a password that have at least 8 character:\n");


    char *pass=(char*)malloc(1000*sizeof(char));
    gets(pass);
    if(strlen(pass)<8||strlen(pass)>100||strstr(pass," ")!=0)
    {
        printf("for your own security please enter a strong password that contain at least 8 character and maximum 100 character without space\n");
        gets(pass);
        while(strlen(pass)<8||strlen(pass)>100||strstr(pass," ")!=0)
        {
            printf("Try again pls\n");
            gets(pass);
        }
    }
    strcpy(temp.password,pass);
    free(pass);
    temp.lose=0;
    temp.win=0;
    temp.allGamesPlayed=0;
    arruser[userCount]=temp;
    userCount++;
    return userCount-1;
}
void changeName(struct user *input)
{
    char *name=(char*)malloc(1000*sizeof(char));
    printf("Please enter your new profile name :");

    gets(name);
    while(strlen(name)>100||strstr(name," ")!=0)
    {
        printf("Too much character or space!\nTry again pls\n");
        gets(name);
    }
    strcpy(input->name,name);
    free(name);

}

void showStats(struct user *input)
{

    printf("***  You have played %d Game and Won %d and Lost %d of them  ***\n",input->allGamesPlayed,input->win,input->lose);
}
void generateBomb(int mapSize,char realboard[][mapSize],int bombCount)
{
    for(int i=0; i<bombCount; i++)
    {

        createBomb(mapSize,realboard);
    }
}

void createBomb(int mapSize,char realboard[][mapSize])
{
    static int initialized = 0;
    if (!initialized)
    {
        time_t t;
        srand((unsigned) time(&t));
        initialized = 1;
    }
    int x=rand()%mapSize;
    int y=rand()%mapSize;

    int countflag=0;
    for(int i=0; i<mapSize; i++)
    {
        if(realboard[i][y]=='*')
        {
            countflag++;
        }
    }
    if(countflag>=3)
    {
        createBomb(mapSize,realboard);
        return ;
    }

    if(realboard[x][y]!='*')
    {

        realboard[x][y]='*';
    }
    else
    {
        createBomb(mapSize,realboard);
    }
}
void fillArr(int mapSize,char realboard[][mapSize])
{
    for(int i=0; i<mapSize; i++)
    {
        for(int j=0; j<mapSize; j++)
        {
            if(realboard[i][j]!='*')
            {
                realboard[i][j]='-';
            }
        }
    }
}
int nearBomb(int x,int y,int mapsize,char realboard[][mapsize])
{
    int count=0;
//   printf(" house %d %d ",x,y);
    if (validPoint (x-1, y,mapsize) == 1)
    {
        if(realboard[x-1][y]=='*')
        {
            count++;
        }
    }
    if (validPoint (x+1, y,mapsize) == 1)
    {
        if(realboard[x+1][y]=='*')
        {
            count++;
        }

    }
    if (validPoint (x, y+1,mapsize) == 1)
    {
        if(realboard[x][y+1]=='*')
        {
            count++;
        }
    }
    if (validPoint (x, y-1,mapsize) == 1)
    {
        if(realboard[x][y-1]=='*')
        {
            count++;
        }
    }
    if (validPoint (x-1, y+1,mapsize) == 1)
    {
        if(realboard[x-1][y+1]=='*')
        {
            count++;
        }
    }
    if (validPoint (x-1, y-1,mapsize) == 1)
    {
        if(realboard[x-1][y-1]=='*')
        {
            count++;
        }
    }
    if (validPoint (x+1, y+1,mapsize) == 1)
    {
        if(realboard[x+1][y+1]=='*')
        {
            count++;
        }
    }
    if (validPoint (x+1, y-1,mapsize) == 1)
    {
        if(realboard[x+1][y-1]=='*')
        {
            count++;
        }
    }
    return count;
}
void fillArrint(int mapSize,int realboardint[][mapSize],char realboard[][mapSize])
{

    for(int i=0; i<mapSize; i++)
    {
        for(int j=0; j<mapSize; j++)
        {
            if(realboard[i][j]=='*')
            {
                realboardint[i][j]=-1;
            }
            else
            {
                realboardint[i][j]=nearBomb(i,j,mapSize,realboard);
            }
        }
    }

}

int validPoint(int x,int y,int mapSize)
{
    if(x>=0&&x<mapSize&&y>=0&&y<mapSize)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
void cleararr(int mapsize,char realboard[][mapsize],int realboardint[][mapsize])
{
    printf("\e[1;1H\e[2J");
    printf("Current status of game is :\n");
    printf("\n\n        1 2 3 4 5 6 7 8\n\n");
    for(int i=0; i<mapsize; i++)
    {
        for(int j=0; j<mapsize; j++)
        {
            realboard[i][j]='-';
            realboardint[i][j]=0;
        }
    }
}

int putFlag(int mapsize,int x,int y,int realBoardint[][mapsize],char showBoard[][mapsize],int *flagcount,int *trueguess)
{
// 20 for flag ascii code
    if(showBoard[x][y]==20)
    {
        showBoard[x][y]='-';
        *flagcount=*flagcount+1;
        if(realBoardint[x][y]==-1)
        {
            *trueguess=*trueguess-1;
        }
    }
    else if(*flagcount==0)
    {
        printf("You Don't have any flag left !\n");
        printf("press e to continue\n");
        return 0;
    }
    else if(showBoard[x][y]=='-')
    {
        showBoard[x][y]='?';
        *flagcount=*flagcount-1;
        if(realBoardint[x][y]==-1)
        {
            *trueguess=*trueguess+1;
        }
    }
    if(mapsize==8)
    {
        if(*trueguess==10)
        {
            return 1;
        }
    }
    if(mapsize==16)
    {
        if(*trueguess==40)
        {
            return 1;
        }
    }
    return 0;
}

void endGame(int mapsize,int realboardint[][mapsize],char showboard[][mapsize],int flagCount,int trueguess)
{

    char temp=229;
    printf("\e[1;1H\e[2J\n");
    printf("\033[0;31m");
    printf("##        #######   ######  ########    #### \n");
    printf("##       ##     ## ##    ##    ##       #### \n");
    printf("##       ##     ## ##          ##       #### \n");
    printf("##       ##     ##  ######     ##        ##  \n");
    printf("##       ##     ##       ##    ##            \n");
    printf("##       ##     ## ##    ##    ##       #### \n");
    printf("########  #######   ######     ##       #### \n");
    printf("\x1b[32m");
    for(int i=0; i<mapsize; i++)
    {
        if(i+1>=10)
        {
            printf("    %d  ",i+1);
        }
        else
        {
            printf("     %d  ",i+1);
        }
        for(int j=0; j<mapsize; j++)
        {
            if(realboardint[i][j]!=-1)
            {
                printf("%c ",showboard[i][j]);
            }
            else
            {
                printf("\033[0;31m");
                printf("%c ",temp);
                printf("\x1b[32m");

            }

        }
        printf("\n");
    }
    if(mapsize==8)
    {
        printf("\n     You put %d flags and %d of them were Bomb\n",10-flagCount,trueguess);
    }
    else if(mapsize==16)
    {
        printf("\n     You put %d flags and %d of them were Bomb\n",40-flagCount,trueguess);
    }
    sleep(4);
}

int reveal(int sizemap,int x,int y,int realboardint[][sizemap],char showboard[][sizemap],int memoryOFarr[][sizemap])
{
    if(memoryOFarr[x][y]==0)
    {
        memoryOFarr[x][y]=1;

        if(realboardint[x][y]==-1)
        {
            return -1;
        }
        else if(realboardint[x][y]==0)  // reveal more
        {
            showboard[x][y]='0';

            if (validPoint (x-1, y,sizemap) == 1)
            {
                reveal(sizemap,x-1,y,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x+1, y,sizemap) == 1)
            {
                reveal(sizemap,x+1,y,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x, y+1,sizemap) == 1)
            {
                reveal(sizemap,x,y+1,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x, y-1,sizemap) == 1)
            {
                reveal(sizemap,x,y-1,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x+1, y+1,sizemap) == 1)
            {
                reveal(sizemap,x+1,y+1,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x-1, y+1,sizemap) == 1)
            {
                reveal(sizemap,x-1,y+1,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x-1, y-1,sizemap) == 1)
            {
                reveal(sizemap,x-1,y-1,realboardint,showboard,memoryOFarr);
            }
            if (validPoint (x+1, y-1,sizemap) == 1)
            {
                reveal(sizemap,x+1,y-1,realboardint,showboard,memoryOFarr);
            }
            return 0;
        }
        else
        {
            if(realboardint[x][y]==1) showboard[x][y]='1';
            else if(realboardint[x][y]==2)showboard[x][y]='2';
            else if(realboardint [x][y]==3)showboard[x][y]='3';
            else if(realboardint [x][y]==4)showboard[x][y]='4';
            else if(realboardint [x][y]==5)showboard[x][y]='5';
            else if(realboardint [x][y]==6)showboard[x][y]='6';
            else if(realboardint [x][y]==7)showboard[x][y]='7';
            else if(realboardint [x][y]==8)showboard[x][y]='8';
            return 0;
        }

    }
    else
    {
        return -1;
    }
}

void win(int mapsize,int realboardint[][mapsize],char showboard[][mapsize])
{

    char temp=229;
    printf("\e[1;1H\e[2J\n");
    printf("\033[0;34m");
    printf("##     ## ####  ######  ########  #######  ########  ##    ##     #### \n");
    printf("##     ##  ##  ##    ##    ##    ##     ## ##     ##  ##  ##      #### \n");
    printf("##     ##  ##  ##          ##    ##     ## ##     ##   ####       #### \n");
    printf("##     ##  ##  ##          ##    ##     ## ########     ##         ##   \n");
    printf(" ##   ##   ##  ##          ##    ##     ## ##   ##      ##       \n");
    printf("  ## ##    ##  ##    ##    ##    ##     ## ##    ##     ##        #### \n");
    printf("   ###    ####  ######     ##     #######  ##     ##    ##        #### \n");
    printf("\x1b[32m");
    for(int i=0; i<mapsize; i++)
    {
        if(i+1>=10)
        {
            printf("    %d  ",i+1);
        }
        else
        {
            printf("     %d  ",i+1);
        }
        for(int j=0; j<mapsize; j++)
        {
            if(realboardint[i][j]!=-1)
            {
                printf("%c ",showboard[i][j]);
            }
            else
            {
                printf("\033[0;34m");
                printf("%c ",temp);
                printf("\x1b[32m");

            }

        }
        printf("\n");
    }
    sleep(2);
}

void searchInStr(int *xinput,int *yinput,char *mode,char *input)
{
    int i=0;
    int temp=0;
    *xinput=0;
    *yinput=0;
    while(input[i]!='\0')
    {

        if(input[i]==' ')
        {
            i++;
            temp=0;
            while(input[i]!=' ')
            {
                temp=input[i]-'0';
                *yinput=*yinput*10 + temp;
                i++;
            }
            i++;
            *mode=input[i];
            break;
        }
        temp=input[i]-'0';
        *xinput=*xinput*10 + temp;
        i++;
    }

}

int play()
{
    int flagCount=10;
    int trueguess=0;

    int gameOverStatus=0;
    printf("Please Choose the difficulty :\n----------1-Easy 8x8 \n----------2-Medium 16x16\n");
    int path=0;
    int sizeMap=0;
    char *pathinput=(char*)malloc(1000*sizeof(char));
    gets(pathinput);
    path=atoi(pathinput);
    while(strlen(pathinput)>1|| (path!=1&&path!=2))
    {
        printf("please enter a valid option without space:\n");
        gets(pathinput);
        path=atoi(pathinput);
    }
    free(pathinput);
    if(path==1)
    {
        sizeMap=8;
        flagCount=10;
    }
    else if(path==2)
    {
        sizeMap=16;
        flagCount=40;
    }
    printf("\e[1;1H\e[2J\n");
    int xInput=0;
    int yInput=0;
    char modeInput;
    char realBoard[sizeMap][sizeMap];
    char showBoard[sizeMap][sizeMap];
    int realBoardint[sizeMap][sizeMap];
    int memoryOFarr[sizeMap][sizeMap];
    for(int i=0; i<sizeMap; i++)
    {
        for(int j=0; j<sizeMap; j++)
        {
            memoryOFarr[i][j]=0;
            showBoard[i][j]='-';
        }
    }

    generateBomb(sizeMap,realBoard,flagCount);
    fillArr(sizeMap,realBoard);
    fillArrint(sizeMap,realBoardint,realBoard);
    for(int i=0; i<sizeMap; i++)
    {
        if(i+1>=10)
        {
            printf("    %d  ",i+1);
        }
        else
        {
            printf("     %d  ",i+1);
        }

        for(int j=0; j<sizeMap; j++)
        {
            printf("%c ",showBoard[i][j]);
        }
        printf("\n");
    }

    printf("What is your Move?:\nNOTE: L for revealing the given location and R for putting or removing flag (for example 1 2 L is a valid move or 5 8 R) \n");
    char *input=(char*)malloc(1000*sizeof(char));

    gets(input);
    while(strlen(input)>8)
    {
        printf("Invalid move please choose again\n");
        gets(input);
    }
    searchInStr(&xInput,&yInput,&modeInput,input);
    while(validPoint(xInput-1,yInput-1,sizeMap)==-1|| (modeInput!='R'&&modeInput!='L'))
    {
        printf("Invalid move please choose again\n");
        gets(input);
        while(strlen(input)>8)
        {
            printf("Invalid move please choose again\n");
            gets(input);
        }
        searchInStr(&xInput,&yInput,&modeInput,input);
    }

    if(realBoardint[xInput-1][yInput-1]==-1) // check for first spot
    {
        while(realBoardint[xInput-1][yInput-1]==-1)
        {
            cleararr(sizeMap,realBoard,realBoardint);
            generateBomb(sizeMap,realBoard,flagCount);
            fillArr(sizeMap,realBoard);
            fillArrint(sizeMap,realBoardint,realBoard);
        }
    }
    reveal(sizeMap,xInput-1,yInput-1,realBoardint,showBoard,memoryOFarr);


    while(gameOverStatus==0) // real jobbbbbbbbbbbbbb
    {

        printf("\e[1;1H\e[2J");
        printf("Current status of game is :\nTotal flag left : %d\n",flagCount);
        if(sizeMap==8)
        {
            printf("\n\n        1 2 3 4 5 6 7 8\n\n");
        }
        else if(sizeMap==16)
        {
            printf("\n\n        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\n\n");
        }

        for(int i=0; i<sizeMap; i++)
        {
            if(i+1>=10)
            {
                printf("    %d  ",i+1);
            }
            else
            {
                printf("     %d  ",i+1);
            }
            for(int j=0; j<sizeMap; j++)
            {
                printf("%c ",showBoard[i][j]);
            }
            printf("\n");
        }

        printf("\n\n");

        printf("What is your Move?:\nNOTE: L for revealing the given location and R for putting or removing flag (for example 1 2 L is a valid move or 5 8 R)\n");
        gets(input);
        while(strlen(input)>8)
        {
            printf("Invalid move please choose again\n");
            gets(input);
        }
        searchInStr(&xInput,&yInput,&modeInput,input);
        while(validPoint(xInput-1,yInput-1,sizeMap)==-1|| (modeInput!='R'&&modeInput!='L'))
        {

            printf("Invalid move please choose again\n");
            gets(input);
            while(strlen(input)>8)
            {
                printf("Invalid move please choose again\n");
                gets(input);
            }
            searchInStr(&xInput,&yInput,&modeInput,input);
        }
        // check the move
        if(showBoard[xInput-1][yInput-1]!='-'&&showBoard[xInput-1][yInput-1]!=20)
        {
            printf("Invalid Move!\n");
            sleep(1);

        }
        else
        {
            int temp=0;
            if(modeInput=='L')
            {
                if(showBoard[xInput-1][yInput-1]==20)
                {
                    putFlag(sizeMap,xInput-1,yInput-1,realBoardint,showBoard,&flagCount,&trueguess);
                }
                temp=reveal(sizeMap,xInput-1,yInput-1,realBoardint,showBoard,memoryOFarr);
            }
            else if(modeInput=='R')
            {
                temp=putFlag(sizeMap,xInput-1,yInput-1,realBoardint,showBoard,&flagCount,&trueguess);
                if(sizeMap==8)
                {
                    if(trueguess==10)
                    {
                        gameOverStatus=1;
                        temp=1;
                    }
                }
                if(sizeMap==16)
                {
                    if(trueguess==40)
                    {
                        gameOverStatus=1;
                        temp=1;
                    }
                }
            }

            // flag and lost
            if(temp==-1)
            {
                gameOverStatus=-1;
            }
            else if(temp==1)
            {
                gameOverStatus=1;
            }
        } // end while game
        // game over
    }
    free(input);
    if(gameOverStatus==-1)
    {
        endGame(sizeMap,realBoardint,showBoard,flagCount,trueguess);
        return -1;
    }
    else if(gameOverStatus==1)
    {
        win(sizeMap,realBoardint,showBoard);
        return 1;
    }
    return 0;
}

void menu()
{

    //  printf("\u2660\n");
    printf("\x1b[32m");
    printf(" #     #                                              #######        \n");
    printf(" #  #  # ###### #       ####   ####  #    # ######       #     ####  \n");
    printf(" #  #  # #      #      #    # #    # ##  ## #            #    #    # \n");
    printf(" #  #  # #####  #      #      #    # # ## # #####        #    #    # \n");
    printf(" #  #  # #      #      #      #    # #    # #            #    #    # \n");
    printf(" #  #  # #      #      #    # #    # #    # #            #    #    # \n");
    printf("  ## ##  ###### ######  ####   ####  #    # ######       #     ####  \n\n");
    printf(" #     #                   #####                                            \n");
    printf(" ##   ## # #    # ######  #     # #    # ###### ###### #####  ###### #####  \n");
    printf(" # # # # # ##   # #       #       #    # #      #      #    # #      #    # \n");
    printf(" #  #  # # # #  # #####    #####  #    # #####  #####  #    # #####  #    # \n");
    printf(" #     # # #  # # #             # # ## # #      #      #####  #      #####  \n");
    printf(" #     # # #   ## #       #     # ##  ## #      #      #      #      #   #  \n");
    printf(" #     # # #    # ######   #####  #    # ###### ###### #      ###### #    # \n\n\n");

    int userId;
    char *input=(char*)malloc(1000*sizeof(char));

    if(userCount==0)
    {
        printf("You have to sign up for the first time using this game.\n");
        userId=createUser();
    }
    int pathUser=0;

    int temp=0;
    do
    {
        printf("----------Welcome *%s*!\n",arruser[userId].name);
        printf("----------1-Change Name\n");
        printf("----------2-Play!\n");
        printf("----------3-Create a new profile\n");
        printf("----------4-log in to another account\n");
        printf("----------5-Show stats\n");
        printf("----------6-Exit\n");
        gets(input);
        pathUser = atoi(input);
        while(strlen(input)>1||pathUser<1||pathUser>6)
        {
            printf("Please enter a valid number for god's sake\n");
            gets(input);
            pathUser = atoi(input);
        }
        switch(pathUser)
        {
        case 1:
            changeName(&arruser[userId]);
            break;
        case 2:

            temp=play();
            if(temp==1)
            {
                arruser[userId].allGamesPlayed++;
                arruser[userId].win++;
            }
            else if(temp ==-1)
            {
                arruser[userId].allGamesPlayed++;
                arruser[userId].lose++;
            }
            break;
        case 3:
            userId=createUser();
            break;
        case 4:
            userId=login(userId);
            break;

        case 5:
            showStats(&arruser[userId]);
            break;
        case 6:
            return;
            break;

        default :
            printf("Please enter a valid number\n");
            break;
        }

    }
    while((pathUser!=6));
    free(input);
} // end function


int main()
{
// 20 for flag 229 for bomb
    menu();
    //play();
    return 0;
}
