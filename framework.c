#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>


#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "framework.h"

/*----------------------------------------------------------*/


int IsOnItem(Menu *m, int index)
{
    return (m->state[index] & 1); /* 用位元運算來判斷目前選擇的項目 */
}
int IsItemSelected(Menu *m, int index)
{
    return (m->state[index] & 2);
}
void showMenu(Menu *m)
{
    int i;
    int fg;
    char *str;

    for (i=0; i< m->num_options; i++) {

        if ( !IsOnItem(m, i) ) {
            fg = m->fgcolor;
        } else {
            fg = m->bgcolor;
        }

        if ( !IsItemSelected(m, i) ) {
            str = m->text[i];
        } else {
            str = m->alt_text[i];
        }

        putStringLarge(m->large_font, (m->x)*(m->large_font->width+2),
            (m->y+i)*(m->large_font->height+2), str, fg);
    }
}

void scrollMenu(Menu *m, int diff)
{
    m->state[m->cursor] = m->state[m->cursor] & (~1);  /* 把目前游標所在的選項狀態清除 */
    m->cursor = (m->cursor + diff + m->num_options) % m->num_options; /* 把遊標移到下一個選項 */
    m->state[m->cursor] = m->state[m->cursor] | 1; /* 選擇目前游標所在的選項 */
}

void radioMenu(Menu *m)
{
    int i;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = m->state[i] & (~2); /* 清掉全部的選項 */
    }
    m->state[m->cursor] = m->state[m->cursor] | 2; /* 設定目前游標 */
}
void toggleMenu(Menu *m)
{
    m->state[m->cursor] = m->state[m->cursor] ^ 2;  /* 利用位元運算 產生 toggle 的效果 */
}

int pause(Pausescreen*pauses)
{
    int k;
    int key_down[NUM_KEYS3] = {0};
    int key_val[NUM_KEYS3] = {VK_UP, VK_DOWN, VK_RETURN, VK_SPACE};
    char str[40] = {'\0'};
    while (1)
    {
        clearScreen();
        restoreScreen();
        Sleep(50);
        putStringLarge(pauses->large_font, 5 ,4, str, 14);
        showpause(pauses);
        drawCmdWindow();

        for (k=0; k<NUM_KEYS3; k++)
        {
            if(KEY_UP(key_val[k]) && key_down[k])
            {
                key_down[k] = 0;
            }
        }

        for (k=0; k<NUM_KEYS3; k++)
        {
            if(KEY_DOWN(key_val[k]) && !key_down[k])
            {
                key_down[k] = 1;

                switch (key_val[k])
                {
                case VK_UP:
                    scrollpause(pauses, -1);
                    break;
                case VK_DOWN:
                    scrollpause(pauses, +1);
                    break;
                case VK_RETURN:
                    if (IsOnItemp(pauses, 0))
                        return 0;
                    else if (IsOnItemp(pauses, 1))
                        return 1;
                    break;
                case VK_SPACE:
                    radiopause(pauses);
                    break;
                }
            }
        }
    }
}
    void setpause(Pausescreen *p)
{
    int i;

    p->large_font = read_font("font.txt");
    p->x = 1;
    p->y = 2;
    p->fgcolor = 12;
    p->bgcolor = 15;
    p->num_options = 2;
    p->cursor = 0;
    for (i=0; i<p->num_options; i++)
        p->state[i] = 0;
    p->state[p->cursor] = p->state[p->cursor] | 1;

    strcpy(p->text[0], "RETURN");
    strcpy(p->text[1], "EXIT");
    strcpy(p->alt_text[0], "RETURN *");
    strcpy(p->alt_text[1], "EXIT *");
}
void showpause(Pausescreen *p)
{
    int i;
    int fg;
    char *str;

    for (i=0; i< p->num_options; i++) {

        if ( !IsOnItemp(p, i) ) {
            fg = p->fgcolor;
        } else {
            fg = p->bgcolor;
        }

        if ( !IsItemSelectedp(p, i) )
        {
            str = p->text[i];
        }
        else
        {
            str = p->alt_text[i];
        }
        putStringLarge(p->large_font, (p->x)*(p->large_font->width+2),
            (p->y+i)*(p->large_font->height+2), str, fg);
    }
}
int IsOnItemp(Pausescreen *p, int index)
{
    return (p->state[index] & 1); /* 用位元運算來判斷目前選擇的項目 */
}
int IsItemSelectedp(Pausescreen *p, int index)
{
    return (p->state[index] & 2);
}
void scrollpause(Pausescreen *p, int diff)
{
    p->state[p->cursor] = p->state[p->cursor] & (~1);  /* 把目前游標所在的選項狀態清除 */
    p->cursor = (p->cursor + diff + p->num_options) % p->num_options; /* 把遊標移到下一個選項 */
    p->state[p->cursor] = p->state[p->cursor] | 1; /* 選擇目前游標所在的選項 */
}

void radiopause(Pausescreen *p)
{
    int i;
    for (i=0; i<p->num_options; i++) {
        p->state[i] = p->state[i] & (~2); /* 清掉全部的選項 */
    }
    p->state[p->cursor] = p->state[p->cursor] | 2; /* 設定目前游標 */
}
void togglepause(Pausescreen *p)
{
    p->state[p->cursor] = p->state[p->cursor] ^ 2;  /* 利用位元運算 產生 toggle 的效果 */
}



