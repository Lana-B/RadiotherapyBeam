{
	gStyle->SetOptStat(0);
	TFile* _file0e=new TFile("/storage/lb8075/Test10x10_v10_PeaksOnly_Edep.root"); //1000jobs
	TFile* _file1e=new TFile("/storage/lb8075/Test10x10_v10_TroughsOnly_806_Edep.root"); //806 jobs
	TFile* _file0=new TFile("/storage/lb8075/Test10x10_v10_PeaksOnlyGamma_Edep.root"); //1000jobs
	TFile* _file1=new TFile("/storage/lb8075/Test10x10_v10_TroughsOnlyGamma_Edep.root"); //1000 jobs
	TH3F* hist=(TH3F*)_file0->Get("histo");
	TH1F* histy=(TH1F*)hist->ProjectionY("p");
	TH3F* hist1=(TH3F*)_file1->Get("histo");
	TH1F* histy1=(TH1F*)hist1->ProjectionY("p1");
	TH3F* histe=(TH3F*)_file0e->Get("histo");
	TH1F* histye=(TH1F*)histe->ProjectionY("pe");
	TH3F* hist1e=(TH3F*)_file1e->Get("histo");
	TH1F* histy1e=(TH1F*)hist1e->ProjectionY("p1e");
	histy->Draw();
	histy1->Draw();
	histye->Draw();
	histy1e->Draw();
	histy1e->Scale(1000.0/806);
	histy1->SetLineColor(kRed);
	histy1e->SetLineColor(kRed);
	histye->SetLineStyle(2);
	histy1e->SetLineStyle(2);


	TH1F* histClone = (TH1F*)histy->Clone();
	TH1F* histClone1 = (TH1F*)histy1->Clone();
	histClone->Add(histye);
	histClone1->Add(histy1e);
	histClone->Draw();
	histClone1->Draw();
	histClone1->SetLineColor(kRed-9);
	histClone->SetLineColor(kBlue-9);
	histClone1->SetLineStyle(3);
	histClone->SetLineStyle(3);
	histClone1->SetLineWidth(4);
	histClone->SetLineWidth(4);

	histClone->Draw("hist");
	histy->Draw("hist same");
	histy1->Draw("hist same");
	histye->Draw("hist same");	
	histy1e->Draw("hist same");
	histClone1->Draw("hist same");

	TLegend* legend = new TLegend(0.4,0.25,0.6,0.45);

	legend->AddEntry(histClone,"300um-g+e","l");
	legend->AddEntry(histClone1,"250um-g+e","l");
	legend->AddEntry(histy,"300um-g","l");
	legend->AddEntry(histy1,"250um-g","l");
	legend->AddEntry(histye,"300um-e","l");
	legend->AddEntry(histy1e,"250um-e","l");
	legend->Draw();

	Double_t yint=histy->Integral(65,171);
	Double_t y1int=histy1->Integral(65,171);
	Double_t yinte=histye->Integral(65,171);
	Double_t y1inte=histy1e->Integral(65,171);
	Double_t yintC=histClone->Integral(65,171);
	Double_t y1intC=histClone1->Integral(65,171);
	std::cout<<"gamma peaks:"<<yint<<"  troughs:"<<y1int<<"  ratio p/t"<<yint/y1int<<"  ratio t/p"<<y1int/yint<<std::endl;
	std::cout<<"e     peaks:"<<yinte<<"  troughs:"<<y1inte<<"  ratio p/t"<<yinte/y1inte<<"  ratio t/p"<<y1inte/yinte<<std::endl;
	std::cout<<"both  peaks:"<<yintC<<"  troughs:"<<y1intC<<"  ratio p/t"<<yintC/y1intC<<"  ratio t/p"<<y1intC/yintC<<std::endl;
	std::cout<<"change in ratio:"<<(y1int/yint)/(y1intC/yintC)<<" or : "<<(y1intC/yintC)/(y1int/yint)<<std::endl;
}
