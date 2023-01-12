#ifndef button_H
#define button_H


#define NUMBUTTONS 19
#define NUMBACKGROUND 6

// йкюяя дкъ ймнонй
class button: public objectClickable
{
public:
   // онксвюел йннпдхмюрш сцкнб
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
   buttonBack(int x1, int y1, int x2, int y2) : _abracadabra_cast(button(x1, y1, x2, y2));