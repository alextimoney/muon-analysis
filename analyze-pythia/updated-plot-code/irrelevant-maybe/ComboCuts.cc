// ComboCuts.cc
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
  TH1F *cut_muons5 = new TH1F("muon cuts 5", "muon cuts 5", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *tempcut1  = (TH1F*)infile[i].Get("ComboCuts1");
    TH1F *tempcut2  = (TH1F*)infile[i].Get("ComboCuts2");
    TH1F *tempcut3  = (TH1F*)infile[i].Get("ComboCuts3");
    TH1F *tempcut4  = (TH1F*)infile[i].Get("ComboCuts4");
    TH1F *tempcut5  = (TH1F*)infile[i].Get("ComboCuts5");


    all_muons->Add(tempall);
    cut_muons1->Add(tempcut1);
    cut_muons2->Add(tempcut2);
    cut_muons3->Add(tempcut3);
    cut_muons4->Add(tempcut4);
    cut_muons5->Add(tempcut5);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Muon pT with Cuts");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  cut_muons1->SetLineColor(42);
  cut_muons1->SetLineWidth(3);
  cut_muons1->Draw("HIST SAME");

  cut_muons2->SetLineColor(32);
  cut_muons2->SetLineWidth(3);
  cut_muons2->Draw("HIST SAME");

  cut_muons3->SetLineColor(38);
  cut_muons3->SetLineWidth(3);
  cut_muons3->Draw("HIST SAME");

  cut_muons4->SetLineColor(48);
  cut_muons4->SetLineWidth(3);
  cut_muons4->Draw("HIST SAME");

  cut_muons5->SetLineColor(33);
  cut_muons5->SetLineWidth(3);
  cut_muons5->Draw("HIST SAME");

  auto leg = new TLegend(0.4, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "f");
  leg->AddEntry(cut_muons1, "MET > 30 GeV","f");
  leg->AddEntry(cut_muons2, "1 muon || MET > 30 GeV","f");  
  leg->AddEntry(cut_muons3, "(Met > 5 && 1 muon) || MET > 30","f");
  leg->AddEntry(cut_muons4, "(Met > 10 && 1 muon) || MET > 30","f");
  leg->AddEntry(cut_muons5, "(Met > 15 && 1 muon) || MET > 30","f");

  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/combo_cuts.png");
  cx->Close();

  float pass_cut_values[6][7];
  for(int j = 0; j < 7; j++) {
    pass_cut_values[0][j] = all_muons->Integral(j*10,1000);
    pass_cut_values[1][j] = cut_muons1->Integral(j*10,1000);
    pass_cut_values[2][j] = cut_muons2->Integral(j*10,1000);
    pass_cut_values[3][j] = cut_muons3->Integral(j*10,1000);
    pass_cut_values[4][j] = cut_muons4->Integral(j*10,1000);
    pass_cut_values[5][j] = cut_muons5->Integral(j*10,1000);
  }


  for(int i = 0; i < 6; i++) {
    cout << pass_cut_values[i][3] << endl;
  }

  TCanvas *cy = new TCanvas("cy","cy", 800, 600);
  cy->cd();

  // gStyle->SetOptStat(0);
  // gStyle->SetTitleFont(132, "t");
  // gStyle->SetLabelFont(132, "t");
  // gStyle->SetTextFont(132);

  double x[7] = {0, 10, 20, 30, 40, 50, 60};
  double y[7] = {pass_cut_values[0][0], pass_cut_values[0][1], pass_cut_values[0][2], pass_cut_values[0][3], pass_cut_values[0][4],
                 pass_cut_values[0][5], pass_cut_values[0][6]};

  auto g = new TGraph(5,x,y);
  g->SetTitle("Number of Muons that Pass Momentum Thresholds;Bare Muon pT [GeV];N_{muons}");
  g->SetLineColor(46);
  g->SetLineWidth(3);
  g->Draw();

  double y1[7] = {pass_cut_values[1][0], pass_cut_values[1][1], pass_cut_values[1][2], pass_cut_values[1][3], pass_cut_values[1][4],
          pass_cut_values[1][5], pass_cut_values[1][6]};
  auto g1 = new TGraph(5,x,y1);
  g1->SetLineColor(42);
  g1->SetLineWidth(3);
  g1->Draw("SAME");

  double y2[7] = {pass_cut_values[2][0], pass_cut_values[2][1], pass_cut_values[2][2], pass_cut_values[2][3], pass_cut_values[2][4],
          pass_cut_values[2][5], pass_cut_values[2][6]};
  auto g2 = new TGraph(5,x,y2);
  g2->SetLineColor(32);
  g2->SetLineWidth(3);
  g2->Draw("SAME");

  double y3[7] = {pass_cut_values[3][0], pass_cut_values[3][1], pass_cut_values[3][2], pass_cut_values[3][3], pass_cut_values[3][4],
          pass_cut_values[3][5], pass_cut_values[3][6]};
  auto g3 = new TGraph(5,x,y3);
  g3->SetLineColor(38);
  g3->SetLineWidth(3);
  g3->Draw("SAME");

  double y4[7] = {pass_cut_values[4][0], pass_cut_values[4][1], pass_cut_values[4][2], pass_cut_values[4][3], pass_cut_values[4][4],
          pass_cut_values[4][5], pass_cut_values[4][6]};
  auto g4 = new TGraph(5,x,y4);
  g4->SetLineColor(48);
  g4->SetLineWidth(3);
  g4->Draw("SAME");

  double y5[7] = {pass_cut_values[5][0], pass_cut_values[5][1], pass_cut_values[5][2], pass_cut_values[5][3], pass_cut_values[5][4],
          pass_cut_values[5][5], pass_cut_values[5][6]};
  auto g5 = new TGraph(5,x,y5);
  g5->SetLineColor(33);
  g5->SetLineWidth(3);
  g5->Draw("SAME");

  leg->SetTextSize(0.035);
  leg->Draw();

  cy->SetLogy();
  cy->Print("./plots/pass_cuts.png");
  cy->Close();
}