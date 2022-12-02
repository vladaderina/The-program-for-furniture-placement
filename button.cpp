#include "button.hpp"
#include <math.h>
#include <clocale>

IMAGE *createmask(IMAGE *p)
{
   int w = imagewidth(p);
   int h = imageheight(p);
   IMAGE *m = createimage(w, h);
   int c = imagegetpixel(p, 0, 0);
   for (int x = 0; x < w; ++x)
   {
      for (int y = 0; y < h; ++y)
      {
         int d = imagegetpixel(p, x, y);

         if (c == d)
         {
            imageputpixel(m, x, y, WHITE);
            imageputpixel(p, x, y, BLACK);
         }
         else imageputpixel(m, x, y, BLACK);
      }
   }
   return m;
}

//��������� ������
void button :: draw()
{
   //�������
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

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
void buttonFile :: press()
{
   //��������
   action();
}
//������� �� ������� ������ � �����������
void buttonParam :: press()
{
   int num = Pages :: example().getPage();
   if (num == 0)
   {
      if ((areaParams :: example().weightWall > 35 && areaParams :: example().weightWall < 65) ||
            (areaParams :: example().heightWall > 250 && areaParams :: example().heightWall < 500) ||
            (w > 0 && areaParams :: example().weightWall == 35) ||
            (h > 0 && areaParams :: example().heightWall == 250) ||
            (w < 0 && areaParams :: example().weightWall == 65) ||
            (h < 0 && areaParams :: example().heightWall == 500))
      {
         areaParams :: example().weightWall += w * 5;
         areaParams :: example().heightWall += h * 10;
      }
   }
   else if (num == 1)
   {
      if ((areaParams :: example().weightDoor > 70 && areaParams :: example().weightDoor < 90) ||
            (areaParams :: example().heightDoor > 200 && areaParams :: example().heightDoor < 240) ||
            (w > 0 && areaParams :: example().weightDoor == 70) ||
            (h > 0 && areaParams :: example().heightDoor == 200) ||
            (w < 0 && areaParams :: example().weightDoor == 90) ||
            (h < 0 && areaParams :: example().heightDoor == 240))
      {
         areaParams :: example().weightDoor += w * 10;
         areaParams :: example().heightDoor += h * 5;
      }
   }
   else
   {
      if ((areaParams :: example().weightWindow > 100 && areaParams :: example().weightWindow < 250) ||
            (areaParams :: example().heightWindow > 110 && areaParams :: example().heightWindow < 210) ||
            (w > 0 && areaParams :: example().weightWindow == 100) ||
            (h > 0 && areaParams :: example().heightWindow == 110) ||
            (w < 0 && areaParams :: example().weightWindow == 250) ||
            (h < 0 && areaParams :: example().heightWindow == 210))
      {
         areaParams :: example().weightWindow += w * 75;
         areaParams :: example().heightWindow += h * 5;
      }
   }
   areaParams :: example().draw();
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

/*void arrows(int x1, int y1, int x2, int y2)
{
   char str_w[10], str_h[10];
   int wight = (x2 - x1) / 2;
   int height = (y2 - y1) / 2;
   sprintf(str_w, "%d", wight);
   sprintf(str_h, "%d", height);
   // ����������� ������ � ����� �������
   int d = 30;
   outtextxy(x1 + wight, y1 - d - 10, str_w);
   outtextxy(x1 - d - 20, y1 + height, str_h);
   
   line(x1, y1 - d, x2, y1 - d);
   
   line(x2 - d + 10, y1 - d - 5, x2, y1 - d);
   line(x2, y1 - d, x2 - d + 10, y1 - d + 5);
   line(x1 + d - 10, y1 - d - 5, x1, y1 - d);

   line(x1, y1 - d, x1 + d - 10, y1 - d + 5);
   
   line(x1 - d, y1, x1 - d, y2);
   
   line(x1 - d, y1, x1 - d - 5, y1 + d - 10);
   line(x1 - d, y1, x1 - d + 5, y1 + d - 10);
   line(x1 - d, y2, x1 - d - 5, y2 - d + 10);
   line(x1 - d, y2, x1 - d + 5, y2 - d + 10);
}*/

//��������� ������
void modeFigure(int x1, int y1, int x2, int y2)
{
   int w = areaParams :: example().weightWall;
   setcolor(RGB(70, 70, 70));
   setlinestyle(SOLID_LINE, 2, 2);
   //Pages :: example().draw();
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(7, 20, 7, 10);
   //arrows(x1, y1, x2, y2);
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setwritemode(XOR_PUT);
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
   //������
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
}
//�����
void toolWall()
{
   if (areaDraw :: example().getNumRoom() == 0)
   {
      int x1, y1, x2, y2, w = areaParams :: example().weightWall;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {    
         figure *rect = new objectWall(x1, y1, x2, y2, w);
         rect -> draw();
         areaDraw :: example().setCenter(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2));
         areaDraw :: example().setCoord(x1, y1, x2, y2);
         areaDraw :: example().addFigure(rect);
         areaDraw :: example().setNumRoom(1);
      }
   }
   else
   {
      IMAGE *image =  loadBMP("icon/back/text1.jpg");
      putimage(64, 556, image, COPY_PUT);
   }
}
//����
void toolWindow()
{

}
//������������ ������� �� �����
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a)
{
   IMAGE *b = imageturn(a, 90, WHITE);
   IMAGE *c = imageturn(a, 180, WHITE);
   IMAGE *d = imageturn(a, 270, WHITE);
   int centerY = areaDraw :: example().getCenterY();
   int centerX = areaDraw :: example().getCenterX();
   int xt1 = areaDraw :: example().getX1();
   int yt1 = areaDraw :: example().getY1();
   int xt2 = areaDraw :: example().getX2();
   int yt2 = areaDraw :: example().getY2();

   if (double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) &&
         y1 >= yt1 && y1 <= centerY &&
         double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      y1 = yt1;
      numWall = 1;
      return a;
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) &&
            y1 <= yt2 && y1 >= centerY &&
            double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      y1 = yt2 - imageheight(c);
      numWall = 3;
      return c;
   }
   else if (double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) &&
            x1 <= xt2 && x1 >= centerX &&
            double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      x1 = xt2 - imagewidth(d);
      numWall = 2;
      return d;
   }
   else
   {
      x1 = xt1;
      numWall = 4;
      return b;
   }
}
//�����
void toolDoor()
{
   if (areaDraw :: example().getNumRoom() != 0)
   {
      int x1, y1, numWall;
      x1 = mousex();
      y1 = mousey();
      IMAGE *a = loadBMP("icon/wall.bmp");
      IMAGE *m = positionOnWall(x1, y1, numWall, a);
      figure *rect= new objectFigureOnWall(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), numWall, m);
      rect -> m = createmask(m);
      rect -> draw();
      areaDraw :: example().addFigure(rect);
   }
   else
   {
      IMAGE *image =  loadBMP("icon/back/text2.jpg");
      putimage(61, 556, image, COPY_PUT);
   }
}

//��������� � ������
void fileSave()
{
   areaDraw::example().save();
}
//������� ���������
void fileEnd()
{
   closegraph();
}