MPAFDisplay md;

void ssdl2015BTag(){
  md.refresh();

  //general parameters ********************* general parameters
  string dir="SSDL2015";
  string fileName="ssdl2fb_oct";
  string fileList="ssdl2fb_oct";
  
  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  md.dp.setObservables("MET");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=1;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={0,200};
  int xDiv[3]={8,6,0};
  int yDiv[3]={6,6,0}; //Nlabel /  sous-Div /ssdiv
  bool logYScale=false;
  bool overFlowBin=true;
  bool underFlowBin=false;
  bool showDMCRatio=true;
  bool showGrid=false;
  float markerSize=0.8;
  float lineWidth=2;

  bool summedSignal=false;
  bool stacking=true;

  bool cmsPrel=true;

  float xt=0.68;
  float yt=0.48;
  float st=0.039;
  string addText="";

  //string autoBinFile="susybinninghigh";
  //md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=true;
  
  bool mcStatSyst=false;
  string systSources="";

  bool uncDet=true;

  string Norm="";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=1280; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring15.db");

  map<string,float> LumisXS;

  //via XSect
  
  map<string,float> KFactors;
 
  // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
  

  //control categories ==============================
  //md.anConf.setControlCategs("Fake");
  //===============================================================
  
  md.anConf.addSample( "_sig_T1t_1200_800", "T14t12",  kOrange-2); 
  md.anConf.addSample( "_sig_T1t_1500_100","T14t15",  kOrange-2);
  md.anConf.addSample( "_sig_T5Deg","T54qDeg",  kOrange-2); 
  md.anConf.addSample( "_sig_T5q","T54q12",  kOrange-2); 
  md.anConf.addSample( "_sig_T5t", "T54q12",  kOrange-2); 
  md.anConf.addSample( "_sig_T6_600_425","T6ttWW60",  kOrange-2); 
  md.anConf.addSample( "_sig_T6_650_150","T6ttWW65",  kOrange-2); 
  md.anConf.addSample( "_standard_prompt_Rares","rare",  kOrange-2); 
  md.anConf.addSample( "_standard_prompt_WWss", "WW++", kOrange-2); 
  md.anConf.addSample( "_standard_prompt_WZ","WZ",kOrange-2); 
  md.anConf.addSample( "_standard_prompt_XG", "XG",  kOrange-2); 
  md.anConf.addSample( "_standard_prompt_ttW", "TTW",  kOrange-2); 
  md.anConf.addSample( "_standard_prompt_ttZH", "TTZH",  kOrange-2); 


  //===============================================================

  //*********************************************************************²

  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
  md.dp.setNormalization( Norm );
  md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal, 
			 mcOnly,cmsPrel, uncDet);
  
  md.prepareDisplay();
  //md.doPlot();
  //md.getStatistics("nominal");
  //md.addExternalSystUnc("rare","btag",30,-30);
  
  
  md.getCategSystematic("BTag","HH","selected");
  md.getCategSystematic("BTag","HL","selected");
  md.getCategSystematic("BTag","LL","selected");
  gROOT->ProcessLine(".q");
    //md.drawStatistics("global_BR00H", "selected");

  //md.savePlot("SUSY3L");
  // md.dp.addText(xt,yt,st,addText);

}
