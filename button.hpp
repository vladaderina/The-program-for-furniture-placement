#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 25
#define NUMBACKGROUND 5

// ����� ��� ������
class button: public objectClickable
{
public:
   // �������� ���������� ����� � ������ �� ��������
   button(int x, int y) : objectClickable(x, y, x + 62, y + 62) {}
   //���������� ������
   void draw();
};
// ����� ��� ������ ������
class buttonFurniture: public button
{
   //��� ������(0-14)
   int type;
   //����������
   ptrFunction tool; 
public:
   //�������� ���������� �����, �������� ��� ������ � ��������� �� ����������
   buttonFurniture(int x, int y, int type, ptrFunction t) : button(x, y), type(type), tool(t) {}
   //������� �� �������
   void press();
};
// ����� ��� ���������� �������
class buttonParam: public button
{
   int w, h;
public:
   //�������� ���������� �����, �������� ��� ������ � ��������� �� ����������
   buttonParam(int x, int y, int w, int h) : 
                        button(x, y), w(w), h(h) {}
   //������� �� �������
   void press();
};
// ����� ��� ������ ��������������
class buttonTools : public button
{
   //����������
   ptrFunction tool; 
public:
   //�������� ���������� �����, �������� ��� ������ � ��������� �� ����������
   buttonTools(int x, int y, int type, ptrFunction t) : button(x, y), tool(t) {}
   //������� �� �������
   void press();
};
//����� ��� ������ ������ � ������
class buttonFile: public button
{
   //��������
   ptrFunction action; 
public:
   // �������� ���������� �����, �������� � ��������� �� �������� � ������
   buttonFile(int x, int y, ptrFunction a) : button(x, y), action(a) {}
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
//���������� ����
void toolWindow();
//���������� �����
void toolDoor();
//�������� �� �������
void fileLoad();
//���������� � ������
void fileSave();
//�������� ������ �����
void toolHeightDown();
//������ �������� ���������
void fileEnd(); 
#endif