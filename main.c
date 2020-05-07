#include <stdio.h>
#include<stdlib.h>
#include <Windows.h>
#include<conio.h>
#include<time.h>
#define WIDTH 50
#define HEIGHT 24
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define STAR_NUM 30
#define width 522
#define height 190
typedef struct _Star
{
   int x;
   int y;
   int speed;
}Star;

void clearCursor(){CONSOLE_CURSOR_INFO c= {0};c.dwSize =1;c.bVisible=FALSE;SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);}
void gotoxy(int x,int y){COORD pos={x,y};SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);}
void resizeConsole()
{
   char chTemp[20];
   sprintf(chTemp,
      "Mode con cols=%d lines=%d",width,height);
   system(chTemp);
}
int hx = 240  ,  hy = 70   ;                //    ÇöÀç:x,    ÇöÀç:y 
int direct[4][2]={0,-3,-3,0,3,0,0,3};         //    À§ÂÊ ¿ÞÂÊ ¿À¸¥ÂÊ ¾Æ·¡ ÂÊ 
int display_num=0;                              //     ÇöÀç ³ª´Â °ú¿¬ ¾î¶² Àå¸é¿¡ Á¸ÀçÇÏ´Â°¡ / 0 Àº ¸ðµå¼±ÅÃ / 1Àº µð*°í / 2´Â ¿µ¾î / 3Àº ¼öÇÐ / 4´Â º¸½º·ë/ 5´Â ¾ÆÄÉÀÌµå 
int EXP=1; 
int player_hp;
int monster_hp;
int monster_damage;      ///////////¸ó½ºÅÍ°¡ ÁÖ´Â µ¥¹ÌÁö 

/////////////////////////////////// ÀÌ¹ÌÁö ÆÄÀÏÀ» ÀÔ·Â¹Þ¾Æ Ãâ·ÂÇØÁÖ´Â ÇÁ¸°ÅÍ±â

void print_img(int x, int y, FILE *fp)
{
    int ch[520];
    fseek(fp,SEEK_SET,0);
    gotoxy(x,y);
    while(fgets(ch,519,fp))
    {
        printf("%s",ch);
        gotoxy(x,++y);
    }
}

READ_STORY(FILE *fp)
{
   int x=5,y=9;
   int ch[52];
    fseek(fp,SEEK_SET,0);
    gotoxy(x,y);
    while(fgets(ch,50,fp))
    {
        printf("%s",ch);
        gotoxy(x,(y+=2));
    }
   getch();
}
void print_bound()
{
      int y,x;
   for(y=0;y<26;y++)
   {
      if(y<2)
      {
         puts("");
         continue;
      }
      for(x=0;x<50;x+=2)
      {
         if(y==2||y==25||x==0||x==48)
            printf("¢Þ");
         else
            printf("  ");
      }
   }
}

///////////////////////////////////////////////         ¾Æ·¡ 4°³ÀÇ ÇÔ¼ö´Â    _____¹Ì´Ï°ÔÀÓ ____ ¿µ¾î______
void displayScore(int s)
{
   gotoxy(25,1);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      7);
   printf("Score : %2d",s);
   
}
void clearText(int x,int y)
{
   gotoxy(x,y);
   putchar(32);
}
char displayText(int x,int y,int text)
{
   
   gotoxy(x,y);
   putchar(text);
   return text;
   
}
int MINIGAME_ENGLISH()
{
   Loading();
   srand((unsigned int)time(0));
   int x,y;
   int score=0,cnt=0,i;
   char ch;
   char chTemp[20];
   FILE *pont=fopen("PontSize.txt","r");
   print_img(0,0,pont);
   getch();
   
   fflush(stdin);
   system("cls");
   // ¸®»çÀÌÁî ÄÜ¼Ö  
   sprintf(chTemp,
      "Mode con cols=%d lines=%d",50,26);
   system(chTemp);
   
   //////////////////////////////Å×µÎ¸® Ãâ·Â  
   print_bound();
   /////////////////

   FILE *fp ;
    
   fp = fopen("Eng_Sin.txt", "r");
   
   READ_STORY(fp);/////ÀÌÀüÀÌ¾ß±â 
   system("cls");
   print_bound();
   {
      gotoxy(17,6);
      printf("-ºÐ³ëÀÇ ¾ËÆÄºª-");
      gotoxy(8,8);
      printf("(Àü)¿ä¿ø ¼±»ý´ÔÀÇ");
      gotoxy(8,10);
      printf("ºÐ³ë·ÎÀÎÇØ");
      gotoxy(8,12);
      printf("¾ËÆÄºªÀÌ °øÁß¿¡ ¶°´Ù´Ñ´Ù");
      gotoxy(8,14);
      printf("¶°´Ù´Ï´Â ¾ËÆÄºªÀ» ¸ÂÃßÀÚ");
      gotoxy(8,16);
      printf("start press any key");
      getch();
   }
   system("cls");
   print_bound();
   displayScore(score);
   clearCursor();
   
   srand((unsigned int)time(0));
   
   for(i=0;i<25;i++)
   {
      x= rand()%46+2;//2~47
      y= rand()%22+3;//3~25
      char text= rand()%26+'a'; 
      ch = displayText(x,y,text);
      Sleep(600);
      while(kbhit())
      {
         
         if(getch()==text&&cnt==0)
         {
            score++;
            displayScore(score);   
            cnt=1;
         }
         
      }
      cnt=0;
      clearText(x,y);
   }
   gotoxy(10,13);
   printf("Ã¤Á¡ÁßÀÔ´Ï´Ù Àá½Ã¸¸ ±â´Ù·ÁÁÖ¼¼¿ä!"); 
   Sleep(2000);
   fflush(stdin);
   return score; 
}
////////////////////////////////// ¾Æ·¡ ÇÔ¼öµéÀº __________¹Ì´Ï°ÔÀÓ______¼öÇÐ____
 

void displayStartScreen() {
   while (!kbhit()) {
      gotoxy(11, 13);
      printf("½ÃÀÛÇÏ·Á¸é ¾Æ¹«Å°³ª ´©¸£¼¼¿ä");
      Sleep(400);
      gotoxy(11, 13);
      printf("                            ");
      Sleep(600);
   }
   while (_kbhit()) {
      _getch();
   }
}
void initstar(Star *s)
{
   int i=0;
   for(i=0;i<STAR_NUM;i++)
   {
      s[i].x=rand()%46+2;
      s[i].y=3;
      s[i].speed=rand()%10 +2;
   }
}
void displaystar(Star *s,int count)
{
   int i=0;
   for(i=0;i<STAR_NUM;i++) 
   {
      if(s[i].y>3&&s[i].y<25&& (count)%s[i].speed==0){
         gotoxy(s[i].x,s[i].y-1);   
          printf(" ");
       }
    if(s[i].y>24&& (count)%s[i].speed==0){   
       gotoxy(s[i].x,s[i].y-1);
      printf(" ");
      s[i].x=rand()%46+2;
       s[i].y=3;
       s[i].speed=rand()%7 +3;
   }
   if(count%s[i].speed == 0){
      gotoxy(s[i].x, s[i].y);
      int O=rand()%4; 
       printf(O==0?"+":O==1?"-":O==2?"X":"¡À");
       s[i].y++;
   }   
   }
}
void Smove(int x, int dir)
{
   if(dir==LEFT)
   {
      gotoxy(x+1,24);
      printf(" ");
   }
   else if(dir == RIGHT)
   {
      gotoxy(x-1,24);
      printf(" ");
   }
   gotoxy(x,24);
   printf("¡ã"); 
}
int checkCrush(Star *s,int x){
   int i;
   for(i=0;i<STAR_NUM;i++){
      if(s[i].y == 24 && 
      (s[i].x == x || s[i].x==x+1))
      return 1;
   }
   return 0;
}

int MINIGAME_MATH()
{
   srand(time(NULL));
   int score = 0;
   int count = 0;
   char key;
   int xPosition = WIDTH/2;
   Star s[STAR_NUM];
   
   ///¸®»çÀÌÁî ÄÜ¼Ö  
   char chTemp[50];
   sprintf(chTemp, "Mode con cols=%d lines=%d", 50, 26);
   system(chTemp);
   ///
   clearCursor();
   displayStartScreen();
   system("cls");
   //Å×µÎ¸® 
   print_bound();
   //////
      FILE *fp ;
    
   fp = fopen("Math_Upset.txt", "r");
   
   READ_STORY(fp);/////ÀÌÀüÀÌ¾ß±â 
   system("cls");
   print_bound();
   int y,x;

   /////
   displayScore(score);
   initstar(s);
   Smove(xPosition,0);
   while (score<126) {
      displaystar(s,count);
         if(kbhit())
         {
         key = getch();
         if(key==LEFT)
         {
            if(xPosition>2)
               Smove(--xPosition,LEFT);
         }   
         else if(key==RIGHT)
         {
            if(xPosition< WIDTH-4)
               Smove(++xPosition,RIGHT);
         }
      }
         if (count % 40 == 0) {
         displayScore(score);
         score++;
         count = 0;
      }
      if(checkCrush(s,xPosition)){
         system("cls");
         gotoxy(WIDTH/2-6,HEIGHT/2);
         puts("You Died.");
         gotoxy(WIDTH/2-6,HEIGHT/2+1);
       printf("Score : %d",score);
       break;
     }
      Sleep(10);
      count++;
   }
   gotoxy(10,13);
   printf("Ã¤Á¡ÁßÀÔ´Ï´Ù Àá½Ã¸¸ ±â´Ù·ÁÁÖ¼¼¿ä!"); 
   Sleep(2000);
   return score/25;
}





///////////////////////////////////    ÀÌµ¿Àü ÈçÀûÀ» Áö¿ò  
Clean(int y,int x)      //ÇöÀç Ä¿¼­ À§Ä¡¿¡¼­ µµÆ® »çÀÌÁî¸¸Å­ Áö¿ò 
{
   int i;
   char siz[45];
   for(i=0;i<43;i++)
   {
      siz[i]=' ';
   }
   
   
   
   for(i=0;i<34;i++)
   {
      gotoxy(x,y++);
      printf("%s",siz);
      
   }
   
   
}







///////////////////////////////////¸ÊÀ» ÇÁ¸°Æ®ÇÔ 
print_MAP()
{
   FILE *fp ;

   char arr[522],*res;   

    fp = fopen("maintitle.txt", "r");

   
   while((res=fgets(arr, 514, fp)) != NULL)
   {
      printf("%s",res);
   } fclose(fp);

}
 



////////////////////////////////////    Ä³¸¯ÅÍ¸¦ Ãâ·ÂÇØÁÜ //////////////
Print_Charictor()
{
   FILE *fp;
   
   fp = fopen("charictor.txt", "r");
   
   
   print_img(hx,hy,fp);
   
}


/*À§´Â ±âº»¼Ò½º ¾Æ·¡ºÎÅÍ ¼Ò½º½ÃÀÛ*/




//////////////////////////////////////¿òÁ÷ÀÓÀ» °üÀåÇÏ´Â ¼Ò½º
void move(int dir)
{
   Clean(hy,hx);
   hx+=direct[dir][0];
   hy+=direct[dir][1];
   Print_Charictor();

  
} 






///////////////////////////////////    ÀÌº¥Æ® ¸Ê 




/////////////////// ´ë¸ÁÀÇ ¿£µù
print_img_ENDING(FILE *fp)
{
    int ch[522],i=0;
    int y=0;
    fseek(fp,SEEK_SET,0);
    gotoxy(0,0);
    while(fgets(ch,520,fp))
    {
       i++;
       if(i==4||i==33||i==63||i==92||i==123||i==153)
       {
          Sleep(600);
         while(kbhit()) getch();         /////////////½ºÅä¸® ¸· ³Ñ±â±â ¹æÁö¿ë 
          getch();
      }
        printf("%s",ch);
        gotoxy(0,++y);
    }
    Sleep(1000);
    while(kbhit()) getch();
}




///////////////////////////////////    µð¹Ì°í 
Select_Math()//¼öÇÐ¼±ÅÃ
{
   int score=0;
   int GAIN_EXP;////ÀÌ¹ø °ÔÀÓ¿¡¼­ ¾ò°ÔµÇ´Â °æÇèÄ¡  
   
   score=MINIGAME_MATH();
   system("cls");
   srand((unsigned int)time(0));
   
   while(kbhit()) getch();
   if(score>20)
   {
      GAIN_EXP= 16+rand()%10;
      
      gotoxy(7,8);
      printf("Àå¹®º¹ : ®G ®G ®G ®G ®G  ");
      getch();
      
      gotoxy(13,10);
      printf(" ½´ÆÛ ¸Å¿ì Äª Ãê ®G®G®G "); 
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
   }
   else if(score>16)
   {
      GAIN_EXP= 12+rand()%6;
      
      gotoxy(7,8);
      printf("Àå¹®º¹ : ®G ®G ®G ®G ®G  ");
      getch();
      
      gotoxy(13,10);
      printf(" ¸Å¿ì Äª Ãê ®G®G®G "); 
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
   }
   
   else if(score > 12)
   {
      GAIN_EXP= 7+rand()%4;
         
      gotoxy(11,8);
      puts("Àå*º¹ : Ãß¿¡¿¢");
      getch();
      
      gotoxy(11,10);
      puts(" ®G®G ®G®G¹ö°Å »çµå¸±°Ô¿ä");
      
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
      
   }
      
   else
   {
      GAIN_EXP= rand()%2+1;
      gotoxy(11,7);
      puts("Àå*º¹:  ®G ®G Ãß¿¢ Ãß¿¢ Ãß¿¢");
      getch();
      gotoxy(11,9);
      puts("Ãß¿¢ Ãß¿¢ ÃßÇØ ÃßÇØ ³Ê ³ª°¡");
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
         
   }

   
}

//////////////////¿µ¾î¼±ÅÃ 
Select_English()
{
   int score=0;
   int GAIN_EXP;////ÀÌ¹ø °ÔÀÓ¿¡¼­ ¾ò°ÔµÇ´Â °æÇèÄ¡  
   
   score=MINIGAME_ENGLISH();
   system("cls");
   srand((unsigned int)time(0));
   
   while(kbhit()) getch();
   if(score>16)
   {
      GAIN_EXP= 12+rand()%6;
      
      gotoxy(7,8);
      printf("( Àü)¿ä¿ø : ÀÚ¡æ³×¡é ");
      getch();
      
      gotoxy(13,10);
      printf("¸Å¡é¿ì¡è Äª¡éÂù¡è ÇØÁÖµµ·Ï ÇÏ°Ú³×"); 
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
   }
   else if(score>16)
   {
      GAIN_EXP= 12+rand()%6;
      
      gotoxy(7,8);
      printf("( Àü)¿ä¿ø : ÀÚ¡æ³×¡é ");
      getch();
      
      gotoxy(13,10);
      printf(" Äª¡éÂù¡è ÇØÁÖµµ·Ï ÇÏ°Ú³×"); 
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
   }
   
   else if(score > 12)
   {
      GAIN_EXP= 7+rand()%4;
         
      gotoxy(11,8);
      puts("( Àü)¿ä¿ø : ÀßÇß±º");
      getch();
      
      gotoxy(11,10);
      puts(" ¹¹ ÀÌÁ¤µµ¸é ºÁÁÖµµ·Ï ÇÏÁö¿ä.");
      
      getch();
      
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
      
   }
      
   else
   {
      GAIN_EXP= rand()%2+1;
      gotoxy(11,7);
      puts("³Ê !@#$%$@!#$!%^^#^$^#$^!#@#$@%$!235");
      getch();
      gotoxy(8,9);
      puts("ÃéÅ© Ãß¿¡²ô Ãé¿¡¿¡¿¡¿¡¿¡¿¡²ô#@$!@^^#^$@%");
      getch();
      gotoxy(11,13);
      printf("³ª´Â °æÇèÄ¡ %dÀ» ¾ò¾ú´Ù!\n",GAIN_EXP);
      getch();
      gotoxy(11,15);
      EXP=EXP+GAIN_EXP;
      
      printf("³ªÀÇ °æÇèÄ¡´Â %d°¡ µÇ¾ú´Ù! ",EXP);
      getch();
         
   }

   
}


//////////////////¿£µù¼±ÅÃ  
Select_Ending()
{
   Loading();
   FILE *San=fopen("San.txt","r");
   FILE *ENDING_OPEN=fopen("EndScript_Open.txt","r");
   FILE *NOW_YOUR_ENDING;
   print_img_ENDING(ENDING_OPEN);         //////°øÅë ¿£µù ½ºÅ©¸³Æ® 
   Sleep(800);
   system("cls");
   
   
   print_img(0,0,San);         //////º¸½ºÀÇ »çÁø  
   Sleep(800);
   system("cls");
   
   //////////////////////////
   Loading();
   while(kbhit()) getch();
   
   
   ///////exp ¿¡ µû¶ó ´Ù¸£°Ô º¸¿©Áö´Â ½ºÅ©¸³Æ® 
   if(EXP>20000)
   {
      NOW_YOUR_ENDING=fopen("EndScript_GreatGraduation.txt","r");
   }
   else if(EXP>13000)
   {
      NOW_YOUR_ENDING=fopen("EndScript_Gradiation.txt","r");
   }
   else if(EXP>8000)
   {
      NOW_YOUR_ENDING=fopen("EndScript_Out.txt","r");
   }
   else
   {
      NOW_YOUR_ENDING=fopen("EndScript_Jall.txt","r");
   }
   print_img_ENDING(NOW_YOUR_ENDING);
   
}


/////////////////////////////////////esc Å°¸¦ ´­·¶À» ¶§ ÀÌÀüÈ­¸éÀ¸·Î µ¹¾Æ°¡´Â °Í ±¸Çö 0 Àº ¸ðµå¼±ÅÃ / 1Àº µð*°í / 2´Â ¿µ¾î / 3Àº ¼öÇÐ / 4´Â º¸½º·ë/ 5´Â ¾ÆÄÉÀÌµå
RETURN_DISPLAY()
{
   if(display_num==1||display_num==5)
   {
      
      system("cls");
      display_num=0;
      hx = 240;
      hy = 70;
      print_MAP();
      Print_Charictor();
   }
   else if(display_num==2||display_num==3||display_num==4)
   {
      display_num=1;
      gotoxy(10,13);
      system("cls");
      
      printf("ÆùÆ® Å©±â¸¦ 5·Î Á¶ÀýÇÏ½Ã¿À.");
      getch();
      resizeConsole();
      Loading();
      system("cls");
      FILE *Map;
      Map = fopen("diXgo.txt", "r");
      print_img(0,0,Map);
      hx=20;hy=20;
   }
   else 
   {
      display_num=5;
      system("cls");
      FILE *ar_MAP=fopen("ar_Map.txt","r");
      print_img(0,0,ar_MAP); 
      
   }
}


D_Clean(int y)
{
   int i;
   char siz[150];
   for(i=0;i<140;i++)
   {
      siz[i]=32;
   }
   
   for(i=0;i<15;i++)
   {
      gotoxy(347,y++);
      printf("%s",siz);
      
   }
}


prt_now_hp(int Hp,int HIT)
{
   int hp,hhp,now_x=440;
   FILE *dm;
   FILE *rmove=fopen("Damage_remove.txt","r");
   FILE *HH=fopen("Damage_Hp.txt","r");
   print_img(400,7,HH);
   fclose(HH);
   for(hp=Hp;hp;hp/=10)
   {
      hhp = hp % 10 ;
      if(hhp==0)
         dm=fopen("Damage_0.txt","r");
      else if(hhp==1)
         dm=fopen("Damage_1.txt","r");
      else if(hhp==2)
         dm=fopen("Damage_2.txt","r");
      else if(hhp==3)
         dm=fopen("Damage_3.txt","r");
      else if(hhp==4)
         dm=fopen("Damage_4.txt","r");
      else if(hhp==5)
         dm=fopen("Damage_5.txt","r");
      else if(hhp==6)
         dm=fopen("Damage_6.txt","r");
      else if(hhp==7)
         dm=fopen("Damage_7.txt","r");
      else if(hhp==8)
         dm=fopen("Damage_8.txt","r");
      else if(hhp==9)
         dm=fopen("Damage_9.txt","r");
      print_img(now_x,30,dm);
      now_x-=28;
      fclose(dm);
   }
   getch();
   getch();
   
   print_img(348,34,rmove);
   getch();
   getch();
   D_Clean(30);
   now_x=440;
   Hp-=HIT;
   for(hp=Hp;hp;hp/=10)
   {
      hhp = hp % 10 ;
      if(hhp==0)
         dm=fopen("Damage_0.txt","r");
      else if(hhp==1)
         dm=fopen("Damage_1.txt","r");
      else if(hhp==2)
         dm=fopen("Damage_2.txt","r");
      else if(hhp==3)
         dm=fopen("Damage_3.txt","r");
      else if(hhp==4)
         dm=fopen("Damage_4.txt","r");
      else if(hhp==5)
         dm=fopen("Damage_5.txt","r");
      else if(hhp==6)
         dm=fopen("Damage_6.txt","r");
      else if(hhp==7)
         dm=fopen("Damage_7.txt","r");
      else if(hhp==8)
         dm=fopen("Damage_8.txt","r");
      else if(hhp==9)
         dm=fopen("Damage_9.txt","r");
      print_img(now_x,30,dm);
      now_x-=28;
      fclose(dm);
   }
   getch();
   getch();
   D_Clean(30);
   D_Clean(7);
   while(kbhit()) getch();
   return Hp>0;
}
prt_damage(int dam)
{
   int dmg,now_x=430;
   FILE *dm;
   for(;dam;dam/=10)
   {
      dmg= dam % 10 ;
      if(dmg==0)
         dm=fopen("Damage_0.txt","r");
      else if(dmg==1)
         dm=fopen("Damage_1.txt","r");
      else if(dmg==2)
         dm=fopen("Damage_2.txt","r");
      else if(dmg==3)
         dm=fopen("Damage_3.txt","r");
      else if(dmg==4)
         dm=fopen("Damage_4.txt","r");
      else if(dmg==5)
         dm=fopen("Damage_5.txt","r");
      else if(dmg==6)
         dm=fopen("Damage_6.txt","r");
      else if(dmg==7)
         dm=fopen("Damage_7.txt","r");
      else if(dmg==8)
         dm=fopen("Damage_8.txt","r");
      else if(dmg==9)
         dm=fopen("Damage_9.txt","r");
      print_img(now_x,40,dm);
      now_x-=28;
      fclose(dm);
   }
   getch();
   D_Clean(40);
}



/////////////½Î¿ì´Â Àå¸é ±¸Çö  
int fight(FILE *Boss_image,    FILE *Boss_hit,    FILE *Boss_killed,    FILE *Boss_die)
{
   FILE *Player_Hit=fopen("Player_Hit.txt","r"),*Monster_Hit=fopen("Monster_Hit.txt","r"),*Critical=fopen("Critical.txt","r");
   FILE *Exp_Up=fopen("Exp_Up.txt","r");
   FILE *Obe_DrSword=fopen("Obe_DrSword.txt","r");
   FILE *Obe_Ball=fopen("Obe_Ball.txt","r");
   int attack_key;
   int attack_damage;
   srand(time(NULL));
   int random;
   int n_hp;
   int n_dam;
   
   while(player_hp>0&&monster_hp>0)
   {
      
      system("cls");
      print_img(0,0,Boss_image);
   
      /////ÇÃ·¹ÀÌ¾î°¡ °ø°ÝÇÕ´Ï´Ù.
      attack_key=getch();
      /////////////////esc µµ Ãß°¡
      if(attack_key==27)
      {
         RETURN_DISPLAY();
         return 0;
      }
      else if(attack_key=='q')            ///////²¿Áý°í ¶§¸®°í ÇÒÄû±â 
      {
         attack_damage = 47 + rand()%8 + EXP/100;
      }
      else if(attack_key=='w')         /////// ƒÆ¹°±â 
      {
         attack_damage = 40 + rand()%23 + EXP/100;
      }
      else if(attack_key=='e')          //////// ½´ÆÛ ²¿Áý°í ¶§¸®°í ÇÒÄû°í ±ú¹°±â 
      {
         attack_damage = 20 + rand()%64 + EXP/100;
      }
      else if(attack_key=='r')         ///////°­·ÁÅ©ÇÑ ±Þ¼Ò ³ë¸®±â 
      {
         attack_damage = rand()%99 + EXP/100;
      }
      else
         continue;
         
      n_dam=attack_damage;
      n_hp=monster_hp;
      system("cls");
      print_img(0,0,Boss_hit);
      prt_damage(n_dam);
      monster_hp = monster_hp - attack_damage;
      
      Sleep(300);
      print_img(0,150,Monster_Hit);
      if(!prt_now_hp(n_hp,n_dam))
      {
         break;
      }
      
      Sleep(800);
      system("cls");
      
      if(display_num==8)
      {
         if(rand()%1000==103)         ////////   0.1ÆÛ¼¾Æ®ÀÇ È®·ü·Î Áï»ç 
         {
            player_hp=0;
            system("cls");
            print_img(0,0,Obe_DrSword);
            Sleep(2000);
            continue;   
         }
         
         system("cls");
         print_img(0,0,Boss_image);
         Sleep(200);
         system("cls");
         print_img(0,0,Obe_Ball);
         
      }
      else
      {
         print_img(0,0,Boss_image);
      }
      
      n_dam=monster_damage;
      n_hp=player_hp;
      Sleep(300);
      print_img(0,150,Player_Hit);
      prt_damage(n_dam);
      
      player_hp = player_hp - monster_damage;
      Sleep(300);
      prt_now_hp(n_hp,n_dam);
      Sleep(800);
      while(kbhit()) getch();
   }
   
   
   //////¸®ÅÏ ÇÃ·¡ÀÌ¾î ½Â :  1    ////    ¸ó½ºÅÍ ½Â :  0 
   if(monster_hp>0)
   {
      FILE *You_Lose=fopen("You_Lose.txt","r");
      
      system("cls");
      
      print_img(0,0,You_Lose);
      
      Sleep(3000);
      RETURN_DISPLAY();
      return 0;
   }
   else
   {
      system("cls");
      Sleep(300);
      print_img(0,0,Boss_killed);
      
      Sleep(3000);
      system("cls");
      print_img(0,0, Boss_die);
      Sleep(2000);
      system("cls");
      print_img(0,66,Exp_Up);
      Sleep(1000);
      system("cls");
      RETURN_DISPLAY();
      return 1;
   }
   
}




///////////////////////////////////    ¾îµåº¥Ã³
int adventure()
{

   FILE *Boss_image,*Boss_hit,*Boss_killed,*Boss_die;
   
   int sel_num,win_lose;

   player_hp=100+EXP/10;

   sel_num = getch();
   if(sel_num==27||sel_num == '1'||sel_num == '2'||sel_num == '3'||sel_num == '4')
   {
      if(sel_num==27)
      {
         RETURN_DISPLAY();
         return 0;
      }
      else if(sel_num == '1')
      {
         display_num=6;
         Boss_image=fopen("Mushroom_Spone.txt","r");
         Boss_hit=fopen("Mushroom_Fall.txt","r");
         Boss_killed=fopen("Mushroom_Fall.txt","r");
         Boss_die=fopen("Mushroom_Kill.txt","r");
         monster_hp = 600;
         monster_damage = 5-EXP/100;
         win_lose = fight(Boss_image,Boss_hit,Boss_killed,Boss_die);
         if(win_lose == 1)
         {
            EXP += 70 +rand()%16;
         }
         if(win_lose == 0)
         {
            EXP += 2 ; 
         }
         
      }
      else if(sel_num == '2')
      {
         Boss_image=fopen("Gumi_Spone.txt","r");
         Boss_hit=fopen("Gumi_Broken.txt","r");
         Boss_killed=fopen("Gumi_Broken","r");
         Boss_die=fopen("Gumi_Die.txt","r");
         display_num=7;
         
         monster_hp = 1400;
         monster_damage = 8-EXP/100;
         win_lose = fight(Boss_image,Boss_hit,Boss_killed,Boss_die);
         if(win_lose == 1)
         {
            EXP += 190 +rand()%80;
         }
         if(win_lose == 0)
         {
            EXP += 4 ; 
         }
      }
      else if(sel_num == '3')
      {
         display_num=8;
         Boss_image=fopen("Obe_Spone.txt","r");
         Boss_hit=fopen("Obe_Hit.txt","r");
         Boss_killed=fopen("Obe_Hit.txt","r");
         Boss_die=fopen("Obe_Die.txt","r");
         monster_hp = 9999;
         monster_damage = 100-EXP/100;
         win_lose = fight(Boss_image,Boss_hit,Boss_killed,Boss_die);
         if(win_lose == 1)
         {
            EXP += 8000 +rand()%1000;
         }
         if(win_lose == 0)
         {
            EXP += 14 ; 
         }
         
      }
      else if(sel_num == '4')
      {
         display_num=9;
         
         Boss_image=fopen("dragon.txt","r");
         Boss_hit=fopen("Dragon_Hit.txt","r");
         Boss_killed=fopen("Dragon_Kill.txt","r");
         Boss_die=fopen("Dragon_Die.txt","r");
         monster_hp = 6666;
         monster_damage = 30-EXP/100;
         win_lose = fight(Boss_image,Boss_hit,Boss_killed,Boss_die);
         if(win_lose == 1)
         {
            EXP += 4000 +rand()%2000;
         }
         if(win_lose == 0)
         {
            EXP += 17 ; 
         }
      }
   }
   adventure(); 
   
}




///////////////////////////////////    µð¹®°í



//////////////////////////////////// ½É½ÉÇÏÁö ¸»¶ó°í ¸¸µç ½Ã°¢Àû È¿°ú¸¦ ºÎ¿©ÇÑ ·ÎµùÈ­¸é

Loading()
{FILE *LU=fopen("Sq_LU.txt","r"),*LURD=fopen("Sq_LU,RD.txt","r"),*LRD=fopen("Sq_L,RD.txt","r"),*ABL=fopen("Sq_ABL.txt","r");FILE *MID=fopen("Sq_NoMid.txt","r"),*MID_=fopen("Sq_NoMidBig.txt","r"),*MID__=fopen("Sq_NoMidSmall.txt","r");system("cls");print_img(0,0,LU);system("cls");print_img(0,0,LURD);system("cls");print_img(0,0,LRD);system("cls");print_img(0,0,ABL);system("cls");print_img(0,0,MID);system("cls");print_img(0,0,MID_);system("cls");print_img(0,0,MID__);system("cls");}
 
 
 
 

///////////////////////////////////// Å°°Ë»ç 

int Key_Gumsa()
{
   if(display_num==0)
   {
      if(hx>=316&&hy>=49&&hx<=462&&hy<=121)           ///////////////////¿©±â¿¡ ·£´ýÀ¸·Î µð¹®°í°¡´Â°Å Ãß°¡ 
      {
         display_num=1;
         system("cls");
         FILE *Map;
         Map = fopen("diXgo.txt", "r");
         print_img(0,0,Map);
         hx=20;hy=20;
      }
      else if(hx>=50&&hy>=49&&hx<=196&&hy<=121)    
      {
         display_num=5;
         system("cls");
         Loading();
         while(kbhit()) getch();
         FILE *ar_MAP=fopen("ar_Map.txt","r");
         print_img(0,0,ar_MAP); 
         adventure();
      }
   }
   
   else if(display_num==1)
   {
      if( hx>=296 && hx<=508 && hy>=89 && hy<=145 )   ///¿µ¾î 
      {
         display_num=2;
         system("cls");
         Select_English(); 
                                     /////¿©±â ¿µ¾î   
      }
      else if( hx>=4 && hx<=232 && hy>=60 && hy<=126 )     ///¼öÇÐ 
      {
         display_num=3;
         system("cls");                                /////¿©±â ¼öÇÐ
         Select_Math();
      }
      
      
      else if( hx>=201 && hx<=506 && hy>=4 && hy<=43 )     ///º¸½º·ë 
      {
         display_num=3;
         system("cls");                                /////¿©±â º¸½º·ë (=¿£µù)
         Select_Ending(); 
      }
   }
   
}
 


/////////              main           /////////////////////////////////////////

main()
{
   
   int Key;
   clearCursor();
   resizeConsole();
   Loading();
   print_MAP();
   Print_Charictor();

   
   while(1)      
   {
      
      while(kbhit())
      {
         Key=getch();
         if((hy>6&&Key==UP)||(hx>7&&Key==LEFT)||(hx<460&&Key==RIGHT)||(hy<105&&Key==DOWN))
         {
            Key=Key==UP?0:Key==LEFT?1:Key==RIGHT?2:3;        ///////¿©±â¼­ Å°´Â ÀÌµ¿ÇÏ´Âµ¥¿¡ Áß¿äÇÑ ¿­¼è°¡ µÉ °ÍÀÓ  
            move(Key);
         }
         else if(Key=='a'||Key=='A')
         {
            Key_Gumsa();
         }
         else if(Key==27)      ////////////////////////////esc Å°´Â 27ÀÓ 
         {
             RETURN_DISPLAY();  ///////////////ÀÌÀüÈ­¸éÀ¸·Î µ¹¾Æ°¨  
         }
         
      }
   }
   
   
   
   getchar();
   
   
}
