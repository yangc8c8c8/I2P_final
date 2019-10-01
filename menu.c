#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
/* ���İO�o�n�[�J�o�� */
#include "audio.h"
/* �t�~�٦����U���]�w */
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
putASCII2()  �̫��ӰѼƤ��O�O�r���e���M�I�����C��
�i�H�ѦҤU�����C��ȹ�Ӫ�ӳ]�w�A�Q�n���C��
   0: ��     1: �t��   2: �t��   3: �t�C
   4: �t��   5: �t��   6: �t��   7: �L��
   8: �t��   9: �G��  10: �G��  11: �G�C
  12: �G��  13: �G��  14: �G��  15: ��
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

    /* �Ұ���L���� ��ӵ{�����u�n���@���N��F*/
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
        /* �L�a�j��  �̭��]�t�F�o�ӵ{�����D�n�u�@
        �ӥB�C���j��|���_��̷s���e����ܨ�ù��W
        ���O���ʵe�@�� �C���j���s�@���e�� */
        while (!IsEnding)
        {
            /* �C�g�L REFRESH_RATE �� ticks �~�|��s�@���e�� */
            cur_tick = timer(); /* �C�� tick 0.01 �� */
            //sprintf(str, "%10d", cur_tick/1000);

            if (cur_tick-last_tick > REFRESH_RATE)
            {
                last_tick = cur_tick;

                clearScreen();
                restoreScreen();

                putStringLarge(mainmenu.large_font, OFFSET_X, OFFSET_Y-1, str, 14);

                /* ����e�X�� */
                showMenu(&mainmenu);
                /* ���F�n���@�s�� putASCII2() ���ʧ@���ͮĪG
                �����n�I�s�@�� drawCmdWindow() �⤧�e�e���������e�@����ܨ�ù��W */
                drawCmdWindow();

            } /* end of if (cur_tick % REFRESH_RATE == 0 ... */
            for (k=0; k<NUM_KEYS; k++)
            {
                /* ����q�쥻�Q���U�����A �ܦ���}�����A  �o�O���F�B�z���ۤ��񪺱��p */
                if(KEY_UP(key_val[k]) && key_down[k])
                {
                    key_down[k] = 0;
                }
            }
            /* ��L���� �B�z���ۤ��񪺪��p */
            for (k=0; k<NUM_KEYS; k++)
            {
                /* ����q�쥻�Q���U�����A �ܦ���}�����A  �o�O���F�B�z���ۤ��񪺱��p */
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
                        /* �i�H�ոլݩ��U�t�@�ؿ��Φ�
                            �P�ɯ঳�h�Ӷ��إi�H�Q���
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
    m->state[m->cursor] = m->state[m->cursor] | 1;  /* �ثe��ܪ����� */

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
