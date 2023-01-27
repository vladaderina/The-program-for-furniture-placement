#ifndef INTERFACE_H
#define INTERFACE_H
#include "graphics.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#define NUMBACKGROUND 25
#define  NUMOBJECT 6

using namespace std;

//  указатель на функцию
typedef void (*ptrFunction)();
// фоны
extern IMAGE *background[NUMBACKGROUND];
// объекты мебели
extern IMAGE *object[NUMOBJECT];
extern bool flag;

//-----------------------------------------------ОШИБКИ-----------------------------------------------//
struct Error
{
   virtual ~Error() {} // деструктор
   virtual const void *what() const = 0; // сообщение для печати
};

struct ManyRoomsError: Error // создание более 1 комнаты
{
   const void *what() const; // сообщение для печати
};

struct NoRoomError: Error // не создано ни одной комнаты
{
   const void *what() const; // сообщение для печати
};

struct ObjectOverlayError: Error // объекты накладываются друг на друга
{
   const void *what() const; // сообщение для печати
};

//-----------------------------------------------СТРАНИЦЫ-----------------------------------------------//
class Pages 
{
   // номер страницы со списком всей мебели
   int listFurniturePage;
   // номер страницы с типами выбранной мебели
   int listTypePage;
   // номер текущей страницы
   int currentPage;
   // конструктор
   Pages() : currentPage(0) {}
public:
   // экземпляр класса
   static Pages &example();
   // отрисовка фона
   void draw();
   // сеттер для номера текущей страницы
   void setCurrentPage(int page);
   // геттер для номера текущей страницы
   int getCurrentPage();
   // сеттер для номера страницы со списком всей мебели
   void setListFurniturePage(int page);
   // геттер для номера страницы со списком всей мебели 
   int getListFurniturePage();
   // сеттер для номера страницы с типами выбранной мебели
   void setListTypePage(int page);
   // геттер для номера страницы с типами выбранной мебели
   int getListTypePage();
};

//-----------------------------------------------ОБЪЕКТЫ НА ЭКРАНЕ-----------------------------------------------//
class ObjectDisplay
{
public:
   int x1, y1, x2, y2;
   // конструктор
   ObjectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
   // внутренние координаты
   bool in(int x, int y); 
   // виртуальная функция для отрисовки объекта
   virtual void draw() = 0;
   // геттеры для координат углов
   int getX1();
   int getY1();
   int getX2();
   int getY2();
   //деструктор
   virtual ~ObjectDisplay(){}
};

//-----------------------------------------------ОБЪЕКТЫ С РЕАКЦИЕЙ НА НАЖАТИЕ-----------------------------------------------//
class ObjectClickable: public ObjectDisplay
{
public:
   // конструктор
   ObjectClickable(int x1, int y1, int x2, int y2) : ObjectDisplay(x1, y1, x2, y2) {}
   // функция реакции на нажатие
   virtual void press() = 0;
};

//-----------------------------------------------ФИГУРЫ-----------------------------------------------//
class Figure: public ObjectDisplay
{
protected:
   //тип объекта:
   //1 - мебель
   //2 - стены
   //3 - объекты на стене
   int type;
   int height;
   int heightLift;
   // изображение объекта
   IMAGE *m;
public:
   // устанавливаем координаты углов, высоту и высоту подъема
   Figure(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE *m) : ObjectDisplay(x1, y1, x2, y2), 
            height(height), heightLift(heightLift), m(m) {}
   // отрисовка объекта
   virtual void draw();
   // геттер для высоты фигуры
   virtual int getHeight();
   // геттер для высоты подъема фигуры
   virtual int getHeightLift();
   // геттер для типа фигуры
   virtual int getType();
};

//-----------------------------------------------МЕБЕЛЬ-----------------------------------------------//
class ObjectFurniture : public Figure
{
public:
   // конструктор
   ObjectFurniture(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE* m) :
                           Figure(x1, y1, x2, y2, height, heightLift, m) {}
   // отрисовка объекта
   void draw() override;
   // геттеры для типа фигуры
   int getType();
   // геттер для высоты фигуры
   int getHeight();
   // геттер для высоты фигуры над полом
   int getHeightLift();
};

//-----------------------------------------------СТЕНЫ-----------------------------------------------//
class ObjectWall : public Figure
{
   // ширина стены
   int w;
   // координаты центра комнаты
   int weightRoom, heightRoom;
   // вычисление параметров комнаты
   void paramRoom();
public:
   // конструктор
   ObjectWall(int x1, int y1, int x2, int y2, int height, int w) : Figure(x1, y1, x2, y2, height, 0, NULL), w(w) { type = 2; }
   // отрисовка объекта 
   void draw() override; 
   // геттер для ширины стены
   int getW();
   // геттер для типа объекта
   int getType();
   // сеттер для ширины стены
   void setW(int w);
   // геттер для высоты стены
   int getHeight();
   // геттер для высоты стены над уровнем пола
   int getHeightLift();
};

//-----------------------------------------------НА СТЕНЕ-----------------------------------------------//
class ObjectFigureOnWall : public Figure
{
public:
   // номер одной из 4 стен, на которой находится объект
   int numWall;
   // конструктор
   ObjectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, int height, int heightLift, IMAGE *a) : 
         Figure(x1, y1, x2, y2, height, heightLift, a), numWall(numWall)
         { type = 3; }
   // отрисовка объекта
   void draw() override;
   // геттер для типа объекта
   int getType();
   // геттер для высоты объекта
   int getHeight();
   // геттер для высоты объекта над уровнем пола
   int getHeightLift();
};

//-----------------------------------------------ПАРАМЕТРЫ-----------------------------------------------//
class AreaParams : public ObjectDisplay
{
   // устанавливаем начальные параметры рисования
   AreaParams (int x1, int y1, int x2, int y2) : ObjectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), heightWall(250),
   rotationFurniture(0), heightLiftFurniture (0),
   height(0), heightLift(0)
   { obj = NULL; } 
   // запрещение создания копий и присваивания
   AreaParams (const AreaParams &) = delete;
   AreaParams & operator = (const AreaParams &) = delete;
   // запрещение уничтожения объекта
   ~AreaParams() {}
public:
      // тип объекта
   int type;
   // название объекта
   string name;
   // высота объекта
   int height;
   // высота подъема объекта
   int heightLift;
   IMAGE *obj;
   int weightDoor,
        heightDoor,
        weightWindow,
        heightWindow,
        weightWall,
        heightWall,
        rotationFurniture,
        heightLiftFurniture;
   // экземпляр класса
   static AreaParams &example();
   // отрисовка параметров
   void draw();
   // сеттеры для параметров
   void changeWallParam(int w, int h);
   void changeDoorParam(int w, int h);
   void changeWindowParam(int w, int h);
   void changeFurnitureParam(int r, int hl);
   void changeFurnitureOnWallParam(int r, int hl);
};

//-----------------------------------------------РАБОЧАЯ СРЕДА-----------------------------------------------//
class AreaDraw : public ObjectClickable
{
   IMAGE *back = loadBMP("icon/back/areaDraw.jpg");
   // получаем координаты углов
   AreaDraw(int x1, int y1, int x2, int y2) : ObjectClickable(x1, y1, x2, y2), tool(nullptr), numRoom(0) {}
   ptrFunction tool; // текущий инструмент
   // координаты центра комнаты
   struct center
   {
      int x, y;
   } center;
   // координаты углов комнаты
   struct coord
   {
      int x1, y1, x2, y2;
   } coord;
public:
   // число комнат расположенных на экране
   int numRoom;
   // вектор объектов расположенных на экране
   vector <Figure*> figures;
   // рабочая среда
   static AreaDraw &example();
   // проверка наложения объекта на другие
   bool overlay(int x1, int y1, int x2, int y2, int h, int hl);
   // проверка на границы комнаты
   bool inRoom(int x, int y);
   // удаление фигуры
   void deleteFigure(int x, int y);
   // сохранение объекта на поле
   void addFigure(Figure* Figure);
   // отрисовка объектов
   void draw() override;
   // задний фон
   void drawBack();
   // проекция объекта перед установкой
   void projection(int x, int y);
   // функция реакции на нажатие
   void press() override;
   // сеттер для инструмента рисования
   void setTool(ptrFunction t);
   // сеттер для координат центра
   void setCenter(int xc, int yc);
   // сеттер для количества комнат
   void setNumRoom(int num);
   // сеттер для координат углов комнаты
   void setCoord(int xt1, int yt1, int xt2, int yt2);
   // геттер для координат углов комнаты
   int getX1();
   int getY1();
   int getX2();
   int getY2();
   // геттер для инструмента рисования
   ptrFunction getTool();
   // геттер для количества комнат
   int getNumRoom();
   int getCenterY() { return center.y; }
   int getCenterX() { return center.x; }
   //СОХРАНИТЬ В ПРОЕКТ
   void save();
};

//расположение на стене
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a);
//изменение размера объекта
IMAGE * resize(IMAGE *p, int w, int h);
#endif