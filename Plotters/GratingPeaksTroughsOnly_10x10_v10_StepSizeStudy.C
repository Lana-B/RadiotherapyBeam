{
	std::map<string,TFile*> fileMap;
	std::map<string,TH3F*> TH3FMap;
	std::map<string,TH1F*> TH1FMap;

	// const int nFiles=8;
	// std::array<string,nFiles> fileIDs={"Peaks5eM4","Troughs5eM4","Peaks5eM3","Troughs5eM3","Peaks5eM2","Troughs5eM2","Peaks1eM2","Troughs1eM2"};
	// std::array<string,nFiles> fileNames={"/storage/lb8075/Test10x10_v10_PeaksOnly_Edep.root","/storage/lb8075/Test10x10_v10_TroughsOnly_806_Edep.root",
	// "/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp0005_Edep.root","/storage/lb8075/Test10x10_v10_TroughsOnlyEOnly_SSp0005_Edep.root",
	// "/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp005_Edep.root","/storage/lb8075/Test10x10_v10_TroughsOnlyEOnly_SSp005_Edep.root",
	// "/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp001_Edep.root","/storage/lb8075/Test10x10_v10_TroughsOnlyEOnly_SSp001_Edep.root"};
	// std::array<int,nFiles> jobsCompleted={1000,806,1000,1000,1000,1000,1000,1000};

	// const int nFiles=3;
	// std::array<string,nFiles> fileIDs={"Peaks5eM4","Peaks6eM1"};
	// std::array<string,nFiles> fileNames={"/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp0005_Edep.root","/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp001_Edep.root",
	// "/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp06_Edep.root"};
	// std::array<int,nFiles> jobsCompleted={1000,1000};

	// const int nFiles=2;
	// std::array<string,nFiles> fileIDs={"Big","Small"};
	// std::array<string,nFiles> fileNames={"/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp003_Edep.root",
	// "/storage/lb8075/Test10x10_v10_PeaksOnlyEOnly_SSp003Epi_p0005_Edep.root"};
	// std::array<int,nFiles> jobsCompleted={1000,1000};


	const int nFiles=1;
	std::array<string,nFiles> fileIDs={"Electrons","gammas"};
	std::array<string,nFiles> fileNames={"/storage/lb8075/Field5x5-PS-Input_Elec_v2_Edep.root"};
	std::array<int,nFiles> jobsCompleted={1000};

	gStyle->SetOptStat(0);

	for (int ii=0;ii<fileIDs.size();ii++)
	{
		fileMap[fileIDs[ii].c_str()]=new TFile(fileNames[ii].c_str());
		TH3FMap[fileIDs[ii].c_str()]=(TH3F*)fileMap[fileIDs[ii].c_str()]->Get("histo");
		TH1FMap[fileIDs[ii].c_str()]=(TH1F*)TH3FMap[fileIDs[ii].c_str()]->ProjectionY(fileIDs[ii].c_str());

		TH1FMap[fileIDs[ii].c_str()]->Draw();
		TH1FMap[fileIDs[ii].c_str()]->Rebin(2);
		TH1FMap[fileIDs[ii].c_str()]->Scale(1000.0/jobsCompleted[ii]);
	}
	TLegend* legend = new TLegend(0.4,0.25,0.6,0.45);

	for (int ii=0;ii<fileIDs.size();ii++)
	{
		TH1FMap[fileIDs[ii].c_str()]->SetLineColor(ii+2);
		if(ii==0){
			TH1FMap[fileIDs[ii].c_str()]->Draw("");
		}
		else{
			TH1FMap[fileIDs[ii].c_str()]->Draw("same");
		}
		legend->AddEntry(TH1FMap[fileIDs[ii].c_str()],fileIDs[ii].c_str(),"l");
		cout<<TH1FMap[fileIDs[ii].c_str()]->Integral()<<endl;
	}
	legend->Draw();
}
