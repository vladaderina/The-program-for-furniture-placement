



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
//пеюйжхъ мю мюфюрхе ймнойх хмярпслемрюпхъ
void buttonTools :: press()
{
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
//оюпюлерпш тхцспш
void modeFigure(int x1, int y1, int x2, int y2)
{
   char str_w[10], str_h[10];
   int wight = (x2 - x1) / 2;
   int height = (y2 - y1) / 2;
   sprintf(str_w, "%d", wight);
   sprintf(str_h, "%d", height);
   int w = areaParams :: example().weightWall;
   setcolor(RGB(180, 180, 180));
   setlinestyle(SOLID_LINE, 2, 2);
   Pages :: example().draw();
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(7, 20, 7, 10);
   
   // нрнапюфемхе ьхпхмш х дкхмш йнлмюрш
   int d = 30;
   outtextxy(x1 + wight, y1 - d - 10, str_w);
   outtextxy(x1 - d - 20, y1 + height, str_h);
   
   line(x1, y1 - d, x2, y1 - d);
   
   line(x2 - d + 10, y1 - d - 5, x2, y1 - d);
   line(x2, y1 - d, x2 - d + 10, y1 - d + 5);
   line(x1 + d - 10, y1 - d - 5, x1, y1 - d);

   line(x1, y1 - d, x1 + d - 10, y1 - d + 5);
   
   line(x1 - d, y1, x1 - d, y2);
   
   line(x1 - d, y1, x1 - d - 5, y1 + d - 10);
   line(x1 - d, y1, x1 - d + 5, y1 + d - 10);
   line(x1 - d, y2, x1 - d - 5, y2 - d + 10);
   line(x1 - d, y2, x1 - d + 5, y2 - d + 10);
   
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   rectangle(x1, y1, x2, y2);
}
//пюяръцхбюмхе тхцспш опх пхянбюмхх
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
      IMAGE *image = loadBMP("icon/back/1area.jpg");
      putimage(0, 0, image, COPY_PUT);
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
      modeFigure(x1, y1, x2, y2);
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
   //нангмювемхе вхякнл
   string tittle = to_string(objectFurniture::example().getT());
   setcolor(WHITE);
   setbkcolor(COLOR(63, 63, 63));
   outtextxy(x1, y1, tittle.c_str());
   //назейр
   figure *rect = new objectFurniture(x1, y1, x2, y2, objectFurniture::example().getT());
   areaDraw::example().addFigure(rect);
   areaDraw::example().outputObjects();
}
//яремю
void toolWall()
{
   if (areaDraw :: example().getNumRoom() == 0)
   {
      int x1, y1, x2, y2, w = areaParams :: example().weightWall;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {    
         figure *rect = new objectWall(x1, y1, x2, y2, w);
         objectWall :: _abracadabra_cast(example());