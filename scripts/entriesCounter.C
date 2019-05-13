{
	std::vector<float> entrieStorage;
	TH1F *h1 = new TH1F("h1", "entries", 300,170000,174000);
	gStyle->SetStatFormat("6.4g");
	int counter=0;
	for (int i=52;i<450;i++){
		if(i%100==0){
			cout<<i<<endl;
		}
		stringstream ss;
		ss<<i;
		string filenum=ss.str();
		string filename=("/mnt/shared/home/lb8075/RadiotherapyBeam/datasets/Field7x7-PS-Gen_Elec/Field-PSA"+filenum+".root").c_str();
		// cout<<filename<<endl;
		TFile *file1=new TFile(filename.c_str());
		if (!file1->IsZombie()){
			TTree* tree1=(TTree*)file1->Get("PhaseSpace");
			// entrieStorage.pushback(tree1->GetEntries());
			h1->Fill(tree1->GetEntries());
			counter++;
		}
	}
	cout<<h1->GetMean()<<"    counter: "<<counter<<endl;
	h1->Draw("hist");
}

