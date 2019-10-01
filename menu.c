#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
/* 音效記得要加入這個 */
#include "audio.h"
/* 另外還有底下的設定 */
/* For sound effect: In [Project Options]->[Parameters]->[Linker] add the parameter -lwinmm */


#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "image.h"
#include "framework.h"
#include "menu.h"
#include "start.h"
#include "game.h"

/*
putASCII2()  最後兩個參數分別是字元前景和背景的顏色
可以參考下面的顏色值對照表來設定你想要的顏色
   0: 黑     1: 暗藍   2: 暗綠   3: 暗青
   4: 暗紅   5: 暗紫   6: 暗黃   7: 淺灰
   8: 暗灰   9: 亮藍  10: 亮綠  11: 亮青
  12: 亮紅  13: 亮紫  14: 亮黃  15: 白
*/

#define WIDTH     30
#define HEIGHT    20
#define OFFSET_X  5
#define OFFSET_Y  5

#define NUM_KEYS 7
#define REFRESH_RATE 10



void menu(void)
{
    time_t t1,t2;
    int IsEnding = 0,ending=1;
    int k,temp;
    char str[40] = {'\0'};
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    int cur_tick, last_tick;
    Menu mainmenu;
    Image* background;
    background = read_image("tank.pixel", "tank.color");
    Audio audio;
    openAudioFile("menu.wav", &audio);

    /* 啟動鍵盤控制 整個程式中只要做一次就行了*/
    initializeKeyInput();
    cur_tick = last_tick = timer();

    setMainmenu(&mainmenu);
    playAudio(&audio);
    while(ending)
    {
        IsEnding=0;
        show_image(background, 0, 0);
        about();
        saveScreen();
        /* 無窮迴圈  裡面包含了這個程式的主要工作
        而且每次迴圈會不斷把最新的畫面顯示到螢幕上
        像是播動畫一樣 每次迴圈更新一次畫面 */
        while (!IsEnding)
        {
            /* 每經過 REFRESH_RATE 個 ticks 才會更新一次畫面 */
            cur_tick = timer(); /* 每個 tick 0.01 秒 */
            //sprintf(str, "%10d", cur_tick/1000);

            if (cur_tick-last_tick > REFRESH_RATE)
            {
                last_tick = cur_tick;

                clearScreen();
                restoreScreen();

                putStringLarge(mainmenu.large_font, OFFSET_X, OFFSET_Y-1, str, 14);

                /* 把選單畫出來 */
                showMenu(&mainmenu);
                /* 為了要讓一連串 putASCII2() 的動作產生效果
                必須要呼叫一次 drawCmdWindow() 把之前畫的全部內容一次顯示到螢幕上 */
                drawCmdWindow();

            } /* end of if (cur_tick % REFRESH_RATE == 0 ... */
            for (k=0; k<NUM_KEYS; k++)
            {
                /* 按鍵從原本被按下的狀態 變成放開的狀態  這是為了處理按著不放的情況 */
                if(KEY_UP(key_val[k]) && key_down[k])
                {
                    key_down[k] = 0;
                }
            }
            /* 鍵盤控制 處理按著不放的狀況 */
            for (k=0; k<NUM_KEYS; k++)
            {
                /* 按鍵從原本被按下的狀態 變成放開的狀態  這是為了處理按著不放的情況 */
                if(KEY_DOWN(key_val[k]) && !key_down[k])
                {
                    key_down[k] = 1;

                    switch (key_val[k])
                    {
                    case VK_UP:
                        scrollMenu(&mainmenu, -1);
                        break;
                    case VK_DOWN:
                        scrollMenu(&mainmenu, +1);
                        break;
                    case VK_RETURN:
                        if (IsOnItem(&mainmenu, 0))
                        {
                            IsEnding = 1;
                            pauseAudio(&audio);
                            t1=clock();
                            temp=game1();
                            if (temp==-1)
                            {
                                t2=clock();
                                draw_win();
                                ranking(t2-t1);
                            }
                            else if(temp>=0)
                                draw_gg(temp);
                        }
                        else if (IsOnItem(&mainmenu, 1))
                        {
                            IsEnding = 1;
                            pauseAudio(&audio);
                            temp=game2();
                            if (temp==1)
                                draw_win1();
                            else if(temp==0)
                                draw_win2();
                            clearScreen();
                        }
                        else if (IsOnItem(&mainmenu, 2))
                        {
                            IsEnding = 1;
                            pauseAudio(&audio);
                            showrank();
                        }

                        else if (IsOnItem(&mainmenu, 3))
                        {
                            ending=0;
                            IsEnding = 1;
                            pauseAudio(&audio);
                        }

                        break;
                    case VK_SPACE:
                        /* 可以試試看底下另一種選單形式
                            同時能有多個項目可以被選到
                            toggleMenu(&mainmenu);
                        */
                        radioMenu(&mainmenu);
                        break;
                    }
                }
            }
        } /* while (IsEnding) */
    }
}
int timer(void)
{
    return (clock()/(0.001*CLOCKS_PER_SEC));
}
void setMainmenu(Menu *m)
{
    int i;

    m->large_font = read_font("font.txt");
    m->x = 1;
    m->y = 2;
    m->fgcolor = 12;
    m->bgcolor = 15;
    m->num_options = 4;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++)
    {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;  /* 目前選擇的項目 */

    strcpy(m->text[0], "ONE PLAYER");
    strcpy(m->text[1], "TWO PLAYER");
    strcpy(m->text[2], "RANK");
    strcpy(m->text[3], "EXIT");
    strcpy(m->alt_text[0], "ONE PLAYER *");
    strcpy(m->alt_text[1], "TWO PLAYER *");
    strcpy(m->alt_text[2], "RANK *");
    strcpy(m->alt_text[3], "EXIT *");
}
void ranking(double take)
{
    int i;
    double ran[4];
    FILE *fin;
    fin=fopen("rank.txt","r");
    for(i=0;i<3;i++)
        fscanf(fin,"%lf",ran+i);
    fclose(fin);
    ran[3]=take;
    qsort(ran,4,sizeof(double),rancompare);
    fin=fopen("rank.txt","w");
    for(i=0;i<3;i++)
        fprintf(fin,"%lf\n",ran[i]);
    fclose(fin);
}
int rancompare(void*a,void*b)
{
    double* aa=(double*)a;
    double* bb=(double*)b;
    return *aa-*bb;
}
void showrank(void)
{
    int i,j,k;
    double ran[3];
    char temp[12]="",temp2[3]="",t;
    FILE *fin;
    Font *large_font=read_font("font.txt");
    fin=fopen("rank.txt","r");
    clearScreen();
    restoreScreen();
    for(i=0;i<3;i++)
    {
        fscanf(fin,"%lf",ran+i);
        j=(int)ran[i]/60000;
        k=(int)ran[i]/1000%60;
        sprintf(temp,"%d",j);
        sprintf(temp2,"%d",k);
        strcat(temp," min ");
        strcat(temp,temp2);
        strcat(temp," s");
        putStringLarge(large_font,7,10+10*i,temp,9);
    }
    putString(60,40,"Press  r and enter to continue.",10,1);
    drawCmdWindow();
    while(t=getchar())
        if(t=='r')break;
}
