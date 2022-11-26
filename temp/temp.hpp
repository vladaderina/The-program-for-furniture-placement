#ifndef INTERFACE_H
#define INTERFACE_H






using namespace std;

//сйюгюрекэ мю тсмйжхч
typedef void (*ptrFunction)();
extern IMAGE *background[4];
// йкюяя дкъ назейрнб, йнрнпше нрнапюфючряъ мю щйпюме
class objectDisplay 
{
protected:
   //йннпдхмюрш бепьхм опълнсцнкэмхйю
   int x1, y1, x2, y2;
public:
   
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
      return x1+1; 
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
   //онксвюел йннпдхмюрш сцкнб
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
   //дкъ опнбепйх мюфюрхъ мю тхцспс
   virtual bool checkPressed(int x, int y) = 0;
   //нрпхянбйю назейрю
   virtual void draw() = 0;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   virtual void press() = 0;
   //тсмйжхъ янупюмемхъ назейрю
   virtual void save(FILE *f) = 0;
   //церрепш дкъ йннпдхмюр сцкнб
   virtual int getX1(); 
   virtual int getY1();
   virtual int getX2();
   virtual int getY2();
};

// йкюяя дкъ назейрнб-леаекх
class objectFurniture : public figure
{
   //рхо леаекх (0-14)
   int t;
public:
   //онксвюел йннпдхмюрш сцкнб
   objectFurniture(int x1, int y1, int x2, int y2, int t) : figure(x1, y1, x2, y2), t(1) { type = 1; }
   //дкъ опнбепйх мюфюрхъ мю тхцспс
   bool checkPressed(int x, int y) override;
   //нрпхянбйю назейрю
   void draw() override;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //тсмйжхъ янупюмемхъ назейрю
   void save(FILE *f) override;
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
   //дкъ опнбепйх мюфюрхъ мю тхцспс
   bool checkPressed(int x, int y) override;
   //нрпхянбйю назейрю
   void draw() override; //МЮПХЯНБЮРЭ ТХЦСПС
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //тсмйжхъ янупюмемхъ назейрю
   void save(FILE *f);
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
   //яерреп дкъ ьхпхмш яремш
   void setW(int w);
};


// йкюяя дкъ назейрнб, йнрнпше мюундъряъ мю яреме (гюйпюьеммши опълнсцнкэмхй)
class objectFigureOnWall : public figure
{
public:
   IMAGE *objectOnWall;
   //онксвюел йннпдхмюрш сцкнб
   objectFigureOnWall(int x1, int y1, int x2, int y2, IMAGE *a) : figure(x1, y1, x2, y2), objectOnWall(a) { type = 3; }
   //дкъ опнбепйх мюфюрхъ мю тхцспс
   bool checkPressed(int x, int y) override;
   //нрпхянбйю назейрю
   void draw() override;
   //тсмйжхъ пеюйжхх мю мюфюрхе
   void press() override;
   //тсмйжхъ янупюмемхъ назейрю
   void save(FILE *f);
   //церрепш дкъ йннпдхмюр сцкнб
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

// йкюяя дкъ пюанвеи япедш
class areaDraw: public objectClickable 
{
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
   // онксвюел йннпдхмюрш сцкнб
   areaDraw(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2), tool(nullptr)
   { 
      numRoom = 0; 
   } 
   // люяяхб дкъ назейрнб пюяонкнфеммшу мю щйпюме
   vector <figure*> figures;
public:
   //мнлеп тнмю
   int back;
   //пюанвюъ япедю
   static areaDraw &example();
   //гюохяшбюел назейрш
   void outputObjects();
   //сдюкемхе тхцспш  б рнвйе йнрнпни мюундхряъ йспянп
   void deleteFigure(int x, int y);
   //янупюмемхе тхцспш
   void addFigure(figure* figure);
   //нрпхянбйю
   void draw() override;
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
   //яерреп дкъ мнлепю тнмю
   void setBack(int back)
   { 
      this -> back = back; 
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
      return _abracadabra_cast(coord);