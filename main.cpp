#include <graphics.h>
#include "interface.hpp"
#include "button.hpp"

// ÕŒœ » ”œ–¿¬À≈Õ»ﬂ
button *buttons[NUMBUTTONS];
//»Õ»÷»¿À»«¿÷»ﬂ
void mainInitialization()
{
   for(int i = 1; i <=  NUMBACKGROUND; i++)
   {
      string back = "icon/back/" + to_string(i) + ".jpg";
      background[i - 1] = loadBMP(back.c_str());
   }
   for(int i = 1; i <=  3; i++)
   {
      string obj = "object/door/" + to_string(i) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   for(int i = 4; i <=  6; i++)
   {
      string obj = "object/window/" + to_string(i - 3) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   for(int i = 7; i <= 7; i++)
   {
      string obj = "object/sofas/" + to_string(3) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   // ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ
   buttons[0] = new buttonTools(0, 73, 1, toolWall);
   buttons[1] = new buttonTools(0, 73 + 75, 1, toolDoor);
   buttons[2] = new buttonTools(0, 73 + 75 * 2, 1, toolWindow);
   buttons[3] = new buttonTools(0, 75 * 4, 1, toolDelete);
   // ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ
   buttons[4] = new buttonFile(0, 630, fileEnd);
   buttons[5] = new buttonFile(0, 510, fileSave);
   // ÕŒœ » Ã≈¡≈À»
   for(int i = 6; i <= 14; i++)
   {
      buttons[i] = new buttonFurniture(90, 190 + 50 * ((i - 6) % 15) + 26 * ((i - 6) / 3), (i - 6), toolDelete);
   }
   // ÕŒœ » œ¿–¿Ã≈“–Œ¬
   buttons[15] = new buttonParam(85, 215, 1, 0);
   buttons[16] = new buttonParam(85, 295, 0, 1);
   buttons[17] = new buttonParam(290, 215, -1, 0);
   buttons[18] = new buttonParam(290, 290, 0, -1);
   //”—“¿Õ¿¬À»¬¿≈Ã —“¿Õƒ¿–“Õ€… »Õ—“–”Ã≈Õ“
   areaDraw::example().setTool(toolWall);
}

//Œ—ÕŒ¬Õ¿ﬂ ‘”Õ ÷»ﬂ
int main()
{
   initwindow(1280, 720, "RoomPlanner", 0, 0, true);
   //»Õ»÷»¿À»«¿÷»ﬂ » Œ“–»—Œ¬ ¿ ›À≈Ã≈Õ“Œ¬
   mainInitialization();
   
   setbkcolor(RGB(243, 243, 243));
   Pages :: example().draw();
   int x, y;
   areaParams :: example().draw();
   swapbuffers();
   while(1)
   {
      // Œ–ƒ»Õ¿“€  ”–—Œ–¿
      x = mousex();
      y = mousey();
      //Œ“—À≈∆»¬¿≈Ã Õ¿∆¿“»≈
      if(mousebuttons())
      {
         if (areaDraw :: example().in(x, y))
         {
            areaDraw :: example().press();
         }
         else
         {
            for (int i = 0; i <= 3; i++)
            {
               if (buttons[i] -> in(x, y)) 
               {
                  Pages :: example().setPage(i);
                  Pages :: example().draw();
                  areaDraw :: example().draw();
                  if (i != 3) 
                  {
                     areaParams :: example().draw();
                  }
                  swapbuffers();
                  buttons[i] -> press();
                  break;
               }
            }
            int num = Pages :: example().getPage();
            if (num == 0 || num == 1 || num == 2)
            {
               for(int i = 15; i <= 18; i++)
               {
                  if(buttons[i] -> in(x, y))
                  {
                     delay(50);
                     buttons[i] -> press();
                  }
               }
            }
            else if (num == 3 || num == 4)
            {
               for(int i = 6; i <= 14; i++)
               {
                  if (buttons[i] -> in(x, y))
                     bar(buttons[i] -> x1, buttons[i] -> y1, buttons[i] -> x2, buttons[i] -> y2);
                     buttons[i] -> press();
               }
            }
            for (int i = 4; i <= 5; i++)
            {
               if (buttons[i] -> in(x, y)) 
               {
                  buttons[i] -> press();
                  if (i == 4) return 0;
               }
            }
         }
      }
      if (areaDraw :: example().inRoom(x, y))
      {
         areaDraw :: example().projection(x, y);
      }
      else 
      {
         Pages :: example().draw();
         areaDraw :: example().draw();
         swapbuffers();
      }
      delay(30);
   }   
}
