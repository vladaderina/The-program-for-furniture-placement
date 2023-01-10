#ifndef INTERFACE_H
#define INTERFACE_H





#define NUMBACKGROUND 5
#define  NUMOBJECT 7

using namespace std;

//  ��������� �� �������
typedef void (*ptrFunction)();
extern IMAGE *background[NUMBACKGROUND];
extern IMAGE *object[NUMOBJECT];
extern bool flag;

// ������� ����� ��� ������
struct Error
{
   int showTime = 0;
   virtual ~Error() {} // ����������
   virtual const void *what() const = 0; // ��������� ��� ������
};

struct ManyRoomsError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text1.jpg");
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      return 0;
   }
};

struct NoRoomError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text2.jpg");
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      return 0;
   }
};

struct ObjectOverlayError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text3.jpg");
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
      swapbuffers();
      //delay(1300);
      return 0;
   }
};

// ����� ��� �������
class Pages 
{
   //����� ��������
   int page;
   Pages() : page(0) {}
public:
   static Pages &example();
   //��������� ����
   void draw();
   //������ ��� ������ ��������
   void setPage(int page)
   {
      this -> page = page; 
   }
   //������ ��� ������ ��������
   int getPage()
   {
      return page; 
   }
};

// ����� ��� ��������, ������� ������������ �� ������
class objectDisplay 
{
public:
   int x1, y1, x2, y2;
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
      return x1 + 1; 
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
   // ������������� ���������� �����
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
   //��������� �������
   virtual void draw() = 0;
   //������� ������� �� �������
   virtual void press() = 0;
   //������� ��� ��������� �����
   virtual int getX1(); 
   virtual int getY1();
   virtual int getX2();
   virtual int getY2();
   //������ ��� ���� ������
   virtual int getType();
};

// ����� ��� ��������-������
class objectFurniture : public figure
{
   //��� ������ (0-14)
   int t;
public:
   //�������� ���������� �����
   objectFurniture(int x1, int y1, int x2, int y2, int t) : figure(x1, y1, x2, y2), t(1) { type = 1; }
   //��������� ������� 
   void draw() override;
   //������� ������� �� �������
   void press() override;
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
   int getType()
   {
      return type;
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
   //��������� �������
   void draw() override; //���������� ������
   //������� ������� �� �������
   void press() override;
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
   //������ ��� ���� ������
   int getType()
   {
      return type;
   }
   //������ ��� ������ �����
   void setW(int w);
};

// ����� ��� ��������, ������� ��������� �� �����
class objectFigureOnWall : public figure
{
public:
   //����� ����� �� 4 ����, �� ������� ���������� ������
   int numWall;
   IMAGE *objectOnWall;
   //�������� ���������� �����
   objectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, IMAGE *a) : figure(x1, y1, x2, y2), numWall(numWall), objectOnWall(a) { type = 3; }
   //��������� �������
   void draw() override;
   //������� ������� �� �������
   void press() override;
   //������ ��� ���� ������
   int getType()
   {
      return type;
   }
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
};

// ����� ��� ����������
class areaParams : public objectDisplay
{
   int w, h;
   // �������� ���������� �����
   areaParams (int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), _abracadabra_cast(heightWall(250));