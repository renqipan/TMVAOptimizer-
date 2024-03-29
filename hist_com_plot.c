void hist_com_plot(){
	gStyle->SetOptStat(0);
	TFile* file1=TFile::Open("/afs/cern.ch/user/r/repan/root_file/ozgur_had.root");
	TFile* file2=TFile::Open("/afs/cern.ch/user/r/repan/CMSSW_9_4_0/src/TMVAOptimizer/tth_BDT_powheg_app.root");

	TH1D* train_S=(TH1D*) file1->Get("SignalValuesTra");
	TH1D* train_B=(TH1D*) file1->Get("BackgroundValuesTra");
	TH1D* test_S=(TH1D*) file1->Get("SignalValuesTest");
	TH1D* test_B=(TH1D*) file1->Get("BackgroundValuesTest");
	TH1F* powheg=(TH1F*)file2->Get("MVA_BDT_powheg");	

	train_S->SetLineColor(1);
	train_B->SetLineColor(2);
	test_S->SetLineColor(3);
	test_B->SetLineColor(4);
	powheg->SetLineColor(6);
	float scale=1.0/powheg->Integral("width");
	powheg->Scale(scale);

	//test_B->SetAxisRange(-0.2,0.2);	
	TCanvas* c= new TCanvas();
	train_S->SetTitle("BDT output distribution;Response value;Density");
	test_B->Draw("Hist");
	test_S->Draw("sameHist");
	train_B->Draw("same");
	train_S->Draw("same");

	//powheg->DrawNormalized("same");

	TLegend leg(.7,.7,.9,.9);
	leg.SetFillColor(0);
	leg.AddEntry(train_S,"Train-sig");
	leg.AddEntry(train_B,"Train-bkg");
	leg.AddEntry(test_S,"Test-sig");
	leg.AddEntry(test_B,"Test-bkg");
	//leg.AddEntry(powheg,"apply-powheg");
	leg.DrawClone("Same");

	gPad->Print("hadronic_ozgur.png");
}
