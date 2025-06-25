// MuonIsolation.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  
  TFile infile[28] = {"$PWD/histograms/updated/ttbar-dilep.root", "$PWD/histograms/updated/ttbar-semilep.root",
    "$PWD/histograms/updated/wbos.root", "$PWD/histograms/updated/zbos.root", "$PWD/histograms/updated/gamma.root", 
    "$PWD/histograms/updated/bottom2.root", "$PWD/histograms/updated/bottom20.root", "$PWD/histograms/updated/bottom40.root", "$PWD/histograms/updated/bottom60.root", "$PWD/histograms/updated/bottom120.root",
    "$PWD/histograms/updated/charm2.root", "$PWD/histograms/updated/charm10.root","$PWD/histograms/updated/charm20.root", "$PWD/histograms/updated/charm40.root", "$PWD/histograms/updated/charm60.root", "$PWD/histograms/updated/charm120.root",
    "$PWD/histograms/updated/bb2.root", "$PWD/histograms/updated/bb20.root","$PWD/histograms/updated/bb40.root", "$PWD/histograms/updated/bb60.root", "$PWD/histograms/updated/bb120.root","$PWD/histograms/updated/bb200.root", 
    "$PWD/histograms/updated/cc2.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc40.root", "$PWD/histograms/updated/cc60.root", "$PWD/histograms/updated/cc120.root", "$PWD/histograms/updated/cc200.root"};

  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *iso1 = new TH1F("sum iso1", "sum iso1", 60, 0, 120);
  TH1F *iso2 = new TH1F("sum iso2", "sum iso2", 60, 0, 120);
  TH1F *iso3 = new TH1F("sum iso3", "sum iso3", 60, 0, 120);
  TH1F *iso4 = new TH1F("sum iso4", "sum iso4", 60, 0, 120);
  TH1F *iso5 = new TH1F("sum iso5", "sum iso5", 60, 0, 120);
  TH1F *iso6 = new TH1F("sum iso6", "sum iso6", 60, 0, 120);
  TH1F *iso7 = new TH1F("sum iso7", "sum iso7", 60, 0, 120);


  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1 = (TH1F*)infile[i].Get("Iso1");
    TH1F *temp2 = (TH1F*)infile[i].Get("Iso2");
    TH1F *temp3 = (TH1F*)infile[i].Get("Iso3");
    TH1F *temp4 = (TH1F*)infile[i].Get("Iso4");
    TH1F *temp5 = (TH1F*)infile[i].Get("Iso5");
    TH1F *temp6 = (TH1F*)infile[i].Get("Iso6");
    TH1F *temp7 = (TH1F*)infile[i].Get("Iso7");

    all_muons->Add(tempall);
    iso1->Add(temp1);
    iso2->Add(temp2);
    iso3->Add(temp3);
    iso4->Add(temp4);
    iso5->Add(temp5);
    iso6->Add(temp6);
    iso7->Add(temp7);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon Isolation 'Trigger' Passes");
  all_muons->SetTitleFont(132, "t");

  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  iso1->SetLineColor(42);
  iso1->SetLineWidth(3);
  iso1->Draw("HIST SAME");

  iso2->SetLineColor(41);
  iso2->SetLineWidth(3);
  iso2->Draw("HIST SAME");

  iso3->SetLineColor(30);
  iso3->SetLineWidth(3);
  iso3->Draw("HIST SAME");

  iso4->SetLineColor(29);
  iso4->SetLineWidth(3);
  iso4->Draw("HIST SAME");

  iso5->SetLineColor(38);
  iso5->SetLineWidth(3);
  iso5->Draw("HIST SAME");

  iso6->SetLineColor(36);
  iso6->SetLineWidth(3);
  iso6->Draw("HIST SAME");

  iso7->SetLineColor(40);
  iso7->SetLineWidth(3);
  iso7->Draw("HIST SAME");


  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(iso1, "Muon Isolation > 70 GeV","f");
  leg->AddEntry(iso2, "Muon Isolation < 70 GeV", "f");
  leg->AddEntry(iso3, "Muon Isolation < 50 GeV", "f");
  leg->AddEntry(iso4, "Muon Isolation < 40 GeV", "f");
  leg->AddEntry(iso5, "Muon Isolation < 30 GeV", "f");
  leg->AddEntry(iso6, "Muon Isolation < 20 GeV", "f");
  leg->AddEntry(iso7, "Muon Isolation < 10 GeV", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/variables/iso.png");
  cx->Close();

}