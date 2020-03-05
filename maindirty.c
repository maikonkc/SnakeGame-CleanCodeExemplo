//snake game in c

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define U 72 //down
#define D 80 //up
#define L 75 //right
#define R 77 //left

int lenght; //length
int bend;   //bend
int len;    //len
char key;   //key
int life;   //life

struct coordinate{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int main(){
    char key;

    Screen();
    load();

    lenght=5;
    head.x=25;
    head.y=20;
    head.direction=R;

    Boarder();
    Food();

    life=3;
    bend[0]=head;

    Move();

    return 0;
}
void Move(){
    int key,count;

    do{
        Food();
        fflush(stdin); 
        len=0;

        for(count=0;count<30;count++){
            body[count].x=0;
            body[count].y=0;
            if(count==lenght) break;
        }

        toDelay();
        Boarder();

        if(head.direction==R) Right();
        else if(head.direction==L) Left();
        else if(head.direction==D) Down();
        else if(head.direction==U) Up();
        toCheckExitGameCondition();
    }while(!kbhit()); 

    key=getch();
    if(key==27){
        system("cls");
        exit(0);
    }
    // bend increment
    if(
    (key==R&&head.direction!=L&&head.direction!=R)||
    (key==L&&head.direction!=R&&head.direction!=L)||
    (key==U&&head.direction!=D&&head.direction!=U)||
    (key==D&&head.direction!=U&&head.direction!=D)){

        bend++;
        bend[bend]=head;
        head.direction=key;

        //It makes the snake stop
        if(key==U) head.y--;
        if(key==D) head.y++;
        if(key==R) head.x++;
        if(key==L) head.x--;

        Move();
    }else{
        printf("\a");
        Move();
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
void load(){
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
    for(count=4;count<lenght;count++){   //starts with 4 because it needs minimum 4 element to touch its own body
        if(body[0].x==body[count].x&&body[0].y==body[count].y) check++;
        if(count==lenght||check!=0) break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0){
        life--;

        if(life>=0){
            head.x=25;
            head.y=20;
            bend=0;
            head.direction=R;
            Move();
        }
        else{
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y){ //it generates food in random places when the snake eats
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

    for(count=0;count<=(head.y-bend[bend].y)&&len<lenght;count++)
    {
        GotoXY(head.x,head.y-count);
        if(len==0) printf("v");
        else printf("*");

        body[len].x=head.x;
        body[len].y=head.y-count;
        len++;
    }
    Bend();
    if(!kbhit()) head.y++;
}
void Left(){
    int count;

    for(count=0;count<=(bend[bend].x-head.x)&&len<lenght;count++){
        GotoXY((head.x+count),head.y);
        if(len==0) printf("<");
        else printf("*");

        body[len].x=head.x+count;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit()) head.x--;
}
void Right(){
    int count;

    for(count=0;count<=(head.x-bend[bend].x)&&len<lenght;count++){
        body[len].x=head.x-count;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        if(len==0) printf(">");
        else printf("*");
        len++;
    }
    Bend();
    if(!kbhit()) head.x++;
}
void Up(){
   int count;

   for(count=0;count<=(bend[bend].y-head.y)&&len<lenght;count++){
        GotoXY(head.x,head.y+count);
        if(len==0) printf("^");
        else printf("*");

        body[len].x=head.x;
        body[len].y=head.y+count;
        len++;
   }
   Bend();
   if(!kbhit()) head.y--;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bend(){
    int i,j,difference;
    for(i=bend;i>=0&&len<lenght;i--){
        if(bend[i].x==bend[i-1].x){
            difference=bend[i].y-bend[i-1].y;
            if(difference<0)
                for(j=1;j<=(-difference);j++){
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
            else if(difference>0)
                for(j=1;j<=difference;j++){
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
            }
            else if(bend[i].y==bend[i-1].y){
                difference=bend[i].x-bend[i-1].x;
                if(difference<0)
                    for(j=1;j<=(-difference)&&len<lenght;j++){
                        body[len].x=bend[i].x+j;
                        body[len].y=bend[i].y;
                        GotoXY(body[len].x,body[len].y);
                        printf("*");
                        len++;
                        if(len==lenght) break;
                    }
                else if(difference>0)
                    for(j=1;j<=difference&&len<lenght;j++){
                        body[len].x=bend[i].x-j;
                        body[len].y=bend[i].y;
                        GotoXY(body[len].x,body[len].y);
                        printf("*");
                        len++;
                        if(len==lenght) break;
                    }
             }
   }
}
void Boarder(){
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
void Screen(){
   printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
   //It says to screeen: Welcome to the mini Snake Game.(Press any key to continue)
   getch();
   system("cls");
   //It Clears to screen
   printf("\tGame instructions:\n");
   //It says: Game Instructions
   printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the lenght of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
   //It says -> Use arrow keys to move the snake. -> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the lenght of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc.
   printf("\n\nPress any key to play game...");
   //It says Press any key to play game...
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
    //It opens the file to update
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //It shows the date when you played the game
    fprintf(info,"Score:%d\n", Scoreonly());
    //It shows the Score's player
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
    //This function gets the player's name
    char playerName[20];

    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",playerName);

    toTurnFirstLetterCapital(playerName);
}
void printRecords(){
    //This function prints the record
    FILE *info; 
    char records;

    info=fopen("record.txt","r");
    do{
        putchar(records=getc(info));
    }while(records!=EOF);
    fclose(info);
}
void statusBar(){
    //This Function shows the status bar
    GotoXY(20,8);
    printf("SCORE : %d",returnScore());
    GotoXY(50,8);
    printf("Life : %d",life);
}
int returnScore(){
    //This Function returns the Score
    int score;
    score = lenght-5;

    return score;
}

int Scoreonly(){
int score=returnScore();
system("cls");
return score;
}