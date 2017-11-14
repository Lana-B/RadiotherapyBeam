{
	//map<string,TF1*> fits1D;
	const Int_t nptn=10;
    Double_t radii[nptn]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
    Double_t fullDiodeVals0[nptn];
    Double_t fullDiodeVals1[nptn];
    Double_t fullDiodeVals2[nptn];
    Double_t fullDiodeVals3[nptn];
    Double_t fullDiodeVals4[nptn];
    Double_t fullDiodeVals5[nptn];
    Double_t fullDiodeVals6[nptn];
    Double_t fullDiodeVals7[nptn];
    Double_t fullDiodeVals8[nptn];
    // Double_t fullDiodeVals7[nptn];
    Double_t radiusPlot[nptn];
    double energyDepCounter=0;
	for(Int_t i=0; i<9; i++){
		TFile *file1;
		if(i==0){
			file1 =new TFile("../outputI/output-gamma-Edep.root"); //no legs side
		}
		else if(i==1){
			file1 =new TFile("../outputJ/output-gamma-Edep.root"); //legs side
		}
		else if(i==2){
			file1 =new TFile("../outputK/output-gamma-Edep.root"); //water side
		}
	    else if(i==3){
			file1 =new TFile("../outputF2/output-gamma-Edep.root"); //water top
		}
	    else if(i==4){
			file1 =new TFile("../outputG2/output-gamma-Edep.root"); //legs top
		}
		else if(i==5){
			file1 =new TFile("../outputH2/output-gamma-Edep.root"); //no legs top
		}
		else if(i==6){
			file1 =new TFile("../outputL/output-gamma-Edep.root"); //legs 20mum top
		}
		else if(i==7){
			file1 =new TFile("../outputM/output-gamma-Edep.root"); //legs 30mum  top
		}
		else if(i==8){
			file1 =new TFile("../outputN/output-gamma-Edep.root"); //legs 100mum top
		}
		TH3D* histo3d = (TH3D*)file1->Get("histo;100");
		double integralValue = histo3d->Integral();
		int nBinsX = histo3d->GetNbinsX();
		int nBinsY = histo3d->GetNbinsY();
		int nBinsZ = histo3d->GetNbinsZ();
		

		for (int j=0; j<10;j++){

			energyDepCounter=0;
			double radiusBin = j*4;
			for(int xVal=0; xVal<nBinsX; xVal++){
				for(int yVal=0; yVal<nBinsY; yVal++){
					for(int zVal=0; zVal<nBinsZ; zVal++){
						if((((xVal-50)*(xVal-50))+((yVal-50)*(yVal-50)))<(radiusBin*radiusBin)){
							energyDepCounter+=histo3d->GetBinContent(xVal,yVal,zVal);
						}			
					}
				}	
			}
			cout<<"radius "<<radiusBin<<"  endep: "<<energyDepCounter<<" total: "<<histo3d->Integral()<<endl;
			radiusPlot[j]=radiusBin/36.0;
			if(i==0){
				fullDiodeVals0[j]=energyDepCounter;
			}
			else if(i==1){
				fullDiodeVals1[j]=energyDepCounter;
			}
			else if(i==2){
				fullDiodeVals2[j]=energyDepCounter;
			}
			else if(i==3){
				fullDiodeVals3[j]=energyDepCounter;
			}
			else if(i==4){
				fullDiodeVals4[j]=energyDepCounter;
			}
			else if(i==5){
				fullDiodeVals5[j]=energyDepCounter;
			}
			else if(i==6){
				fullDiodeVals6[j]=energyDepCounter;
			}
			else if(i==7){
				fullDiodeVals7[j]=energyDepCounter;
			}
			else if(i==8){
				fullDiodeVals8[j]=energyDepCounter;
			}
		}
	}
	TGraph * fullDiodeGraph0 = new TGraph(nptn, radiusPlot, fullDiodeVals0);
	TGraph * fullDiodeGraph1 = new TGraph(nptn, radiusPlot, fullDiodeVals1);
	TGraph * fullDiodeGraph2 = new TGraph(nptn, radiusPlot, fullDiodeVals2);
	TGraph * fullDiodeGraph3 = new TGraph(nptn, radiusPlot, fullDiodeVals3);
	TGraph * fullDiodeGraph4 = new TGraph(nptn, radiusPlot, fullDiodeVals4);
	TGraph * fullDiodeGraph5 = new TGraph(nptn, radiusPlot, fullDiodeVals5);
	TGraph * fullDiodeGraph6 = new TGraph(nptn, radiusPlot, fullDiodeVals6);
	TGraph * fullDiodeGraph7 = new TGraph(nptn, radiusPlot, fullDiodeVals7);
	// TGraph * fullDiodeGraph8 = new TGraph(nptn, radiusPlot, fullDiodeVals8);
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetGrid();
	fullDiodeGraph7->Draw();
	fullDiodeGraph7->SetLineColor(kBlue-3);
	fullDiodeGraph7->SetLineStyle(1);
    fullDiodeGraph7->SetTitle("no phantom");
    fullDiodeGraph7->GetXaxis()->SetTitle("Radius (mm)");
    fullDiodeGraph7->GetYaxis()->SetTitle("Total energy deposited (MeV)");
	fullDiodeGraph7->SetLineWidth(3);

	// fullDiodeGraph0->Draw("same");
 //    fullDiodeGraph0->SetLineColor(kOrange);
	// fullDiodeGraph0->SetLineStyle(5);

    // fullDiodeGraph0->SetTitle("");
    // fullDiodeGraph0->GetXaxis()->SetTitle("Radius (mm)");
    // fullDiodeGraph0->GetYaxis()->SetTitle("Total Energy Deposit (MeV)");

	// fullDiodeGraph1->Draw("same");
	// fullDiodeGraph1->SetLineStyle(5);

	// fullDiodeGraph2->Draw("same");
	// fullDiodeGraph2->SetLineStyle(5);
	// fullDiodeGraph2->SetLineColor(kCyan);
	// fullDiodeGraph3->Draw("same");
	// fullDiodeGraph3->SetLineColor(kCyan);
	// fullDiodeGraph3->SetLineStyle(1);
	fullDiodeGraph4->Draw("same");
	fullDiodeGraph4->SetLineColor(kGreen+1);
	fullDiodeGraph4->SetLineWidth(3);

	fullDiodeGraph4->SetLineStyle(2);

	// fullDiodeGraph5->Draw("same");
	// fullDiodeGraph5->SetLineColor(kRed);
	// fullDiodeGraph5->SetLineStyle(1);

	fullDiodeGraph6->Draw("same");
	fullDiodeGraph6->SetLineColor(kRed);
	fullDiodeGraph6->SetLineWidth(3);
	fullDiodeGraph6->SetLineStyle(6);

	// fullDiodeGraph7->Draw("same");
	// fullDiodeGraph7->SetLineColor(kMagenta);
	// fullDiodeGraph7->SetLineStyle(1);

	TLegend *leg = new TLegend(0.1, 0.7, 0.53, 0.9);
	// leg->SetHeader("Grating","C"); // option "C" allows to center the header
	leg->SetFillColor(10);
	leg->AddEntry(fullDiodeGraph4, "With legs 10 #mum - top beam","l");
	// leg->AddEntry(fullDiodeGraph1, "With legs - side beam","l");
	// leg->AddEntry(fullDiodeGraph5, "No legs - top beam","l");
	// leg->AddEntry(fullDiodeGraph0, "No legs - side beam","l");
	// leg->AddEntry(fullDiodeGraph3, "All Water - top beam","l");
	// leg->AddEntry(fullDiodeGraph2, "All Water - side beam","l");
	leg->AddEntry(fullDiodeGraph6, "With legs 20 #mum - top beam","l");
	leg->AddEntry(fullDiodeGraph7, "With legs 30 #mum - top beam","l");
	// leg->AddEntry(fullDiodeGraph8, "With legs 100#mum - side beam","l");

	leg->Draw();
	c1->SaveAs("radiusEdepThick.png");

}