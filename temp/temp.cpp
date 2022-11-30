



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

//ÎÒÐÈÑÎÂÊÀ ÊÍÎÏÊÈ
void button :: draw()
{
   //ÇÀËÈÂÊÀ
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   //ÊÎÍÒÓÐ
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
   rectangle(x1, y1, x2, y2);
}
//ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÌÅÁÅËÈ
void buttonFurniture :: press()
{
   //ÓÑÒÀÍÎÂÈÒÜ ÈÍÑÒÐÓÌÅÍÒ È ÒÈÏ ÒÈÏ ÌÅÁÅËÈ
   areaDraw::example().setTool(tool);
   objectFurniture::example().setT(type);
}
//ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÐÀÁÎÒÛ Ñ ÔÀÉËÎÌ
void buttonFile :: press()
{
   //ÄÅÉÑÒÂÈÅ
   action();
}
//ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ Ñ ÏÀÐÀÌÅÒÐÀÌÈ
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
//ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÈÍÑÒÐÓÌÅÍÒÀÐÈß
void buttonTools :: press()
{
   areaDraw :: example().setTool(tool);
}
//ÓÄÀËÈÒÜ
void toolDelete()
{
   //ÊÓÐÑÎÐ
   int x = mousex();
   int y = mousey();
   //ÓÄÀËÅÍÈÅ ÔÈÃÓÐÛ, ÊÎÒÎÐÎÉ ÏÐÈÍÀÄËÅÆÈÒ ÒÎ×ÊÀ Â ÊÎÒÎÐÎÉ ÍÀÕÎÄÈÒÑß ÊÓÐÑÎÐ
   areaDraw :: example().deleteFigure(x, y);
}
//ÏÀÐÀÌÅÒÐÛ ÔÈÃÓÐÛ
void modeFigure(int x1, int y1, int x2, int y2)
{
   char str[10];
   int wight = x2 - x1;
   sprintf(str, "%d", wight);
   int w = areaParams :: example().weightWall;
   setwritemode(XOR_PUT);
   setcolor(RGB(80, 80, 80));
   setlinestyle(SOLID_LINE, 3, 3);
   bar(x1, y1 - 30, _abracadabra_cast(x2);