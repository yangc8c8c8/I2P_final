#ifndef CONSOLE_DRAW3_
#define CONSOLE_DRAW3_
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 180
extern void putASCII2( int x, int y, int ch, int fgcolor, int bgcolor );
extern void putString(int x, int y, char *p, int fg_color, int bg_color);
extern void drawCmdWindow();
extern void clearScreen();
extern void saveScreen();
extern void restoreScreen();
#endif
/*
putASCII2()  �̫��ӰѼƤ��O�O�r���e���M�I�����C��
�i�H�ѦҤU�����C��ȹ�Ӫ�ӳ]�w�A�Q�n���C��

   0: ��     1: �t��   2: �t��   3: �t�C
   4: �t��   5: �t��   6: �t��   7: �L��
   8: �t��   9: �G��  10: �G��  11: �G�C
  12: �G��  13: �G��  14: �G��  15: ��
*/
