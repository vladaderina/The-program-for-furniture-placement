#include <graphics.h>
#include "interface.hpp"
#include "button.hpp"

//������ ����������
button *buttons[NUMBUTTONS];
//�������������
void mainInitialization()
{
   background[0] = loadBMP("Walls.jpg");
   background[1] = loadBMP("Door.jpg");
   background[2] = loadBMP("Windows.jpg");
   background[3] = loadBMP("Furniture_1.jpg");
   //������ �������������� (�����)
   buttons[0] = new buttonTools(0, 73, "icon/wall.bmp", toolWall);
   buttons[1] = new buttonTools(0, 73 + 75, "icon/door.bmp", toolDoor);
   buttons[2] = new buttonTools(0, 73 + 75*2, "icon/window.bmp", toolWindow);
   buttons[3] = new buttonTools(0, 75*4, "icon/delete.bmp", toolDelete);
   //������ ������ � ������ (������)
   buttons[4] = new buttonFile(0, 630, "icon/close.bmp", fileEnd);
   buttons[5] = new buttonFile(799, 102, "icon/save.bmp", fileSave);
   //������ ������
   for(int i = 6; i < NUMBUTTONS; i++)
   {
      buttons[i] = new buttonFurniture(160 + 120*((i - 6)%5), 600+82*((i - 6)/5), "icon/furniture/" + to_string(i - 5) + ".bmp", (i - 6), toolFurniture);
   }
   //������������� ����������� ���������� (������� ������ ��� �������� ���������, ���� �� ������, �� ��������� �������� ��� ������� ���) 
   areaDraw::example().setTool(toolWall);
}
//���������
void mainDraw()
{

   //��������� ������
   for(int i = 0; i < NUMBUTTONS; ++i)
   {  
      buttons[i]->draw();
   }
   //��������� ��������� ��������
   areaDraw::example().draw();
}
//�������� �������
int main()
{
   initwindow(1280, 720);
   //������������� � ��������� ���������
   mainInitialization();
   IMAGE *image1;
   image1 = loadBMP("Walls.jpg");
   putimage(0, 0, image1, COPY_PUT);
   mainDraw();
   int x, y;
   while(1) 
   {
      //��������� �������
      x = mousex();
      y = mousey();
      //����������� �������
      if(mousebuttons() == 1)
      {
         if(areaDraw::example().in(x, y))
         {
            areaDraw::example().press();
         }
         else
         {
            for(int i = 0; i < NUMBUTTONS; ++i)
            {
               if(buttons[i] -> in(x, y)) 
               {
                  areaDraw :: example().setBack(i);
                  putimage(0, 0, background[areaDraw::example().back], COPY_PUT);
                  areaDraw :: example().draw();
                  buttons[i]->press();
                  break;
               }
            }
         }
      }
      delay(60);
   }
   closegraph();
}
