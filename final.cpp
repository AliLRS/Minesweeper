#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <ctime>
#include <fstream>
#include "clui.h"

using namespace std;

struct player
{
    char name[100];
    int score;
};

struct Save
{
    int leng;
    int RealBoard[26][26];
    int DisplayBoard[26][26];
    int flag;
    player gamer;
};


//variables:
int NumMines = 4;
int leng = 5;
int DisplayBoard[26][26], RealBoard[26][26];
int flag = 4;
const int numPlayers = 10;
player players[numPlayers+1];
int indexOfPlayer;
Save save[5];
const int cols =  get_window_cols();
const int rows = get_window_rows();


//functions:
void Name();
void Menu();
void ChooseLevel();
void CustomMode();
bool InBoundCheck(int i , int j);
void Initialise();
void PlaceMines(int RealBoard[26][26]);
void MineCount();
void PrintBoard();
bool IsMine(int row, int col);
void PlayGame();
void EndGame();
void LostGame();
bool WinCheck();
void PutFlag(int row, int col);
void FinalBoard();
void WinGame();
void IsZero(int row, int col);
void Leaderboard();
void SaveGame();
void SaveList();
void LoadGame(int x);
void Header();
void Header2();
void SaveLeaderboard();
void LoadLeaderboard();
void SaveDetail();
void LoadDetail();



int main()
{
    init_clui();

    srand(time(NULL));

    LoadLeaderboard();
    LoadDetail();

    Name();
    Menu();

    return 0;
}

void Name()
{
    clear_screen();
    char* username = new char[100];
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-4, cols/2-7);
    printf("Enter your name");
    change_color_rgb(100, 180, 250);    //blue
    cursor_to_pos(rows/2-3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-2, cols/2-15);
    printf("*                             *");
    cursor_to_pos(rows/2-1, cols/2-15);
    printf("*******************************");
    reset_color();
    cursor_to_pos(rows/2-2, cols/2-14);
    cin >> username;            //////////////////////////////////  cin.getline(username, 100);
    for(int i=0; i<numPlayers; i++)
    {
        if(strcmp(players[i].name, username) == 0)
        {
            indexOfPlayer = i;
            delete[] username;
            return;
        }
    }
    int i=0;
    while(players[i].name[0]!='\0')
    {
        i++;
    }
    if(i >= numPlayers)
    {
        change_color_rgb(185, 0, 0);    //red
        cursor_to_pos(rows/2+1, cols/2-14);
        printf("List is full for new people!");
        cursor_to_pos(rows/2+2, cols/2-18);
        printf("enter the names of those on the list");
        reset_color();
        delay(2000);
        delete[] username;
        Name();
    }
    else
    {
        indexOfPlayer = i;
        strcpy(players[i].name, username);
        delete[] username;
    }
}

void Menu()
{
    clear_screen();
    Header2();
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-7, cols/2-11);
    printf("Please select an option");      // blue
    change_color_rgb(100, 180, 250);
    cursor_to_pos(rows/2-5, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-4, cols/2-15);
    printf("* 1 *        New Game         *");
    cursor_to_pos(rows/2-3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-2, cols/2-15);
    printf("* 2 *        Load Game        *");
    cursor_to_pos(rows/2-1, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2, cols/2-15);
    printf("* 3 *       Change Name       *");
    cursor_to_pos(rows/2+1, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2+2, cols/2-15);
    printf("* 4 *       Leaderboard       *");
    cursor_to_pos(rows/2+3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2+4, cols/2-15);
    printf("* 5 *          Quit           *");
    cursor_to_pos(rows/2+5, cols/2-15);
    printf("*******************************");

    int i=1;
    char x = '\0';
    while(1)
    {
        cursor_to_pos(9+2*i, 47);
        x = getch();
        if(x=='w' || x=='W')
        {
            if(i == 1) i = 5;
            else i--;
        }
        else if(x=='s' || x=='S')
        {
            if(i == 5) i = 1;
            else i++;
        }
        else if(x==13 || x==' ')
        {
            break;
        }
    }
    reset_color();
    if(i == 1) ChooseLevel();
    else if(i == 2) SaveList();
    else if(i == 3)
    {
        Name();
        Menu();
    }
    else if(i == 4) Leaderboard();
    else if(i == 5) EndGame();
}

void ChooseLevel()
{
    clear_screen();
    Header2();
    cursor_to_pos(2, 51);
    change_color_rgb(90, 240, 30);//light green
    printf("Back: ");
    change_color_rgb(190, 15, 0);
    printf("[Esc]");
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-7, cols/2-15);
    printf("        Choose Game level");
    change_color_rgb(100, 180, 250);        //light blue
    cursor_to_pos(rows/2-5, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-4, cols/2-15);
    printf("* 1 *        easy mode        *");
    cursor_to_pos(rows/2-3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-2, cols/2-15);
    printf("* 2 *       medium mode       *");
    cursor_to_pos(rows/2-1, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2, cols/2-15);
    printf("* 3 *        hard mode        *");
    cursor_to_pos(rows/2+1, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2+2, cols/2-15);
    printf("* 4 *       Custom mode       *");
    cursor_to_pos(rows/2+3, cols/2-15);
    printf("*******************************");
    int i=1;
    char x = '\0';
    while(1)
    {
        cursor_to_pos(9+2*i, 47);
        x = getch();
        if(x=='w' || x=='W')
        {
            if(i == 1) i = 4;
            else i--;
        }
        else if(x=='s' || x=='S')
        {
            if(i == 4) i = 1;
            else i++;
        }
        else if(x==13 || x==' ' || x==27)
        {
            break;
        }
    }
    reset_color();
    if(x == 27)
    {
        Menu();
        return;
    }
    if(i == 1)
    {
        leng = 5;
        NumMines = 4;
        flag = 4;
        Initialise();
        PlaceMines(RealBoard);
        MineCount();
        PlayGame();
    }
    else if(i == 2)
    {
        leng = 12;
        NumMines = 28;
        flag = 28;
        Initialise();
        PlaceMines(RealBoard);
        MineCount();
        PlayGame();
    }
    else if(i == 3)
    {
        leng = 20;
        NumMines = 96;
        flag = 96;
        Initialise();
        PlaceMines(RealBoard);
        MineCount();
        PlayGame();
    }
    else if(i == 4)
    {
        CustomMode();
    }
}

void CustomMode()
{
    clear_screen();
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-5, cols/2-15);
    printf("          Custom mode!");
    cursor_to_pos(rows/2-4, cols/2-15);
    printf("   Enter the number of rows");
    change_color_rgb(100, 180, 250);        //light blue
    cursor_to_pos(rows/2-3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2-2, cols/2-15);
    printf("*                             *");
    cursor_to_pos(rows/2-1, cols/2-15);
    printf("*******************************");
    reset_color();
    cursor_to_pos(rows/2-2, cols/2);
    reset_color();
    scanf("%d", &leng);
    if(leng < 5  || leng > 20)
    {
        play_beep();
        change_color_rgb(185, 0, 0);    //red
        cursor_to_pos(rows/2, cols/2-5);
        printf("Invalid input");
        reset_color();
        delay(1500);
        ChooseLevel();
        return;
    }
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2+1, cols/2-15);
    printf("   Enter the number of mines");
    cursor_to_pos(rows/2+2, cols/2-15);
    printf("   (5 <= n <= half of tiles)");
    change_color_rgb(100, 180, 250);        //light blue
    cursor_to_pos(rows/2+3, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2+4, cols/2-15);
    printf("*                             *");
    cursor_to_pos(rows/2+5, cols/2-15);
    printf("*******************************");
    cursor_to_pos(rows/2+4, cols/2);
    reset_color();
    scanf("%d", &NumMines);
    if(NumMines < 5  ||  NumMines > (leng*leng)/2)
    {
        play_beep();
        change_color_rgb(185, 0, 0);    //red
        cursor_to_pos(rows/2+6, cols/2-5);
        printf("Invalid input\n");
        reset_color();
        delay(1500);
        Menu();
    }
    flag = NumMines;
    Initialise();
    PlaceMines(RealBoard);
    MineCount();
    PlayGame();
}

bool InBoundCheck(int i , int j)
{
    if(i >= 0 && i < leng && j >= 0 && j < leng) return true;

    return false;
}

void Initialise()
{
    for(int i=0; i<leng; i++)
    {
        for(int j=0; j<leng; j++)
        {
            DisplayBoard[i][j]=0;
            RealBoard[i][j]=0;
        }
    }
}

void PlaceMines(int RealBoard[26][26])
{
    for(int i=0; i<NumMines; i++)
    {
        int row = rand()%leng;
        int col = rand()%leng;
        while(RealBoard[row][col]==10)      // 10 = sign of mine
        {
            row = rand()%leng;
            col = rand()%leng;
        }
        RealBoard[row][col]=10;
    }
}

void MineCount()
{
    for(int row=0; row<leng; row++)
    {
        for(int col=0; col<leng; col++)
        {
            if(RealBoard[row][col]==10)     // 10 = sign of mine
            {
                for(int x=row-1; x<=row+1; x++)
                {
                    for(int y=col-1; y<=col+1; y++)
                    {
                        if(InBoundCheck(x, y))
                        {
                            if(RealBoard[x][y]!=10)
                                RealBoard[x][y]++;
                        }
                    }
                }
            }
        }
    }
}

bool IsMine(int row, int col)
{
    if(DisplayBoard[row][col] != 1) return false;
    return (RealBoard[row][col]==10);
}

void PrintBoard()
{
    clear_screen();
    Header();
    cursor_to_pos(5, 3);
    change_color_rgb(90, 240, 30);//light green
    cout << "Player: ";
    change_color_rgb(20, 180, 160);//light blue
    cout << players[indexOfPlayer].name;
    cursor_to_pos(rows/2-leng/2, cols/2-3*leng/2);
    printf("    ");
    change_color_rgb(90, 240, 30);//light green
    for(int i=0; i<leng; i++)
    {
        if(i < 8) printf("%d  ", i+1);
        else printf("%d ", i+1);
    }
    reset_color();


    for(int i=0; i<leng; i++)
    {
        cursor_to_pos(rows/2-leng/2+1+i, cols/2-3*leng/2);
        change_color_rgb(90, 240, 30);//light green
        if(i > 8) printf("%d", i+1);
        else printf(" %d", i+1);
        reset_color();
        for(int j=0; j<leng; j++)
        {
            if(DisplayBoard[i][j]==0)       //not selected
            {
                printf("  -");
            }
            else if(DisplayBoard[i][j]==1)      //selected -- a number
            {
                change_color_rgb(20, 180, 160);//light blue
                printf("  %d", RealBoard[i][j]);
                reset_color();
            }
            else if(DisplayBoard[i][j]==-1)     //flag
            {
                change_color_rgb(230, 240, 30);//yellow
                printf("  #");
                reset_color();
            }
        }
    }
    cursor_to_pos(rows/2+leng/2+3, cols/2-7);
    change_color_rgb(215, 215, 5);  //yellow
    printf("Number of flags: %d", flag);
    reset_color();
}

void PlayGame()
{
    /*
    Initialise();
    PlaceMines(RealBoard);
    MineCount();
    */
    int row=0;
    int col=0;
    for(int i=0; i< leng*leng; i++)
    {
        PrintBoard();
        //FinalBoard();/////////////////////////////////////////////
        char input ='0';
        while(1)
        {
            cursor_to_pos(rows/2-leng/2+row+1, cols/2-3*leng/2+4+3*col);
            input = getch();
            if(input=='a' || input=='A')
            {
                if(col == 0) col = leng-1;
                else col--;
            }
            else if(input=='d' || input=='D')
            {
                if(col == leng-1) col = 0;
                else col++;
            }
            else if(input=='w' || input=='W')
            {
                if(row == 0) row = leng-1;
                else row--;
            }
            else if(input=='s' || input=='S')
            {
                if(row == leng-1) row = 0;
                else row++;
            }
            else if(input==' ' || input == 13)
            {
                break;
            }
            else if(input=='f' || input=='F')
            {
                break;
            }
            else if(input=='o' || input=='O')
            {
                SaveGame();
                Menu();
                return;
            }
            else if(input=='q' || input=='Q')
            {
                Menu();
                return;
            }
        }
        cursor_to_pos(leng+5, 1);

        if(DisplayBoard[row][col]==1)        //checking if the tile has already been selected     // 1 = sign of selected tile
        {
            change_color_rgb(185, 0, 0);    //red
            cursor_to_pos(rows/2+leng/2+4, cols/2-18);
            printf("That position has already been selected");
            reset_color();
            delay(2000);
            i--;
            continue;
        }

        if(input == ' ' || input == 13)
        {
            if(DisplayBoard[row][col]==-1)
            {
                change_color_rgb(185, 0, 0);    //red
                cursor_to_pos(rows/2+leng/2+4, cols/2-16);
                printf("That position has already been flagged");
                reset_color();
                delay(2000);
                i--;
                continue;
            }
            else
            {
                if(RealBoard[row][col]==0) IsZero(row, col);
                DisplayBoard[row][col]=1;
            }
        }
        if(input == 'f' || input == 'F') PutFlag(row, col);

        if(IsMine(row, col)) break;

        if(WinCheck()) break;
    }
    if(IsMine(row, col)) LostGame();
    if(WinCheck())
    {
        players[indexOfPlayer].score += (20*NumMines)+(10*leng*leng);
        WinGame();
    }
}

void EndGame()
{
    SaveLeaderboard();
    SaveDetail();
    clear_screen();
    change_color_rgb(100, 180, 250);    //light blue
    cursor_to_pos(rows/2-3, cols/2-7);
    printf("have a nice day!");
    reset_color();
    delay(2000);
    quit();
}

void LostGame()
{
    clear_screen();
    change_color_rgb(185, 0, 0);    //red
    cursor_to_pos(rows/2-4, cols/2-9);
    printf("You stepped on a mine!");
    delay(1500);
    cursor_to_pos(rows/2-3, cols/2-3);
    printf("Game Over!");
    delay(1500);
    reset_color();
    FinalBoard();
    delay(3000);
    Menu();
}

void WinGame()
{
    clear_screen();
    change_color_rgb(0, 150, 190);  //blue
    cursor_to_pos(rows/2-4, cols/2-7);
    printf("Congratulation!");
    delay(1500);
    cursor_to_pos(rows/2-3, cols/2-3);
    printf("You Won!");
    delay(1500);
    reset_color();
    FinalBoard();
    delay(3000);
    Menu();
}

bool WinCheck()
{
    int numMove=0;
    for(int i=0; i<leng; i++)
    {
        for(int j=0; j<leng; j++)
        {
            if(DisplayBoard[i][j]==1) numMove++;
        }
    }
    return (numMove >= leng*leng - NumMines);
}

void PutFlag(int row, int col)
{
    if(flag>0  && DisplayBoard[row][col]==0)
    {
        DisplayBoard[row][col]=-1;
        flag--;
    }
    else if(flag<=0  && DisplayBoard[row][col]==0)
    {
        change_color_rgb(185, 0, 0);    //red
        cursor_to_pos(rows/2+leng/2+3, cols/2-7);
        printf("All flags are used");
        reset_color();
        delay(1500);
    }
    else if(DisplayBoard[row][col]==-1)
    {
        DisplayBoard[row][col]=0;
        flag++;
    }
}

void FinalBoard()
{
    clear_screen();
    change_color_rgb(90, 240, 30);//light green
    cursor_to_pos(rows/2-leng/2-2, cols/2-5);
    printf("This is full map");
    reset_color();
    cursor_to_pos(rows/2-leng/2, cols/2-3*leng/2);
    printf("    ");
    change_color_rgb(90, 240, 30);//light green
    for(int i=0; i<leng; i++)
    {
        if(i < 8) printf("%d  ", i+1);
        else printf("%d ", i+1);
        delay(10);
    }
    reset_color();

    for(int i=0; i<leng; i++)
    {
        cursor_to_pos(rows/2-leng/2+1+i, cols/2-3*leng/2);
        change_color_rgb(90, 240, 30);//light green
        if(i > 8) printf("%d", i+1);
        else printf(" %d", i+1);
        delay(10);
        reset_color();
        for(int j=0; j<leng; j++)
        {
            if(RealBoard[i][j]==10)     //mine
            {
                change_color_rgb(190, 15, 0);
                printf("  *");
                reset_color();
            }
            else
            {
                change_color_rgb(20, 180, 160);//light blue
                printf("  %d", RealBoard[i][j]);
                reset_color();
            }
            delay(10);
        }
    }
}

void IsZero(int row, int col)
{
    if(DisplayBoard[row][col] == 1) return;

    DisplayBoard[row][col]=1;
    for(int x=row-1; x<=row+1; x++)
    {
        for(int y=col-1; y<=col+1; y++)
        {
            if(InBoundCheck(x, y))
            {
                if(RealBoard[x][y]==0) IsZero(x, y);
                DisplayBoard[x][y]=1;
            }
        }
    }
}

void swap(player* a1, player* a2)
{
    player temp = *a1;
    *a1 = *a2;
    *a2 = temp;
}

void bubbleSort(player* p, int size)
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if(players[j+1].score > players[j].score)
                swap(&p[j], &p[j+1]);
        }
    }
}

void Leaderboard()
{
    clear_screen();
    int size = 0;
    while(players[size].name[0] != '\0')
    {
        size++;
    }
    bubbleSort(players, size);
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-8, cols/2-15);
    printf("          Leaderboard");
    cursor_to_pos(rows/2-6, cols/2-15);
    printf("Rank      Name         Score");
    change_color_rgb(100, 180, 250);        //light blue
    cursor_to_pos(rows/2-5, cols/2-15);
    printf("*******************************");
    for(int i=1; i<=size; i++)
    {
        cursor_to_pos(rows/2-6+2*i, cols/2-15);
        printf("*   *                 *       *");
        cursor_to_pos(rows/2-5+2*i, cols/2-15);
        printf("*******************************");
    }
    for(int i=0; i<size; i++)
    {
        cursor_to_pos(rows/2-4+2*i, cols/2-13);
        cout << i+1;
        cursor_to_pos(rows/2-4+2*i, cols/2-10);
        cout << players[i].name;
        cursor_to_pos(rows/2-4+2*i, cols/2+8);
        cout << players[i].score;
    }
    change_color_rgb(90, 240, 30);//light green
    cursor_to_pos(rows/2-1+2*size, cols/2-15);
    printf("    Press any key to back");
    reset_color();
    char x = getch();
    x++;
    Menu();
}

void SaveGame()
{
    int i=0;
    while(save[i].leng != 0)
    {
        if(strcmp(save[i].gamer.name, players[indexOfPlayer].name) == 0)
        {
            break;
        }
        i++;
    }
    save[i].leng = leng;
    save[i].flag = flag;
    save[i].gamer = players[indexOfPlayer];
    for(int j=0; j<leng; j++)
    {
        for(int z=0; z<leng; z++)
        {
            save[i].DisplayBoard[j][z] = DisplayBoard[j][z];
            save[i].RealBoard[j][z] = RealBoard[j][z];
        }
    }
}

void SaveList()
{
    clear_screen();
    Header2();
    cursor_to_pos(2, 51);
    change_color_rgb(90, 240, 30);//light green
    printf("Back: ");
    change_color_rgb(190, 15, 0);
    printf("[Esc]");
    int size=0;
    while(save[size].leng != 0)
    {
        size++;
    }
    change_color_rgb(245, 225, 65);    //yellow
    cursor_to_pos(rows/2-8, cols/2-15);
    printf("           SaveList");
    cursor_to_pos(rows/2-6, cols/2-15);
    printf("     Name              Score");
    change_color_rgb(100, 180, 250);        //light blue
    cursor_to_pos(rows/2-5, cols/2-15);
    printf("*******************************");
    for(int i=1; i<=size; i++)
    {
        cursor_to_pos(rows/2-6+2*i, cols/2-15);
        printf("*   *                 *       *");
        cursor_to_pos(rows/2-5+2*i, cols/2-15);
        printf("*******************************");
    }
    for(int i=0; i<size; i++)
    {
        cursor_to_pos(rows/2-4+2*i, cols/2-13);
        cout << i+1;
        cursor_to_pos(rows/2-4+2*i, cols/2-10);
        cout << save[i].gamer.name;
        cursor_to_pos(rows/2-4+2*i, cols/2+8);
        cout << save[i].gamer.score;
    }
    reset_color();
    int i=1;
    char x = '\0';
    if(size == 0)
    {
        cursor_to_pos(rows/2-6+2*i, cols/2-13);
        while(x != 27)
        {
            x = getch();
        }
        Menu();
        return;
    }
    while(1)
    {
        cursor_to_pos(rows/2-6+2*i, cols/2-13);
        x = getch();
        if(x=='w' || x=='W')
        {
            if(i == 1) i = size;
            else i--;
        }
        else if(x=='s' || x=='S')
        {
            if(i == size) i = 1;
            else i++;
        }
        else if(x==13 || x==' ' || x==27)
        {
            break;
        }
    }
    if(x == 27)
    {
        Menu();
        return;
    }
    else
    {
        LoadGame(i-1);
    }
    PlayGame();
}

void LoadGame(int x)
{
    leng = save[x].leng;
    flag = save[x].flag;
    for(int j=0; j<leng; j++)
    {
        for(int z=0; z<leng; z++)
        {
            DisplayBoard[j][z] = save[x].DisplayBoard[j][z];
            RealBoard[j][z] = save[x].RealBoard[j][z];
        }
    }
    int i=0;
    while(players[i].name[0] != '\0')
    {
        if(strcmp(players[i].name, save[x].gamer.name) == 0)
        {
            indexOfPlayer = i;
            break;
        }
        i++;
    }
}

void Header()
{
    cursor_to_pos(3, 1);
    change_color_rgb(20, 180, 160);//light blue
    for(int i=0; i<cols; i++)
    {
        printf("-");
    }
    cursor_to_pos(2, 3);
    change_color_rgb(90, 240, 30);//light green
    printf("Navigation:");
    cursor_to_pos(1, 18);
    change_color_rgb(190, 15, 0);
    printf("[w]");
    cursor_to_pos(2, 15);
    printf("[a][s][d]");
    cursor_to_pos(2, 30);
    change_color_rgb(90, 240, 30);//light green
    printf("Select: ");
    change_color_rgb(190, 15, 0);
    printf("[Enter]");
    cursor_to_pos(2, 51);
    change_color_rgb(90, 240, 30);//light green
    printf("Flag: ");
    change_color_rgb(190, 15, 0);
    printf("[f]");
    cursor_to_pos(2, 66);
    change_color_rgb(90, 240, 30);//light green
    printf("Save and quit: ");
    change_color_rgb(190, 15, 0);
    printf("[o]");
    cursor_to_pos(2, 90);
    change_color_rgb(90, 240, 30);//light green
    printf("Quit: ");
    change_color_rgb(190, 15, 0);
    printf("[q]");
    reset_color();
}

void Header2()
{
    cursor_to_pos(3, 1);
    change_color_rgb(20, 180, 160);//light blue
    for(int i=0; i<cols; i++)
    {
        printf("-");
    }
    cursor_to_pos(2, 3);
    change_color_rgb(90, 240, 30);//light green
    printf("Navigation:");
    cursor_to_pos(1, 18);
    change_color_rgb(190, 15, 0);
    printf("[w]");
    cursor_to_pos(2, 15);
    printf("   [s]   ");
    cursor_to_pos(2, 30);
    change_color_rgb(90, 240, 30);//light green
    printf("Select: ");
    change_color_rgb(190, 15, 0);
    printf("[Enter]");
    reset_color();
}

void SaveLeaderboard()
{
    int size = 0;
    while(players[size].name[0] != '\0')
    {
        size++;
    }
    ofstream fout("Leaderboard.txt");
    if(fout.is_open())
    {
    fout << size  << endl << endl;
    for(int i=0; i<size; i++)
    {
        fout << players[i].name << " " << players[i].score << endl;
    }
    fout.close();
    }
}

void LoadLeaderboard()
{
    int size;
    ifstream fin("Leaderboard.txt");
    if(fin.is_open())
    {
    fin >> size;

    for(int i=0; i<size; i++)
    {
        fin >> players[i].name >> players[i].score;
    }
    fin.close();
    }
}

void SaveDetail()
{
    int size=0;
    while(save[size].leng != 0)
    {
        size++;
    }
    ofstream fout("SaveList.txt");
    if(fout.is_open())
    {
        fout << size << endl << endl;
        for(int i=0; i<size; i++)
        {
            fout << save[i].leng << endl;
            for(int j=0; j<save[i].leng; j++)
            {
                for(int z=0; z<save[i].leng; z++)
                {
                    fout << save[i].RealBoard[j][z]<< " ";
                }
                fout << endl;
            }
            fout << endl;
            for(int j=0; j<save[i].leng; j++)
            {
                for(int z=0; z<save[i].leng; z++)
                {
                    fout << save[i].DisplayBoard[j][z]<< " ";
                }
                fout << endl;
            }
            fout << save[i].flag << endl;
            fout << save[i].gamer.name << endl;
            fout << save[i].gamer.score << endl;
            fout << endl << endl;
        }
        fout.close();
    }
}

void LoadDetail()
{
    int size;
    ifstream fin("SaveList.txt");
    if(fin.is_open())
    {
        fin >> size;
        for(int i=0; i<size; i++)
        {
            fin >> save[i].leng;
            for(int j=0; j<save[i].leng; j++)
            {
                for(int z=0; z<save[i].leng; z++)
                {
                    fin >> save[i].RealBoard[j][z];
                }
            }
            for(int j=0; j<save[i].leng; j++)
            {
                for(int z=0; z<save[i].leng; z++)
                {
                    fin >> save[i].DisplayBoard[j][z];
                }
            }
            fin >> save[i].flag;
            fin >> save[i].gamer.name;
            fin >> save[i].gamer.score;
        }
        fin.close();
    }
}
