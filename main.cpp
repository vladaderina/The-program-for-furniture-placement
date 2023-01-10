#include <graphics.h>
#include "interface.hpp"
#include "button.hpp"

//������ ����������
button *buttons[NUMBUTTONS];
//�������������
void mainInitialization()
{
   for(int i = 1; i <=  NUMBACKGROUND; i++)
   {
      string back = "icon/back/" + to_string(i) + ".jpg";
      background[i - 1] = loadBMP(back.c_str());
   }
   for(int i = 1; i <= 3; i++)
   {
      string obj = "object/door/" + to_string(i) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   for(int i = 4; i <= 6; i++)
   {
      string obj = "object/window/" + to_string(i - 3) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   for(int i = 7; i <= 7; i++)
   {
      string obj = "object/sofas/" + to_string(3) + ".bmp";
      object[i - 1] = loadBMP(obj.c_str());
   }
   // ������ ��������������
   buttons[0] = new buttonTools(0, 73, 1, toolWall);
   buttons[1] = new buttonTools(0, 73 + 75, 1, toolOnWall);
   buttons[2] = new buttonTools(0, 73 + 75 * 2, 1, toolOnWall);
   buttons[3] = new buttonPage(0, 75 * 4, 73, 373, 3);
   // ������ ������ � ������
   buttons[4] = new buttonFile(0, 630, fileEnd);
   buttons[5] = new buttonFile(0, 510, fileSave);
   // ������ ��� ������������ �������
   int x = 90, y;
   for(int i = 6; i <= 14; i++)
   {
      y = 190 + 50 * ((i - 6) % 15) + 26 * ((i - 6) / 3);
      buttons[i] = new buttonPage(x, y, 290, y + 35, 5);
   }
   
   // ������ ����������
   buttons[15] = new buttonParam(85, 215, 1, 0);
   buttons[16] = new buttonParam(85, 295, 0, 1);
   buttons[17] = new buttonParam(290, 215, -1, 0);
   buttons[18] = new buttonParam(290, 290, 0, -1);
   //������������� ����������� ����������
   areaDraw :: example().setTool(toolWall);
}

//�������� �������
int main()
{
   initwindow(1280, 720, "RoomPlanner", 0, 0, true);
   //������������� � ��������� ���������
   mainInitialization();
   setbkcolor(RGB(243, 243, 243));
   Pages :: example().draw();
   int x, y;
   areaParams :: example().draw();
   swapbuffers();
   while(1)
   {
      //��������� �������
      x = mousex();
      y = mousey();
      //����������� �������
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
                     delay(200);
                     buttons[i] -> press();
                  }
               }
            }
            else if (num == 3 || num == 4)
            {
               for(int i = 6; i <= 14; i++)
               {
                  if (buttons[i] -> in(x, y))
                  {
                     buttons[i] -> press();
                  }
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
      if (areaDraw :: example().getNumRoom() && areaDraw :: example().inRoom(x, y))
      {
         //flag = 1;
         areaDraw :: example().projection(x, y);
      }
      else if (areaDraw :: example().getNumRoom() && Pages :: example().getPage() != 0)
      {
         //flag = 0;
         Pages :: example().draw();
         //areaDraw :: example().drawBack();
         areaDraw :: example().draw();
         if (Pages :: example().getPage() >= 0 && Pages :: example().getPage() <= 2) areaParams :: example().draw();
         swapbuffers();
      }
      delay(30);
   }   
}
