/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Jan Hoss, ETHZ, 12/2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef SUSY3L_sync_HH
#define SUSY3L_sync_HH

#include "analysis/core/MPAF.hh"

class SUSY3L_sync: public MPAF {

public:
    // Member Functions
    SUSY3L_sync(std::string);
    virtual ~SUSY3L_sync();

private:
    void initialize();

    void run();
    void defineOutput();
    void loadInput();
    void modifyWeight();
    void writeOutput();

    void modifySkimming();

    void collectKinematicObjects();
    bool electronSelection(int);
    bool muonSelection(int);
    bool tauSelection(int);
    bool vetoElectronSelection(int);
    bool vetoMuonSelection(int);
    bool bJetSelection(int);
    bool goodJetSelection(int);

    bool baseSelection();
    void setBaselineRegion();
    void setSignalRegion();
    void setCut(std::string, float, std::string, float = 0);
    bool hardLegSelection();
    bool lowMllPair();
    bool ZEventSelection();
    bool ZEventSelectionLoop();
    bool srSelection();

    void fillEventPlots(std::string);



    float HT();
    float M_T(float, float, float, float);
    float DeltaPhi(float, float);

    string _pairmass;
    string _BR;
    string _SR;

private:

    //counter categories, 0 is ALWAYS global (even if not specified later)
    enum {kGlobal=0, kElId, kElVeto, kMuId, kMuVeto, kTauId, kTauVeto, kJetId, kBJetId, conZEvents};

    //cut variables
    float _valCutLepMultiplicityBR;
    float _pt_cut_hard_leg;
    float _M_T_3rdLep_MET_cut;
    float _valCutNJetsBR;
    float _valCutNBJetsBR;
    float _ZMassWindow;
    float _lowMllCut;
    float _valCutHTBR;
    float _valCutMETBR;
    float _valCutHTSR;
    float _valCutMETSR;
    float _valCutNJetsSR;
    float _valCutNBJetsSR;
    
    std::string _cTypeLepMultiplicityBR;
    std::string _cTypeNJetsBR;
    std::string _cTypeNBJetsBR;
    std::string _cTypeHTBR;
    std::string _cTypeMETBR;
    std::string _cTypeNJetsSR;
    std::string _cTypeNBJetsSR;
    std::string _cTypeHTSR;
    std::string _cTypeMETSR;

    float _upValCutLepMultiplicityBR;
    float _upValCutNJetsBR;
    float _upValCutNBJetsBR;
    float _upValCutHTBR;
    float _upValCutMETBR;
    float _upValCutNJetsSR;
    float _upValCutNBJetsSR;
    float _upValCutHTSR;
    float _upValCutMETSR;

    //vectors for electron, muon, and tau candidates
    std::vector<int> _elIdx;
    std::vector<int> _muIdx;
    std::vector<int> _tauIdx;

    //length of candiate vectors
    int _nEls;
    int _nVEls;
    int _nMus;
    int _nVMus;
    int _nTaus;
    int _nVTaus;
    int _nJets;
    int _nBJets;

    //list of object candidates
    CandList _els;
    CandList _vEls;
    CandList _mus;
    CandList _vMus;
    CandList _taus;
    CandList _vTaus;
    CandList _jets;
    CandList _bJets;
    Candidate* _met;
    Candidate* _Z;

    float _HT;
    float _deltaR;
    
};

#endif
