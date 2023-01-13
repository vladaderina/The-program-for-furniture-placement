#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 35
#define NUMBACKGROUND 24

// йкюяя дкъ ймнонй
class button: public objectClickable
{
public:
   // онксвюел йннпдхмюрш сцкнб
   button(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
   //мюпхянбюрэ назейр
   void draw();
};

//йкюяя дкъ ймнонй пюанрш я тюикнл
class buttonFile: public button
{
   //деиярбхе
   ptrFunction action; 
public:
   // онксвюел йннпдхмюрш сцкнб, йюпрхмйс х сйюгюрекэ мю деиярбхе я тюикнл
   buttonFile(int x, int y, ptrFunction a) : button(x, y, x + 73, y + 73), action(a) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};

// йкюяя дкъ хглемемхъ оюпюлерпнб назейрю
class buttonParam: public button
{
   int w, h;
public:
   //онксвюел йннпдхмюрш сцкнб х оюпюлерпш назейрю
   buttonParam(int x, int y, int w, int h) : 
                        button(x, y, x + 75, y + 35), w(w), h(h) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};

// йкюяя ймнонй дкъ бнгбпюрю мю опедшдсысч ярпюмхжс
class buttonBack: public button
{
public:
   //онксвюел йннпдхмюрш сцкнб
   buttonBack(int x1, int y1, int x2, int y2) : button(x1, y1, x2, y2) {};
   //пеюйжхъ мю мюфюрхе
   void press();
};

// йкюяя дкъ оепеундю мю ярпюмхжс
class buttonPage: public button
{
protected:
   // мнлеп ярпюмхжш
   int page;
public:
   //онксвюел йннпдхмюрш сцкнб х мнлеп тнмю
   buttonPage(int x1, int y1, int x2, int y2, int page) : button(x1, y1, x2, y2), page(page) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};

// йкюяя дкъ ймнонй хмярпслемрюпхъ
class buttonTools : public buttonPage
{
protected:
   //хмярпслемр
   ptrFunction tool;
public:
   //онксвюел йннпдхмюрш сцкнб, мнлеп ярпюмхжш х сйюгюрекэ мю хмярпслемр
   buttonTools(int x1, int y1, int x2, int y2, int page, ptrFunction t) : buttonPage(x1, y1, x2, y2, page), tool(t) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};

// йкюяя дкъ ймнонй леаекх
class buttonFurniture : public buttonTools
{
   // мнлеп ймнойх
   int num;
public:
   //онксвюел йннпдхмюрш сцкнб, мнлеп ярпюмхжш х сйюгюрекэ мю хмярпслемр
   buttonFurniture(int x1, int y1, int x2, int y2, int page, int num, ptrFunction t) : buttonTools(x1, y1, x2, y2, page, t), num(num) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};

//-----------------------------------------------тсмйжхх-----------------------------------------------/
//хмярпслемр сдюкемхъ
void toolDelete();
//хмярпслемр оепелеыемхъ
void toolMove();
//хмярпслемр леаекэ
void toolFurniture();
//хмярпслемр яремю
void toolWall();
//хмярпслемр назейр мю яреме
void toolOnWall();
//гюцпсгйю хг опнейрю
void fileLoad();
//янупюмемхе б опнейр
void fileSave();
//хглемхрэ ьхпхмс яремш
void toolHeightDown();
//ймнойю гюйпшрхъ опнцпюллш
void fileEnd(); 
#endif