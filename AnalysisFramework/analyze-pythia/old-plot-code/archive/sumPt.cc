// sumPt.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

TFile infile[9] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                     "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root"};

  TH1F *all_muons = new TH1F("sum", "sum", 50, 0, 120);
  TH1F *sum1 = new TH1F("sum1", "sum1", 50, 0, 120);
  TH1F *sum2 = new TH1F("sum2", "sum2", 50, 0, 120);
  TH1F *sum3 = new TH1F("sum3", "sum3", 50, 0, 120);
  TH1F *sum4 = new TH1F("sum4", "sum4", 50, 0, 120);
  TH1F *sum5 = new TH1F("sum5", "sum5", 50, 0, 120);
  TH1F *sum6 = new TH1F("sum6", "sum6", 50, 0, 120);
  TH1F *sum7 = new TH1F("sum7", "sum7", 50, 0, 120);
  TH1F *sum8 = new TH1F("sum8", "sum8", 50, 0, 120);


  for (int i = 0; i < 7; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1 = (TH1F*)infile[i].Get("SumMJMPt1");
    TH1F *temp2 = (TH1F*)infile[i].Get("SumMJMPt2");
    TH1F *temp3 = (TH1F*)infile[i].Get("SumMJMPt3");
    TH1F *temp4 = (TH1F*)infile[i].Get("SumMJMPt4");
    TH1F *temp5 = (TH1F*)infile[i].Get("SumMJMPt5");
    TH1F *temp6 = (TH1F*)infile[i].Get("SumMJMPt6");
    TH1F *temp7 = (TH1F*)infile[i].Get("SumMJMPt7");
    TH1F *temp8 = (TH1F*)infile[i].Get("SumMJMPt8");

    all_muons->Add(tempall);
    sum1->Add(temp1);
    sum2->Add(temp2);
    sum3->Add(temp3);
    sum4->Add(temp4);
    sum5->Add(temp5);
    sum6->Add(temp6);
    sum7->Add(temp7);
    sum8->Add(temp8);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Sum of pT (MET, Jet)");
  all_muons->SetTitleFont(132, "t");

  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  sum1->SetLineColor(42);
  sum1->SetLineWidth(3);
  sum1->Draw("HIST SAME");

  sum2->SetLineColor(41);
  sum2->SetLineWidth(3);
  sum2->Draw("HIST SAME");

  sum3->SetLineColor(30);
  sum3->SetLineWidth(3);
  sum3->Draw("HIST SAME");

  sum4->SetLineColor(29);
  sum4->SetLineWidth(3);
  sum4->Draw("HIST SAME");

  sum5->SetLineColor(38);
  sum5->SetLineWidth(3);
  sum5->Draw("HIST SAME");

  sum6->SetLineColor(36);
  sum6->SetLineWidth(3);
  sum6->Draw("HIST SAME");

  sum7->SetLineColor(40);
  sum7->SetLineWidth(3);
  sum7->Draw("HIST SAME");

  sum8->SetLineColor(48);
  sum8->SetLineWidth(3);
  sum8->Draw("HIST SAME");

  auto leg = new TLegend(0.55, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "all events", "f");
  leg->AddEntry(sum1, "0 < Sum pT [GeV] < 5","f");
  leg->AddEntry(sum2, "5 < Sum pT [GeV] < 10", "f");
  leg->AddEntry(sum3, "10 < Sum pT [GeV] < 20", "f");
  leg->AddEntry(sum4, "20 < Sum pT [GeV] < 30", "f");
  leg->AddEntry(sum5, "30 < Sum pT [GeV] < 40", "f");
  leg->AddEntry(sum6, "40 < Sum pT [GeV] < 50", "f");
  leg->AddEntry(sum7, "50 < Sum pT [GeV] < 60", "f");
  leg->AddEntry(sum8, "60 < Sum pT [GeV]", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/all_events/sumPtMJ.png");
  cx->Close();

}