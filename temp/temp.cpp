

IMAGE *background[NUMBACKGROUND];
IMAGE *object[NUMOBJECT];
bool flag = 0;

bool objectDisplay :: in(int x, int y)
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

//-----------------------------------------------������-----------------------------------------------//

const void *ManyRoomsError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text1.jpg");
   putimage(63, 556, image, COPY_PUT); 
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
   swapbuffers();
   return 0;
}

const void *NoRoomError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text2.jpg");
   putimage(63, 556, image, COPY_PUT); 
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
   swapbuffers();
   return 0;
}
const void *ObjectOverlayError :: what() const
{
   IMAGE *image =  loadBMP("icon/back/text3.jpg");
   putimage(63, 556, image, COPY_PUT);
   swapbuffers();
   putimage(63, 556, image, COPY_PUT); // ��������� ��� ������
   swapbuffers();
   //delay(1300);
   return 0;
}
//-----------------------------------------------��������-----------------------------------------------//
Pages &Pages :: example()
{
   static Pages pg;
   return pg;
}
void Pages :: draw()
{
   putimage(0, 0, background[Pages :: example().getCurrentPage()], COPY_PUT);
}
void Pages :: setCurrentPage(int page)
{
   currentPage = page; 
}
// ������ ��� ������ ������� ��������
int Pages :: getCurrentPage()
{
   return currentPage; 
}
// ������ ��� ������ �������� �� ������� ���� ������
void Pages :: setListFurniturePage(int page)
{
   listFurniturePage = page; 
}
// ������ ��� ������ �������� �� ������� ���� ������ 
int Pages :: getListFurniturePage()
{
   return listFurniturePage; 
}
// ������ ��� ������ �������� � ������ ��������� ������
void Pages :: setListTypePage(int page)
{
   listTypePage = page; 
}
// ������ ��� ������ �������� � ������ ��������� ������
int Pages :: getListTypePage()
{
   return listTypePage; 
}

//-----------------------------------------------������� �� ������-----------------------------------------------//
// ������� ��� ��������� �����
int objectDisplay :: getX1()
{ 
   return x1; 
}
int objectDisplay :: getY1()
{ 
   return y1; 
}
int objectDisplay :: getX2()
{
   return x2; 
}
int objectDisplay :: getY2()
{
   return y2; 
}
//-----------------------------------------------������-----------------------------------------------//
//���������
void objectFurniture :: draw()
{
   putimage(x1, y1, m, TRANSPARENT_PUT);
}
// ������� ��� ���� ������
int objectFurniture :: getType()
{
   return type;
}
// ������ ��� ������ ������
int objectFurniture :: getHeight()
{
   return height;
}
int objectFurniture :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------�����-----------------------------------------------//
//���������
void objectWall :: draw()
{
   setlinestyle(SOLID_LINE, w / 3, w / 3);
   setcolor(RGB(153, 153, 153));
   rectangle(x1, y1, x2, y2);
}
void objectWall :: setW(int widthWall)
{
   w = widthWall;
}
void objectWall :: paramRoom()
{
   weightRoom = x2 - x1;
   heightRoom = y2 - y1;
}
// ������ ��� ������ �����
int objectWall :: getW()
{
   return w;
}
// ������ ��� ���� �������
int objectWall :: getType()
{
   return type;
}
// ������ ��� ������ �����
int objectWall :: getHeight()
{
   return height;
}   
// ������ ��� ������ ����� ��� ������� ����
int objectWall :: getHeightLift()
{
   return 0;
}
//-----------------------------------------------��-�����-----------------------------------------------//
//���������
void objectFigureOnWall :: draw()
{
   setcolor(RGB(243, 243, 243));
   if (numWall == 1)
   {
      line(x1, y1, x1 + imagewidth(m), y1);
   }
   else if (numWall == 2)
      line(x1 + imagewidth(m), y1, x1 + imagewidth(m), y1+ imageheight(m));
   else if (numWall == 3)
      line(x1, y1 + imageheight(m), x1 + imagewidth(m), y1 + imageheight(m));
   else if (numWall == 4)
      line(x1, y1, x1, y1+ imageheight(m));
   putimage(x1, y1, m, TRANSPARENT_PUT);
}
// ������ ��� ���� �������
int objectFigureOnWall :: getType()
{
   return type;
}
// ������ ��� ������ �������
int objectFigureOnWall :: getHeight()
{
   return height;
}
// ������ ��� ������ ������� ��� ������� ����
int objectFigureOnWall :: getHeightLift()
{
   return heightLift;
}
//-----------------------------------------------���������-----------------------------------------------//
areaParams &areaParams :: example()
{
   static areaParams pa(70, 60, 400, 720);
   return pa;
}
void areaParams :: draw()
{
   char str_w[10], str_h[10];
   char str_w_room[10], str_h_room[10];
   int num = Pages :: example().getCurrentPage();
   setcolor(RGB(0, 0, 0));
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   setbkcolor(RGB(243, 243, 243));
   if (num == 0)
   {
      sprintf(str_h, "%d", weightWall);
      sprintf(str_w, "%d", heightWall);
      sprintf(str_h_room, "%d", 2 * (areaDraw :: example().getY2() - areaDraw :: example().getY1()) / 3);
      sprintf(str_w_room, "%d", 2 * (areaDraw :: example().getX2() - areaDraw :: example().getX1()) / 3);
      setcolor(RGB(153, 153, 153));
      if (areaDraw :: _abracadabra_cast(example());