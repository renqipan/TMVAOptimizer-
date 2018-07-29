#ifndef TMVAOptimizer_h
#define TMVAOptimizer_h
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Config.h"
#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TMVA/DataLoader.h"
class TMVAAnalyzer{
public:
    TMVAAnalyzer(std::vector<TString> varNames, TString methodName, bool addEvalBranch, TString evalBranchName ){
        _addEvalBranch = addEvalBranch; 
        _evalBranchName = evalBranchName;
        _evalVars.resize(varNames.size());
        _varNames = varNames;
        _trainVars.resize(varNames.size());
        _methodName = methodName;            
        TMVA::Tools::Instance();
        _minSignal = 2.1;
        _hEffData    = new TH1F("eff Data","eff Data", _binMVA, -1.,1.);
        _hEvalSignal = new TH1F("SignalValues","Signal Resp Histo", _binMVA, -1.,1.);
        _hEvalBkgSR  = new TH1F("BackgroundValuesSR","Background Resp Histo SR", _binMVA, -1.,1.);
        _hEvalBkg    = new TH1F("BackgroundValues","Background Resp Histo", _binMVA, -1.,1.);
        _hEvalBkgTra = new TH1F("BackgroundValuesTra","Background Resp Histo", _binMVA, -1.,1.);
        _hEvalBkgTest= new TH1F("BackgroundValuesTest","Background Resp Histo", _binMVA, -1.,1.);
        _hEvalBkgData= new TH1F("BackgroundValuesData","Background Resp Histo", _binMVA, -1.,1.);
        for(unsigned int nbin = 0; nbin <= _binMVA; nbin++){
            _distOfInterestBkg.push_back( new TH1F(TString("massMVAbkg")+TString::Format("%d",nbin),"Mass for given MVA cut", 80, 100, 180)); 
        }  
        for(unsigned int nbin = 0; nbin <= _binMVA; nbin++){
            _distOfInterestSig.push_back( new TH1F(TString("massMVAsig")+TString::Format("%d",nbin),"Mass for given MVA cut", 80, 100, 180)); 
        }  

    }
    ~TMVAAnalyzer(){
        delete _hEffData;
        delete _hEvalSignal;
        delete _hEvalBkg;
        delete _hEvalBkgSR;
        delete _hEvalBkgTest;
        delete _hEvalBkgTra;
        delete _hEvalBkgData;
        for(unsigned int nbin = 0; nbin <= _binMVA; nbin++){
            delete _distOfInterestBkg.at(nbin);
        }  
        for(unsigned int nbin = 0; nbin <= _binMVA; nbin++){
            delete _distOfInterestSig.at(nbin);
        }  
    }
    void setNTree(Float_t nTrees){
        _nTrees = nTrees;
    }
    void setOutputPath (TString outputPath){
        _outputPath = outputPath;
    }
    void setMinNodeSize(Float_t minNodeSize){
        _minNodeSize = minNodeSize;
    }
    void setMaxDepth(Float_t maxDepth){
        _maxDepth = maxDepth;
    }
    void setAdaBoostB(Float_t adaBoostB){
        _adaBoostB = adaBoostB;
    }
    void setBaggingRatio(Float_t baggingRatio){
        _baggingRatio = baggingRatio;
    }
    void setCSVM(Float_t cSVM){
        _cSVM = cSVM;
    }
    void setGammaRBF(Float_t gammaRBF){
        _gammaRBF = gammaRBF;
    }
    void TMVAClassification();
    void TMVAClassificationApp();
    void fitandfindMax();
    enum sampleType{kGJet, kTTggJet, kQCD, kVBF, kTTH, kDiPho, kTTgg0Jet, kTTJet, kTTgJet,kGGHgg, kTgJet, kData, kWZH, kTHQ, kTHW, kBBH};
private:
    void trainSample (TTree * sample, int sampNo);
    void trainInterface (TString fName, TString tName, int sampNo);
    void evalSample (TTree * sample, int sampNo, bool addEvalBranch, TString evalBranchName);
    void evalInterface (TString fName, TString tName, int sampNo);
    std::vector <TH1F*> _distOfInterestBkg;
    std::vector <TH1F*> _distOfInterestSig;
    TH1F* _hEffData;
    TH1F* _hEvalSignal;
    TH1F* _hEvalBkg;
    TH1F* _hEvalBkgTra;
    TH1F* _hEvalBkgTest;
    TH1F* _hEvalBkgData;
    TH1F* _hEvalBkgSR;
    bool _addEvalBranch;
    TString _evalBranchName;
    Float_t _nTrees, _minNodeSize, _maxDepth, _adaBoostB, _baggingRatio, _cSVM, _gammaRBF, _minSignal; 
    const int _binMVA = 200; 
    TMVA::Factory * _factory;
    TMVA::Reader * _reader;
    TMVA::DataLoader * _dataloaderTrain;
    TMVA::DataLoader * _dataloaderTest;
    std::vector<Float_t> _evalVars;
    std::vector<Double_t> _trainVars;
    std::vector<TString> _varNames;
    TString _methodName, _outputPath;
    TFile* outputFile;
};
#endif
