#include "interface.hpp"

IMAGE *background[NUMBACKGROUND];
IMAGE *object[NUMOBJECT];

bool objectDisplay :: in(int x, int y)
{
   if (x1 > x2)
      swap(x1,x2);
   if (y1 > y2)
      swap(y1,y2);
   if (x > x1 && x < x2 && y > y1 && y < y2)
      return true;
   else
      return false;
}

void drawimage(int x, int y, IMAGE *m, IMAGE *p)
{
   putimage(x, y, m, AND_PUT);
   putimage(x, y, p, OR_PUT);
}

// »«Ã≈Õ≈Õ»≈ –¿«Ã≈–¿  ¿–“»Õ »
IMAGE * resize(IMAGE *p, int w, int h)
{
   int wp = imagewidth(p);
   int hp = imageheight(p);
   IMAGE *r=createimage(w, h);
   for (int x = 0; x < w; ++x)
      for (int y = 0; y < h; ++y)
         imageputpixel(r, x, y, imagegetpixel(p, x * wp / w, y * hp / h));
   return r;
}

//-----------------------------------------------—“–¿Õ»÷€-----------------------------------------------//
Pages &Pages :: example()
{
   static Pages pg;
   return pg;
}
void Pages :: draw()
{
    putimage(0, 0, background[Pages :: example().getPage()], COPY_PUT);
}

//-----------------------------------------------Ã≈¡≈À‹-----------------------------------------------//
void objectFurniture :: setT(int type) 
{
   t = type;
   draw();
}
//Œ“–»—Œ¬ ¿
void objectFurniture :: draw()
{
   //«¿À»¬ ¿
   setcolor(t);
   setfillstyle(SOLID_FILL, t);
   bar(x1, y1, x2, y2);
   // ŒÕ“”–
   setcolor(BLACK);
   rectangle(x1, y1, x2, y2);
}
void objectFurniture::press()
{
}
objectFurniture &objectFurniture::example()
{
   static objectFurniture st(0, 0, 0, 0, 1);
   return st;
}
//-----------------------------------------------—“≈Õ€-----------------------------------------------//
void objectWall :: press()
{
}
//Œ“–»—Œ¬ ¿
void objectWall :: draw()
{
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setcolor(RGB(153, 153, 153));
   rectangle(x1, y1, x2, y2);
}
void objectWall :: setW(int widthWall)
{
   w = widthWall;
}
void objectWall :: paramRoom()
{
   weightRoom = x2 - x1;
   heightRoom = y2 - y1;
}
//-----------------------------------------------Õ¿-—“≈Õ≈-----------------------------------------------//
void objectFigureOnWall :: press()
{
}
//Œ“–»—Œ¬ ¿
void objectFigureOnWall :: draw()
{
   setcolor(RGB(243, 243, 243));
   if (numWall == 1)
      line(x1, y1, x1 + imagewidth(objectOnWall), y1);
   else if (numWall == 2)
      line(x1 + imagewidth(objectOnWall), y1, x1 + imagewidth(objectOnWall), y1+ imageheight(objectOnWall));
   else if (numWall == 3)
      line(x1, y1 + imageheight(objectOnWall), x1 + imagewidth(objectOnWall), y1 + imageheight(objectOnWall));
   else if (numWall == 4)
      line(x1, y1, x1, y1+ imageheight(objectOnWall));
   putimage(x1, y1, objectOnWall, TRANSPARENT_PUT);
}
//-----------------------------------------------œ¿–¿Ã≈“–€-----------------------------------------------//
areaParams &areaParams :: example()
{
   static areaParams pa(70, 60, 400, 720);
   return pa;
}
void areaParams :: draw()
{
   char str_w[10], str_h[10];
   char str_w_room[10], str_h_room[10];
   int num = Pages :: example().getPage();
   setcolor(RGB(0, 0, 0));
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   if (num == 0)
   {
      sprintf(str_h, "%d", weightWall); 
      sprintf(str_w, "%d", heightWall);
      sprintf(str_h_room, "%d", 2 * (areaDraw::example().getY2() - areaDraw::example().getY1()) / 3);
      sprintf(str_w_room, "%d", 2 * (areaDraw::example().getX2() - areaDraw::example().getX1()) / 3);
      setcolor(RGB(153, 153, 153));
      outtextxy(230, 407, str_w_room);
      outtextxy(230, 489, str_h_room);
      setcolor(RGB(0, 0, 0));
   }
   else if (num == 1)
   {
      sprintf(str_h, "%d", weightDoor);
      sprintf(str_w, "%d", heightDoor);
   }
   else
   {
      sprintf(str_h, "%d", weightWindow);
      sprintf(str_w, "%d", heightWindow);
   }

   setcolor(COLOR(0, 0, 0));
   outtextxy(230, 241, str_h);
   outtextxy(230, 324, str_w);
}

 void areaParams :: changeParam()
{
   int num = Pages :: example().getPage();
   if (num == 0)
   {
      if ((weightWall > 35 && weightWall < 65) ||
            (heightWall > 250 && heightWall < 500) ||
            (w > 0 && weightWall == 35) ||
            (h > 0 && heightWall == 250) ||
            (w < 0 && weightWall == 65) ||
            (h < 0 && heightWall == 500))
      {
         weightWall += w * 5;
         areaParams :: example().obj = object[(areaParams :: example().weightDoor / 10) % 7 + w];
         heightWall += h * 10;
      }
   }
   else if (num == 1)
   {
      if ((weightDoor > 70 && weightDoor < 90) ||
            (heightDoor > 200 && heightDoor < 240) ||
            (w > 0 && weightDoor == 70) ||
            (h > 0 && heightDoor == 200) ||
            (w < 0 && weightDoor == 90) ||
            (h < 0 && heightDoor == 240))
      {
         weightDoor += w * 10;
         heightDoor += h * 5;
         obj = object[(90 - weightDoor) / 10];
      }
   }
   else
   {
      if ((weightWindow > 100 && weightWindow < 250) ||
            (heightWindow > 110 && heightWindow < 210) ||
            (w > 0 && weightWindow == 100) ||
            (h > 0 && heightWindow == 110) ||
            (w < 0 && weightWindow == 250) ||
            (h < 0 && heightWindow == 210))
      {
         weightWindow += w * 75;
         heightWindow += h * 5;
         obj = object[(250 - weightWindow) / 75 + 3];
      }
   }
   draw();
   swapbuffers();
}

void areaParams :: setParam(int w, int h)
{
   this -> w = w;
   this -> h = h;
}
//-----------------------------------------------–¿¡Œ◊¿ﬂ —–≈ƒ¿-----------------------------------------------//
//–¿¡Œ◊¿ﬂ —–≈ƒ¿
areaDraw &areaDraw :: example()
{
   static areaDraw pa(400, 60, 1280, 720);
   return pa;
}
//Œ“–»—Œ¬ ¿
void areaDraw :: draw()
{
   Pages :: example().draw();
   //‘»√”–€
   for(int i = 0; i < areaDraw :: example().figures.size(); i++)
      figures[i] -> draw();
}
//œ–Œ≈ ÷»ﬂ Œ¡⁄≈ “¿ œ≈–≈ƒ ”—“¿ÕŒ¬ Œ…
void areaDraw :: projection(int x, int y)
{
   if (numRoom)
   {
      IMAGE *a;
      a = areaParams :: example().obj;
      if (a != NULL)
      {
         int numWall;
         IMAGE *m1 = positionOnWall(x, y, numWall, a);
         imageputpixel(m1, 0, 0, WHITE);
         int x1 = x;
         int y1 = y;
         Pages :: example().draw();
         draw();
         if (Pages :: example().getPage() != 3)
         {
            areaParams :: example().draw();
         } setlinestyle(SOLID_LINE, 2, 2);
         
         if (overlay(x1, y1, x1 + imagewidth(m1), y1 + imageheight(m1))) setcolor(RED);
         else setcolor(GREEN);
         rectangle(x1, y1, x1 + imagewidth(m1), y1 + imageheight(m1));
         putimage(x1, y1, m1, TRANSPARENT_PUT);
         swapbuffers();
      }
   }
}
//–≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈
void areaDraw :: press()
{
   int x = mousex();
   int y = mousey();
   if (mousebuttons() == 1)
   {
      if (!numRoom)
         tool();
      else if (x >= coord.x1 && x <= coord.x2
      && y >= coord.y1 && y<= coord.y2)
         tool();
   }
}
//œ–Œ¬≈– ¿ Õ¿ÀŒ∆≈Õ»ﬂ Œ¡⁄≈ “¿ Õ¿ ƒ–”√»≈
bool areaDraw :: overlay(int a, int b, int c, int d)
{
   for (int i = figures.size() - 1; i >= 1; i--)
   {
      int x1 = figures[i] -> getX1();
      int y1 = figures[i] -> getY1();
      int x2 = figures[i] -> getX2();
      int y2 = figures[i] -> getY2();
      if (((x1 <= a && x2 >= a) || (x1 <= c && x2 >= c) ||
         (x1 >= a && x2 <= c)) && ((y1 <= b && y2 >= b) || 
         (y1 <= d && y2 >= d) ||
         (y1 >= b && y2 <= d)))
         return true;
   }
   return false;
}
//—Œ’–¿Õ»“‹
void areaDraw :: save()
{
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(400, 60, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}

//ƒŒ¡¿¬»“‹ Œ¡⁄≈ “
void areaDraw :: addFigure(figure* figure)
{
   figures.push_back(figure);
}

//”ƒ¿À»“‹ Œ¡⁄≈ “
void areaDraw :: deleteFigure(int x, int y)
{
   delay(150);
   int num = Pages :: example().getPage();
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      if (figures[i] -> in(x, y))
      {
         if (figures[i] -> getType() == 2)
         {
            numRoom = 0;
            figures.erase(figures.begin(), figures.end());
            draw();
            if (num != 1 && num != 2 && num != 3) areaParams :: example().draw();
            areaDraw :: example().setCoord(0, 0, 0, 0);
            swapbuffers();
            break;
         }
         figures.erase(figures.begin() + i); 
         draw();
         if (num != 1 && num != 2 && num != 3) areaParams :: example().draw();
         //delay(600);
         swapbuffers();
         break;
      }
   }
}