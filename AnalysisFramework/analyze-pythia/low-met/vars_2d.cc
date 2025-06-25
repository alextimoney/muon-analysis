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
  
  TH2F* Isolation = new TH2F ("Isolation", "Muon isolation and pT", 60, 0, 80, 60, 0, 100);
  TH2F* MuonJetR = new TH2F ("MuonJetR", "Muon/Jet dR and Muon pT", 60, 0, 80, 60, 0, 10);
  TH2F* MuonJetPhi = new TH2F ("MuonJetPhi", "Muon/Jet Phi and Muon pT", 60, 0, 80, 60, 0, M_PI);
  TH2F* MetMuonPhi = new TH2F ("MetMuonPhi", "Muon/Met Phi and Muon pT", 60, 0, 80, 60, 0, M_PI);
  TH2F* JetpT = new TH2F ("JetpT", "Jet pT and Muon pT", 60, 0, 80, 60, 0, 120);

  for (int i = 0; i < 28; i++) {
    TH2F *temp1 = (TH2F*)infile[i].Get("TH2_Isolation");
    TH2F *temp2 = (TH2F*)infile[i].Get("TH2_MuonJetR");
    TH2F *temp3 = (TH2F*)infile[i].Get("TH2_MuonJetPhi");
    TH2F *temp4 = (TH2F*)infile[i].Get("TH2_MetMuonPhi");
    TH2F *temp5 = (TH2F*)infile[i].Get("TH2_JetpT");

    Isolation->Add(temp1);
    MuonJetR->Add(temp2);
    MuonJetPhi->Add(temp3);
    MetMuonPhi->Add(temp4);
    JetpT->Add(temp5);
  }

  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(132, "t");

  TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
  c2->cd();

  MuonJetR->SetTitle("Jet & Muon Delta r vs. Muon pT");
  MuonJetR->SetTitleFont(132, "t");

  MuonJetR->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  MuonJetR->GetYaxis()->SetTitle("delta r between Lead Jet & Muon");
  MuonJetR->GetXaxis()->SetTitleFont(132);
  MuonJetR->GetYaxis()->SetTitleFont(132);
  MuonJetR->SetContour(1000);
  MuonJetR->Draw("colz");

  c2->SetLogz();
  c2->Print("./plots/2d/r_MuonJet.png");
  c2->Close();

  TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
  c3->cd();

  MuonJetPhi->SetTitle("Jet & Muon Delta Phi vs. Muon pT");
  MuonJetPhi->SetTitleFont(132, "t");
  MuonJetPhi->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  MuonJetPhi->GetYaxis()->SetTitle("Phi between Lead Jet & Muon");
  MuonJetPhi->GetXaxis()->SetTitleFont(132);
  MuonJetPhi->GetYaxis()->SetTitleFont(132);
  MuonJetPhi->SetContour(1000);
  MuonJetPhi->Draw("colz");

  c3->SetLogz();
  c3->Print("./plots/2d/phi_MuonJet.png");
  c3->Close();

  TCanvas *c4 = new TCanvas("c4","c4", 800, 600);
  c4->cd();

  MetMuonPhi->SetTitle("Met & Muon Delta Phi vs. Muon pT");
  MetMuonPhi->SetTitleFont(132, "t");
  MetMuonPhi->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  MetMuonPhi->GetYaxis()->SetTitle("Phi between Met & Muon");
  MetMuonPhi->GetXaxis()->SetTitleFont(132);
  MetMuonPhi->GetYaxis()->SetTitleFont(132);
  MetMuonPhi->SetContour(1000);
  MetMuonPhi->Draw("colz");

  c4->SetLogz();
  c4->Print("./plots/2d/phi_MetMuon.png");
  c4->Close();

  TCanvas *c5 = new TCanvas("c5","c5", 800, 600);
  c5->cd();

  JetpT->SetTitle("Lead Jet pT vs. Muon pT");
  JetpT->SetTitleFont(132, "t");
  JetpT->GetXaxis()->SetTitle("Bare Muon pT [GeV]");
  JetpT->GetYaxis()->SetTitle("Lead Jet pT [GeV]");
  JetpT->GetXaxis()->SetTitleFont(132);
  JetpT->GetYaxis()->SetTitleFont(132);
  JetpT->SetContour(1000);
  JetpT->Draw("colz");

  c5->SetLogz();
  c5->Print("./plots/2d/pT_Jets.png");
  c5->Close();
}