//snake game in c

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define U 72 //up
#define D 80 //down
#define L 75 //left
#define R 77 //right

int lenght;
int bend;
int len;
char k;
int life;

struct coordinate{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int main(){
    char k;

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
<<<<<<< HEAD
void toMove(){
    int k,z;
=======
void Move(){
    int key,count;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401

    do{
        Food();
        fflush(stdin); // clean buffer
        len=0;

<<<<<<< HEAD
        for(z=0;z<30;z++){
            body[z].x=0;
            body[z].y=0;
            if(z==lenght) break;
=======
        for(count=0;count<30;count++){
            body[count].x=0;
            body[count].y=0;
            if(count==lenght) break;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        }

        toDelay();
        Boarder();

        if(head.direction==R) Right();
        else if(head.direction==L) Left();
        else if(head.direction==D) Down();
        else if(head.direction==U) Up();
        toCheckExitGameCondition();
    }while(!kbhit()); // kbhit => verify if a k have been pressed.

    k=getch();
    if(k==27){
        system("cls");
        exit(0);
    }
    // bend increment
    if(
<<<<<<< HEAD
    (k==R&&head.direction!=L&&head.direction!=R)||
    (k==L&&head.direction!=R&&head.direction!=L)||
    (k==U&&head.direction!=D&&head.direction!=U)||
    (k==D&&head.direction!=U&&head.direction!=D)){

        bend++;
        bend[bend]=head;
        head.direction=k;

        //It moves the snack
        if(k==U) head.y--;
        if(k==D) head.y++;
        if(k==R) head.x++;
        if(k==L) head.x--;
=======
    (key==R&&head.direction!=L&&head.direction!=R)||
    (key==L&&head.direction!=R&&head.direction!=L)||
    (key==U&&head.direction!=D&&head.direction!=U)||
    (key==D&&head.direction!=U&&head.direction!=D)){

        bend++;
        bend[bend]=head;
        head.direction=key;

        //It moves the snack
        if(key==U) head.y--;
        if(key==D) head.y++;
        if(key==R) head.x++;
        if(key==L) head.x--;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401

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
<<<<<<< HEAD
void loadScreen(){
	int load;
=======
void load(){
	int loadComponent;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401

    gotoxy(36,14);
    printf("loading...");

    gotoxy(30,15);

    for (load = 1; load <= 20; load++){
        sleep(2/3);
        printf("%c",177);
    }

    getch();
}
void toDelay(){
    statusBar();
    long double z;
    for(z=0;z<=(10000000);z++); //sleep very fast but not so much
}
void toCheckExitGameCondition(){
<<<<<<< HEAD
    int z,check=0;
    for(z=4;z<lenght;z++){   //starts with 4 because it needs minimum 4 element to touch its own body
        if(body[0].x==body[z].x&&body[0].y==body[z].y) check++;
        if(z==lenght||check!=0) break;
=======
    int count,check=0;
    for(count=4;count<lenght;count++){   //starts with 4 because it needs minimum 4 element to touch its own body
        if(body[0].x==body[count].x&&body[0].y==body[count].y) check++;
        if(count==lenght||check!=0) break;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0){
        life--;

        if(life>=0){
            head.x=25;
            head.y=20;
            bend=0;
            head.direction=R;
<<<<<<< HEAD
            toMove();
=======
            Move();
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        }
        else{
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any k to quit the game\n");
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
    int z;

<<<<<<< HEAD
    for(z=0;z<=(head.y-bend[bend].y)&&len<lenght;z++)
    {
        GotoXY(head.x,head.y-z);
=======
    for(count=0;count<=(head.y-bend[bend].y)&&len<lenght;count++)
    {
        GotoXY(head.x,head.y-count);
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        if(len==0) printf("v");
        else printf("*");

        body[len].x=head.x;
<<<<<<< HEAD
        body[len].y=head.y-z;
=======
        body[len].y=head.y-count;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        len++;
    }
    Bend();
    if(!kbhit()) head.y++;
}
void Left(){
    int z;

<<<<<<< HEAD
    for(z=0;z<=(bend[bend].x-head.x)&&len<lenght;z++){
        GotoXY((head.x+z),head.y);
        if(len==0) printf("<");
        else printf("*");

        body[len].x=head.x+z;
=======
    for(count=0;count<=(bend[bend].x-head.x)&&len<lenght;count++){
        GotoXY((head.x+count),head.y);
        if(len==0) printf("<");
        else printf("*");

        body[len].x=head.x+count;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit()) head.x--;
}
void Right(){
    int z;

<<<<<<< HEAD
    for(z=0;z<=(head.x-bend[bend].x)&&len<lenght;z++){
        body[len].x=head.x-z;
=======
    for(count=0;count<=(head.x-bend[bend].x)&&len<lenght;count++){
        body[len].x=head.x-count;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
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
   int z;

<<<<<<< HEAD
   for(z=0;z<=(bend[bend].y-head.y)&&len<lenght;z++){
        GotoXY(head.x,head.y+z);
=======
   for(count=0;count<=(bend[bend].y-head.y)&&len<lenght;count++){
        GotoXY(head.x,head.y+count);
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        if(len==0) printf("^");
        else printf("*");

        body[len].x=head.x;
<<<<<<< HEAD
        body[len].y=head.y+z;
=======
        body[len].y=head.y+count;
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
        len++;
   }
   Bend();
   if(!kbhit()) head.y--;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Bend(){
    int i,j,d;
    for(i=bend;i>=0&&len<lenght;i--){
        if(bend[i].x==bend[i-1].x){
<<<<<<< HEAD
            d=bend[i].y-bend[i-1].y;
            if(d<0)
                for(j=1;j<=(-d);j++){
=======
            difference=bend[i].y-bend[i-1].y;
            if(difference<0)
                for(j=1;j<=(-difference);j++){
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
<<<<<<< HEAD
            else if(d>0)
                for(j=1;j<=d;j++){
=======
            else if(difference>0)
                for(j=1;j<=difference;j++){
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==lenght) break;
                }
            }
            else if(bend[i].y==bend[i-1].y){
<<<<<<< HEAD
                d=bend[i].x-bend[i-1].x;
                if(d<0)
                    for(j=1;j<=(-d)&&len<lenght;j++){
=======
                difference=bend[i].x-bend[i-1].x;
                if(difference<0)
                    for(j=1;j<=(-difference)&&len<lenght;j++){
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
                        body[len].x=bend[i].x+j;
                        body[len].y=bend[i].y;
                        GotoXY(body[len].x,body[len].y);
                        printf("*");
                        len++;
                        if(len==lenght) break;
                    }
<<<<<<< HEAD
                else if(d>0)
                    for(j=1;j<=d&&len<lenght;j++){
=======
                else if(difference>0)
                    for(j=1;j<=difference&&len<lenght;j++){
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
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
<<<<<<< HEAD
void printInitScreen(){
   printf("\tWelcome to the mini Snake game.(press any k to continue)\n");
   getch();
   system("cls");
   printf("\tGame instructions:\n");
   printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the lenght of the snake will be increased by 1 element and thus the pts.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any k. To continue the paused game press any other k once again\n\n-> If you want to exit press esc. \n");
   printf("\n\nPress any k to play game...");
=======
void Screen(){
   printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
   getch();
   system("cls");
   printf("\tGame instructions:\n");
   printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the lenght of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
   printf("\n\nPress any key to play game...");
>>>>>>> cd3daf7e95be11cc84ff2d8dc9885eedd21e1401
   if(getch()==27) exit(0);
   system("cls");
}
void record(){
    char precord,rec;

    getPlayerName();
    addScoreTimeToFile();

    printf("wanna see past rec press 'y'\n");
    precord=getch();
    system("cls");
    if(precord=='y') printRecords();
}
void addScoreTimeToFile(){
    FILE *inf;
    time_t mytime;

    mytime = time(NULL);
    inf=fopen("record.txt","a+");
    fprintf(inf,"Played Date:%s",ctime(&mytime));
    fprintf(inf,"Score:%d\n", Scoreonly());
    fclose(inf);
}
char toTurnFirstLetterCapital(char pname[20]){
    char mxname[20];
    int z;
    FILE *inf;

    //to convert the first letter after space to capital
    for(z=0;pname[z]!='\0';z++){ 
    mxname[0]=toupper(pname[0]);
    if(pname[z-1]==' '){
    mxname[z]=toupper(pname[z]);
    mxname[z-1]=pname[z-1];}
    else mxname[z]=pname[z];
    }
    mxname[z]='\0';

    inf=fopen("record.txt","a+");
    fprintf(inf,"Player Name :%s\n",mxname);
    fclose(inf);

}
void getPlayerName(){
    char pname[20];

    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",pname);

    toTurnFirstLetterCapital(pname);
}
void printRecords(){
    FILE *inf; 
    char rec;

    inf=fopen("record.txt","r");
    do{
        putchar(rec=getc(inf));
    }while(rec!=EOF);
    fclose(inf);
}
void statusBar(){
    GotoXY(20,8);
    printf("SCORE : %d",returnScore());
    GotoXY(50,8);
    printf("Life : %d",life);
}
int returnScore(){
    int pts;
    pts = lenght-5;

    return pts;
}

int Scoreonly(){
int pts=returnScore();
system("cls");
return pts;
}