#include "TMVAOptimizer.h"
#include "fom.h" 
#include <iostream>
using namespace TMVA;

void TMVAAnalyzer::evalSample (TTree * sample, int sampNo, bool addEvalBranch,TString branchName){
    Float_t sampleWeight = 1.0, weight, diPhoMass;
    static int fileNo = 0;
    const Float_t maxWeight = 1.0; 
    Float_t nJets, trained = 0.;
    sample->SetBranchAddress("weight", &weight );
    sample->SetBranchAddress("mass", &diPhoMass );
    int varInd = 0;
    for(auto varName :_varNames){
        sample->SetBranchAddress(varName,&_evalVars[varInd]);
        varInd++;
    }    
    TBranch *newBranch;
    Float_t BDTvalue = 0.;
    static Float_t nSig = 0., nBkg = 0.;
    if(addEvalBranch){
        if(! sample->FindBranch(branchName)){
               newBranch = sample-> Branch(branchName,&BDTvalue,branchName+"/F");
        } else {
            std::cout << "Branch already exists; moving on without adding it to the tree" << std::endl;
        }
    }
    for (UInt_t i=0; i<sample->GetEntries(); i++) {
        sample->GetEntry(i);
        BDTvalue = _reader->EvaluateMVA(_methodName );
        if(addEvalBranch)        newBranch->Fill();
        if(ksig == sampNo){
            _hEvalSignal->Fill(BDTvalue, weight);
            for(int indexBin = 0; indexBin <= _hEvalSignal->FindFixBin(BDTvalue); indexBin ++){ 
                _distOfInterestSig.at(indexBin)->Fill(diPhoMass, weight);
            }
        } 
        else if(diPhoMass > 135. || diPhoMass < 115. ){
            if(kbkg == sampNo){
                _hEvalBkgData->Fill(BDTvalue);
                for(int indexBin = 1; indexBin <= _hEvalBkgData->FindFixBin(BDTvalue); indexBin ++){ 
                    _distOfInterestBkg.at(indexBin)->Fill(diPhoMass);
                }
            } else {
                _hEvalBkg->Fill(BDTvalue, weight);
                if (i%5 == 0 || i%5 == 2 || i%5 == 4) _hEvalBkgTra->Fill(BDTvalue, weight/0.6);
                else if(i%5 == 1 || i%5 == 3) _hEvalBkgTest->Fill(BDTvalue, weight/0.4);
            }
        } else {
            if(kbkg != sampNo){
//                weight = weight / 25.;
                _hEvalBkgSR->Fill(BDTvalue, weight); 
            }

        }
    }
    fileNo ++ ;
}

void TMVAAnalyzer::evalInterface (TString fName, TString tName, int sampNo){ 
    if (gSystem->AccessPathName( fName))  // file does not exist in local directory
        std::cout << " The file not found " << fName<< std::endl;
    TFile *input = TFile::Open( fName);
    TTree *tree     = (TTree*)input->Get(tName);
    evalSample(tree, sampNo, _addEvalBranch, _evalBranchName);
    if(_addEvalBranch){
        input->cd("tagsDumper/trees/");
        tree->Write("", TObject::kOverwrite);
    }
    input->Close();
}
