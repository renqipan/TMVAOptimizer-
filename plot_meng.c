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
TH1F* hp=new TH1F("hpp","BDT of Pan",100,-0.2,0.2);
TH1F* hm=new TH1F("hmm","BDT of Meng",100,-0.2,0.2);

for(int i=0;i<test->GetEntries();i++){
	test->GetEntry(i);hp->Fill(test_BDT,test_weight);
}
for(int j=0;j<train->GetEntries();j++){
	train->GetEntry(j);hp->Fill(train_BDT,train_weight );
}

TTree* treeMeng=(TTree*)file2->Get("tth_13TeV_all");
treeMeng->Draw("BDTG>>hmm","weight");
auto canvas= new TCanvas();// not necessary
gStyle->SetOptStat(0);
hp->SetLineColor(3);
hm->SetLineColor(4);
hm->GetXaxis()->SetTitle("BDT output");
hm->GetYaxis()->SetTitle("Rates"); 
hm->DrawNormalized("hist");
hp->DrawNormalized("histSame");
TLegend leg(.7,.7,.9,.9);
leg.SetFillColor(0);
leg.AddEntry(hp,"Pan");
leg.AddEntry(hm,"Meng");
leg.DrawClone("Same");

gPad->Print("pan_meng.png");

}
