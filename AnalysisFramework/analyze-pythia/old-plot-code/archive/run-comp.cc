// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[9] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar.root", "$PWD/histograms/run1/wbos.root",
                     "$PWD/histograms/run1/zbos-mc.root", "$PWD/histograms/run1/gamma.root",
                     "$PWD/histograms/toroid-off-run.root"};
  
  TH1F *all_muons = new TH1F("sum", "sum", 50, 0, 120);
  TH1F *to_muons = new TH1F("to", "to", 50, 0, 120);
  TH1F *ratio1 = new TH1F("ratio of all muons to TO muons", "rat", 50, 0, 120);


  // Note: keeping this in for possibly a later comparison of making these cuts on the toroid off data??? 
  // if that's even possible

  // TH1F *cut_muons1 = new TH1F("muon cuts 1", "muon cuts 1", 50, 0, 120);


  // Get the histograms
  // ==================

  for (int i = 0; i < 8; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    // TH1F *tempcut1  = (TH1F*)infile[i].Get("Final_Cuts1");

    all_muons->Add(tempall);
    // cut_muons1->Add(tempcut1);
  }

  TH1F *BigTO = (TH1F*)infile[8].Get("muon_pT_hist");
  TH1F *tempTO = new TH1F("temp", "temp", 50, 0, 120000);
  tempTO->Add(BigTO);
  tempTO->GetXaxis()->SetLimits(0, 120);
  to_muons->Add(tempTO);

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  pad1 = new TPad("pad1", "pad1", 0.05, 0.30, 1.0, .96);
  pad1->SetTicky(0);
  pad1->SetLeftMargin(.1);
  pad1->SetBottomMargin(.001);
  pad1->Draw();
  cx->cd();
  pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1.0, .30);
  pad2->SetGrid();
  pad2->SetTicky(0);
  pad2->SetLeftMargin(.1);
  pad2->SetBottomMargin(0.2);
  pad2->SetTopMargin(.02);
  pad2->Draw();

  pad1->cd();

  all_muons->SetTitle("Final Cuts");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(30);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  to_muons->SetLineColor(38);
  to_muons->SetLineWidth(3);
  to_muons->Draw("HIST SAME");

  // cut_muons1->SetLineColor(42);
  // cut_muons1->SetLineWidth(3);
  // cut_muons1->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "Pythia Events", "f");
  leg->AddEntry(to_muons, "T-O run Events", "f");
  // leg->AddEntry(cut_muons1, "MET > 30 GeV","f");

  leg->SetTextSize(0.035);
  leg->Draw();

  pad1->SetLogy();

  // Make the ratio plot
  pad2->cd();

  ratio1->Add(all_muons);
  ratio1->Divide(to_muons);

  ratio1->SetLineColor(38);
  ratio1->SetLineWidth(3);
  ratio1->Draw("HIST");

  ratio1->GetYaxis()->SetLabelSize(0.07);
  ratio1->GetXaxis()->SetLabelSize(0.07);
  ratio1->GetYaxis()->SetTitle("Pythia / T-O run");
  ratio1->GetYaxis()->SetTitleSize(0.09);
  ratio1->GetYaxis()->SetTitleOffset(0.45);

  line = new TLine(0, 1, 120, 1);
  line->SetLineColor(35);
  line->SetLineWidth(3);
  line->SetLineStyle(2);
  line->Draw();

  pad2->SetLogy();

  cx->Print("./plots/toroid-off-run/run-comp.png");
  cx->Close();


  TCanvas *cy = new TCanvas("cy","cy", 800, 600);
  cy->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  all_muons->Scale(0.0001);
  // to_muons->Scale(1/to_muons->GetSumOfWeights());

  all_muons->GetXaxis()->SetTitle("N_{muons}");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->Draw("HIST");
  to_muons->Draw("HIST SAME");

  leg->Draw();

  cy->SetLogy();
  cy->Print("./plots/toroid-off-run/run-comp-scaled.png");
  cy->Close();
}