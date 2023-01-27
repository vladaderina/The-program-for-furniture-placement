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
class ObjectDisplay
{
public:
   int x1, y1, x2, y2;
   // �����������
   ObjectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
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
   virtual ~ObjectDisplay(){}
};

//-----------------------------------------------������� � �������� �� �������-----------------------------------------------//
class ObjectClickable: public ObjectDisplay
{
public:
   // �����������
   ObjectClickable(int x1, int y1, int x2, int y2) : ObjectDisplay(x1, y1, x2, y2) {}
   // ������� ������� �� �������
   virtual void press() = 0;
};

//-----------------------------------------------������-----------------------------------------------//
class Figure: public ObjectDisplay
{
protected:
   //��� �������:
   //1 - ������
   //2 - �����
   //3 - ������� �� �����
   int type;
   int height;
   int heightLift;
   // ����������� �������
   IMAGE *m;
public:
   // ������������� ���������� �����, ������ � ������ �������
   Figure(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE *m) : ObjectDisplay(x1, y1, x2, y2), 
            height(height), heightLift(heightLift), m(m) {}
   // ��������� �������
   virtual void draw();
   // ������ ��� ������ ������
   virtual int getHeight();
   // ������ ��� ������ ������� ������
   virtual int getHeightLift();
   // ������ ��� ���� ������
   virtual int getType();
};

//-----------------------------------------------������-----------------------------------------------//
class ObjectFurniture : public Figure
{
public:
   // �����������
   ObjectFurniture(int x1, int y1, int x2, int y2, int height, int heightLift, IMAGE* m) :
                           Figure(x1, y1, x2, y2, height, heightLift, m) {}
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
class ObjectWall : public Figure
{
   // ������ �����
   int w;
   // ���������� ������ �������
   int weightRoom, heightRoom;
   // ���������� ���������� �������
   void paramRoom();
public:
   // �����������
   ObjectWall(int x1, int y1, int x2, int y2, int height, int w) : Figure(x1, y1, x2, y2, height, 0, NULL), w(w) { type = 2; }
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
class ObjectFigureOnWall : public Figure
{
public:
   // ����� ����� �� 4 ����, �� ������� ��������� ������
   int numWall;
   // �����������
   ObjectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, int height, int heightLift, IMAGE *a) : 
         Figure(x1, y1, x2, y2, height, heightLift, a), numWall(numWall)
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
class AreaParams : public ObjectDisplay
{
   // ������������� ��������� ��������� ���������
   AreaParams (int x1, int y1, int x2, int y2) : ObjectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), heightWall(250),
   rotationFurniture(0), heightLiftFurniture (0),
   height(0), heightLift(0)
   { obj = NULL; } 
   // ���������� �������� ����� � ������������
   AreaParams (const AreaParams &) = delete;
   AreaParams & operator = (const AreaParams &) = delete;
   // ���������� ����������� �������
   ~AreaParams() {}
public:
      // ��� �������
   int type;
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
        heightLiftFurniture;
   // ��������� ������
   static AreaParams &example();
   // ��������� ����������
   void draw();
   // ������� ��� ����������
   void changeWallParam(int w, int h);
   void changeDoorParam(int w, int h);
   void changeWindowParam(int w, int h);
   void changeFurnitureParam(int r, int hl);
   void changeFurnitureOnWallParam(int r, int hl);
};

//-----------------------------------------------������� �����-----------------------------------------------//
class AreaDraw : public ObjectClickable
{
   IMAGE *back = loadBMP("icon/back/areaDraw.jpg");
   // �������� ���������� �����
   AreaDraw(int x1, int y1, int x2, int y2) : ObjectClickable(x1, y1, x2, y2), tool(nullptr), numRoom(0) {}
   ptrFunction tool; // ������� ����������
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
public:
   // ����� ������ ������������� �� ������
   int numRoom;
   // ������ �������� ������������� �� ������
   vector <Figure*> figures;
   // ������� �����
   static AreaDraw &example();
   // �������� ��������� ������� �� ������
   bool overlay(int x1, int y1, int x2, int y2, int h, int hl);
   // �������� �� ������� �������
   bool inRoom(int x, int y);
   // �������� ������
   void deleteFigure(int x, int y);
   // ���������� ������� �� ����
   void addFigure(Figure* Figure);
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