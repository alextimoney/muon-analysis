// FinalCuts.cc
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
  TH1F *cut_muons1 = new TH1F("muon cuts 1", "muon cuts 1", 60, 0, 120);
  TH1F *cut_muons2 = new TH1F("muon cuts 2", "muon cuts 2", 60, 0, 120);
  TH1F *cut_muons3 = new TH1F("muon cuts 3", "muon cuts 3", 60, 0, 120);
  TH1F *cut_muons4 = new TH1F("muon cuts 4", "muon cuts 4", 60, 0, 120);

  float L1_prescale = 7.386750749;

  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *tempcut1  = (TH1F*)infile[i].Get("ComboCuts1");
    TH1F *tempcut2  = (TH1F*)infile[i].Get("ComboCuts2");
    TH1F *tempcut3  = (TH1F*)infile[i].Get("ComboCuts3");
    TH1F *tempcut4  = (TH1F*)infile[i].Get("ComboCuts4");

    all_muons->Add(tempall);
    cut_muons1->Add(tempcut1);
    cut_muons2->Add(tempcut2);
    cut_muons3->Add(tempcut3);
    cut_muons4->Add(tempcut4);
  }

  all_muons->Scale(1/L1_prescale);
  cut_muons1->Scale(1/L1_prescale);
  cut_muons2->Scale(1/L1_prescale);
  cut_muons3->Scale(1/L1_prescale);
  cut_muons4->Scale(1/L1_prescale);

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");
  gStyle->SetLabelFont(132, "t");
  gStyle->SetTextFont(132);

  double x[60];
  double y[60];
  for(int i = 60; i > 0; i--) {
    x[i] = i*2;
    y[i] = all_muons->Integral(i*2, 200);
  }

  auto g = new TGraph(60,x,y);
  g->SetTitle("Survival Function;Momentum;Number of Muons");
  g->SetLineColor(46);
  g->SetLineWidth(3);
  // g->GetYaxis()->SetRangeUser(0, 10000000000);
  g->Draw();

  for(int i = 0; i < 60; i++) {
    x[i] = i*2+2;
    y[59-i] = cut_muons1->Integral(59-i, 60);
  }
  auto g1 = new TGraph(60, x, y);
  g1->SetLineColor(42);
  g1->SetLineWidth(3);
  g1->Draw("SAME"); 

  for(int i = 0; i < 60; i++) {
    x[i] = i*2+2;
    y[59-i] = cut_muons2->Integral(59-i, 60);
  }
  auto g2 = new TGraph(60, x, y);
  g2->SetLineColor(32);
  g2->SetLineWidth(3);
  g2->Draw("SAME"); 

  for(int i = 0; i < 60; i++) {
    x[i] = i*2+2;
    y[59-i] = cut_muons3->Integral(59-i, 60);
  }
  auto g3 = new TGraph(60, x, y);
  g3->SetLineColor(38);
  g3->SetLineWidth(3);
  g3->Draw("SAME");

  for(int i = 0; i < 60; i++) {
    x[i] = i*2+2;
    y[59-i] = cut_muons4->Integral(59-i, 60);
  }
  auto g4 = new TGraph(60, x, y);
  g4->SetLineColor(48);
  g4->SetLineWidth(3);
  g4->Draw("SAME");

  auto leg = new TLegend(0.5, 0.60, 0.9, 0.89);
  leg->AddEntry(g, "All Events", "f");
  leg->AddEntry(g1, "MET > 30 GeV","f");
  leg->AddEntry(g2, "Met > 5, 1 muon || MET > 30", "f");
  leg->AddEntry(g3, "Met > 10, 1 muon || MET > 30", "f");
  leg->AddEntry(g4, "Met > 15, 1 muon || MET > 30", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/cdf.png");
  cx->Close();
}