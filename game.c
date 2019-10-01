#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "game.h"

int plate[hight][weidth]={0};


int tank_shape[4][9]=
{
    {
        0,5,0,
        4,5,4,
        4,6,4
    },
    {
        4,4,0,
        6,5,5,
        4,4,0
    },
    {
        4,6,4,
        4,5,4,
        0,5,0
    },
    {
        0,4,4,
        5,5,6,
        0,4,4
    }
};
int boss_shape[4][36]=
{
    {
        0,0,5,5,0,0,
        0,0,5,5,0,0,
        4,4,5,5,4,4,
        4,4,5,5,4,4,
        4,4,6,6,4,4,
        4,4,6,6,4,4
    },
    {
        4,4,4,4,0,0,
        4,4,4,4,0,0,
        6,6,5,5,6,6,
        6,6,5,5,6,6,
        4,4,4,4,0,0,
        4,4,4,4,0,0
    },
    {
        4,4,6,6,4,4,
        4,4,6,6,4,4,
        4,4,5,5,4,4,
        4,4,5,5,4,4,
        0,0,5,5,0,0,
        0,0,5,5,0,0

    },
    {
        0,0,4,4,4,4,
        0,0,4,4,4,4,
        5,5,5,5,6,6,
        5,5,5,5,6,6,
        0,0,4,4,4,4,
        0,0,4,4,4,4
    }
};


int game1(void)
{
    clearScreen();
    int i=1,k,count=0;
    int kill=0,totalkill=0,flag;

    int key_val[NUM_KEYS1] = {VK_A, VK_S, VK_D, VK_W, VK_SPACE,VK_Q};

    tank *all_tank;
    bullet nb[500];
    Pausescreen pauses;

    setpause(&pauses);
    openAudioFile("hit.wav", &efx[0]);
    openAudioFile("door.wav", &efx[1]);
    openAudioFile("boom.wav", &efx[2]);
    openAudioFile("bgm.wav", &efx[3]);
    srand(time(NULL));
    playAudio(&efx[3]);

    while(1)
    {
        flag=1;
        all_tank=(tank*)malloc(i*NUM_TANK*sizeof(tank));
        boundary();
        map(i+'0');
        getank(all_tank,0,i*NUM_TANK);
        while(1)
        {
            clearScreen();
            walls();
            if(count)
                flying(nb,all_tank,count,i);
            kill=0;
            for(k=0;k<i*NUM_TANK;k++)
            {
                if(all_tank[k].flag)
                    showtank(all_tank,k);
                else
                    kill++;
            }
            lifebar1(all_tank);
            drawCmdWindow();
            if(all_tank[0].flag==0)
            {
                free(all_tank);
                pauseAudio(&efx[3]);
                return totalkill+kill;
            }
            if(kill==i*NUM_TANK-1)
            {
                if(flag)
                {
                    flag=0;
                    playAudio(&efx[1]);
                }
                for(k=1;k<4;k++)
                    plate[k][weidth-1]=0;
            }
            if(all_tank[0].x+3>=weidth)
            {
                free(all_tank);
                totalkill+=kill;
                i++;
                Sleep(200);
                break;
            }
            Sleep(100);
            enemies(all_tank,nb,&count,i);

            for (k=0; k<NUM_KEYS1; k++)
            {
                if(KEY_DOWN(key_val[k]) )
                {
                    switch (key_val[k])
                    {
                    case VK_A:
                        all_tank[0].direction=3;
                        turn(all_tank);
                        if(check(all_tank[0],3))all_tank[0].x--;
                        break;
                    case VK_S:
                        all_tank[0].direction=2;
                        turn(all_tank);
                        if(check(all_tank[0],2))all_tank[0].y++;
                        break;
                    case VK_D:
                        all_tank[0].direction=1;
                        turn(all_tank);
                        if(check(all_tank[0],1))all_tank[0].x++;
                        break;
                    case VK_W:
                        all_tank[0].direction=0;
                        turn(all_tank);
                        if(check(all_tank[0],0))all_tank[0].y--;
                        break;
                    case VK_Q:
                        saveScreen();
                        if(pause(&pauses))
                            {
                                pauseAudio(&efx[3]);
                                return -2;
                            }
                        break;
                    case VK_SPACE:
                        shoot(nb,all_tank[0],count++,0);
                        if(count==500)count=1;
                        break;
                    }
                }
            }
        }
    if(i==stage)
    {
        all_tank=(tank*)malloc(2*sizeof(tank));

        boundary();
        map(i+'0');
        getank(all_tank,0,1);
        getboss(all_tank+1);
        while(1)
        {
            clearScreen();
            walls();
            if(count)
                flying(nb,all_tank,count,i);
            if(all_tank[1].flag)
                showboss(all_tank+1);
            showtank(all_tank,0);
            lifebar1(all_tank);
            lifebarb(all_tank);
            drawCmdWindow();
            if(all_tank[0].flag==0)
            {
                free(all_tank);
                pauseAudio(&efx[3]);
                return totalkill;
            }
            if(!all_tank[1].flag)
            {
                free(all_tank);
                pauseAudio(&efx[3]);
                return -1;
            }
            Sleep(100);
            boss(all_tank,nb,&count);

            for (k=0; k<NUM_KEYS1; k++)
            {
                if(KEY_DOWN(key_val[k]) )
                {
                    switch (key_val[k])
                    {
                    case VK_A:
                        all_tank[0].direction=3;
                        turn(all_tank);
                        if(check(all_tank[0],3))all_tank[0].x--;
                        break;
                    case VK_S:
                        all_tank[0].direction=2;
                        turn(all_tank);
                        if(check(all_tank[0],2))all_tank[0].y++;
                        break;
                    case VK_D:
                        all_tank[0].direction=1;
                        turn(all_tank);
                        if(check(all_tank[0],1))all_tank[0].x++;
                        break;
                    case VK_W:
                        all_tank[0].direction=0;
                        turn(all_tank);
                        if(check(all_tank[0],0))all_tank[0].y--;
                        break;
                    case VK_Q:
                        saveScreen();
                        if(pause(&pauses))
                        {
                            pauseAudio(&efx[3]);
                            return -2;
                        }
                        break;
                    case VK_SPACE:
                        shoot(nb,all_tank[0],count++,0);
                        if(count==500)count=1;
                        break;
                    }
                }
            }
        }
    }
    }
}
int game2(void)
{
    clearScreen();
    int k,count=0;
    int offset_ys,offset_xs,offset_y,offset_x,
        offset_ys2,offset_xs2,offset_y2,offset_x2;
    int key_val[NUM_KEYS2] = {VK_A, VK_S, VK_D, VK_W, VK_SPACE, VK_LEFT, VK_DOWN, VK_RIGHT, VK_UP, VK_P,  VK_Q};

    tank all_tank[2];
    bullet nb[500];
    Pausescreen pauses;

    setpause(&pauses);
    openAudioFile("hit.wav", &efx[0]);
    openAudioFile("boom.wav", &efx[2]);
    openAudioFile("bgm.wav", &efx[3]);
    srand(time(NULL));

    boundary();
    map('6');
    getank(all_tank,0,2);
    all_tank[0].death=0;
    all_tank[1].death=0;
    playAudio(&efx[3]);


    while(1)
    {
        offset_ys=(all_tank[0].y-phight>0?all_tank[0].y-phight:0);
        offset_xs=(all_tank[0].x-pwitdth>0?all_tank[0].x-pwitdth:0);
        offset_y=(all_tank[0].y+phight<hight?(offset_ys?all_tank[0].y+phight:(2*phight)):hight-1);
        offset_x=(all_tank[0].x+pwitdth<weidth?(offset_xs?all_tank[0].x+pwitdth:(2*pwitdth)):weidth-1);
        offset_ys2=(all_tank[1].y-phight>0?all_tank[1].y-phight:0);
        offset_xs2=(all_tank[1].x-pwitdth>0?all_tank[1].x-pwitdth:0);
        offset_y2=(all_tank[1].y+phight<hight?(offset_ys2?all_tank[1].y+phight:(2*phight)):hight-1);
        offset_x2=(all_tank[1].x+pwitdth<weidth?(offset_xs2?all_tank[1].x+pwitdth:(2*pwitdth)):weidth-1);
        clearScreen();
        walls1(offset_ys,offset_xs,offset_y,offset_x);
        walls2(offset_ys2,offset_xs2,offset_y2,offset_x2);

        if(!all_tank[0].flag)
        {
            getank2(all_tank,0);
            all_tank[0].death++;
        }
        if(!all_tank[1].flag)
        {
            getank2(all_tank,1);
            all_tank[1].death++;
        }
        if(all_tank[0].death==10)
        {
            pauseAudio(&efx[3]);
            return 0;
        }
        if(all_tank[1].death==10)
        {
            pauseAudio(&efx[3]);
            return 1;
        }

        if(count)
            flying2(nb,all_tank,count,offset_xs,offset_ys,offset_xs2,offset_ys2,offset_x,offset_y,offset_x2,offset_y2);

        showtank1(all_tank,offset_ys,offset_xs,offset_y,offset_x);
        showtank2(all_tank,offset_ys2,offset_xs2,offset_y2,offset_x2);
        lifebar2(all_tank);
        drawCmdWindow();

        Sleep(100);

        for (k=0; k<NUM_KEYS2; k++)
        {
            if(KEY_DOWN(key_val[k]) )
            {

                switch (key_val[k])
                {
                case VK_A:
                    all_tank[0].direction=3;
                    turn(all_tank);
                    if(check(all_tank[0],3))all_tank[0].x--;
                    break;
                case VK_S:
                    all_tank[0].direction=2;
                    turn(all_tank);
                    if(check(all_tank[0],2))all_tank[0].y++;
                    break;
                case VK_D:
                    all_tank[0].direction=1;
                    turn(all_tank);
                    if(check(all_tank[0],1))all_tank[0].x++;
                    break;
                case VK_W:
                    all_tank[0].direction=0;
                    turn(all_tank);
                    if(check(all_tank[0],0))all_tank[0].y--;
                    break;
                case VK_LEFT:
                    all_tank[1].direction=3;
                    turn(all_tank+1);
                    if(check(all_tank[1],3))all_tank[1].x--;
                    break;
                case VK_DOWN:
                    all_tank[1].direction=2;
                    turn(all_tank+1);
                    if(check(all_tank[1],2))all_tank[1].y++;
                    break;
                case VK_RIGHT:
                    all_tank[1].direction=1;
                    turn(all_tank+1);
                    if(check(all_tank[1],1))all_tank[1].x++;
                    break;
                case VK_UP:
                    all_tank[1].direction=0;
                    turn(all_tank+1);
                    if(check(all_tank[1],0))all_tank[1].y--;
                    break;
                case VK_Q:
                    saveScreen();
                    if(pause(&pauses))
                    {
                        pauseAudio(&efx[3]);
                        return 2;
                    }
                    break;
                case VK_SPACE:
                    shoot(nb,all_tank[0],count++,0);
                    if(count==500)count=1;
                    break;
                case VK_P:
                    shoot(nb,all_tank[1],count++,1);
                    if(count==500)count=1;
                    break;
                }
            }
        }


    }

}
void boundary(void)
{
    int i,j;
    for(i=0;i<weidth;i++)
    {
        plate[0][i]=3;
        plate[hight-1][i]=3;
    }
    for(i=1;i<hight-1;i++)
    {
        plate[i][0]=3;
        plate[i][weidth-1]=3;
    }
}
void walls(void)
{
    int i,j;

    for(i=0;i<hight;i++)
    {
        for(j=0;j<weidth;j++)
        {
            if(plate[i][j]==0)
            {
                putASCII2(2*j,i,' ',0,0);
                putASCII2(2*j+1,i,' ',0,0);
            }
            else if(plate[i][j]==3)
            {
                putASCII2(2*j,i,0xA1,5,8);
                putASCII2(2*j+1,i,0xBB,5,8);
            }
            else if(plate[i][j]==2)
            {
                putASCII2(2*j,i,0xA1,8,0);
                putASCII2(2*j+1,i,0xBC,8,0);
            }
            else if(plate[i][j]==1)
            {
                putASCII2(2*j,i,0xA1,8,0);
                putASCII2(2*j+1,i,0xBD,8,0);
            }
        }

    }
}
void walls1(int oys,int oxs,int oy,int ox)
{
    int i,j;

    for(i=oys;i<=oy;i++)
    {
        for(j=oxs;j<=ox;j++)
        {
            if(plate[i][j]==0)
            {
                putASCII2(2*(j-oxs),i-oys,' ',0,0);
                putASCII2(2*(j-oxs)+1,i-oys,' ',0,0);
            }
            else if(plate[i][j]==3)
            {
                putASCII2(2*(j-oxs),i-oys,0xA1,5,8);
                putASCII2(2*(j-oxs)+1,i-oys,0xBB,5,8);
            }
            else if(plate[i][j]==2)
            {
                putASCII2(2*(j-oxs),i-oys,0xA1,8,0);
                putASCII2(2*(j-oxs)+1,i-oys,0xBC,8,0);
            }
            else if(plate[i][j]==1)
            {
                putASCII2(2*(j-oxs),i-oys,0xA1,8,0);
                putASCII2(2*(j-oxs)+1,i-oys,0xBD,8,0);
            }
        }

    }
}
void walls2(int oys,int oxs,int oy,int ox)
{
    int i,j;
    for(i=oys;i<=oy;i++)
    {
        for(j=oxs;j<=ox;j++)
        {
            if(plate[i][j]==0)
            {
                putASCII2(2*(j-oxs+p2off),i-oys,' ',0,0);
                putASCII2(2*(j-oxs+p2off)+1,i-oys,' ',0,0);
            }
            else if(plate[i][j]==3)
            {
                putASCII2(2*(j-oxs+p2off),i-oys,0xA1,5,8);
                putASCII2(2*(j-oxs+p2off)+1,i-oys,0xBB,5,8);
            }
            else if(plate[i][j]==2)
            {
                putASCII2(2*(j-oxs+p2off),i-oys,0xA1,8,0);
                putASCII2(2*(j-oxs+p2off)+1,i-oys,0xBC,8,0);
            }
            else if(plate[i][j]==1)
            {
                putASCII2(2*(j-oxs+p2off),i-oys,0xA1,8,0);
                putASCII2(2*(j-oxs+p2off)+1,i-oys,0xBD,8,0);
            }
        }

    }
}
void map(char n)
{
    FILE *fin;
    switch(n)
    {
        case '1':
            fin=fopen("map1.txt","r");
            break;
        case '2':
            fin=fopen("map2.txt","r");
            break;
        case '3':
            fin=fopen("map3.txt","r");
            break;
        case '4':
            fin=fopen("map4.txt","r");
            break;
        case '5':
            fin=fopen("map5.txt","r");
            break;
        case '6':
            fin=fopen("map6.txt","r");
            break;
    }
    int i,j,map[hight-2][weidth-2];
    for(i=0;i<(hight-2)*(weidth-2);i++)
        fscanf(fin,"%1d",&plate[i/(weidth-2)+1][i%(weidth-2)+1]);

    fclose(fin);
}
void getank(tank *tanks,int s,int n)
{
    int i,j,k;
    for(k=s;k<n;k++)
    {
        tanks[k].x=rand()%(weidth-4)+1;
        int flag;
        do{
            flag=0;
            tanks[k].y=rand()%(hight-4)+1;
            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    if(plate[tanks[k].y+i][tanks[k].x+j])
                        flag=1;
                }
            }
        }while(flag);
        tanks[k].direction=1;
        if(k==0)
            tanks[k].flag=LIFE*n/NUM_TANK;
        else
            tanks[k].flag=LIFE;

        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                tanks[k].shape[i][j]=tank_shape[tanks[k].direction][3*i+j];
            }
        }
    }
}
void getank2(tank *tanks,int n)
{
    int i,j,k;
        tanks[n].x=rand()%(weidth-4)+1;
        int flag;
        do{
            flag=0;
            tanks[n].y=rand()%(hight-4)+1;
            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {
                    if(plate[tanks[n].y+i][tanks[n].x+j])
                        flag=1;
                }
            }
        }while(flag);
        tanks[n].direction=1;
            tanks[n].flag=LIFE;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                tanks[n].shape[i][j]=tank_shape[tanks[n].direction][3*i+j];
            }
        }
}
void getboss(tank *boss)
{
    int i,j;

    boss->x=30;
    boss->y=37;
    boss->direction=1;
    boss->flag=LIFE*2*stage/NUM_TANK;

    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            boss->shape[i][j]=boss_shape[boss->direction][6*i+j];
        }
    }
}
void turn(tank *player)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            player->shape[i][j]=tank_shape[player->direction][3*i+j];
        }
    }
}
void turnboss(tank *player)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            player->shape[i][j]=boss_shape[player->direction][6*i+j];
        }
    }
}
int const check(tank player,int t)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(player.shape[i][j])
            {
                switch(t)
                {
                    case 3:
                    if(plate[player.y+i][player.x+j-1]==1||plate[player.y+i][player.x+j-1]==2||plate[player.y+i][player.x+j-1]==3)
                        return 0;
                    break;
                    case 2:
                    if(plate[player.y+i+1][player.x+j]==1||plate[player.y+i+1][player.x+j]==2||plate[player.y+i+1][player.x+j]==3)
                        return 0;
                    break;
                    case 1:
                    if(plate[player.y+i][player.x+j+1]==1||plate[player.y+i][player.x+j+1]==2||plate[player.y+i][player.x+j+1]==3)
                        return 0;
                    break;
                    case 0:
                    if(plate[player.y+i-1][player.x+j]==1||plate[player.y+i-1][player.x+j]==2||plate[player.y+i-1][player.x+j]==3)
                        return 0;
                    break;
                }
            }
        }
    }
    return 1;
}
int const checkboss(tank player,int t)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
                switch(t)
                {
                    case 3:
                    if(plate[player.y+i][player.x+j-1]==1||plate[player.y+i][player.x+j-1]==2||plate[player.y+i][player.x+j-1]==3)
                        return 0;
                        break;
                    case 2:
                    if(plate[player.y+i+1][player.x+j]==1||plate[player.y+i+1][player.x+j]==2||plate[player.y+i+1][player.x+j]==3)
                        return 0;
                        break;
                    case 1:
                    if(plate[player.y+i][player.x+j+1]==1||plate[player.y+i][player.x+j+1]==2||plate[player.y+i][player.x+j+1]==3)
                        return 0;
                        break;
                    case 0:
                    if(plate[player.y+i-1][player.x+j]==1||plate[player.y+i-1][player.x+j]==2||plate[player.y+i-1][player.x+j]==3)
                        return 0;
                        break;
                }
        }
    }
    return 1;
}
void showtank(tank *tanks,int k)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            switch ((tanks+k)->shape[i][j])
            {
                case 4:
                    putASCII2(2*((tanks+k)->x+j),(tanks+k)->y+i,0xA1,change_color(tanks,k),0);
                    putASCII2(2*((tanks+k)->x+j)+1,(tanks+k)->y+i,0xB4,change_color(tanks,k),0);
                    break;
                case 5:
                    putASCII2(2*((tanks+k)->x+j),(tanks+k)->y+i,k?0xDA:0xA2,change_color(tanks,k),0);
                    putASCII2(2*((tanks+k)->x+j)+1,(tanks+k)->y+i,k?0x5D:0x60,change_color(tanks,k),0);
                    break;
                case 6:
                    putASCII2(2*((tanks+k)->x+j),(tanks+k)->y+i,0xA1,change_color(tanks,k),0);
                    putASCII2(2*((tanks+k)->x+j)+1,(tanks+k)->y+i,0xC0,change_color(tanks,k),0);
                    break;
            }
        }
    }
}
void showboss(tank *tanks)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<6;j++)
        {
            switch (tanks->shape[i][j])
            {
                case 4:
                    putASCII2(2*((tanks)->x+j),(tanks)->y+i,0xA1,change_color(tanks,0),0);
                    putASCII2(2*((tanks)->x+j)+1,(tanks)->y+i,0xB4,change_color(tanks,0),0);
                    break;
                case 5:
                    putASCII2(2*((tanks)->x+j),(tanks)->y+i,0xDA,change_color(tanks,0),0);
                    putASCII2(2*((tanks)->x+j)+1,(tanks)->y+i,0x5D,change_color(tanks,0),0);
                    break;
                case 6:
                    putASCII2(2*((tanks)->x+j),(tanks)->y+i,0xA1,change_color(tanks,0),0);
                    putASCII2(2*((tanks)->x+j)+1,(tanks)->y+i,0xC0,change_color(tanks,0),0);
                    break;
            }
        }
    }
}
void showtank1(tank *tanks,int oys,int oxs,int oy,int ox)
{
    int i,j,k;
    for(k=0;k<2;k++)
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(tanks[k].y+i<=oy&&tanks[k].y+i>=oys&&tanks[k].x+j<=ox&&tanks[k].x+j>=oxs)
                switch ((tanks+k)->shape[i][j])
                    {
                    case 4:
                        putASCII2(2*((tanks+k)->x+j-oxs),(tanks+k)->y+i-oys,0xA1,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs)+1,(tanks+k)->y+i-oys,0xB4,change_color(tanks,k),0);
                        break;
                    case 5:
                        putASCII2(2*((tanks+k)->x+j-oxs),(tanks+k)->y+i-oys,k?0xDA:0xA2,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs)+1,(tanks+k)->y+i-oys,k?0x5D:0x60,change_color(tanks,k),0);
                        break;
                    case 6:
                        putASCII2(2*((tanks+k)->x+j-oxs),(tanks+k)->y+i-oys,0xA1,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs)+1,(tanks+k)->y+i-oys,0xC0,change_color(tanks,k),0);
                        break;
                    }
            }
        }
    }
}
void showtank2(tank *tanks,int oys,int oxs,int oy,int ox)
{
    int i,j,k;
    for(k=0;k<2;k++)
    {
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(tanks[k].y+i<=oy&&tanks[k].y+i>=oys&&tanks[k].x+j<=ox&&tanks[k].x+j>=oxs)
                switch ((tanks+k)->shape[i][j])
                    {
                    case 4:
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off),(tanks+k)->y+i-oys,0xA1,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off)+1,(tanks+k)->y+i-oys,0xB4,change_color(tanks,k),0);
                        break;
                    case 5:
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off),(tanks+k)->y+i-oys,k?0xDA:0xA2,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off)+1,(tanks+k)->y+i-oys,k?0x5D:0x60,change_color(tanks,k),0);
                        break;
                    case 6:
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off),(tanks+k)->y+i-oys,0xA1,change_color(tanks,k),0);
                        putASCII2(2*((tanks+k)->x+j-oxs+p2off)+1,(tanks+k)->y+i-oys,0xC0,change_color(tanks,k),0);
                        break;
                    }
            }
        }
    }
}
void shoot(bullet *nb,tank player,int c,int n)
{
    int i=c;
    nb[i].direction=player.direction;
    nb[i].party=n;
    nb[i].flag=1;
    switch(nb[i].direction)
    {
        case 0:
            nb[i].x=player.x+1;
            nb[i].y=player.y;
            break;
        case 1:
            nb[i].x=player.x+2;
            nb[i].y=player.y+1;
            break;
        case 2:
            nb[i].x=player.x+1;
            nb[i].y=player.y+2;
            break;
        case 3:
            nb[i].x=player.x;
            nb[i].y=player.y+1;
            break;
    }
}
void shootboss(bullet *nb,tank player,int c,int n)
{
    int i=c,j;
    for(j=0;j<2;j++)
    {
        nb[i+j].direction=player.direction;
        nb[i+j].party=n;
        nb[i+j].flag=1;
        switch(nb[i+j].direction)
        {
            case 0:
                nb[i+j].x=player.x+2+j;
                nb[i+j].y=player.y;
                break;
            case 1:
                nb[i+j].x=player.x+5;
                nb[i+j].y=player.y+2+j;
                break;
            case 2:
                nb[i+j].x=player.x+2+j;
                nb[i+j].y=player.y+5;
                break;
            case 3:
                nb[i+j].x=player.x;
                nb[i+j].y=player.y+2+j;
                break;
        }
    }
}
void flying(bullet *nb,tank *tanks,int c,int n)
{
    int i;
    for(i=0;i<=c-1;i++)
    {
        int k,j,h;
        if(nb[i].flag)
        {
            switch(nb[i].direction)
            {
                case 0:
                    nb[i].y-=2;
                break;
                case 1:
                    nb[i].x+=2;
                break;
                case 2:
                    nb[i].y+=2;
                break;
                case 3:
                    nb[i].x-=2;
                break;
            }
            if(n==stage)
            {
                for(k=0;k<3;k++)
                {
                    for(j=0;j<3;j++)
                    {
                        if((tanks[0].x+j==nb[i].x)&&(tanks[0].y+k==nb[i].y)&&(nb[i].party))
                        {
                            tanks[0].flag--;
                            if(!tanks[0].flag)
                            {
                                tanks[0].x=63;
                                tanks[0].y=42;
                            }
                            nb[i].flag=0;
                            playAudio(&efx[0]);
                            return;
                        }
                    }
                }
                for(k=0;k<6;k++)
                {
                    for(j=0;j<6;j++)
                    {
                        if((tanks[1].x+j==nb[i].x)&&(tanks[1].y+k==nb[i].y)&&(!nb[i].party))
                        {
                            tanks[1].flag--;
                            if(!tanks[1].flag)
                            {
                                tanks[1].x=63;
                                tanks[1].y=42;
                            }
                            nb[i].flag=0;
                            playAudio(&efx[0]);
                            return;
                        }
                    }
                }
            }
            else
            {
               for(h=0;h<n*NUM_TANK;h++)
                {
                    for(k=0;k<3;k++)
                    {
                        for(j=0;j<3;j++)
                        {
                            if((tanks[h].x+j==nb[i].x)&&(tanks[h].y+k==nb[i].y)&&((nb[i].party&&!h)||(!(nb[i].party)&&h)))
                            {
                                tanks[h].flag--;
                                if(!tanks[h].flag)
                                {
                                    tanks[h].x=63;
                                    tanks[h].y=42;
                                }
                                nb[i].flag=0;
                                playAudio(&efx[0]);
                                return;
                            }
                        }
                    }
                }
            }

            if( plate[nb[i].y][nb[i].x]==2)
            {
                playAudio(&efx[2]);
                for(k=0;k<3;k++)
                {
                    for(j=0;j<3;j++)
                        if(plate[nb[i].y-1+k][nb[i].x-1+j]==2)
                            plate[nb[i].y-1+k][nb[i].x-1+j]=0;
                }
                nb[i].flag=0;
            }
            else if( plate[nb[i].y][nb[i].x]==1)
            {
                nb[i].flag=0;
            }
            else if( plate[nb[i].y][nb[i].x]==3||plate[nb[i].y][nb[i].x-1]==3||plate[nb[i].y][nb[i].x+1]==3||plate[nb[i].y-1][nb[i].x]==3||plate[nb[i].y+1][nb[i].x]==3)
            {
                nb[i].flag=0;
            }
            else
            {
                if(!nb[i].party)
                {
                    putASCII2(2*nb[i].x,nb[i].y,0xA1,11,0);
                    putASCII2(2*nb[i].x+1,nb[i].y,0xB8,11,0);
                }
                else
                {
                    putASCII2(2*nb[i].x,nb[i].y,0xA1,12,0);
                    putASCII2(2*nb[i].x+1,nb[i].y,0xB8,12,0);
                }
            }
        }
    }
}
void flying2(bullet *nb,tank *tanks,int c,int oxs1,int oys1,int oxs2,int oys2,int ox1,int oy1,int ox2,int oy2)
{
    int i;
    for(i=0;i<=c-1;i++)
    {
        int k,j,h;
        if(nb[i].flag)
        {
            switch(nb[i].direction)
            {
                case 0:
                    nb[i].y-=2;
                break;
                case 1:
                    nb[i].x+=2;
                break;
                case 2:
                    nb[i].y+=2;
                break;
                case 3:
                    nb[i].x-=2;
                break;
            }
            for(h=0;h<2;h++)
            {
                for(k=0;k<3;k++)
                {
                    for(j=0;j<3;j++)
                    {
                        if((tanks[h].x+j==nb[i].x)&&(tanks[h].y+k==nb[i].y)&&((nb[i].party&&!h)||(!(nb[i].party)&&h)))
                        {
                            tanks[h].flag--;
                            if(!tanks[h].flag)
                            {
                                tanks[h].x=63;
                                tanks[h].y=42;
                            }
                            nb[i].flag=0;
                            playAudio(&efx[0]);
                            return;
                        }
                    }
                }
            }
            if( plate[nb[i].y][nb[i].x]==2)
            {
                playAudio(&efx[2]);
                for(k=0;k<3;k++)
                {
                    for(j=0;j<3;j++)
                        if(plate[nb[i].y-1+k][nb[i].x-1+j]==2)
                            plate[nb[i].y-1+k][nb[i].x-1+j]=0;
                }
                nb[i].flag=0;
            }
            else if( plate[nb[i].y][nb[i].x]==1)
            {
                nb[i].flag=0;
            }
            else if( plate[nb[i].y][nb[i].x]==3||plate[nb[i].y][nb[i].x-1]==3||plate[nb[i].y][nb[i].x+1]==3||plate[nb[i].y-1][nb[i].x]==3||plate[nb[i].y+1][nb[i].x]==3)
            {
                nb[i].flag=0;
            }
            else
            {
                if(nb[i].x>=oxs2&&nb[i].x<=ox2&&nb[i].y>=oys2&&nb[i].y<=oy2)
                {
                    putASCII2(2*(nb[i].x-oxs2+p2off),nb[i].y-oys2,0xA1,12,0);
                    putASCII2(2*(nb[i].x-oxs2+p2off)+1,nb[i].y-oys2,0xB8,12,0);
                }
                if(nb[i].x>=oxs1&&nb[i].x<=ox1&&nb[i].y>=oys1&&nb[i].y<=oy1)
                {
                    putASCII2(2*(nb[i].x-oxs1),nb[i].y-oys1,0xA1,12,0);
                    putASCII2(2*(nb[i].x-oxs1)+1,nb[i].y-oys1,0xB8,12,0);
                }
            }
        }
    }
}
void enemies(tank*tanks,bullet *nb,int *c,int n)
{
    int k;
    for(k=1;k<n*NUM_TANK;k++)
    {
        if(tanks[k].flag)
        {
            /*if(plate[tanks[k].y][tanks[k].x]&&tanks[k].direction==0)tanks[k].direction=1;
            else if(plate[tanks[k].y][tanks[k].x]&&tanks[k].direction==3)tanks[k].direction=2;
            else if(plate[tanks[k].y+2][tanks[k].x]&&tanks[k].direction==2)tanks[k].direction=0;
            else if(plate[tanks[k].y+2][tanks[k].x]&&tanks[k].direction==3)tanks[k].direction=1;
            else if(plate[tanks[k].y][tanks[k].x+2]&&tanks[k].direction==1)tanks[k].direction=2;
            else if(plate[tanks[k].y][tanks[k].x+2]&&tanks[k].direction==0)tanks[k].direction=3;
            else if(plate[tanks[k].y+2][tanks[k].x+2]&&tanks[k].direction==2)tanks[k].direction=3;
            else if(plate[tanks[k].y+2][tanks[k].x+2]&&tanks[k].direction==1)tanks[k].direction=0;
            else */tanks[k].direction=find_next_step(tanks,k);
            turn(tanks+k);
            if(check(tanks[k],tanks[k].direction))
            {
                switch(tanks[k].direction)
                {
                    case 0:
                        tanks[k].y--;
                    break;
                    case 1:
                        tanks[k].x++;
                    break;
                    case 2:
                        tanks[k].y++;
                    break;
                    case 3:
                        tanks[k].x--;
                    break;
                }
            }
            if((tanks[k].x==tanks[0].x)||(tanks[k].y==tanks[0].y))
            {
                shoot(nb,tanks[k],*c,k);
                (*c)++;
                if((*c)==500)(*c)=1;
            }
        }
    }
}
void boss(tank*tanks,bullet *nb,int *c)
{
    if(plate[tanks[1].y][tanks[1].x]&&tanks[1].direction==0)tanks[1].direction=1;
    else if(plate[tanks[1].y][tanks[1].x]&&tanks[1].direction==3)tanks[1].direction=2;
    else if(plate[tanks[1].y+2][tanks[1].x]&&tanks[1].direction==2)tanks[1].direction=0;
    else if(plate[tanks[1].y+2][tanks[1].x]&&tanks[1].direction==3)tanks[1].direction=1;
    else if(plate[tanks[1].y][tanks[1].x+2]&&tanks[1].direction==1)tanks[1].direction=2;
    else if(plate[tanks[1].y][tanks[1].x+2]&&tanks[1].direction==0)tanks[1].direction=3;
    else if(plate[tanks[1].y+2][tanks[1].x+2]&&tanks[1].direction==2)tanks[1].direction=3;
    else if(plate[tanks[1].y+2][tanks[1].x+2]&&tanks[1].direction==1)tanks[1].direction=0;
    else tanks[1].direction=find_next_step(tanks,1);
    turnboss(tanks+1);
    if(checkboss(tanks[1],tanks[1].direction))
    {
        switch(tanks[1].direction)
        {
            case 0:
                tanks[1].y--;
            break;
            case 1:
                tanks[1].x++;
            break;
            case 2:
                tanks[1].y++;
            break;
            case 3:
                tanks[1].x--;
            break;
        }
    }
    if((tanks[1].x+2==tanks[0].x)||(tanks[1].y+2==tanks[0].y))
    {
        shootboss(nb,tanks[1],*c,1);
        (*c)+=2;
        if((*c)==500)(*c)=1;
    }
}
int find_next_step(tank*tanks,int k)
{
    enqueue(tanks[0].x+1,tanks[0].y+1);
    plate[tanks[0].y+1][tanks[0].x+1]=-1;

    while(isQueueEmpty())
    {
        dequeue();
        if(v.x>0&&v.x<(weidth-1)&&v.y>0&&v.y<(hight-1))
        {
            if(!plate[v.y-1][v.x])
            {
                plate[v.y-1][v.x]=-1;
                if((v.x==tanks[k].x+1)&&(v.y-1==tanks[k].y+1))
                {
                    reset();
                    return 2;
                }
                enqueue(v.x,v.y-1);
            }
            if(!plate[v.y][v.x+1])
            {
                plate[v.y][v.x+1]=-1;
                if((v.x+1==tanks[k].x+1)&&(v.y==tanks[k].y+1))
                {
                    reset();
                    return 3;
                }
                enqueue(v.x+1,v.y);
            }
            if(!plate[v.y+1][v.x])
            {
                plate[v.y+1][v.x]=-1;
                if((v.x==tanks[k].x+1)&&(v.y+1==tanks[k].y+1))
                {
                    reset();
                    return 0;
                }
                enqueue(v.x,v.y+1);
            }
            if(!plate[v.y][v.x-1])
            {
                plate[v.y][v.x-1]=-1;
                if((v.x-1==tanks[k].x+1)&&(v.y==tanks[k].y+1))
                {
                    reset();
                    return 1;
                }
                enqueue(v.x+1,v.y);
            }
        }
    }
    reset();
    return rand()%4;
}
void enqueue(int x,int y)
{
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->next=NULL;
    new_node->x=x;
    new_node->y=y;
    if(rear==NULL)front=new_node;
    else rear->next=new_node;
    rear=new_node;
}
void dequeue(void)
{
    if(front==rear)rear=NULL;
    ptr=front;
    front=front->next;
    v.x=ptr->x;
    v.y=ptr->y;
    free(ptr);
}
int isQueueEmpty(void)
{
    if(front==NULL&&rear==NULL)return 0;
    return 1;
}
void reset(void)
{
    int i,j;
    for(i=1;i<hight-1;i++)
        for(j=1;j<weidth-1;j++)
            if(plate[i][j]==-1)
                plate[i][j]=0;
    rear=NULL;
    while(front!=NULL)
    {
        ptr=front;
        front=front->next;
        free(ptr);
    }
}
int change_color(tank *tanks,int k)
{
    if(k)
    {
        if(tanks[k].flag>2)
            return 14;
        else if(tanks[k].flag==2)
            return 12;
        else
            return 4;
    }
    else
    {
        if(tanks[k].flag>2)
            return 13;
        else if(tanks[k].flag==2)
            return 9;
        else
            return 1;
    }
}
void lifebar1(tank* tanks)
{
    int i;
    for(i=0;i<tanks[0].flag;i++)
    {
        putASCII2(2*(tanks[0].x+i),tanks[0].y+4,0xA2,12,0);
        putASCII2(2*(tanks[0].x+i)+1,tanks[0].y+4,0x6F,12,0);
    }
}
void lifebarb(tank* tanks)
{
    int i;
    for(i=0;i<tanks[1].flag;i++)
    {
        putASCII2(2*(tanks[1].x+i),tanks[1].y+7,0xA2,12,0);
        putASCII2(2*(tanks[1].x+i)+1,tanks[1].y+7,0x6F,12,0);
    }
}
void lifebar2(tank* tanks)
{
    int i;
    char temp[2];
    Font *large_font=read_font("font.txt");
    for(i=0;i<tanks[0].flag;i++)
    {
        putASCII2(2*(5+i),2*phight+5,0xA2,12,0);
        putASCII2(2*(5+i)+1,2*phight+5,0x6F,12,0);
    }
    temp[0]=(tanks[1].death)+'0';
    temp[1]=0;
    putStringLarge(large_font,20,2*phight+5,temp,10);
    for(i=0;i<tanks[1].flag;i++)
    {
        putASCII2(2*(5+i+p2off),2*phight+5,0xA2,12,0);
        putASCII2(2*(5+i+p2off)+1,2*phight+5,0x6F,12,0);
    }
    temp[0]=(tanks[0].death)+'0';
    putStringLarge(large_font,20+2*p2off,2*phight+5,temp,10);
}
