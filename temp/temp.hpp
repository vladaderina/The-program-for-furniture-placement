#ifndef INTERFACE_H
#define INTERFACE_H





#define NUMBACKGROUND 5
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
   //мнлеп ярпюмхжш
   int page;
   Pages() : page(0) {}
public:
   static Pages &example();
   //нрпхянбйю тнмю
   void draw();
   //яерреп дкъ мнлепю ярпюмхжш
   void setPage(int page)
   {
      this -> page = page; 
   }
   //церреп дкъ мнлепю ярпюмхжш
   int getPage()
   {
      return page; 
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
   weightWall (35), _abracadabra_cast(heightWall(250));