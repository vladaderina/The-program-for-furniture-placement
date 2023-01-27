#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 36
#define NUMBACKGROUND 25

//-----------------------------------------------КЛАСС ДЛЯ КНОПОК-----------------------------------------------//
class Button: public ObjectClickable
{
public:
   // конструктор
   Button(int x1, int y1, int x2, int y2) : ObjectClickable(x1, y1, x2, y2) {}
   // нарисовать объект
   void draw(){};
};

//-----------------------------------------------КЛАСС ДЛЯ КНОПОК СОХРАНЕНИЯ И ВЫХОДА-----------------------------------------------//
class ButtonCommand: public Button
{
   // действие
   ptrFunction action; 
public:
   // конструктор
   ButtonCommand(int x, int y, ptrFunction a) : Button(x, y, x + 73, y + 73), action(a) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС ДЛЯ КНОПОК ИЗМЕНЕНИЯ ПАРАМЕТРОВ-----------------------------------------------//
class ButtonParam: public Button
{
   int p1, p2;
public:
   // конструктор
   ButtonParam(int x, int y, int p1, int p2) : 
                        Button(x, y, x + 75, y + 35), p1(p1), p2(p2) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ДЛЯ ВОЗВРАТА НА ПРЕДЫДУЩУЮ СТРАНИЦУ-----------------------------------------------//
class ButtonPreviousPage: public Button
{
public:
   // конструктор
   ButtonPreviousPage(int x1, int y1, int x2, int y2) : Button(x1, y1, x2, y2) {};
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ДЛЯ ПЕРЕХОДА НА СТРАНИЦУ-----------------------------------------------//
class ButtonNextPage: public Button
{
protected:
   // номер страницы
   int page;
public:
   // конструктор
   ButtonNextPage(int x1, int y1, int x2, int y2, int page) : Button(x1, y1, x2, y2), page(page) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ИНСТРУМЕТАРИЯ-----------------------------------------------//
class ButtonTools : public ButtonNextPage
{
protected:
   // инструмент
   ptrFunction tool;
public:
   // конструктор
   ButtonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : ButtonNextPage(x1, y1, x2, y2, page), tool(t) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК МЕБЕЛИ-----------------------------------------------//
class ButtonFurniture : public ButtonTools
{
   // номер кнопки
   int num;
public:
   // конструктор
   ButtonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : ButtonTools(x1, y1, x2, y2, page, t), num(num) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------ФУНКЦИИ-----------------------------------------------/
// инструмент "Удалить"
void toolDelete();
// инструмент "Мебель"
void toolFurniture();
// инструмент "Стена"
void toolWall();
// инструмент  "Объект на стене"
void toolOnWall();
// сохранение проекта
void fileSave();
// закрытие про
void fileEnd(); 
#endif