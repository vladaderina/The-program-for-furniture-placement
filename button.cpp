#include "button.hpp"
#include <math.h>
#include <clocale>

///---------------------------- À¿—— ƒÀﬂ  ÕŒœŒ  —Œ’–¿Õ≈Õ»ﬂ » ¬€’Œƒ¿-------------------------------------//
void buttonFile :: press()
{
   // ƒ≈…—“¬»≈
   action();
}

//----------------------------------------------- À¿—— ƒÀﬂ  ÕŒœŒ  »«Ã≈Õ≈Õ»ﬂ œ¿–¿Ã≈“–Œ¬----------------------------------------------//
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

//----------------------------------------------- À¿——  ÕŒœŒ  ƒÀﬂ ¬Œ«¬–¿“¿ Õ¿ œ–≈ƒ€ƒ”Ÿ”ﬁ —“–¿Õ»÷”-----------------------------------------------//
void buttonBack :: press()
{
   int m = Pages :: example().getListFurniturePage();
   int n = Pages :: example().getListTypePage();
   int p = Pages :: example().getCurrentPage();
   if (p == 23) 
   {
      Pages :: example().setCurrentPage(n);
      areaParams :: example().obj = NULL;
   }
   else if (p >= 5 && p <= 22) Pages :: example().setCurrentPage(m);
   areaParams :: example().rotationFurniture = 0;
   areaParams :: example().heightFurniture = 0;
   areaDraw :: example().setTool(NULL);
   Pages :: example().draw();
   areaDraw :: example().draw();
   swapbuffers();
   delay(200);
}

//----------------------------------------------- À¿——  ÕŒœŒ  ƒÀﬂ œ≈–≈’Œƒ¿ Õ¿ —“–¿Õ»÷”-----------------------------------------------//
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
//----------------------------------------------- À¿——  ÕŒœŒ  »Õ—“–”Ã≈“¿–»ﬂ-----------------------------------------------//
void buttonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().setType(1);
   areaParams :: example().draw();
   if (page == 1)
   {
      areaParams :: example().obj = object[((90 - areaParams :: example().weightDoor) / 10) % 3];
      areaParams :: example().heightLift = 0;
      areaParams :: example().height = areaParams :: example().heightDoor;
   }
   else if (page == 2)
   {
      areaParams :: example().obj = object[((250 - areaParams :: example().weightWindow) / 75) + 3];
      areaParams :: example().heightLift = 150;
      areaParams :: example().height = areaParams :: example().heightWindow;
   }
   else areaParams :: example().obj = NULL;
   areaDraw :: example().setTool(tool);
   swapbuffers();
}

//----------------------------------------------- À¿——  ÕŒœŒ  Ã≈¡≈À»-----------------------------------------------//
void buttonFurniture :: press()
{
   int p = Pages :: example().getCurrentPage();
   string param = "object/"+ to_string(p - 4) + "/param.cfg";
   ifstream file(param);
   int m;
   string s;
   int k;
   int j = 0;
   while (getline(file, s))
   {
      j++;
      if (j == num)
      {
         areaParams :: example().name.clear();
         int i = 0;
         while (s[i] != ':')
         {
            areaParams :: example().name += s[i];
            i++;
         }
         k = i + 2;
         istringstream s1(s.substr(k));
         s1 >> areaParams :: example().height;
      }
   }
   file.close();
   
   string obj = "object/"+ to_string(p - 4) + "/" + to_string(num) + ".bmp";
   areaParams :: example().obj = loadBMP(obj.c_str());
   Pages :: example().setListTypePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   swapbuffers();
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().heightLift = 0;
   areaDraw :: example().setTool(tool);
   setbkcolor(WHITE);
   setcolor(BLACK);
   settextjustify(LEFT_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   const char * c = areaParams :: example().name.c_str();
   outtextxy(120, 123, c);
   cout << 11;
   swapbuffers();
}

//-----------------------------------------------‘”Õ ÷»»-----------------------------------------------//
//-----------------------------------------------”ƒ¿À»“‹-----------------------------------------------//
void toolDelete()
{
   //  ”–—Œ–
   int x = mousex();
   int y = mousey();
   // ”ƒ¿À≈Õ»≈ ‘»√”–€,  Œ“Œ–Œ… œ–»Õ¿ƒÀ≈∆»“ “Œ◊ ¿ ¬  Œ“Œ–Œ… Õ¿’Œƒ»“—ﬂ  ”–—Œ–
   areaDraw :: example().deleteFigure(x, y);
}
 
//-----------------------------------------------Ã≈¡≈À‹-----------------------------------------------//
void toolFurniture()
{
   int x1 = mousex();
   int y1 = mousey();
   IMAGE *a = areaParams :: example().obj;
   IMAGE *m;
   int numWall;
   if (areaParams :: example().getType() == 1) m = positionOnWall(x1, y1, numWall, a);
   else m = a;
   int height = areaParams :: example().height;
   int heightLift = areaParams :: example().heightFurniture;
   if (x1 + imagewidth(m) > areaDraw :: example().getX2()) x1 = areaDraw :: example().getX2() - imagewidth(m);
   if (y1 + imageheight(m) > areaDraw :: example().getY2()) y1 = areaDraw :: example().getY2() - imageheight(m);
   if (!areaDraw :: example().getNumRoom()) throw NoRoomError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()) && 
               areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), height, heightLift)) throw ObjectOverlayError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()))
   {
      if (x1 + imagewidth(m) > areaDraw :: example().getX2()) x1 = areaDraw :: example().getX2() - imagewidth(m);
      if (y1 + imageheight(m) > areaDraw :: example().getY2()) y1 = areaDraw :: example().getY2() - imageheight(m);
      figure *rect = new objectFurniture(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), 
                                                            height, heightLift, m);
      areaDraw :: example().addFigure(rect);
      areaDraw :: example().draw();
      areaDraw :: example().projection(x1, y1);
   }
   swapbuffers();
   delay(200);
}

//-----------------------------------------------œ¿–¿Ã≈“–€ —“≈Õ€-----------------------------------------------//
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

//-----------------------------------------------–¿—“ﬂ√»¬¿Õ»≈ —“≈Õ€ œ–» –»—Œ¬¿Õ»»-----------------------------------------------//
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

//-----------------------------------------------—“≈Õ¿-----------------------------------------------//
void toolWall()
{
   areaParams :: example().obj = NULL;
   if (areaDraw :: example().getNumRoom() != 0) throw ManyRoomsError();
   else
   {
      int x1, y1, x2, y2, w = areaParams :: example().weightWall;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {
         figure *rect = new objectWall(x1, y1, x2, y2, areaParams :: example().heightWall, w);
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

//-----------------------------------------------–¿—œŒÀŒ∆≈Õ»≈ Œ¡⁄≈ “¿ Õ¿ —“≈Õ≈-----------------------------------------------//
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a)
{
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
      IMAGE *d = imageturn(a, 270, WHITE);
      x1 = xt2 - imagewidth(d);
      if (y1 > yt2 - imageheight(d)) y1 = yt2 - imageheight(d);
      numWall = 2;
      return d;
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) &&
            y1 <= yt2 && y1 >= centerY &&
            double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {   
      IMAGE *c = imageturn(a, 180, WHITE);
      y1 = yt2 - imageheight(c);
      if (x1 > xt2 - imagewidth(c)) x1 = xt2 - imagewidth(c);
      numWall = 3;
      return c;
   }
   else
   {
      IMAGE *b = imageturn(a, 90, WHITE);
      x1 = xt1;
      if (y1 > yt2 - imageheight(b)) y1 = yt2 - imageheight(b);
      numWall = 4;
      return b;
   }
}

//-----------------------------------------------Œ¡⁄≈ “€ Õ¿ —“≈Õ≈-----------------------------------------------//
void toolOnWall()
{
   int x1, y1, numWall;
   x1 = mousex();
   y1 = mousey();
   IMAGE *a;
   a = areaParams :: example().obj;
   IMAGE *m = positionOnWall(x1, y1, numWall, a);
   int height = areaParams :: example().height;
   int heightLift = areaParams :: example().heightLift;
   if (!areaDraw :: example().getNumRoom()) throw NoRoomError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()) && 
               areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), height, heightLift)) throw ObjectOverlayError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()))
   {
      figure *rect = new objectFigureOnWall(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), 
      numWall, height, heightLift, m);
      areaDraw :: example().addFigure(rect);
      areaDraw :: example().draw();
      areaDraw :: example().projection(x1, y1);
   }
   swapbuffers();
   delay(200);
}

//-----------------------------------------------—Œ’–¿Õ»“‹-----------------------------------------------//
void fileSave()
{
   areaDraw::example().save();
}
//-----------------------------------------------¬€…“»-----------------------------------------------//
void fileEnd()
{
   closegraph();
}