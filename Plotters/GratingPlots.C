{
    gStyle->SetOptStat(0);
    TFile * gratingFileAir = new TFile("/storage/lb8075/Grating/grating20x20AirWorld10K_Edep.root");
    TH3D* histAir3D = (TH3D*)gratingFileAir->Get("histo");
    TH1D* histAir1DY = (TH1D*)histAir3D->ProjectionY("histAir1DY");
    TFile* gratingFileVacuum = new TFile("/storage/lb8075/Grating/grating20x20VacuumWorld10K_Edep.root");
    TH3D* histVacuum3D = (TH3D*)gratingFileVacuum->Get("histo");
    TH1D* histVacuum1DY = (TH1D*)histVacuum3D->ProjectionY("histVacuum1DY");

    TFile * gratingFile1mmAir = new TFile("/storage/lb8075/Grating/grating1mm20x20AirWorld10K_Edep.root");
    TH3D* hist1mmAir3D = (TH3D*)gratingFile1mmAir->Get("histo");
    TH1D* hist1mmAir1DY = (TH1D*)hist1mmAir3D->ProjectionY("hist1mmAir1DY");
    TFile* gratingFile1mmVacuum = new TFile("/storage/lb8075/Grating/grating1mm20x20VacuumWorld10K_Edep.root");
    TH3D* hist1mmVacuum3D = (TH3D*)gratingFile1mmVacuum->Get("histo");
    TH1D* hist1mmVacuum1DY = (TH1D*)hist1mmVacuum3D->ProjectionY("hist1mmVacuum1DY");

    TH1D* Subtraction = (TH1D*)histAir1DY->Clone();
    Subtraction->Add(histVacuum1DY,-1);
    TH1D* Subtraction1mm = (TH1D*)hist1mmAir1DY->Clone();
    Subtraction1mm->Add(hist1mmVacuum1DY,-1);

    TCanvas c1;
    histAir1DY->Draw();

    histAir1DY->GetYaxis()->SetRangeUser(200,3200);

    histAir1DY->Draw();
    histAir1DY->SetMarkerStyle(7);
    hist1mmAir1DY->SetMarkerStyle(2);
    hist1mmAir1DY->SetMarkerColor(kMagenta-9);

    histVacuum1DY->SetMarkerColor(kRed);
    histVacuum1DY->SetMarkerStyle(7);

    hist1mmVacuum1DY->SetMarkerColor(kBlue);
    hist1mmVacuum1DY->SetMarkerStyle(2);
    Subtraction->SetMarkerColor(kGreen+7);
    Subtraction->SetMarkerStyle(7);
    Subtraction1mm->SetMarkerStyle(2);
    Subtraction1mm->SetMarkerColor(kGreen+3);
    histVacuum1DY->Draw("same");
    Subtraction->Draw("same");

	TLegend *leg = new TLegend(0.35, 0.31, 0.65, 0.5);
	// leg->SetHeader("Grating","C"); // option "C" allows to center the header
	leg->SetFillColor(10);
	leg->AddEntry(histAir1DY, "400 #mum - in air","p");
	leg->AddEntry(histVacuum1DY, "400 #mum - in vacuum","p");

	leg->AddEntry(Subtraction, "400 #mum - Difference","p");

	leg->Draw();

    c1.SaveAs("Grating400micron.png");

   TCanvas c2;
   hist1mmAir1DY->GetYaxis()->SetRangeUser(200,3200);
   hist1mmAir1DY->Draw();
   hist1mmVacuum1DY->Draw("same");
   Subtraction1mm->Draw("same");

   TLegend *leg2 = new TLegend(0.35, 0.31, 0.65, 0.5);
   	
   leg2->AddEntry(hist1mmAir1DY, "1 mm - in air","p");
   leg2->AddEntry(hist1mmVacuum1DY, "1 mm - in vacuum","p");
   leg2->AddEntry(Subtraction1mm, "1 mm - Difference","p");
   leg2->Draw();

}
