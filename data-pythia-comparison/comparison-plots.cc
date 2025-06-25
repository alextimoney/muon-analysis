// rates.cc
// ------------
// Rescales muon pT histograms to match bins from L1 trigger

{
  TFile infile[28] = {"$PWD/../AnalysisFramework/analyze-pythia/histograms/run1/ttbar-dilep.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/run1/ttbar-semilep.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/run1/wbos.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/run1/zbos.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/run1/gamma.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bottom2.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bottom20.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bottom40.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bottom60.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bottom120.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm2.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm10.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm20.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm40.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm60.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/charm120.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb2.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb20.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb40.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb60.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb120.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/bb200.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc2.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc20.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc40.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc60.root", 
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc120.root",
                      "$PWD/../AnalysisFramework/analyze-pythia/histograms/pTmin/cc200.root"
                      };
  TFile runfile = "$PWD/../toroid-off-analysis-plots/mtree_out/run-data.root";
  
  int num_bins = 60;
  double target_n = 121575003;
  float L1_prescale = 7.386750749;
  float nEvents = 0;
  int nMuons = 0;

  TH1F *pythia_pT = new TH1F("pythia_pT", "pythia_pT", num_bins, 0, 120);
  TH1F *pythia_pT_norm_n = new TH1F("pythia_pT_norm_n", "pythia_pT_norm_n", num_bins, 0, 120);
  TH1F *pythia_P = new TH1F("pythia_P", "pythia_P", num_bins, 0, 120);
  TH1F *run_pT = (TH1F*)runfile.Get("muon_pT");
  TH1F *run_P = (TH1F*)runfile.Get("muon_P");

  for (int i = 0; i < 28; i++) {
    TH1F *temp_pythia_pT = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp_pythia_P = (TH1F*)infile[i].Get("Muon_P");
    TH1F *tempN = (TH1F*)infile[i].Get("WeightedMuons");
    
    nEvents += tempN->GetSumOfWeights();

    pythia_pT->Add(temp_pythia_pT); 
    pythia_pT_norm_n->Add(temp_pythia_pT);

    pythia_P->Add(temp_pythia_P);
  }

  // Normalization to # of events
  float scale_factor = target_n/nEvents;
  pythia_pT_norm_n->Scale(scale_factor);

  // Prescale
  pythia_pT->Scale(1/L1_prescale);
  pythia_P->Scale(1/L1_prescale);

  // Convert from MeV to GeV
  run_pT->GetXaxis()->SetLimits(0, 120);
  run_P->GetXaxis()->SetLimits(0, 120);

  // Plotting
  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *c1 = new TCanvas("c1","c1", 800, 600);
  c1->cd();

  pythia_pT->SetTitle("Comparison of Muon p_{T} from Pythia to Run Data");
  pythia_pT->SetTitleFont(132, "t");
  
  pythia_pT->GetXaxis()->SetTitle("Muon p_{T} [GeV]");
  pythia_pT->GetYaxis()->SetTitle("N_{muons}");
  pythia_pT->GetYaxis()->SetRangeUser(10, 10000000000);
  pythia_pT->GetXaxis()->SetRangeUser(7, 80);
  
  pythia_pT->GetXaxis()->SetTitleFont(132);
  pythia_pT->GetYaxis()->SetTitleFont(132);

  pythia_pT->SetLineColor(45);
  pythia_pT->SetLineWidth(3);
  pythia_pT->Draw("HIST");

  // pythia_pT_norm_n->SetLineColor(38);
  // pythia_pT_norm_n->SetLineWidth(3);
  // pythia_pT_norm_n->Draw("HIST SAME");

  run_pT->SetLineColor(36);
  run_pT->SetLineWidth(3);
  run_pT->Draw("HIST SAME");

  cout << pythia_pT->Integral(30, 1000) << endl;

  auto leg = new TLegend(0.7, 0.8, 0.9, 0.89);
  leg->AddEntry(pythia_pT, "Pythia", "l");
  // leg->AddEntry(pythia_pT_norm_n, "Pythia (# of events scaling)", "l");
  leg->AddEntry(run_pT, "Run Data", "l");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->Draw();

  c1->SetLogy();
  c1->Print("comparison_pT.png");
  c1->Close();

  TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
  c2->cd();

  pythia_P->SetTitle("Comparison of Muon p from Pythia to Run Data");
  pythia_P->SetTitleFont(132, "t");
  
  pythia_P->GetXaxis()->SetTitle("Muon P [GeV]");
  pythia_P->GetYaxis()->SetTitle("N_{muons}");
  pythia_P->GetYaxis()->SetRangeUser(10, 10000000000);
  pythia_P->GetXaxis()->SetRangeUser(7, 80);
  
  pythia_P->GetXaxis()->SetTitleFont(132);
  pythia_P->GetYaxis()->SetTitleFont(132);

  pythia_P->SetLineColor(45);
  pythia_P->SetLineWidth(3);
  pythia_P->Draw("HIST");

  run_P->SetLineColor(36);
  run_P->SetLineWidth(3);
  run_P->Draw("HIST SAME");

  auto leg2 = new TLegend(0.7, 0.8, 0.9, 0.89);
  leg2->AddEntry(pythia_P, "Pythia", "l");
  leg2->AddEntry(run_P, "Run Data", "l");
  leg2->SetTextSize(0.035);
  leg2->SetBorderSize(0);
  leg2->Draw();

  c2->SetLogy();
  c2->Print("comparison_P.png");
  c2->Close();

  TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
  c3->cd();

  TH1F *ratio_pT = new TH1F("ratio_pT", "ratio_pT", num_bins, 0, 120);
  TH1F *ratio_P = new TH1F("ratio_P", "ratio_P", num_bins, 0, 120);

  ratio_pT->Add(pythia_pT);
  ratio_pT->Divide(run_pT);

  ratio_P->Add(pythia_P);
  ratio_P->Divide(run_P);

  ratio_pT->SetTitle("Ratios of Pythia and Run Data");
  ratio_pT->SetTitleFont(132, "t");
  ratio_pT->GetXaxis()->SetRangeUser(7, 80);
  ratio_pT->GetYaxis()->SetRangeUser(0.09, 20);
  
  ratio_pT->GetXaxis()->SetTitle("[GeV]");
  ratio_pT->GetYaxis()->SetTitle("N_{muons}");
  
  ratio_pT->GetXaxis()->SetTitleFont(132);
  ratio_pT->GetYaxis()->SetTitleFont(132);

  ratio_pT->SetLineColor(30);
  ratio_pT->SetLineWidth(3);
  ratio_pT->Draw("HIST");

  ratio_P->SetLineColor(38);
  ratio_P->SetLineWidth(3);
  ratio_P->Draw("HIST SAME");

  auto leg3 = new TLegend(0.7, 0.8, 0.9, 0.89);
  leg3->AddEntry(ratio_pT, "Muon p_{T}", "l");
  leg3->AddEntry(ratio_P, "Muon P", "l");
  leg3->SetTextSize(0.035);
  leg3->SetBorderSize(0);
  leg3->Draw();

  line1 = new TLine(7, 2, 80, 2);
  line1->SetLineColor(48);
  line1->SetLineWidth(3);
  line1->SetLineStyle(2);
  line1->Draw();

  line2 = new TLine(7, 1, 80, 1);
  line2->SetLineColor(35);
  line2->SetLineWidth(3);
  line2->SetLineStyle(2);
  line2->Draw();

  line3 = new TLine(7, 0.5, 80, 0.5);
  line3->SetLineColor(48);
  line3->SetLineWidth(3);
  line3->SetLineStyle(2);
  line3->Draw();

  c3->SetLogy();
  c3->Print("comparison-ratio.png");
  c3->Close();

}
