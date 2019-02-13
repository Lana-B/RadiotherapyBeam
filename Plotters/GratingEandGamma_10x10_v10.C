{
	TFile* _file0=new TFile("/storage/lb8075/Test10x10_v10_EonlyEdep.root");
	TFile* _file1=new TFile("/storage/lb8075/Test10x10_v10_GammaOnly_Edep.root");
	TH3F* hist=(TH3F*)_file0->Get("histo");
	TH1F* histy=(TH1F*)hist->ProjectionY("p");
	TH3F* hist1=(TH3F*)_file1->Get("histo");
	TH1F* histy1=(TH1F*)hist1->ProjectionY("p1");
	histy->Draw();
	histy1->Draw();
	histy1->SetLineColor(kRed);
	histy1->Scale(4);
	histy1->Draw("hist");
	histy->Draw("hist same");
	// TH1F* histClone=(TH1F*)histy->Clone();
	// histClone->Add(histy1);
	// histClone->SetLineColor(kGreen);
	// histClone->Draw("hist");
	// histClone->Scale(1/histClone->GetMaximum());
	// histClone->Draw("hist");
	histy->Scale(1.03/histy->GetMaximum());
	histy1->Scale(1/histy1->GetMaximum());

	histy->Draw("hist");
	histy1->Draw("hist same");
}
