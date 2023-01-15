



// Œ“–»—Œ¬ ¿  ÕŒœ »
void button :: draw()
{
   
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » –¿¡Œ“€ — ‘¿…ÀŒÃ
void buttonFile :: press()
{
   // ƒ≈…—“¬»≈
   action();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » — œ¿–¿Ã≈“–¿Ã»
void buttonParam :: press()
{
   areaParams :: example().setParam(w, h);
   areaParams :: example().changeParam();
}

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » œ≈–≈ Àﬁ◊≈Õ»ﬂ —“–¿Õ»÷€
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

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » »Õ—“–”Ã≈Õ“¿–»ﬂ
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

// –≈¿ ÷»ﬂ Õ¿ Õ¿∆¿“»≈  ÕŒœ » Ã≈¡≈À»
void buttonFurniture :: press()
{
   int p = Pages :: example().getCurrentPage();
   string param = "object/"+ to_string(p - 4) + "/groups.cfg";
   ifstream file(param);
   int m;
   string s, f = areaParams :: _abracadabra_cast(example());