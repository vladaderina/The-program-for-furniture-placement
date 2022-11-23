#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 21

// ����� ��� ������
class button: public objectClickable
{
   //�������� ��� ������
   IMAGE *image;
public:
   
   // �������� ���������� ����� � ������ �� ��������
   button(int x, int y, string icon) : objectClickable(x, y, x + 62, y + 62), image(loadBMP(icon.c_str())) {}
   
   //���������� ������
   void draw();
   
   //����������
   ~button(){ 
      freeimage(image); 
   }
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
   buttonFurniture(int x, int y, string icon, int type, ptrFunction t) : button(x, y, icon), type(type), tool(t) {}
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
   buttonTools(int x, int y, string icon, ptrFunction t) : button(x, y, icon), tool(t) {}
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
   buttonFile(int x, int y, string icon, ptrFunction a) : button(x, y, icon), action(a) {}
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
void toolPlus();
//������ �������� ���������
void fileEnd(); 
#endif