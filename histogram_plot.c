void plot_hist(){
	gStyle->SetOptStat(0);
	TFile* file1=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/bin/output/TMVA.root");
	TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/tth_BDT_powheg_apply.root");

	TH1F* train_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_Train_S");
	TH1F* train_B=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_Train_S");
	TH1F* test_S=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_S");
	TH1F* test_B=(TH1F*) file1->Get("Method_BDT/BDT/MVA_BDT_B");
	TH1F* powheg=(TH1F*)file2->Get("MVA_BDT_powheg");
	TCanvas* c= new TCanvas();
	train_S->SetTitle("BDT output distribution;Response value;Density");
	train_S->Draw();
	train_B->Draw("same");
	test_S->Draw("sameHist");
	test_B->Draw("sameHist");
	powheg->Draw("same");

	TLegend leg(.7,.7,.9,.9);
	leg.SetFillColor(0);
	leg.AddEntry(train_S,"Train-even");
	leg.AddEntry(train_B,"Train-odd");
	leg.AddEntry(test_S,"Test-even");
	leg.AddEntry(test_B,"Test-odd");
	leg.AddEntry(powheg,"powheg");
	leg.DrawClone("Same");

	gPad->Print("add_powheg.png");


}