{
	gStyle->SetOptStat(0);
	TFile* _file0=new TFile("/storage/lb8075/Test10x10_v10_PeaksOnly_Edep.root"); //1000jobs
	TFile* _file1=new TFile("/storage/lb8075/Test10x10_v10_TroughsOnly_806_Edep.root"); //806 jobs
	TH3F* hist=(TH3F*)_file0->Get("histo");
	TH1F* histy=(TH1F*)hist->ProjectionY("p");
	TH3F* hist1=(TH3F*)_file1->Get("histo");
	TH1F* histy1=(TH1F*)hist1->ProjectionY("p1");
	histy->Draw();
	histy1->Draw();
	histy1->SetLineColor(kRed);
	histy1->Scale(1000.0/806);
	histy1->Draw("hist");
	histy->Draw("hist same");

	TLegend* legend = new TLegend(0.1,0.1,0.3,0.25);
	legend->AddEntry(histy,"Peaks","l");
	legend->AddEntry(histy1,"Troughs","l");
	legend->Draw();

	Double_t yint=histy->Integral(65,171);
	Double_t y1int=histy1->Integral(65,171);
	std::cout<<"peaks:"<<yint<<"  troughs:"<<y1int<<"  nbins:"<<histy->GetMaximumBin()<<"  ratio"<<yint/y1int<<std::endl;
}
