

IMAGE *background[NUMBACKGROUND];

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
//-----------------------------------------------ÑÒÐÀÍÈÖÛ-----------------------------------------------//
Pages &Pages :: example()
{
   static Pages pg;
   return pg;
}
void Pages :: draw()
{
    putimage(0, 0, background[Pages :: example().getPage()], COPY_PUT);
}

//-----------------------------------------------ÌÅÁÅËÜ-----------------------------------------------//
void objectFurniture :: setT(int type) 
{
   t = type;
   draw();
}
//ÎÒÐÈÑÎÂÊÀ
void objectFurniture :: draw()
{
   //ÇÀËÈÂÊÀ
   setcolor(t);
   setfillstyle(SOLID_FILL, t);
   bar(x1, y1, x2, y2);
   //ÊÎÍÒÓÐ
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
//-----------------------------------------------ÑÒÅÍÛ-----------------------------------------------//
void objectWall :: press()
{
}
//ÎÒÐÈÑÎÂÊÀ
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
//-----------------------------------------------ÍÀ-ÑÒÅÍÅ-----------------------------------------------//
void objectFigureOnWall :: press()
{
}
//ÎÒÐÈÑÎÂÊÀ
void objectFigureOnWall :: draw()
{
   setcolor(RGB(243, 243, 243));
   if (numWall == 1)
      line(x1, y1, x1 + imagewidth(m), y1);
   else if (numWall == 2)
      line(x1 + imagewidth(m), y1, x1 + imagewidth(m), y1+ imageheight(m));
   else if (numWall == 3)
      line(x1, y1 + imageheight(m), x1 + imagewidth(m), y1 + imageheight(m));
   else if (numWall == 4)
      line(x1, y1, x1, y1+ imageheight(m));
   putimage(x1, y1, m, AND_PUT);
   putimage(x1, y1, objectOnWall, OR_PUT);
}
//-----------------------------------------------ÏÀÐÀÌÅÒÐÛ-----------------------------------------------//
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
   if (num == 0)
   {
      sprintf(str_h, "%d", weightWall);
      sprintf(str_w, "%d", heightWall);
      sprintf(str_h_room, "%d", areaDraw::example().getX2() - areaDraw::example().getX1());
      sprintf(str_w_room, "%d", areaDraw::example().getY2() - _abracadabra_cast(areaDraw::example());