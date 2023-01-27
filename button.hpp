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
class buttonParam: public Button
{
   int w, h;
public:
   // конструктор
   buttonParam(int x, int y, int w, int h) : 
                        Button(x, y, x + 75, y + 35), w(w), h(h) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ДЛЯ ВОЗВРАТА НА ПРЕДЫДУЩУЮ СТРАНИЦУ-----------------------------------------------//
class buttonBack: public Button
{
public:
   // конструктор
   buttonBack(int x1, int y1, int x2, int y2) : Button(x1, y1, x2, y2) {};
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ДЛЯ ПЕРЕХОДА НА СТРАНИЦУ-----------------------------------------------//
class buttonPage: public Button
{
protected:
   // номер страницы
   int page;
public:
   // конструктор
   buttonPage(int x1, int y1, int x2, int y2, int page) : Button(x1, y1, x2, y2), page(page) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК ИНСТРУМЕТАРИЯ-----------------------------------------------//
class buttonTools : public buttonPage
{
protected:
   // инструмент
   ptrFunction tool;
public:
   // конструктор
   buttonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : buttonPage(x1, y1, x2, y2, page), tool(t) {}
   // реакция на нажатие
   void press();
};

//-----------------------------------------------КЛАСС КНОПОК МЕБЕЛИ-----------------------------------------------//
class buttonFurniture : public buttonTools
{
   // номер кнопки
   int num;
public:
   // конструктор
   buttonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : buttonTools(x1, y1, x2, y2, page, t), num(num) {}
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