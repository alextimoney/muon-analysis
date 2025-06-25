// Met.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile = "$PWD/histograms/updated/wbos.root";

  // TH1F *w_muon_pT = new TH1F("w_muon_pT", "w_muon_pT", 60, 0, 120);
  // TH1F *w_pT = new TH1F("w_pT", "w_pT", 60, 0, 120);
  // TH1F *jet_pT = new TH1F("jet_pT", "jet_pT", 60, 0, 120);
  // TH1F *met = new TH1F("met", "met", 60, 0, 120);


  TH1F *w_muon_pT = (TH1F*)infile.Get("Bare_Muon_pT");
  // TH1F *w_pT = (TH1F*)infile[i].Get("--");
  TH1F *jet_pT = (TH1F*)infile.Get("JetPt");
  TH1F *met = (TH1F*)infile.Get("MetPt");


  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  w_muon_pT->SetTitle("W Boson Kinematics");
  w_muon_pT->SetTitleFont(132, "t");

  w_muon_pT->GetXaxis()->SetTitle("pT [GeV]");
  w_muon_pT->GetYaxis()->SetTitle("N_{muons}");

  w_muon_pT->GetXaxis()->SetTitleFont(132);
  w_muon_pT->GetYaxis()->SetTitleFont(132);

  w_muon_pT->SetLineColor(46);
  w_muon_pT->SetLineWidth(3);
  w_muon_pT->Draw("HIST");

  // w_pT->SetLineColor(42);
  // w_pT->SetLineWidth(3);
  // w_pT->Draw("HIST SAME");

  jet_pT->SetLineColor(42);
  jet_pT->SetLineWidth(3);
  jet_pT->Draw("HIST SAME");

  met->SetLineColor(30);
  met->SetLineWidth(3);
  met->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(w_muon_pT, "Muon pT", "f");
  // leg->AddEntry(w_pT, "W Boson pT","f");
  leg->AddEntry(jet_pT, "Jet pT", "f");
  leg->AddEntry(met, "MET", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/w-recoil.png");
  cx->Close();
}