



// ÎÒÐÈÑÎÂÊÀ ÊÍÎÏÊÈ
void button :: draw()
{
   
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÐÀÁÎÒÛ Ñ ÔÀÉËÎÌ
void buttonFile :: press()
{
   // ÄÅÉÑÒÂÈÅ
   action();
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ Ñ ÏÀÐÀÌÅÒÐÀÌÈ
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÏÅÐÅÊËÞ×ÅÍÈß ÑÒÐÀÍÈÖÛ
void buttonPage :: press()
{
   int p = Pages :: example().getCurrentPage();
   if (p == 3 || p == 4) Pages :: example().setListFurniturePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaDraw :: example().setTool(NULL);
   swapbuffers();
   delay(200);
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÈÍÑÒÐÓÌÅÍÒÀÐÈß
void buttonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().setType(1);
   if (page != 3)
   {
      areaParams :: example().draw();
   }
   if (page == 1)
   {
      areaParams :: example().obj = object[((90 - areaParams :: example().weightDoor) / 10) % 3];
      areaParams :: example().heightLift = 0;
      areaParams :: example().height = areaParams :: example().heightDoor;
   }
   else if (page == 2)
   {
      areaParams :: example().obj = object[((250 - areaParams :: example().weightWindow) / 75) + 3];
      areaParams :: example().heightLift = 150;
      areaParams :: example().height = areaParams :: example().heightWindow;
   }
   else areaParams :: example().obj = NULL;
   areaDraw :: example().setTool(tool);
   swapbuffers();
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÌÅÁÅËÈ
void buttonFurniture :: press()
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
         areaParams :: example().name.clear();
         int i = 0;
         while (s[i] != ':')
         {
            areaParams :: example().name += s[i];
            i++;
         }
         k = i + 2;
         istringstream s1(s.substr(k));
         s1 >> areaParams :: example().height;
      }
   }
   file.close();
   
   string obj = "object/"+ to_string(p - 4) + "/" + to_string(num) + ".bmp";
   Pages :: example().setListTypePage(p);
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: example().obj = loadBMP(obj.c_str());
   areaParams :: example().setType(2);
   areaDraw :: example().setTool(tool);
   setbkcolor(WHITE);
   setcolor(BLACK);
   settextjustify(LEFT_TEXT, CENTER_TEXT);
   settextstyle(1, HORIZ_DIR,  USER_CHAR_SIZE);
   setusercharsize(9, 20, 9, 10);
   const char * c = areaParams :: example().name.c_str();
   outtextxy(120, 123, c);
   swapbuffers();
}

// ÐÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÍÀÇÀÄ
void buttonBack :: press()
{
   int m = Pages :: example().getListFurniturePage();
   int n = Pages :: example().getListTypePage();
   int p = Pages :: example().getCurrentPage();
   if (p == 23) Pages :: example().setCurrentPage(n);
   else if (p >= 5 && p <= 22) Pages :: example().setCurrentPage(m);
   areaParams :: example().rotationFurniture = 0;
   areaParams :: example().heightFurniture = 0;
   Pages :: example().draw();
   areaDraw :: example().draw();
   swapbuffers();
   delay(200);
}

// ÓÄÀËÈÒÜ
void toolDelete()
{
   // ÊÓÐÑÎÐ
   int x = mousex();
   int y = mousey();
   // ÓÄÀËÅÍÈÅ ÔÈÃÓÐÛ, ÊÎÒÎÐÎÉ ÏÐÈÍÀÄËÅÆÈÒ ÒÎ×ÊÀ Â ÊÎÒÎÐÎÉ ÍÀÕÎÄÈÒÑß ÊÓÐÑÎÐ
   areaDraw :: example().deleteFigure(x, y);
}
 
// ÌÅÁÅËÜ
void toolFurniture()
{
   int x1 = mousex();
   int y1 = mousey();
   IMAGE *m = areaParams :: example().obj;
   int height = areaParams :: example().height;
   int heightLift = areaParams :: example().heightFurniture;
   if (!areaDraw :: example().getNumRoom()) throw NoRoomError();
   else if (areaDraw :: example().inRoom(mousex(), mousey()) && 
               areaDraw :: example().overlay(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), height, heightLift)) throw ObjectOverlayError();
   else if (areaDraw :: example().inRoom(x1, y1))
   {
      figure *rect = new objectFurniture(x1, y1, x1 + imagewidth(m), y1 + imageheight(m), 
      areaParams :: example().height, areaParams :: example().heightFurniture, m);
      areaDraw :: example().addFigure(rect);
      areaDraw :: _abracadabra_cast(example());