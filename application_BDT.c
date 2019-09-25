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

	TString variables[45]={"dipho_sumpt", "dipho_cosphi", "dipho_rapidity", "nb_loose","jet1_pt", "jet2_pt", "jet3_pt","jet4_pt","jet5_pt","jet6_pt","jet7_pt","jet8_pt", "jet1_eta", "jet2_eta", "jet3_eta", "jet4_eta", "jet5_eta", "jet6_eta", "jet7_eta", "jet8_eta", "jet1_phi", "jet2_phi", "jet3_phi", "jet4_phi", "jet5_phi", "jet6_phi", "jet7_phi", "jet8_phi", "jet1_bdiscriminant", "jet2_bdiscriminant", "jet3_bdiscriminant", "jet4_bdiscriminant", "jet5_bdiscriminant", "jet6_bdiscriminant", "jet7_bdiscriminant", "jet8_bdiscriminant", "jet1_energy", "jet2_energy", "jet3_energy", "jet4_energy", "jet5_energy", "jet6_energy", "jet7_energy", "jet8_energy","mass" };
	Float_t values[45];
	for(int kk=0;kk<45;kk++)
		reader->AddVariable(variables[kk],&values[kk]);


	TString BDTFileName="TMVAClassification_BDT.weights.xml";
	TString dir="/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/";
	TString BTDFile=dir+BDTFileName;
         reader->BookMVA("BDT method", BTDFile );
	int nbin=100;
    TH1F *histBDT= new TH1F( "MVA_BDT_powheg","MVA_BDT_powheg",nbin, -0.5,0.5 );
    //define root file and tree
	TChain *tsignal= new  TChain("tthHadronicTagDumper/trees/tth_13TeV_all");
	tsignal->Add("/afs/cern.ch/user/r/repan/root_file/ttHToGG_M125_13TeV_powheg.root");
	//tsignal->Add("ttHiggs0PToGG2.root");
	//tsignal->Add("ttHiggs0PToGG3.root");

	
	for(int jj=0;jj<45;jj++)
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
    TString outputFile("tth_BDT_powheg_app.root");
    TFile *target  = new TFile( outputFile,"update" );
    histBDT->Write();

    target->Close();
	std::cout << "--- Created root file: "<<outputFile<<" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;

}
