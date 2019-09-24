void newRootFile(){
	/*TChain *tc= new TChain("tthLeptonicTagDumper/trees/tth_13TeV_all");
	tc->Add("ttHiggs0PToGG1.root");
	tc->Add("ttHiggs0PToGG2.root");
	tc->Add("ttHiggs0MToGG1.root");
	tc->Add("ttHiggs0MToGG2.root");
  */
  string fileName[3]={"ttHiggs0PToGG1.root","ttHiggs0PToGG2.root","ttHToGG_M125_13TeV_powheg.root"};
  for(int kk=0;kk<3;kk++){
    TFile *sigFile = new TFile(fileName[kk].c_str(),"update");
    TTree *tc=(TTree *) sigFile->Get("tthLeptonicTagDumper/trees/tth_13TeV_all");
  	
    float diph_pt,mass,diph_cosphi,diph_rapidity;
    float ele1_pt,ele1_eta,ele1_phi,ele1_energy;
    float muon1_pt,muon1_eta,muon1_phi,muon1_energy;
    float n_ele,n_muons,n_jets;
    tc->SetBranchAddress("dipho_sumpt",&diph_pt);
    tc->SetBranchAddress("mass",&mass);
    tc->SetBranchAddress("dipho_cosphi",&diph_cosphi);
    tc->SetBranchAddress("dipho_rapidity",&diph_rapidity);
    tc->SetBranchAddress("ele1_pt",&ele1_pt);
    tc->SetBranchAddress("ele1_energy",&ele1_energy);
    tc->SetBranchAddress("ele1_phi",&ele1_phi);
    tc->SetBranchAddress("ele1_eta",&ele1_eta);
    tc->SetBranchAddress("muon1_energy",&muon1_energy);
    tc->SetBranchAddress("muon1_phi",&muon1_phi);
    tc->SetBranchAddress("muon1_eta",&muon1_eta);
    tc->SetBranchAddress("muon1_pt",&muon1_pt);
    tc->SetBranchAddress("n_ele",&n_ele);
    tc->SetBranchAddress("n_muons",&n_muons);
    tc->SetBranchAddress("n_jets",&n_jets);
    float diPhoPtoM,diPhoCosPhi,diPhoY;
    float lepPt_1,lepEta_1,lepPhi_1,lepE_1,nLep;
    TBranch* PtoM=tc->Branch("diPhoPtoM",&diPhoPtoM,"diPhoPtoM/F");
    TBranch* cosphi=tc->Branch("diPhoCosPhi",&diph_cosphi,"diPhoCosPhi/F");
    TBranch* phoY=tc->Branch("diPhoY",&diph_rapidity,"diPhoY/F");
    TBranch* leppt=tc->Branch("lepPt_1",&lepPt_1,"lepPt_1/F");
    TBranch* lepE=tc->Branch("lepE_1",&lepE_1,"lepE_1/F");
    TBranch* lepPhi=tc->Branch("lepPhi_1",&lepPhi_1,"lepPhi_1/F");
    TBranch* lepEta=tc->Branch("lepEta_1",&lepEta_1,"lepEta_1/F");
    TBranch* nlep=tc->Branch("nLep",&nLep,"nLep/F");
    TBranch* njets=tc->Branch("nJetsBl",&n_jets,"nJetsBl/F");

    float jet_pt1,jet_eta1,jet_phi1,jet_bdiscriminant1,jet_energy1;
    tc->SetBranchAddress("jet_pt1",&jet_pt1);
    tc->SetBranchAddress("jet_eta1",&jet_eta1);
    tc->SetBranchAddress("jet_phi1",&jet_phi1);
    tc->SetBranchAddress("jet_energy1",&jet_energy1);
    tc->SetBranchAddress("jet_bdiscriminant1",&jet_bdiscriminant1);
    TBranch* jet1pt=tc->Branch("jetPt_1",&jet_pt1,"jetPt_1/F");
    TBranch* jet1eta=tc->Branch("jetEta_1",&jet_eta1,"jetEta_1/F");
    TBranch* jet1E=tc->Branch("jetE_1",&jet_energy1,"jetE_1/F");
    TBranch* jet1phi=tc->Branch("jetPhi_1",&jet_phi1,"jetPhi_1/F");
    TBranch* btag1=tc->Branch("btag_1",&jet_bdiscriminant1,"btag_1/F");

     float jet_pt2,jet_eta2,jet_phi2,jet_bdiscriminant2,jet_energy2;
    tc->SetBranchAddress("jet_pt2",&jet_pt2);
    tc->SetBranchAddress("jet_eta2",&jet_eta2);
    tc->SetBranchAddress("jet_phi2",&jet_phi2);
    tc->SetBranchAddress("jet_energy2",&jet_energy2);
    tc->SetBranchAddress("jet_bdiscriminant2",&jet_bdiscriminant2);
    TBranch* jet2pt=tc->Branch("jetPt_2",&jet_pt2,"jetPt_2/F");
    TBranch* jet2eta=tc->Branch("jetEta_2",&jet_eta2,"jetEta_2/F");
    TBranch* jet2E=tc->Branch("jetE_2",&jet_energy2,"jetE_2/F");
    TBranch* jet2phi=tc->Branch("jetPhi_2",&jet_phi2,"jetPhi_2/F");
    TBranch* btag2=tc->Branch("btag_2",&jet_bdiscriminant2,"btag_2/F"); 

    float jet_pt3,jet_eta3,jet_phi3,jet_bdiscriminant3,jet_energy3;
    tc->SetBranchAddress("jet_pt3",&jet_pt3);
    tc->SetBranchAddress("jet_eta3",&jet_eta3);
    tc->SetBranchAddress("jet_phi3",&jet_phi3);
    tc->SetBranchAddress("jet_energy3",&jet_energy3);
    tc->SetBranchAddress("jet_bdiscriminant3",&jet_bdiscriminant3);
    TBranch* jet3pt=tc->Branch("jetPt_3",&jet_pt3,"jetPt_3/F");
    TBranch* jet3eta=tc->Branch("jetEta_3",&jet_eta3,"jetEta_3/F");
    TBranch* jet3E=tc->Branch("jetE_3",&jet_energy3,"jetE_3/F");
    TBranch* jet3phi=tc->Branch("jetPhi_3",&jet_phi3,"jetPhi_3/F");
    TBranch* btag3=tc->Branch("btag_3",&jet_bdiscriminant3,"btag_3/F");	

     float jet_pt4,jet_eta4,jet_phi4,jet_bdiscriminant4,jet_energy4;
    tc->SetBranchAddress("jet_pt4",&jet_pt4);
    tc->SetBranchAddress("jet_eta4",&jet_eta4);
    tc->SetBranchAddress("jet_phi4",&jet_phi4);
    tc->SetBranchAddress("jet_energy4",&jet_energy4);
    tc->SetBranchAddress("jet_bdiscriminant4",&jet_bdiscriminant4);
    TBranch* jet4pt=tc->Branch("jetPt_4",&jet_pt4,"jetPt_4/F");
    TBranch* jet4eta=tc->Branch("jetEta_4",&jet_eta4,"jetEta_4/F");
    TBranch* jet4E=tc->Branch("jetE_4",&jet_energy4,"jetE_4/F");
    TBranch* jet4phi=tc->Branch("jetPhi_4",&jet_phi4,"jetPhi_4/F");
    TBranch* btag4=tc->Branch("btag_4",&jet_bdiscriminant4,"btag_4/F");

     float jet_pt5,jet_eta5,jet_phi5,jet_bdiscriminant5,jet_energy5;
    tc->SetBranchAddress("jet_pt5",&jet_pt5);
    tc->SetBranchAddress("jet_eta5",&jet_eta5);
    tc->SetBranchAddress("jet_phi5",&jet_phi5);
    tc->SetBranchAddress("jet_energy5",&jet_energy5);
    tc->SetBranchAddress("jet_bdiscriminant5",&jet_bdiscriminant5);
    TBranch* jet5pt=tc->Branch("jetPt_5",&jet_pt5,"jetPt_5/F");
    TBranch* jet5eta=tc->Branch("jetEta_5",&jet_eta5,"jetEta_5/F");
    TBranch* jet5E=tc->Branch("jetE_5",&jet_energy5,"jetE_5/F");
    TBranch* jet5phi=tc->Branch("jetPhi_5",&jet_phi5,"jetPhi_5/F");
    TBranch* btag5=tc->Branch("btag_5",&jet_bdiscriminant5,"btag_5/F");
     float jet_pt6,jet_eta6,jet_phi6,jet_bdiscriminant6,jet_energy6;
    tc->SetBranchAddress("jet_pt6",&jet_pt6);
    tc->SetBranchAddress("jet_eta6",&jet_eta6);
    tc->SetBranchAddress("jet_phi6",&jet_phi6);
    tc->SetBranchAddress("jet_energy6",&jet_energy6);
    tc->SetBranchAddress("jet_bdiscriminant6",&jet_bdiscriminant6);
    TBranch* jet6pt=tc->Branch("jetPt_6",&jet_pt6,"jetPt_6/F");
    TBranch* jet6eta=tc->Branch("jetEta_6",&jet_eta6,"jetEta_6/F");
    TBranch* jet6E=tc->Branch("jetE_6",&jet_energy6,"jetE_6/F");
    TBranch* jet6phi=tc->Branch("jetPhi_6",&jet_phi6,"jetPhi_6/F");
    TBranch* btag6=tc->Branch("btag_6",&jet_bdiscriminant6,"btag_6/F");
  	Int_t nentries = (Int_t)tc->GetEntries();

     for (Int_t ii=0; ii<nentries; ii++) {
     	tc->GetEntry(ii);
      diPhoPtoM=diph_pt/mass;
      lepPt_1=ele1_pt>muon1_pt? ele1_pt:muon1_pt;
      lepEta_1=ele1_pt>muon1_pt? ele1_eta:muon1_eta;
      lepPhi_1=ele1_pt>muon1_pt? ele1_phi:muon1_phi;
      lepE_1=ele1_pt>muon1_pt? ele1_energy:muon1_energy;
      nLep=n_ele+n_muons;

       if(ii%10000==0)
         { cout<<nLep<<" "<<diPhoPtoM<<" "<<lepPhi_1<<" "<<lepE_1<<endl;}
    // 	 tc->Fill();
       PtoM->Fill(); 
       cosphi->Fill();
       phoY->Fill();
       lepE->Fill();
       leppt->Fill();
       lepPhi->Fill();
       lepEta->Fill();
       nlep->Fill();
       njets->Fill();
       jet1pt->Fill();
       jet1phi->Fill();
       jet1eta->Fill();
       jet1E->Fill();
       btag1->Fill(); 
       jet2pt->Fill();
       jet2phi->Fill();
       jet2eta->Fill();
       jet2E->Fill();
       btag2->Fill(); 
       jet3pt->Fill();
       jet3phi->Fill();
       jet3eta->Fill();
       jet3E->Fill();
       btag3->Fill();
       jet4pt->Fill();
       jet4phi->Fill();
       jet4eta->Fill();
       jet4E->Fill();
       btag4->Fill();
       jet5pt->Fill();
       jet5phi->Fill();
       jet5eta->Fill();
       jet5E->Fill();
       btag5->Fill();
       jet6pt->Fill();
       jet6phi->Fill();
       jet6eta->Fill();
       jet6E->Fill();
       btag6->Fill();     
  } 
      tc->Write("",TObject::kOverwrite); // save only the new version of the tree
      auto branches=tc->GetListOfBranches(); // the retun type is TObjectArray *
      cout<<fileName[kk]<<" has been editted."<<endl;
      for(int j=0;j<branches->GetEntries();j++){
      string	branchName=branches->At(j)->GetName();
      	if(branchName=="diPhoPtoM")
      		cout<<"the variable diPhoPtoM has been writen to the root file."<<endl;
      	if(branchName=="nLep")
      		cout<<"the variable nLep has been writen to the root file."<<endl;
      	if(branchName=="diPhoCosPhi")
      		cout<<"the variable diPhoCosPhi has been writen to the root file."<<endl;
        if(branchName=="jet_pt1")
          branchName="jetPt_1";
        if(branchName=="jet_eta1")
          branchName="jetEta_1";
       }
       cout<<"the number of total events is "<<tc->GetEntries()<<endl;
      sigFile->Close();
}

}