#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 25
#define NUMBACKGROUND 5

// йкюяя дкъ ймнонй
class button: public objectClickable
{
public:
   // онксвюел йннпдхмюрш сцкнб х яяшкйс мю йюпрхмйс
   button(int x, int y) : objectClickable(x, y, x + 62, y + 62) {}
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
   buttonFurniture(int x, int y, int type, ptrFunction t) : button(x, y), type(type), tool(t) {}
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
                        button(x, y), w(w), h(h) {}
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
   buttonTools(int x, int y, int type, ptrFunction t) : button(x, y), tool(t) {}
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
   buttonFile(int x, int y, ptrFunction a) : button(x, y), action(a) {}
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