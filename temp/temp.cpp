



// нрпхянбйю ймнойх
void button :: draw()
{
   
}
// пеюйжхъ мю мюфюрхе ймнойх леаекх
void buttonFurniture :: press()
{
   // сярюмнбхрэ хмярпслемр х рхо рхо леаекх
   areaDraw :: example().setTool(tool);
   objectFurniture :: example().setT(type);
}

// пеюйжхъ мю мюфюрхе ймнойх пюанрш я тюикнл
void buttonFile :: press()
{
   // деиярбхе
   action();
}

// пеюйжхъ мю мюфюрхе ймнойх я оюпюлерпюлх
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// пеюйжхъ мю мюфюрхе ймнойх оепейкчвемхъ ярпюмхжш
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

// пеюйжхъ мю мюфюрхе ймнойх хмярпслемрюпхъ
void buttonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   if (p == 5) Pages :: _abracadabra_cast(example());