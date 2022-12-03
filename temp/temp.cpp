


// —Œ«ƒ¿Õ»≈ Ã¿— »
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
// »«Ã≈Õ≈Õ»≈ –¿«Ã≈–¿  ¿–“»Õ »
IMAGE * resize(IMAGE *p, int w, int h)
{
   int wp=imagewidth(p);
   int hp=imageheight(p);
   IMAGE *r=createimage(w, h);
   for (int x = 0; x < w; ++x)
      for (int y = 0; y < h; ++y)
         imageputpixel(r, x, y, imagegetpixel(p, x * wp / w, y * hp / h));
   return r;
}
//Œ“–»—Œ¬ ¿  ÕŒœ »
void button :: draw()
{
   //«¿À»¬ ¿
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   // ŒÕ“”–
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
   rectangle(x1, y1, x2, y2);
}
//–≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » Ã≈¡≈À»
void buttonFurniture :: press()
{
   //”—“¿ÕŒ¬»“‹ »Õ—“–”Ã≈Õ“ » “»œ “»œ Ã≈¡≈À»
   areaDraw::example().setTool(tool);
   objectFurniture::example().setT(type);
}
//–≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ
void buttonFile :: press()
{
   //ƒ≈…—“¬»≈
   action();
}
//–≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » — œ¿–¿Ã≈“–¿Ã»
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
//–≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ
void buttonTools :: press()
{
   areaDraw :: example().setTool(tool);
}
//”ƒ¿À»“‹
void toolDelete()
{
   // ”–—Œ–
   int x = mousex();
   int y = mousey();
   //”ƒ¿À≈Õ»≈ ‘»√”–€,  Œ“Œ–Œ… œ–»Õ¿ƒÀ≈∆»“ “Œ◊ ¿ ¬  Œ“Œ–Œ… Õ¿’Œƒ»“—ﬂ  ”–—Œ–
   areaDraw :: example().deleteFigure(x, y);
}

//Ã≈¡≈À‹
void toolFurniture()
{
   // ŒŒ–ƒ»Õ¿“€
   int x1, y1, x2, y2; // ŒŒ–ƒ»Õ¿“€

   //ÿ»–»Õ¿ » ¬€—Œ“¿
   int w, h;

   //◊»“¿≈Ã ÿ»–»Õ” » ¬€—Œ“” »« ‘¿…À¿
   string t  ="cfg/" + to_string(objectFurniture::example().getT() + 1) + ".txt";
   FILE *f = fopen(t.c_str(), "r");
   fscanf(f, "%d:%d", &w, &h);
   fclose(f);

   // ŒŒ–ƒ»Õ¿“€
   x1 = 200;
   y1 = 100;

   int k = getch();
   while (1) {
      //œ≈–≈Ã≈Ÿ≈Õ»≈ ‘»√”–€
      k = getch();
      //¬Õ»«
      if (k == KEY_DOWN) {
         y1 += 10;
      }
      //¬¬≈–’
      if (k == KEY_UP) {
         y1 -= 10;
      }
      //¬À≈¬Œ
      if (k == KEY_LEFT)
      {
         x1 -= 10;
      }
      //¬œ–¿¬Œ
      if (k == KEY_RIGHT)
      {
         x1 += 10;
      }
      //œŒ¬Œ–Œ“
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
      //–¿—◊≈“ » Œ“–»—Œ¬ ¿
      x2 = x1 + w;
      y2 = y1 + h;
      //œŒƒ“¬≈–∆ƒ≈Õ»≈ ”—“¿ÕŒ¬ » Ã≈¡≈À»
      if (k == KEY_ENTER) {
         setfillstyle(SOLID_FILL, objectFurniture::example().getT());
         bar(x1, y1, x2, y2);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
         //Õ≈ Õ¿ À¿ƒ€¬¿“‹ ‘»√”–€ ƒ–”√ Õ¿ ƒ–”√¿
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
   //Œ¡⁄≈ “
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
}
//œ¿–¿Ã≈“–€ ‘»√”–€
void modeFigure(int x1, int y1, int x2, int y2)
{
   int w = areaParams :: example().weightWall;
   setcolor(RGB(70, 70, 70));
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setwritemode(XOR_PUT);
   rectangle(x1, y1, x2, y2);
   setwritemode(COPY_PUT);
}
//–¿—“ﬂ√»¬¿Õ»≈ ‘»√”–€ œ–» –»—Œ¬¿Õ»»
bool modeStretch(int &x1, int &y1, int &x2, int &y2, void (*shape)(int x1, int y1, int x2, int y2))
{
   x1 = mousex();
   y1 = mousey();
   x2 = x1;
   y2 = y1;
   shape(x1, y1, x2, y2);
   char str_w[10], str_h[10];
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
      if (((cursorX != x2 || cursorY != y2) &&
         (cursorX - x1 > 100 && cursorY - y1 >= 100)) ||
         (((cursorX >= x2) && (cursorX - x1 <= 100)) ||
         ((cursorY >= y2) && (cursorY - y1 <= 100))))
      {
         int wight = 2 * (x2 - x1) / 3;
         int height = 2 * (y2 - y1) / 3;
         sprintf(str_w, "%d", wight);
         sprintf(str_h, "%d", height);
         setcolor(RGB(153, 153, 153));
         outtextxy(230, 407, str_w);
         outtextxy(230, 489, str_h);
         shape(x1, y1, x2, y2);
         x2 = cursorX;
         y2 = cursorY;
         shape(x1, y1, x2, y2);
      }
   }
   shape(x1, y1, x2, y2);
   return 1;
}

//—“≈Õ¿
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

//–¿—œŒÀŒ∆≈Õ»≈ Œ¡⁄≈ “¿ Õ¿ —“≈Õ≈
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

//Œ ÕŒ
void toolWindow()
{
      if (areaDraw :: example().getNumRoom() != 0)
   {
      int x1, y1, numWall;
      x1 = mousex();
      y1 = mousey();
      if (areaParams :: _abracadabra_cast(example());