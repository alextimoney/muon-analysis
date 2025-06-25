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
  
  
  // Get the histograms
  // ==================

  
  TH1F *ttbar_di = (TH1F*)infile[0].Get("Bare_Muon_pT");
  TH1F *ttbar_semi = (TH1F*)infile[1].Get("Bare_Muon_pT");
  TH1F *wbos = (TH1F*)infile[2].Get("Bare_Muon_pT");
  TH1F *zbos = (TH1F*)infile[3].Get("Bare_Muon_pT");
  TH1F *gamma = (TH1F*)infile[4].Get("Bare_Muon_pT");
  TH1F *bottom2 = (TH1F*)infile[5].Get("Bare_Muon_pT");
  TH1F *bottom20 = (TH1F*)infile[6].Get("Bare_Muon_pT");
  TH1F *bottom40 = (TH1F*)infile[7].Get("Bare_Muon_pT");
  TH1F *bottom60 = (TH1F*)infile[8].Get("Bare_Muon_pT");
  TH1F *bottom120 = (TH1F*)infile[9].Get("Bare_Muon_pT");
  TH1F *charm2 = (TH1F*)infile[10].Get("Bare_Muon_pT");
  TH1F *charm10 = (TH1F*)infile[11].Get("Bare_Muon_pT");
  TH1F *charm20 = (TH1F*)infile[12].Get("Bare_Muon_pT");
  TH1F *charm40 = (TH1F*)infile[13].Get("Bare_Muon_pT");
  TH1F *charm60 = (TH1F*)infile[14].Get("Bare_Muon_pT");
  TH1F *charm120 = (TH1F*)infile[15].Get("Bare_Muon_pT");
  TH1F *bb2 = (TH1F*)infile[16].Get("Bare_Muon_pT");
  TH1F *bb20 = (TH1F*)infile[17].Get("Bare_Muon_pT");
  TH1F *bb40 = (TH1F*)infile[18].Get("Bare_Muon_pT");
  TH1F *bb60 = (TH1F*)infile[19].Get("Bare_Muon_pT");
  TH1F *bb120 = (TH1F*)infile[20].Get("Bare_Muon_pT");
  TH1F *bb200 = (TH1F*)infile[21].Get("Bare_Muon_pT");
  TH1F *cc2 = (TH1F*)infile[22].Get("Bare_Muon_pT");
  TH1F *cc20 = (TH1F*)infile[23].Get("Bare_Muon_pT");
  TH1F *cc40 = (TH1F*)infile[24].Get("Bare_Muon_pT");
  TH1F *cc60 = (TH1F*)infile[25].Get("Bare_Muon_pT");
  TH1F *cc120 = (TH1F*)infile[26].Get("Bare_Muon_pT");
  TH1F *cc200 = (TH1F*)infile[27].Get("Bare_Muon_pT");
  TH1F *ttbar = new TH1F("ttbar", "pT", 60, 0, 120);
  TH1F *bottomonium = new TH1F("bottomonium", "pT", 60, 0, 120);
  TH1F *charmonium = new TH1F("charmonium", "pT", 60, 0, 120);
  TH1F *bbbar = new TH1F("bbbar", "pT", 60, 0, 120);
  TH1F *ccbar = new TH1F("ccbar", "pT", 60, 0, 120);
  TH1F *sum = new TH1F("SumpT", "pT", 60, 0, 120);

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");
  gStyle->SetLabelFont(132, "t");
  gStyle->SetTextFont(132);

  ttbar->Add(ttbar_di);
  ttbar->Add(ttbar_semi);

  bottomonium->Add(bottom2);
  bottomonium->Add(bottom20);
  bottomonium->Add(bottom40);
  bottomonium->Add(bottom60);
  bottomonium->Add(bottom120);

  charmonium->Add(charm2);
  charmonium->Add(charm10);
  charmonium->Add(charm20);
  charmonium->Add(charm40);
  charmonium->Add(charm60);
  charmonium->Add(charm120);

  ccbar->Add(cc2);
  ccbar->Add(cc20);
  ccbar->Add(cc40);
  ccbar->Add(cc60);
  ccbar->Add(cc120);
  ccbar->Add(cc200);

  bbbar->Add(bb2);
  bbbar->Add(bb20);
  bbbar->Add(bb40);
  bbbar->Add(bb60);
  bbbar->Add(bb120);
  bbbar->Add(bb200);

  sum->Add(bottomonium);
  sum->Add(charmonium);
  sum->Add(bbbar);
  sum->Add(ccbar);
  sum->Add(ttbar);
  sum->Add(wbos);
  sum->Add(zbos);

  double x[50];
  double y[50];
  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = sum->Integral(49-i, 50);
  }

  auto g = new TGraph(50,x,y);
  g->SetTitle("Muons Passing Each Cut;Momentum;Number of Muons");
  g->SetLineColor(46);
  g->SetLineWidth(3);
  g->Draw();

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = bottomonium->Integral(49-i, 50);
  }
  auto g1 = new TGraph(50, x, y);
  g1->SetLineColor(42);
  g1->SetLineWidth(3);
  g1->Draw("SAME"); 

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = charmonium->Integral(49-i, 50);
  }
  auto g2 = new TGraph(50, x, y);
  g2->SetLineColor(41);
  g2->SetLineWidth(3);
  g2->Draw("SAME"); 

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = bbbar->Integral(49-i, 50);
  }
  auto g3 = new TGraph(50, x, y);
  g3->SetLineColor(30);
  g3->SetLineWidth(3);
  g3->Draw("SAME");

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = ccbar->Integral(49-i, 50);
  }
  auto g4 = new TGraph(50, x, y);
  g4->SetLineColor(29);
  g4->SetLineWidth(3);
  g4->Draw("SAME");

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = ttbar->Integral(49-i, 50);
  }
  auto g5 = new TGraph(50, x, y);
  g5->SetLineColor(38);
  g5->SetLineWidth(3);
  g5->Draw("SAME");

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = wbos->Integral(49-i, 50);
  }
  auto g6 = new TGraph(50, x, y);
  g6->SetLineColor(36);
  g6->SetLineWidth(3);
  g6->Draw("SAME");

  for(int i = 0; i < 50; i++) {
    x[i] = i*2.4+2.4;
    y[49-i] = zbos->Integral(49-i, 50);
  }
  auto g7 = new TGraph(50, x, y);
  g7->SetLineColor(48);
  g7->SetLineWidth(3);
  g7->Draw("SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(g, "All Events", "f");
  leg->AddEntry(g1, "Bottomonium","f");
  leg->AddEntry(g2, "Charmonium", "f");
  leg->AddEntry(g3, "bbbar", "f");
  leg->AddEntry(g4, "ccbar", "f");
  leg->AddEntry(g5, "ttbar", "f");
  leg->AddEntry(g6, "wbos", "f");
  leg->AddEntry(g7, "zbos", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/cdf.png");
  cx->Close();
}