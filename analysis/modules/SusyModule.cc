#include "analysis/modules/SusyModule.hh"


SusyModule::SusyModule(VarClass* vc):
  _vc(vc),_dbm(nullptr)
{
  defineLeptonWPS();
  
}

SusyModule::SusyModule(VarClass* vc, DataBaseManager* dbm):
  _vc(vc), _dbm(dbm)
{
  defineLeptonWPS();
  loadDBs();
}

SusyModule::~SusyModule() {

  delete _vc;
}

void
SusyModule::loadDBs() {

  //_dbm->loadDb("PileupWeights.root",""); -> done with trees

  //HLT scale factors
  _dbm->loadDb("hltDEG","hltSFDoubleEG.db");
  _dbm->loadDb("hltDMu","hltSFDoubleMu.db");
  _dbm->loadDb("hltSEle","hltSFSingleEle.db");
  _dbm->loadDb("hltSMu","hltSFSingleMu.db");
  
  //lepton scale factors
  _dbm->loadDb("eleSFDb","electronSF.db");
  _dbm->loadDb("muSFDb","muonSF.db");
  _dbm->loadDb("tauSFDb","tauSF.db");

 
  _dbm->loadDb("BTagEffUSDG", "GC_BTagEffs.root", (string)("h2_BTaggingEff_csv_med_Eff_udsg") );
  _dbm->loadDb("BTagEffCB", "GC_BTagEffs.root", (string)("h2_BTaggingEff_csv_med_Eff_b")   );
  cout<<" pouet "<<endl; 
  _dbm->loadDb("BTagSF", "BTagSFMedium.db");
  cout<<" pouet "<<endl;
}

void
SusyModule::defineLeptonWPS() {

  _cLostHitWP.resize(kNWPs);
  _tChWP.resize(kNWPs);
  _sipWP.resize(kNWPs);
  _muIdWP.resize(kNWPs);
  _dxyWP.resize(kNWPs);
  _dzWP.resize(kNWPs);
  _elMvaIdWP.resize(3);
  _multiIsoWP.resize(3);
  _ptWP.resize(2);

  for(int i=0;i<3;++i) {
    _elMvaIdWP[i].resize(kNWPs);
    _multiIsoWP[i].resize(kNWPs);
    if(i!=2) _ptWP[i].resize(kNWPs);
  }
  
  //muId
  _muIdWP[kDenom] = 0; 
  _muIdWP[kLoose] = 0;//1000. 
  _muIdWP[kTight] = 1; 
  

  //conv rej ====================
  _cLostHitWP[kDenom] = 1; 
  _cLostHitWP[kLoose] = 1; 
  _cLostHitWP[kTight] = 0; 

  //pt ============================
  _ptWP[kEl][kDenom] = 7 ; _ptWP[kMu][kDenom] = 5 ;
  _ptWP[kEl][kLoose] = 7 ; _ptWP[kMu][kLoose] = 5 ;
  _ptWP[kEl][kTight] = 15; _ptWP[kMu][kTight] = 10;

  //sip & IP ======================
  _sipWP[kDenom] = 4.0; 
  _sipWP[kLoose] = 1000.0;//1000. 
  _sipWP[kTight] = 4.0; 
  
  _dxyWP[kDenom] = 0.05; //cm
  _dxyWP[kLoose] = 0.05; //cm
  _dxyWP[kTight] = 0.05; //cm
  
  _dzWP[kDenom] = 0.1; //cm
  _dzWP[kLoose] = 0.1; //cm
  _dzWP[kTight] = 0.1; //cm

  //ithgt charge
  _tChWP[kLoose]=-1;
  _tChWP[kTight]=1;

  //el mva id ======================
  //Phys14 50ns?
  // _elMvaIdWP[kEBC][kLoose] = -0.11;
  // _elMvaIdWP[kEBF][kLoose] = -0.35;
  // _elMvaIdWP[kEE ][kLoose] = -0.55;

  // _elMvaIdWP[kEBC][kTight] = 0.73;
  // _elMvaIdWP[kEBF][kTight] = 0.57;
  // _elMvaIdWP[kEE ][kTight] = 0.05;

  _elMvaIdWP[kEBC][kLoose] = -0.70;
  _elMvaIdWP[kEBF][kLoose] = -0.83;
  _elMvaIdWP[kEE ][kLoose] = -0.92;

  _elMvaIdWP[kEBC][kLooseHT] = -0.155;
  _elMvaIdWP[kEBF][kLooseHT] = -0.56;
  _elMvaIdWP[kEE ][kLooseHT] = -0.76;

  _elMvaIdWP[kEBC][kTight] = 0.87;
  _elMvaIdWP[kEBF][kTight] = 0.60;
  _elMvaIdWP[kEE ][kTight] = 0.17;

  //multiIso =======================
  _multiIsoWP[kMiniIso][kDenom]      = 0.4 ; _multiIsoWP[kPtRatio][kDenom]      = 0   ; _multiIsoWP[kPtRel][kDenom]      = 0  ;
  _multiIsoWP[kMiniIso][kVLoose]     = 0.25; _multiIsoWP[kPtRatio][kVLoose]     = 0.67; _multiIsoWP[kPtRel][kVLoose]     = 6.0;
  _multiIsoWP[kMiniIso][kLoose]      = 0.20; _multiIsoWP[kPtRatio][kLoose]      = 0.69; _multiIsoWP[kPtRel][kLoose]      = 6.0;
  _multiIsoWP[kMiniIso][kMedium]     = 0.16; _multiIsoWP[kPtRatio][kMedium]     = 0.76; _multiIsoWP[kPtRel][kMedium]     = 7.2; 
  _multiIsoWP[kMiniIso][kTight]      = 0.12; _multiIsoWP[kPtRatio][kTight]      = 0.80; _multiIsoWP[kPtRel][kTight]      = 7.2;
  _multiIsoWP[kMiniIso][kVTight]     = 0.09; _multiIsoWP[kPtRatio][kVTight]     = 0.84; _multiIsoWP[kPtRel][kVTight]     = 7.2;

  _multiIsoWP[kMiniIso][kSpecFakeEl] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeEl] = 0.80; _multiIsoWP[kPtRel][kSpecFakeEl] = 7.2;
  _multiIsoWP[kMiniIso][kSpecFakeMu] = 0.4 ; _multiIsoWP[kPtRatio][kSpecFakeMu] = 0.76; _multiIsoWP[kPtRel][kSpecFakeMu] = 7.2;
}


//=====================================================
// lepton selection

bool
SusyModule::multiIsoSel(int idx, int wp) const {
  if( _vc->get("LepGood_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
      (_vc->get("LepGood_jetPtRatiov2", idx)>_multiIsoWP[kPtRatio][wp] ||
       _vc->get("LepGood_jetPtRelv2", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}


bool
SusyModule::multiIsoSelCone(int idx, int wp) const {

  if( _vc->get("LepGood_miniRelIso", idx)<_multiIsoWP[kMiniIso][wp] &&
	(conePt(idx, wp)*_vc->get("LepGood_pt",idx) *_vc->get("LepGood_jetPtRatiov2", idx)>_multiIsoWP[kPtRatio][wp] ||
	 _vc->get("LepGood_jetPtRelv2", idx)>_multiIsoWP[kPtRel][wp]) ) return true;
  
  return false;
}

bool
SusyModule::invMultiIsoSel(int idx, int wp) const {
  
  if( _vc->get("LepGood_miniRelIso", idx)>_multiIsoWP[kMiniIso][wp]) return false;
  if( 1./_vc->get("LepGood_jetPtRelv2", idx) > (1/_multiIsoWP[kPtRel][wp] + _vc->get("LepGood_miniRelIso", idx)) ) return false;
  
  return true;
}

bool 
SusyModule::elMvaSel(int idx, int wp) const {

  int etaBin=-1;

  if     (std::abs(_vc->get("LepGood_eta", idx)) < 0.8  ) etaBin=0;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 1.479) etaBin=1;
  else if(std::abs(_vc->get("LepGood_eta", idx)) < 2.5  ) etaBin=2;

  if(_vc->get("LepGood_mvaIdSpring15", idx) <  _elMvaIdWP[etaBin][wp]  ) return false;
    
  return true;
}



bool
SusyModule::muIdSel(const Candidate*c, int idx, int wp, bool chCut) const {

  int wpIso = kDenom;
  // if(         _vc->get("LepGood_pt"          , idx)  < _ptWP[kMu][wp]) return false; //cout<<" pt"<<endl;
  //if(   c->pt()  < _ptWP[kMu][wp]) return false; //cout<<" pt"<<endl;
  //if(std::abs(_vc->get("LepGood_eta"         , idx)) >  2.4          ) return false;//cout<<" eta"<<endl;
  if(std::abs(c->eta() ) >  2.4          ) return false;//cout<<" eta"<<endl;
  if(         _vc->get("LepGood_mediumMuonId", idx)  < _muIdWP[wp]   ) return false;//cout<<" id"<<endl;
  if( chCut && _vc->get("LepGood_tightCharge" , idx)  <= 1 ) return false;//cout<<" tc"<<endl;
  if(         _vc->get("LepGood_sip3d"       , idx)  > _sipWP[wp]    ) return false;//cout<<" sip"<<endl;
  if(std::abs(_vc->get("LepGood_dz"          , idx)) > _dzWP[wp]     ) return false;//cout<<" dz"<<endl;
  if(std::abs(_vc->get("LepGood_dxy"         , idx)) > _dxyWP[wp]    ) return false;//cout<<" dxy"<<endl;
  if(!multiIsoSel(idx, wpIso )               ) return false;//cout<<" iso"<<endl;
  //cout<<" youpi ID "<<idx<<endl;
  return true;

}


bool
SusyModule::elIdSel(const Candidate* c, int idx, int wp, int mvaWp, bool chCut) const {

  int wpIso=kDenom;
  //  cout<<" starting "<< _vc->get("LepGood_pt",idx)<<"   "<<conePt(idx)<<endl;
  //if(_vc->get("LepGood_pt"         , idx)  < _ptWP[kEl][wp] ) return false; //cout<<" pt "<<endl;
  //if( c->pt()  < _ptWP[kEl][wp] ) return false; //cout<<" pt "<<endl;
  if(std::abs(_vc->get("LepGood_eta"        , idx)) > 2.5            ) return false; 
  // if(std::abs(_vc->get("LepGood_eta"        , idx)) > 1.4442 &&
  //    std::abs(_vc->get("LepGood_eta"        , idx)) < 1.566          ) return false;
  // cout<<" eta "<<endl;

  if(_vc->get("LepGood_convVeto", idx)  != 1             ) return false;//cout<<" conv "<<endl;
  if(_vc->get("LepGood_lostHits", idx)  > _cLostHitWP[wp]) return false;//cout<<" losthit "<<endl;

  if(chCut && _vc->get("LepGood_tightCharge", idx)  <= _tChWP[wp]    ) return false;//cout<<" charge "<<_tChWP[wp]<<endl;

  if(_vc->get("LepGood_sip3d"      , idx)  > _sipWP[wp]     ) return false;//cout<<" sip "<<endl;
  if(std::abs(_vc->get("LepGood_dz", idx)) > _dzWP[wp]      ) return false;//cout<<" dz "<<endl;
  if(std::abs(_vc->get("LepGood_dxy", idx)) > _dxyWP[wp]     ) return false;//cout<<" dx "<<endl;
  if(!elMvaSel(idx, mvaWp)                                           ) return false;//cout<<" mvaId "<<endl;
  if(!multiIsoSel(idx, wpIso)        ) return false;//cout<<" iso "<<endl;

  //cout<<idx<<"   iso+sip"<<endl;

  // electron cleaning ==================
  // for(unsigned int il=0; il<_vc->get("nLepGood"); ++il){
  //   float dr = KineUtils::dR(_vc->get("LepGood_eta", il), _vc->get("LepGood_eta", idx),
  //                            _vc->get("LepGood_phi", il), _vc->get("LepGood_phi", idx));
  //   if(std::abs(_vc->get("LepGood_pdgId"))==13 && dr<0.05 ) return false;
  // }
  //cout<<idx<<"   clean"<<endl;
  return true;
}

bool
SusyModule::elHLTEmulSel(int idx, bool withIso) const {

  if(std::abs(_vc->get("LepGood_eta",idx))<1.479) {
    if(_vc->get("LepGood_sigmaIEtaIEta",idx) > 0.011 ) return false;
    if(std::abs(_vc->get("LepGood_dEtaScTrkIn",idx)) > 0.01 ) return false;
    if(std::abs(_vc->get("LepGood_dPhiScTrkIn",idx)) > 0.04 ) return false;
    if(_vc->get("LepGood_hadronicOverEm",idx) > 0.08 ) return false;
    if(std::abs(_vc->get("LepGood_eInvMinusPInv",idx)) > 0.01 ) return false;
  }
  else {
    if(_vc->get("LepGood_sigmaIEtaIEta",idx) > 0.031 ) return false;
    if(std::abs(_vc->get("LepGood_dEtaScTrkIn",idx)) > 0.01 ) return false;
    if(std::abs(_vc->get("LepGood_dPhiScTrkIn",idx)) > 0.08 ) return false;
    if(_vc->get("LepGood_hadronicOverEm",idx) > 0.08 ) return false;
    if(std::abs(_vc->get("LepGood_eInvMinusPInv",idx)) > 0.01 ) return false;
  }
  
  if(withIso) {
    if(_vc->get("LepGood_ecalPFClusterIso",idx) > 0.45*_vc->get("LepGood_pt",idx) ) return false;
    if(_vc->get("LepGood_hcalPFClusterIso",idx) > 0.25*_vc->get("LepGood_pt",idx) ) return false;
    if(_vc->get("LepGood_dr03TkSumPt",idx) > 0.2*_vc->get("LepGood_pt",idx) ) return false;
  }

  return true;
}


//===========================================================
bool
SusyModule::jetSel( int jetIdx) const {
  
  if(_vc->get("Jet_pt", jetIdx)<40.0) return false;
  return true;
}

float 
SusyModule::HT(const CandList* jets){
  float ht = 0;
  unsigned int nJets=jets->size();
  for(unsigned int i=0; i<nJets; ++i) 
    ht += jets->at(i)->pt();
  
  return ht;
}


//=============================================================
bool
SusyModule::mllVetoSelection(const Candidate* l1, const Candidate* l2,
			     const CandList* allLeps) const {
  
  for(unsigned int i = 0; i < allLeps->size(); ++i) {
    if(l1!=allLeps->at(i) && mllZVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllZVeto(l2, allLeps->at(i))) return false;
    if(l1!=allLeps->at(i) && mllLMGVeto(l1, allLeps->at(i))) return false;
    if(l2!=allLeps->at(i) && mllLMGVeto(l2, allLeps->at(i))) return false;
  }
  
  return true;
}

bool 
SusyModule::mllLMGVeto(const Candidate* cand, const Candidate* veto) const {
  
  float mll = Candidate::create(cand, veto)->mass();

  if(mll <= 8.0) return true;
  if(cand->charge()==veto->charge() ) return false;
  if(mll <= 12.0) return true;

  return false;
}


bool 
SusyModule::mllZVeto(const Candidate* cand, const Candidate* veto) const {
 
  if(veto->pt() < 10) return false;
  float mll = Candidate::create(cand, veto)->mass();
  
  if(cand->charge()==veto->charge() ) return false;
  if(std::abs(cand->pdgId())==std::abs(veto->pdgId()) ) {
    if(mll >= 76.0 && mll <= 106.0) return true;
  }

  return false;
}


bool
SusyModule::passMllSingleVeto(const Candidate* c1, const Candidate* c2, 
			      float mllm, float mllM, bool ossf) {

  // cout<<"Id "<<c1->pdgId()<<"  "<<c2->pdgId()<<"  "<< Candidate::create(c1,c2)->mass()<<"  "<<mllm<<"  "<<mllM<<endl;
  if( (c1->pdgId()== -c2->pdgId()) || !ossf) {
    //cout<<" ==> aqui "<<c2->uid()<<"   "<<c1->uid()<<endl;
    
    float mll = Candidate::create(c1,c2)->mass();
    //cout<<" ==> aqui! "<<endl;
    if(mll>mllm && mll<mllM) return false; 
  }
  return true;
}


bool
SusyModule::passMllMultiVeto(const Candidate* c1, const CandList* cands, 
			     float mllm, float mllM, bool ossf) {

  for(size_t il=0;il<cands->size();il++) {
    if( c1==cands->at(il) ) continue;
    //cout<<" passng veto? "<<passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)<<endl;
    if(!passMllSingleVeto(c1, cands->at(il), mllm, mllM, ossf)) return false;
  }
  return true;
}

CandList
SusyModule::bestSSPair(const CandList* leps, bool byflav,
		       bool bypassMV, bool os, 
		       float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

//HACK: replaced nullptr with NULL
  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;
  
  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      
      if(!passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false) && !bypassMV) continue;
      
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
      
      int flav= (byflav?(std::abs(leps->at(il1)->pdgId()) + std::abs(leps->at(il2)->pdgId())):0);
      int st=leps->at(il1)->pt()+leps->at(il2)->pt();

      if(flav<tmpFlav) continue;
      
      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;
      
      tmpSt=st;
      clist[0]=leps->at(il1);
      clist[1]=leps->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1

  return clist;
}

CandList
SusyModule::bestSSPair(const CandList* leps1, const CandList* leps2, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl,
		       int& idx1, int& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  //HACK: replaced nullptr with NULL
  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;

  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(leps1->at(il1), leps2->at(il2), 0, 8, false) && !bypassMV) continue;

      if( (leps1->at(il1)->charge()!=leps2->at(il2)->charge())!=os ) continue;
      int flav= (byflav?(std::abs(leps1->at(il1)->pdgId()) + std::abs(leps2->at(il2)->pdgId())):0);
      int st=leps1->at(il1)->pt()+leps2->at(il2)->pt();

      if(flav<tmpFlav) continue;
      if(flav>tmpFlav) tmpSt=0;
      tmpFlav=flav;
      if(st<tmpSt) continue;

      tmpSt=st;
      clist[0]=leps1->at(il1);
      clist[1]=leps2->at(il2);
      idx1 = il1;
      idx2 = il2;
    
    }//il2
  }//il1
  return clist;
}


CandList
SusyModule::bestSSPair(Candidate* c1, const CandList* leps, bool byflav,
		       bool bypassMV, bool os, float pTthrMu, float pTthrEl, 
		       int& idx1, int& idx2) {

  CandList clist(2,NULL);
  int tmpFlav=0;
  int tmpSt=0;

  idx1=0;
  idx2=1;
 
  float pTthr1,pTthr2;

  for(unsigned int il=0;il<leps->size();il++) {
      
    pTthr1 = (std::abs(c1->pdgId())==11)?pTthrEl:pTthrMu;
    pTthr2 = (std::abs(leps->at(il)->pdgId())==11)?pTthrEl:pTthrMu;

    //conditional pt threshold, could evolve in CERN code 
    if(c1->pt()<pTthr1 || leps->at(il)->pt()<pTthr2) continue; 

    if(!passMllSingleVeto(c1, leps->at(il), 0, 8, false) && !bypassMV) continue;

    if((c1->charge()!=leps->at(il)->charge())!=os) continue;

    int flav= (byflav?(std::abs(c1->pdgId()) + std::abs(leps->at(il)->pdgId())):0);
    int st=c1->pt()+leps->at(il)->pt();

    if(flav<tmpFlav) continue;

    if(flav>tmpFlav) tmpSt=0;
    tmpFlav=flav;
    if(st<tmpSt) continue;

    tmpSt=st;
    clist[0]=c1;
    clist[1]=leps->at(il);
    idx1 = 0;
    idx2 = il;
    
  }//il

  return clist;
}



vector<CandList>
SusyModule::buildSSPairs(const CandList* leps, vector<unsigned int> idxs,
			 bool byflav, bool bypassMV, bool os, 
			 float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  vector<CandList> clist;
  float pTthr1,pTthr2;

  for(unsigned int il1=0;il1<leps->size()-1;il1++) {
    for(unsigned int il2=il1+1;il2<leps->size();il2++) {
      pTthr1 = (std::abs(leps->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      // cout<<il1<<"   "<<il2<<"    "<<leps->at(il1)->pt()<<"   "<<leps->at(il2)->pt()<<"   "<<passMllSingleVeto(leps->at(il1), leps->at(il2), 0, 8, false)
      // 	  <<" ->   "<<(leps->at(il1)->charge()!=leps->at(il2)->charge())<<endl;
      bool isMu=std::abs(_vc->get("LepGood_pdgId",idxs[il1]))==13;
      Candidate* c1=Candidate::create(_vc->get("LepGood_pt",idxs[il1]),
				      _vc->get("LepGood_eta",idxs[il1]),
				      _vc->get("LepGood_phi",idxs[il1]),
				      _vc->get("LepGood_pdgId",idxs[il1]),
				      _vc->get("LepGood_charge",idxs[il1]),
				      isMu?0.105:0.005 );

      isMu=std::abs(_vc->get("LepGood_pdgId",idxs[il2]))==13;
      Candidate* c2=Candidate::create(_vc->get("LepGood_pt",idxs[il2]),
				      _vc->get("LepGood_eta",idxs[il2]),
				      _vc->get("LepGood_phi",idxs[il2]),
				      _vc->get("LepGood_pdgId",idxs[il2]),
				      _vc->get("LepGood_charge",idxs[il2]),
				      isMu?0.105:0.005 );


      //conditional pt threshold, could evolve in CERN code 
      if(leps->at(il1)->pt()<pTthr1 || leps->at(il2)->pt()<pTthr2) continue; 
      //cout<<" cands => "<<leps->at(il2)->uid()<<endl;
      if(!passMllSingleVeto(c1, c2, 0, 8, false) && !bypassMV) continue;
      
      if( (leps->at(il1)->charge()!=leps->at(il2)->charge())!=os ) continue;
    
      CandList tmp(2,NULL);
     
      tmp[0]=leps->at(il1);
      tmp[1]=leps->at(il2);

      clist.push_back(tmp);

      idx1.push_back(il1);
      idx2.push_back(il2);
      
    }//il2
  }//il1

  return clist;
}


vector<CandList>
SusyModule::buildSSPairs(const CandList* leps1, const CandList* leps2, 
			 vector<unsigned int> idxs1,
			 vector<unsigned int> idxs2,
			 bool byflav,
			 bool bypassMV, bool os, float pTthrMu, float pTthrEl,
			 vector<int>& idx1, vector<int>& idx2) {

  //LISTS HAVE TO BE COMPLEMENTARY, NO OVERLAPS!

  vector<CandList> clist;
  float pTthr1,pTthr2;

  vector<InternalCList> iCList;

  for(unsigned int il1=0;il1<leps1->size();il1++) {
    for(unsigned int il2=0;il2<leps2->size();il2++) {
      
      pTthr1 = (std::abs(leps1->at(il1)->pdgId())==11)?pTthrEl:pTthrMu;
      pTthr2 = (std::abs(leps2->at(il2)->pdgId())==11)?pTthrEl:pTthrMu;

      bool isMu=std::abs(_vc->get("LepGood_pdgId",idxs1[il1]))==13;
      Candidate* c1=Candidate::create(_vc->get("LepGood_pt",idxs1[il1]),
				      _vc->get("LepGood_eta",idxs1[il1]),
				      _vc->get("LepGood_phi",idxs1[il1]),
				      _vc->get("LepGood_pdgId",idxs1[il1]),
				      _vc->get("LepGood_charge",idxs1[il1]),
				      isMu?0.105:0.005 );

      isMu=std::abs(_vc->get("LepGood_pdgId",idxs2[il2]))==13;
      Candidate* c2=Candidate::create(_vc->get("LepGood_pt",idxs2[il2]),
				      _vc->get("LepGood_eta",idxs2[il2]),
				      _vc->get("LepGood_phi",idxs2[il2]),
				      _vc->get("LepGood_pdgId",idxs2[il2]),
				      _vc->get("LepGood_charge",idxs2[il2]),
				      isMu?0.105:0.005 );

      // cout<<il1<<"  "<<il2<<"   "<<leps1->at(il1)->pt()<<"   "<<leps2->at(il2)->pt()<<"   "<<c1->pt()<<passMllSingleVeto(leps1->at(il1), leps2->at(il2), 0, 8, false)
      // 	  <<"  "<<leps1->at(il1)->charge()<<" <> "<<leps2->at(il2)->charge()<<"   "<<c1->charge()<<" <> "<<c2->charge()<<"   "<<(leps1->at(il1)->charge()!=leps2->at(il2)->charge())<<"  "<<os<<"   "<<((leps1->at(il1)->charge()!=leps2->at(il2)->charge())!=os)<<endl;

      //conditional pt threshold, could evolve in CERN code 
      if(leps1->at(il1)->pt()<pTthr1 || leps2->at(il2)->pt()<pTthr2) continue; 
      if(!passMllSingleVeto(c1, c2, 0, 8, false) && !bypassMV) continue;
      if( (c1->charge()!=c2->charge())!=os ) continue;
      CandList tmp(2,NULL);
     
      tmp[0]=leps1->at(il1);
      tmp[1]=leps2->at(il2);

      InternalCList iclist;
      iclist.list = tmp;
      iclist.il1 = il1;
      iclist.il2 = il2;
      
      iCList.push_back(iclist);
    
    
    }//il2
  }//il1
  
  //ordering ================
  std::sort( iCList.begin(), iCList.end() );
  // if(iCList.size()>=2)
  //   cout<<" ===================== new pair ===================== "<<endl;
  for(unsigned int il=0;il<iCList.size();++il) {
    // if(iCList.size()>=2)
    //   cout<<" sorting pairs!!!!!! "<<il<<" -->  "<<iCList[il].list[0]->pdgId()
    // 	  <<"  "<<iCList[il].list[1]->pdgId()<<" --> "
    // 	  <<iCList[il].list[0]->pt()<<"  "<<iCList[il].list[1]->pt()<<endl;

    clist.push_back(iCList[il].list);
    idx1.push_back(iCList[il].il1);
    idx2.push_back(iCList[il].il2);
  }

  //=========================
  

  return clist;
}


const Candidate*
SusyModule::jetLepAware(const Candidate* lep) {
  
  float drTmp=1000;
  int idx=-1;
  string type="";
  Candidate* lepJet;
  vector<string> jetTypes;//({"Jet"});//,"DiscJet"});
  jetTypes.push_back("Jet");
  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    for(int ij=0;ij<_vc->get("n"+jType);ij++) {
      Candidate* jet=Candidate::create(_vc->get(jType+"_rawPt", ij),
				       _vc->get(jType+"_eta", ij),
				       _vc->get(jType+"_phi", ij) );
     
      float dR=lep->dR( jet );
      if(dR<drTmp && jet->pt()>0.8*lep->pt()){
	drTmp=dR;
	lepJet=jet;
	idx=ij;
	type=jType;
      }
    }//loop jet
  }//jet types

  //=======================================
  TLorentzVector l=lep->p4();
  if(idx==-1) return lep;//no jet matched
  
  TLorentzVector j=lepJet->p4();
  cout<<" rho "<<(j-l).Rho()<<endl;
  if( (j-l).Rho()<0.0001) return lep; //only the lepton
  cout<<"  L1 : "<<_vc->get(type+"_CorrFactor_L1")<<" --: "<<_vc->get(type+"_CorrFactor_L1L2L3Res")<<endl;
  j = (j-l*(1/_vc->get(type+"_CorrFactor_L1")) )*_vc->get(type+"_CorrFactor_L1L2L3Res")+l;
  lepJet=Candidate::create(j.Pt(), j.Eta(), j.Phi() );
  return lepJet;

}

float
SusyModule::pTRatio(const Candidate* lep, const Candidate* jet) {
  return lep->pt()/jet->pt();
}


float
SusyModule::pTRel(const Candidate* lep, const Candidate* jet) {
  if( (jet->p4()-lep->p4()).Rho()<0.0001) return 0;
  return (jet->p4()-lep->p4()).Perp(lep->p4().Vect() );
}


float
SusyModule::closestJetPt(int idx) const {
  return _vc->get("LepGood_pt", idx) / _vc->get("LepGood_jetPtRatiov2", idx);
}


float 
SusyModule::conePt(int idx, int isoWp) const {
  
    if(_vc->get("LepGood_jetPtRelv2", idx) > _multiIsoWP[kPtRel][isoWp] ) {
      return _vc->get("LepGood_pt", idx)*(1 + std::max((double) 0., _vc->get("LepGood_miniRelIso", idx) - _multiIsoWP[kMiniIso][isoWp] ) );
    }
    return std::max(_vc->get("LepGood_pt", idx), (double) closestJetPt(idx) * _multiIsoWP[kPtRatio][isoWp] );
}


void
SusyModule::ptJets(CandList allJets, vector<unsigned int> allJetIdxs,
                   CandList& jets, vector<unsigned int>& jetIdxs, float thr){

  for(unsigned int i = 0; i < allJets.size(); ++i) {
    if(allJets[i] -> pt() > thr) {
      jets   .push_back(allJets   [i]);
      jetIdxs.push_back(allJetIdxs[i]);
    }
  }

}


void
SusyModule::cleanJets(CandList* leptons, 
		      CandList& cleanJets, vector<unsigned int>& jetIdxs,
		      CandList& cleanBJets, vector<unsigned int>& bJetIdxs, float thr, float bthr ) {

  cleanJets.clear();
  cleanBJets.clear();
  jetIdxs.clear();
  bJetIdxs.clear();

  vector<string> jetTypes;//({"Jet","DiscJet"});
  jetTypes.push_back("Jet");
  jetTypes.push_back("DiscJet");
  CandList jets;
  vector<bool> bvals;
  for(size_t it=0;it<jetTypes.size();it++) {
    string jType=jetTypes[it];
    
    for(int ij=0;ij<_vc->get("n"+jType);ij++) {
      //cout<<_vc->get(jType+"_pt", ij)<<"  "<<_vc->get(jType+"_eta", ij)<<"  "<<jType<<endl;
      if(_vc->get(jType+"_id",ij)<1) continue;
      
      Candidate* jet=Candidate::create(_vc->get(jType+"_pt", ij),
				       _vc->get(jType+"_eta", ij),
				       _vc->get(jType+"_phi", ij) );

      jets.push_back(jet);
      bvals.push_back( _vc->get(jType+"_btagCSV",ij)<0.890 );//0.814
    }
  }


  map<Candidate*, std::pair<float,Candidate*> > cmap;
  map<Candidate*, std::pair<float,Candidate*> >::const_iterator it;

  for(unsigned int il=0;il<leptons->size();il++) {
    for(unsigned int ij=0;ij<jets.size();ij++) {

      float dR=leptons->at(il)->dR( jets[ij] );
      it = cmap.find(leptons->at(il));
      if(it==cmap.end() ) {
	cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
      else if(dR<it->second.first) {
	cmap[ leptons->at(il) ] =std::make_pair(dR, jets[ij] );
      }
    }
  }

  bool pass=true;
  for(unsigned int ij=0;ij<jets.size();ij++) {

    pass=true;
    for(unsigned int il=0;il<leptons->size();il++) {
      it = cmap.find(leptons->at(il));
      if(it->second.first > 0.4 ) continue;
      if(it->second.second == jets[ij] ) {pass=false; break;}
    }
    if(!pass) continue;

    if(jets[ij]->pt()<bthr) continue;
    
    if(jets[ij]->pt()>thr) {
      cleanJets.push_back(jets[ij] );
      jetIdxs.push_back(ij);
    }
    
    if(bvals[ij]) continue;
    
    cleanBJets.push_back(jets[ij]);
    bJetIdxs.push_back(ij);
  } //loop jets

}

void 
SusyModule::correctFlipRate(float& rate, float eta){

  if( -2.0 < eta && eta < -1.5) rate *= 3.6;
  else                          rate *= 1.15;

}


// Scale factors ====================================
void
SusyModule::applyHLTSF(const string& hltLine, float& weight){

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  weight *= _dbm->getDBValue("hltSF", hltLine);

}

void 
SusyModule::applyHLTSF(const string& hltLine, const CandList& cands, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  if(hltLine=="HLT_DoubleEG") {
    weight *= _dbm->getDBValue("hltDEG", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_DoubleMu") {
    weight *= _dbm->getDBValue("hltDMu", std::abs(cands[0]->eta()), cands[0]->pt(), cands[1]->eta(), cands[1]->pt() );
  }
  else if(hltLine=="HLT_SingleEle") {
    weight *= _dbm->getDBValue("hltSEle", std::abs(cands[0]->eta()), cands[0]->pt() );
  }
  else if(hltLine=="HLT_SingleMu") {
    weight *= _dbm->getDBValue("hltSMu", std::abs(cands[0]->eta()), cands[0]->pt() );
  }


}

void 
SusyModule::applyLepSF(const CandList& cands, float& weight) {

  for(unsigned int ic=0;ic<cands.size();ic++) {
    applySingleLepSF(cands[ic], weight);
  }

}


void 
SusyModule::applySingleLepSF(const Candidate* cand, float& weight) {

  if(_dbm==nullptr) {cout<<"Error, DB manager not set in the susy module, please change the constructor"<<endl; abort();}

  switch(std::abs(cand->pdgId())) {
  case 11: {weight *= _dbm->getDBValue("eleSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 13: {weight *= _dbm->getDBValue("muSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  case 15: {weight *= _dbm->getDBValue("tauSFDb", std::abs(cand->eta()), cand->pt() ); break;}
  }

}

float
SusyModule::bTagSF(CandList& jets , vector<unsigned int>& jetIdx ,
                   CandList& bJets, vector<unsigned int>& bJetIdx, int st){
  // put st = -1 / 0 / +1 for down / central / up

  float pdata = 1.0;
  float pmc   = 1.0;

  // light jets
  for(unsigned int i = 0; i < jets.size(); ++i) {
    if(find(bJetIdx.begin(), bJetIdx.end(), jetIdx[i]) == bJetIdx.end()){
      pdata *= (1 - bTagMediumEfficiency(jets[i], jetIdx[i], false) * 
		           bTagMediumScaleFactor(jets[i], jetIdx[i], false, st));
      pmc   *= (1 - bTagMediumEfficiency(jets[i], jetIdx[i], false));
    }
  }
  // bjets
  for(unsigned int i = 0; i < bJets.size(); ++i){
    pdata *= bTagMediumEfficiency (bJets[i], bJetIdx[i], true) * 
             bTagMediumScaleFactor(bJets[i], bJetIdx[i], true, st);
    pmc   *= bTagMediumEfficiency (bJets[i], bJetIdx[i], true);
  }

  if(pmc != 0) return pdata/pmc;
  return 1.0;

}

float
SusyModule::bTagMediumEfficiency(Candidate* jet, int jetIdx, bool isBTagged){

  if(isBTagged) 
    return _dbm->getDBValue("BTagEffCB", bTagPt(jet->pt()), std::abs(jet->eta()));
  return _dbm->getDBValue("BTagEffUSDG", bTagPt(jet->pt()), std::abs(jet->eta()));
} 

float
SusyModule::bTagMediumScaleFactor(Candidate* jet, int jetIdx, bool isBTagged, int st){

  //cout<<jet->pt()<<"    "<<jet->eta()<<"   "<<isBTagged<<"  "<<st<<" --> "<<_dbm->getDBValue("BTagSF",(isBTagged?1:2), jet->eta(), jet->pt())<<"   "<<endl;

  // if(st==0)  
  //   return _dbm->getTF1DBValue("BTagSF", jet->pt(), 1, !isBTagged, (isBTagged?1:2), jet->eta(), jet->pt(), 0.5);
  // else if(st==1)
  //   return _dbm->getTF1DBErrH("BTagSF", jet->pt(), 1, !isBTagged, (isBTagged?1:2), jet->eta(), jet->pt(), 0.5);
  // else
  //   return _dbm->getTF1DBErrL("BTagSF", jet->pt(), 1, !isBTagged, (isBTagged?1:2), jet->eta(), jet->pt(), 0.5);

  if(st==0){ 
    return _dbm->getDBValue("BTagSF", (isBTagged?1:2), jet->eta(), bTagPt(jet->pt()));
  }
  else if(st==1)
    return _dbm->getDBErrH("BTagSF",  (isBTagged?1:2), jet->eta(), bTagPt(jet->pt()));
  else
    return _dbm->getDBErrL("BTagSF",  (isBTagged?1:2), jet->eta(), bTagPt(jet->pt()));

} 


float
SusyModule::bTagPt(float rawPt){

  if(rawPt < 30) return 30;
  return rawPt;

}
