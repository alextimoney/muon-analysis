// nJets.cc
// ------------
// Takes histograms from analysis files and analyse them, and creates final plots of the desired histograms

{

  // Load the analysis files
  // =======================

  TFile infile1[9] = {"$PWD/histograms/run1/bottomonium.root", "$PWD/histograms/run1/charmonium.root",
                     "$PWD/histograms/run1/bbbar.root", "$PWD/histograms/run1/ccbar.root", 
                     "$PWD/histograms/run1/ttbar-dilep.root", "$PWD/histograms/run1/ttbar-semilep.root",
                     "$PWD/histograms/run1/wbos.root", "$PWD/histograms/run1/zbos.root", "$PWD/histograms/run1/gamma.root"};

  TFile infile2[9] = {"$PWD/histograms/no-parton-shower/bottomonium-ps.root", "$PWD/histograms/no-parton-shower/charmonium-ps.root",
                     "$PWD/histograms/no-parton-shower/bbbar-ps.root", "$PWD/histograms/no-parton-shower/ccbar-ps.root", 
                     "$PWD/histograms/no-parton-shower/ttbar-dilep-ps.root", "$PWD/histograms/no-parton-shower/ttbar-semilep-ps.root",
                     "$PWD/histograms/no-parton-shower/wbos-ps.root", "$PWD/histograms/no-parton-shower/zbos-ps.root", 
                     "$PWD/histograms/no-parton-shower/gamma-ps.root"};

  TH1F *all_muons = new TH1F("sum", "sum", 50, 0, 120);
  TH1F *all_muons_no_ps = new TH1F("to", "to", 50, 0, 120);
  TH1F *ratio1 = new TH1F("ratio of all muons to TO muons", "rat", 50, 0, 120);

  // Get the histograms
  // ==================

  for (int i = 0; i < 9; i++) {
    TH1F *tempall1 = (TH1F*)infile1[i].Get("Bare_Muon_pT");
    TH1F *tempall2 = (TH1F*)infile2[i].Get("Bare_Muon_pT");

    all_muons->Add(tempall1);
    all_muons_no_ps->Add(tempall2);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

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

  all_muons->SetTitle("Parton shower on vs. off");
  all_muons->SetTitleFont(132, "t");
  
  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{muons}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(30);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  all_muons_no_ps->SetLineColor(38);
  all_muons_no_ps->SetLineWidth(3);
  all_muons_no_ps->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "Parton shower ON", "f");
  leg->AddEntry(all_muons_no_ps, "Parton shower OFF", "f");

  leg->SetTextSize(0.035);
  leg->Draw();

  pad1->SetLogy();

  // Make the ratio plot
  pad2->cd();

  ratio1->Add(all_muons_no_ps);
  ratio1->Divide(all_muons);

  ratio1->SetLineColor(38);
  ratio1->SetLineWidth(3);
  ratio1->Draw("HIST");

  ratio1->GetYaxis()->SetLabelSize(0.07);
  ratio1->GetXaxis()->SetLabelSize(0.07);
  ratio1->GetYaxis()->SetTitle("OFF/ON");
  ratio1->GetYaxis()->SetTitleSize(0.09);
  ratio1->GetYaxis()->SetTitleOffset(0.45);

  line = new TLine(0, 1, 120, 1);
  line->SetLineColor(35);
  line->SetLineWidth(3);
  line->SetLineStyle(2);
  line->Draw();

  pad2->SetLogy();

  cx->Print("./plots/parton-shower/ratio.png");
  cx->Close();
}