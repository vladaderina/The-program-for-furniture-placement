#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 19
#define NUMBACKGROUND 5

// йкюяя дкъ ймнонй
class button: public objectClickable
{
public:
   // онксвюел йннпдхмюрш сцкнб х яяшкйс мю йюпрхмйс
   button(int x1, int y1, int x2, int y2) : objectClickable(x1, y1, x2, y2) {}
   //мюпхянбюрэ назейр
   void draw();
};
// йкюяя дкъ ймнонй леаекх
class buttonFurniture: public button
{
   //рхо леаекх(0-14)
   int type;
   //хмярпслемр
   ptrFunction tool; 
public:
   //онксвюел йннпдхмюрш сцкнб, йюпрхмйс дкъ ймнойх х сйюгюрекэ мю хмярпслемр
   buttonFurniture(int x, int y, int type, ptrFunction t) : button(x, y, x + 290, y + 35), type(type), tool(t) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};
// йкюяя дкъ оюпюлерпнб назейрю
class buttonParam: public button
{
   int w, h;
public:
   //онксвюел йннпдхмюрш сцкнб, йюпрхмйс дкъ ймнойх х сйюгюрекэ мю хмярпслемр
   buttonParam(int x, int y, int w, int h) : 
                        button(x, y, x + 75, y + 35), w(w), h(h) {}
   //пеюйжхъ мю мюфюрхе
   void press();
};
// йкюяя дкъ ймнонй хмярпслемрюпхъ
class buttonTools : public button
{
   //хмярпслемр
   ptrFunction tool; 
public:
   //онксвюел йннпдхмюрш сцкнб, йюпрхмйс дкъ ймнойх х сйюгюрекэ мю хмярпслемр
   buttonTools(int x, int y, int type, ptrFunction t) : button(x, y, x + 73, y + 73), tool(t) {}
   //пеюйжхъ мю мюфюрхе
   void press();
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
//-----------------------------------------------тсмйжхх-----------------------------------------------/
IMAGE *createmask(IMAGE *p);
IMAGE *positionOnWall(int &x1, int &y1, int &numWall, IMAGE *a);
void drawimage(int x, int y, IMAGE *m, IMAGE *p);
//хмярпслемр сдюкемхъ
void toolDelete();
//хмярпслемр оепелеыемхъ
void toolMove();
//хмярпслемр леаекэ
void toolFurniture();
//хмярпслемр яремю
void toolWall();
//хмярпслемр нймн
void toolWindow();
//хмярпслемр дбепх
void toolDoor();
//гюцпсгйю хг опнейрю
void fileLoad();
//янупюмемхе б опнейр
void fileSave();
//хглемхрэ ьхпхмс яремш
void toolHeightDown();
//ймнойю гюйпшрхъ опнцпюллш
void fileEnd(); 
#endif