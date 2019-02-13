/////Code for fitting the amplitude to the grating patterns ////
//
//
//

Double_t FitFunc(Double_t *x, Double_t *par) {
//***********************************************//

    Double_t fitval=(par[0]+par[1]*x[0]+par[2]*x[0]*x[0]+par[3]*sin(par[4]*(x[0]+par[5])));

    
    return fitval;
} 

Double_t FitSine(Double_t *x, Double_t *par){
	Double_t fitval=par[0]+par[1]*sin((par[2]*x[0])+par[3]);
	return fitval;
}

Double_t FitPoly(Double_t *x, Double_t *par) {
//***********************************************//

    Double_t fitval=(par[0]+par[1]*x[0]+par[2]*x[0]*x[0]);
    
    return fitval;
} 


void AmplitudeFitter()
{
	gStyle->SetOptStat(0);
	int nParams = 4;
	int projXmin;
	int projXmax;
	int projYmin;
	int projYmax;

	std::vector<string> fileNames;
	std::vector<float> PtoP;
	std::vector<float> PHeight;	
	std::vector<float> PtoPErr;
	std::vector<float> PHeightErr;
	std::vector<float> Pconst;
	std::vector<float> Pxconst;	
	std::vector<float> Px2const;	
	std::vector<float> PconstErr;
	std::vector<float> PxconstErr;
	std::vector<float> Px2constErr;

	std::vector<float> PtoPUP;
	std::vector<float> PHeightUP;	
	std::vector<float> PtoPErrUP;
	std::vector<float> PHeightErrUP;
	std::vector<float> PconstUP;
	std::vector<float> PxconstUP;	
	std::vector<float> Px2constUP;	
	std::vector<float> PconstErrUP;
	std::vector<float> PxconstErrUP;
	std::vector<float> Px2constErrUP;
	TCanvas cFunc;


	projXmin = 0;
	projXmax = 167;
	projYmin = 26;
	projYmax = 187;

	fileNames.push_back("/storage/lb8075/Grating/grating400micron3x3VacuumWorld_Edep.root");


	TFile * _file0;

	for(int fileIter=0; fileIter<fileNames.size(); fileIter++){
		_file0 = new TFile(fileNames[fileIter].c_str());

		TH3D * outdn = (TH3D*)_file0->Get("histo");
		TH1D * py = (TH1D*)outdn->ProjectionY();
		TH1D * px = (TH1D*)outdn->ProjectionX();

		TCanvas *cpx = new TCanvas();
		px->Draw();

		TCanvas *cpy = new TCanvas();
		py->Draw();

		cpx->SaveAs("xprog.png");
		cpy->SaveAs("yprog.png");

		// //full window in py
		TH1D * pyWindow = outdn->ProjectionY("py", projXmin, projXmax);
		// float av1, av2, av3;
		// std::vector<Int_t> vecPeaks;
		// std::vector<Int_t> vecTroughs;
		// std::vector<float> vecxVals;
		// std::vector<float> vecyVals;
		// std::vector<float> vecyValsReal;

		//window in py where active area of detector is working
		TH1F *hSubset = new TH1F("hSub","hSub",projYmax-projYmin+1,projYmin,projYmax);
		for(int sub=projYmin; sub<projYmax+2;sub++){
			int subB = sub-projYmin;
			hSubset->SetBinContent(subB, pyWindow->GetBinContent(sub));
		}

		//root peak finder
		// TCanvas cSubset;
		// hSubset->Draw("hist p l");
		// hSubset->ShowPeaks();
		// cSubset.SaveAs("subset.png");

		// // TSpectrum *specSub = new TSpectrum(); 
		// // int num = specSub->Search(hSubset);
		// // specSub->Search(hSubset);

		// // Double_t *xpeakSub = specSub->GetPositionX();
		// // Double_t *ypeakSub = specSub->GetPositionY();	

		// // std::vector<float> ypeakheights;
		// // TCanvas cheights;
		// // TH1D * hheights = new TH1D("y","y",25,0,100000000);
		// // // for(int m=0; m<vecyValsReal.size()-1;m++){
		// // // 	// std::cout<<abs(vecyValsReal[m]-vecyValsReal[m+1])<<std::endl;
		// // // 		hheights->Fill( abs(vecyValsReal[m]-vecyValsReal[m+1]));
		// // // }
		// // for(int m=0;m<num-1;m++){
		// // 	// std::cout<<xpeakSub[m]<<std::endl;
		// // 	int peakpos1 = round((xpeakSub[m])/1.0);
		// // 	// std::cout<<peakpos1<<std::endl;
		// // 	int peakpos2 = round((xpeakSub[m+1])/1.0);
		// // 	float peak1 = hSubset->GetBinContent(peakpos1);
		// // 	float peak2 = hSubset->GetBinContent(peakpos2);
		// // 	int troughPos  = round((xpeakSub[m]-xpeakSub[m+1])/2);
		// // 	float trough = hSubset->GetBinContent(troughPos);
		// // 	// std::cout<<peak1<<"  "<<peak2<<"  "<<trough<<std::endl;
		// // 	// float height = peak2-trough;
		// // 	float height = ypeakSub[m+1]-trough;
		// // 	// std::cout<<height<<std::endl;
		// // 	hheights->Fill( height);
		// // }
		// // hheights->Draw();

		TCanvas *cDP= new TCanvas("cDP","cDP",400,400);
	    gPad->SetFillColor(10);
	    cDP->SetTopMargin(.1);
	    cDP->SetBottomMargin(.12);
	    cDP->SetRightMargin(.1);//.15
	    cDP->SetLeftMargin(.13);

		hSubset->Draw();
		TF1 *func2=new TF1("fit",FitSine,projYmin,projYmax,nParams);
		func2->SetLineColor(kRed);
		func2->SetLineWidth(2);
		func2->SetLineStyle(7);
	    func2->SetParNames("const","Amp","width","shift");
		// func2->SetParameter(0,2834);
		func2->SetParameter(1,135);
		func2->SetParameter(2,0.47);
		hSubset->SetTitle("");
		hSubset->Fit("fit"," ","SAME",projYmin,projYmax);
		cDP->SaveAs("fittedOutput3x3.pdf");

		//fit 2nd order polynomial + sin function 
		// TF1 *func2=new TF1("fit",FitFunc,projYmin,projYmax,nParams);
		// //    func2->SetParameters(60,2000,200);
		// func2->SetLineColor(kRed);
		// func2->SetLineWidth(2);
		// func2->SetLineStyle(7);
		// func2->SetParameter(0,165000000);
		// func2->SetParameter(4,0.21);
		// // func2->SetParameter(5,0);
		// func2->SetParameter(3,5000000);
	 //    // func2->SetParNames("const","lin","quad","sin");

		// func2->SetParameter(0,-4.26656e+08);
		// func2->SetParameter(1, 4.64782e+05);
		// func2->SetParameter(2,-8.82595e+01);
		// func2->GetYaxis()->SetRangeUser(144000000,156000000); 
		// // func2->GetYaxis()->SetNoExponent(kFALSE); 
		// // TGaxis::SetMaxDigits(3);
		// hSubset->SetTitle("");
		// hSubset->GetXaxis()->SetTitle("Pixel Number");
		// hSubset->GetYaxis()->SetTitle("ADC counts");
		// hSubset->GetYaxis()->SetTitleOffset(1.45);
		// hSubset->GetXaxis()->SetNdivisions(3);

		// hSubset->Fit("fit"," ","SAME",projYmin,projYmax);
		// hSubset->SetLineWidth(1);
		// hSubset->SetMarkerStyle(23);
	
		// TLegend *leg = new TLegend(0.15, 0.78, 0.3, 0.9);
		// // leg->SetHeader("Grating","C"); // option "C" allows to center the header
		// leg->SetFillColor(10);
		// leg->AddEntry(hSubset, "Data","l");
		// leg->AddEntry(func2, "Fit","l");
		// leg->Draw();


		// cDP->SaveAs(("sinpeaks"+fileNames[fileIter]+".pdf").c_str());


		// cFunc.cd();
		// TF1 *funcFile1=new TF1("f1",FitPoly,projYmin,projYmax,nParams);
		// funcFile1->SetParameter(0,func2->GetParameter(0)-func2->GetParameter(3));
		// funcFile1->SetParameter(1,func2->GetParameter(1));
		// funcFile1->SetParameter(2,func2->GetParameter(2));
		// funcFile1->SetTitle("");
		// if(fileIter==0){
		// 	funcFile1->GetYaxis()->SetRangeUser(130000000,190000000);
		// 	funcFile1->Draw();
		// } 
		// else{
		// 	funcFile1->SetLineColor(kBlue);
		// 	funcFile1->Draw("same");
		// } 
		// cFunc.SaveAs("baseline.pdf");
		// 	PHeightUP.push_back(abs(2*func2->GetParameter(3)));
		// 	PHeightErrUP.push_back(2*func2->GetParError(3));
		// 	PtoPUP.push_back(2*TMath::Pi()*14.5/func2->GetParameter(4));
		// 	PtoPErrUP.push_back((2*TMath::Pi()*14.5/func2->GetParameter(4))*(func2->GetParError(4)/func2->GetParameter(4)));
		// 	PconstUP.push_back(func2->GetParameter(0));
		// 	PxconstUP.push_back(func2->GetParameter(1));
		// 	Px2constUP.push_back(func2->GetParameter(2));
		// 	PconstErrUP.push_back(func2->GetParError(0));
		// 	PxconstErrUP.push_back(func2->GetParError(1));
		// 	Px2constErrUP.push_back(func2->GetParError(2));

	}

	// const int npoints = PHeight.size();
	// float fieldSize[npoints];
	// float fieldSizeErr[npoints];


	// for(int heights=0; heights<npoints; heights++){
	// 	std::cout<<"heights:  "<<PHeight[heights]<<"  heightsErr:  "<<PHeightErr[heights]<<"  widths: "<<PtoP[heights]<<"  widthsErr: "<<PtoPErr[heights]<<std::endl;
	// 	fieldSize[heights] = (heights+3);
	// 	fieldSizeErr[heights] = 0;
	// }

	// const int npointsUP = PHeightUP.size();
	// float fieldSizeUP[npointsUP];
	// float fieldSizeErrUP[npointsUP];


	// for(int heights=0; heights<npointsUP; heights++){
	// 	std::cout<<"heights:  "<<PHeightUP[heights]<<"  widths: "<<PtoPUP[heights]<<std::endl;
	// 	if(heights<2){
	// 		fieldSizeUP[heights] = (heights+3);
	// 	}
	// 	else fieldSizeUP[heights] = (heights+4);

	// 	fieldSizeErrUP[heights] = 0;
	// }


	// TCanvas c1("c1","c1",400,400);
 //    gPad->SetFillColor(10);
 //    c1.SetTopMargin(.1);
 //    c1.SetBottomMargin(.12);
 //    c1.SetRightMargin(.1);//.15
 //    c1.SetLeftMargin(.13);

	// TGraphErrors * down = new TGraphErrors(PHeight.size(),fieldSize, &PHeight[0],fieldSizeErr, &PHeightErr[0]);
	// TGraphErrors * up = new TGraphErrors(PHeightUP.size(),fieldSizeUP, &PHeightUP[0],fieldSizeErrUP, &PHeightErrUP[0]);
	// down->GetXaxis()->SetTitle("X*X field size");
	// down->GetYaxis()->SetNoExponent(kFALSE); 
	// TGaxis::SetMaxDigits(3);
	// down->GetYaxis()->SetTitle("Peak height above baseline");
	// down->GetYaxis()->SetTitleOffset(1.2);
	// down->GetXaxis()->SetTitleSize(0.04);
	// down->GetYaxis()->SetTitleSize(0.04);
	// down->SetTitle("");
	// up->SetLineColor(kRed);
	// down->SetLineColor(kBlack);
	// down->Draw("AP");
	// // up->Draw("AP same");
	// c1.SaveAs("Heights.pdf");

	// TCanvas c2("c2","c2",400,400);
 //    gPad->SetFillColor(10);
 //    c2.SetTopMargin(.1);
 //    c2.SetBottomMargin(.12);
 //    c2.SetRightMargin(.1);//.15
 //    c2.SetLeftMargin(.13);	
	// TGraphErrors * down2 = new TGraphErrors(PHeight.size(),fieldSize, &PtoP[0],fieldSizeErr, &PtoPErr[0]);
	// TGraphErrors * up2 = new TGraphErrors(PHeightUP.size(),fieldSizeUP, &PtoPUP[0],fieldSizeErrUP, &PtoPErrUP[0]);
	// down2->GetXaxis()->SetTitle("X*X field size");
	// down2->GetYaxis()->SetTitle("Pitch (#mum)");
	// down2->GetYaxis()->SetTitleOffset(1.55);
	// down2->GetXaxis()->SetTitleSize(0.04);
	// down2->GetYaxis()->SetTitleSize(0.04);

	// // down2->GetYaxis()->SetNoExponent(kFALSE); 

	// down2->SetTitle("");
	// down2->Draw("AP");
	// up2->SetLineColor(kRed);
	// down2->SetLineColor(kBlack);

	// // up2->Draw("AP same");
	// c2.SaveAs("Pitch.pdf");

}
