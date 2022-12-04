#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 19
#define NUMBACKGROUND 5

// ����� ��� ������
class button: public objectClickable
{
public:
   // �������� ���������� ����� � ������ �� ��������
   button(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
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
   buttonFurniture(int x, int y, int type, ptrFunction t) : button(x, y, x + 290, y + 35), type(type), tool(t) {}
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
                        button(x, y, x + 75, y + 35), w(w), h(h) {}
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
   buttonTools(int x, int y, int type, ptrFunction t) : button(x, y, x + 73, y + 73), tool(t) {}
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
   buttonFile(int x, int y, ptrFunction a) : button(x, y, x + 73, y + 73), action(a) {}
   //������� �� �������
   void press();
};
//-----------------------------------------------�������-----------------------------------------------/
IMAGE *createmask(IMAGE *p);
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a);
void drawimage(int x, int y, IMAGE *m, IMAGE *p);
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