#ifndef INTERFACE_H
#define INTERFACE_H
#include "graphics.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#define NUMBACKGROUND 24
#define  NUMOBJECT 7

using namespace std;

//  сйюгюрекэ мю тсмйжхч
typedef void (*ptrFunction)();
extern IMAGE *background[NUMBACKGROUND];
extern IMAGE *object[NUMOBJECT];
extern bool flag;

// аюгнбши йкюяя дкъ ньханй
struct Error
{
   int showTime = 0;
   virtual ~Error() {} // ДЕЯРПСЙРНП
   virtual const void *what() const = 0; // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
};

struct ManyRoomsError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text1.jpg");
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      return 0;
   }
};

struct NoRoomError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text2.jpg");
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      return 0;
   }
};

struct ObjectOverlayError: Error
{
   const void *what() const
   {
      IMAGE *image =  loadBMP("icon/back/text3.jpg");
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      putimage(63, 556, image, COPY_PUT); // ЯННАЫЕМХЕ ДКЪ ОЕВЮРХ
      swapbuffers();
      //delay(1300);
      return 0;
   }
};

// йкюяя дкъ ярпюмхж
class Pages 
{
   // мнлеп ярпюмхжш ян яохяйнл бяеи леаекх 
   int listFurniturePage;
   // мнлеп ярпюмхжш я рхоюлх бшапюммни леаекх
   int listTypePage;
   // мнлеп рейсыеи ярпюмхжш
   int currentPage;
   Pages() : currentPage(0) {}
public:
   static Pages &example();
   // нрпхянбйю тнмю
   void draw();
   // яерреп дкъ мнлепю рейсыеи ярпюмхжш
   void setCurrentPage(int page)
   {
      currentPage = page; 
   }
   // церреп дкъ мнлепю рейсыеи ярпюмхжш
   int getCurrentPage()
   {
      return currentPage; 
   }
   // яерреп дкъ мнлепю ярпюмхжш ян яохяйнл бяеи леаекх
   void setListFurniturePage(int page)
   {
      listFurniturePage = page; 
   }
   // церреп дкъ мнлепю ярпюмхжш ян яохяйнл бяеи леаекх 
   int getListFurniturePage()
   {
      return listFurniturePage; 
   }
   // яерреп дкъ мнлепю ярпюмхжш я рхоюлх бшапюммни леаекх
   void setListTypePage(int page)
   {
      listTypePage = page; 
   }
   // церреп дкъ мнлепю ярпюмхжш я рхоюлх бшапюммни леаекх
   int getListTypePage()
   {
      return listTypePage; 
   }
};

// йкюяя дкъ назейрнб, йнрнпше нрнапюфючряъ мю щйпюме
class objectDisplay 
{
public:
   int x1, y1, x2, y2;
   //онксвюел йннпдхмюрш бепьхм опълнсцнкэмхйю
   objectDisplay(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
   //бмсрпеммхе йннпдхмюрш
   bool in(int x, int y); 
   //бхпрсюкэмюъ тсмйжхъ дкъ нрпхянбйх назейрю
   virtual void draw() = 0;
   //церрепш дкъ йннпдхмюр бепумецн кебнцн сцкю, бшянрш х ьхпхмш
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
   //деярпсйрнп
   virtual ~objectDisplay(){}
};

//йкюяя дкъ назейрнб, йнрнпше пеюцхпсчр мю мюфюрхе
class objectClickable: public objectDisplay
{
public:
   // сярюмюбкхбюел йннпдхмюрш сцкнб
   objectClickable(int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2) {}
   //тсмйжхъ пеюйжхх мю мюфюрхе
   virtual void press() = 0;
};

//йкюяя дкъ бяеу тхцсп
class figure: public objectClickable
{
protected:
   //рхо назейрю:
      //1 - леаекэ
      //2 - яремш
      //3 - назейрш мю яреме
   int type;
public:
   //онксвюел йннпдхмюрш сцкнб
   figure(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
   //нрпхянбйю назейрю
   virtual void draw() = 0;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   virtual void press() = 0;
   //церрепш дкъ йннпдхмюр сцкнб
   virtual int getX1(); 
   virtual int getY1();
   virtual int getX2();
   virtual int getY2();
   //церреп дкъ рхою тхцспш
   virtual int getType();
};

// йкюяя дкъ назейрнб-леаекх
class objectFurniture : public figure
{
   //рхо леаекх (0-14)
   int t;
public:
   //онксвюел йннпдхмюрш сцкнб
   objectFurniture(int x1, int y1, int x2, int y2, int t) : figure(x1, y1, x2, y2), t(1) { type = 1; }
   //нрпхянбйю назейрю 
   void draw() override;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //церрепш дкъ йннпдхмюр сцкнб
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
   //церреп дкъ рхою леаекх
   int getT()
   {
      return t;
   }
   //церреп дкъ рхою тхцспш
   int getType()
   {
      return type;
   }
   //яерреп дкъ рхою леаекх
   void setT(int t);
   //назейр
   static objectFurniture &example();
};

//йкюяя дкъ ярем
class objectWall : public figure
{
   //ьхпхмю яремш
   int w;
   // йннпдхмюрш жемрпю йнлмюрш
   int weightRoom, heightRoom;
   // бшвхякемхе оюпюлерпнб йнлмюрш
   void paramRoom();
public:
   //йнмярпсйрнп
   objectWall(int x1, int y1, int x2, int y2, int w) : figure(x1, y1, x2, y2), w(w) { type = 2; }
   //нрпхянбйю назейрю
   void draw() override; //МЮПХЯНБЮРЭ ТХЦСПС
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //церрепш дкъ йннпдхмюр сцкнб
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
   //церреп дкъ ьхпхмш яремш
   int getW()
   {
      return w;
   }
   //церреп дкъ рхою тхцспш
   int getType()
   {
      return type;
   }
   //яерреп дкъ ьхпхмш яремш
   void setW(int w);
};

// йкюяя дкъ назейрнб, йнрнпше мюундъряъ мю яреме
class objectFigureOnWall : public figure
{
public:
   //мнлеп ндмни хг 4 ярем, мю йнрнпни пюяонкнфем назейр
   int numWall;
   IMAGE *objectOnWall;
   //онксвюел йннпдхмюрш сцкнб
   objectFigureOnWall(int x1, int y1, int x2, int y2, int numWall, IMAGE *a) : figure(x1, y1, x2, y2), numWall(numWall), objectOnWall(a) { type = 3; }
   //нрпхянбйю назейрю
   void draw() override;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //церреп дкъ рхою тхцспш
   int getType()
   {
      return type;
   }
   //церрепш дкъ йннпдхмюр сцкнб
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

// йкюяя дкъ оюпюлерпнб
class areaParams : public objectDisplay
{
   int w, h;
   // онксвюел йннпдхмюрш сцкнб
   areaParams (int x1, int y1, int x2, int y2) : objectDisplay(x1, y1, x2, y2),
   weightDoor(70), heightDoor(200), 
   weightWindow(100), heightWindow(110), 
   weightWall (35), heightWall(250),
   rotationFurniture(0), heightFurniture (0)
   { obj = NULL; } 
public:
   IMAGE *obj;
   int weightDoor,
        heightDoor,
        weightWindow,
        heightWindow,
        weightWall,
        heightWall,
        rotationFurniture,
        heightFurniture;
   static areaParams &example();
   void draw();
   void setParam(int w, int h);
   void changeParam();
};

// йкюяя дкъ пюанвеи япедш
class areaDraw: public objectClickable 
{
   IMAGE *back = loadBMP("icon/back/areaDraw.jpg");
   // онксвюел йннпдхмюрш сцкнб
   areaDraw(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2), tool(nullptr), numRoom(0) {} 
protected:
   // вхякн йнлмюр пюяонкнфеммшу мю щйпюме
   int numRoom;
   // йннпдхмюрш жемрпю йнлмюрш
   struct center
   {
      int x, y;
   } center;
   // йннпдхмюрш сцкнб йнлмюрш
   struct coord
   {
      int x1, y1, x2, y2;
   } coord;
   //бшапюммши хмярпслемр
   ptrFunction tool; // РЕЙСЫХИ ХМЯРПСЛЕМР
public:
   // люяяхб дкъ назейрнб пюяонкнфеммшу мю щйпюме
   vector <figure*> figures;
   //пюанвюъ япедю
   static areaDraw &example();
   //гюохяшбюел назейрш
   void outputObjects();
   //опнбепйю мюкнфемхъ назейрю мю дпсцхе
   bool overlay(int a, int b, int c, int d);
   // опнбепйю мю цпюмхжш йнлмрюмш 
   bool inRoom(int x, int y);
   //сдюкемхе тхцспш  б рнвйе йнрнпни мюундхряъ йспянп
   void deleteFigure(int x, int y);
   //янупюмемхе тхцспш
   void addFigure(figure* figure);
   //нрпхянбйю назейрнб
   void draw() override;
   // гюдмхи тнм
   void drawBack();
   //опнейжхъ назейрю оепед сярюмнбйни
   void projection(int x, int y);
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //яерреп дкъ хмярпслемрю пхянбюмхъ
   void setTool(ptrFunction t)
   { 
      tool = t; 
   }
   //яерреп дкъ йннпдхмюр жемрпю
   void setCenter(int xc, int yc)
   { 
      center.x = xc;
      center.y = yc;
   }
   //яерреп дкъ йнкхвеярбю йнлмюр
   void setNumRoom(int num)
   { 
      numRoom = num; 
   }
   //яерреп дкъ йннпдхмюр сцкнб йнлмюрш
   void setCoord(int xt1, int yt1, int xt2, int yt2)
   {
      coord.x1 = xt1;
      coord.y1 = yt1;
      coord.x2 = xt2;
      coord.y2 = yt2;
   } 
   // церреп дкъ йннпдхмюр сцкнб йнлмюрш
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
      return coord.x2;
   }
   int getY2()
   {
      return coord.y2;
   }
   //церреп дкъ хмярпслемрю пхянбюмхъ
   ptrFunction getTool()
   { 
      return tool; 
   }
   //церреп дкъ йннпдхмюр жемрпю йнлмюрш
   //ptrFunction getя()
   //{ 
   //   return tool; 
   //}
   //церреп дкъ йнкхвеярбю йнлмюр
   int getNumRoom()
   {
      return numRoom;
   }
   int getCenterY() { return center.y; }
   int getCenterX() { return center.x; }
   //янупюмхрэ б опнейр
   void save();
};

void drawimage(int x, int y, IMAGE *m, IMAGE *p);
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a);
IMAGE *createmask(IMAGE *p);
void drawimage(int x, int y, IMAGE *m, IMAGE *p);
IMAGE * resize(IMAGE *p, int w, int h);
#endif