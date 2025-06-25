// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[28] = {"$PWD/../histograms/met-low/ttbar-dilep.root", "$PWD/../histograms/met-low/ttbar-semilep.root",
                      "$PWD/../histograms/met-low/wbos.root", "$PWD/../histograms/met-low/zbos.root", "$PWD/../histograms/met-low/gamma.root", 
                      "$PWD/../histograms/met-low/bottom2.root", "$PWD/../histograms/met-low/bottom20.root", "$PWD/../histograms/met-low/bottom40.root", "$PWD/../histograms/met-low/bottom60.root", "$PWD/../histograms/met-low/bottom120.root",
                      "$PWD/../histograms/met-low/charm2.root", "$PWD/../histograms/met-low/charm10.root","$PWD/../histograms/met-low/charm20.root", "$PWD/../histograms/met-low/charm40.root", "$PWD/../histograms/met-low/charm60.root", "$PWD/../histograms/met-low/charm120.root",
                      "$PWD/../histograms/met-low/bb2.root", "$PWD/../histograms/met-low/bb20.root","$PWD/../histograms/met-low/bb40.root", "$PWD/../histograms/met-low/bb60.root", "$PWD/../histograms/met-low/bb120.root","$PWD/../histograms/met-low/bb200.root", 
                      "$PWD/../histograms/met-low/cc2.root", "$PWD/../histograms/met-low/cc40.root", "$PWD/../histograms/met-low/cc40.root", "$PWD/../histograms/met-low/cc60.root", "$PWD/../histograms/met-low/cc120.root", "$PWD/../histograms/met-low/cc200.root"};
 const char *titles[7] = {"Bottomonium", "Charmonium", "bbbar", "ccbar", "ttbar", "wbos", "zbos"};
  
  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *jet0 = new TH1F("sum met1", "sum met1", 60, 0, 120);
  TH1F *jet1 = new TH1F("sum met2", "sum met2", 60, 0, 120);
  TH1F *jet2 = new TH1F("sum met3", "sum met3", 60, 0, 120);
  TH1F *jetmulti = new TH1F("sum met4", "sum met4", 60, 0, 120);


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

  all_muons->SetTitle("Number of Jets");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

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

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(jet0, "No_Jets","f");
  leg->AddEntry(jet1, "One_Jet", "f");
  leg->AddEntry(jet2, "Two_Jets", "f");
  leg->AddEntry(jetmulti, ">2_Jets", "f");

  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/nJets.png");
  cx->Close();
}