MPAFDisplay md;

void dataCardProd_HHSR9_T14t12() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="ssdl2fb_oct"; // not needed for statistics but provides the normalization
  string fileList="ssdl2fb_oct"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=1; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  //md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================

  md.addDataCardSigSample("HHSR9:_sig_T1t_1200_800","T14t12");
  
  md.addDataCardSample("HHSR9:_standard_prompt_WZ", "WZ");
  md.addDataCardSample("HHSR9:_standard_prompt_ttW","ttW");
  md.addDataCardSample("HHSR9:_standard_prompt_ttZH","ttHZ");
  md.addDataCardSample("HHSR9:_standard_prompt_WW", "WW");
  md.addDataCardSample("HHSR9:_standard_prompt_TG", "XG");
  md.addDataCardSample("HHSR9:_standard_prompt_VG", "XG");
  md.addDataCardSample("HHSR9:_standard_prompt_Rares","rares");
  md.addDataCardSample("HHSR9:_flipsappl_data", "flip");
  md.addDataCardSample("HHSR9:_fakesappl_data", "fake");

  md.addDataCardSample("HHSR9:data","data");
  
  
  //lumi
  md.addNuisanceParameter("lumi","WZ:ttW:ttHZ:WW:XG:rares:T14t12","lnN","1.08:1.08:1.08:1.08:1.08:1.08:1.08");

  //experimental uncertainties
  md.addNuisanceParameter("jes","ttW:ttZH:WW:XG:rares:T14t12","lnN","1.00:1.01:1.01:1.03:1.03:1.10");
  md.addNuisanceParameter("btag","ttW:ttZH:WW:XG:rares:T14t12","lnN","1.11:1.11:1.11:1.09:1.11:1.01");
  md.addNuisanceParameter("lEff","ttW:ttZH:WW:XG:rares:T14t12","lnN","1.04:1.04:1.04:1.04:1.04:1.04");
  md.addNuisanceParameter("tEff","ttW:ttZH:WW:XG:rares:T14t12","lnN","1.02:1.02:1.02:1.02:1.02:1.02");
  md.addNuisanceParameter("tHTE","ttW:ttZH:WW:XG:rares:T14t12","lnN","-:-:-:-:-:-");
  
  //test
  md.addNuisanceParameter("BTag","ttW","lnN","");
  
  //Data-driven methods
  md.addNuisanceParameter("chMID","flip","lnN","1.30");
  md.addNuisanceParameter("fratio","fake","lnN","1.30");
  md.addNuisanceParameter("frEwk","fake","lnN","1.10");

  //theoretical uncertainties
  md.addNuisanceParameter("wzTh","WZ","lnN","1.30");
  md.addNuisanceParameter("WWTh","ttW","lnN","1.50");
  md.addNuisanceParameter("TGTh","XG","lnN","1.50");
  md.addNuisanceParameter("rareTh","rares","lnN","1.50");
  //md.addNuisanceParameter("sigTh","T14t12","lnN","SIGTHTAG");

  md.addNuisanceParameter("ttWPdf","ttW","lnN","1.04");
  md.addNuisanceParameter("ttHZPdf","ttHZ","lnN","1.04");
  md.addNuisanceParameter("ttWXs","ttW","lnN","1.13");
  md.addNuisanceParameter("ttHZXs","ttHZ","lnN","1.11");
  md.addNuisanceParameter("ttWAcc","ttW","lnN","1.03");
  md.addNuisanceParameter("ttHZAcc","ttHZ","lnN","1.03");


  string srs[66]={ 
    "HHSR1", "HHSR2", "HHSR3", "HHSR4", "HHSR5", "HHSR6", "HHSR7", "HHSR8",
    "HHSR9", "HHSR10", "HHSR11", "HHSR12", "HHSR13", "HHSR14", "HHSR15", "HHSR16",
    "HHSR17", "HHSR18", "HHSR19", "HHSR20", "HHSR21", "HHSR22", "HHSR23", "HHSR24",
    "HHSR25", "HHSR26", "HHSR27", "HHSR28", "HHSR29", "HHSR30", "HHSR31", "HHSR32",
    
    "HLSR1", "HLSR2", "HLSR3", "HLSR4", "HLSR5", "HLSR6", "HLSR7", "HLSR8",
    "HLSR9", "HLSR10", "HLSR11", "HLSR12", "HLSR13", "HLSR14", "HLSR15", "HLSR16",
    "HLSR17", "HLSR18", "HLSR19", "HLSR20", "HLSR21", "HLSR22", "HLSR23", "HLSR24",
    "HLSR25","HLSR26",
    
    "LLSR1", "LLSR2", "LLSR3", "LLSR4", "LLSR5", "LLSR6", "LLSR7", "LLSR8"
  };

  //statistical uncertainties
  for(int isr=0;isr<66;isr++) {
    if(srs[isr]=="HHSR9") {
      md.addNuisanceParameter("ttW"+srs[isr]+"stat","ttW","gmN","");
      md.addNuisanceParameter("ttHZ"+srs[isr]+"stat","ttHZ","lnN","");
      md.addNuisanceParameter("WW"+srs[isr]+"stat","WW","lnN","");
      md.addNuisanceParameter("XG"+srs[isr]+"stat","XG","lnN","1.18");
      md.addNuisanceParameter("rares"+srs[isr]+"stat","rares","lnN","");
      md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","1.07");
      md.addNuisanceParameter("flip"+srs[isr]+"stat","flip","lnN","");
      md.addNuisanceParameter("T14t12"+srs[isr]+"stat","T14t12","lnN","");
      
    }
    else {
      md.addNuisanceParameter("ttW"+srs[isr]+"stat","ttW","gmN","-");
      md.addNuisanceParameter("ttHZ"+srs[isr]+"stat","ttHZ","lnN","-");
      md.addNuisanceParameter("WW"+srs[isr]+"stat","WW","lnN","-");
      md.addNuisanceParameter("XG"+srs[isr]+"stat","XG","lnN","-");
      md.addNuisanceParameter("rares"+srs[isr]+"stat","rares","lnN","-");
      md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","-");
      md.addNuisanceParameter("flip"+srs[isr]+"stat","flip","lnN","-");
      md.addNuisanceParameter("T14t12"+srs[isr]+"stat","T14t12","lnN","-");
    }
  }//signal regions  

  //md.overwriteNuisanceParameter("ttWHHSR9stat","ttW","2.00");


  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
  md.makeSingleDataCard("T14t12", "global_HHSR9", "selected", "ssdl2015_HHSR9_T14t12");


  gROOT->ProcessLine(".q");

}
