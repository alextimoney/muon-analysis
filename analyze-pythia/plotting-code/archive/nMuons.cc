// nMuons.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[8] = {"$PWD/histograms/bottomonium.root", "$PWD/histograms/charmonium.root",
                     "$PWD/histograms/bbbar.root", "$PWD/histograms/ccbar.root", 
                     "$PWD/histograms/ttbar.root", "$PWD/histograms/wbos.root",
                     "$PWD/histograms/zbos.root"};
  
  TH1F *all_muons = new TH1F("sum", "sum", 50, 0, 120);
  TH1F *muon1 = new TH1F("sum muon1", "sum muon1", 50, 0, 120);
  TH1F *muon2 = new TH1F("sum muon2", "sum muon2", 50, 0, 120);
  TH1F *muon3 = new TH1F("sum muon3", "sum muon3", 50, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 7; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1  = (TH1F*)infile[i].Get("OneMuon");
    TH1F *temp2 = (TH1F*)infile[i].Get("TwoMuon");
    TH1F *temp3  = (TH1F*)infile[i].Get("ThreeMuon");

    all_muons->Add(tempall);
    muon1->Add(temp1);
    muon2->Add(temp2);
    muon3->Add(temp3);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Number of Muons");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  muon1->SetLineColor(42);
  muon1->SetLineWidth(3);
  muon1->Draw("HIST SAME");

  muon2->SetLineColor(41);
  muon2->SetLineWidth(3);
  muon2->Draw("HIST SAME");

  muon3->SetLineColor(30);
  muon3->SetLineWidth(3);
  muon3->Draw("HIST SAME");


  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(muon1, "One_Muon","f");
  leg->AddEntry(muon2, "Two_Muon", "f");
  leg->AddEntry(muon3, "Three_Muon", "f");

  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/all_events/nMuons.png");
  cx->Close();
}