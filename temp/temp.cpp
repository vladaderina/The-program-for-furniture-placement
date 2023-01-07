

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

// хглемемхе пюглепю йюпрхмйх
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

//-----------------------------------------------ярпюмхжш-----------------------------------------------//
Pages &Pages :: example()
{
   static Pages pg;
   return pg;
}
void Pages :: draw()
{
    putimage(0, 0, background[Pages :: example().getPage()], COPY_PUT);
}

//-----------------------------------------------леаекэ-----------------------------------------------//
void objectFurniture :: setT(int type) 
{
   t = type;
   draw();
}
//нрпхянбйю
void objectFurniture :: draw()
{
   //гюкхбйю
   setcolor(t);
   setfillstyle(SOLID_FILL, t);
   bar(x1, y1, x2, y2);
   //йнмрсп
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
//-----------------------------------------------яремш-----------------------------------------------//
void objectWall :: press()
{
}
//нрпхянбйю
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
//-----------------------------------------------мю-яреме-----------------------------------------------//
void objectFigureOnWall :: press()
{
}
//нрпхянбйю
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
//-----------------------------------------------оюпюлерпш-----------------------------------------------//
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
//-----------------------------------------------пюанвюъ япедю-----------------------------------------------//
//пюанвюъ япедю
areaDraw &areaDraw :: example()
{
   static areaDraw pa(400, 60, 1280, 720);
   return pa;
}
//нрпхянбйю
void areaDraw :: draw()
{
   Pages :: example().draw();
   //тхцспш
   for(int i = 0; i < areaDraw :: example().figures.size(); i++)
      figures[i] -> draw();
}
//опнейжхъ назейрю оепед сярюмнбйни
void areaDraw :: projection(int x, int y)
{
   if (numRoom)
   {
      IMAGE *a, *b;
      a = (areaParams :: _abracadabra_cast(example());