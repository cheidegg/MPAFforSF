MPAFDisplay md;

void ssdl2015card_test() {
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

  md.addDataCardSigSample("HHSR1:_standard_prompt_ttW","ttW");
  
  md.addDataCardSample("HHSR1:_standard_prompt_ttZH","rares");
  md.addDataCardSample("HHSR1:_standard_prompt_Rares","rares");
  md.addDataCardSample("HHSR1:_standard_prompt_WW", "WW");
  md.addDataCardSample("HHSR1:_standard_prompt_WZ", "WZ");
  md.addDataCardSample("HHSR1:_standard_prompt_TG", "TG");
  md.addDataCardSample("HHSR1:_standard_prompt_VG", "VG");
  md.addDataCardSample("HHSR1:_flipsappl_data", "flip");
  md.addDataCardSample("HHSR1:_fakesappl_data", "fake");


  md.addDataCardSample("HHSR1:_standard_prompt_ttZH","pseudodata");
  md.addDataCardSample("HHSR1:_standard_prompt_Rares","pseudodata");
  md.addDataCardSample("HHSR1:_standard_prompt_WW", "pseudodata");
  md.addDataCardSample("HHSR1:_standard_prompt_WZ", "pseudodata");
  md.addDataCardSample("HHSR1:_standard_prompt_TG", "pseudodata");
  md.addDataCardSample("HHSR1:_standard_prompt_VG", "pseudodata");
  md.addDataCardSample("HHSR1:_flipsappl_data", "pseudodata");
  md.addDataCardSample("HHSR1:_fakesappl_data", "pseudodata");

  //experimental uncertainties
  md.addNuisanceParameter("jes","ttW:rares","lnN","1.08:1.07");

  //Data-driven methods
  md.addNuisanceParameter("chMID","flip","lnN","1.30");
  md.addNuisanceParameter("fratio","fake","lnN","1.35");

  //syst from stat uncertainties == automatic
  //md.addNuisanceParameter("wzstat","wz","lnN",""); //--> already given by the 8/15% on Xsect
  // md.addNuisanceParameter("tthstat","tth","lnN","");
  // md.addNuisanceParameter("ttwstat","ttw","lnN","");
  // md.addNuisanceParameter("ttzstat","ttz","lnN","");
  // md.addNuisanceParameter("fakestat","fake","lnN","");
  // md.addNuisanceParameter("chMIdstat","chMId","lnN","");
  // md.addNuisanceParameter("SIGTAGstat","SIGTAG","lnN","");

  
  // string srs[66]={ 
  //   "SR1A", "SR2A", "SR3A", "SR4A", "SR5A", "SR6A", "SR7A", "SR8A",
  //   "SR9A", "SR10A", "SR11A", "SR12A", "SR13A", "SR14A", "SR15A", "SR16A",
  //   "SR17A", "SR18A", "SR19A", "SR20A", "SR21A", "SR22A", "SR23A", "SR24A",
  //   "SR25A", "SR26A", "SR27A", "SR28A", "SR29A", "SR30A", "SR31A", "SR32A",
    
  //   "SR1B", "SR2B", "SR3B", "SR4B", "SR5B", "SR6B", "SR7B", "SR8B",
  //   "SR9B", "SR10B", "SR11B", "SR12B", "SR13B", "SR14B", "SR15B", "SR16B",
  //   "SR17B", "SR18B", "SR19B", "SR20B", "SR21B", "SR22B", "SR23B", "SR24B",
  //   "SR25B","SR26B",
    
  //   "SR1C", "SR2C", "SR3C", "SR4C", "SR5C", "SR6C", "SR7C", "SR8C"
  // };



  // for(int isr=0;isr<66;isr++) {
  //   if(srs[isr]=="CATTAG") {
  //     md.addNuisanceParameter("tth"+srs[isr]+"stat","tth","lnN","");
  //     md.addNuisanceParameter("ttw"+srs[isr]+"stat","ttw","lnN","");
  //     md.addNuisanceParameter("ttz"+srs[isr]+"stat","ttz","lnN","");
  //     md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","");
  //     md.addNuisanceParameter("chMId"+srs[isr]+"stat","chMId","lnN","");
  //     md.addNuisanceParameter("SIGTAG"+srs[isr]+"stat","SIGTAG","lnN","");
  //   }
  //   else {
  //     md.addNuisanceParameter("tth"+srs[isr]+"stat","tth","lnN","-");
  //     md.addNuisanceParameter("ttw"+srs[isr]+"stat","ttw","lnN","-");
  //     md.addNuisanceParameter("ttz"+srs[isr]+"stat","ttz","lnN","-");
  //     md.addNuisanceParameter("fake"+srs[isr]+"stat","fake","lnN","-");
  //     md.addNuisanceParameter("chMId"+srs[isr]+"stat","chMId","lnN","-");
  //     md.addNuisanceParameter("SIGTAG"+srs[isr]+"stat","SIGTAG","lnN","-");
  //   }
  // }//signal regions  


  // md.addNuisanceParameter("SIGTAGStat","SIGTAG","lnN","");
  // md.addNuisanceParameter("ttwStat","ttw","lnN","");
  // md.addNuisanceParameter("ttzStat","ttz","lnN","");
  // md.addNuisanceParameter("wzStat","wz","lnN","");

  //md.addNuisanceParameter("sigNorm","T1t415","lnN","1.10");


  // }
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
   
  md.prepareDisplay();
  
 //  int nCateg=66; //47
 //  vector<string> _categs(nCateg,"");
 
 // string srs[66]={ 

 //    "SR1A", "SR2A", "SR3A", "SR4A", "SR5A", "SR6A", "SR7A", "SR8A",
 //    "SR9A", "SR10A", "SR11A", "SR12A", "SR13A", "SR14A", "SR15A", "SR16A",
 //    "SR17A", "SR18A", "SR19A", "SR20A", "SR21A", "SR22A", "SR23A", "SR24A",
 //    "SR25A", "SR26A", "SR27A", "SR28A", "SR29A", "SR30A", "SR31A", "SR32A",
    
 //    "SR1B", "SR2B", "SR3B", "SR4B", "SR5B", "SR6B", "SR7B", "SR8B",
 //    "SR9B", "SR10B", "SR11B", "SR12B", "SR13B", "SR14B", "SR15B", "SR16B",
 //    "SR17B", "SR18B", "SR19B", "SR20B", "SR21B", "SR22B", "SR23B", "SR24B",
 //    "SR25B","SR26B",
    
 //    "SR1C", "SR2C", "SR3C", "SR4C", "SR5C", "SR6C", "SR7C", "SR8C"
 // }

  // _categs.assign(srs, srs+nCateg);
  // for(size_t ic=0;ic< _categs.size();ic++) {
  //   string cat=_categs[ic];
    md.makeSingleDataCard("ttW", "global_HHSR1", "selected", "ssdl2015_ttW");
  // }

  gROOT->ProcessLine(".q");

}
