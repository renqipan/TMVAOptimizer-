void plot_pan(){
TFile*  file1=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA.root");
TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ttHgg_0PM_lep_new_2018_bdt.root");
TFile* file3=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ozgur.root");
TFile*  file4=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA2018.root");

TTree* test=(TTree*)file1->Get("TestTree");
TTree* train=(TTree*)file1->Get("TrainTree");
float test_BDT,train_BDT,test_weight,train_weight;
test->SetBranchAddress("BDT",&test_BDT);
train->SetBranchAddress("BDT",&train_BDT);
test->SetBranchAddress("weight",&test_weight);
train->SetBranchAddress("weight",&train_weight);
int class_test,class_train;
test->SetBranchAddress("classID",&class_test);
train->SetBranchAddress("classID",&class_train);

TTree* test1=(TTree*)file4->Get("TestTree");
TTree* train1=(TTree*)file4->Get("TrainTree");
float test_BDT1,train_BDT1,test_weight1,train_weight1;
test1->SetBranchAddress("BDT",&test_BDT1);
train1->SetBranchAddress("BDT",&train_BDT1);
test1->SetBranchAddress("weight",&test_weight1);
train1->SetBranchAddress("weight",&train_weight1);
int class_test1,class_train1;
test1->SetBranchAddress("classID",&class_test1);
train1->SetBranchAddress("classID",&class_train1);
TH1F* hp=new TH1F("hp","BDT of Pan",100,-0.2,0.2);
TH1F* hm=new TH1F("hm","BDT of Meng",100,-0.2,0.2);
TH1F* hc=new TH1F("hc","BDT of Pan-2018",100,-0.2,0.2);

for(int i=0;i<test->GetEntries();i++){
	test->GetEntry(i);
	if(class_test==0)
		hp->Fill(test_BDT,test_weight);
}
for(int j=0;j<train->GetEntries();j++){
	train->GetEntry(j);
    if(class_train==0)
		hp->Fill(train_BDT,train_weight );
}

for(int i=0;i<test1->GetEntries();i++){
	test1->GetEntry(i);
    if(class_test1==0)
		hc->Fill(test_BDT1,test_weight1);
}
for(int j=0;j<train1->GetEntries();j++){
	train1->GetEntry(j);
	if(class_train1==0)
		hc->Fill(train_BDT1,train_weight1 );
}

float scale_hp=1.0/hp->Integral("width");
hp->Scale(scale_hp);
hp->SetLineColor(2);
float scale_hc=1.0/hc->Integral("width");
hc->Scale(scale_hc);
hc->SetLineColor(3);

TTree* treeMeng=(TTree*)file2->Get("tth_13TeV_all");
treeMeng->Draw("BDTG>>hm","weight");
gStyle->SetOptStat(0);
hm->SetLineColor(4);
hm->GetXaxis()->SetTitle("BDT output");
hm->GetYaxis()->SetTitle("Rates"); 
float scale=1.0/hm->Integral("width");
hm->Scale(scale);
hm->Draw("hist");
hp->Draw("histSame");
hc->Draw("histSame");

TLegend leg1(.7,.7,.9,.9);
leg1.SetFillColor(0);
leg1.AddEntry(hp,"Pan-3yr.");
leg1.AddEntry(hm,"Meng-2018");
leg1.AddEntry(hc,"Pan-2018");
leg1.DrawClone("Same");
gPad->Print("pan_lep.png");

}