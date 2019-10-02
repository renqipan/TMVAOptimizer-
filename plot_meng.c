void plot_meng(){
TFile*  file1=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA.root");
TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ttHgg_0PM_lep_new_2018_bdt.root");
TFile* file3=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ozgur.root");

TH1F* oz_ts=(TH1F*)file3->Get("SignalValuesTest");
TH1F* oz_tr=(TH1F*)file3->Get("SignalValuesTra");
auto oz_sum=new TH1F(*oz_tr);
oz_sum->Add(oz_ts,1.0);
float scale_oz=1.0/oz_sum->Integral("width");
oz_sum->Scale(scale_oz);
oz_sum->SetLineColor(2);

TH1F* train_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_Train_S");
TH1F* test_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_S");
//train_S->SetLineColor(1);
//test_S->SetLineColor(2);
auto pan3=new TH1F(*test_S);
pan3->Add(train_S,1.);
float scale3=1.0/pan3->Integral("width");
pan3->Scale(scale3);
pan3->SetLineColor(3);

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
oz_sum->Draw("histSame");
//train_S->Draw("histsame");
//test_S->Draw("histSame");
cout<<"pan:nbins="<<nbins<<endl;
cout<<"ozgur:nbins="<<oz_sum->GetNbinsX()<<endl;
cout<<"meng:nbins="<<hm->GetNbinsX()<<endl;

TLegend leg1(.7,.7,.9,.9);
leg1.SetFillColor(0);
leg1.AddEntry(pan3,"Pan-3yr.");
leg1.AddEntry(hm,"Meng");
leg1.AddEntry(oz_sum,"Ozgur");
leg1.DrawClone("Same");
gPad->Print("pan_meng1.png");
}
