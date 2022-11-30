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
   // ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ (—À≈¬¿)
   buttons[0] = new buttonTools(0, 73, 1, toolWall);
   buttons[1] = new buttonTools(0, 73 + 75, 1, toolDoor);
   buttons[2] = new buttonTools(0, 73 + 75 * 2, 1, toolWindow);
   buttons[3] = new buttonTools(0, 75 * 4, 1, toolDelete);
   // ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ (—œ–¿¬¿)
   buttons[4] = new buttonFile(0, 630, fileEnd);
   buttons[5] = new buttonFile(799, 102, fileSave);
   // ÕŒœ » Ã≈¡≈À»
   for(int i = 6; i < 21; i++)
   {
      buttons[i] = new buttonFurniture(160 + 120*((i - 6)%5), 600+82*((i - 6)/5), (i - 6), toolFurniture);
   }
   // ÕŒœ » œ¿–¿Ã≈“–Œ¬
   buttons[21] = new buttonParam(85, 215, 1, 0);
   buttons[22] = new buttonParam(85, 295, 0, 1);
   buttons[23] = new buttonParam(290, 215, -1, 0);
   buttons[24] = new buttonParam(290, 290, 0, -1);
   //”—“¿Õ¿¬À»¬¿≈Ã —“¿Õƒ¿–“Õ€… »Õ—“–”Ã≈Õ“ ( Œ“Œ–€… ¬€¡–¿Õ œ–» Œ“ –€“»» œ–Œ√–¿ÃÃ€, ≈—À» Õ≈ ¬€¡–¿Õ, “Œ œ–Œ√–¿ÃÃ¿  –¿ÿ»“—ﬂ œ–» Õ¿∆¿“»≈ À Ã) 
   areaDraw::example().setTool(toolWall);
}
//Œ“–»—Œ¬ ¿
void mainDraw()
{
   //Œ“–»—Œ¬ ¿  ÕŒœŒ 
   for(int i = 0; i < NUMBUTTONS; ++i)
   {  
      buttons[i]->draw();
   }
   //Œ“–»—Œ¬ ¿ —“¿“»◊Õ€’ Œ¡⁄≈ “Œ¬
   areaDraw::example().draw();
}
//Œ—ÕŒ¬Õ¿ﬂ ‘”Õ ÷»ﬂ
int main()
{
   initwindow(1280, 720);
   //»Õ»÷»¿À»«¿÷»ﬂ » Œ“–»—Œ¬ ¿ ›À≈Ã≈Õ“Œ¬
   mainInitialization();
   setbkcolor(RGB(243,243,243));
   Pages :: example().draw();
   mainDraw();
   int x, y;
   areaParams :: example().draw();
   while(1) 
   {
      // Œ–ƒ»Õ¿“€  ”–—Œ–¿
      x = mousex();
      y = mousey();
      //Œ“—À≈∆»¬¿≈Ã Õ¿∆¿“»≈
      if(mousebuttons() == 1)
      {
         if (areaDraw :: example().in(x, y))
         {
            areaDraw :: example().press();
         }
         else
         {
            for (int i = 0; i < 4; ++i)
            {
               if(buttons[i] -> in(x, y)) 
               {
                  Pages :: example().setPage(i);
                  Pages :: example().draw();
                  areaDraw :: example().draw();
                  if (i != 3) areaParams :: example().draw();
                  buttons[i] -> press();
                  break;
               }
            }
            int num = Pages :: example().getPage();
            if (num == 0 || num == 1 || num == 2)
            {
               for(int i = 1; i <= 4; ++i)
               {
                  if(buttons[20 + i] -> in(x, y))
                  {
                     buttons[20 + i] -> press();
                  }
               }
            }
            else if (num == 3 || num == 4)
            {
               for(int i = 0; i < 15; ++i)
               {
                  if(buttons[6 + i] -> in(x, y))
                     buttons[6 + i] -> press();
               }
            }
         }
      }
      delay(200);
   }
   closegraph();
}
