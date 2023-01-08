#include "button.hpp"
#include <math.h>
#include <clocale>

//IMAGE *errorRoom = loadBMP("icon/back/text1.jpg");
//Error manyRoom(64, 556, errorRoom);

//нрпхянбйю ймнойх
void button :: draw()
{
   //гюкхбйю
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   //йнмрсп
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
   rectangle(x1, y1, x2, y2);
}
//пеюйжхъ мю мюфюрхе ймнойх леаекх
void buttonFurniture :: press()
{
   //сярюмнбхрэ хмярпслемр х рхо рхо леаекх
   areaDraw::example().setTool(tool);
   objectFurniture::example().setT(type);
}
//пеюйжхъ мю мюфюрхе ймнойх пюанрш я тюикнл
void buttonFile :: press()
{
   //деиярбхе
   action();
}
//пеюйжхъ мю мюфюрхе ймнойх я оюпюлерпюлх
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}
//пеюйжхъ мю мюфюрхе ймнойх хмярпслемрюпхъ
void buttonTools :: press()
{
   int numPage = Pages :: example().getPage();
   if (numPage == 1)
      areaParams :: example().obj = object[((90 - areaParams :: example().weightDoor) / 10) % 3];
   else if (numPage == 2)
      areaParams :: example().obj = object[((250 - areaParams :: example().weightWindow) / 75) + 3];
   else areaParams :: example().obj = NULL;
   areaDraw :: example().setTool(tool);
}
//сдюкхрэ
void toolDelete()
{
   //йспянп
   int x = mousex();
   int y = mousey();
   //сдюкемхе тхцспш, йнрнпни опхмюдкефхр рнвйю б йнрнпни мюундхряъ йспянп
   areaDraw :: example().deleteFigure(x, y);
}

//леаекэ
void toolFurniture()
{
   //йннпдхмюрш
   int x1, y1, x2, y2; //йннпдхмюрш

   //ьхпхмю х бшянрю
   int w, h;

   //вхрюел ьхпхмс х бшянрс хг тюикю
   string t  ="cfg/" + to_string(objectFurniture::example().getT() + 1) + ".txt";
   FILE *f = fopen(t.c_str(), "r");
   fscanf(f, "%d:%d", &w, &h);
   fclose(f);

   //йннпдхмюрш
   x1 = 200;
   y1 = 100;

   int k = getch();
   while (1) {
      //оепелеыемхе тхцспш
      k = getch();
      //бмхг
      if (k == KEY_DOWN) {
         y1 += 10;
      }
      //ббепу
      if (k == KEY_UP) {
         y1 -= 10;
      }
      //бкебн
      if (k == KEY_LEFT)
      {
         x1 -= 10;
      }
      //бопюбн
      if (k == KEY_RIGHT)
      {
         x1 += 10;
      }
      //онбнпнр
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
      //пюявер х нрпхянбйю
      x2 = x1 + w;
      y2 = y1 + h;
      //ондрбепфдемхе сярюмнбйх леаекх
      if (k == KEY_ENTER) {
         setfillstyle(SOLID_FILL, objectFurniture::example().getT());
         bar(x1, y1, x2, y2);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
         //ме мюйкюдшбюрэ тхцспш дпсц мю дпсцю
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
   //назейр
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
}
//оюпюлерпш тхцспш
void modeFigure(int x1, int y1, int x2, int y2)
{
   char str_w[10], str_h[10];
   int w = areaParams :: example().weightWall;
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().draw();
   int wight = 2 * (x2 - x1) / 3;
   int height = 2 * (y2 - y1) / 3;
   sprintf(str_w, "%d", wight);
   sprintf(str_h, "%d", height);
   setcolor(RGB(153, 153, 153));
   outtextxy(230, 407, str_w);
   outtextxy(230, 489, str_h);
   setcolor(RGB(200, 200, 200));
   rectangle(x1, y1, x2, y2);
   swapbuffers();
}
//пюяръцхбюмхе тхцспш опх пхянбюмхх
bool modeStretch(int &x1, int &y1, int &x2, int &y2, void (*shape)(int x1, int y1, int x2, int y2))
{
   x1 = mousex();
   y1 = mousey();
   x2 = x1;
   y2 = y1;
   shape(x1, y1, x2, y2);
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
      if ((cursorX - x1 > 0) && (cursorY - y1 > 0))
      {
         shape(x1, y1, x2, y2);
         x2 = cursorX;
         y2 = cursorY;
         shape(x1, y1, x2, y2);
      }
   }
   shape(x1, y1, x2, y2);
   return 1;
}

//яремю
void toolWall()
{
   areaParams :: example().obj = NULL;
   if (areaDraw :: example().getNumRoom() != 0) throw manyRooms();
   else
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
   swapbuffers();
}

//пюяонкнфемхе назейрю мю яреме
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
      if (x1 > xt2 - imagewidth(a)) x1 = xt2 - imagewidth(a);
      numWall = 1;
      return a;
   }
   else if (double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) &&
            x1 <= xt2 && x1 >= centerX &&
            double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      x1 = xt2 - imagewidth(d);
      if (y1 > yt2 - imageheight(d)) y1 = yt2 - imageheight(d);
      numWall = 2;
      return d;
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) &&
            y1 <= yt2 && y1 >= centerY &&
            double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      y1 = yt2 - imageheight(c);
      if (x1 > xt2 - imagewidth(c)) x1 = xt2 - imagewidth(c);
      numWall = 3;
      return c;
   }
   else
   {
      x1 = xt1;
      if (y1 > yt2 - imageheight(b)) y1 = yt2 - imageheight(b);
      numWall = 4;
      return b;
   }
}

//нймн
void toolWindow()
{
   if (areaDraw :: example().getNumRoom() == 0) throw noRoom();
   else
   {
      int x1, y1, numWall;
      x1 = mousex();
      y1 = mousey();
      IMAGE *a;
      a = areaParams :: example().obj;
      IMAGE *m = positionOnWall(x1, y1, numWall, a);
      figure *rect = new objectFigureOnWall(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), numWall, m);
      rect -> draw();
      areaDraw :: example().addFigure(rect);
   }
   swapbuffers();
}

//дбепэ
void toolDoor()
{
   if (areaDraw :: example().getNumRoom() == 0) throw noRoom();
   else
   {
      int x1, y1, numWall;
      x1 = mousex();
      y1 = mousey();
      IMAGE *a;
      a = areaParams :: example().obj;
      imageputpixel(a, 0, 0, WHITE);
      IMAGE *m = positionOnWall(x1, y1, numWall, a);
      figure *rect= new objectFigureOnWall(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), numWall, m);
      rect -> draw();
      areaDraw :: example().addFigure(rect);
   }
   swapbuffers();
}
//янупюмхрэ б опнейр
void fileSave()
{
   areaDraw::example().save();
}
//гюйпшрэ опнцпюллс
void fileEnd()
{
   closegraph();
}