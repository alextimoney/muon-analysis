// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile_bias[4] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                          "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root"};
  TFile infile_nobias[4] = {"$PWD/histograms/no-bias-selection/bottomonium.root", "$PWD/histograms/no-bias-selection/charmonium.root",
                            "$PWD/histograms/no-bias-selection/bbbar.root", "$PWD/histograms/no-bias-selection/ccbar.root"};
  
  TH1F *all_muons_bias = new TH1F("sum bias", "sum bias", 60, 0, 120);
  TH1F *all_muons_nobias = new TH1F("sum no bias", "sum no bias", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 4; i++) {
    TH1F *tempall_bias = (TH1F*)infile_bias[i].Get("Bare_Muon_pT");
    TH1F *tempall_nobias = (TH1F*)infile_nobias[i].Get("Bare_Muon_pT");

    all_muons_bias->Add(tempall_bias);
    all_muons_nobias->Add(tempall_nobias);
  }

  TH1F *bottom_bias = (TH1F*)infile_bias[0].Get("Bare_Muon_pT");
  TH1F *charm_bias = (TH1F*)infile_bias[1].Get("Bare_Muon_pT");
  TH1F *bb_bias = (TH1F*)infile_bias[2].Get("Bare_Muon_pT");
  TH1F *cc_bias = (TH1F*)infile_bias[3].Get("Bare_Muon_pT");
  TH1F *bottom_nobias = (TH1F*)infile_nobias[0].Get("Bare_Muon_pT");
  TH1F *charm_nobias = (TH1F*)infile_nobias[1].Get("Bare_Muon_pT");
  TH1F *bb_nobias = (TH1F*)infile_nobias[2].Get("Bare_Muon_pT");
  TH1F *cc_nobias = (TH1F*)infile_nobias[3].Get("Bare_Muon_pT");

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  // pad1 = new TPad("pad1", "pad1", 0.05, 0.30, 1.0, .96);
  // pad1->SetTicky(0);
  // pad1->SetLeftMargin(.1);
  // pad1->SetBottomMargin(.001);
  // pad1->Draw();
  // cx->cd();
  // pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1.0, .30);
  // pad2->SetGrid();
  // pad2->SetTicky(0);
  // pad2->SetLeftMargin(.1);
  // pad2->SetBottomMargin(0.2);
  // pad2->SetTopMargin(.02);
  // pad2->Draw();

  // pad1->cd();

  all_muons_bias->SetTitle("Bias selection vs. not");
  all_muons_bias->SetTitleFont(132, "t");
  
  all_muons_bias->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons_bias->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons_bias->GetXaxis()->SetTitleFont(132);
  all_muons_bias->GetYaxis()->SetTitleFont(132);
  all_muons_bias->GetXaxis()->SetRangeUser(1, 50000000000);

  all_muons_bias->SetLineColor(46);
  all_muons_bias->SetLineWidth(3);
  all_muons_bias->Draw("HIST");

  all_muons_nobias->SetLineColor(46);
  all_muons_nobias->SetLineWidth(3);
  all_muons_nobias->Draw("HIST SAME");

  // bottom_bias->SetLineColor(37);
  // bottom_bias->SetLineWidth(3);
  // bottom_bias->Draw("HIST SAME");

  // bottom_nobias->SetLineColor(37);
  // bottom_nobias->SetLineWidth(3);
  // bottom_nobias->Draw("HIST SAME");

  // charm_bias->SetLineColor(37);
  // charm_bias->SetLineWidth(3);
  // charm_bias->Draw("HIST SAME");

  // charm_nobias->SetLineColor(37);
  // charm_nobias->SetLineWidth(3);
  // charm_nobias->Draw("HIST SAME");

  bb_bias->SetLineColor(30);
  bb_bias->SetLineWidth(3);
  bb_bias->Draw("HIST SAME");

  bb_nobias->SetLineColor(30);
  bb_nobias->SetLineWidth(3);
  bb_nobias->Draw("HIST SAME");

  // cc_bias->SetLineColor(38);
  // cc_bias->SetLineWidth(3);
  // cc_bias->Draw("HIST SAME");

  // cc_nobias->SetLineColor(38);
  // cc_nobias->SetLineWidth(3);
  // cc_nobias->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons_bias, "All processes, bias", "f");
  leg->AddEntry(all_muons_nobias, "All processes, no bias", "f");
  // leg->AddEntry(bottom_bias, "Bottomonium, bias", "f");
  // leg->AddEntry(bottom_nobias, "Bottomonium, no bias", "f");
  // leg->AddEntry(charm_bias, "Charmonium, bias", "f");
  // leg->AddEntry(charm_nobias, "Charmonium, no bias", "f");
  leg->AddEntry(bb_bias, "bbbar, bias", "f");
  leg->AddEntry(bb_nobias, "bbbar, no bias", "f");
  // leg->AddEntry(cc_bias, "ccbar, bias", "f");
  // leg->AddEntry(cc_nobias, "ccbar, no bias", "f");
  // leg->AddEntry(cut_muons1, "MET > 30 GeV","f");

  leg->SetTextSize(0.035);
  leg->Draw();

  // pad1->SetLogy();

  // // Make the ratio plot
  // pad2->cd();

  // ratio1->Add(all_muons);
  // ratio1->Divide(to_muons);

  // ratio1->SetLineColor(38);
  // ratio1->SetLineWidth(3);
  // ratio1->Draw("HIST");

  // ratio1->GetYaxis()->SetLabelSize(0.07);
  // ratio1->GetXaxis()->SetLabelSize(0.07);
  // ratio1->GetYaxis()->SetTitle("Pythia / T-O run");
  // ratio1->GetYaxis()->SetTitleSize(0.09);
  // ratio1->GetYaxis()->SetTitleOffset(0.45);

  // line = new TLine(0, 1, 120, 1);
  // line->SetLineColor(35);
  // line->SetLineWidth(3);
  // line->SetLineStyle(2);
  // line->Draw();

  // pad2->SetLogy();

  cx->SetLogy();

  cx->Print("./plots/bb-bias-comp.png");
  cx->Close();
}