



// ��������� ������
void button :: draw()
{
   
}

// ������� �� ������� ������ ������ � ������
void buttonFile :: press()
{
   // ��������
   action();
}

// ������� �� ������� ������ � �����������
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// ������� �� ������� ������ ������������ ��������
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

// ������� �� ������� ������ ��������������
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
      areaParams :: example().obj = object[((90 - areaParams :: example().weightDoor) / 10) % 3];
   else if (page == 2)
      areaParams :: example().obj = object[((250 - areaParams :: example().weightWindow) / 75) + 3];
   else areaParams :: example().obj = NULL;
   areaDraw :: example().setTool(tool);
   swapbuffers();
}

// ������� �� ������� ������ ������
void buttonFurniture :: press()
{
   int p = Pages :: example().getCurrentPage();
   string param = "object/"+ to_string(p - 4) + "/groups.cfg";
   ifstream file(param);
   int m;
   string s, f = areaParams :: _abracadabra_cast(example());