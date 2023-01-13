#include "button.hpp"
#include <math.h>
#include <clocale>

// Œ“–»—Œ¬ ¿  ÕŒœ »
void button :: draw()
{
   
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ
void buttonFile :: press()
{
   // ƒ≈…—“¬»≈
   action();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » — œ¿–¿Ã≈“–¿Ã»
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » œ≈–≈ Àﬁ◊≈Õ»ﬂ —“–¿Õ»÷€
void buttonPage :: press()
{
   int p = Pages :: example().getCurrentPage();
   if (p == 3 || p == 4) Pages :: example().setListFurniturePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaDraw :: example().setTool(NULL);
   swapbuffers();
   delay(200);
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ
void buttonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().setType(1);
   if (page != 3)
   {
      areaParams :: example().draw();
   }
   if (page == 1)
      areaParams :: example().obj = object[((90 - areaParams :: example().weightDoor) / 10) % 3];
   else if (page == 2)
      areaParams :: example().obj = object[((250 - areaParams :: example().weightWindow) / 75) + 3];
   else areaParams :: example().obj = NULL;
   areaDraw :: example().setTool(tool);
   swapbuffers();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » Ã≈¡≈À»
void buttonFurniture :: press()
{
   int p = Pages :: example().getCurrentPage();
   string obj = "object/"+ to_string(p - 4) + "/" + to_string(num) + ".bmp";
   Pages :: example().setListTypePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().obj = loadBMP(obj.c_str());
   areaParams :: example().setType(2);
   areaDraw :: example().setTool(tool);
   swapbuffers();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » Õ¿«¿ƒ
void buttonBack :: press()
{
   int m = Pages :: example().getListFurniturePage();
   int n = Pages :: example().getListTypePage();
   int p = Pages :: example().getCurrentPage();
   if (p == 23) Pages :: example().setCurrentPage(n);
   else if (p >= 5 && p <= 22) Pages :: example().setCurrentPage(m);
   Pages :: example().draw();
   areaDraw :: example().draw();
   swapbuffers();
   delay(200);
}

// ”ƒ¿À»“‹
void toolDelete()
{
   //  ”–—Œ–
   int x = mousex();
   int y = mousey();
   // ”ƒ¿À≈Õ»≈ ‘»√”–€,  Œ“Œ–Œ… œ–»Õ¿ƒÀ≈∆»“ “Œ◊ ¿ ¬  Œ“Œ–Œ… Õ¿’Œƒ»“—ﬂ  ”–—Œ–
   areaDraw :: example().deleteFigure(x, y);
}
 
// Ã≈¡≈À‹
void toolFurniture()
{
   // ◊»“¿≈Ã ÿ»–»Õ” » ¬€—Œ“” »« ‘¿…À¿
   //string t  ="cfg/" + to_string(objectFurniture::example().getT() + 1) + ".txt";
   //FILE *f = fopen(t.c_str(), "r");
   //fscanf(f, "%d:%d", &w, &h);
   //fclose(f);
   int x1 = mousex();
   int y1 = mousey();
   IMAGE *m = areaParams :: example().obj;
   // putimage(x1, y1, m, TRANSPARENT_PUT);
   if (!areaDraw :: example().getNumRoom()) throw NoRoomError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()) && 
               areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m), y1 + imageheight(m))) throw ObjectOverlayError();
   else if (areaDraw :: example().inRoom(x1, y1))
   {
      figure *rect = new objectFurniture(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), m);
      areaDraw :: example().addFigure(rect);
      for (int i = 0; i < areaDraw :: example().figures.size(); i++)
         areaDraw :: example().figures[i] -> draw();
      areaDraw :: example().projection(x1, y1);
   }
   swapbuffers();
   delay(200);
}

// œ¿–¿Ã≈“–€ ‘»√”–€
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

// –¿—“ﬂ√»¬¿Õ»≈ ‘»√”–€ œ–» –»—Œ¬¿Õ»»
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

// —“≈Õ¿
void toolWall()
{
   areaParams :: example().obj = NULL;
   if (areaDraw :: example().getNumRoom() != 0) throw ManyRoomsError();
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
         areaDraw :: example().draw();
         swapbuffers();
         areaDraw :: example().draw();
         areaDraw :: example().setNumRoom(1);
      }
   }
   swapbuffers();
}

// –¿—œŒÀŒ∆≈Õ»≈ Œ¡⁄≈ “¿ Õ¿ —“≈Õ≈
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

// Œ¡⁄≈ “€ Õ¿ —“≈Õ≈
void toolOnWall()
{
   int x1, y1, numWall;
   x1 = mousex();
   y1 = mousey();
   IMAGE *a;
   a = areaParams :: example().obj;
   IMAGE *m = positionOnWall(x1, y1, numWall, a);
   if (!areaDraw :: example().getNumRoom()) throw NoRoomError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()) && 
               areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m), y1 + imageheight(m))) throw ObjectOverlayError();
   else if (areaDraw :: example().inRoom(x1, y1))
   {
      figure *rect = new objectFigureOnWall(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), numWall, m);
      areaDraw :: example().addFigure(rect);
      for (int i = 0; i < areaDraw :: example().figures.size(); i++)
         areaDraw :: example().figures[i] -> draw();
      areaDraw :: example().projection(x1, y1);
   }
   swapbuffers();
   delay(200);
}

// —Œ’–¿Õ»“‹ ¬ œ–Œ≈ “
void fileSave()
{
   areaDraw::example().save();
}
// «¿ –€“‹ œ–Œ√–¿ÃÃ”
void fileEnd()
{
   closegraph();
}