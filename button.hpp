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
class ButtonParam: public Button
{
   int p1, p2;
public:
   // �����������
   ButtonParam(int x, int y, int p1, int p2) : 
                        Button(x, y, x + 75, y + 35), p1(p1), p2(p2) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ��� �������� �� ���������� ��������-----------------------------------------------//
class ButtonPreviousPage: public Button
{
public:
   // �����������
   ButtonPreviousPage(int x1, int y1, int x2, int y2) : Button(x1, y1, x2, y2) {};
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ��� �������� �� ��������-----------------------------------------------//
class ButtonNextPage: public Button
{
protected:
   // ����� ��������
   int page;
public:
   // �����������
   ButtonNextPage(int x1, int y1, int x2, int y2, int page) : Button(x1, y1, x2, y2), page(page) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ �������������-----------------------------------------------//
class ButtonTools : public ButtonNextPage
{
protected:
   // ����������
   ptrFunction tool;
public:
   // �����������
   ButtonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : ButtonNextPage(x1, y1, x2, y2, page), tool(t) {}
   // ������� �� �������
   void press();
};

//-----------------------------------------------����� ������ ������-----------------------------------------------//
class ButtonFurniture : public ButtonTools
{
   // ����� ������
   int num;
public:
   // �����������
   ButtonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : ButtonTools(x1, y1, x2, y2, page, t), num(num) {}
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