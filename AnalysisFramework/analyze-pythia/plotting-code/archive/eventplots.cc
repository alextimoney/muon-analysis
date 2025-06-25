// FinalCuts.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[11] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                     "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root",
                     "$PWD/histograms/pTmin/charm40.root", "$PWD/histograms/pTmin/charm60.root"};
  
  // Get the histograms
  // ==================

  TH1F *bottomonium = (TH1F*)infile[0].Get("Bare_Muon_pT");
  TH1F *charm_uncut = (TH1F*)infile[1].Get("Bare_Muon_pT");
  TH1F *bbbar = (TH1F*)infile[2].Get("Bare_Muon_pT");
  TH1F *ccbar = (TH1F*)infile[3].Get("Bare_Muon_pT");
  TH1F *ttbar_di = (TH1F*)infile[4].Get("Bare_Muon_pT");
  TH1F *ttbar_semi = (TH1F*)infile[5].Get("Bare_Muon_pT");
  TH1F *wbos = (TH1F*)infile[6].Get("Bare_Muon_pT");
  TH1F *zbos = (TH1F*)infile[7].Get("Bare_Muon_pT");
  TH1F *gamma = (TH1F*)infile[8].Get("Bare_Muon_pT");
  TH1F *charm40 = (TH1F*)infile[9].Get("Bare_Muon_pT");
  TH1F *charm60 = (TH1F*)infile[10].Get("Bare_Muon_pT");
  TH1F *ttbar = new TH1F("ttbar", "pT", 60, 0, 120);
  TH1F *charmonium = new TH1F("charmonium", "pT", 60, 0, 120);
  TH1F *sum = new TH1F("SumpT", "pT", 60, 0, 120);

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  ttbar->Add(ttbar_di);
  ttbar->Add(ttbar_semi);

  charmonium->Add(charm_uncut);
  charmonium->Add(charm40);
  charmonium->Add(charm60);

  sum->Add(bottomonium);
  sum->Add(charmonium);
  sum->Add(bbbar);
  sum->Add(ccbar);
  sum->Add(ttbar);
  sum->Add(wbos);
  sum->Add(zbos);
  sum->Add(gamma);

  sum->SetTitle("Muon Bare pT Normalized to Cross-section");
  sum->SetTitleFont(132, "t");

  sum->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  sum->GetYaxis()->SetTitle("N_{events}");
  sum->GetYaxis()->SetRangeUser(1,100000000000);
  
  sum->GetXaxis()->SetTitleFont(132);
  sum->GetYaxis()->SetTitleFont(132);

  sum->SetLineColor(46);
  sum->SetLineWidth(3);
  sum->Draw("HIST");

  bottomonium->SetLineColor(42);
  bottomonium->SetLineWidth(3);
  bottomonium->Draw("HIST SAME");

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

  gamma->SetLineColor(40);
  gamma->SetLineWidth(3);
  gamma->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(sum, "All Events", "f");
  leg->AddEntry(bottomonium, "Bottomonium","f");
  leg->AddEntry(charmonium, "Charmonium", "f");
  leg->AddEntry(bbbar, "bbbar", "f");
  leg->AddEntry(ccbar, "ccbar", "f");
  leg->AddEntry(ttbar, "ttbar", "f");
  leg->AddEntry(wbos, "wbos", "f");
  leg->AddEntry(zbos, "zbos", "f");
  leg->AddEntry(gamma, "gamma*", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  TLatex *lumilabel = new TLatex(0.69, 0.58, "luminosity: 100pb^(-1)");
  lumilabel->SetNDC();
  lumilabel->SetTextSize(0.03);
  lumilabel->SetTextAlign(22); // Center align
  lumilabel->SetTextFont(132);
  lumilabel->Draw();
  cx->Update();

  cx->SetLogy();
  cx->Print("./plots/all_events.png");
  cx->Close();
}