



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
   areaParams :: _abracadabra_cast(example());