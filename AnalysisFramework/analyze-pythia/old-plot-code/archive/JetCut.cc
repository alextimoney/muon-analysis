// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[20] = {"$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                      "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root", 
                      "$PWD/histograms/pTmin/bottom2.root", "$PWD/histograms/pTmin/bottom40.root", "$PWD/histograms/pTmin/bottom60.root",
                      "$PWD/histograms/pTmin/charm2.root", "$PWD/histograms/pTmin/charm20.root", "$PWD/histograms/pTmin/charm40.root", "$PWD/histograms/pTmin/charm60.root", 
                      "$PWD/histograms/pTmin/bb2.root", "$PWD/histograms/pTmin/bb40.root", "$PWD/histograms/pTmin/bb60.root", "$PWD/histograms/pTmin/bb120.root", 
                      "$PWD/histograms/pTmin/cc2.root", "$PWD/histograms/pTmin/cc40.root", "$PWD/histograms/pTmin/cc60.root", "$PWD/histograms/pTmin/cc120.root"};
                   
  TH1F *ttbar = new TH1F("ttbar", "pT", 60, 0, 120);
  TH1F *bottomonium = new TH1F("bottomonium", "pT", 60, 0, 120);
  TH1F *charmonium = new TH1F("charmonium", "pT", 60, 0, 120);
  TH1F *bbbar = new TH1F("bbbar", "pT", 60, 0, 120);
  TH1F *ccbar = new TH1F("ccbar", "pT", 60, 0, 120);
  TH1F *sum = new TH1F("SumpT", "pT", 60, 0, 120);

  TH1F *jet1 = new TH1F("sum jet1", "sum jet1", 60, 0, 120);
  TH1F *jet2 = new TH1F("sum jet2", "sum jet2", 60, 0, 120);
  TH1F *jet3 = new TH1F("sum jet3", "sum jet3", 60, 0, 120);
  TH1F *jet4 = new TH1F("sum jet4", "sum jet4", 60, 0, 120);
  TH1F *jet5 = new TH1F("sum jet5", "sum jet5", 60, 0, 120);
  TH1F *jet6 = new TH1F("sum jet6", "sum jet6", 60, 0, 120);
  TH1F *jet7 = new TH1F("sum jet7", "sum jet7", 60, 0, 120);

  TH1F *jetevents = new TH1F("jetevents", "jetevents", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 20; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1  = (TH1F*)infile[i].Get("30_GeV_Jet");
    TH1F *temp2  = (TH1F*)infile[i].Get("40_GeV_Jet");
    TH1F *temp3 = (TH1F*)infile[i].Get("50_GeV_Jet");
    TH1F *temp4  = (TH1F*)infile[i].Get("60_GeV_Jet");
    TH1F *temp5  = (TH1F*)infile[i].Get("70_GeV_Jet");
    TH1F *temp6  = (TH1F*)infile[i].Get("80_GeV_Jet");
    TH1F *temp7  = (TH1F*)infile[i].Get("90_GeV_Jet");

    TH1F *temponejet = (TH1F*)infile[i].Get("One_Jet");
    TH1F *temptwojet = (TH1F*)infile[i].Get("Two_Jet");
    TH1F *tempmultjet = (TH1F*)infile[i].Get("Mult_Jet");

    sum->Add(tempall);
    jetevents->Add(temponejet);
    jetevents->Add(temptwojet);
    jetevents->Add(tempmultjet);
    jet1->Add(temp1);
    jet2->Add(temp2);
    jet3->Add(temp3);
    jet4->Add(temp4);
    jet5->Add(temp5);
    jet6->Add(temp6);
    jet7->Add(temp7);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  sum->SetTitle("Jet Cuts");
  sum->SetTitleFont(132, "t");
  
  sum->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  sum->GetYaxis()->SetTitle("N_{events}");
  
  sum->GetXaxis()->SetTitleFont(132);
  sum->GetYaxis()->SetTitleFont(132);

  sum->SetLineColor(46);
  sum->SetLineWidth(3);
  sum->Draw("HIST");

  jetevents->SetLineColor(37);
  jetevents->SetLineWidth(3);
  jetevents->Draw("HIST SAME");

  jet1->SetLineColor(42);
  jet1->SetLineWidth(3);
  jet1->Draw("HIST SAME");

  jet2->SetLineColor(41);
  jet2->SetLineWidth(3);
  jet2->Draw("HIST SAME");

  jet3->SetLineColor(30);
  jet3->SetLineWidth(3);
  jet3->Draw("HIST SAME");

  jet4->SetLineColor(29);
  jet4->SetLineWidth(3);
  jet4->Draw("HIST SAME");

  jet5->SetLineColor(38);
  jet5->SetLineWidth(3);
  jet5->Draw("HIST SAME");

  jet6->SetLineColor(36);
  jet6->SetLineWidth(3);
  jet6->Draw("HIST SAME");

  jet7->SetLineColor(40);
  jet7->SetLineWidth(3);
  jet7->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(sum, "all events", "f");
  leg->AddEntry(jetevents, "events with a jet", "f");
  leg->AddEntry(jet1, "30 < Jet pT [GeV] < 40","f");
  leg->AddEntry(jet2, "40 < Jet pT [GeV] < 50", "f");
  leg->AddEntry(jet3, "50 < Jet pT [GeV] < 60", "f");
  leg->AddEntry(jet4, "60 < Jet pT [GeV] < 70", "f");
  leg->AddEntry(jet5, "70 < Jet pT [GeV] < 80", "f");
  leg->AddEntry(jet6, "80 < Jet pT [GeV] < 90", "f");
  leg->AddEntry(jet7, "90 < Jet pT [GeV]", "f");

  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/JetPt.png");
  cx->Close();
}