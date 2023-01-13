



// ÎÒĞÈÑÎÂÊÀ ÊÍÎÏÊÈ
void button :: draw()
{
   
}

// ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ĞÀÁÎÒÛ Ñ ÔÀÉËÎÌ
void buttonFile :: press()
{
   // ÄÅÉÑÒÂÈÅ
   action();
}

// ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ Ñ ÏÀĞÀÌÅÒĞÀÌÈ
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÏÅĞÅÊËŞ×ÅÍÈß ÑÒĞÀÍÈÖÛ
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

// ĞÅÀÊÖÈß ÍÀ ÍÀÆÀÒÈÅ ÊÍÎÏÊÈ ÈÍÑÒĞÓÌÅÍÒÀĞÈß
void buttonTools :: press()
{
   int p = Pages :: example().getCurrentPage();
   Pages :: example().setCurrentPage(page);
   Pages :: example().draw();
   areaDraw :: example().draw();
   areaParams :: _abracadabra_cast(example());