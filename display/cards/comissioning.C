MPAFDisplay md;

void comissioning() {
  md.refresh();


  //general parameters ********************* general parameters
  string dir="Comissioning";
  string fileName="comissioning"; // not needed for statistics but provides the normalization
  string fileList="comissioning"; // put command line that gives all files as in a "ls" command

  bool mcOnly = false;
  
  md.anConf.configureNames( dir, fileName, fileList );
  md.anConf.configureData(false, 0, mcOnly);
  
  md.dp.setObservables("CCMassSS");
  
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=0;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={60,120};
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

  // string autoBinFile="chargeFlip";
  // md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  
  bool mcStatSyst=true;
  string systSources="";

  bool uncDet=false;

  string Norm="";

  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=673; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  md.anConf.loadXSDB("XSectionsSpring15.db");
  //md.anConf.loadKFDB("kFactorsPhys14.db");
  

  map<string,float> LumisXS;

  //via XSect
  map<string,float> KFactors;
  

  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================
  // md.anConf.addSample( "WWTo2L2Nu_50ns",      "VV", kRed+1); 
  //md.anConf.addSample( "WZp8_50ns",           "VV", kRed+1); 
  // md.anConf.addSample( "ZZp8_50ns",           "VV", kRed+1); 
  // md.anConf.addSample( "TToLeptons_tch_50ns", "single-top", kViolet-3); 
  // md.anConf.addSample( "T_tWch_50ns",         "single-top", kViolet-3); 

  md.anConf.addSample( "TT_pow", "t#bar{t}", kMagenta+3); 
  // md.anConf.addSample( "WJetsToLNu_50ns", "W+jets", kOrange+7); 

  // md.anConf.addSample( "DYJetsToLL_M10to50_50ns", "Z/#gamma*", kOrange-2); 
  md.anConf.addSample( "DYJetsToLL_M50", "Z/#gamma*", kOrange-2); 

  // md.anConf.addSample( "DoubleEG_Run2015B_17Jul2015_runs_251244_251562", "data", kBlack);
  //md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_256630_257599", "data", kBlack);
   //md.anConf.addSample( "DoubleMuon_Run2015B_17Jul2015_runs_251244_251562", "data", kBlack);
  // md.anConf.addSample( "DoubleMuon_Run2015B_v1_runs_251643_251883", "data", kBlack);
  // md.anConf.addSample( "SingleElectron_Run2015B_17Jul2015_runs_251244_251562", "data", kBlack);
  // md.anConf.addSample( "SingleElectron_Run2015B_v1_runs_251643_251883", "data", kBlack);
  // md.anConf.addSample( "SingleMuon_Run2015B_17Jul2015_runs_251244_251562", "data", kBlack);
  // md.anConf.addSample( "SingleMuon_Run2015B_v1_runs_251643_251883", "data", kBlack);

   md.anConf.addSample( "DoubleEG_Run2015D_v3_run_256926", "data", kBlack);
   md.anConf.addSample( "DoubleEG_Run2015D_v3_runs_257600_258158", "data", kBlack);
   md.anConf.addSample( "DoubleEG_Run2015D_v4_runs_258159_258714", "data", kBlack);

  //md.anConf.addSample( "DoubleEG_Run2015D_256926_258714", "data", kBlack);

  // }
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
  
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
  //md.producePlots("chargeFlipControl800");
  md.doPlot();
  
  //md.makeSingleDataCard("sig", "global_SR1A", "weigthing", "test");
 

    //gROOT->ProcessLine(".q");

}
