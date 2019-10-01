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
void draw_anime(void){
Font *large_font=read_font("font.txt");
Audio startaudio[1];
openAudioFile("start.wav", &startaudio[0]);
playAudio(&startaudio[0]);
int c=0;
Image *anime[62];
anime[0]=read_image("1.pixel","1.color");
anime[1]=read_image("2.pixel","2.color");
anime[2]=read_image("3.pixel","3.color");
anime[3]=read_image("4.pixel","4.color");
anime[4]=read_image("5.pixel","5.color");
anime[5]=read_image("6.pixel","6.color");
anime[6]=read_image("7.pixel","7.color");
anime[7]=read_image("8.pixel","8.color");
anime[8]=read_image("9.pixel","9.color");
anime[9]=read_image("10.pixel","10.color");
anime[10]=read_image("11.pixel","11.color");
anime[11]=read_image("12.pixel","12.color");
anime[12]=read_image("13.pixel","13.color");
anime[13]=read_image("14.pixel","14.color");
anime[14]=read_image("15.pixel","15.color");
anime[15]=read_image("16.pixel","16.color");
anime[16]=read_image("17.pixel","17.color");
anime[17]=read_image("18.pixel","18.color");
anime[18]=read_image("19.pixel","19.color");
anime[19]=read_image("20.pixel","20.color");
anime[20]=read_image("21.pixel","21.color");
anime[21]=read_image("22.pixel","22.color");
anime[22]=read_image("23.pixel","23.color");
anime[23]=read_image("24.pixel","24.color");
anime[24]=read_image("25.pixel","25.color");
anime[25]=read_image("26.pixel","26.color");
anime[26]=read_image("27.pixel","27.color");
anime[27]=read_image("28.pixel","28.color");
anime[28]=read_image("29.pixel","29.color");
anime[29]=read_image("30.pixel","30.color");
anime[30]=read_image("31.pixel","31.color");
anime[31]=read_image("32.pixel","32.color");
anime[32]=read_image("33.pixel","33.color");
anime[33]=read_image("34.pixel","34.color");
anime[34]=read_image("35.pixel","35.color");
anime[35]=read_image("36.pixel","36.color");
anime[36]=read_image("37.pixel","37.color");
anime[37]=read_image("38.pixel","38.color");
anime[38]=read_image("39.pixel","39.color");
anime[39]=read_image("40.pixel","40.color");
anime[40]=read_image("41.pixel","41.color");
anime[41]=read_image("42.pixel","42.color");
anime[42]=read_image("43.pixel","43.color");
anime[43]=read_image("44.pixel","44.color");
anime[44]=read_image("45.pixel","45.color");
anime[45]=read_image("46.pixel","46.color");
anime[46]=read_image("47.pixel","47.color");
anime[47]=read_image("48.pixel","48.color");
anime[48]=read_image("49.pixel","49.color");
anime[49]=read_image("50.pixel","50.color");
anime[50]=read_image("51.pixel","51.color");
anime[51]=read_image("52.pixel","52.color");
anime[52]=read_image("53.pixel","53.color");
anime[53]=read_image("54.pixel","54.color");
anime[54]=read_image("55.pixel","55.color");
anime[55]=read_image("56.pixel","56.color");
anime[56]=read_image("57.pixel","57.color");
anime[57]=read_image("58.pixel","58.color");
anime[58]=read_image("59.pixel","59.color");
anime[59]=read_image("60.pixel","60.color");
anime[60]=read_image("61.pixel","61.color");
anime[61]=read_image("62.pixel","62.color");
while(c<62){
show_image(anime[c],0,0);
if(c>=20)
putStringLarge(large_font,19,22,"T",11);
if(c>=22)
putStringLarge(large_font,20,22," A",12);
if(c>=24)
putStringLarge(large_font,30,22," N",13);
if(c>=26)
putStringLarge(large_font,40,22," K",14);
if(c>=28)
putStringLarge(large_font,60,22," W",10);
if(c>=30)
putStringLarge(large_font,70,22," O",11);
if(c>=32)
putStringLarge(large_font,80,22," R",12);
if(c>=34)
putStringLarge(large_font,90,22," L",13);
if(c>=36)
putStringLarge(large_font,100,22," D",14);
drawCmdWindow();
Sleep(100);
c++;
if(c<61)
clearScreen();
else{
putString(60,40,"Press any key to continue.",10,1);
drawCmdWindow();
while((getche())!=0){
break;
}
clearScreen();
break;
}
}

}
//start with sound complete version
void draw_gg(int temp){
char tem[3]="";
sprintf(tem,"%d",temp-1);
Font *large_font=read_font("font.txt");
Audio gg[1];
openAudioFile("gg.wav", &gg[0]);
playAudio(&gg[0]);
putStringLarge(large_font,30,22," WASTED ",4);
putStringLarge(large_font,20,30,"TANK KILL",15);
putStringLarge(large_font,95,30,tem,15);
drawCmdWindow();
Sleep(2000);
clearScreen();
}
void draw_win(){
Font *large_font=read_font("font.txt");
Audio win[1];
openAudioFile("win.wav", &win[0]);
playAudio(&win[0]);
putStringLarge(large_font,30,11,"All",10);
drawCmdWindow();
putStringLarge(large_font,30,22,"targets",10);
drawCmdWindow();
putStringLarge(large_font,30,33,"eliminated.",10);
drawCmdWindow();
Sleep(3100);
clearScreen();
}
void draw_win1(){
Font *large_font=read_font("font.txt");
Audio win[1];
openAudioFile("win.wav", &win[0]);
playAudio(&win[0]);
putStringLarge(large_font,30,11,"WINNER",10);
drawCmdWindow();
putStringLarge(large_font,35,22,"P 1",10);
drawCmdWindow();
Sleep(3100);
clearScreen();
}
void draw_win2(){
Font *large_font=read_font("font.txt");
Audio win[1];
openAudioFile("win.wav", &win[0]);
playAudio(&win[0]);
putStringLarge(large_font,90,11,"WINNER",10);
drawCmdWindow();
putStringLarge(large_font,95,22,"P 2",10);
drawCmdWindow();
Sleep(3100);
clearScreen();
}
void about(){
//clearScreen();
Font *large_font=read_font("font.txt");
putStringLarge(large_font,93,8,"TANK",12);
drawCmdWindow();
Sleep(300);
putStringLarge(large_font,125,8,"WORLD",15);
drawCmdWindow();
Sleep(500);
putStringLarge(large_font,125,33,"WORLD",12);
drawCmdWindow();
Sleep(400);
putStringLarge(large_font,93,33,"TANK",15);
drawCmdWindow();
//Sleep(30000);
}
