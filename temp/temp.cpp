



//нрпхянбйю ймнойх
void button::draw()
{

   //гюкхбйю
   setfillstyle(SOLID_FILL, COLOR(63, 63, 63));
   bar(x1, y1, x2, y2);

   //хйнмйю
   putimage(x1 + 1, y1 + 1, image, COPY_PUT);

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
void buttonFile::press()
{
   //деиярбхе
   action();
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
   setwritemode(XOR_PUT);
   setcolor(WHITE);
   rectangle(x1, y1, x2, y2);
   line(x1, y1 - 20, x2, y1 - 20);
   line(x1, y1 - 20, x2, y1 - 20);
   setwritemode(COPY_PUT);
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
      int x1, y1, x2, y2, w = 1;
      if (modeStretch(x1, y1, x2, y2, modeFigure))
      {
         setlinestyle(SOLID_LINE, THICK_WIDTH, THICK_WIDTH);
         setcolor(BLACK);
         rectangle(x1, y1, x2, y2);
      }
      figure *ptr = new objectWall(x1, y1, x2, y2, w);
      areaDraw :: _abracadabra_cast(example());