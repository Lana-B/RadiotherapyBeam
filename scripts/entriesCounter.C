{
	std::vector<float> entrieStorage;
	TH1F *h1 = new TH1F("h1", "entries", 300, 136000, 139000);
	for (int i=1;i<200;i++){
		if(i%10==0){
			cout<<i<<endl;
		}
		stringstream ss;
		ss<<i;
		string filenum=ss.str();
		string filename=("/hdfs/user/lb8075/RadiotherapyBeam/Grating/Field5x5-PS-Gen_Elec_v2/Field-PSA"+filenum+".root").c_str();
		// cout<<filename<<endl;
		TFile *file1=new TFile(filename.c_str());
		TTree* tree1=(TTree*)file1->Get("PhaseSpace");
		// cout<<tree1->GetEntries()<<endl;;
		// entrieStorage.pushback(tree1->GetEntries());
		h1->Fill(tree1->GetEntries());
	}

	h1->Draw("hist");
}

