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
   //������ �������������� (�����)
   buttons[0] = new buttonTools(0, 73, 1, toolWall);
   buttons[1] = new buttonTools(0, 73 + 75, 1, toolDoor);
   buttons[2] = new buttonTools(0, 73 + 75 * 2, 1, toolWindow);
   buttons[3] = new buttonTools(0, 75 * 4, 1, toolDelete);
   //������ ������ � ������ (������)
   buttons[4] = new buttonFile(0, 630, fileEnd);
   buttons[5] = new buttonFile(799, 102, fileSave);
   //������ ������
   for(int i = 6; i < 15; i++)
   {
      buttons[i] = new buttonFurniture(90, 190 + 50 * ((i - 6) % 15) + 26 * ((i - 6) / 3), (i - 6), toolFurniture);
   }
   //������ ����������
   buttons[15] = new buttonParam(85, 215, 1, 0);
   buttons[16] = new buttonParam(85, 295, 0, 1);
   buttons[17] = new buttonParam(290, 215, -1, 0);
   buttons[18] = new buttonParam(290, 290, 0, -1);
   //������������� ����������� ���������� (������� ������ ��� �������� ���������, ���� �� ������, �� ��������� �������� ��� ������� ���) 
   areaDraw::example().setTool(toolWall);
}
//���������
void mainDraw()
{
   //��������� ������
   for(int i = 0; i < NUMBUTTONS; ++i)
   {  
      buttons[i] -> draw();
   }
   //��������� ��������� ��������
   areaDraw :: example().draw();
}
//�������� �������
int main()
{
   initwindow(1280, 720);
   //������������� � ��������� ���������
   mainInitialization();
   setbkcolor(RGB(243, 243, 243));
   Pages :: example().draw();
   mainDraw();
   int x, y;
   areaParams :: example().draw();
   while(1) 
   {
      //��������� �������
      x = mousex();
      y = mousey();
      //����������� �������
      if(mousebuttons())
      {
         if (areaDraw :: example().in(x, y))
         {
            areaDraw :: example().press();
         }
         else
         {
            for (int i = 0; i < 4; i++)
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
               for(int i = 1; i <= 4; i++)
               {
                  if(buttons[14 + i] -> in(x, y))
                  {
                     buttons[14 + i] -> press();
                  }
               }
            }
            else if (num == 3 || num == 4)
            {
               for(int i = 0; i < 9; i++)
               {
                  //if (buttons[6 + i] -> in(x, y))
                     bar(buttons[6 + i] -> x1, buttons[6 + i] -> y1, buttons[6 + i] -> x2, buttons[6 + i] -> y2);
                     //buttons[6 + i] -> press();
               }
            }
         }
      }
      delay(200);
   }
   closegraph();
}
