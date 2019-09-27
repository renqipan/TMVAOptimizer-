/* These methods handles the TMVA training */

#include "TMVAOptimizer.h"
#include "fom.h" 
#include <iostream>
using namespace TMVA;
/* The trainSample method is called from trainInterface, the sampNo is a typedef defined in the TMVAOptimizer headher file. This method also arranges the ratio of the train and test events for a given sample. For the moment this ratio is hardcoded to train/all=0.6  */
void TMVAAnalyzer::trainSample ( TTree * sample, int sampNo){
    int varInd = 0;
    std::vector<Float_t> dummyVars;
    dummyVars.resize(_varNames.size());
    for(auto varName :_varNames){
        sample->SetBranchAddress(varName, &dummyVars[varInd]);
        varInd++;
    }     
    Float_t weight, pho1_sigmaEOverE, pho2_sigmaEOverE;
    sample->SetBranchAddress("weight", &weight );
    //sample->SetBranchAddress("pho1_sigmaEOverE",&pho1_sigmaEOverE);
    //sample->SetBranchAddress("pho2_sigmaEOverE",&pho2_sigmaEOverE);
    for (UInt_t i=0; i< sample->GetEntries(); i++) {
        varInd = 0;
        sample->GetEntry(i);
        for(auto dummyVar :dummyVars){
            if(dummyVar != dummyVar){
                std::cout << _varNames[varInd] << std::endl;
                std::cout << dummyVar << std::endl;
            }

            _trainVars[varInd] = dummyVar;
            varInd++;
        }  
     /*     
        if( sampNo == ksig ){
            weight = weight;
            if (i%5 == 0 || i%5 == 2 || i%5 == 4) _dataloaderTrain->AddSignalTrainingEvent( _trainVars, weight );
            else if(i%5 == 1 || i%5 == 3) _dataloaderTrain->AddSignalTestEvent    ( _trainVars, weight );
        } 
        else {
            if (i%5 == 0 || i%5 == 2 || i%5 == 4) _dataloaderTrain->AddBackgroundTrainingEvent( _trainVars, weight );
            else if(i%5 == 1 || i%5 == 3) _dataloaderTrain->AddBackgroundTestEvent    ( _trainVars, weight );
        }
    */    

    }
}
/* the method which arranges the filenames according the TTHAnalyzer framework, a minor modification is required to make it generic*/
void TMVAAnalyzer::trainInterface (TString fName, TString tName, int sampNo){
    if (gSystem->AccessPathName( fName)) 
        std::cout << " The file not found " << fName<< std::endl;
    TFile *input = (TFile*)TFile::Open( fName);
    TTree *tree     = (TTree*)input->Get(tName);
//    std::cout << fName << std::endl;
    std::cout << "Opened the " << fName << " file with the number of entries: " << tree->GetEntries() << std::endl;
    trainSample(tree, sampNo);
    input->Close();
}
