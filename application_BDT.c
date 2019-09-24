//this is a c++ program for tth analysis application using trained and tested result
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

void application_BDT(){
	// This loads the library
    TMVA::Tools::Instance();
	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
	//Float_t diPhoPtoM,diPhoCosPhi,diPhoY;
	//Float_t lepPt_1,lepEta_1,lepPhi_1,lepE_1,nLep,nJetsBl;

	TString variables[39]={"diPhoPtoM", "diPhoCosPhi", "diPhoY", "lepPt_1", "lepEta_1", 
	"lepPhi_1","lepE_1", "nLep","nJetsBl","jetPt_1", "jetPt_2", 
	"jetPt_3","jetPt_4","jetPt_5","jetPt_6", "jetEta_1", "jetEta_2", 
	"jetEta_3", "jetEta_4", "jetEta_5", "jetEta_6", "jetPhi_1", "jetPhi_2", 
	"jetPhi_3","jetPhi_4", "jetPhi_5","jetPhi_6", "btag_1", "btag_2", "btag_3", 
	"btag_4", "btag_5", "btag_6", "jetE_1", "jetE_2", "jetE_3","jetE_4","jetE_5","jetE_6" };
	Float_t values[39];
	for(int kk=0;kk<39;kk++)
		reader->AddVariable(variables[kk],&values[kk]);


	TString BDTFileName="TMVAClassification_BDT.weights.xml";
	TString dir="/home/renqi/Documents/tth_todiph/dataset_diph_lep3/weights/";
	TString BTDFile=dir+BDTFileName;
	reader->BookMVA("BDT method", BTDFile );
	int nbin=100;
    TH1F *histBDT= new TH1F( "MVA_BDT_sig","MVA_BDT_sig",nbin, -0.5,0.5 );
    //define root file and tree
	TChain *tsignal= new  TChain("tth_13TeV_all");
	tsignal->Add("ttHiggs0PToGG1.root");
	tsignal->Add("ttHiggs0PToGG2.root");
	tsignal->Add("ttHiggs0PToGG3.root");

	
	for(int jj=0;jj<39;jj++)
		tsignal->SetBranchAddress(variables[jj],&values[jj]);

	std::cout << "--- Processing: " << tsignal->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();

	for (Long64_t ievt=0; ievt<tsignal->GetEntries();ievt++) {

	      if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

	      tsignal->GetEntry(ievt);
	      histBDT ->Fill( reader->EvaluateMVA( "BDT method") );
	}
	// Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
    TString outputFile("tth_BDT_me3.root");
    TFile *target  = new TFile( outputFile,"update" );
    histBDT->Write();

    target->Close();
	std::cout << "--- Created root file: "<<outputFile<<" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;

}