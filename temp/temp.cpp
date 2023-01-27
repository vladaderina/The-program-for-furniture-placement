



///----------------------------ÊËÀÑÑ ÄËß ÊÍÎÏÎÊ ÑÎÕÐÀÍÅÍÈß È ÂÛÕÎÄÀ-------------------------------------//
void ButtonCommand :: press()
{
   // ÄÅÉÑÒÂÈÅ
   action();
}

//-----------------------------------------------ÊËÀÑÑ ÄËß ÊÍÎÏÎÊ ÈÇÌÅÍÅÍÈß ÏÀÐÀÌÅÒÐÎÂ----------------------------------------------//
void ButtonParam :: press()
{
   int num = Pages :: example().getCurrentPage();
   int num2 = Pages :: example().getListTypePage();
   if (num == 0)
      AreaParams :: example().setWallParam(p1, p2);
   else if (num == 1)
      AreaParams :: example().setDoorParam(p1, p2);
   else if (num == 2)
      AreaParams :: example().setWindowParam(p1, p2);
   else if (num == 23 && num2 != 12)
      AreaParams :: example().setFurnitureParam(p1, p2);
   else if (num == 23 && num2 == 12)
      AreaParams :: example().setFurnitureOnWallParam(p1, p2);
   AreaParams :: example().draw();
   swapbuffers();
}

//-----------------------------------------------ÊËÀÑÑ ÊÍÎÏÎÊ ÄËß ÂÎÇÂÐÀÒÀ ÍÀ ÏÐÅÄÛÄÓÙÓÞ ÑÒÐÀÍÈÖÓ-----------------------------------------------//
void ButtonPreviousPage :: press()
{
   int m = Pages :: example().getListFurniturePage();
   int n = Pages :: example().getListTypePage();
   int p = Pages :: example().getCurrentPage();
   if (p == 23) 
   {
      Pages :: example().setCurrentPage(n);
      AreaParams :: example().obj = NULL;
   }
   else if (p >= 5 && p <= 22) Pages :: example().setCurrentPage(m);
   AreaParams :: example().rotationFurniture = 0;
   AreaParams :: example().heightLiftFurniture = 0;
   AreaDraw :: example().setTool(NULL);
   Pages :: example().draw();
   AreaDraw :: example().draw();
   swapbuffers();
   delay(200);
}

//-----------------------------------------------ÊËÀÑÑ ÊÍÎÏÎÊ ÄËß ÏÅÐÅÕÎÄÀ ÍÀ ÑÒÐÀÍÈÖÓ-----------------------------------------------//
void ButtonNextPage :: press()
{
   int p = Pages :: example().getCurrentPage();
   if (p == 3 || p == 4) Pages :: example().setListFurniturePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   AreaDraw :: example().draw();
   AreaDraw :: example().setTool(NULL);
   swapbuffers();
   delay(200);
}
//-----------------------------------------------ÊËÀÑÑ ÊÍÎÏÎÊ ÈÍÑÒÐÓÌÅÒÀÐÈß-----------------------------------------------//
void ButtonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   AreaDraw :: example().draw();
   AreaParams :: example().type = 1;
   AreaParams :: example().draw();
   if (page == 1)
   {
      AreaParams :: example().obj = object[((90 - AreaParams :: example().weightDoor) / 10) % 3];
      AreaParams :: example().heightLift = 0;
      AreaParams :: example().height = AreaParams :: example().heightDoor;
   }
   else if (page == 2)
   {
      AreaParams :: example().obj = object[((250 - AreaParams :: example().weightWindow) / 75) + 3];
      AreaParams :: example().heightLift = 150;
      AreaParams :: example().height = AreaParams :: example().heightWindow;
   }
   else AreaParams :: example().obj = NULL;
   AreaDraw :: example().setTool(tool);
   swapbuffers();
}

//-----------------------------------------------ÊËÀÑÑ ÊÍÎÏÎÊ ÌÅÁÅËÈ-----------------------------------------------//
void ButtonFurniture :: press()
{
   int p = Pages :: example().getCurrentPage();
   string param = "object/"+ to_string(p - 4) + "/param.cfg";
   ifstream file(param);
   int m;
   string s;
   int k;
   int j = 0;
   while (getline(file, s))
   {
      j++;
      if (j == num)
      {
         AreaParams :: example().name.clear();
         int i = 0;
         while (s[i] != ':')
         {
            AreaParams :: example().name += s[i];
            i++;
         }
         k = i + 2;
         istringstream s1(s.substr(k));
         s1 >> AreaParams :: example().height;
      }
   }
   file.close();
   
   string obj = "object/"+ to_string(p - 4) + "/" + to_string(num) + ".bmp";
   AreaParams :: example().obj = loadBMP(obj.c_str());
   Pages :: example().setListTypePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   swapbuffers();
   Pages :: example().draw();
   AreaDraw :: example().draw();
   AreaParams :: example().heightLift = 0;
   AreaDraw :: example().setTool(tool);
   setbkcolor(WHITE);
   setcolor(BLACK);
   settextjustify(LEFT_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   const char * c = AreaParams :: example().name.c_str();
   outtextxy(120, 123, c);
   cout << 11;
   swapbuffers();
}

//-----------------------------------------------ÔÓÍÊÖÈÈ-----------------------------------------------//
//-----------------------------------------------ÓÄÀËÈÒÜ-----------------------------------------------//
void toolDelete()
{
   // ÊÓÐÑÎÐ
   int x = mousex();
   int y = mousey();
   // ÓÄÀËÅÍÈÅ ÔÈÃÓÐÛ, ÊÎÒÎÐÎÉ ÏÐÈÍÀÄËÅÆÈÒ ÒÎ×ÊÀ Â ÊÎÒÎÐÎÉ ÍÀÕÎÄÈÒÑß ÊÓÐÑÎÐ
   AreaDraw :: example().deleteFigure(x, y);
}
 
//-----------------------------------------------ÌÅÁÅËÜ-----------------------------------------------//
void toolFurniture()
{
   int x1 = mousex();
   int y1 = mousey();
   IMAGE *a = AreaParams :: example().obj;
   IMAGE *m;
   int numWall;
   if (AreaParams :: example().type == 1) m = positionOnWall(x1, y1, numWall, a);
   else m = a;
   int height = AreaParams :: example().height;
   int heightLift = AreaParams :: _abracadabra_cast(example());