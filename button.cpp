#include "button.hpp"
#include <math.h>
#include <clocale>

IMAGE *createmask(IMAGE *p)
{
   int w = imagewidth(p);
   int h = imageheight(p);
   IMAGE *m = createimage(w, h);
   int c = imagegetpixel(p, 0, 0);
   for(int x = 0; x < w; ++x)
   {
      for(int y = 0; y < h; ++y)
      { 
         int d = imagegetpixel(p, x, y);
         
         if(c == d)
         { 
            imageputpixel(m, x, y, WHITE);
            imageputpixel(p, x, y, BLACK);
         }
         else imageputpixel(m, x, y, BLACK);
      }
   }
   return m;
}

//ÎÒĞÈÑÎÂÊÀ ÊÍÎÏÊÈ
void button :: draw()
{

   //ÇÀËÈÂÊÀ
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   //ÊÎÍÒÓĞ
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
   rectangle(x1, y1, x2, y2);
}
//ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÌÅÁÅËÈ
void buttonFurniture :: press()
{
   //ÓÑÒÀÍÎÂÈÒÜ ÈÍÑÒĞÓÌÅÍÒ È ÒÈÏ ÒÈÏ ÌÅÁÅËÈ
   areaDraw::example().setTool(tool);
   objectFurniture::example().setT(type);
}
//ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ĞÀÁÎÒÛ Ñ ÔÀÉËÎÌ
void buttonFile :: press()
{
   //ÄÅÉÑÒÂÈÅ
   action();
}
//ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ Ñ ÏÀĞÀÌÅÒĞÀÌÈ
void buttonParam :: press()
{
   int num = Pages :: example().getPage();
   if (num == 0)
   {
      if ((areaParams :: example().weightWall > 15 && areaParams :: example().weightWall < 65) ||
         (areaParams :: example().heightWall > 250 && areaParams :: example().heightWall < 500) ||
         (w > 0 && areaParams :: example().weightWall == 15) || 
         (h > 0 && areaParams :: example().heightWall == 250) ||
         (w < 0 && areaParams :: example().weightWall == 65) ||
         (h < 0 && areaParams :: example().heightWall == 500))
      {
         areaParams :: example().weightWall += w;
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
//ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÈÍÑÒĞÓÌÅÍÒÀĞÈß
void buttonTools :: press()
{
   areaDraw :: example().setTool(tool);
}
//ÓÄÀËÈÒÜ
void toolDelete()
{
   //ÊÓĞÑÎĞ
   int x = mousex();
   int y = mousey();
   //ÓÄÀËÅÍÈÅ ÔÈÃÓĞÛ, ÊÎÒÎĞÎÉ ÏĞÈÍÀÄËÅÆÈÒ ÒÎ×ÊÀ Â ÊÎÒÎĞÎÉ ÍÀÕÎÄÈÒÑß ÊÓĞÑÎĞ
   areaDraw :: example().deleteFigure(x, y);
}
//ÏÀĞÀÌÅÒĞÛ ÔÈÃÓĞÛ
void modeFigure(int x1, int y1, int x2, int y2)
{
   int w = areaParams :: example().weightWall;
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setcolor(RGB(153,153,153));
   setwritemode(XOR_PUT);
   setcolor(WHITE);
   rectangle(x1, y1, x2, y2);
   setwritemode(COPY_PUT);
}
//ĞÀÑÒßÃÈÂÀÍÈÅ ÔÈÃÓĞÛ ÏĞÈ ĞÈÑÎÂÀÍÈÈ
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

//ÌÅÁÅËÜ
void toolFurniture()
{
   //ÊÎÎĞÄÈÍÀÒÛ
   int x1, y1, x2, y2; //ÊÎÎĞÄÈÍÀÒÛ

   //ØÈĞÈÍÀ È ÂÛÑÎÒÀ
   int w, h;

   //×ÈÒÀÅÌ ØÈĞÈÍÓ È ÂÛÑÎÒÓ ÈÇ ÔÀÉËÀ
   string t  ="cfg/" + to_string(objectFurniture::example().getT() + 1) + ".txt";
   FILE *f = fopen(t.c_str(), "r");
   fscanf(f, "%d:%d", &w, &h);
   fclose(f);

   //ÊÎÎĞÄÈÍÀÒÛ
   x1 = 200;
   y1 = 100;

   int k = getch();
   while (1) {
      //ÏÅĞÅÌÅÙÅÍÈÅ ÔÈÃÓĞÛ
      k = getch();
      //ÂÍÈÇ
      if (k == KEY_DOWN) {
         y1 += 10;
      }
      //ÂÂÅĞÕ
      if (k == KEY_UP) {
         y1 -= 10;
      }
      //ÂËÅÂÎ
      if (k == KEY_LEFT)
      {
         x1 -= 10;
      }
      //ÂÏĞÀÂÎ
      if (k == KEY_RIGHT)
      {
         x1 += 10;
      }
      //ÏÎÂÎĞÎÒ
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
      //ĞÀÑ×ÅÒ È ÎÒĞÈÑÎÂÊÀ
      x2 = x1 + w;
      y2 = y1 + h;
      modeFigure(x1, y1, x2, y2);
      //ÏÎÄÒÂÅĞÆÄÅÍÈÅ ÓÑÒÀÍÎÂÊÈ ÌÅÁÅËÈ
      if (k == KEY_ENTER) {
         setfillstyle(SOLID_FILL, objectFurniture::example().getT());
         bar(x1, y1, x2, y2);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
         //ÍÅ ÍÀÊËÀÄÛÂÀÒÜ ÔÈÃÓĞÛ ÄĞÓÃ ÍÀ ÄĞÓÃÀ
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
   //ÎÁÎÇÍÀ×ÅÍÈÅ ×ÈÑËÎÌ
   string tittle = to_string(objectFurniture::example().getT());
   setcolor(WHITE);
   setbkcolor(COLOR(63, 63, 63));
   outtextxy(x1, y1, tittle.c_str());
   //ÎÁÚÅÊÒ
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
   areaDraw::example().outputObjects();
}
//ÑÒÅÍÀ
void toolWall()
{
   if (areaDraw :: example().getNumRoom() == 0)
   {
      int x1, y1, x2, y2, w = areaParams :: example().weightWall;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {
         setlinestyle(SOLID_LINE, w / 3, w / 3);
         setcolor(RGB(153,153,153));
         rectangle(x1, y1, x2, y2);
      }
      figure *rect = new objectWall(x1, y1, x2, y2, w);
      areaDraw :: example().setCenter(x1 + ((x2 - x1) / 2), y1 + ((y2 - y1) / 2));
      areaDraw :: example().setCoord(x1, y1, x2, y2);
      areaDraw :: example().addFigure(rect);
      areaDraw :: example().outputObjects();
      areaDraw :: example().setNumRoom(1);
   }
   else
   {
      setbkcolor(WHITE);
      settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(9, 20, 9, 10);
      setcolor(COLOR(227, 38, 54));
      string warning = "Ìîæíî ñîçäàòü òîëüêî îäíó êîìíàòó!";
      outtextxy(160, 600,  warning.c_str());
   }
}
//ÎÊÍÎ
void toolWindow()
{

}
void positionOnWall(int &x1, int &y1, IMAGE &a)
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
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) && 
               y1 <= yt2 && y1 >= centerY &&
               double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
         a = c;
         y1 = yt2 - imageheight(a);
   }
   else if (double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
               x1 <= xt2 && x1 >= centerX &&
               double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      a = d;
      x1 = xt2 - imagewidth(d);
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
               x1 >= xt1 && x1 <= centerX &&
               double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   { 
         a = b;
         x1 = xt1;
   }
   rect -> draw();
   areaDraw :: example().addFigure(rect);
   areaDraw :: example().outputObjects();
}
//ÄÂÅĞÜ
void toolDoor()
{
   int x1, y1;
   x1 = mousex();
   y1 = mousey();
   //IMAGE *m;
   IMAGE *a = loadBMP("icon/wall.bmp");
   IMAGE *b = imageturn(a, 90, WHITE);
   IMAGE *c = imageturn(a, 180, WHITE);
   IMAGE *d = imageturn(a, 270, WHITE);
   int centerY = areaDraw :: example().getCenterY();
   int centerX = areaDraw :: example().getCenterX();
   int xt1 = areaDraw :: example().getX1();
   int yt1 = areaDraw :: example().getY1(); 
   int xt2 = areaDraw :: example().getX2();
   int yt2 = areaDraw :: example().getY2();
   // ÏÅĞÅÄÀÅÌ : èçîáğàæåíèå, óêàçàòåëü íà íàæàòèå êíîïêè ìûøè (èëè òàì âû÷èñëÿåì)
   // 
   figure *rect;
   if (double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) && 
       y1 >= yt1 && y1 <= centerY &&
       double(y1 - centerY) <= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      rect = new objectFigureOnWall(x1, yt1, x1 + imagewidth(a), yt1 + imageheight(a), a);
      rect -> m = createmask(a);
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt1 - centerX) && 
               y1 <= yt2 && y1 >= centerY &&
               double(y1 - centerY) >= double(x1 - centerX) * (yt1 - centerY) / (xt2 - centerX))
   {
      rect = new objectFigureOnWall(x1, yt2 - imageheight(c), x1 + imagewidth(c), yt2, c);
      rect -> m = createmask(c);
   }
   else if (double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
               x1 <= xt2 && x1 >= centerX &&
               double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      rect = new objectFigureOnWall(xt2 - imagewidth(d), y1, xt2, y1 + imageheight(d), d);
      rect -> m = createmask(d);
   }
   else if (double(y1 - centerY) >= double(x1 - centerX) * (yt2 - centerY) / (xt2 - centerX) && 
               x1 >= xt1 && x1 <= centerX &&
               double(y1 - centerY) <= double(x1 - centerX) * (yt2 - centerY) / (xt1 - centerX))
   {
      rect = new objectFigureOnWall(xt1, y1, xt1 + imagewidth(b), y1 + imageheight(b), b);
      rect -> m = createmask(b);
   }
   rect -> draw();
   areaDraw :: example().addFigure(rect);
   areaDraw :: example().outputObjects();
}

//ÑÎÕĞÀÍÈÒÜ Â ÏĞÎÅÊÒ
void fileSave()
{
   areaDraw::example().save();
}
//ÇÀÊĞÛÒÜ ÏĞÎÃĞÀÌÌÓ
void fileEnd()
{
   closegraph(CURRENT_WINDOW);
}