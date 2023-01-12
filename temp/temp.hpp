#ifndef button_H
#define button_H


#define NUMBUTTONS 19
#define NUMBACKGROUND 6

// ����� ��� ������
class button: public objectClickable
{
public:
   // �������� ���������� �����
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
   buttonBack(int x1, int y1, int x2, int y2) : _abracadabra_cast(button(x1, y1, x2, y2));