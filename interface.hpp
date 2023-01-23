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
class objectDisplay
{
public:
   int x1, y1, x2, y2;
   // конструктор
   objectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
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
   virtual ~objectDisplay(){}
};

//-----------------------------------------------ОБЪЕКТЫ С РЕАКЦИЕЙ НА НАЖАТИЕ-----------------------------------------------//
class objectClickable: public objectDisplay
{
public:
   // конструктор
   objectClickable(int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2) {}
   // функция реакции на нажатие
   virtual void press() = 0;
};

//-----------------------------------------------ФИГУРЫ-----------------------------------------------//
class figure: public objectDisplay
{
protected:
   //тип объекта:
   //1 - мебель
   //2 - стены
   //3 - объекты на стене
   int type;
   int height;
   int heightLift; 
public:
   // устанавливаем координаты углов, высоту и высоту подъема
   figure(int x1, int y1, int x2, int y2, int height, int heightLift) : objectDisplay(x1, y1, x2, y2), height(height), heightLift(heightLift) {}
   // отрисовка объекта
   virtual void draw() = 0;
   // геттер для высоты фигуры
   virtual int getHeight();
   // геттер для высоты подъема фигуры
   virtual int getHeightLift();
   // геттер для типа фигуры
   virtual int getType();
};

//-----------------------------------------------МЕБЕЛЬ-----------------------------------------------//
class objectFurniture : public figure
{
public:
   // изображение мебели
   IMAGE* m;
   // конструктор
   objectFurniture(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE* m) :
                           figure(x1, y1, x2, y2, height, heightLift), m(m)
   {
      type = 1;
   }
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
class objectWall : public figure
{
   // ширина стены
   int w;
   // координаты центра комнаты
   int weightRoom, heightRoom;
   // вычисление параметров комнаты
   void paramRoom();
public:
   // конструктор
   objectWall(int x1, int y1, int x2, int y2, int height, int w) : figure(x1, y1, x2, y2, height, 0), w(w) { type = 2; }
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
class objectFigureOnWall : public figure
{
public:
   // номер одной из 4 стен, на которой находится объект
   int numWall;
   IMAGE *objectOnWall;
   // конструктор
   objectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, int height, int heightLift, IMAGE *a) : 
         figure(x1, y1, x2, y2, height, heightLift), numWall(numWall), objectOnWall(a)
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
class areaParams : public objectDisplay
{
   // тип объекта
   int type;
   int a, b;
   // устанавливаем начальные параметры рисования
   areaParams (int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), heightWall(250),
   rotationFurniture(0), heightFurniture (0),
   height(0), heightLift(0)
   { obj = NULL; } 
public:
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
        heightFurniture;
   // экземпляр класса
   static areaParams &example();
   // отрисовка параметров
   void draw();
   // геттер типа фигуры
   int getType();
   // сеттер типа фигуры
   void setType(int type);
   // сеттер параметров
   void setParam(int a, int b);
   // изменение параметров
   void changeParam();
};

//-----------------------------------------------РАБОЧАЯ СРЕДА-----------------------------------------------//
class areaDraw: public objectClickable 
{
   IMAGE *back = loadBMP("icon/back/areaDraw.jpg");
   // получаем координаты углов
   areaDraw(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2), tool(nullptr), numRoom(0) {} 
protected:
   // число комнат расположенных на экране
   int numRoom;
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
   // выбранный инструмент
   ptrFunction tool; // текущий инструмент
public:
   // вектор объектов расположенных на экране
   vector <figure*> figures;
   // рабочая среда
   static areaDraw &example();
   // записываем объекты
   void outputObjects();
   // проверка наложения объекта на другие
   bool overlay(int a, int b, int c, int d, int e, int f);
   // проверка на границы комнаты
   bool inRoom(int x, int y);
   // удаление фигуры
   void deleteFigure(int x, int y);
   // сохранение объекта на поле
   void addFigure(figure* figure);
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