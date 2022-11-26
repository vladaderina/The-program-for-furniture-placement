#ifndef INTERFACE_H
#define INTERFACE_H






using namespace std;

//��������� �� �������
typedef void (*ptrFunction)();
extern IMAGE *background[4];
// ����� ��� ��������, ������� ������������ �� ������
class objectDisplay 
{
protected:
   //���������� ������ ��������������
   int x1, y1, x2, y2;
public:
   
   //�������� ���������� ������ ��������������
   objectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
   //���������� ����������
   bool in(int x, int y); 
   //����������� ������� ��� ��������� �������
   virtual void draw() = 0;
   //������� ��� ��������� �������� ������ ����, ������ � ������
   int getTop() { 
      return y1 + 1; 
   }
   int getLeft() { 
      return x1+1; 
   }
   int getHeight() {
      return y2 - y1 - 1; 
   }
   int getWidth() {
      return x2 - x1 - 1; 
   }
   //����������
   virtual ~objectDisplay(){}
};

//����� ��� ��������, ������� ��������� �� �������
class objectClickable: public objectDisplay
{
public:
   //�������� ���������� �����
   objectClickable(int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2) {}
   //������� ������� �� �������
   virtual void press() = 0;
};

//����� ��� ���� �����
class figure: public objectClickable
{
protected:
   //��� �������:
      //1 - ������
      //2 - �����
      //3 - ������� �� �����
   int type;
public:
   //�������� ���������� �����
   figure(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
   //��� �������� ������� �� ������
   virtual bool checkPressed(int x, int y) = 0;
   //��������� �������
   virtual void draw() = 0;
   //������� ������� �� �������
   virtual void press() = 0;
   //������� ���������� �������
   virtual void save(FILE *f) = 0;
   //������� ��� ��������� �����
   virtual int getX1(); 
   virtual int getY1();
   virtual int getX2();
   virtual int getY2();
};

// ����� ��� ��������-������
class objectFurniture : public figure
{
   //��� ������ (0-14)
   int t;
public:
   //�������� ���������� �����
   objectFurniture(int x1, int y1, int x2, int y2, int t) : figure(x1, y1, x2, y2), t(1) { type = 1; }
   //��� �������� ������� �� ������
   bool checkPressed(int x, int y) override;
   //��������� �������
   void draw() override;
   //������� ������� �� �������
   void press() override;
   //������� ���������� �������
   void save(FILE *f) override;
   //������� ��� ��������� �����
   int getX1()
   { 
      return x1; 
   }
   int getY1()
   { 
      return y1; 
   }
   int getX2(){
      return x2; 
   }
   int getY2()
   {
      return y2; 
   }
   //������ ��� ���� ������
   int getT()
   {
      return t;
   }
   //������ ��� ���� ������
   void setT(int t);
   //������
   static objectFurniture &example();
};
//����� ��� ����
class objectWall : public figure
{
   //������ �����
   int w;
   // ���������� ������ �������
   int weightRoom, heightRoom;
   // ���������� ���������� �������
   void paramRoom();
public:
   //�����������
   objectWall(int x1, int y1, int x2, int y2, int w) : figure(x1, y1, x2, y2), w(w) { type = 2; }
   //��� �������� ������� �� ������
   bool checkPressed(int x, int y) override;
   //��������� �������
   void draw() override; //���������� ������
   //������� ������� �� �������
   void press() override;
   //������� ���������� �������
   void save(FILE *f);
   //������� ��� ��������� �����
   int getX1()
   { 
      return x1; 
   }
   int getY1()
   { 
      return y1; 
   }
   int getX2()
   {
      return x2; 
   }
   int getY2()
   {
      return y2; 
   }
   //������ ��� ������ �����
   int getW()
   {
      return w;
   }
   //������ ��� ������ �����
   void setW(int w);
};


// ����� ��� ��������, ������� ��������� �� ����� (����������� �������������)
class objectFigureOnWall : public figure
{
public:
   IMAGE *objectOnWall;
   //�������� ���������� �����
   objectFigureOnWall(int x1, int y1, int x2, int y2, IMAGE *a) : figure(x1, y1, x2, y2), objectOnWall(a) { type = 3; }
   //��� �������� ������� �� ������
   bool checkPressed(int x, int y) override;
   //��������� �������
   void draw() override;
   //������� ������� �� �������
   void press() override;
   //������� ���������� �������
   void save(FILE *f);
   //������� ��� ��������� �����
   int getX1(){ 
      return x1; 
   }
   int getY1(){ 
      return y1; 
   }
   int getX2(){
      return x2; 
   }
   int getY2(){
      return y2; 
   }
};

// ����� ��� ������� �����
class areaDraw: public objectClickable 
{
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
   //��������� ����������
   ptrFunction tool; // ������� ����������
   // �������� ���������� �����
   areaDraw(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2), tool(nullptr)
   { 
      numRoom = 0; 
   } 
   // ������ ��� �������� ������������� �� ������
   vector <figure*> figures;
public:
   //����� ����
   int back;
   //������� �����
   static areaDraw &example();
   //���������� �������
   void outputObjects();
   //�������� ������  � ����� ������� ��������� ������
   void deleteFigure(int x, int y);
   //���������� ������
   void addFigure(figure* figure);
   //���������
   void draw() override;
   //������� ������� �� �������
   void press() override;
   //������ ��� ����������� ���������
   void setTool(ptrFunction t)
   { 
      tool = t; 
   }
   //������ ��� ��������� ������
   void setCenter(int xc, int yc)
   { 
      center.x = xc;
      center.y = yc;
   }
   //������ ��� ������ ����
   void setBack(int back)
   { 
      this -> back = back; 
   }
   //������ ��� ���������� ������
   void setNumRoom(int num)
   { 
      numRoom = num; 
   }
   //������ ��� ��������� ����� �������
   void setCoord(int xt1, int yt1, int xt2, int yt2)
   {
      coord.x1 = xt1;
      coord.y1 = yt1;
      coord.x2 = xt2;
      coord.y2 = yt2;
   } 
   // ������ ��� ��������� ����� �������
   int getX1()
   {
      return coord.x1;
   } 
   int getY1()
   {
      return coord.y1;
   }
   int getX2()
   {
      return _abracadabra_cast(coord);