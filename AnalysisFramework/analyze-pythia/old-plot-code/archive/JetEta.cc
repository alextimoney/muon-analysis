// LJPR.C
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile[9] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                     "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root"};

  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *jet1 = new TH1F("sum jet1", "sum jet1", 60, 0, 120);
  TH1F *jet2 = new TH1F("sum jet2", "sum jet2", 60, 0, 120);
  TH1F *jet3 = new TH1F("sum jet3", "sum jet3", 60, 0, 120);
  TH1F *jet4 = new TH1F("sum jet4", "sum jet4", 60, 0, 120);
  TH1F *jet5 = new TH1F("sum jet5", "sum jet5", 60, 0, 120);
  TH1F *jet6 = new TH1F("sum jet6", "sum jet6", 60, 0, 120);
  TH1F *jet7 = new TH1F("sum jet7", "sum jet7", 60, 0, 120);
  TH1F *jet8 = new TH1F("sum jet8", "sum jet8", 60, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 7; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1  = (TH1F*)infile[i].Get("JetEta1");
    TH1F *temp2 = (TH1F*)infile[i].Get("JetEta2");
    TH1F *temp3  = (TH1F*)infile[i].Get("JetEta3");
    TH1F *temp4  = (TH1F*)infile[i].Get("JetEta4");
    TH1F *temp5  = (TH1F*)infile[i].Get("JetEta5");
    TH1F *temp6  = (TH1F*)infile[i].Get("JetEta6");
    TH1F *temp7  = (TH1F*)infile[i].Get("JetEta7");
    TH1F *temp8  = (TH1F*)infile[i].Get("JetEta8");

    all_muons->Add(tempall);
    jet1->Add(temp1);
    jet2->Add(temp2);
    jet3->Add(temp3);
    jet4->Add(temp4);
    jet5->Add(temp5);
    jet6->Add(temp6);
    jet7->Add(temp7);
    jet8->Add(temp8);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Lead Jet Pseudorapidity");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

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

  jet8->SetLineColor(48);
  jet8->SetLineWidth(3);
  jet8->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(jet1, "0 < |eta| < 0.5","f");
  leg->AddEntry(jet2, "0.5 < |eta| < 1", "f");
  leg->AddEntry(jet3, "1 < |eta| < 1.5", "f");
  leg->AddEntry(jet4, "1.5 < |eta| < 2", "f");
  leg->AddEntry(jet5, "2 < |eta| < 2.5", "f");
  leg->AddEntry(jet6, "2.5 < |eta| < 5", "f");
  leg->AddEntry(jet7, "5 < |eta| < 10", "f");
  leg->AddEntry(jet8, "10 < |eta|", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/muon-pt/JetEta.png");
  cx->Close();
}
