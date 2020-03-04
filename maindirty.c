//snake game in c

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define U 72
#define D 80
#define L 75
#define R 77

int lenght;
int bend;
int len;
char key;
int life;

struct coordinate{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate headSnake, bend[500],food,bodySnake[30];

int main(){
    char key;

    printInitScreen();
    loadScreen();

    lenght=5;
    headSnake.x=25;
    headSnake.y=20;
    headSnake.direction=R;

    printBoarder();
    eatFood();

    life=3;
    bend[0]=headSnake;

    toMove();

    return 0;
}
void toMove(){
    int key,count;

    do{
        eatFood();
        fflush(stdin); // clean buffer
        len=0;

        for(count=0;count<30;count++){
            bodySnake[count].x=0;
            bodySnake[count].y=0;
            if(count==lenght) break;
        }

        toDelay();
        printBoarder();

        if(headSnake.direction==R) Right();
        else if(headSnake.direction==L) Left();
        else if(headSnake.direction==D) Down();
        else if(headSnake.direction==U) Up();
        toCheckExitGameCondition();
    }while(!kbhit()); // kbhit => verify if a key have been pressed.

    key=getch();
    if(key==27){
        system("cls");
        exit(0);
    }
    // bend increment
    if(
    (key==R&&headSnake.direction!=L&&headSnake.direction!=R)||
    (key==L&&headSnake.direction!=R&&headSnake.direction!=L)||
    (key==U&&headSnake.direction!=D&&headSnake.direction!=U)||
    (key==D&&headSnake.direction!=U&&headSnake.direction!=D)){

        bend++;
        bend[bend]=headSnake;
        headSnake.direction=key;

        //It moves the snack
        if(key==U) headSnake.y--;
        if(key==D) headSnake.y++;
        if(key==R) headSnake.x++;
        if(key==L) headSnake.x--;

        toMove();
    }else{
        printf("\a");
        toMove();
    }
}

void gotoxy(int x, int y){
 COORD coord;

 coord.X = x;
 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }
void loadScreen(){
	int loadComponent;

    gotoxy(36,14);
    printf("loading...");

    gotoxy(30,15);

    for (loadComponent = 1; loadComponent <= 20; loadComponent++){
        sleep(2/3);
        printf("%c",177);
    }

    getch();
}
void toDelay(){
    statusBar();
    long double count;
    for(count=0;count<=(10000000);count++); //sleep very fast but not so much
}
void toCheckExitGameCondition(){
    int count,check=0;
    for(count=4;count<lenght;count++){   //starts with 4 because it needs minimum 4 element to touch its own bodySnake
        if(bodySnake[0].x==bodySnake[count].x&&bodySnake[0].y==bodySnake[count].y) check++;
        if(count==lenght||check!=0) break;
    }
    if(headSnake.x<=10||headSnake.x>=70||headSnake.y<=10||headSnake.y>=30||check!=0){
        life--;

        if(life>=0){
            headSnake.x=25;
            headSnake.y=20;
            bend=0;
            headSnake.direction=R;
            toMove();
        }
        else{
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void eatFood()
{
    if(headSnake.x==food.x&&headSnake.y==food.y){ //it generates food in random places when the snake eats
        lenght++;
        srand(time(0));

        food.x=rand()%70;
        if(food.x<=10) food.x+=11;
        food.y=rand()%30;
        if(food.y<=10) food.y+=11;
    }
    else if(food.x==0) // when start the game
    {
        food.x=rand()%70;
        if(food.x<=10) food.x+=11;
        food.y=rand()%30;
        if(food.y<=10) food.y+=11;
    }
}

// directions commands /////////////////////////////////////////////////////////////////////////////
void Down(){
    int count;

    for(count=0;count<=(headSnake.y-bend[bend].y)&&len<lenght;count++)
    {
        GotoXY(headSnake.x,headSnake.y-count);
        if(len==0) printf("v");
        else printf("*");

        bodySnake[len].x=headSnake.x;
        bodySnake[len].y=headSnake.y-count;
        len++;
    }
    Bend();
    if(!kbhit()) headSnake.y++;
}
void Left(){
    int count;

    for(count=0;count<=(bend[bend].x-headSnake.x)&&len<lenght;count++){
        GotoXY((headSnake.x+count),headSnake.y);
        if(len==0) printf("<");
        else printf("*");

        bodySnake[len].x=headSnake.x+count;
        bodySnake[len].y=headSnake.y;
        len++;
    }
    Bend();
    if(!kbhit()) headSnake.x--;
}
void Right(){
    int count;

    for(count=0;count<=(headSnake.x-bend[bend].x)&&len<lenght;count++){
        bodySnake[len].x=headSnake.x-count;
        bodySnake[len].y=headSnake.y;
        GotoXY(bodySnake[len].x,bodySnake[len].y);
        if(len==0) printf(">");
        else printf("*");
        len++;
    }
    Bend();
    if(!kbhit()) headSnake.x++;
}
void Up(){
   int count;

   for(count=0;count<=(bend[bend].y-headSnake.y)&&len<lenght;count++){
        GotoXY(headSnake.x,headSnake.y+count);
        if(len==0) printf("^");
        else printf("*");

        bodySnake[len].x=headSnake.x;
        bodySnake[len].y=headSnake.y+count;
        len++;
   }
   Bend();
   if(!kbhit()) headSnake.y--;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bend(){
    int i,j,difference;
    for(i=bend;i>=0&&len<lenght;i--){
        if(bend[i].x==bend[i-1].x){
            difference=bend[i].y-bend[i-1].y;
            if(difference<0)
                for(j=1;j<=(-difference);j++){
                    bodySnake[len].x=bend[i].x;
                    bodySnake[len].y=bend[i].y+j;
                    GotoXY(bodySnake[len].x,bodySnake[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
            else if(difference>0)
                for(j=1;j<=difference;j++){
                    bodySnake[len].x=bend[i].x;
                    bodySnake[len].y=bend[i].y-j;
                    GotoXY(bodySnake[len].x,bodySnake[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
            }
            else if(bend[i].y==bend[i-1].y){
                difference=bend[i].x-bend[i-1].x;
                if(difference<0)
                    for(j=1;j<=(-difference)&&len<lenght;j++){
                        bodySnake[len].x=bend[i].x+j;
                        bodySnake[len].y=bend[i].y;
                        GotoXY(bodySnake[len].x,bodySnake[len].y);
                        printf("*");
                        len++;
                        if(len==lenght) break;
                    }
                else if(difference>0)
                    for(j=1;j<=difference&&len<lenght;j++){
                        bodySnake[len].x=bend[i].x-j;
                        bodySnake[len].y=bend[i].y;
                        GotoXY(bodySnake[len].x,bodySnake[len].y);
                        printf("*");
                        len++;
                        if(len==lenght) break;
                    }
             }
   }
}
void printBoarder(){
    system("cls");
    int i;

    // Displaying fruit
    GotoXY(food.x,food.y);
    printf("%c",254);

    // Displaying borders
    for(i=10;i<71;i++){
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10;i<31;i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }

}
void printInitScreen(){
   printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
   getch();
   system("cls");
   printf("\tGame instructions:\n");
   printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the lenght of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's bodySnake.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
   printf("\n\nPress any key to play game...");
   if(getch()==27) exit(0);
   system("cls");
}
void record(){
    char printPastRecords,records;

    getPlayerName();
    addScoreTimeToFile();

    printf("wanna see past records press 'y'\n");
    printPastRecords=getch();
    system("cls");
    if(printPastRecords=='y') printRecords();
}
void addScoreTimeToFile(){
    FILE *info;
    time_t mytime;

    mytime = time(NULL);
    info=fopen("record.txt","a+");
    fprintf(info,"Played Date:%s",ctime(&mytime));
    fprintf(info,"Score:%d\n", Scoreonly());
    fclose(info);
}
char toTurnFirstLetterCapital(char playerName[20]){
    char capitalName[20];
    int count;
    FILE *info;

    //to convert the first letter after space to capital
    for(count=0;playerName[count]!='\0';count++){ 
    capitalName[0]=toupper(playerName[0]);
    if(playerName[count-1]==' '){
    capitalName[count]=toupper(playerName[count]);
    capitalName[count-1]=playerName[count-1];}
    else capitalName[count]=playerName[count];
    }
    capitalName[count]='\0';

    info=fopen("record.txt","a+");
    fprintf(info,"Player Name :%s\n",capitalName);
    fclose(info);

}
void getPlayerName(){
    char playerName[20];

    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",playerName);

    toTurnFirstLetterCapital(playerName);
}
void printRecords(){
    FILE *info; 
    char records;

    info=fopen("record.txt","r");
    do{
        putchar(records=getc(info));
    }while(records!=EOF);
    fclose(info);
}
void statusBar(){
    GotoXY(20,8);
    printf("SCORE : %d",returnScore());
    GotoXY(50,8);
    printf("Life : %d",life);
}
int returnScore(){
    int score;
    score = lenght-5;

    return score;
}

int Scoreonly(){
int score=returnScore();
system("cls");
return score;
}