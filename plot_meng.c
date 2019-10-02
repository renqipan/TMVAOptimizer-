void plot_meng(){
TFile*  file1=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA.root");
TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ttHgg_0PM_lep_new_2018_bdt.root");
TTree* test=(TTree*)file1->Get("TestTree");
TTree* train=(TTree*)file1->Get("TrainTree");
float test_BDT,train_BDT,test_weight,train_weight;
test->SetBranchAddress("BDT",&test_BDT);
train->SetBranchAddress("BDT",&train_BDT);
test->SetBranchAddress("weight",&test_weight);
train->SetBranchAddress("weight",&train_weight);
TH1F* hp=new TH1F("hp","BDT of Pan",100,-0.2,0.2);
TH1F* hm=new TH1F("hm","BDT of Meng",100,-0.2,0.2);

for(int i=0;i<test->GetEntries();i++){
	test->GetEntry(i);hp->Fill(test_BDT,test_weight);
}
for(int j=0;j<train->GetEntries();j++){
	train->GetEntry(j);hp->Fill(train_BDT,train_weight );
}
  hp->DrawNormalized("hist");
  hp->SetLineColor(3);
  gStyle->SetOptStat(0);
  hp->GetXaxis()->SetTitle("BDT output");
  hp->GetYaxis()->SetTitle("Rates"); 

TTree* treeMeng=(TTree*)file2->Get("tth_13TeV_all");
treeMeng->Draw("BDTG"+">>hm","weight");
hm->DrawNormalized("histsame");
hm->SetLineColor(4);

TLegend leg(.7,.7,.9,.9);
leg.SetFillColor(0);
leg.AddEntry(hp,"Pan");
leg.AddEntry(hm,"Meng");
leg.DrawClone("Same");

gPad->Print("pan_meng.png");

}