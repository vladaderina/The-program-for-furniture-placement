#include <graphics.h>
#include "interface.hpp"
#include "button.hpp"

// ÕŒœ » ”œ–¿¬À≈Õ»ﬂ
button *buttons[NUMBUTTONS];
//»Õ»÷»¿À»«¿÷»ﬂ
void mainInitialization()
{
   for (int i = 1; i <=  NUMBACKGROUND; i++)
   {
      string back = "icon/back/" + to_string(i) + ".jpg";
      background[i - 1] = loadBMP(back.c_str());
   }
   for (int i = 1; i <= 3; i++)
   {
      string obj = "object/door/" + to_string(i) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   for (int i = 4; i <= 6; i++)
   {
      string obj = "object/window/" + to_string(i - 3) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }

   //  ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ
   buttons[0] = new buttonTools(0, 73, 73, 149, 0, toolWall);
   buttons[1] = new buttonTools(0, 150, 73, 222, 1, toolOnWall);
   buttons[2] = new buttonTools(0, 223, 73, 296, 2, toolOnWall);
   
   //  ÕŒœ » Ã≈¡≈À»
   buttons[5] = new buttonFurniture(70, 170, 240, 285, 23, 1, toolFurniture);
   buttons[6] = new buttonFurniture(240, 170, 400, 285, 23, 2, toolFurniture);
   buttons[7] = new buttonFurniture(70, 285, 235, 420, 23, 3, toolFurniture);
   buttons[8] = new buttonFurniture(240, 285, 400, 420, 23, 4, toolFurniture);
   
   //  ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ
   buttons[9] = new buttonFile(0, 630, fileEnd);
   buttons[10] = new buttonFile(0, 510, fileSave);
   
   //  ÕŒœ » ƒÀﬂ œ≈–≈ Àﬁ◊≈Õ»ﬂ —“–¿Õ»÷
   buttons[3] = new buttonPage(0, 300, 73, 373, 3);
   buttons[4] = new buttonPage(0, 565, 73, 635, 24);
   int y;
   for(int i = 11; i <= 19; i++)
   {
      y = 190 + 50 * ((i - 11) % 15) + 26 * ((i - 11) / 3);
      buttons[i] = new buttonPage(90, y, 400, y + 35, i - 6);
      buttons[i + 9] = new buttonPage(90, y, 400, y + 35, i + 3);
   }
   buttons[29] = new buttonPage(70, 130, 400, 160, 3);
   buttons[30] = new buttonPage(70, 685, 400, 720, 4);
   
   //  ÕŒœ » œ¿–¿Ã≈“–Œ¬
   buttons[31] = new buttonParam(85, 215, 1, 0);
   buttons[32] = new buttonParam(85, 295, 0, 1);
   buttons[33] = new buttonParam(290, 215, -1, 0);
   buttons[34] = new buttonParam(290, 290, 0, -1);
   
   // ÕŒœ ¿ ¬Œ«¬–¿“¿ Õ¿«¿ƒ
   buttons[35] = new buttonBack(70, 90, 240, 140);
   
   //”—“¿Õ¿¬À»¬¿≈Ã —“¿Õƒ¿–“Õ€… »Õ—“–”Ã≈Õ“
   areaDraw :: example().setTool(toolWall);
}

//Œ—ÕŒ¬Õ¿ﬂ ‘”Õ ÷»ﬂ
int main()
{
   setlocale(LC_ALL, "rus");
   initwindow(1280, 720, "RoomPlanner", 0, 0, true);
   //»Õ»÷»¿À»«¿÷»ﬂ » Œ“–»—Œ¬ ¿ ›À≈Ã≈Õ“Œ¬
   mainInitialization();
   int x, y;
   Pages :: example().draw();
   areaParams :: example().draw();
   swapbuffers();
   Pages :: example().draw();
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
         if (flag) 
         {
            IMAGE* p = loadBMP("icon/back/clean.jpg");
            putimage(63, 556, p, COPY_PUT);
            swapbuffers();
            putimage(63, 556, p, COPY_PUT);
            swapbuffers();
            flag = 0;
         }
         if (areaDraw :: example().in(x, y))
         {
            areaDraw :: example().press();
         }
         else
         {
            int num = Pages :: example().getCurrentPage();
            for (int i = 0; i <= 4; i++)
            {
               if (buttons[i] -> in(x, y)) 
               {
                  buttons[i] -> press();
                  break;
               }
            }
            if (num >= 5 && num <= 22)
            {
               for (int i = 5; i <= 8; i++)
               {
                  if (buttons[i] -> in(x, y)) 
                  {
                     buttons[i] -> press();
                     break;
                  }
               }
            }
            if (num <= 2 || num == 23)
            {
               for (int i = 31; i <= 34; i++)
               {
                  if (buttons[i] -> in(x, y))
                  {
                     delay(200);
                     buttons[i] -> press();
                  }
               }
            }
            if (num == 3 || num == 4)
            {
               for (int i = 29; i <= 30; i++)
               {
                  if (buttons[i] -> in(x, y))
                  {
                     buttons[i] -> press();
                  }
               }
            }
            if (num == 3)
            {
               for (int i = 11; i <= 19; i++)
               {
                  if (buttons[i] -> in(x, y))
                  {
                     buttons[i] -> press();
                  }
               }
            }
            if (num == 4)
            {
               for (int i = 20; i <= 28; i++)
               {
                  if (buttons[i] -> in(x, y))
                  {
                     buttons[i] -> press();
                  }
               }
            }
            if (num >= 5 && num <= 23)
            {
               if (buttons[35] -> in(x, y)) 
               {
                  buttons[35] -> press();
               }
            }
            for (int i = 9; i <= 10; i++)
            {
               if (buttons[i] -> in(x, y)) 
               {
                  buttons[i] -> press();
                  if (i == 9) return 0;
               }
            }
         }
      }
      if (areaDraw :: example().getTool() != NULL)
      {
         if (areaDraw :: example().getNumRoom() && areaDraw :: example().inRoom(x, y))
         {
            areaDraw :: example().projection(x, y);
         }
         else if (areaDraw :: example().getNumRoom() && Pages :: example().getCurrentPage() != 0)
         {
            Pages :: example().draw();
            areaDraw :: example().draw();
            if ((Pages :: example().getCurrentPage() >= 0 && Pages :: example().getCurrentPage() <= 2) || Pages :: example().getCurrentPage() == 23) areaParams :: example().draw();
            swapbuffers();
         }
      }
      delay(30);
   }   
}
