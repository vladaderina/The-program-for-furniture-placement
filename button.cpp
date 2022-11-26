#include "button.hpp"
#include <math.h>
#include <clocale>

//��������� ������
void button::draw()
{

   //�������
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   //������
   putimage(x1 + 1, y1 + 1, image, COPY_PUT);

   //������
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
   rectangle(x1, y1, x2, y2);
}
//������� �� ������� ������ ������
void buttonFurniture :: press()
{
   //���������� ���������� � ��� ��� ������
   areaDraw::example().setTool(tool);
   objectFurniture::example().setT(type);
}
//������� �� ������� ������ ������ � ������
void buttonFile::press()
{
   //��������
   action();
}
//������� �� ������� ������ ��������������
void buttonTools :: press()
{
   areaDraw :: example().setTool(tool);
}
//�������
void toolDelete()
{
   //������
   int x = mousex();
   int y = mousey();
   //�������� ������, ������� ����������� ����� � ������� ��������� ������
   areaDraw :: example().deleteFigure(x, y);
}
//��������� ������
void modeFigure(int x1, int y1, int x2, int y2)
{
   setwritemode(XOR_PUT);
   setcolor(WHITE);
   rectangle(x1, y1, x2, y2);
   setwritemode(COPY_PUT);
}
//������������ ������ ��� ���������
bool modeStretch(int &x1, int &y1, int &x2, int &y2, void (*shape)(int x1, int y1, int x2, int y2))
{
   x1 = mousex();
   y1 = mousey();
   x2 = x1;
   y2 = y1;
   shape(x1, y1, x2, y2);
   int x5;
   int x6;
   int y5;
   int y6;
   while (1)
   {
      int cursorClick = mousebuttons();
      if (!cursorClick)
      {
         break;
      }
      int cursorX = mousex();
      int cursorY = mousey();
      if (!areaDraw :: example().in(cursorX, cursorY))
      {
         shape(x1, y1, x2, y2);
         return 0;
      }
      if (cursorX != x2 || cursorY != y2)
      {
         shape(x1, y1, x2, y2);
         x2 = cursorX;
         y2 = cursorY;
         shape(x1, y1, x2, y2);
      }
   }
   shape(x1, y1, x2,y2);
   return 1;
}

//������
void toolFurniture()
{
   //����������
   int x1, y1, x2, y2; //����������

   //������ � ������
   int w, h;

   //������ ������ � ������ �� �����
   string t  ="cfg/" + to_string(objectFurniture::example().getT() + 1) + ".txt";
   FILE *f = fopen(t.c_str(), "r");
   fscanf(f, "%d:%d", &w, &h);
   fclose(f);

   //����������
   x1 = 200;
   y1 = 100;

   int k = getch();
   while (1) {
      //����������� ������
      k = getch();
      //����
      if (k == KEY_DOWN) {
         y1 += 10;
      }
      //�����
      if (k == KEY_UP) {
         y1 -= 10;
      }
      //�����
      if (k == KEY_LEFT)
      {
         x1 -= 10;
      }
      //������
      if (k == KEY_RIGHT)
      {
         x1 += 10;
      }
      //�������
      if (k == KEY_SHIFT)
      {
         swap(w, h);
      }
      if (x1 < 100) {
         x1 += 10;
      }
      if (y1 < 20) {
         y1 += 10;
      }
      if (y2 > 550) {
         y1 -= 10;
      }
      if (x2 > 750) {
         x1 -= 10;
      }
      //������ � ���������
      x2 = x1 + w;
      y2 = y1 + h;
      modeFigure(x1, y1, x2, y2);
      //������������� ��������� ������
      if (k == KEY_ENTER) {
         setfillstyle(SOLID_FILL, objectFurniture::example().getT());
         bar(x1, y1, x2, y2);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
         //�� ����������� ������ ���� �� �����
         for (int i = x1; i < x2; i++)
         {
            for (int j = y1; j < y2; j++)
            {
               areaDraw::example().deleteFigure(i, j);
            }
         }
         break;
      }
   }
   //����������� ������
   string tittle = to_string(objectFurniture::example().getT());
   setcolor(WHITE);
   setbkcolor(COLOR(63, 63, 63));
   outtextxy(x1, y1, tittle.c_str());
   //������
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
   areaDraw::example().outputObjects();
}
//�����
void toolWall()
{
   if (areaDraw :: example().getNumRoom() == 0)
   {
      int x1, y1, x2, y2, w = 1;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {
         setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
      }
      figure *ptr = new objectWall(x1, y1, x2, y2, w);
      cout << x1 << "\n" << y1 << "\n" << x2 << "\n" << y2 << "\n";
      areaDraw :: example().setCenter(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2));
      cout << areaDraw :: example().getCenterX() << " " << areaDraw :: example().getCenterY();
      areaDraw :: example().setCoord(x1, y1, x2, y2);
      areaDraw :: example().addFigure(ptr);
      areaDraw :: example().outputObjects();
      areaDraw :: example().setNumRoom(1);
   }
   else
   {
      setbkcolor(WHITE);
      settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(9, 20, 9, 10);
      setcolor(COLOR(227, 38, 54));
      string warning = "����� ������� ������ ���� �������!";
      outtextxy(80, 600,  warning.c_str());
   }
}
//����
void toolWindow()
{
   /*int x1, y1, x2, y2;
   if(modeStrtch(x1, y1, x2, y2, modeFigure))
   {
      setfillstyle(SOLID_FILL, COLOR(178, 255, 255));
      bar(x1, y1, x2, y2);
      setcolor(BLACK);
      rectangle(x1, y1, x2, y2);
   }
   figure* rect = new objectFigureOnWall(x1, y1, x2, y2);
   areaDraw::example().addFigure(rect);
   areaDraw::example().outputObjects();*/
}

//�����
void toolDoor()
{
   int x1, y1;
   x1 = mousex();
   y1 = mousey();
   IMAGE *a = loadBMP("icon/wall.bmp");
   int centerY = areaDraw::example().getCenterY();
   int centerX = areaDraw::example().getCenterX();
   int xt1 = areaDraw::example().getX1();
   int yt1 = areaDraw::example().getY1(); 
   int xt2 = areaDraw::example().getX2();
   int yt2 = areaDraw::example().getY2();
   
   if (double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) && 
       y1 >= yt1 && y1 <= centerY &&
       double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      figure *rect = new objectFigureOnWall(x1, yt1, x1 + imagewidth(a), yt1 + imageheight(a), a);
      putimage(x1, yt1, a, COPY_PUT);
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) && 
      y1 <= yt2 && y1 >= centerY &&
      double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      figure *rect = new objectFigureOnWall(x1, yt2, x1 + imagewidth(a), yt2 + imageheight(a), a);
      putimage(x1, yt2, a, COPY_PUT);
   }
   else if (double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
      x1 <= xt2 && x1 >= centerX &&
      double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      figure *rect = new objectFigureOnWall(xt2, y1, xt2 + imagewidth(a), y1 + imageheight(a), a);
      putimage(xt2, y1, a, COPY_PUT);
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
      x1 >= xt1 && x1 <= centerX &&
      double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      figure *rect = new objectFigureOnWall(xt1, y1, xt1 + imagewidth(a), y1 + imageheight(a), a);
      putimage(xt1, y1, a, COPY_PUT);
   }
   areaDraw::example().addFigure(rect);
   //areaDraw::example().outputObjects();
}

//��������� � ������
void fileSave()
{
   areaDraw::example().save();
}
//������� ���������
void fileEnd()
{
   closegraph(CURRENT_WINDOW);
}