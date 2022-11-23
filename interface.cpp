#include "interface.hpp"

IMAGE *background[4];

bool objectDisplay::in(int x, int y)
{
   return x > x1 && y > y1 && x < x2 && y < y2;
}

//-----------------------------------------------������-----------------------------------------------//
//���������� �������
void objectFurniture::save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
   fwrite(&t, sizeof(int), 1, f);
}

//�������� �������
bool objectFurniture::checkPressed(int x, int y)
{
   
   if (x1 > x2)
      swap(x1,x2);
   if (y1 > y2)
      swap(y1,y2);   
   if (x > x1 && x < x2 && y > y1 && y < y2)
      return true;
   else
      return false;
}

void objectFurniture::setT(int type) 
{
   t = type;
   draw();
}
//���������
void objectFurniture::draw()
{
   //�������
   setcolor(t);
   setfillstyle(SOLID_FILL, t);
   bar(x1, y1, x2, y2);
   //������
   setcolor(BLACK);
   rectangle(x1, y1, x2, y2);
}
void objectFurniture::press()
{
}
objectFurniture &objectFurniture::example()
{
   static objectFurniture st(0, 0, 0, 0, 1);
   return st;
}
//-----------------------------------------------�����-----------------------------------------------//
//���������� �������
void objectWall::save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
   fwrite(&w, sizeof(int), 1, f);
}
//�������� �������
bool objectWall::checkPressed(int x, int y)
{
   if (x1 > x2)
      swap(x1,x2);
   if (y1 > y2)
      swap(y1,y2);
   if (x > x1 && x < x2 && y > y1 && y < y2)
      return true;
   else
      return false;
}
//���������
void objectWall :: draw()
{
    cout << 1;
   //������
   setcolor(BLACK);
   setlinestyle(SOLID_LINE, w, w);
   rectangle(x1, y1, x2, y2);
}
void objectWall :: setW(int widthWall)
{
   w = widthWall;
}
void objectWall :: setNum(int number)
{
   num = number;
}
objectWall& objectWall :: example() 
{
   static objectWall sw(0, 0, 0, 0, 3);
   return sw;
}
//-----------------------------------------------��-�����-----------------------------------------------//
void objectFigureOnWall :: press(){
}
void objectWall::press(){}
//���������� �������
void objectFigureOnWall :: save(FILE *f)
{
   fwrite(&type, sizeof(int), 1, f);
   fwrite(&x1, sizeof(int), 1, f);
   fwrite(&y1, sizeof(int), 1, f);
   fwrite(&x2, sizeof(int), 1, f);
   fwrite(&y2, sizeof(int), 1, f);
}
//�������� �������
bool objectFigureOnWall :: checkPressed(int x, int y)
{
   if (x1 > x2)
   {
      swap(x1, x2);
   }
   if (y1 > y2)
   {
      swap(y1, y2);
   }
   if (x > x1 && x < x2 && y > y1 && y < y2)
   {
      return true;
   }
   else{
      return false;
   }
}
//���������
void objectFigureOnWall :: draw()
{
   //putimage(x, y, objectOnWall, COPY_PUT)
}
//-----------------------------------------------������� �����-----------------------------------------------//
//������� �����
areaDraw &areaDraw::example()
{
   static areaDraw pa(400, 60, 1280, 720);
   return pa;
}
//���������
void areaDraw :: draw()
{
   putimage(0, 0, background[back], COPY_PUT);
   //������
   for(int i = 0; i < areaDraw::example().figures.size(); i++)
      figures[i] -> draw();
}
//������� �� �������
void areaDraw :: press()
{
      tool();
}
//���������
void areaDraw::save()
{
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}

//�������� ������
void areaDraw :: addFigure(figure* figure)
{
   figures.push_back(figure);
}
//���������� �������
void areaDraw::outputObjects()
{
   ofstream fout;
   fout.open("output.txt");
   fout << "figures: \n";
   
   for(int i = 0; i < figures.size(); i++) 
   {
      fout << "x1: " << figures[i]->getX1() << " y1: " << figures[i] -> getY1() << " x2: " << figures[i] -> getX2() << " y2: " << figures[i]->getY2() <</*figures[i]->getT() <<*/ "\n";
   }
}
//������� ������
void areaDraw :: deleteFigure(int x, int y)
{
   for (int i = 0; i < figures.size(); i++)
   {
      if (figures[i] -> checkPressed(x, y))
      {
         figures.erase(figures.begin() + i); 
         draw();
         outputObjects();
         break;
      }
   }
}