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

//  ��������� �� �������
typedef void (*ptrFunction)();
// ����
extern IMAGE *background[NUMBACKGROUND];
// ������� ������
extern IMAGE *object[NUMOBJECT];
extern bool flag;

//-----------------------------------------------������-----------------------------------------------//
struct Error
{
   virtual ~Error() {} // ����������
   virtual const void *what() const = 0; // ��������� ��� ������
};

struct ManyRoomsError: Error // �������� ����� 1 �������
{
   const void *what() const; // ��������� ��� ������
};

struct NoRoomError: Error // �� ������� �� ����� �������
{
   const void *what() const; // ��������� ��� ������
};

struct ObjectOverlayError: Error // ������� ������������� ���� �� �����
{
   const void *what() const; // ��������� ��� ������
};

//-----------------------------------------------��������-----------------------------------------------//
class Pages 
{
   // ����� �������� �� ������� ���� ������
   int listFurniturePage;
   // ����� �������� � ������ ��������� ������
   int listTypePage;
   // ����� ������� ��������
   int currentPage;
   // �����������
   Pages() : currentPage(0) {}
public:
   // ��������� ������
   static Pages &example();
   // ��������� ����
   void draw();
   // ������ ��� ������ ������� ��������
   void setCurrentPage(int page);
   // ������ ��� ������ ������� ��������
   int getCurrentPage();
   // ������ ��� ������ �������� �� ������� ���� ������
   void setListFurniturePage(int page);
   // ������ ��� ������ �������� �� ������� ���� ������ 
   int getListFurniturePage();
   // ������ ��� ������ �������� � ������ ��������� ������
   void setListTypePage(int page);
   // ������ ��� ������ �������� � ������ ��������� ������
   int getListTypePage();
};

//-----------------------------------------------������� �� ������-----------------------------------------------//
class objectDisplay
{
public:
   int x1, y1, x2, y2;
   // �����������
   objectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
   // ���������� ����������
   bool in(int x, int y); 
   // ����������� ������� ��� ��������� �������
   virtual void draw() = 0;
   // ������� ��� ��������� �����
   int getX1();
   int getY1();
   int getX2();
   int getY2();
   //����������
   virtual ~objectDisplay(){}
};

//-----------------------------------------------������� � �������� �� �������-----------------------------------------------//
class objectClickable: public objectDisplay
{
public:
   // �����������
   objectClickable(int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2) {}
   // ������� ������� �� �������
   virtual void press() = 0;
};

//-----------------------------------------------������-----------------------------------------------//
class figure: public objectDisplay
{
protected:
   //��� �������:
   //1 - ������
   //2 - �����
   //3 - ������� �� �����
   int type;
   int height;
   int heightLift; 
public:
   // ������������� ���������� �����, ������ � ������ �������
   figure(int x1, int y1, int x2, int y2, int height, int heightLift) : objectDisplay(x1, y1, x2, y2), height(height), heightLift(heightLift) {}
   // ��������� �������
   virtual void draw() = 0;
   // ������ ��� ������ ������
   virtual int getHeight();
   // ������ ��� ������ ������� ������
   virtual int getHeightLift();
   // ������ ��� ���� ������
   virtual int getType();
};

//-----------------------------------------------������-----------------------------------------------//
class objectFurniture : public figure
{
public:
   // ����������� ������
   IMAGE* m;
   // �����������
   objectFurniture(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE* m) :
                           figure(x1, y1, x2, y2, height, heightLift), m(m)
   {
      type = 1;
   }
   // ��������� �������
   void draw() override;
   // ������� ��� ���� ������
   int getType();
   // ������ ��� ������ ������
   int getHeight();
   // ������ ��� ������ ������ ��� �����
   int getHeightLift();
};

//-----------------------------------------------�����-----------------------------------------------//
class objectWall : public figure
{
   // ������ �����
   int w;
   // ���������� ������ �������
   int weightRoom, heightRoom;
   // ���������� ���������� �������
   void paramRoom();
public:
   // �����������
   objectWall(int x1, int y1, int x2, int y2, int height, int w) : figure(x1, y1, x2, y2, height, 0), w(w) { type = 2; }
   // ��������� ������� 
   void draw() override; 
   // ������ ��� ������ �����
   int getW();
   // ������ ��� ���� �������
   int getType();
   // ������ ��� ������ �����
   void setW(int w);
   // ������ ��� ������ �����
   int getHeight();
   // ������ ��� ������ ����� ��� ������� ����
   int getHeightLift();
};

//-----------------------------------------------�� �����-----------------------------------------------//
class objectFigureOnWall : public figure
{
public:
   // ����� ����� �� 4 ����, �� ������� ��������� ������
   int numWall;
   IMAGE *objectOnWall;
   // �����������
   objectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, int height, int heightLift, IMAGE *a) : 
         figure(x1, y1, x2, y2, height, heightLift), numWall(numWall), objectOnWall(a)
         { type = 3; }
   // ��������� �������
   void draw() override;
   // ������ ��� ���� �������
   int getType();
   // ������ ��� ������ �������
   int getHeight();
   // ������ ��� ������ ������� ��� ������� ����
   int getHeightLift();
};

//-----------------------------------------------���������-----------------------------------------------//
class areaParams : public objectDisplay
{
   // ��� �������
   int type;
   int a, b;
   // ������������� ��������� ��������� ���������
   areaParams (int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), heightWall(250),
   rotationFurniture(0), heightFurniture (0),
   height(0), heightLift(0)
   { obj = NULL; } 
public:
   // �������� �������
   string name;
   // ������ �������
   int height;
   // ������ ������� �������
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
   // ��������� ������
   static areaParams &example();
   // ��������� ����������
   void draw();
   // ������ ���� ������
   int getType();
   // ������ ���� ������
   void setType(int type);
   // ������ ����������
   void setParam(int a, int b);
   // ��������� ����������
   void changeParam();
};

//-----------------------------------------------������� �����-----------------------------------------------//
class areaDraw: public objectClickable 
{
   IMAGE *back = loadBMP("icon/back/areaDraw.jpg");
   // �������� ���������� �����
   areaDraw(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2), tool(nullptr), numRoom(0) {} 
protected:
   // ����� ������ ������������� �� ������
   int numRoom;
   // ���������� ������ �������
   struct center
   {
      int x, y;
   } center;
   // ���������� ����� �������
   struct coord
   {
      int x1, y1, x2, y2;
   } coord;
   // ��������� ����������
   ptrFunction tool; // ������� ����������
public:
   // ������ �������� ������������� �� ������
   vector <figure*> figures;
   // ������� �����
   static areaDraw &example();
   // ���������� �������
   void outputObjects();
   // �������� ��������� ������� �� ������
   bool overlay(int a, int b, int c, int d, int e, int f);
   // �������� �� ������� �������
   bool inRoom(int x, int y);
   // �������� ������
   void deleteFigure(int x, int y);
   // ���������� ������� �� ����
   void addFigure(figure* figure);
   // ��������� ��������
   void draw() override;
   // ������ ���
   void drawBack();
   // �������� ������� ����� ����������
   void projection(int x, int y);
   // ������� ������� �� �������
   void press() override;
   // ������ ��� ����������� ���������
   void setTool(ptrFunction t);
   // ������ ��� ��������� ������
   void setCenter(int xc, int yc);
   // ������ ��� ���������� ������
   void setNumRoom(int num);
   // ������ ��� ��������� ����� �������
   void setCoord(int xt1, int yt1, int xt2, int yt2);
   // ������ ��� ��������� ����� �������
   int getX1();
   int getY1();
   int getX2();
   int getY2();
   // ������ ��� ����������� ���������
   ptrFunction getTool();
   // ������ ��� ���������� ������
   int getNumRoom();
   int getCenterY() { return center.y; }
   int getCenterX() { return center.x; }
   //��������� � ������
   void save();
};

//������������ �� �����
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a);
//��������� ������� �������
IMAGE * resize(IMAGE *p, int w, int h);
#endif