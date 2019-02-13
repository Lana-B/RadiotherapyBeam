void BinContentChecker(){
	TFile* fileEdep = TFile::Open("Gratingoutput-gamma1-Edep.root");
	TFile* fileEdepUnc = TFile::Open("Gratingoutput-gamma1-Edep-Uncertainty.root");
	TFile* fileHits = TFile::Open("Gratingoutput-gamma1-NbOfHits.root");
	TH3D* Edep3D = (TH3D*)fileEdep->Get("histo;167");
	TH3D* EdepUnc3D = (TH3D*)fileEdepUnc->Get("histo;167");
	TH3D* Hits = (TH3D*)fileHits->Get("histo;167");
	for (int i=0; i<234;i++){
		cout<<i<<" Hits: "<<Hits->GetBinContent(82,i,1)<<"  Unc: "<<EdepUnc3D->GetBinContent(82,i,1)<<"  Edep: "<<Edep3D->GetBinContent(82,i,1)<<endl;
	} 

}