// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/histograms/ttbar-dilep.root", "$PWD/histograms/ttbar-semilep.root",
                      "$PWD/histograms/wbos.root", "$PWD/histograms/zbos.root", "$PWD/histograms/gamma.root", 
                      "$PWD/histograms/bottom2.root", "$PWD/histograms/bottom20.root", "$PWD/histograms/bottom40.root", "$PWD/histograms/bottom60.root", "$PWD/histograms/bottom120.root",
                      "$PWD/histograms/charm2.root", "$PWD/histograms/charm10.root","$PWD/histograms/charm20.root", "$PWD/histograms/charm40.root", "$PWD/histograms/charm60.root", "$PWD/histograms/charm120.root",
                      "$PWD/histograms/bb2.root", "$PWD/histograms/bb20.root","$PWD/histograms/bb40.root", "$PWD/histograms/bb60.root", "$PWD/histograms/bb120.root","$PWD/histograms/bb200.root", 
                      "$PWD/histograms/cc2.root", "$PWD/histograms/cc40.root", "$PWD/histograms/cc40.root", "$PWD/histograms/cc60.root", "$PWD/histograms/cc120.root", "$PWD/histograms/cc200.root"};

  const char *titles[7] = {"Bottomonium", "Charmonium", "bbbar", "ccbar", "ttbar", "wbos", "zbos"};
  
  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *jet0 = new TH1F("sum jet1", "sum jet1", 60, 0, 120);
  TH1F *jet1 = new TH1F("sum jet2", "sum jet2", 60, 0, 120);
  TH1F *jet2 = new TH1F("sum jet3", "sum jet3", 60, 0, 120);
  TH1F *jetmulti = new TH1F("sum jet4", "sum jet4", 60, 0, 120);


  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp0  = (TH1F*)infile[i].Get("No_Jet");
    TH1F *temp1 = (TH1F*)infile[i].Get("One_Jet");
    TH1F *temp2  = (TH1F*)infile[i].Get("Two_Jet");
    TH1F *tempm  = (TH1F*)infile[i].Get("Mult_Jet");

    all_muons->Add(tempall);
    jet0->Add(temp0);
    jet1->Add(temp1);
    jet2->Add(temp2);
    jetmulti->Add(tempm);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon p_{T} Distribution for Number of Jets in Event");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Muon p_{T} [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);
  all_muons->GetXaxis()->SetRangeUser(5, 80);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  jet0->SetLineColor(42);
  jet0->SetLineWidth(3);
  jet0->Draw("HIST SAME");

  jet1->SetLineColor(41);
  jet1->SetLineWidth(3);
  jet1->Draw("HIST SAME");

  jet2->SetLineColor(30);
  jet2->SetLineWidth(3);
  jet2->Draw("HIST SAME");

  jetmulti->SetLineColor(29);
  jetmulti->SetLineWidth(3);
  jetmulti->Draw("HIST SAME");

  auto leg = new TLegend(0.7, 0.68, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "l");
  leg->AddEntry(jet0, "nJets = 0","l");
  leg->AddEntry(jet1, "nJets = 1", "l");
  leg->AddEntry(jet2, "nJets = 2", "l");
  leg->AddEntry(jetmulti, "nJets > 2", "l");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/nJets.png");
  cx->Close();
}