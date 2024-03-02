#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>                         //按钮响应慢，第二个身体吃掉后会出现卡顿(已解决）
#include <windows.h>                           //随机生成墙和食物慢 内置暂停与右侧画线区域未设置，other按键贴图，rule函数乱码，speed函数边界
#include <conio.h>
#include <time.h>
#include <mmsystem.h>


void movesnake(int j,char s);
void sweep(int *x,int *y);
int start();
void showrule();
int choosespeed();
int rad(int x);

struct Snake
{
    int x[100];
    int y[100];
    int len;
    int derect[100];
} snake;

struct Food
{
    int x;
    int y;
    int a;


} f[100];

struct Well
{
    int x;
    int y;
    int len;
    int derect;
} well[10];

void creatfood(int i);
void eat(int x);
void creatwell();
int rule();
 MUSIC music ;


int main()
{
    snake.derect[0]='s';
    snake.x[0]=30;
    snake.y[0]=30;
    snake.len=1;
    int counter;
    int j=0;
    int flag=1;
    f[0].a=1;
    int speed=1;
    for(counter=1; counter<100; counter++)
    {
        f[counter].a=0;
    }


    int choice = 0;
    while(choice !=1)
    {
        choice = start();
        switch(choice)
        {
        case 1:
            break;
        case 2:
            showrule();
            break;
        case 3:
            speed=choosespeed();
            break;

        }
    }


    initgraph(700, 480);

    setbkcolor(BLUE);
    cleardevice();
    setcolor(WHITE);
    line(640,0,640,480);



    PIMAGE pic;
    pic=newimage(20,20);
    PIMAGE temp;
    temp=newimage();

    getimage(temp,"dj.png");
    int tempwidth =getwidth(temp);
    int temphigh= getheight(temp);

    putimage(pic,0,0,20,20,temp,0,0,tempwidth,temphigh);
    putimage(snake.x[0]-10,snake.y[0]-10,pic);
    delimage(temp);
    temp = NULL;

    creatwell();
    creatfood(0);
    bool zanting=false;
    bool mo=true;
    music.OpenFile("Ava.MP3");
    int i;
    char infor=snake.derect[0];
    while(flag)
    {
        if(!zanting)
        {
            movesnake(snake.len,infor);
        }
       // movesnake(snake.len,infor);
        for(i=0; i<11-speed; i++)
        {
            Sleep(100);
            if(kbhit())
            {
                infor=getch();
                switch(infor)
                {
                case 'w':
                case 'W':
                    snake.derect[0]='w';
                    mo=true;
                    break;
                case 's':
                case 'S':
                    snake.derect[0]='s';
                    mo=true;
                    break;
                case 'A':
                case 'a':
                    snake.derect[0]='a';
                    mo=true;
                    break;
                case 'd':
                case 'D':
                    snake.derect[0]='d';
                    mo=true;
                    break;
                case' ':
                    infor=snake.derect[0];
                    zanting=!zanting;
                default:
                    infor=snake.derect[0];
                    mo=false;
                    break;

                }
            if(mo)
            {
               break;
            }


            }


        }

        flag=rule();
        eat(j);

        for(; j<100; j++)
        {
            if(f[j].a==0)
            {
                creatfood(j+1);
                f[j+1].a=1;
                j++;
                break;
            }
            break;
        }
        fflush(stdin);

    }
    //--------------------------//
    while(!kbhit())
    {
        Sleep(100);
    }
    closegraph();
    return 0;

}
void movesnake(int j,char s)
{

    int i;
    int x=snake.x[0];
    int y= snake.y[0];


    setfillcolor(BLUE);
    bar(snake.x[0]-10,snake.y[0]-10,snake.x[0]+10,snake.y[0]+10);

    switch(s)
    {
    case 'w':
    case 'W':
        snake.y[0]-=20;
        break;
    case 's':
    case 'S':
        snake.y[0]+=20;
        break;
    case 'A':
    case 'a':
        snake.x[0]-=20;
        break;
    case 'd':
    case 'D':
        snake.x[0]+=20 ;
        break;

    }


    for(i=2; i<=j; i++)
    {
        sweep(&snake.x[i-1],&x);
        sweep(&snake.y[i-1],&y);


        setfillcolor(BLUE);
        bar(x-10,y-10,x+10,y+10);

    }




    PIMAGE pic;
    pic=newimage(20,20);
    PIMAGE temp;
    temp=newimage();

    getimage(temp,"dj.png");
    int tempwidth =getwidth(temp);
    int temphigh= getheight(temp);

    putimage(pic,0,0,20,20,temp,0,0,tempwidth,temphigh);
    putimage(snake.x[0]-10,snake.y[0]-10,pic);
    delimage(temp);
    temp = NULL;






    for(i=1; i<=snake.len-1; i++)
    {
        setcolor(GREEN);
        setfillcolor(YELLOW);
        circle(snake.x[i],snake.y[i],10);
        floodfill(snake.x[i], snake.y[i], GREEN);

    }

}

void creatfood(int i)
{
    srand(time(NULL));

    f[i].x =(rand()%29)*20+30;
    f[i].y = rad(f[i].x);
    int counter;



    for(counter=0; counter<snake.len; counter++)
    {
        if(f[i].x==snake.x[counter]&&f[i].y==snake.y[counter])
        {

            f[i].x =(rand()%29)*20+30;
            f[i].y = rad(f[i].x);
        }
    }


    setcolor(GREEN);
    setfillcolor(WHITE);
    circle(f[i].x,f[i].y,10);
    floodfill(f[i].x, f[i].y, GREEN);
}
void eat(int x)
{
    if(snake.x[0]==f[x].x&&snake.y[0]==f[x].y)
    {
        f[x].a=0;
        snake.len=snake.len+1;
        snake.derect[snake.len-1]=snake.derect[snake.len-2];
        switch(snake.derect[snake.len-2])
        {
        case 'w':
        case 'W':
            snake.x[snake.len-1]=snake.x[snake.len-2];
            snake.y[snake.len-1]=snake.y[snake.len-2]+20;
            break;
        case 's':
        case 'S':
            snake.x[snake.len-1]=snake.x[snake.len-2];
            snake.y[snake.len-1]=snake.y[snake.len-2]-20;
        case 'A':
        case 'a':
            snake.x[snake.len-1]=snake.x[snake.len-2]+20;
            snake.y[snake.len-1]=snake.y[snake.len-2];
            break;
        case 'd':
        case 'D':
            snake.x[snake.len-1]=snake.x[snake.len-2]-20;
            snake.y[snake.len-1]=snake.y[snake.len-2];
            break;
        }
        setcolor(GREEN);
        setfillcolor(YELLOW);
        circle(snake.x[snake.len-1],snake.y[snake.len-1],10);
        floodfill(snake.x[snake.len-1],snake.y[snake.len-1],GREEN);


    }
}


void sweep(int *x,int *y)
{
    int tmp;
    tmp=*x;//tmp£½a
    *x=*y;//a£½b
    *y=tmp;//b£½tmp
}

void creatwell()
{
    int counter;
    int counter2;
    int i;
    srand(time(NULL));
    well[0]. x =(rand()%22)*20+30;
    well[0]. y =(rand()%20)*20+50;
    well[0]. len=rand()%3+3;
    for(counter=0; counter<5; counter++)
    {
        for(i=0; i<counter; i++)
        {
            do
            {
                srand(time(NULL)+counter);
                well[counter]. x =(rand()%22)*20+50;
                well[counter]. y =(rand()%20)*20+50;
                well[counter]. len=rand()%3+3;
            }
            while((well[counter].x-well[i].x-well[i].len*20)<=20&&(well[i].x-well[counter].x-well[counter].len*20)<=20&&abs(well[counter].y-well[i].y)<=20);
        }
        for(counter2=0; counter2<well[counter]. len; counter2++)
        {
            setcolor(GREEN);
            setfillcolor(BLACK);
            circle(well[counter].x +counter2*20,well[counter].y,10);
            floodfill(well[counter].x +counter2*20,well[counter].y,GREEN);
        }
    }
    for(counter=5; counter<10; counter++)
    {
        for(i=0; i<counter; i++)
        {
            do
            {
                srand(time(NULL)+counter+5);
                well[counter].x=(rand()%29)*20+50;
                well[counter].y=(rand()%13)*20+50;
                well[counter].len=rand()%3+3;
            }
            while((i<5&&well[counter].x>=(well[i].x-20)&&(well[counter].x-well[i].x-well[i].len*20)<=20&&well[i].y>=(well[counter].y-20)&&(well[i].y-well[counter].y-well[counter].len*20)<=20)||
                    (i>=5&&(well[counter].y-well[i].y-well[i].len*20)<=20&&(well[i].y-well[counter].y-well[counter].len*20)<=20&&abs(well[counter].x-well[i].x)<=20));
        }
        for(counter2=0; counter2<well[counter]. len; counter2++)
        {
            setcolor(GREEN);
            setfillcolor(BLACK);
            circle(well[counter].x,well[counter].y+counter2*20,10);
            floodfill(well[counter].x,well[counter].y+counter2*20,GREEN);
        }
    }

}


int start()
{

    int choice;
    int x,y;
    int flag=1;
    initgraph(640, 500);
    PIMAGE phto;
    phto = newimage();
    getimage(phto, "cfm.jpg");
    putimage(0,0,phto);

    setfillcolor(BLACK);
    bar(180,400,450,500);
    setfont(100, 0, "свт╡");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    outtextxy(200, 400, "MENU");
    bool mark=false;
    mouse_msg msg= {0};
    for (; flag; delay_fps(60))
    {

        while (mousemsg())
        {
            msg=getmouse();


            if(msg.is_left())
            {
                if( msg.is_down())
                {

                    x = msg.x;
                    y= msg.y;

                    mark=((100<x)&&(x<500)&&(300<y)&&(y<500));

                }
                if( msg.is_up()&&mark)
                {
                    flag=0;

                }



            }
        }


    }


    closegraph();


    initgraph(800,428);
    PIMAGE pic;
    pic= newimage();
    getimage(pic,"menu.jpg");
    putimage(0,0,pic);


    setfillcolor(BLACK);
    bar(400,20,650,110);
    setfillcolor(BLACK);
    bar(400,120,650,210);
    setfillcolor(BLACK);
    bar(400,220,650,310);
    setfillcolor(BLACK);
    bar(400,320,650,410);



    setfont(100, 0, "свт╡");
    setcolor(BLUE);
    setbkmode(TRANSPARENT);
    outtextxy(420, 15, "START");
    outtextxy(420, 115, "RULE");
    outtextxy(400, 215, "SPEED");
    outtextxy(400, 315, "OTHER");
    flag=1;
    bool mark1=false;
    bool mark2=false;
    bool mark3=false;
    bool mark4=false;
    mouse_msg msg1= {0};
    for (; flag; delay_fps(60))
    {

        while (mousemsg())
        {
            msg1=getmouse();


            if(msg1.is_left())
            {
                if( msg1.is_down())
                {

                    x = msg1.x;
                    y= msg1.y;

                    mark1=((400<x)&&(x<650)&&(20<y)&&(y<110));
                    mark2=((400<x)&&(x<650)&&(120<y)&&(y<210));
                    mark3=((400<x)&&(x<650)&&(220<y)&&(y<310));
                    mark4=((400<x)&&(x<650)&&(320<y)&&(y<410));

                }
                if( msg1.is_up()&&mark1)
                {
                    flag=0;
                    choice=1;

                }
                if( msg1.is_up()&&mark2)
                {
                    flag=0;
                    choice=2;

                }
                if( msg1.is_up()&&mark3)
                {
                    flag=0;
                    choice=3;

                }
                if( msg1.is_up()&&mark4)
                {
                    flag=0;
                    choice=4;

                }


            }
        }


    }
    closegraph();

    return choice;
}




int rule()
{
    int i;


    for(i=0; i<5; i++)
    {
        if(snake.y[0]==well[i].y)
        {

            if(snake.x[0]<=well[i].x+(well[i].len-1)*20&&snake.x[0]>=well[i].x)
            {
                cleardevice();
                PIMAGE pics;
                pics=newimage();
                getimage(pics,"dead.jpg");
                putimage(0,0,pics);
                music.SetVolume(1);
                music.Play(0);
                setfont(100,0,"幼圆");
                outtextxy(100,100,"GAME OVER");
                setfont(50,0,"幼圆");
                outtextxy(50,350,"PRESS ANY KEY TO CONTINUE");
                setfont(50,0,"幼圆");
                outtextxy(100,250,"GRADE:");
                setfont(50,0,"幼圆");
                xyprintf(250,250,"%d",snake.len);
                return 0;
            }

        }
    }
    for(i=5; i<10; i++)
    {
        if(snake.x[0]==well[i].x)
        {

            if(snake.y[0]<=well[i].y+(well[i].len-1)*20&&snake.y[0]>=well[i].y)
            {
                cleardevice();
                 PIMAGE pics;
                pics=newimage();
                getimage(pics,"dead.jpg");
                 putimage(0,0,pics);
                 music.SetVolume(1);
                music.Play(0);
                setfont(100,0,"幼圆");

                outtextxy(100,100,"GAME OVER");
                setfont(50,0,"幼圆");
                outtextxy(50,350,"PRESS ANY KEY TO CONTINUE");
                setfont(50,0,"幼圆");
                outtextxy(100,250,"GRADE:");
                setfont(50,0,"幼圆");
                xyprintf(250,250,"%d",snake.len);
                return 0;

            }
        }

    }
    if(snake.x[0]<0||snake.x[0]>640||snake.y[0]<0||snake.y[0]>480)
    {
        cleardevice();
        PIMAGE pics;
                pics=newimage();
                getimage(pics,"dead.jpg");
                 putimage(0,0,pics);
        music.SetVolume(1);
                music.Play(0);
        setfont(100,0,"幼圆");

        outtextxy(100,100,"GAME OVER");
        setfont(50,0,"幼圆");
        outtextxy(50,350,"PRESS ANY KEY TO CONTINUE");
        setfont(50,0,"幼圆");
        outtextxy(100,250,"GRADE:");
        setfont(50,0,"幼圆");
        xyprintf(250,250,"%d",snake.len);
        return 0;
    }
    int counter2;
    for(counter2=1; counter2<snake.len; counter2++)
    {
        if(snake.x[0]==snake.x[counter2]&&snake.y[0]==snake.y[counter2])
        {
            cleardevice();
            PIMAGE pics;
                pics=newimage();
                getimage(pics,"dead.jpg");
                 putimage(0,0,pics);
            music.SetVolume(1);
                music.Play(0);
            setfont(100,0,"幼圆");

            outtextxy(100,100,"GAME OVER");
            setfont(50,0,"幼圆");
            outtextxy(50,350,"PRESS ANY KEY TO CONTINUE");
            setfont(50,0,"幼圆");
            outtextxy(100,250,"GRADE:");
            setfont(50,0,"幼圆");
            xyprintf(250,250,"%d",snake.len);
            return 0;
        }
    }
    return 1;
}





void showrule()
{
    initgraph(800,428);


    PIMAGE pic1;
    pic1=newimage();
    getimage(pic1,"j.jpg");
    putimage(0,0,pic1);
    setfillcolor(BLACK);
    bar(75,85,225,125);

    setfont(50,0,"幼圆");
    outtextxy(75,75,"return");
    outtextxy(400,75,"W/w：向上移动");
    outtextxy(400,175,"S/s：向下移动");
    outtextxy(400,275,"A/a：向左移动");
    outtextxy(400,375,"D/d：向右移动");


    int flag=1;
    int x;
    int y;

    bool mark=false;
    mouse_msg msg= {0};
    for (; flag; delay_fps(60))
    {

        while (mousemsg())
        {
            msg=getmouse();


            if(msg.is_left())
            {
                if( msg.is_down())
                {

                    x = msg.x;
                    y= msg.y;

                    mark=((75<x)&&(x<225)&&(85<y)&&(y<125));

                }
                if( msg.is_up()&&mark)
                {
                    flag=0;

                }
            }
        }


    }
}





int choosespeed()
{
    initgraph(340,405);
    PIMAGE pic;
    pic=newimage();
    getimage(pic,"dif.jpg");
    putimage(0,0,pic);


    PIMAGE pic1;
    pic1=newimage(20,20);

    PIMAGE temp;
    temp=newimage();

    getimage(temp,"button.jpg");
    int tempwidth =getwidth(temp);
    int temphigh= getheight(temp);

    putimage(pic1,0,0,20,20,temp,0,0,tempwidth,temphigh);

    delimage(temp);
    temp = NULL;
    setcolor(YELLOW);

    line(20,350,320,350);
    putimage(10,340,pic1);

    setbkcolor(WHITE);
    delay_ms(0);
    setcolor(BLACK);
    setfont(50, 0, "幼圆");
    setbkmode(TRANSPARENT);

    int x,y;
    int flag=1;
    int picx=10;
    int diffculty=1;

    bool mark =true;
    bool paint =true;
    mouse_msg msg= {0};
   while(flag)
    {
      while (mousemsg()){
            msg=getmouse();


            if(msg.is_left())
            {
                if(msg.is_down())
                {
                    x=msg.x;
                    y= msg.y;

                    if(picx<=x&&x<=picx+20&&340<=y&&y<=360)
                    {
                        mark=false;

                        break;
                    }
                    if(10<=x&&x<=160&&50<=y&&y<=100)
                    {
                        flag=0;
                        break;
                    }

                }

            }

            if(!mark)
            {
                picx=msg.x;
                paint=true;
            }
            if(msg.is_up()&&!mark)

           {
                 mark=true;
           }
           if(picx<10)
           {
               picx=10;
           }
            if(picx>310)
           {
               picx=310;
           }
            if (paint)
            {
                putimage(0,0,pic);
                setcolor(YELLOW);
                diffculty=picx/30;
                 line(20,350,320,350);
                putimage(picx,340,pic1);


                outtextxy(10, 00, "diffculty");

                outtextxy(10, 50, "return");
                xyprintf(250,0,"%d",diffculty);
                setcolor(WHITE);
                line(230-(100-diffculty*9),180,230+(100-diffculty*9),180);
                line(230,180-(100-diffculty*9),230,180+(100-diffculty*9));
               circle(230 ,180,100-diffculty*9);
            }
      }

    }


    closegraph();
    return diffculty ;

}


int rad(int x)
{
    int k;
    srand(time(NULL));

    int b[5]= {0,0,0,0,0};
    int c;
    int d;
    for(k=0; k<5; k++)
    {
        if(well[k].x<=x&&well[k].x+(well[k].len-1)*20>=x)
        {
            b[k]=well[k].y;
        }
    }
    for(k=5; k<10; k++)
    {
        if(well[k].x==x)
        {
            c=well[k].y;
            d=well[k].y+well[k].len*20;
        }
    }
    int result=(rand()%21)*20+30;
    while((result>=c&&result<=d)||(result==b[0])||(result==b[1])||(result==b[2])||(result==b[3])||(result==b[4]))
    {
        result=(rand()%21)*20+30;
    }
    return result ;
}
