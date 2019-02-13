{
	TFile * inFile = new TFile("/hdfs/user/lb8075/RadiotherapyBeam/211117_gammaBeamAtPillar/output-gamma98-Edep.root");
	TH3D* inHist = (TH3D*) inFile->Get("histo;100");

	int nEntries  =inHist->GetEntries();
	double sumOfSquares = 0;
	double  nDeposits = 0;
	cout<<"Entries: "<<nEntries<<endl;

	for (int i=0; i<nEntries; i++)
	{
		if (inHist->GetBinContent(i)==0){
			continue;
		}
		else{
			sumOfSquares+= ( (inHist->GetBinContent(i)) * (inHist->GetBinContent(i)));
			nDeposits++;
	                cout<<inHist->GetBinContent(i)<<endl;

		}
	}

	nthRoot = 1.0/nDeposits;
	double result = pow(sumOfSquares,nthRoot);
	cout<<"Sigma on measurement = "<<result<<" on "<<nDeposits<<" deposits"<<" with a sumofSquareErr of "<<sumOfSquares<<" and a root of "<<nthRoot<<endl;
}
