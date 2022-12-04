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
      ptrFunction a = toolDoor;
      if (areaDraw :: example().getTool() == a)
      {
         if (areaDraw :: example().in(x, y))
         {
            IMAGE *a;
            if (areaParams :: example().weightDoor == 70) a = loadBMP("icon/door1.bmp");
            else if (areaParams :: example().weightDoor == 80) a = loadBMP("icon/door2.bmp");
            else a = loadBMP("icon/door3.bmp");
            int numWall;
            IMAGE *m1 = positionOnWall(x, y, numWall, a), *m2;
            imageputpixel(a, 0, 0, WHITE);
            int x1 = x;
            int y1 = y;
            m2 = createmask(m1);
            Pages :: example().draw();
            areaDraw :: example().draw();
            if (Pages :: example().getPage() != 3)
            {
               areaParams :: example().draw();
            }
            setlinestyle(SOLID_LINE, 2, 2);
            if (areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m2), y1 + imageheight(m2))) setcolor(RED);
            else setcolor(GREEN);
            rectangle(x1, y1, x1 + imagewidth(m2), y1 + imageheight(m2));
            drawimage(x1, y1, m2, m1);
            swapbuffers();
         }
      }
   }
}
