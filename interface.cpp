#include "interface.hpp"

IMAGE *background[NUMBACKGROUND];
IMAGE *object[NUMOBJECT];
bool flag = 0;

bool ObjectDisplay :: in(int x, int y)
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
int ObjectDisplay :: getX1()
{ 
   return x1; 
}
int ObjectDisplay :: getY1()
{ 
   return y1; 
}
int ObjectDisplay :: getX2()
{
   return x2; 
}
int ObjectDisplay :: getY2()
{
   return y2; 
}
//-----------------------------------------------МЕБЕЛЬ-----------------------------------------------//
//ОТРИСОВКА
void ObjectFurniture :: draw()
{
   putimage(x1, y1, m, TRANSPARENT_PUT);
}
// геттеры для типа фигуры
int ObjectFurniture :: getType()
{
   return type;
}
// геттер для высоты фигуры
int ObjectFurniture :: getHeight()
{
   return height;
}
int ObjectFurniture :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------СТЕНЫ-----------------------------------------------//
//ОТРИСОВКА
void ObjectWall :: draw()
{
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setcolor(RGB(153, 153, 153));
   rectangle(x1, y1, x2, y2);
}
void ObjectWall :: setW(int widthWall)
{
   w = widthWall;
}
void ObjectWall :: paramRoom()
{
   weightRoom = x2 - x1;
   heightRoom = y2 - y1;
}
// геттер для ширины стены
int ObjectWall :: getW()
{
   return w;
}
// геттер для типа объекта
int ObjectWall :: getType()
{
   return type;
}
// геттер для высоты стены
int ObjectWall :: getHeight()
{
   return height;
}   
// геттер для высоты стены над уровнем пола
int ObjectWall :: getHeightLift()
{
   return 0;
}
//-----------------------------------------------НА-СТЕНЕ-----------------------------------------------//
//ОТРИСОВКА
void ObjectFigureOnWall :: draw()
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
int ObjectFigureOnWall :: getType()
{
   return type;
}
// геттер для высоты объекта
int ObjectFigureOnWall :: getHeight()
{
   return height;
}
// геттер для высоты объекта над уровнем пола
int ObjectFigureOnWall :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------ПАРАМЕТРЫ-----------------------------------------------//
AreaParams &AreaParams :: example()
{
   static AreaParams pa(70, 60, 400, 720);
   return pa;
}
void AreaParams :: draw()
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
      sprintf(str_h_room, "%d", 2 * (AreaDraw :: example().getY2() - AreaDraw :: example().getY1()) / 3);
      sprintf(str_w_room, "%d", 2 * (AreaDraw :: example().getX2() - AreaDraw :: example().getX1()) / 3);
      setcolor(RGB(153, 153, 153));
      if (AreaDraw :: example().numRoom)
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
      sprintf(str_w, "%d", heightLiftFurniture);
      setcolor(WHITE);
      bar(120, 123, 400, 180);
      setcolor(BLACK);
      const char * c = AreaParams :: example().name.c_str();
      outtextxy(120, 123, c);
   }
   setcolor(COLOR(0, 0, 0));
   outtextxy(230, 241, str_h);
   outtextxy(230, 324, str_w);
}

void AreaParams :: changeWallParam(int w, int h)
{
   if ((weightWall > 35 && weightWall < 65) ||
      (heightWall > 250 && heightWall < 500) ||
      (w > 0 && weightWall == 35) ||
      (h > 0 && heightWall == 250) ||
      (w < 0 && weightWall == 65) ||
      (h < 0 && heightWall == 500))
   {
      weightWall += w * 5;
      heightWall += h * 10;
      heightLift = 0;
   }
}
void AreaParams :: changeDoorParam(int w, int h)
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
      heightLift = 0;
      obj = object[((90 - weightDoor) / 10) % 3];
   }
}
void AreaParams :: changeWindowParam(int w, int h)
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
      heightLift = 170;
      obj = object[(250 - weightWindow) / 75 + 3];
   }
}
void AreaParams :: changeFurnitureParam(int r, int hl)
{
   if ((rotationFurniture > 0 && rotationFurniture < 360) ||
      (heightLiftFurniture > 0 && heightLiftFurniture < heightWall) ||
      (r > 0 && rotationFurniture == 0) ||
      (hl > 0 && heightLiftFurniture == 0) ||
      (r < 0 && rotationFurniture == 360) ||
      (hl < 0 && heightLiftFurniture == heightWall))
   {
      rotationFurniture += r * 90;
      heightLiftFurniture += hl * 10;
      heightLift = heightLiftFurniture;
      if (r) obj = imageturn(obj, 90, NO_COLOR);
   }
}
void AreaParams :: changeFurnitureOnWallParam(int r, int hl)
{
   if ((rotationFurniture > 0 && rotationFurniture < 360) ||
      (heightLiftFurniture > 0 && heightLiftFurniture < heightWall) ||
      (r > 0 && rotationFurniture == 0) ||
      (hl > 0 && heightLiftFurniture == 0) ||
      (r < 0 && rotationFurniture == 360) ||
      (hl < 0 && heightLiftFurniture == heightWall))
   {
      rotationFurniture += r * 180;
      heightLiftFurniture += hl * 10;
      heightLift = heightLiftFurniture;
      if (r) obj = imageturn(obj, 180, NO_COLOR);
   }
}
//-----------------------------------------------РАБОЧАЯ СРЕДА-----------------------------------------------//
//РАБОЧАЯ СРЕДА
AreaDraw &AreaDraw :: example()
{
   static AreaDraw pa(400, 60, 1280, 720);
   return pa;
}
//ОТРИСОВКА
void AreaDraw :: draw()
{
   for (int i = 0; i < figures.size(); i++)
      figures[i] -> draw();
}
// ЗАДНИЙ ФОН
void AreaDraw :: drawBack()
{
   putimage(1280 - imagewidth(back), 720 - imageheight(back), back, COPY_PUT);
}

// ПРОВЕРКА НА ГРАНИЦЫ КОМНТАНЫ
bool AreaDraw :: inRoom(int x, int y)
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
void AreaDraw :: projection(int x, int y)
{
   if (numRoom)
   {
      IMAGE *obj = AreaParams :: example().obj;
      int type = AreaParams :: example().type;
      if (obj != NULL)
      {
         int x1, y1;
         if (type == 3) obj = positionFigureOnWall(x, y, obj);
         x1 = x;
         y1 = y;
         imageputpixel(obj, 0, 0, WHITE);
         drawBack();
         int height = AreaParams :: example().height;
         int heightLift = AreaParams :: example().heightLift;
         figures[0] -> draw();
         int i;
         for (i = 1; i < figures.size(); i++)
         {
            if (figures[i]  -> getHeightLift() + figures[i]  -> getHeight() <= heightLift + height)
               figures[i] -> draw();
            else break;
         }
         if (x1 + imagewidth(obj) > getX2()) x1 = getX2() - imagewidth(obj);
         if (y1 + imageheight(obj) > getY2()) y1 = getY2() - imageheight(obj);
         putimage(x1, y1, obj, TRANSPARENT_PUT);
         for (i; i < figures.size(); i++)
            figures[i] -> draw();
         AreaParams :: example().draw();
         setlinestyle(SOLID_LINE, 2, 2);
         if (overlay(x1, y1, x1 + imagewidth(obj), y1 + imageheight(obj), height, heightLift)) setcolor(RED);
         else setcolor(GREEN);
         rectangle(x1, y1, x1 + imagewidth(obj), y1 + imageheight(obj));
         swapbuffers();
      }
   }
}
//РЕАКЦИЯ НА НАЖАТИЕ
void AreaDraw :: press()
{
   int x = mousex();
   int y = mousey();
   if (mousebuttons() == 1 && AreaDraw :: example().getTool() != NULL)
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
bool AreaDraw :: overlay(int x1, int y1, int x2, int y2, int h, int hl)
{
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      int setX1 = figures[i] -> getX1();
      int setY1 = figures[i] -> getY1();
      int setX2 = figures[i] -> getX2();
      int setY2 = figures[i] -> getY2();
      int height = figures[i] -> getHeight();
      int heightLift = figures[i] -> getHeightLift();
      bool m = hl >= heightLift ? (heightLift + height) > hl : (h + hl) > heightLift;
      if (h == 0)
      {
         m = 0;
         return false;
      }
      if (i && ((setX1 <= x1 && setX2 >= x1) || (setX1 <= x2 && setX2 >= x2) ||
         (setX1 >= x1 && setX2 <= x2)) && ((setY1 <= y1 && setY2 >= y1) ||
         (setY1 <= y2 && setY2 >= y2) || (setY1 >= y1 && setY2 <= y2)) && m)
         return true;
      else if (!i && (x1 < setX1 || x2 > setX2 || y1 < setY1 || y2 > setY2))
         return true;
   }
   return false;
}
//СОХРАНИТЬ
void AreaDraw :: save()
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
void AreaDraw :: addFigure(Figure* Figure)
{
   bool flag1 = 0;
   if (figures.size() > 1)
   {
      for (int i = 1; i < figures.size(); i++)
      {
         if (figures[i] -> getHeightLift() + figures[i] -> getHeight() > 
             Figure -> getHeightLift() + Figure -> getHeight()) 
         {
            flag1 = 1;
            auto iter = figures.begin() + i;
            figures.insert(iter, Figure);
            break;
         }
      }
      if (!flag1) figures.push_back(Figure);
   }
   else 
   {
      figures.push_back(Figure);
   }
}

//УДАЛИТЬ ОБЪЕКТ
void AreaDraw :: deleteFigure(int x, int y)
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
               delete figures[j];
            }
            setCoord(0, 0, 0, 0);
            for (int i = 0; i < 2; i++)
            {
               Pages :: example().draw();
               if ((num >= 0 && num <= 2) || num == 23) AreaParams :: example().draw();
               swapbuffers();
            }
            break;
         }
         figures.erase(figures.begin() + i);
         delete figures[i];
         draw();
         if ((num >= 0 && num <= 2) || num == 23) AreaParams :: example().draw();
         swapbuffers();
         break;
      }
   }
}
void AreaDraw :: setTool(ptrFunction t)
{ 
   tool = t; 
}
// сеттер для координат центра
void AreaDraw :: setCenter(int xc, int yc)
{ 
   center.x = xc;
   center.y = yc;
}
// сеттер для количества комнат
void AreaDraw :: setNumRoom(int num)
{ 
   numRoom = num; 
}
// сеттер для координат углов комнаты
void AreaDraw :: setCoord(int xt1, int yt1, int xt2, int yt2)
{
   coord.x1 = xt1;
   coord.y1 = yt1;
   coord.x2 = xt2;
   coord.y2 = yt2;
} 
// геттер для координат углов комнаты
int AreaDraw :: getX1()
{
   return coord.x1;
} 
int AreaDraw :: getY1()
{
   return coord.y1;
}
int AreaDraw :: getX2()
{
   return coord.x2;
}
int AreaDraw :: getY2()
{
   return coord.y2;
}
// геттер для инструмента рисования
ptrFunction AreaDraw :: getTool()
{ 
   return tool; 
}
// геттер для количества комнат
int AreaDraw :: getNumRoom()
{
   return numRoom;
}