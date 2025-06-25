// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[7] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar.root", "$PWD/histograms/run1/wbos.root",
                     "$PWD/histograms/run1/zbos.root"};
  
  // Get the histograms
  // ==================

  TH1F *bottomonium = (TH1F*)infile[0].Get("Bare_Muon_pT_norm1");
  TH1F *charmonium = (TH1F*)infile[1].Get("Bare_Muon_pT_norm1");
  TH1F *bbbar = (TH1F*)infile[2].Get("Bare_Muon_pT_norm1");
  TH1F *ccbar = (TH1F*)infile[3].Get("Bare_Muon_pT_norm1");
  TH1F *ttbar = (TH1F*)infile[4].Get("Bare_Muon_pT_norm1");
  TH1F *wbos = (TH1F*)infile[5].Get("Bare_Muon_pT_norm1");
  TH1F *zbos = (TH1F*)infile[6].Get("Bare_Muon_pT_norm1");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  bottomonium->SetTitle("Muon Bare pT Normalized to 1");
  bottomonium->SetTitleFont(132, "t");

  bottomonium->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  bottomonium->GetYaxis()->SetTitle("N_{events}");
  
  bottomonium->GetXaxis()->SetTitleFont(132);
  bottomonium->GetYaxis()->SetTitleFont(132);

  bottomonium->SetLineColor(42);
  bottomonium->SetLineWidth(3);
  bottomonium->Draw("HIST");

  charmonium->SetLineColor(41);
  charmonium->SetLineWidth(3);
  charmonium->Draw("HIST SAME");

  bbbar->SetLineColor(30);
  bbbar->SetLineWidth(3);
  bbbar->Draw("HIST SAME");

  ccbar->SetLineColor(29);
  ccbar->SetLineWidth(3);
  ccbar->Draw("HIST SAME");

  ttbar->SetLineColor(38);
  ttbar->SetLineWidth(3);
  ttbar->Draw("HIST SAME");

  wbos->SetLineColor(36);
  wbos->SetLineWidth(3);
  wbos->Draw("HIST SAME");

  zbos->SetLineColor(48);
  zbos->SetLineWidth(3);
  zbos->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(bottomonium, "Bottomonium","f");
  leg->AddEntry(charmonium, "Charmonium", "f");
  leg->AddEntry(bbbar, "bbbar", "f");
  leg->AddEntry(ccbar, "ccbar", "f");
  leg->AddEntry(ttbar, "ttbar", "f");
  leg->AddEntry(wbos, "wbos", "f");
  leg->AddEntry(zbos, "zbos", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/norm1.png");
  cx->Close();
}