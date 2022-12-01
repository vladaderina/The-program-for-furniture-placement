#include "interface.hpp"

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
//-----------------------------------------------ÑÒĞÀÍÈÖÛ-----------------------------------------------//
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
//ÑÎÕĞÀÍÅÍÈÅ ÎÁÚÅÊÒÀ
void objectFurniture::save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
   fwrite(&t, sizeof(int), 1, f);
}
void objectFurniture :: setT(int type) 
{
   t = type;
   draw();
}
//ÎÒĞÈÑÎÂÊÀ
void objectFurniture :: draw()
{
   //ÇÀËÈÂÊÀ
   setcolor(t);
   setfillstyle(SOLID_FILL, t);
   bar(x1, y1, x2, y2);
   //ÊÎÍÒÓĞ
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
//ÑÎÕĞÀÍÅÍÈÅ ÎÁÚÅÊÒÀ
void objectWall :: save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
   fwrite(&w, sizeof(int), 1, f);
}
void objectWall :: press()
{
}
//ÎÒĞÈÑÎÂÊÀ
void objectWall :: draw()
{
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setcolor(RGB(153,153,153));
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
//ÑÎÕĞÀÍÅÍÈÅ ÎÁÚÅÊÒÀ
void objectFigureOnWall :: save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
}
//ÎÒĞÈÑÎÂÊÀ
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
//-----------------------------------------------ÏÀĞÀÌÅÒĞÛ-----------------------------------------------//
areaParams &areaParams :: example()
{
   static areaParams pa(70, 60, 400, 720);
   return pa;
}
void areaParams :: draw()
{
   char str_w[10], str_h[10];
   int num = Pages :: example().getPage();
   if (num == 0)
   {
      sprintf(str_h, "%d", weightWall);
      sprintf(str_w, "%d", heightWall);
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

   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);

   setcolor(COLOR(0, 0, 0));
   outtextxy(230, 241, str_h);
   outtextxy(230, 324, str_w);
}
//-----------------------------------------------ĞÀÁÎ×Àß ÑĞÅÄÀ-----------------------------------------------//
//ĞÀÁÎ×Àß ÑĞÅÄÀ
areaDraw &areaDraw :: example()
{
   static areaDraw pa(400, 60, 1280, 720);
   return pa;
}
//ÎÒĞÈÑÎÂÊÀ
void areaDraw :: draw()
{
   Pages :: example().draw();
   //ÔÈÃÓĞÛ
   for(int i = 0; i < areaDraw :: example().figures.size(); i++)
      figures[i] -> draw();
}
//ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ
void areaDraw :: press()
{
   int x = mousex();
   int y = mousey();
   if (mousebuttons() == 1)
   {
      tool();
   }
   else if (mousebuttons() == 2)
   {
      for (int i = figures.size() - 1; i >= 0; i--)
      {
         if (figures[i] -> in(x, y))
         {
            cout << 1;
            if (figures[i] -> getType() == 2)
            {
               numRoom = 0;
               figures.erase(figures.begin(), figures.end());
               draw();
               if (numRoom != 3) areaParams :: example().draw();
               outputObjects();
               break;
            }
            figures.erase(figures.begin() + i); 
            draw();
            if (numRoom != 3) areaParams :: example().draw();
            outputObjects();
            delay(60);
            break;
         }
      }
   }
}
//ÑÎÕĞÀÍÈÒÜ
void areaDraw :: save()
{
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}

//ÄÎÁÀÂÈÒÜ ÎÁÚÅÊÒ
void areaDraw :: addFigure(figure* figure)
{
   figures.push_back(figure);
}
//ÇÀÏÈÑÛÂÀÅÌ ÎÁÚÅÊÒÛ
void areaDraw :: outputObjects()
{
   ofstream fout;
   fout.open("output.txt");
   fout << "figures: \n";
   
   for(int i = 0; i < figures.size(); i++) 
   {
      fout << "x1: " << figures[i]->getX1() << " y1: " << figures[i] -> getY1() << " x2: " << figures[i] -> getX2() << " y2: " << figures[i]->getY2() <</*figures[i]->getT() <<*/ "\n";
   }
}
//ÓÄÀËÈÒÜ ÎÁÚÅÊÒ
void areaDraw :: deleteFigure(int x, int y)
{
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      if (figures[i] -> in(x, y))
      {
         cout << 1;
         if (figures[i] -> getType() == 2)
         {
            numRoom = 0;
            figures.erase(figures.begin(), figures.end());
            draw();
            if (numRoom != 3) areaParams :: example().draw();
            outputObjects();
            break;
         }
         figures.erase(figures.begin() + i); 
         draw();
         if (numRoom != 3) areaParams :: example().draw();
         outputObjects();
         delay(600);
         break;
      }
   }
}