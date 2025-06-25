// rates.cc
// ------------
// Rescales muon pT histograms to match bins from L1 trigger

{
  
  TFile runfile = "$PWD/../toroid-off-analysis-plots/mtree_out/run-data.root";
  
  int num_bins = 60;

  TH1F *run_pT = (TH1F*)runfile.Get("muon_pT");
  TH1F *run_P = (TH1F*)runfile.Get("muon_P");

  // Convert from MeV to GeV
  run_pT->GetXaxis()->SetLimits(0, 120);
  run_P->GetXaxis()->SetLimits(0, 120);

  // Plotting
  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *c1 = new TCanvas("c1","c1", 800, 600);
  c1->cd();

  run_pT->SetTitle("Muon p_{T} Distribution for Toroid-Off Runs");
  run_pT->SetTitleFont(132, "t");
  
  run_pT->GetXaxis()->SetTitle("Bare Muon p_{T} [GeV]");
  run_pT->GetYaxis()->SetTitle("N_{muons}");
  run_pT->GetYaxis()->SetRangeUser(10, 100000000);
  run_pT->GetXaxis()->SetRangeUser(0, 80);

  run_pT->SetLineColor(36);
  run_pT->SetLineWidth(3);
  run_pT->Draw("HIST SAME");

  c1->SetLogy();
  c1->Print("run_pT.png");
  c1->Close();
}
