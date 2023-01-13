#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 35
#define NUMBACKGROUND 24

// ����� ��� ������
class button: public objectClickable
{
public:
   // �������� ���������� �����
   button(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
   //���������� ������
   void draw();
};

//����� ��� ������ ������ � ������
class buttonFile: public button
{
   //��������
   ptrFunction action; 
public:
   // �������� ���������� �����, �������� � ��������� �� �������� � ������
   buttonFile(int x, int y, ptrFunction a) : button(x, y, x + 73, y + 73), action(a) {}
   //������� �� �������
   void press();
};

// ����� ��� ��������� ���������� �������
class buttonParam: public button
{
   int w, h;
public:
   //�������� ���������� ����� � ��������� �������
   buttonParam(int x, int y, int w, int h) : 
                        button(x, y, x + 75, y + 35), w(w), h(h) {}
   //������� �� �������
   void press();
};

// ����� ������ ��� �������� �� ���������� ��������
class buttonBack: public button
{
public:
   //�������� ���������� �����
   buttonBack(int x1, int y1, int x2, int y2) : button(x1, y1, x2, y2) {};
   //������� �� �������
   void press();
};

// ����� ��� �������� �� ��������
class buttonPage: public button
{
protected:
   // ����� ��������
   int page;
public:
   //�������� ���������� ����� � ����� ����
   buttonPage(int x1, int y1, int x2, int y2, int page) : button(x1, y1, x2, y2), page(page) {}
   //������� �� �������
   void press();
};

// ����� ��� ������ ��������������
class buttonTools : public buttonPage
{
protected:
   //����������
   ptrFunction tool;
public:
   //�������� ���������� �����, ����� �������� � ��������� �� ����������
   buttonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : buttonPage(x1, y1, x2, y2, page), tool(t) {}
   //������� �� �������
   void press();
};

// ����� ��� ������ ������
class buttonFurniture : public buttonTools
{
   // ����� ������
   int num;
public:
   //�������� ���������� �����, ����� �������� � ��������� �� ����������
   buttonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : buttonTools(x1, y1, x2, y2, page, t), num(num) {}
   //������� �� �������
   void press();
};

//-----------------------------------------------�������-----------------------------------------------/
//���������� ��������
void toolDelete();
//���������� �����������
void toolMove();
//���������� ������
void toolFurniture();
//���������� �����
void toolWall();
//���������� ������ �� �����
void toolOnWall();
//�������� �� �������
void fileLoad();
//���������� � ������
void fileSave();
//�������� ������ �����
void toolHeightDown();
//������ �������� ���������
void fileEnd(); 
#endif