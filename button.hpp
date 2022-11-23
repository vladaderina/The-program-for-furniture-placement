#ifndef button_H
#define button_H
#include <graphics.h>
#include "interface.hpp"
#define NUMBUTTONS 21

// йкюяя дкъ ймнонй
class button: public objectClickable
{
   //йюпрхмйю дкъ ймнойх
   IMAGE *image;
public:
   
   // онксвюел йннпдхмюрш сцкнб х яяшкйс мю йюпрхмйс
   button(int x, int y, string icon) : objectClickable(x, y, x + 62, y + 62), image(loadBMP(icon.c_str())) {}
   
   //мюпхянбюрэ назейр
   void draw();
   
   //деярпсйрнп
   ~button(){ 
      freeimage(image); 
   }
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
   buttonFurniture(int x, int y, string icon, int type, ptrFunction t) : button(x, y, icon), type(type), tool(t) {}
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
   buttonTools(int x, int y, string icon, ptrFunction t) : button(x, y, icon), tool(t) {}
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
   buttonFile(int x, int y, string icon, ptrFunction a) : button(x, y, icon), action(a) {}
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
void toolPlus();
//ймнойю гюйпшрхъ опнцпюллш
void fileEnd(); 
#endif