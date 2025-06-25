// jet-ratio.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================
  
  TFile infile[7] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar.root", "$PWD/histograms/run1/wbos.root",
                     "$PWD/histograms/run1/zbos.root"};

  TFile infile2[7] = {"$PWD/histograms/2gevjet/bottom-2gevjet.root", "$PWD/histograms/2gevjet/charm-2gevjet.root",
                     "$PWD/histograms/2gevjet/bbbar-2gevjet.root", "$PWD/histograms/2gevjet/ccbar-2gevjet.root", 
                     "$PWD/histograms/2gevjet/ttbar-2gevjet.root", "$PWD/histograms/2gevjet/wbos-2gevjet.root",
                     "$PWD/histograms/2gevjet/zbos-2gevjet.root"};

  
  TH1F *bottomonium = (TH1F*)infile[0].Get("Bare_Muon_pT");
  TH1F *charmonium = (TH1F*)infile[1].Get("Bare_Muon_pT");
  TH1F *bbbar = (TH1F*)infile[2].Get("Bare_Muon_pT");
  TH1F *ccbar = (TH1F*)infile[3].Get("Bare_Muon_pT");
  TH1F *ttbar = (TH1F*)infile[4].Get("Bare_Muon_pT");
  TH1F *wbos = (TH1F*)infile[5].Get("Bare_Muon_pT");
  TH1F *zbos = (TH1F*)infile[6].Get("Bare_Muon_pT");

  TH1F *bottomonium2 = (TH1F*)infile2[0].Get("Bare_Muon_pT");
  TH1F *charmonium2 = (TH1F*)infile2[1].Get("Bare_Muon_pT");
  TH1F *bbbar2 = (TH1F*)infile2[2].Get("Bare_Muon_pT");
  TH1F *ccbar2 = (TH1F*)infile2[3].Get("Bare_Muon_pT");
  TH1F *ttbar2 = (TH1F*)infile2[4].Get("Bare_Muon_pT");
  TH1F *wbos2 = (TH1F*)infile2[5].Get("Bare_Muon_pT");
  TH1F *zbos2 = (TH1F*)infile2[6].Get("Bare_Muon_pT");

  TH1F *sum = new TH1F("SumpT", "pT", 50, 0, 120);
  TH1F *sum2 = new TH1F("SumpT2", "pT", 50, 0, 120);
  TH1F *ratio = new TH1F("ratio of 20 GeV cut to 2 GeV cut", "rat", 50, 0, 120);

  sum->Add(bottomonium);
  sum->Add(charmonium);
  sum->Add(bbbar);
  sum->Add(ccbar);
  sum->Add(ttbar);
  sum->Add(wbos);
  sum->Add(zbos);

  sum2->Add(bottomonium2);
  sum2->Add(charmonium2);
  sum2->Add(bbbar2);
  sum2->Add(ccbar2);
  sum2->Add(ttbar2);
  sum2->Add(wbos2);
  sum2->Add(zbos2);

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

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  sum2->SetTitle("Muon Bare pT Normalized to Cross-section (2 GeV Jet Cut)");
  sum2->SetTitleFont(132, "t");

  sum2->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  sum2->GetYaxis()->SetTitle("N_{muons}");
  sum2->GetYaxis()->SetRangeUser(1,10000000);
  
  sum2->GetXaxis()->SetTitleFont(132);
  sum2->GetYaxis()->SetTitleFont(132);

  sum2->SetLineColor(46);
  sum2->SetLineWidth(3);
  sum2->Draw("HIST");

  bottomonium2->SetLineColor(42);
  bottomonium2->SetLineWidth(3);
  bottomonium2->Draw("HIST SAME");

  charmonium2->SetLineColor(41);
  charmonium2->SetLineWidth(3);
  charmonium2->Draw("HIST SAME");

  bbbar2->SetLineColor(30);
  bbbar2->SetLineWidth(3);
  bbbar2->Draw("HIST SAME");

  ccbar2->SetLineColor(29);
  ccbar2->SetLineWidth(3);
  ccbar2->Draw("HIST SAME");

  ttbar2->SetLineColor(38);
  ttbar2->SetLineWidth(3);
  ttbar2->Draw("HIST SAME");

  wbos2->SetLineColor(36);
  wbos2->SetLineWidth(3);
  wbos2->Draw("HIST SAME");

  zbos2->SetLineColor(48);
  zbos2->SetLineWidth(3);
  zbos2->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(sum2, "All Events", "f");
  leg->AddEntry(bottomonium2, "Bottomonium","f");
  leg->AddEntry(charmonium2, "Charmonium", "f");
  leg->AddEntry(bbbar2, "bbbar", "f");
  leg->AddEntry(ccbar2, "ccbar", "f");
  leg->AddEntry(ttbar2, "ttbar", "f");
  leg->AddEntry(wbos2, "wbos", "f");
  leg->AddEntry(zbos2, "zbos", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  TLatex *lumilabel = new TLatex(0.69, 0.58, "luminosity: 1pm^(-1)");
  lumilabel->SetNDC();
  lumilabel->SetTextSize(0.03);
  lumilabel->SetTextAlign(22); // Center align
  lumilabel->SetTextFont(132);
  lumilabel->Draw();
  cx->Update();

  pad1->SetLogy();

  // Make the ratio plot
  pad2->cd();

  ratio->Add(sum2);
  ratio->Divide(sum);

  ratio->SetLineColor(38);
  ratio->SetLineWidth(3);
  ratio->Draw("HIST");

  ratio->GetYaxis()->SetLabelSize(0.07);
  ratio->GetXaxis()->SetLabelSize(0.07);
  ratio->GetYaxis()->SetTitle("2 GeV cut / 20 GeV cut");
  ratio->GetYaxis()->SetTitleSize(0.09);
  ratio->GetYaxis()->SetTitleOffset(0.45);

  line = new TLine(0, 1, 120, 1);
  line->SetLineColor(35);
  line->SetLineWidth(3);
  line->SetLineStyle(2);
  line->Draw();

  pad2->SetLogy();

  cx->Print("./plots/jet-ratio.png");
  cx->Close();
}