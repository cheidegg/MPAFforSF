#include "analysis/src/TestSel.hh"

#include <algorithm>

TestSel::TestSel(std::string cfg){
  _verbose->Class("TestSel");
  
  startExecution(cfg);
  initialize();
}

TestSel::~TestSel(){
 
}

void TestSel::initialize(){

  _vc->registerVar("run"                          , "I" );
  _vc->registerVar("lumi"                         , "I" );
  _vc->registerVar("evt"                          , "I" );
  _vc->registerVar("nVert"                        , "I" );

  _vc->registerVar("minMllAFAS","D");
  _vc->registerVar("minMllAFOS","D");
  _vc->registerVar("mZ1","D");

  // _vc->registerVar("nJet25","I");
   _vc->registerVar("nBJetLoose25","I");
   _vc->registerVar("nBJetMedium25","I");
  // _vc->registerVar("nBJetTight25","I");
  // _vc->registerVar("nBJetCMVALoose25","I");
  // _vc->registerVar("nBJetCMVAMedium25","I");
  // _vc->registerVar("nBJetCMVATight25","I");
   _vc->registerVar("nJet40","I");
  // _vc->registerVar("nBJetLoose40","I");
   _vc->registerVar("nBJetMedium40","I");
  // _vc->registerVar("nBJetTight40","I");
  // _vc->registerVar("nBJetCMVALoose40","I");
  // _vc->registerVar("nBJetCMVAMedium40","I");
  // _vc->registerVar("nBJetCMVATight40","I");
  // _vc->registerVar("nLepGood20","I");
  // _vc->registerVar("nLepGood15","I");
   _vc->registerVar("nLepGood10","I");
  // _vc->registerVar("htJet25","D");
  // _vc->registerVar("mhtJet25","D");
   _vc->registerVar("htJet40j","D");
  // _vc->registerVar("htJet40ja","D");
  // _vc->registerVar("htJet40","D");
  // _vc->registerVar("htJet40a","D");
  // _vc->registerVar("mhtJet40","D");
  // _vc->registerVar("mhtJet40a","D");
  // _vc->registerVar("nSoftBLoose25","I");
  // _vc->registerVar("nSoftBMedium25","I");
  // _vc->registerVar("nSoftBTight25","I");

   _vc->registerVar("met_pt","D");
  // _vc->registerVar("met_eta","D");
  // _vc->registerVar("met_phi","D");
  // _vc->registerVar("met_mass","D");
  // _vc->registerVar("met_sumEt","D");
  // _vc->registerVar("met_genPt","D");
  // _vc->registerVar("met_genPhi","D");
  // _vc->registerVar("met_genEta","D");

  // _vc->registerVar("nFatJet","I");
  // _vc->registerVar("FatJet_id","AI");
  // _vc->registerVar("FatJet_puId","AI");
  // _vc->registerVar("FatJet_btagCSV","AD");
  // _vc->registerVar("FatJet_btagCMVA","AD");
  // _vc->registerVar("FatJet_rawPt","AD");
  // _vc->registerVar("FatJet_mcPt","AD");
  // _vc->registerVar("FatJet_mcFlavour","AI");
  // _vc->registerVar("FatJet_mcMatchId","AI");
  // _vc->registerVar("FatJet_pt","AD");
  // _vc->registerVar("FatJet_eta","AD");
  // _vc->registerVar("FatJet_phi","AD");
  // _vc->registerVar("FatJet_mass","AD");
  // _vc->registerVar("FatJet_prunedMass","AD");
  // _vc->registerVar("FatJet_trimmedMass","AD");
  // _vc->registerVar("FatJet_tau1","AD");
  // _vc->registerVar("FatJet_tau2","AD");
  // _vc->registerVar("FatJet_tau3","AD");

  // _vc->registerVar("nJetFwd","I");
  // _vc->registerVar("JetFwd_area","AD");
  // _vc->registerVar("JetFwd_qgl","AD");
  // _vc->registerVar("JetFwd_ptd","AD");
  // _vc->registerVar("JetFwd_axis2","AD");
  // _vc->registerVar("JetFwd_mult","AI");
  // _vc->registerVar("JetFwd_partonId","AI");
  // _vc->registerVar("JetFwd_partonMotherId","AI");
  // _vc->registerVar("JetFwd_id","AI");
  // _vc->registerVar("JetFwd_puId","AI");
  // _vc->registerVar("JetFwd_btagCSV","AD");
  // _vc->registerVar("JetFwd_btagCMVA","AD");
  // _vc->registerVar("JetFwd_rawPt","AD");
  // _vc->registerVar("JetFwd_mcPt","AD");
  // _vc->registerVar("JetFwd_mcFlavour","AI");
  // _vc->registerVar("JetFwd_mcMatchId","AI");
  // _vc->registerVar("JetFwd_pt","AD");
  // _vc->registerVar("JetFwd_eta","AD");
  // _vc->registerVar("JetFwd_phi","AD");
  // _vc->registerVar("JetFwd_mass","AD");
  // _vc->registerVar("JetFwd_mcMatchFlav","AI");

  _vc->registerVar("nGenPart","I");
  // _vc->registerVar("GenPart_motherId","AI");
  // _vc->registerVar("GenPart_grandmotherId","AI");
  // _vc->registerVar("GenPart_sourceId","AI");
  // _vc->registerVar("GenPart_charge","AD");
  // _vc->registerVar("GenPart_status","AI");
  _vc->registerVar("GenPart_pdgId","AI");
  _vc->registerVar("GenPart_pt","AD");
  _vc->registerVar("GenPart_eta","AD");
  _vc->registerVar("GenPart_phi","AD");
  // _vc->registerVar("GenPart_mass","AD");
  // _vc->registerVar("GenPart_motherIndex","AI");

  _vc->registerVar("nGenTop","I");
  // _vc->registerVar("GenTop_pdgId","AI");
  _vc->registerVar("GenTop_pt","AD");
  _vc->registerVar("GenTop_eta","AD");
  _vc->registerVar("GenTop_phi","AD");
  _vc->registerVar("GenTop_mass","AD");
  // _vc->registerVar("GenTop_charge","AD");
  // _vc->registerVar("GenTop_status","AI");

  // _vc->registerVar("nLepOther","I");
  // _vc->registerVar("LepOther_eleMVAId","AI");
  // _vc->registerVar("LepOther_mvaId","AD");
  // _vc->registerVar("LepOther_mvaIdTrig","AD");
  // _vc->registerVar("LepOther_mvaSusy","AD");
  // _vc->registerVar("LepOther_jetPtRatio","AD");
  // _vc->registerVar("LepOther_jetBTagCSV","AD");
  // _vc->registerVar("LepOther_jetBTagCMVA","AD");
  // _vc->registerVar("LepOther_jetDR","AD");
  // _vc->registerVar("LepOther_charge","AI");
  // _vc->registerVar("LepOther_tightId","AI");
  // _vc->registerVar("LepOther_eleCutIdCSA14_25ns_v1","AI");
  // _vc->registerVar("LepOther_eleCutIdCSA14_50ns_v1","AI");
  // _vc->registerVar("LepOther_dxy","AD");
  // _vc->registerVar("LepOther_dz","AD");
  // _vc->registerVar("LepOther_edxy","AD");
  // _vc->registerVar("LepOther_edz","AD");
  // _vc->registerVar("LepOther_ip3d","AD");
  // _vc->registerVar("LepOther_sip3d","AD");
  // _vc->registerVar("LepOther_convVeto","AI");
  // _vc->registerVar("LepOther_lostHits","AI");
  // _vc->registerVar("LepOther_relIso03","AD");
  // _vc->registerVar("LepOther_relIso04","AD");
  // _vc->registerVar("LepOther_tightCharge","AI");
  // _vc->registerVar("LepOther_mcMatchId","AI");
  // _vc->registerVar("LepOther_mcMatchAny","AI");
  // _vc->registerVar("LepOther_mcMatchTau","AI");
  // _vc->registerVar("LepOther_pdgId","AI");
  // _vc->registerVar("LepOther_pt","AD");
  // _vc->registerVar("LepOther_eta","AD");
  // _vc->registerVar("LepOther_phi","AD");
  // _vc->registerVar("LepOther_mass","AD");
  // _vc->registerVar("LepOther_chargedHadRelIso03","AD");
  // _vc->registerVar("LepOther_chargedHadRelIso04","AD");
  // _vc->registerVar("LepOther_softMuonId","AI");
  // _vc->registerVar("LepOther_pfMuonId","AI");
  // _vc->registerVar("LepOther_mediumMuonId","AI");
  // _vc->registerVar("LepOther_eleCutId2012_full5x5","AI");
  // _vc->registerVar("LepOther_trackerLayers","AI");
  // _vc->registerVar("LepOther_pixelLayers","AI");
  // _vc->registerVar("LepOther_trackerHits","AI");
  // _vc->registerVar("LepOther_lostOuterHits","AI");
  // _vc->registerVar("LepOther_innerTrackValidHitFraction","AD");
  // _vc->registerVar("LepOther_innerTrackChi2","AD");
  // _vc->registerVar("LepOther_nStations","AD");
  // _vc->registerVar("LepOther_caloCompatibility","AD");
  // _vc->registerVar("LepOther_globalTrackChi2","AD");
  // _vc->registerVar("LepOther_trkKink","AD");
  // _vc->registerVar("LepOther_segmentCompatibility","AD");
  // _vc->registerVar("LepOther_chi2LocalPosition","AD");
  // _vc->registerVar("LepOther_chi2LocalMomentum","AD");
  // _vc->registerVar("LepOther_glbTrackProbability","AD");
  // _vc->registerVar("LepOther_sigmaIEtaIEta","AD");
  // _vc->registerVar("LepOther_dEtaScTrkIn","AD");
  // _vc->registerVar("LepOther_dPhiScTrkIn","AD");
  // _vc->registerVar("LepOther_hadronicOverEm","AD");
  // _vc->registerVar("LepOther_eInvMinusPInv","AD");
  // _vc->registerVar("LepOther_hasSV","AI");
  // _vc->registerVar("LepOther_svRedPt","AD");
  // _vc->registerVar("LepOther_svRedM","AD");
  // _vc->registerVar("LepOther_svLepSip3d","AD");
  // _vc->registerVar("LepOther_svSip3d","AD");
  // _vc->registerVar("LepOther_svNTracks","AD");
  // _vc->registerVar("LepOther_svChi2n","AD");
  // _vc->registerVar("LepOther_svDxy","AD");
  // _vc->registerVar("LepOther_svMass","AD");
  // _vc->registerVar("LepOther_svPt","AD");
  // _vc->registerVar("LepOther_svMCMatchFraction","AD");
  // _vc->registerVar("LepOther_svMva","AD");

  _vc->registerVar("nLepGood","I");
  _vc->registerVar("LepGood_eleMVAId","AI");
  _vc->registerVar("LepGood_mvaId","AD");
  _vc->registerVar("LepGood_mvaIdTrig","AD");
  _vc->registerVar("LepGood_mvaSusy","AD");
  _vc->registerVar("LepGood_jetPtRatio","AD");
  _vc->registerVar("LepGood_jetBTagCSV","AD");
  _vc->registerVar("LepGood_jetBTagCMVA","AD");
  _vc->registerVar("LepGood_jetDR","AD");
  _vc->registerVar("LepGood_charge","AI");
  _vc->registerVar("LepGood_tightId","AI");
  // _vc->registerVar("LepGood_eleCutIdCSA14_25ns_v1","AI");
  // _vc->registerVar("LepGood_eleCutIdCSA14_50ns_v1","AI");
  // _vc->registerVar("LepGood_dxy","AD");
  // _vc->registerVar("LepGood_dz","AD");
  // _vc->registerVar("LepGood_edxy","AD");
  // _vc->registerVar("LepGood_edz","AD");
  // _vc->registerVar("LepGood_ip3d","AD");
   _vc->registerVar("LepGood_sip3d","AD");
   _vc->registerVar("LepGood_convVeto","AI");
   _vc->registerVar("LepGood_lostHits","AI");
  _vc->registerVar("LepGood_relIso03","AD");
  // _vc->registerVar("LepGood_relIso04","AD");
   _vc->registerVar("LepGood_tightCharge","AI");
  // _vc->registerVar("LepGood_mcMatchId","AI");
  // _vc->registerVar("LepGood_mcMatchAny","AI");
  // _vc->registerVar("LepGood_mcMatchTau","AI");
  _vc->registerVar("LepGood_pdgId","AI");
  _vc->registerVar("LepGood_pt","AD");
  _vc->registerVar("LepGood_eta","AD");
  _vc->registerVar("LepGood_phi","AD");
  _vc->registerVar("LepGood_mass","AD");
  // _vc->registerVar("LepGood_chargedHadRelIso03","AD");
  // _vc->registerVar("LepGood_chargedHadRelIso04","AD");
  // _vc->registerVar("LepGood_softMuonId","AI");
  // _vc->registerVar("LepGood_pfMuonId","AI");
  // _vc->registerVar("LepGood_mediumMuonId","AI");
  // _vc->registerVar("LepGood_eleCutId2012_full5x5","AI");
  // _vc->registerVar("LepGood_trackerLayers","AI");
  // _vc->registerVar("LepGood_pixelLayers","AI");
  // _vc->registerVar("LepGood_trackerHits","AI");
  // _vc->registerVar("LepGood_lostOuterHits","AI");
  // _vc->registerVar("LepGood_innerTrackValidHitFraction","AD");
  // _vc->registerVar("LepGood_innerTrackChi2","AD");
  // _vc->registerVar("LepGood_nStations","AD");
  // _vc->registerVar("LepGood_caloCompatibility","AD");
  // _vc->registerVar("LepGood_globalTrackChi2","AD");
  // _vc->registerVar("LepGood_trkKink","AD");
  // _vc->registerVar("LepGood_segmentCompatibility","AD");
  // _vc->registerVar("LepGood_chi2LocalPosition","AD");
  // _vc->registerVar("LepGood_chi2LocalMomentum","AD");
  // _vc->registerVar("LepGood_glbTrackProbability","AD");
  // _vc->registerVar("LepGood_sigmaIEtaIEta","AD");
  // _vc->registerVar("LepGood_dEtaScTrkIn","AD");
  // _vc->registerVar("LepGood_dPhiScTrkIn","AD");
  // _vc->registerVar("LepGood_hadronicOverEm","AD");
  // _vc->registerVar("LepGood_eInvMinusPInv","AD");
  // _vc->registerVar("LepGood_hasSV","AI");
  // _vc->registerVar("LepGood_svRedPt","AD");
  // _vc->registerVar("LepGood_svRedM","AD");
  // _vc->registerVar("LepGood_svLepSip3d","AD");
  // _vc->registerVar("LepGood_svSip3d","AD");
  // _vc->registerVar("LepGood_svNTracks","AD");
  // _vc->registerVar("LepGood_svChi2n","AD");
  // _vc->registerVar("LepGood_svDxy","AD");
  // _vc->registerVar("LepGood_svMass","AD");
  // _vc->registerVar("LepGood_svPt","AD");
  // _vc->registerVar("LepGood_svMCMatchFraction","AD");
  // _vc->registerVar("LepGood_svMva","AD");


  // _vc->registerVar("nGenDHad","I");
  // _vc->registerVar("GenDHad_charge","AD");
  // _vc->registerVar("GenDHad_status","AI");
  // _vc->registerVar("GenDHad_pdgId","AI");
  // _vc->registerVar("GenDHad_pt","AD");
  // _vc->registerVar("GenDHad_eta","AD");
  // _vc->registerVar("GenDHad_phi","AD");
  // _vc->registerVar("GenDHad_mass","AD");
  // _vc->registerVar("GenDHad_flav","AI");
  // _vc->registerVar("GenDHad_sourceId","AI");
  // _vc->registerVar("GenDHad_svMass","AD");
  // _vc->registerVar("GenDHad_svPt","AD");
  // _vc->registerVar("GenDHad_svCharge","AI");
  // _vc->registerVar("GenDHad_svNtracks","AI");
  // _vc->registerVar("GenDHad_svChi2","AD");
  // _vc->registerVar("GenDHad_svNdof","AD");
  // _vc->registerVar("GenDHad_svDxy","AD");
  // _vc->registerVar("GenDHad_svEdxy","AD");
  // _vc->registerVar("GenDHad_svIp3d","AD");
  // _vc->registerVar("GenDHad_svEip3d","AD");
  // _vc->registerVar("GenDHad_svSip3d","AD");
  // _vc->registerVar("GenDHad_svCosTheta","AD");
  // _vc->registerVar("GenDHad_svMva","AD");
  // _vc->registerVar("GenDHad_jetPt","AD");
  // _vc->registerVar("GenDHad_jetBTagCSV","AD");
  // _vc->registerVar("GenDHad_jetBTagCMVA","AD");

  // _vc->registerVar("nGenBHad","I");
  // _vc->registerVar("GenBHad_charge","AD");
  // _vc->registerVar("GenBHad_status","AI");
  // _vc->registerVar("GenBHad_pdgId","AI");
  // _vc->registerVar("GenBHad_pt","AD");
  // _vc->registerVar("GenBHad_eta","AD");
  // _vc->registerVar("GenBHad_phi","AD");
  // _vc->registerVar("GenBHad_mass","AD");
  // _vc->registerVar("GenBHad_flav","AI");
  // _vc->registerVar("GenBHad_sourceId","AI");
  // _vc->registerVar("GenBHad_svMass","AD");
  // _vc->registerVar("GenBHad_svPt","AD");
  // _vc->registerVar("GenBHad_svCharge","AI");
  // _vc->registerVar("GenBHad_svNtracks","AI");
  // _vc->registerVar("GenBHad_svChi2","AD");
  // _vc->registerVar("GenBHad_svNdof","AD");
  // _vc->registerVar("GenBHad_svDxy","AD");
  // _vc->registerVar("GenBHad_svEdxy","AD");
  // _vc->registerVar("GenBHad_svIp3d","AD");
  // _vc->registerVar("GenBHad_svEip3d","AD");
  // _vc->registerVar("GenBHad_svSip3d","AD");
  // _vc->registerVar("GenBHad_svCosTheta","AD");
  // _vc->registerVar("GenBHad_svMva","AD");
  // _vc->registerVar("GenBHad_jetPt","AD");
  // _vc->registerVar("GenBHad_jetBTagCSV","AD");
  // _vc->registerVar("GenBHad_jetBTagCMVA","AD");

  _vc->registerVar("nJet","I");
  // _vc->registerVar("Jet_area","AD");
  // _vc->registerVar("Jet_qgl","AD");
  // _vc->registerVar("Jet_ptd","AD");
  // _vc->registerVar("Jet_axis2","AD");
  // _vc->registerVar("Jet_mult","AI");
  // _vc->registerVar("Jet_partonId","AI");
  // _vc->registerVar("Jet_partonMotherId","AI");
  // _vc->registerVar("Jet_id","AI");
  // _vc->registerVar("Jet_puId","AI");
  _vc->registerVar("Jet_btagCSV","AD");
  // _vc->registerVar("Jet_btagCMVA","AD");
  // _vc->registerVar("Jet_rawPt","AD");
  // _vc->registerVar("Jet_mcPt","AD");
  // _vc->registerVar("Jet_mcFlavour","AI");
  // _vc->registerVar("Jet_mcMatchId","AI");
  _vc->registerVar("Jet_pt","AD");
  _vc->registerVar("Jet_eta","AD");
  _vc->registerVar("Jet_phi","AD");
  _vc->registerVar("Jet_mass","AD");
  // _vc->registerVar("Jet_mcMatchFlav","AI");


  //additional counter categories
  // _au->addCategory( kElId      , "el Id"      );
  // _au->addCategory( kElVeto    , "veto El"    );
  // _au->addCategory( kMuId      , "muon Id"    );
  // _au->addCategory( kMuVeto    , "veto Mu"    );
  // _au->addCategory( kJetId     , "jet Id"     );
  // _au->addCategory( kBJetId    , "b-jet Id"   );
  // _au->addCategory( kVetoLepSel, "vetoLepSel" );
 
  //extra input variables
  // _lepflav = getCfgVarS("LEPFLAV");
  // _mva     = getCfgVarS("LEPID"  );
  // _btag    = getCfgVarS("BTAG"   );
  // _PT      = getCfgVarS("PT"     );
  // _BR      = getCfgVarS("BR"     );
  // _SR      = getCfgVarS("SR"     );
 
  _vc->registerVar("iL1T","F");
  _vc->registerVar("iL2T","F");
  _vc->registerVar("iL1","F");
  _vc->registerVar("iL2","F");
  _vc->registerVar("minMllAFASTL","F");
  _vc->registerVar("minMllAFOSTL","F");
  _vc->registerVar("mZ1cut10TL","F");

}

void TestSel::loadInput(){

}

void TestSel::modifyWeight() {

}

void TestSel::modifySkimming(){

}


void TestSel::defineOutput(){

  string leps[2]={"l1","l2"};
  
  for(int il=0;il<2;il++) {

    _hm->addVariable(leps[il]+"Pt", 200, 0., 200.0,"p_{T}("+leps[il]+") [GeV]");
    _hm->addVariable(leps[il]+"Eta", 60, -3.0, 3.0,"#eta("+leps[il]+") ");
    _hm->addVariable(leps[il]+"Phi", 60, -3.1416, 3.1416,"#phi("+leps[il]+") ");

    _hm->addVariable(leps[il]+"RelIso", 200, 0., 1.,"I("+leps[il]+")/p_{T} ");
    _hm->addVariable(leps[il]+"Iso", 200, 0., 20.0,"I("+leps[il]+") [GeV]");

    
    _hm->addVariable(leps[il]+"DRFJet", 200, 0., 2.0,"#DeltaR("+leps[il]+",j_{F}) ");
    _hm->addVariable(leps[il]+"DRJet", 200, 0., 2.0,"#DeltaR("+leps[il]+",j) ");

  }

  _hm->addVariable("nFatJet", 11, -0.5, 10.5, "Fat jet multiplicity ");
  _hm->addVariable("nJet", 11, -0.5, 10.5, "Jet multiplicity ");

  _hm->addVariable("l1LSF", 200, -1, 1,"LSF(l1) ");
  _hm->addVariable("l2LSF", 200, -1, 1,"LSF(l2) ");

  _hm->addVariable("tau1", 200, 0., 1,"#tau_{1} ");
  _hm->addVariable("tau2", 200, 0., 1,"#tau_{2} ");
  _hm->addVariable("tau3", 200, 0., 1,"#tau_{3} ");

  _hm->addVariable("tau21", 200, 0., 1,"#tau_{2}/#tau_{1} ");
  _hm->addVariable("tau31", 200, 0., 1,"#tau_{3}/#tau_{1} ");
  _hm->addVariable("tau32", 200, 0., 1,"#tau_{3}/#tau_{2} ");

  _hm->addVariable("fjMass", 200, 0., 2000,"M_{fjet} [GeV]");
  _hm->addVariable("fjMassT", 200, 0., 2000,"M_{fjet}T [GeV]");
  _hm->addVariable("fjMassP", 200, 0., 2000,"M_{fjet}P [GeV]");

  _hm->addVariable("GenTopDR", 200, 0., 2.0,"#DeltaR(l,t) ");
  _hm->addVariable("GenTopPt", 200, 0., 1000,"p_{T}(t) [GeV]");
  _hm->addVariable("GenTopEta", 60, -3., 3,"#eta(t) ");
  _hm->addVariable("GenTopPhi", 60, -3.1416, 3.1416,"#phi(t) ");
  _hm->addVariable("GenTopMass", 200, 0., 400,"M_{t} [GeV]");

}

void TestSel::writeOutput(){
 
  _hm->saveHistos ("TestSel", _cfgName);
  _au->saveNumbers("TestSel", _cfgName);

}



void TestSel::run(){

  counter("denominator");
  
// LepGood1_(\w+) : LepGood_\1[iL1T]; AlsoData
// LepGood2_(\w+) : LepGood_\1[iL2T]; AlsoData
// \bmZ1\b: mZ1cut10TL
// minMllAFOS\b: minMllAFOSTL
// minMllAFAS\b: minMllAFASTL


  int idx1 = _vc ->getF("iL1T"); //0;
  int idx2 = _vc ->getF("iL2T"); //1;




// if(!makeCut( _vc ->getI("LepGood_tightId",0) > (std::abs(_vc->getI("LepGood_pdgId",0)) == 11) && 
//               _vc->getI("LepGood_tightId",1) > (std::abs(_vc->getI("LepGood_pdgId",1)) == 11) , "Id") ) return;
 if(!makeCut( _vc->getI("LepGood_tightId", 0) > (std::abs(_vc->getI("LepGood_pdgId",0)) == 11) && 
               _vc->getI("LepGood_tightId",1) > (std::abs(_vc->getI("LepGood_pdgId",1)) == 11), "new tight id", "=") ) return; 

 return;


  if(!makeCut( _vc ->getI("nLepGood10") >= 2, "NlepIni") ) return ;
  // if(!makeCut( _vc ->getD("minMllAFAS") > 8, "minMLLAFAS") ) return ;
  // if(!makeCut( _vc ->getD("minMllAFOS") <= 0 || _vc->getD("minMllAFOS") > 12, "minMLLAFOS") ) return ;
  // if(!makeCut( _vc ->getD("mZ1") < 76 || _vc->getD("mZ1") > 106, "mZl") ) return ;

  if(!makeCut( _vc ->getF("minMllAFASTL") > 8, "minMLLAFAS") ) return ;
  if(!makeCut( _vc ->getF("minMllAFOSTL") <= 0 || _vc->getF("minMllAFOSTL") > 12, "minMLLAFOS") ) return ;
  if(!makeCut( _vc ->getF("mZ1cut10TL") < 76 || _vc->getF("mZ1cut10TL") > 106, "mZl") ) return ;

  // if(!makeCut( _vc ->getI("nLepGood10") == 2, "Nlep") ) return ;
  if(!makeCut( std::abs(_vc->getI("LepGood_pdgId",idx1)) ==11 && std::abs(_vc->getI("LepGood_pdgId",idx2)) ==11, "lepodgId") ) return ;
  if(!makeCut( _vc ->getI("LepGood_charge",idx1)*_vc->getI("LepGood_charge",idx2) > 0, "lepcharge") ) return ;
  if(!makeCut( _vc ->getD("LepGood_pt",idx1) > 25, "pt1") ) return ;
  if(!makeCut( _vc ->getD("LepGood_pt",idx2) > 25, "pt2") ) return ;
  if(!makeCut(max(_vc->getD("LepGood_relIso03",idx1),_vc->getD("LepGood_relIso03",idx2)) < 0.1, "iso") ) return ;
  if(!makeCut( _vc ->getI("LepGood_tightId",idx1) > (std::abs(_vc->getI("LepGood_pdgId",idx1)) == 11) && _vc->getI("LepGood_tightId",idx2) > (std::abs(_vc->getI("LepGood_pdgId",idx2)) == 11) , "Id") ) return ;
  if(!makeCut( max(_vc->getD("LepGood_sip3d",idx1),_vc->getD("LepGood_sip3d",idx2)) < 4, "sip") ) return ;
  if(!makeCut(  (std::abs(_vc->getI("LepGood_pdgId",idx1)) == 13 || 
		 (_vc->getI("LepGood_convVeto",idx1) && _vc->getI("LepGood_lostHits",idx1) == 0 && _vc->getI("LepGood_tightCharge",idx1) > 1)) &&
		(std::abs(_vc->getI("LepGood_pdgId",idx2)) == 13 || 
		 (_vc->getI("LepGood_convVeto",idx2) && _vc->getI("LepGood_lostHits",idx2) == 0 && _vc->getI("LepGood_tightCharge",idx2) > 1)) , "pdgId DepId") ) return ;
  
  if(!makeCut( _vc ->getD("htJet40j") > 80 , "HT") ) return ;
  if(!makeCut( _vc ->getD("met_pt") > 30 || _vc->getD("htJet40j") > 500, "MET") ) return ;
  if(!makeCut( _vc ->getI("nJet40") >=2, "nJet") ) return ;
  if(!makeCut( _vc ->getI("nBJetMedium25") == 0, "nBjet") ) return ;


}


// void
// TestSel::fillObjLists() {
  
// }


int
TestSel::genMatchId(const Candidate* cand) {

  int nGenL = _vc->getI("nGenPart");
  for(int ig = 0; ig < nGenL; ++ig) {
    if(Tools::dR2(cand->eta(), _vc->getD("GenPart_eta", ig),
		  cand->phi(), _vc->getD("GenPart_phi", ig) ) < 0.0025 ) { //to be tuned
      return _vc->getI("GenPart_pdgId", ig);
    }
  }
  
  return -1000000;
}




bool
TestSel::nmu() {

  int nmu=0;

  int nGenL = _vc->getI("nGenPart");
  for(int ig = 0; ig < nGenL; ++ig) {
    if(std::abs(_vc->getI("GenPart_pdgId", ig))!=13) continue;
    
    nmu++;
  }

  return nmu==2;
}


bool
TestSel::acceptance() {

  bool full[2]={false,false};
  bool partial[2]={false,false};
  
  string leps[2]={"l1","l2"};
  int n=-1;

  int nGenL = _vc->getI("nGenPart");
  for(int ig = 0; ig < nGenL; ++ig) {
    if(std::abs(_vc->getI("GenPart_pdgId", ig))!=13) continue;
    n++;
    if(std::abs(_vc->getD("GenPart_eta", ig))>2.4) continue;
    
    fill(leps[n]+"Pt",_vc->getD("GenPart_pt", ig) , _weight);
    
    if(_vc->getD("GenPart_pt", ig)<20) continue;
    
    full[n]=true;

    if(std::abs(_vc->getD("GenPart_eta", ig))>0.9) continue;
    if(std::abs(_vc->getD("GenPart_pt", ig))>40 || std::abs(_vc->getD("GenPart_pt", ig))<30) continue;

    partial[n]=true;

  }

  // if(kill) return ;
  
  return(full[0] && partial[1]) || (full[1] && partial[0]);// full[0]&&full[1];//
}




bool 
TestSel::goodJetSelection(int jetIdx) {
  
  if(_vc->getD("Jet_pt", jetIdx)<40.0) return false;
  if(fabs(_vc->getD("Jet_eta", jetIdx))>  2.4) return false;

  for(int ie=0; ie<_nEls; ++ie) {
    float dr2 = KineUtils::dR2(_els[ie]->eta(),_vc->getD("Jet_eta", jetIdx),
			      _els[ie]->phi(),_vc->getD("Jet_phi", jetIdx));
    if(dr2<0.0025) return false;
  }

  for(int im=0; im<_nMus; ++im){
    float dr2 = KineUtils::dR2(_mus[im]->eta(),_vc->getD("Jet_eta", jetIdx),
			      _mus[im]->phi(),_vc->getD("Jet_phi", jetIdx)); 
    if(dr2<0.0025) return false;
  }

  return true;
}


bool 
TestSel::bJetSelection(int jetIdx) {
 
  if(!goodJetSelection(jetIdx) ) return false;
  if(_vc->getD("Jet_btagCSV", jetIdx)< 0.679) return false;

  return true;
}

int 
TestSel::eventCharge(){
  
  int charge = 0;

  for(int i=0;i<_nEls;++i)
    charge += _els[i]->charge();

  for(int i=0;i<_nMus;++i)
    charge += _mus[i]->charge();

  return charge; 
}


Candidate*
TestSel::closestObj(const Candidate* ref, 
			const CandList objs, int& idx) {

  Candidate* bestCand=nullptr;
  float tmpDR2 = 10000;
  int nObjs = objs.size();
  for(int i=0;i<nObjs;i++) {
    float dR2 = KineUtils::dR2(ref->eta(), objs[i]->eta(),
			       ref->phi(), objs[i]->phi() );
    if(dR2<tmpDR2) { 
      tmpDR2 = dR2; //objs[i]->pt();//
      bestCand = objs[i];
      idx = i;
    }
  }

  return bestCand;
}



Candidate*
TestSel::matchSubJetLep(const Candidate* ref, 
			    const CandList fatJets,
			    const CandList jets) {

  Candidate* tmp(nullptr);
  float tmpDR2 = 10000;
  int nFJets = fatJets.size();
  int nJets = jets.size();

  for(int i=0;i<nFJets;i++) {

    float dR2 = fatJets[i]->dR(ref);
    //cout<<" =>  "<<dR2<<endl;
    if(dR2<0.8) {  //matched 
      //cout<<" ============== matched === "<<endl;
      //CandList subjets; //find subjets
      for(int j=0;j<nJets;j++) {
	float dR2j = fatJets[i]->dR(jets[j]);
	//cout<<" --->  "<<dR2j<<endl;
	if(dR2j<0.4) {
	  //cout<<" ======== jet matched === "<<endl;
	  float dR2l = jets[j]->dR(ref);
	  //cout<<" >>  "<<dR2l<<"  "<<tmpDR2<<endl;
	  if(tmpDR2>dR2l && dR2l<0.4) {
	    // cout<<" ==== jet-lep matched === "<<ref->pt()<<"   "<<jets[j]->pt()<<endl;
	    tmpDR2 = dR2l;
	    tmp = jets[j];
	  }
	}
      }
      
    }
    break;
  }

  return tmp;
}
