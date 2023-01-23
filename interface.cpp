#include "interface.hpp"

IMAGE *background[NUMBACKGROUND];
IMAGE *object[NUMOBJECT];
bool flag = 0;

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

//-----------------------------------------------ОШИБКИ-----------------------------------------------//

const void *ManyRoomsError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text1.jpg");
   putimage(63, 556, image, COPY_PUT); 
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // сообщение для печати
   swapbuffers();
   return 0;
}

const void *NoRoomError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text2.jpg");
   putimage(63, 556, image, COPY_PUT); 
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // сообщение для печати
   swapbuffers();
   return 0;
}
const void *ObjectOverlayError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text3.jpg");
   putimage(63, 556, image, COPY_PUT);
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // сообщение для печати
   swapbuffers();
   return 0;
}
//-----------------------------------------------СТРАНИЦЫ-----------------------------------------------//
Pages &Pages :: example()
{
   static Pages pg;
   return pg;
}
void Pages :: draw()
{
   putimage(0, 0, background[Pages :: example().getCurrentPage()], COPY_PUT);
}
void Pages :: setCurrentPage(int page)
{
   currentPage = page; 
}
// геттер для номера текущей страницы
int Pages :: getCurrentPage()
{
   return currentPage; 
}
// сеттер для номера страницы со списком всей мебели
void Pages :: setListFurniturePage(int page)
{
   listFurniturePage = page; 
}
// геттер для номера страницы со списком всей мебели 
int Pages :: getListFurniturePage()
{
   return listFurniturePage; 
}
// сеттер для номера страницы с типами выбранной мебели
void Pages :: setListTypePage(int page)
{
   listTypePage = page; 
}
// геттер для номера страницы с типами выбранной мебели
int Pages :: getListTypePage()
{
   return listTypePage; 
}

//-----------------------------------------------ОБЪЕКТЫ НА ЭКРАНЕ-----------------------------------------------//
// геттеры для координат углов
int objectDisplay :: getX1()
{ 
   return x1; 
}
int objectDisplay :: getY1()
{ 
   return y1; 
}
int objectDisplay :: getX2()
{
   return x2; 
}
int objectDisplay :: getY2()
{
   return y2; 
}
//-----------------------------------------------МЕБЕЛЬ-----------------------------------------------//
//ОТРИСОВКА
void objectFurniture :: draw()
{
   putimage(x1, y1, m, TRANSPARENT_PUT);
}
// геттеры для типа фигуры
int objectFurniture :: getType()
{
   return type;
}
// геттер для высоты фигуры
int objectFurniture :: getHeight()
{
   return height;
}
int objectFurniture :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------СТЕНЫ-----------------------------------------------//
//ОТРИСОВКА
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
// геттер для ширины стены
int objectWall :: getW()
{
   return w;
}
// геттер для типа объекта
int objectWall :: getType()
{
   return type;
}
// геттер для высоты стены
int objectWall :: getHeight()
{
   return height;
}   
// геттер для высоты стены над уровнем пола
int objectWall :: getHeightLift()
{
   return 0;
}
//-----------------------------------------------НА-СТЕНЕ-----------------------------------------------//
//ОТРИСОВКА
void objectFigureOnWall :: draw()
{
   setcolor(RGB(243, 243, 243));
   if (numWall == 1)
   {
      line(x1, y1, x1 + imagewidth(m), y1);
   }
   else if (numWall == 2)
      line(x1 + imagewidth(m), y1, x1 + imagewidth(m), y1+ imageheight(m));
   else if (numWall == 3)
      line(x1, y1 + imageheight(m), x1 + imagewidth(m), y1 + imageheight(m));
   else if (numWall == 4)
      line(x1, y1, x1, y1+ imageheight(m));
   putimage(x1, y1, m, TRANSPARENT_PUT);
}
// геттер для типа объекта
int objectFigureOnWall :: getType()
{
   return type;
}
// геттер для высоты объекта
int objectFigureOnWall :: getHeight()
{
   return height;
}
// геттер для высоты объекта над уровнем пола
int objectFigureOnWall :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------ПАРАМЕТРЫ-----------------------------------------------//
areaParams &areaParams :: example()
{
   static areaParams pa(70, 60, 400, 720);
   return pa;
}
void areaParams :: draw()
{
   char str_w[10], str_h[10];
   char str_w_room[10], str_h_room[10];
   int num = Pages :: example().getCurrentPage();
   setcolor(RGB(0, 0, 0));
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   setbkcolor(RGB(243, 243, 243));
   if (num == 0)
   {
      sprintf(str_h, "%d", weightWall);
      sprintf(str_w, "%d", heightWall);
      sprintf(str_h_room, "%d", 2 * (areaDraw :: example().getY2() - areaDraw :: example().getY1()) / 3);
      sprintf(str_w_room, "%d", 2 * (areaDraw :: example().getX2() - areaDraw :: example().getX1()) / 3);
      setcolor(RGB(153, 153, 153));
      if (areaDraw :: example().numRoom)
      {
         outtextxy(230, 407, str_w_room);
         outtextxy(230, 489, str_h_room);
      }
      setcolor(RGB(0, 0, 0));
   }
   else if (num == 1)
   {
      sprintf(str_h, "%d", weightDoor);
      sprintf(str_w, "%d", heightDoor);
   }
   else if (num == 2)
   {
      sprintf(str_h, "%d", weightWindow);
      sprintf(str_w, "%d", heightWindow);
   }
   else if (num == 23)
   {
      settextjustify(LEFT_TEXT, CENTER_TEXT);
      sprintf(str_h, "%d", rotationFurniture);
      sprintf(str_w, "%d", heightFurniture);
      setcolor(WHITE);
      bar(120, 123, 400, 180);
      setcolor(BLACK);
      const char * c = areaParams :: example().name.c_str();
      outtextxy(120, 123, c);
   }
   setcolor(COLOR(0, 0, 0));
   outtextxy(230, 241, str_h);
   outtextxy(230, 324, str_w);
}

void areaParams :: changeParam()
{
   int num = Pages :: example().getCurrentPage();
   if (num == 0)
   {
      if ((weightWall > 35 && weightWall < 65) ||
            (heightWall > 250 && heightWall < 500) ||
            (a > 0 && weightWall == 35) ||
            (b > 0 && heightWall == 250) ||
            (a < 0 && weightWall == 65) ||
            (b < 0 && heightWall == 500))
      {
         weightWall += a * 5;
         heightWall += b * 10;
         heightLift = 0;
      }
   }
   else if (num == 1)
   {
      if ((weightDoor > 70 && weightDoor < 90) ||
            (heightDoor > 200 && heightDoor < 240) ||
            (a > 0 && weightDoor == 70) ||
            (b > 0 && heightDoor == 200) ||
            (a < 0 && weightDoor == 90) ||
            (b < 0 && heightDoor == 240))
      {
         weightDoor += a * 10;
         heightDoor += b * 5;
         heightLift = 0;
         obj = object[((90 - weightDoor) / 10) % 3];
      }
   }
   else if (num == 2)
   {
      if ((weightWindow > 100 && weightWindow < 250) ||
            (heightWindow > 110 && heightWindow < 210) ||
            (a > 0 && weightWindow == 100) ||
            (b > 0 && heightWindow == 110) ||
            (a < 0 && weightWindow == 250) ||
            (b < 0 && heightWindow == 210))
      {
         weightWindow += a * 75;
         heightWindow += b * 5;
         heightLift = 170;
         obj = object[(250 - weightWindow) / 75 + 3];
      }
   }
   else if (num == 23)
   {
      if ((rotationFurniture > 0 && rotationFurniture < 360) ||
            (heightFurniture > 0 && heightFurniture < heightWall) ||
            (a > 0 && rotationFurniture == 0) ||
            (b > 0 && heightFurniture == 0) ||
            (a < 0 && rotationFurniture == 360) ||
            (b < 0 && heightFurniture == heightWall))
      {
         rotationFurniture += a * 90;
         heightFurniture += b * 10;
         heightLift = heightFurniture;
         if (a) obj = imageturn(obj, 90, NO_COLOR);
      }
   }
   draw();
   swapbuffers();
}

void areaParams :: setParam(int a, int b)
{
   this -> a = a;
   this -> b = b;
}
int areaParams :: getType()
{
   return type;
}
void areaParams :: setType(int type)
{
   this -> type = type;
}
//-----------------------------------------------РАБОЧАЯ СРЕДА-----------------------------------------------//
//РАБОЧАЯ СРЕДА
areaDraw &areaDraw :: example()
{
   static areaDraw pa(400, 60, 1280, 720);
   return pa;
}
//ОТРИСОВКА
void areaDraw :: draw()
{
   for (int i = 0; i < figures.size(); i++)
      figures[i] -> draw();
}
// ЗАДНИЙ ФОН
void areaDraw :: drawBack()
{
   putimage(1280 - imagewidth(back), 720 - imageheight(back), back, COPY_PUT);
}

// ПРОВЕРКА НА ГРАНИЦЫ КОМНТАНЫ
bool areaDraw :: inRoom(int x, int y)
{
   if (coord.x1 > coord.x2)
      swap(coord.x1, coord.x2);
   if (coord.y1 > coord.y2)
      swap(coord.y1, coord.y2);
   if (x >= coord.x1 && x <= coord.x2
         && y >= coord.y1 && y <= coord.y2)
      return true;
   else
      return false;
}

//ПРОЕКЦИЯ ОБЪЕКТА ПЕРЕД УСТАНОВКОЙ
void areaDraw :: projection(int x, int y)
{
   if (numRoom)
   {
      IMAGE *a;
      a = areaParams :: example().obj;
      int  type = areaParams :: example().getType();
      if (a != NULL)
      {
         int numWall;
         IMAGE *m1;
         int x1, y1;
         
         if (type == 1) m1 = positionOnWall(x, y, numWall, a);
         else m1 = a;
         x1 = x;
         y1 = y;
         imageputpixel(m1, 0, 0, WHITE);
         drawBack();
         int height = areaParams :: example().height;
         int heightLift = areaParams :: example().heightLift;
         figures[0] -> draw();
         int i = 1;
         for (i; i < figures.size(); i++)
         {
            if (figures[i]  -> getHeightLift() + figures[i]  -> getHeight() <= heightLift + height)
            {
               figures[i] -> draw();
            }
            else break;
         }
         if (x1 + imagewidth(m1) > getX2()) x1 = getX2() - imagewidth(m1);
         if (y1 + imageheight(m1) > getY2()) y1 = getY2() - imageheight(m1);
         putimage(x1, y1, m1, TRANSPARENT_PUT);
         for (i; i < figures.size(); i++)
         {
            figures[i] -> draw();
         }
         if (Pages :: example().getCurrentPage() != 3)
         {
            areaParams :: example().draw();
         }
         setlinestyle(SOLID_LINE, 2, 2);
         if (overlay(x1, y1, x1 + imagewidth(m1), y1 + imageheight(m1), height, heightLift)) setcolor(RED);
         else setcolor(GREEN);
         rectangle(x1, y1, x1 + imagewidth(m1), y1 + imageheight(m1));
         swapbuffers();
      }
   }
}
//РЕАКЦИЯ НА НАЖАТИЕ
void areaDraw :: press()
{
   int x = mousex();
   int y = mousey();
   if (mousebuttons() == 1 && areaDraw :: example().getTool() != NULL)
   {
      try
      {
         tool();
      }
      catch (Error &e)
      {
         e.what();
         flag = 1;
         delay(200);
      }
   }
   if (mousebuttons() == 2)
   {
      deleteFigure(x, y);
   }
}
//ПРОВЕРКА НАЛОЖЕНИЯ ОБЪЕКТА НА ДРУГИЕ
bool areaDraw :: overlay(int a, int b, int c, int d, int e, int f)
{
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      int x1 = figures[i] -> getX1();
      int y1 = figures[i] -> getY1();
      int x2 = figures[i] -> getX2();
      int y2 = figures[i] -> getY2();
      int height = figures[i] -> getHeight();
      int heightLift = figures[i] -> getHeightLift();
      bool h = f >= heightLift ? (heightLift + height) > f : (f + e) > heightLift;
      if (e == 0)
      {
         h = 0;
         return false;
      }
      if (i && ((x1 <= a && x2 >= a) || (x1 <= c && x2 >= c) ||
         (x1 >= a && x2 <= c)) && ((y1 <= b && y2 >= b) ||
         (y1 <= d && y2 >= d) || (y1 >= b && y2 <= d)) && h)
         return true;
      else if (!i && (a < x1 || c > x2 || b < y1 || d > y2))
         return true;
   }
   return false;
}
//СОХРАНИТЬ
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

//ДОБАВИТЬ ОБЪЕКТ
void areaDraw :: addFigure(figure *figure)
{
   bool flag = 0;
   if (figures.size() > 1)
   {
      for (int i = 1; i < figures.size(); i++)
      {
         if (figures[i] -> getHeightLift() + figures[i] -> getHeight() > 
             figure -> getHeightLift() + figure -> getHeight()) 
         {
            flag = 1;
            auto iter = figures.begin() + i;
            figures.insert(iter, figure);
            break;
         }
      }
      if (!flag) figures.push_back(figure);
   }
   else 
   {
      figures.push_back(figure);
   }
}

//УДАЛИТЬ ОБЪЕКТ
void areaDraw :: deleteFigure(int x, int y)
{
   delay(150);
   int num = Pages :: example().getCurrentPage();
   Pages :: example().draw();
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      if (figures[i] -> in(x, y))
      {
         if (figures[i] -> getType() == 2)
         {
            numRoom = 0;
            figures.erase(figures.begin(), figures.end());
            for (int j = 0; j < figures.size(); j++)
            {
               //freeimage(figures[j] -> m);
               delete figures[j];
            }
            draw();
            setCoord(0, 0, 0, 0);
            if ((num >= 0 && num <= 2) || num == 23) areaParams :: example().draw();
            swapbuffers();
            break;
         }
         figures.erase(figures.begin() + i);
         //freeimage(figures[i] -> m);
         delete figures[i];
         draw();
         if ((num >= 0 && num <= 2) || num == 23) areaParams :: example().draw();
         swapbuffers();
         break;
      }
   }
}
void areaDraw :: setTool(ptrFunction t)
{ 
   tool = t; 
}
// сеттер для координат центра
void areaDraw :: setCenter(int xc, int yc)
{ 
   center.x = xc;
   center.y = yc;
}
// сеттер для количества комнат
void areaDraw :: setNumRoom(int num)
{ 
   numRoom = num; 
}
// сеттер для координат углов комнаты
void areaDraw :: setCoord(int xt1, int yt1, int xt2, int yt2)
{
   coord.x1 = xt1;
   coord.y1 = yt1;
   coord.x2 = xt2;
   coord.y2 = yt2;
} 
// геттер для координат углов комнаты
int areaDraw :: getX1()
{
   return coord.x1;
} 
int areaDraw :: getY1()
{
   return coord.y1;
}
int areaDraw :: getX2()
{
   return coord.x2;
}
int areaDraw :: getY2()
{
   return coord.y2;
}
// геттер для инструмента рисования
ptrFunction areaDraw :: getTool()
{ 
   return tool; 
}
// геттер для количества комнат
int areaDraw :: getNumRoom()
{
   return numRoom;
}