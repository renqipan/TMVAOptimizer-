void plot_meng(){
TFile*  file1=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA.root");
TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ttHgg_0PM_lep_new_2018_bdt.root");

TH1F* train_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_Train_S");
TH1F* test_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_S");
train_S->SetLineColor(1);
test_S->SetLineColor(2);
auto pan3=new TH1F(*test_S);
pan3->Add(train_S,1.);
scale3=1.0/pan3->Integral("width");
pan3->Scale(scale3);

int nbins=train_S->GetNbinsX();
TH1F* hm=new TH1F("hm","BDT of Meng",nbins,-0.2,0.2);
TTree* treeMeng=(TTree*)file2->Get("tth_13TeV_all");
treeMeng->Draw("BDTG>>hm","weight");
gStyle->SetOptStat(0);
hm->SetLineColor(4);
hm->GetXaxis()->SetTitle("BDT output");
hm->GetYaxis()->SetTitle("Rates"); 

float scale=1.0/hm->Integral("width");
hm->Scale(scale);
hm->Draw("hist");
pan3->Draw("histSame");
//train_S->Draw("histsame");
//test_S->Draw("histSame");


TLegend leg1(.7,.7,.9,.9);
leg1.SetFillColor(0);
leg1.AddEntry(pan3,"Pan-3yr.");
leg1.AddEntry(hm,"Meng");
leg1.DrawClone("Same");
gPad->Print("pan_meng1.png");
}
