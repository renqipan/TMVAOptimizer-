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
TH1F* hp=new TH1F("hp","Distribution of BDT output of Sigal",100,-0.2,0.2);
TH1F* hm=new TH1F("hm","Distribution of BDT output of Sigal",100,-0.2,0.2);
TH1F* hc=new TH1F("hc","BDT of Pan-2018",100,-0.2,0.2);

for(int i=0;i<test->GetEntries();i++){
	test->GetEntry(i);
	if(class_test==0)//"0"denotes signal;"1"denotes background
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
hm->GetYaxis()->SetTitle("Density"); 
float scale=1.0/hm->Integral("width");
hm->Scale(scale);
hm->Draw("hist");
hp->Draw("histSame");
//hc->Draw("histSame");

TLegend leg1(.7,.7,.9,.9);
leg1.SetFillColor(0);
leg1.AddEntry(hp,"Pan-3yr.");
leg1.AddEntry(hm,"Meng-2018");
//leg1.AddEntry(hc,"Pan-2018");
leg1.DrawClone("Same");
gPad->Print("pan_lep.png");
///////////////////////////////////////////////////////
TH1F* test_s=new TH1F("test_s","BDT of Pan",100,-0.2,0.2);
TH1F* test_b=new TH1F("test_b","BDT of Pan",100,-0.2,0.2);
TH1F* train_s=new TH1F("train_s","BDT of Pan",100,-0.2,0.2);
TH1F* train_b=new TH1F("train_b","BDT of Pan",100,-0.2,0.2);
test->Draw("BDT>>test_s","weight*(classID==0)");
test->Draw("BDT>>test_b","weight*(classID==1)");
train->Draw("BDT>>train_s","weight*(classID==0)");
train->Draw("BDT>>train_b","weight*(classID==1)");
float scale1=1.0/test_s->Integral("width");
test_s->Scale(scale1);
float scale2=1.0/test_b->Integral("width");
test_b->Scale(scale2);
float scale3=1.0/train_s->Integral("width");
train_s->Scale(scale3);
float scale4=1.0/train_b->Integral("width");
train_b->Scale(scale4);

test_s->SetLineColor(1);
test_s->GetXaxis()->SetTitle("BDT output");
test_s->GetYaxis()->SetTitle("Density"); 
test_b->SetLineColor(2);
train_b->SetLineColor(3);
train_s->SetLineColor(4);
test_s->Draw("hist");
test_b->Draw("histSame");
train_s->Draw("histSame");
train_b->Draw("histSame");

TLegend leg2(.7,.7,.9,.9);
leg2.SetFillColor(0);
leg2.AddEntry(test_s,"Test-Even");
leg2.AddEntry(test_b,"Test-Odd" );
leg2.AddEntry(train_s,"Train-Even");
leg2.AddEntry(train_b,"Train-Odd");
leg2.DrawClone("Same");
gPad->Print("test_train.png");

}