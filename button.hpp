#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 36
#define NUMBACKGROUND 25

//-----------------------------------------------����� ��� ������-----------------------------------------------//
class Button: public ObjectClickable
{
public:
   // �����������
   Button(int x1, int y1, int x2, int y2) : ObjectClickable(x1, y1, x2, y2) {}
   // ���������� ������
   void draw(){};
};

//-----------------------------------------------����� ��� ������ ���������� � ������-----------------------------------------------//
class ButtonCommand: public Button
{
   // ��������
   ptrFunction action; 
public:
   // �����������
   ButtonCommand(int x, int y, ptrFunction a) : Button(x, y, x + 73, y + 73), action(a) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ��� ������ ��������� ����������-----------------------------------------------//
class buttonParam: public Button
{
   int w, h;
public:
   // �����������
   buttonParam(int x, int y, int w, int h) : 
                        Button(x, y, x + 75, y + 35), w(w), h(h) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ��� �������� �� ���������� ��������-----------------------------------------------//
class buttonBack: public Button
{
public:
   // �����������
   buttonBack(int x1, int y1, int x2, int y2) : Button(x1, y1, x2, y2) {};
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ��� �������� �� ��������-----------------------------------------------//
class buttonPage: public Button
{
protected:
   // ����� ��������
   int page;
public:
   // �����������
   buttonPage(int x1, int y1, int x2, int y2, int page) : Button(x1, y1, x2, y2), page(page) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ �������������-----------------------------------------------//
class buttonTools : public buttonPage
{
protected:
   // ����������
   ptrFunction tool;
public:
   // �����������
   buttonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : buttonPage(x1, y1, x2, y2, page), tool(t) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ������-----------------------------------------------//
class buttonFurniture : public buttonTools
{
   // ����� ������
   int num;
public:
   // �����������
   buttonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : buttonTools(x1, y1, x2, y2, page, t), num(num) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------�������-----------------------------------------------/
// ���������� "�������"
void toolDelete();
// ���������� "������"
void toolFurniture();
// ���������� "�����"
void toolWall();
// ����������  "������ �� �����"
void toolOnWall();
// ���������� �������
void fileSave();
// �������� ���
void fileEnd(); 
#endif