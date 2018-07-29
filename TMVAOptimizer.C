#include "TMVAOptimizer.h"
#include "fom.h" 
#include <iostream>
using namespace TMVA;

void TMVAAnalyzer::TMVAClassification(){
    TString outfileName( _outputPath+"/TMVA.root" );
    (TMVA::gConfig().GetIONames()).fWeightFileDir = _outputPath;
    outputFile = TFile::Open( outfileName, "RECREATE" );
    _factory = new TMVA::Factory( (TString)"TMVAClassification", outputFile,
//                                  (TString)"DrawProgressBar=False:Silent=True:AnalysisType=Classification" );
                                  (TString)"!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );
    _dataloaderTrain = new TMVA::DataLoader("");
    int varInd = 0;
    for(auto varName :_varNames){
        _dataloaderTrain->AddVariable(varName);
        varInd++;
    }     
    
    TCut mycuts = "";
    TCut mycutb = "";
    std::cout << "Performing training..." << std::endl;
 
/*
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8", "vbf_125_13TeV_TTHLeptonicTag",kVBF);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8", "ggh_125_13TeV_TTHLeptonicTag",kGGHgg);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_M40_80-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_WZHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "wzh_125_13TeV_TTHLeptonicTag",kWZH);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet_13TeV_TTHLeptonicTag",kTTgJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet2_13TeV_TTHLeptonicTag",kTTgJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_11o100missing", "ttjet_13TeV_TTHLeptonicTag",kTTJet);


    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8", "vbf_125_13TeV_TTHLeptonicTag",kVBF);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8", "ggh_125_13TeV_TTHLeptonicTag",kGGHgg);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_M40_80-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTHToGG_M125_13TeV_powheg_pythia8", "tth_125_poweg_13TeV_TTHLeptonicTag",kTTH);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_WZHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "wzh_125_13TeV_TTHLeptonicTag",kWZH);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet_13TeV_TTHLeptonicTag",kTTgJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet2_13TeV_TTHLeptonicTag",kTTgJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_11o100missing", "ttjet_13TeV_TTHLeptonicTag",kTTJet);
*/

    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8", "vbf_125_13TeV_TTHLeptonicTag",kVBF);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8", "ggh_125_13TeV_TTHLeptonicTag",kGGHgg);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_DiPhotonJetsBox_M40_80-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTHToGG_M125_13TeV_powheg_pythia8", "tth_125_poweg_13TeV_TTHLeptonicTag",kTTH);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_WZHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "wzh_125_13TeV_TTHLeptonicTag",kWZH);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet_13TeV_TTHLeptonicTag",kTTgJet);
    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8", "ttjet_13TeV_TTHLeptonicTag",kTTJet);
//    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_bbHToGG_M-125_4FS_yb2_13TeV_amcatnlo", "bbh_125_13TeV_TTHLeptonicTag",kBBH);
//    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8", "ttgg_13TeV_TTHLeptonicTag",kTTgg0Jet );

//    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAdatatr/output_DoubleEG-Run2017-17Nov2017train", "Data_13TeV_TTHLeptonicTag",kData );
//    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAdatatr/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8", "thq_125_13TeV_TTHLeptonicTag",kTHQ);
//    trainInterface("/eos/user/m/msahin/TTH/samples2017/MVAdatatr/output_THW_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8", "thw_125_13TeV_TTHLeptonicTag",kTHW);


    _dataloaderTrain->PrepareTrainingAndTestTree( mycuts, mycutb,
                                         "NormMode=NumEvents:!V" );
    if(_methodName.Contains("BDT")){
        _factory->BookMethod(_dataloaderTrain, TMVA::Types::kBDT, _methodName,
                              (TString)"!H:!V:NTrees="+TString::Format("%5.0f",_nTrees)+":MinNodeSize="+TString::Format("%5.1f",_minNodeSize)+"%:MaxDepth="+TString::Format("%5.0f",_maxDepth)+":BoostType=AdaBoost:AdaBoostBeta="+TString::Format("%5.1f",_adaBoostB)+":UseBaggedBoost:BaggedSampleFraction="+TString::Format("%5.1f",_baggingRatio)+":SeparationType=GiniIndex:nCuts=500::VarTransform=Norm" );
    }else if(_methodName.Contains("SVM")){
        _factory->BookMethod(_dataloaderTrain, TMVA::Types::kSVM, _methodName,
                              (TString)"!H:!V:Gamma="+TString::Format("%6.4f",_gammaRBF)+":C="+TString::Format("%5.1f",_cSVM)+":Kernel=RBF:VarTransform=Norm" );
    }else if(_methodName.Contains("Keras")){
        _factory->BookMethod(_dataloaderTrain, TMVA::Types::kPyKeras, _methodName, "H:!V:VarTransform=D,G:FilenameModel=model.h5:NumEpochs=20:BatchSize=100");
    }

    _factory->TrainAllMethods();
    _factory->TestAllMethods();
    _factory->EvaluateAllMethods();
    outputFile->Close();
    delete _factory;      
}

void TMVAAnalyzer::TMVAClassificationApp(){
    _reader = new TMVA::Reader( "!Color:!Silent" );           
    int varInd = 0;
    for(auto varName :_varNames){
        _reader->AddVariable(varName, &_evalVars[varInd]);
        varInd++;
    }     
    
    TString dir    = _outputPath+(TString)"/";
    TString prefix = "TMVAClassification";
    TString methodName = _methodName + TString(" method");
    TString weightfile = dir + prefix + TString("_") + _methodName + TString(".weights.xml");
    _reader->BookMVA( _methodName, weightfile ); 
/*
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8", "vbf_125_13TeV_TTHLeptonicTag",kVBF);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8", "ggh_125_13TeV_TTHLeptonicTag",kGGHgg);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_M40_80-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_DoubleEG-Run2017-17Nov2017", "Data_13TeV_TTHLeptonicTag",kData );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "tth_125_13TeV_TTHLeptonicTag",kTTH);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_WZHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "wzh_125_13TeV_TTHLeptonicTag",kWZH);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet_13TeV_TTHLeptonicTag",kTTgJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet2_13TeV_TTHLeptonicTag",kTTgJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/lepMVA/output_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_11o100missing", "ttjet_13TeV_TTHLeptonicTag",kTTJet);
*/

    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_VBFHToGG_M125_13TeV_amcatnlo_pythia8", "vbf_125_13TeV_TTHLeptonicTag",kVBF);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8", "ggh_125_13TeV_TTHLeptonicTag",kGGHgg);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_DiPhotonJetsBox_M40_80-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa", "dipho_13TeV_TTHLeptonicTag",kDiPho);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "qcd_13TeV_TTHLeptonicTag",kQCD );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_DoubleEG-Run2017-17Nov2017", "Data_13TeV_TTHLeptonicTag",kData );
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8", "gjet_13TeV_TTHLeptonicTag",kGJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "tth_125_13TeV_TTHLeptonicTag",kTTH);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_WZHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8", "wzh_125_13TeV_TTHLeptonicTag",kWZH);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8", "ttgjet_13TeV_TTHLeptonicTag",kTTgJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8", "ttjet_13TeV_TTHLeptonicTag",kTTJet);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8", "thq_125_13TeV_TTHLeptonicTag",kTHQ);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_bbHToGG_M-125_4FS_yb2_13TeV_amcatnlo", "bbh_125_13TeV_TTHLeptonicTag",kBBH);
    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8", "ttgg_13TeV_TTHLeptonicTag",kTTgg0Jet );
//    evalInterface("/eos/user/m/msahin/TTH/samples2017/MVAlepton/output_THW_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8", "thw_125_13TeV_TTHLeptonicTag",kTHW);


    TFile * evalOutput = new TFile(_outputPath+(TString)"_evaluation.root","RECREATE");
    fom findMaxSign(0.01,fom::asimov); 
    fom findMaxSignN(0.0001,fom::stop); 
    Float_t maxSignOv, maxSignTest, maxSignTra, maxSignData;
    std::cout << "Overall: ";
    maxSignOv   = findMaxSign.maxSignificance(_hEvalSignal, _hEvalBkg, true, _minSignal);
    std::cout << "Overall SR: ";
    maxSignOv   = findMaxSign.maxSignificance(_hEvalSignal, _hEvalBkgSR, true, _minSignal);
    std::cout << " Overall naive: ";
    findMaxSignN.maxSignificance(_hEvalSignal, _hEvalBkg, true, _minSignal);
    std::cout << "Train: ";
    maxSignTra  = findMaxSign.maxSignificance(_hEvalSignal, _hEvalBkgTra, true, _minSignal);
    std::cout << "Test: ";
    maxSignTest = findMaxSign.maxSignificance(_hEvalSignal, _hEvalBkgTest, true, _minSignal);
    std::cout << "Data: ";
    maxSignData = findMaxSign.maxSignificance(_hEvalSignal, _hEvalBkgData, true, _minSignal, _hEffData);
    std::cout << "Data naive: ";
    findMaxSignN.maxSignificance(_hEvalSignal, _hEvalBkgData, true, _minSignal);
    std::cout << "The final score for the given training: " <<  TMath::Sqrt((maxSignTest*maxSignTest+maxSignData*maxSignData-fabs(maxSignTra*maxSignTra-maxSignTest*maxSignTest))/2.) << std::endl;
    std::cout << "The consistency score: " << TMath::Sqrt(_hEffData->GetBinContent(_hEffData->GetMaximumBin()-3)*_hEffData->GetBinContent(_hEffData->GetMaximumBin()-3)+_hEffData->GetBinContent(_hEffData->GetMaximumBin()-2)*_hEffData->GetBinContent(_hEffData->GetMaximumBin()-2)+_hEffData->GetBinContent(_hEffData->GetMaximumBin()-1)*_hEffData->GetBinContent(_hEffData->GetMaximumBin()-1)+_hEffData->GetBinContent(_hEffData->GetMaximumBin())*_hEffData->GetBinContent(_hEffData->GetMaximumBin())) << std::endl;
    fitandfindMax();
    _hEffData->Write();
    _hEvalSignal->Write();
    _hEvalBkg->Write();
    _hEvalBkgTra->Write();
    _hEvalBkgTest->Write();
    _hEvalBkgData->Write();
    evalOutput->Close();
    delete _reader;
}

void TMVAAnalyzer::fitandfindMax(){
    TF1 * massFitLow = new TF1("massfitLow",  "[0]*pow(x,[1])", 100, 115);
    TF1 * massFitHigh= new TF1("massfitHigh", "[0]*pow(x,[1])", 135, 180);
    TF1 * massFitAll = new TF1("massfitAll","([0]*pow(x,[1]))*([2]*pow(x,[3]))",100,180);
    Double_t parameters[4], maxSPars[4], bkgYield, sigYield, tmpSigma = 0., maxSigma = 0.; 
    int maxSBin = 0;
    fom asimov(0.15,fom::asimov);
    TCanvas * canvMass = new TCanvas( "Hgg mass","Hgg mass",800,800);
    for(unsigned int nbin = 1; nbin <= _binMVA ; nbin++){
        if (_distOfInterestSig.at(nbin)->Integral(22,28) < _minSignal*0.5) continue;
        parameters[0] = _distOfInterestBkg.at(nbin)->GetBinContent(1);
        parameters[1] = -4.0;
        parameters[2] = _distOfInterestBkg.at(nbin)->GetBinContent(36);
        parameters[3] = -4.0;
        massFitLow->SetParameters(&parameters[0]);
        _distOfInterestBkg.at(nbin)->Fit(massFitLow, "QR");
        massFitHigh->SetParameters(&parameters[2]);
        _distOfInterestBkg.at(nbin)->Fit(massFitHigh, "QR+");
        massFitLow->GetParameters(&parameters[0]);
        massFitHigh->GetParameters(&parameters[2]); 
        massFitAll->SetParameters(parameters);
        _distOfInterestBkg.at(nbin)->Fit(massFitAll, "QR+");
        bkgYield = massFitAll->Integral(122,128);
        sigYield = _distOfInterestSig.at(nbin)->Integral(22,28);
//        std::cout << " estimated background from MC: " << bkgYield << std::endl;
//        std::cout << " estimated signal from MC: " << sigYield << std::endl;
        asimov.setBackground(bkgYield);
        asimov.setSignal(sigYield);
        tmpSigma =  asimov.getSignificance(fom::asimov);
//        std::cout << " corresponding asimov significance: " << tmpSigma << std::endl;
        if(tmpSigma > maxSigma){
            maxSigma = tmpSigma;
            maxSBin = nbin;
            maxSPars[0] = parameters[0]; maxSPars[1] = parameters[1]; maxSPars[2] = parameters[2]; maxSPars[3] = parameters[3]; 
        }
    }
    std::cout << " Maximum Z_A obtained: " << maxSigma << " at bin " << maxSBin << std::endl;
    massFitAll->SetParameters(maxSPars);
    _distOfInterestBkg.at(maxSBin)->Fit(massFitAll, "R");
    _distOfInterestBkg.at(maxSBin)->Draw();
    _distOfInterestSig.at(maxSBin)->Draw("same");
    canvMass->Write();
}


int main (int argc, char* argv[]){
    Float_t nTrees, minNodeSize,  maxDepth,  adaBoostB, baggingRatio, cSVM, gammaSVM;
    TString pathOutput, algoType;
//    std::vector<TString> vars = { "pho1_ptoM","pho2_ptoM","pho1_sceta","pho2_sceta", "diPhoY", "diPhoCosPhi", "minPhoID", "maxPhoID", "diPhoPtoM"};//, "btag_1", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"leadJetPt","nJets","sumJetPt","maxBTagVal", "secondMaxBTagVal","pho1_ptoM","pho2_ptoM","pho1_sceta","pho2_sceta", "diPhoY", "diPhoCosPhi", "minPhoID", "maxPhoID", "diPhoPtoM", "mindRPhoLeadJet", "maxdRPhoLeadJet", "nJetsBl", "btag_1","btag_2", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"nJets","nJetsBl","btag_1","btag_2","btag_3","btag_4","jetPt_1","jetPt_2","jetPt_3","jetPt_4","jetEta_1","jetEta_2","jetEta_3","jetEta_4","jetPhi_1","jetPhi_2","jetPhi_3","jetPhi_4","bjetPt_1","bjetPt_2","bjetEta_1","bjetEta_2","bjetPhi_1","maxBTagVal", "secondMaxBTagVal","sumJetPt" };//, "btag_1", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"nJets","sumJetPt","maxBTagVal", "secondMaxBTagVal","pho1_ptoM","pho2_ptoM","pho1_sceta","pho2_sceta", "pho1_scphi","pho2_scphi","diPhoY","minPhoID","maxPhoID","diPhoPtoM","btag_1","btag_2","btag_3","btag_4","jetPt_1","jetPt_2","jetPt_3","jetPt_4","jetEta_1","jetEta_2","jetEta_3","jetEta_4","pho1_hasPixelSeed","pho2_hasPixelSeed","thirdMaxBTagVal","MET","ttHMVA17tt" };//, "btag_1", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"nJets","sumJetPt","maxBTagVal", "secondMaxBTagVal","pho1_ptoM","pho2_ptoM","pho1_sceta","pho2_sceta", "pho1_scphi","pho2_scphi","diPhoY","diPhoCosPhi","minPhoID","maxPhoID","diPhoPtoM","nJetsBl","btag_1","btag_2","btag_3","btag_4","jetPt_1","jetPt_2","jetPt_3","jetPt_4","jetE_1","jetE_2","jetE_3","jetE_4","jetEta_1","jetEta_2","jetEta_3","jetEta_4","jetPhi_1","jetPhi_2","jetPhi_3","jetPhi_4","pho1_sigmaEOverE","pho2_sigmaEOverE","thirdMaxBTagVal","MET","pho1_hasPixelSeed","pho2_hasPixelSeed" };//, "btag_1", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"nJets","sumJetPt","maxBTagVal", "secondMaxBTagVal","pho1_ptoM","pho2_ptoM","pho1_sceta","pho2_sceta", "pho1_scphi","pho2_scphi","diPhoY","diPhoCosPhi","diPhoPtoM","nJetsBl","btag_1","btag_2","btag_3","btag_4","jetPt_1","jetPt_2","jetPt_3","jetPt_4","jetEta_1","jetEta_2","jetEta_3","jetEta_4","jetPhi_1","jetPhi_2","jetPhi_3","jetPhi_4","pho1_sigmaEOverE","pho2_sigmaEOverE","thirdMaxBTagVal" };//, "btag_1", "thirdMaxBTagVal"};
    std::vector<TString> vars = {"ttHMVA17_new_30vars", "lepPt_1", "lepEta_1", "lepPhi_1" };//, "btag_1", "thirdMaxBTagVal"};
//    std::vector<TString> vars = {"nJets", "sumJetPt", "maxBTagVal", "secondMaxBTagVal", "pho1_ptoM", "pho2_ptoM", "pho1_sceta", "pho2_sceta", "pho1_scphi", "pho2_scphi", "diPhoY", "minPhoID", "maxPhoID", "diPhoPtoM", "btag_1", "btag_2", "btag_3", "jetPt_1", "jetPt_2", "jetPt_3", "jetEta_1", "jetEta_2", "jetEta_3", "pho1_hasPixelSeed", "pho2_hasPixelSeed", "MET", "ttHMVA17_new_30vars", "lepPt_1", "lepEta_1", "lepPhi_1" };//, "btag_1", "thirdMaxBTagVal"};
    std::cout << " variables used: "; 
    for(auto var: vars){
        std::cout << var << "  ";
    }
    std::cout << std::endl;
    std::cout << argv[1] << std::endl;
    if(!(TString(argv[1]).Contains("SVM") || TString(argv[1]).Contains("BDT") || TString(argv[1]).Contains("Keras"))){
        std::cout << "  Usage ./TMVAAnalysis algoName para1 para2 ..." << std::endl; 
        return 0;
    } else {
        algoType = argv[1];
    }
    TMVAAnalyzer mva(vars, algoType, 0 , "");
    if ( argc != 8 && "BDT" == algoType) {
        std::cout << " Usage ./TMVAAnalysis BDT nBDTtrees minNodeSize maxDepth adaBoostB baggingRatio outputPath" << std::endl; 
        return 0;
    } else if("BDT" == algoType) {
        Float_t nTrees = std::atof(argv[2]);
        Float_t minNodeSize = std::atof(argv[3]);
        Float_t maxDepth = std::atof(argv[4]);
        Float_t adaBoostB = std::atof(argv[5]);
        Float_t baggingRatio = std::atof(argv[6]);
        TString pathOutput = TString(argv[7]);
        std::cout<< " Training BDT trees with the following parameters: " << std::endl;
        std::cout<< " number of BDT trees are set to " << TString::Format("%5.0f",nTrees) << std::endl;
        std::cout<< " min node size of a BDT tree is set to  " << TString::Format("%5.1f",minNodeSize) << std::endl;
        std::cout<< " max depth of a BDT tree is set to  " << TString::Format("%5.0f",maxDepth) << std::endl;
        std::cout<< " AdaBoostBeta of a BDT tree is set to  " << TString::Format("%5.1f",adaBoostB) << std::endl;
        std::cout<< " bagging ratio of a BDT tree is set to  " << TString::Format("%5.1f",baggingRatio) << std::endl;
        mva.setNTree(nTrees);
        mva.setMinNodeSize(minNodeSize);
        mva.setMaxDepth(maxDepth);
        mva.setAdaBoostB(adaBoostB);
        mva.setBaggingRatio(baggingRatio);
        mva.setOutputPath(pathOutput);
    } else if(argc != 5 && "SVM" == algoType) {
        std::cout << " Usage ./TMVAAnalysis SVM SVM_C RBF_Gamma outputPath" << std::endl; 
        return 0;
    } else if("SVM" == algoType){
        Float_t cSVM = std::atof(argv[2]);
        Float_t gammaRBF = std::atof(argv[3]); 
        TString pathOutput = TString(argv[4]);
        mva.setCSVM(cSVM);
        mva.setGammaRBF(gammaRBF);
        mva.setOutputPath(pathOutput);
        std::cout << " Training SVMs with the following parameters: " << std::endl;
        std::cout << " C penalty parameter is set to " << TString::Format("%5.0f",cSVM) << std::endl;
        std::cout << " RBF-kernel Gamma parameter is set to " << TString::Format("%6.4f",gammaRBF) << " -> sigma " << TString::Format("%5.2f",1./gammaRBF/2.) << std::endl;
    } else if("Keras" == algoType){
        TString pathOutput = TString(argv[2]);
        mva.setOutputPath(pathOutput);
    }
    mva.TMVAClassification();
    mva.TMVAClassificationApp();
    return 0;
}
