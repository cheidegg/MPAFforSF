{
  if(Recompute) {
    MPAFDisplay md;
 
    //Bloody René Brun
    bool * rtmp= const_cast<bool*> pr;
    *rtmp = false;

  }
  else md.refresh();


  //general parameters ********************* general parameters
  string dir="SSDLBoosted";
  string fileName="ssdlboosted"; //was treeName in LUNE susy_cut_lowpt
  string fileList="ssdlboosted"; //CH: since AnaConfig needs a fileName to open, we need to put the data files into a different variable
  string hName="";

  bool mcOnly = false;
  
  //if(md.isInitStatus()) {
  md.anConf.configureNames( dir, fileName, fileList, hName );
  md.anConf.configureData(false, 0, mcOnly);
  //}
  
  //observables **********************
  //string obs[6]={"","","","","",""};
  md.dp.setObservables("GenTopPt");
    
  //Binning & title ************************* Binning & titre
  string yTitle="number of events";
  int binning=10;
  int addBinBkg=1; //BinB = binning*AddBin
  double rangeY[2]={0,0};
  double rangeX[2]={0.,1000};
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

  // string autoBinFile="susybinninghigh";
  // md.dp.loadAutoBinning(autoBinFile);

  //Systematic uncertainties ********************************
  bool addSystematics=false;
  
  bool mcStatSyst=true;
  string systSources="";

  bool uncDet=false;

  string Norm="norm";
  
  //Lumis( or XSections ) pb-1 & KFactors ************************************
  float lumi=10000; //pb-1 19470
  float energy=13; //TeV

  bool useXS=false;

  map<string,float> LumisXS;
    
  // LumisXS[ "SMS_T1tttt_2J_mGl1200_mLSP800"] =      100322 / (0.0856418 *20) ;
  // LumisXS[ "SMS_T1tttt_2J_mGl1500_mLSP100_PU_S14_POSTLS170_skim"] =      105679 / (0.0141903 *20) ;
  // LumisXS[ "T1tttt_2J_mGo1300_mStop300_mCh285_mChi280_pythia8_S14_skim"] =      35288 / (0.0460525 *20);
  // LumisXS[ "T1tttt_2J_mGo1300_mStop300_mChi280_pythia8_S14_skim"] =      16360 / (0.0460525 *20);
  // LumisXS[ "T1tttt_2J_mGo800_mStop300_mCh285_mChi280_pythia8_S14_skim"] =      30344 / (1.4891* 5);
  // LumisXS[ "T1tttt_2J_mGo800_mStop300_mChi280_pythia8_S14_skim"] =      23343 / (1.4891* 5);
  // LumisXS[ "T5Full_1200_1000_800_skim"] =       121497 / (0.0856418 *20);
  // LumisXS[ "T5Full_1500_800_100_skim"] =       127139 / (0.0141903 *20) ;

  //via XSect
  
  map<string,float> KFactors;
     // if( md.isInitStatus() )
  md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );

  //===============================================================
  // SDYJetsM50_HT600toInf_PU_S14_POSTLS170_skimamples **************************  samples
  //if( md.isInitStatus() ) {

  //md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800_PU_S14_POSTLS170_skim"                     ,  "T1tttt(HL)*20 sig", kViolet-3  );
  // md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100_PU_S14_POSTLS170_skim"                     ,  "T1tttt(HM)*20 sig", kGreen+2  );
  // // //md.anConf.addSample( "T1tttt_2J_mGo1300_mStop300_mChi280_pythia8_S14_skim" , "T1tttt(HM) sig",  kViolet-3  );
  //md.anConf.addSample( "T1tttt_2J_mGo800_mStop300_mCh285_mChi280_pythia8_S14_skim", "T1tttt(8/3/2.85)*5 comp sig", kRed+1 );
  // // //md.anConf.addSample( "T5Full_1500_800_100_skim"                             ,  "T5WW(HL)*20 sig"  , kRed+1  );
  // md.anConf.addSample( "T5Full_1200_1000_800_skim"                            ,  "T5WW(HM)*20 sig"  , kOrange+6  );
   
  md.anConf.addSample( "TTJets",    "t#bar{t}", kBlack);
  md.anConf.addSample( "TTWJets",    "t#bar{t}W", kGray+1);
  md.anConf.addSample( "TTZJets",    "t#bar{t}Z", kGray);
 // md.anConf.addSample( "T_tWch",    "tW", kGray);
 // md.anConf.addSample( "Tbar_tWch",    "tW", kGray);


  md.anConf.addSample( "SMS_T1tttt_2J_mGl1200_mLSP800",    "T1tttt(1.2/0.8)", kOrange+6);
  md.anConf.addSample( "SMS_T1tttt_2J_mGl1500_mLSP100",    "T1tttt(1.2/0.1)", kRed+1);
  md.anConf.addSample( "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280",    "T5tttt(1.0)", kBlue+1);
  md.anConf.addSample( "T5ttttDeg_mGo1300_mStop300_mCh285_mChi280",    "T5tttt(1.3)", kGreen+2);


  // }
  //===============================================================

  //*********************************************************************²
  //Execution macro ******************************************************
 
  //Configuration ================
  //if( md.isInitStatus() ) {
  
  //md.anConf.configureLumi( LumisXS, KFactors, lumi, useXS );
   
  // }

  //plotting ================
  md.dp.setLumiAndEnergy( lumi, energy );
  md.dp.setNormalization( Norm );
  md.dp.configureDisplay(yTitle, rangeY, rangeX, logYScale, xDiv,
			 yDiv, binning, addBinBkg, overFlowBin,
			 underFlowBin, showDMCRatio, showGrid, 
			 stacking, addSystematics, mcStatSyst,
			 markerSize, lineWidth,summedSignal, 
			 mcOnly,cmsPrel, uncDet);

  md.doPlot();
  //md.doStatisticsPlot();
  //md.savePlot("SSDLBoosted_dev");
  // md.dp.addText(xt,yt,st,addText);

}
