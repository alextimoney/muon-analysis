// Muondelta_rlation.cc
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
  
  TH1F *all_muons = new TH1F("sum", "sum", 60, 0, 120);
  TH1F *delta_r1 = new TH1F("sum delta_r1", "sum delta_r1", 60, 0, 120);
  TH1F *delta_r2 = new TH1F("sum delta_r2", "sum delta_r2", 60, 0, 120);
  TH1F *delta_r3 = new TH1F("sum delta_r3", "sum delta_r3", 60, 0, 120);
  TH1F *delta_r4 = new TH1F("sum delta_r4", "sum delta_r4", 60, 0, 120);
  TH1F *delta_r5 = new TH1F("sum delta_r5", "sum delta_r5", 60, 0, 120);
  TH1F *delta_r6 = new TH1F("sum delta_r6", "sum delta_r6", 60, 0, 120);
  TH1F *delta_r7 = new TH1F("sum delta_r7", "sum delta_r7", 60, 0, 120);
  TH1F *delta_r8 = new TH1F("sum delta_r8", "sum delta_r8", 60, 0, 120);

  TH1F *jetevents = new TH1F("jetevents", "jetevents", 60, 0, 120);


  for (int i = 0; i < 28; i++) {
    TH1F *tempall = (TH1F*)infile[i].Get("Bare_Muon_pT");
    TH1F *temp1 = (TH1F*)infile[i].Get("JetMuonR1");
    TH1F *temp2 = (TH1F*)infile[i].Get("JetMuonR2");
    TH1F *temp3 = (TH1F*)infile[i].Get("JetMuonR3");
    TH1F *temp4 = (TH1F*)infile[i].Get("JetMuonR4");
    TH1F *temp5 = (TH1F*)infile[i].Get("JetMuonR5");
    TH1F *temp6 = (TH1F*)infile[i].Get("JetMuonR6");
    TH1F *temp7 = (TH1F*)infile[i].Get("JetMuonR7");
    TH1F *temp8 = (TH1F*)infile[i].Get("JetMuonR8");

    TH1F *temponejet = (TH1F*)infile[i].Get("One_Jet");
    TH1F *temptwojet = (TH1F*)infile[i].Get("Two_Jet");
    TH1F *tempmultjet = (TH1F*)infile[i].Get("Mult_Jet");

    all_muons->Add(tempall);

    jetevents->Add(temponejet);
    jetevents->Add(temptwojet);
    jetevents->Add(tempmultjet);

    delta_r1->Add(temp1);
    delta_r2->Add(temp2);
    delta_r3->Add(temp3);
    delta_r4->Add(temp4);
    delta_r5->Add(temp5);
    delta_r6->Add(temp6);
    delta_r7->Add(temp7);
    delta_r8->Add(temp8);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *cx = new TCanvas("cx","cx", 800, 600);
  cx->cd();

  all_muons->SetTitle("Jet & Muon Delta r 'Trigger' Passes");
  all_muons->SetTitleFont(132, "t");

  all_muons->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  all_muons->GetYaxis()->SetTitle("N_{events}");
  
  all_muons->GetXaxis()->SetTitleFont(132);
  all_muons->GetYaxis()->SetTitleFont(132);

  all_muons->SetLineColor(46);
  all_muons->SetLineWidth(3);
  all_muons->Draw("HIST");

  jetevents->SetLineColor(1);
  jetevents->SetLineWidth(3);
  jetevents->Draw("HIST SAME");

  delta_r1->SetLineColor(42);
  delta_r1->SetLineWidth(3);
  delta_r1->Draw("HIST SAME");

  delta_r2->SetLineColor(41);
  delta_r2->SetLineWidth(3);
  delta_r2->Draw("HIST SAME");

  delta_r3->SetLineColor(30);
  delta_r3->SetLineWidth(3);
  delta_r3->Draw("HIST SAME");

  delta_r4->SetLineColor(29);
  delta_r4->SetLineWidth(3);
  delta_r4->Draw("HIST SAME");

  delta_r5->SetLineColor(38);
  delta_r5->SetLineWidth(3);
  delta_r5->Draw("HIST SAME");

  delta_r6->SetLineColor(36);
  delta_r6->SetLineWidth(3);
  delta_r6->Draw("HIST SAME");

  delta_r7->SetLineColor(48);
  delta_r7->SetLineWidth(3);
  delta_r7->Draw("HIST SAME");

  delta_r8->SetLineColor(40);
  delta_r8->SetLineWidth(3);
  delta_r8->Draw("HIST SAME");

  auto leg = new TLegend(0.6, 0.60, 0.9, 0.89);
  leg->AddEntry(all_muons, "All Events", "f");
  leg->AddEntry(jetevents, "Events with a Jet", "f");
  leg->AddEntry(delta_r1, "Delta r btwn Jet & Mu < 1","f");
  leg->AddEntry(delta_r2, "0.25 < Delta r btwn Jet & Mu < 0.5", "f");
  leg->AddEntry(delta_r3, "0.5 < Delta r btwn Jet & Mu < 1", "f");
  leg->AddEntry(delta_r4, "1 < Delta r btwn Jet & Mu < 2", "f");
  leg->AddEntry(delta_r5, "2 < Delta r btwn Jet & Mu < 3", "f");
  leg->AddEntry(delta_r6, "3 < Delta r btwn Jet & Mu < 4", "f");
  leg->AddEntry(delta_r7, "4 < Delta r btwn Jet & Mu < 5", "f");
  leg->AddEntry(delta_r8, "5 < Delta r btwn Jet & Mu", "f");
  leg->SetTextSize(0.035);
  leg->Draw();

  cx->SetLogy();
  cx->Print("./plots/delta_r.png");
  cx->Close();

}