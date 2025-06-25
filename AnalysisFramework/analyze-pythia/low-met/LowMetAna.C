#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "TH1F.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TString.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <vector>
#include<algorithm>
#include <math.h>
#include <dirent.h>

// ================= //
// !!! FUNCTIONS !!! //
// ================= //

// =========================================================================================================================
// Note: This is function used in kinematic calculations
// Returns a value between 0 to pi
double delta_phi(double phi1, double phi2) 
{
  const double PI=2.0*acos(0.);
  const double TWOPI=2.0*PI;
  
  if (phi1<0) phi1= phi1+TWOPI;
  if (phi2<0) phi2= phi2+TWOPI;

  double PHI=fabs(phi1-phi2);

  return (PHI<=PI)? PHI : TWOPI-PHI;
}

double  delta_r(double phi1, double phi2, double eta1, double eta2) {

  double delta_phi_r = phi1-phi2;
  double delta_eta_r = eta1-eta2;
  double delta_r = sqrt(pow(delta_phi_r, 2)+pow(delta_eta_r, 2));

  return delta_r;
}
// =========================================================================================================================

// ============================= //
// DEFINE YOUR HISTOGRAMS HERE!! //
// ============================= //

int num_bins = 60;

// Binning for pT-related histograms
Float_t ptlead_bins[] = {30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,350.,400.,450.,500.,600.,700.,800.,900.,1000.};
Int_t ptlead_nbin = sizeof(ptlead_bins)/sizeof(Float_t) - 1;

// Declare Root Histograms //
// ------------------------//

// Muon kinematic distributions
TH1F* BareMuon_pT = new TH1F("Bare_Muon_pT", "Momentum of muons with 1 < |eta| < 2.5 normalized to cross-section", num_bins, 0, 120);
TH1F* BareMuon_pT_norm1 = new TH1F("Bare_Muon_pT_norm1", "Momentum of muons with 1 < |eta| < 2.5 normalized to 1", num_bins, 0, 120);
TH1F* BareMuon_pT_no_norm = new TH1F("BareMuon_pT_no_norm", "Momentum of muons without efficiency weighting", num_bins, 0, 120);
TH1F* Muon_P = new TH1F("Muon_P", "Magnitude of muon momentum with 1 < |eta| < 2.5 normalized to cross-section", num_bins, 0, 120);
TH1F* Muon_P_no_norm = new TH1F("Muon_P_no_norm", "Magnitude of muon momentum with 1 < |eta| < 2.5 (raw data)", 120, 0, 120);
TH1F* WeightedMuons = new TH1F("WeightedMuons", "number of events with muon", 5, 0, 2);

// Other kinematic variable distributions
TH1F* JetPt = new TH1F("JetPt", "Momentum of Jets", num_bins, 0, 160);
TH1F* JetEta = new TH1F("JetEta", "Eta of Jets", num_bins, 0, 2.5);
TH1F* nJets = new TH1F("nJets", "Number of Jets", num_bins, 0, 5);
TH1F* nMuons = new TH1F("nMuons", "Number of muons", num_bins, 0, 5);
TH1F* JetMuonPhi = new TH1F("JetMuonPhi", "Phi between jet and muon", num_bins, 0, M_PI);
TH1F* JetMuonR = new TH1F("JetMuonR", "Delta r between jet and muon", num_bins, 0, 10);
TH1F* MetJetPhi = new TH1F("MetJetPhi", "Phi between jet and Met", num_bins, 0, M_PI);
TH1F* MetMuonPhi = new TH1F("MetMuonPhi", "Phi between Met and muon", num_bins, 0, M_PI);
TH1F* MetPt = new TH1F("MetPt", "Momentum of Met", num_bins, 0, 140);
TH1F* MetJetPt = new TH1F("MetJetPt", "Momentum of Met and Jets", num_bins, 0, 180);
TH1F* MuonIsolation = new TH1F("MuonIsolation", "Sum of momentum in cone around muon of r = 0.1", num_bins, 0, 200);

// Other kinematic variable distributions with the desired cut on missing ET
TH1F* JetPt_MetCut = new TH1F("JetPt_MetCut", "Momentum of Jets w 30 GeV Met cut", num_bins, 0, 160);
TH1F* JetEta_MetCut = new TH1F("JetEta_MetCut", "Eta of Jets w 30 GeV Met cut", num_bins, 0, 2.5);
TH1F* nJets_MetCut = new TH1F("nJets_MetCut", "Number of Jets w 30 GeV Met cut", num_bins, 0, 5);
TH1F* nMuons_MetCut = new TH1F("nMuons_MetCut", "Number of muons w 30 GeV Met cut", num_bins, 0, 5);
TH1F* JetMuonPhi_MetCut = new TH1F("JetMuonPhi_MetCut", "Phi between jet and muon w 30 GeV Met cut", num_bins, 0, M_PI);
TH1F* JetMuonR_MetCut = new TH1F("JetMuonR_MetCut", "Delta r between jet and muon w 30 GeV Met cut", num_bins, 0, M_PI);
TH1F* MetJetPhi_MetCut = new TH1F("MetJetPhi_MetCut", "Phi between jet and Met w 30 GeV Met cut", num_bins, 0, M_PI);
TH1F* MetMuonPhi_MetCut = new TH1F("MetMuonPhi_MetCut", "Phi between Met and muon w 30 GeV Met cut", num_bins, 0, M_PI);
TH1F* MetJetPt_MetCut = new TH1F("MetJetPt_MetCut", "Pt sum of Met and Jet w 30 GeV Met cut", num_bins, 0, 180);
TH1F* MuonIsolation_MetCut = new TH1F("MuonIsolation_MetCut", "Sum of momentum in cone around muon of r = 0.1 w 30 GeV Met cut", num_bins, 0, 200);

// Muon distributions for cuts for number of muons and Jets
TH1F* OneMuon = new TH1F("OneMuon", "Momentum of muons in events with one muon, eta cut, normalized", num_bins, 0, 120);
TH1F* TwoMuon = new TH1F("TwoMuon", "Momentum of muons in events with two muons, eta cut, normalized", num_bins, 0, 120);
TH1F* ThreeMuon = new TH1F("ThreeMuon", "Momentum of muons in events with three muons, eta cut, normalized", num_bins, 0, 120);
TH1F* No_Jet = new TH1F("No_Jet", "Momentum of muons in events with no Jets", num_bins, 0, 120);
TH1F* One_Jet = new TH1F("One_Jet", "Momentum of muons in events with one jet", num_bins, 0, 120);
TH1F* Two_Jet = new TH1F("Two_Jet", "Momentum of muons in events with two Jets", num_bins, 0, 120);
TH1F* Mult_Jet = new TH1F("Mult_Jet", "Momentum of muons in events with multiple Jets", num_bins, 0, 120);

// Muon distributions for cuts on jet pT 
TH1F* Jet30GeV = new TH1F("30_GeV_Jet", "Momentum of muons in events with Jets with 30 GeV < pT < 40 GeV", num_bins, 0, 120);
TH1F* Jet40GeV = new TH1F("40_GeV_Jet", "Momentum of muons in events with Jets 40 GeV < pT < 50 GeV", num_bins, 0, 120);
TH1F* Jet50GeV = new TH1F("50_GeV_Jet", "Momentum of muons in events with Jets 50 GeV < pT < 60 GeV", num_bins, 0, 120);
TH1F* Jet60GeV = new TH1F("60_GeV_Jet", "Momentum of muons in events with Jets 60 GeV < pT < 70 GeV", num_bins, 0, 120);
TH1F* Jet70GeV = new TH1F("70_GeV_Jet", "Momentum of muons in events with Jets 70 GeV < pT < 80 GeV", num_bins, 0, 120);
TH1F* Jet80GeV = new TH1F("80_GeV_Jet", "Momentum of muons in events with Jets 80 GeV < pT < 90 GeV", num_bins, 0, 120);
TH1F* Jet90GeV = new TH1F("90_GeV_Jet", "Momentum of muons in events with Jets 30 GeV < pT < 40 GeV", num_bins, 0, 120);

// Muon distributions for cuts on the jet eta 
TH1F* JetEta1 = new TH1F("JetEta1", "Momentum of muons with leading jet 0 < |eta| < 0.5", num_bins, 0, 120);
TH1F* JetEta2 = new TH1F("JetEta2", "Momentum of muons with leading jet 0.5 < |eta| < 1", num_bins, 0, 120);
TH1F* JetEta3 = new TH1F("JetEta3", "Momentum of muons with leading jet 1 < |eta| < 1.5", num_bins, 0, 120);
TH1F* JetEta4 = new TH1F("JetEta4", "Momentum of muons with leading jet 1.5 < |eta| < 2", num_bins, 0, 120);
TH1F* JetEta5 = new TH1F("JetEta5", "Momentum of muons with leading jet 2 < |eta| < 2.5", num_bins, 0, 120);
TH1F* JetEta6 = new TH1F("JetEta6", "Momentum of muons with leading jet 2.5 < |eta| < 5", num_bins, 0, 120);
TH1F* JetEta7 = new TH1F("JetEta7", "Momentum of muons with leading jet 5 < |eta| < 10.", num_bins, 0, 120);
TH1F* JetEta8 = new TH1F("JetEta8", "Momentum of muons with leading jet 10 < |eta| < infin.", num_bins, 0, 120);

// Muon distributions for cuts on Met
TH1F* Met1 = new TH1F("Met1", "Momentum of muons in events with MET < 20 GeV", num_bins, 0, 120);
TH1F* Met2 = new TH1F("Met2", "Momentum of muons in events with 20 GeV < MET < 40 GeV", num_bins, 0, 120);
TH1F* Met3 = new TH1F("Met3", "Momentum of muons in events with 40 GeV MET < 60 GeV", num_bins, 0, 120);
TH1F* Met4 = new TH1F("Met4", "Momentum of muons in events with 60 GeV < MET < 80 GeV", num_bins, 0, 120);
TH1F* Met5 = new TH1F("Met5", "Momentum of muons in events with 80 GeV < MET < 100 GeV", num_bins, 0, 120);
TH1F* Met6 = new TH1F("Met6", "Momentum of muons in events with 100 GeV < MET < 120 GeV", num_bins, 0, 120);
TH1F* Met7 = new TH1F("Met7", "Momentum of muons in events with 120 GeV < MET < 140 GeV", num_bins, 0, 120);
TH1F* Met8 = new TH1F("Met8", "Momentum of muons in events with 140 < MET", num_bins, 0, 120);

// Muon distributions for cuts on Muon Isolation
TH1F* Iso1 = new TH1F("Iso1", "Momentum of muons in events passing iso trig of 10 GeV", num_bins, 0, 120);
TH1F* Iso2 = new TH1F("Iso2", "Momentum of muons in events passing iso trig of 20 GeV", num_bins, 0, 120);
TH1F* Iso3 = new TH1F("Iso3", "Momentum of muons in events passing iso trig of 30 GeV", num_bins, 0, 120);
TH1F* Iso4 = new TH1F("Iso4", "Momentum of muons in events passing iso trig of 40 GeV", num_bins, 0, 120);
TH1F* Iso5 = new TH1F("Iso5", "Momentum of muons in events passing iso trig of 50 GeV", num_bins, 0, 120);
TH1F* Iso6 = new TH1F("Iso6", "Momentum of muons in events passing iso trig of 60 GeV", num_bins, 0, 120);
TH1F* Iso7 = new TH1F("Iso7", "Momentum of muons in events passing iso trig of 70 GeV", num_bins, 0, 120);

// Muon distributions for cuts on azimuthal angle between Met and Jet
TH1F* MetJet1 = new TH1F("MetJet1", "Momentum of muons with angle btwn Met and jet 0 < |phi| < pi/4", num_bins, 0, 120);
TH1F* MetJet2 = new TH1F("MetJet2", "Momentum of muons with angle btwn Met and jet pi/4 < |phi| < pi/2", num_bins, 0, 120);
TH1F* MetJet3 = new TH1F("MetJet3", "Momentum of muons with angle btwn Met and jet pi/2 < |phi| < 3pi/4", num_bins, 0, 120);
TH1F* MetJet4 = new TH1F("MetJet4", "Momentum of muons with angle btwn Met and jet 3pi/4 < |phi| < pi", num_bins, 0, 120);
TH1F* MetJet5 = new TH1F("MetJet5", "Momentum of muons with angle btwn Met and jet pi < |phi| < 5pi/8", num_bins, 0, 120);
TH1F* MetJet6 = new TH1F("MetJet6", "Momentum of muons with angle btwn Met and jet 5pi/8 < |phi| < 3pi/4", num_bins, 0, 120);
TH1F* MetJet7 = new TH1F("MetJet7", "Momentum of muons with angle btwn Met and jet 3pi/4 < |phi| < 7pi/8", num_bins, 0, 120);
TH1F* MetJet8 = new TH1F("MetJet8", "Momentum of muons with angle btwn Met and jet 7pi/8 < |phi| < pi", num_bins, 0, 120);

// Muon distributions for cuts on angle between Met and Muon
TH1F* MetMuon1 = new TH1F("MetMuon1", "Momentum of muons with angle btwn Met and muon 0 < |phi| < pi/8", num_bins, 0, 120);
TH1F* MetMuon2 = new TH1F("MetMuon2", "Momentum of muons with angle btwn Met and muon pi/8 < |phi| < pi/4", num_bins, 0, 120);
TH1F* MetMuon3 = new TH1F("MetMuon3", "Momentum of muons with angle btwn Met and muon pi/4 < |phi| < 3pi/8", num_bins, 0, 120);
TH1F* MetMuon4 = new TH1F("MetMuon4", "Momentum of muons with angle btwn Met and muon 3pi/8 < |phi| < pi/2", num_bins, 0, 120);
TH1F* MetMuon5 = new TH1F("MetMuon5", "Momentum of muons with angle btwn Met and muon pi/2 < |phi| < 5pi/8", num_bins, 0, 120);
TH1F* MetMuon6 = new TH1F("MetMuon6", "Momentum of muons with angle btwn Met and muon 5pi/8 < |phi| < 3pi/4", num_bins, 0, 120);
TH1F* MetMuon7 = new TH1F("MetMuon7", "Momentum of muons with angle btwn Met and muon 3pi/4 < |phi| < 7pi/8", num_bins, 0, 120);
TH1F* MetMuon8 = new TH1F("MetMuon8", "Momentum of muons with angle btwn Met and muon 7pi/8 < |phi| < pi", num_bins, 0, 120);

// Muon distributions for cuts on angle between Jet and Muon
TH1F* JetMuon1 = new TH1F("JetMuon1", "Momentum of muons with angle btwn Jet and muon 0 < |phi| < pi/8", num_bins, 0, 120);
TH1F* JetMuon2 = new TH1F("JetMuon2", "Momentum of muons with angle btwn Jet and muon pi/8 < |phi| < pi/4", num_bins, 0, 120);
TH1F* JetMuon3 = new TH1F("JetMuon3", "Momentum of muons with angle btwn Jet and muon pi/4 < |phi| < 3pi/8", num_bins, 0, 120);
TH1F* JetMuon4 = new TH1F("JetMuon4", "Momentum of muons with angle btwn Jet and muon 3pi/8 < |phi| < pi/2", num_bins, 0, 120);
TH1F* JetMuon5 = new TH1F("JetMuon5", "Momentum of muons with angle btwn Jet and muon pi/2 < |phi| < 5pi/8", num_bins, 0, 120);
TH1F* JetMuon6 = new TH1F("JetMuon6", "Momentum of muons with angle btwn Jet and muon 5pi/8 < |phi| < 3pi/4", num_bins, 0, 120);
TH1F* JetMuon7 = new TH1F("JetMuon7", "Momentum of muons with angle btwn Jet and muon 3pi/4 < |phi| < 7pi/8", num_bins, 0, 120);
TH1F* JetMuon8 = new TH1F("JetMuon8", "Momentum of muons with angle btwn Jet and muon 7pi/8 < |phi| < pi", num_bins, 0, 120);

// Muon distributions for cuts on delta r between Jet and muon
TH1F* JetMuonR1 = new TH1F("JetMuonR1", "Momentum of muons with delta R btwn Jet and muon <1", num_bins, 0, 120);
TH1F* JetMuonR2 = new TH1F("JetMuonR2", "Momentum of muons with delta R btwn Jet and muon 1 < |delta r| < 2", num_bins, 0, 120);
TH1F* JetMuonR3 = new TH1F("JetMuonR3", "Momentum of muons with delta R btwn Jet and muon 2 < |delta r| < 3", num_bins, 0, 120);
TH1F* JetMuonR4 = new TH1F("JetMuonR4", "Momentum of muons with delta R btwn Jet and muon 3 < |delta r| < 4", num_bins, 0, 120);
TH1F* JetMuonR5 = new TH1F("JetMuonR5", "Momentum of muons with delta R btwn Jet and muon 4 < |delta r| < 5", num_bins, 0, 120);
TH1F* JetMuonR6 = new TH1F("JetMuonR6", "Momentum of muons with delta R btwn Jet and muon 5 < |delta r| < 6", num_bins, 0, 120);
TH1F* JetMuonR7 = new TH1F("JetMuonR7", "Momentum of muons with delta R btwn Jet and muon 6 < |delta r| < 7", num_bins, 0, 120);
TH1F* JetMuonR8 = new TH1F("JetMuonR8", "Momentum of muons with delta R btwn Jet and muon 7 < |delta r| < 8", num_bins, 0, 120);

// Muon distributions for cuts on the sum of the Met and Jet
TH1F* MetJetPt1 = new TH1F("MetJetPt1", "Momentum of muons with 30 < (sum of Jet,MET pT) < 35", num_bins, 0, 120);
TH1F* MetJetPt2 = new TH1F("MetJetPt2", "Momentum of muons with 35 < (sum of Jet,MET pT) < 40", num_bins, 0, 120);
TH1F* MetJetPt3 = new TH1F("MetJetPt3", "Momentum of muons with 40 < (sum of Jet,MET pT) < 50", num_bins, 0, 120);
TH1F* MetJetPt4 = new TH1F("MetJetPt4", "Momentum of muons with 50 < (sum of Jet,MET pT) < 60", num_bins, 0, 120);
TH1F* MetJetPt5 = new TH1F("MetJetPt5", "Momentum of muons with 60 < (sum of Jet,MET pT) < 70", num_bins, 0, 120);
TH1F* MetJetPt6 = new TH1F("MetJetPt6", "Momentum of muons with 70 < (sum of Jet,MET pT) < 80", num_bins, 0, 120);
TH1F* MetJetPt7 = new TH1F("MetJetPt7", "Momentum of muons with 80 < (sum of Jet,MET pT) < 90", num_bins, 0, 120);
TH1F* MetJetPt8 = new TH1F("MetJetPt8", "Momentum of muons with 90 < (sum of Jet,MET pT)", num_bins, 0, 120);

// Combining cuts to optimize fit
TH1F* ComboCuts1 = new TH1F("ComboCuts1", "Momentum of muons with MET > 30", num_bins, 0, 120);
TH1F* ComboCuts2 = new TH1F("ComboCuts2", "Momentum of muons with ???", num_bins, 0, 120);
TH1F* ComboCuts3 = new TH1F("ComboCuts3", "Momentum of muons with Jets", num_bins, 0, 120);
TH1F* ComboCuts4 = new TH1F("ComboCuts4", "Momentum of muons with MET > 30 || Jets", num_bins, 0, 120);
TH1F* ComboCuts5 = new TH1F("ComboCuts5", "Momentum of muons with MET > 30 and 1 muon", num_bins, 0, 120);

TH2F* TH2_Isolation = new TH2F ("TH2_Isolation", "Muon isolation and pT", 60, 0, 80, 60, 0, 100);
TH2F* TH2_MuonJetR = new TH2F ("TH2_MuonJetR", "Muon/Jet dR and Muon pT", 60, 0, 80, 60, 0, 10);
TH2F* TH2_MuonJetPhi = new TH2F ("TH2_MuonJetPhi", "Muon/Jet Phi and Muon pT", 60, 0, 80, 60, 0, M_PI);
TH2F* TH2_MetMuonR = new TH2F ("TH2_MetMuonR", "Muon/Met dR and Muon pT", 60, 0, 80, 60, 0, 10);
TH2F* TH2_MetMuonPhi = new TH2F ("TH2_MetMuonPhi", "Muon/Met Phi and Muon pT", 60, 0, 80, 60, 0, M_PI);
TH2F* TH2_JetpT = new TH2F ("TH2_JetpT", "Jet pT and Muon pT", 60, 0, 80, 60, 0, 120);


// ============================= //
// DEFINE IMPORTANT VARIABLES :) //
// ============================= //

// Define luminosity [mb^-1]
// Luminosity: 100 picobarns ^-1
float lumi = 1.26575926e+11;

int RunAnalysis(string sample)
{

    // Load and read the output files from Pythia
    //===========================================

    // Path to input (reco and truth) root files
    string fileIn = sample;

    // Load trees and create chain, add the file and create the tree reader
    TString tree = "ParticleTree";
    TChain *cc_tree = new TChain(tree);
    cc_tree->Add(fileIn.c_str());
    TTreeReader treeReader(cc_tree);

    // Load truth variables

        TTreeReaderArray<double> event_weights(treeReader, "event_weights");

        TTreeReaderValue<int> nMuonBare(treeReader, "nMuonBare");
        TTreeReaderValue<int> nNeutrino(treeReader, "nNeutrino");
        
        TTreeReaderArray<float> muon_bare_pt(treeReader, "muon_bare_pt");
        TTreeReaderArray<float> muon_bare_eta(treeReader, "muon_bare_eta");
        TTreeReaderArray<float> muon_bare_phi(treeReader, "muon_bare_phi");
        TTreeReaderArray<float> muon_bare_E(treeReader, "muon_bare_E");
        TTreeReaderArray<float> muon_bare_charge(treeReader, "muon_bare_charge");

        TTreeReaderArray<float> neutrino_pt(treeReader, "neutrino_pt");
        TTreeReaderArray<float> neutrino_eta(treeReader, "neutrino_eta");
        TTreeReaderArray<float> neutrino_phi(treeReader, "neutrino_phi");
        TTreeReaderArray<float> neutrino_E(treeReader, "neutrino_E");

        TTreeReaderArray<float> lightjet_bare_pt(treeReader, "lightjet_bare_pt");
        TTreeReaderArray<float> lightjet_bare_eta(treeReader, "lightjet_bare_eta");
        TTreeReaderArray<float> lightjet_bare_phi(treeReader, "lightjet_bare_phi");
        TTreeReaderArray<float> lightjet_bare_E(treeReader, "lightjet_bare_E");

        TTreeReaderValue<double> Met(treeReader, "Met");
        TTreeReaderValue<double> Met_phi(treeReader, "Met_phi");

        TTreeReaderArray<float> muonisolation_pt(treeReader, "muonisolation_pt");
        TTreeReaderArray<float> muonisolation_eta(treeReader, "muonisolation_eta");  
    // End truth variables

    // Load reco variables

        TTreeReaderValue<int> nMuonReco(treeReader, "nMuonReco");

        TTreeReaderArray<float> muon_reco_pt(treeReader, "muon_reco_pt");
        TTreeReaderArray<float> muon_reco_eta(treeReader, "muon_reco_eta");
        TTreeReaderArray<float> muon_reco_phi(treeReader, "muon_reco_phi");
        TTreeReaderArray<float> muon_reco_E(treeReader, "muon_reco_E");
        TTreeReaderArray<float> muon_reco_charge(treeReader, "muon_reco_charge");

        TTreeReaderArray<float> jet_reco_pt(treeReader, "jet_reco_pt");
        TTreeReaderArray<float> jet_reco_eta(treeReader, "jet_reco_eta");
        TTreeReaderArray<float> jet_reco_phi(treeReader, "jet_reco_phi");
        TTreeReaderArray<float> jet_reco_E(treeReader, "jet_reco_E");

        TTreeReaderValue<double> RecoMet(treeReader, "RecoMet");
        TTreeReaderValue<double> RecoMet_phi(treeReader, "RecoMet_phi"); 


    // End reco variables

    // Get sum of weights
    

    // Control parameter
    bool dosystematics = true;
    int systnum = 0;
    bool electronChannel = false;
    bool muonChannel =  true;



    // Loop over the events to run analysis on the ntuple
    // ==================================================

    while(treeReader.Next())
    {
        // Fetch object kinematics
        // =======================


        // Get jet kinematics (truth and reco)
        // ----------------------------------------------

        vector<TLorentzVector> JetTrueContainer;
        vector<TLorentzVector> JetRecoContainer;
        TLorentzVector VecSumAllTrueJets;
        TLorentzVector VecSumAllRecoJets;
        int NjTrue = 0;
        int NjReco = 0;

        for (int itjet = 0; itjet<lightjet_bare_E.GetSize(); itjet++)
        {
            // print true jet pT in order
            // myfileT << std::fixed << std::setprecision(2) << jet_true_pt[itjet] << " \n";

            TLorentzVector temptruejet;
            temptruejet.SetPtEtaPhiE(lightjet_bare_pt[itjet], lightjet_bare_eta[itjet], lightjet_bare_phi[itjet], lightjet_bare_E[itjet]);
            JetTrueContainer.push_back(temptruejet);
            VecSumAllTrueJets += temptruejet;
            if ( (lightjet_bare_pt[itjet] > 30. ) && ( fabs(lightjet_bare_eta[itjet]) < 4.4) ) NjTrue++;
        }

         for (int irjet = 0; irjet<jet_reco_pt.GetSize(); irjet++)
        {
            // print reco jet pT in order
            // myfileR << std::fixed << std::setprecision(2) << jet_reco_pt[irjet] << " \n";

            TLorentzVector temprecojet;
            temprecojet.SetPtEtaPhiE(jet_reco_pt[irjet], jet_reco_eta[irjet], jet_reco_phi[irjet], jet_reco_E[irjet]);
            JetRecoContainer.push_back(temprecojet);
            VecSumAllRecoJets += temprecojet;
            if ( (jet_reco_pt[irjet] > 30. ) && ( fabs(jet_reco_eta[irjet]) < 4.4) ) NjReco++;
        }

        // Get muon kinematics (truth and reco)
        // ----------------------------------------------

        vector<TLorentzVector> MuonTrueContainer;
        vector<TLorentzVector> MuonRecoContainer;
        vector<TLorentzVector> MuonContainer_NoCut;
        vector<TLorentzVector> MuonIsoContainer;

        for (int itmuo = 0; itmuo<muon_bare_pt.GetSize(); itmuo++)
        {
            TLorentzVector tempmuonuncut;
            tempmuonuncut.SetPtEtaPhiE(muon_bare_pt[itmuo], muon_bare_eta[itmuo], muon_bare_phi[itmuo], muon_bare_E[itmuo]);
            MuonContainer_NoCut.push_back(tempmuonuncut);
            if(((muon_bare_eta[itmuo] > 1 && muon_bare_eta[itmuo] < 2.5) || 
                (muon_bare_eta[itmuo] < -1 && muon_bare_eta[itmuo] > -2.5))) {
                    if(sample == "/eos/user/a/atimoney/pythia/ch2.root") {
                        if(muon_bare_pt[itmuo] < 26.) {
                            TLorentzVector temptruemuo;
                            temptruemuo.SetPtEtaPhiE(muon_bare_pt[itmuo], muon_bare_eta[itmuo], muon_bare_phi[itmuo], muon_bare_E[itmuo]);
                            MuonTrueContainer.push_back(temptruemuo);
                        }
                    } else {
                        TLorentzVector temptruemuo;
                        temptruemuo.SetPtEtaPhiE(muon_bare_pt[itmuo], muon_bare_eta[itmuo], muon_bare_phi[itmuo], muon_bare_E[itmuo]);
                        MuonTrueContainer.push_back(temptruemuo);
                    }
                }
        }

        for (int irmuo = 0; irmuo<muon_reco_pt.GetSize(); irmuo++)
        {
            TLorentzVector temprecomuo;
            temprecomuo.SetPtEtaPhiE(muon_reco_pt[irmuo], muon_reco_eta[irmuo], muon_reco_phi[irmuo], muon_reco_E[irmuo]);
            MuonRecoContainer.push_back(temprecomuo);
        }

        TLorentzVector Muon1_True;
        TLorentzVector Muon2_True;
        TLorentzVector Muon3_True;
        TLorentzVector Muon1_Reco;
        TLorentzVector Muon2_Reco;
        TLorentzVector Muon3_Reco;

        if (MuonTrueContainer.size() > 0) Muon1_True = MuonTrueContainer[0];
        if (MuonTrueContainer.size() > 1) Muon2_True = MuonTrueContainer[1];
        if (MuonTrueContainer.size() > 2) Muon3_True = MuonTrueContainer[2];
        if (MuonRecoContainer.size() > 0) Muon1_Reco = MuonRecoContainer[0];
        if (MuonRecoContainer.size() > 1) Muon2_Reco = MuonRecoContainer[1];
        if (MuonRecoContainer.size() > 2) Muon3_True = MuonRecoContainer[2];

        // Get Neutrinos
        // ==================================================
        vector<TLorentzVector> NeutrinoContainer;

        for(int i = 0; i < neutrino_pt.GetSize(); i++) {
            TLorentzVector temptrueneu;
            temptrueneu.SetPtEtaPhiE(neutrino_pt[i], neutrino_eta[i], neutrino_phi[i], neutrino_E[i]);
            NeutrinoContainer.push_back(temptrueneu);
        }

        // Calculate missing ET with muons
        // ==================================================

        double met_Px = 0;
        double met_Py = 0;
        double met_Pt = 0;
        double met_Phi = 0;
        for(int i = 0; i < MuonContainer_NoCut.size(); i++) {
            met_Px += MuonContainer_NoCut[i].Px();
            met_Py += MuonContainer_NoCut[i].Py();
        }
        for(int i = 0; i < NeutrinoContainer.size(); i++) {
            met_Px += NeutrinoContainer[i].Px();
            met_Py += NeutrinoContainer[i].Py();
        }
        met_Pt = sqrt(pow(met_Px, 2.0) + pow(met_Py, 2.0));
        met_Phi = atan2(met_Py,met_Px);



        // Calculate kinematic variables to cut on or to plot
        // ==================================================


        // Count the number of leptons above veto thresholds
        // -------------------------------------------------

        // Note: We cannot robustly and accurately reconstruct charged leptons below 7 GeV and beyond |eta| 2.4, even
        //       when the trigger was fired by some other object. We set a counter for all charged lepton that pass
        //       these kinematic requirements.


        int nLowMuoTrue = 0;
        int nLowMuoReco = 0;

        for (size_t iMuo = 0; iMuo < *nMuonBare; iMuo++)
        {
            if ( (muon_bare_pt[iMuo] >= 7.0) && fabs(muon_bare_eta[iMuo]) < 2.4 ) nLowMuoTrue++ ;
        }

        for (size_t iMuo = 0; iMuo < *nMuonReco; iMuo++)
        {
            if ( (muon_reco_pt[iMuo] >= 7.0) && fabs(muon_reco_eta[iMuo]) < 2.4 ) nLowMuoReco++ ;
        }

        // Reweight the event, if needed
        // ==============================

        // Deal with efficiency 
        double mu5_efficiency[11]; 
        double efficiency_scale[MuonTrueContainer.size()];
        double mu5_efficiency_plateau = 0.925; // efficiency above 11 GeV
        double combined_efficiency = 0;

        mu5_efficiency[0] = 0;
        mu5_efficiency[1] = 0; // indices 0-4 are L1 efficiency
        mu5_efficiency[2] = 0.05;
        mu5_efficiency[3] = 0.125;
        mu5_efficiency[4] = 0.25;
        mu5_efficiency[5] = 0.47; // indices 5-10 are HLT efficiency (L1 inclusive)
        mu5_efficiency[6] = 0.65;
        mu5_efficiency[7] = 0.75;
        mu5_efficiency[8] = 0.83;
        mu5_efficiency[9] = 0.87;
        mu5_efficiency[10] = 0.9;

        for(int i = 0; i < MuonTrueContainer.size(); i++) {
            if(MuonTrueContainer[i].Pt() > 11) {
                efficiency_scale[i] = mu5_efficiency_plateau;
            } else {
                for (int k = 11; k > 0; k--) {
                    if(MuonTrueContainer[i].Pt() < k && MuonTrueContainer[i].Pt() > (k-1)) {
                        efficiency_scale[i] = mu5_efficiency[k-1];
                    }
                }
            }
        }

        int mu_counter = 1;
        combined_efficiency = efficiency_scale[0];
        while(mu_counter < MuonTrueContainer.size()) {
            float epsilon_1 = combined_efficiency;
            float epsilon_2 = efficiency_scale[mu_counter];
            combined_efficiency = (epsilon_1 + epsilon_2 - (epsilon_1*epsilon_2));
            mu_counter ++;
        }
        if(combined_efficiency > 1) {
            cout << "error with efficiency" << endl;
        }

        double wgt = combined_efficiency;

        // Apply cuts on muons and fill histograms
        // ==============================
        if(met_Pt < 30) { 

            // Fill muon histograms
            for (int i = 0; i < MuonTrueContainer.size(); i++) {
                if(MuonTrueContainer[i].P() < 5) {
                    wgt = 0;
                }
            }
            for(int i = 0; i < MuonTrueContainer.size(); i++) {
                BareMuon_pT->Fill(MuonTrueContainer[i].Pt(), wgt);
                BareMuon_pT_norm1->Fill(MuonTrueContainer[i].Pt(), wgt);
                Muon_P->Fill(MuonTrueContainer[i].P(), wgt);
                BareMuon_pT_no_norm->Fill(MuonTrueContainer[i].Pt(), wgt);
                Muon_P_no_norm->Fill(MuonTrueContainer[i].Pt(), wgt);
            }
            

            // Muon cut: number of muons
            if(MuonContainer_NoCut.size() == 3) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    ThreeMuon->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            } else if(MuonContainer_NoCut.size() == 2) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    TwoMuon->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            } else if (MuonContainer_NoCut.size() == 1) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    OneMuon->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }

            // Cut on lead jet pT
            if(JetTrueContainer.size() > 0) {
                if((JetTrueContainer[0].Pt() > 30) && (JetTrueContainer[0].Pt() < 40)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet30GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if((JetTrueContainer[0].Pt() > 40) && (JetTrueContainer[0].Pt() < 50)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet40GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if((JetTrueContainer[0].Pt() > 50) && (JetTrueContainer[0].Pt() < 60)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet50GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if((JetTrueContainer[0].Pt() > 60) && (JetTrueContainer[0].Pt() < 70)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet60GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if((JetTrueContainer[0].Pt() > 70) && (JetTrueContainer[0].Pt() < 80)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet70GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if((JetTrueContainer[0].Pt() > 80) && (JetTrueContainer[0].Pt() < 90)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet80GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
                if(JetTrueContainer[0].Pt() > 90) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Jet90GeV->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
            }

            // Muon cut on number of Jets
            if(JetTrueContainer.size() == 0) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    No_Jet->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }
            if(JetTrueContainer.size() == 1) {
                for (int i = 0; i < MuonTrueContainer.size(); i++) {
                    One_Jet->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }
            if(JetTrueContainer.size() == 2) {
                for (int i = 0; i < MuonTrueContainer.size(); i++) {
                    Two_Jet->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }
            if(JetTrueContainer.size() > 2) {
                for (int i = 0; i < MuonTrueContainer.size(); i++) {
                    Mult_Jet->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }
            
            // Muon cut: pseudorapidity of leading jet
            if(JetTrueContainer.size() > 0) {
                if((JetTrueContainer[0].Eta() > -0.5) && (JetTrueContainer[0].Eta() < 0.5)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta1->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -1) && (JetTrueContainer[0].Eta() < 1)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta2->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -1.5) && (JetTrueContainer[0].Eta() < 1.5)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta3->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -2) && (JetTrueContainer[0].Eta() < 2)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta4->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -2.5) && (JetTrueContainer[0].Eta() < 2.5)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta5->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -3) && (JetTrueContainer[0].Eta() < 3)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta6->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if((JetTrueContainer[0].Eta() > -3.5) && (JetTrueContainer[0].Eta() < 3.5)) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta7->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        JetEta8->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
            }

            // Muon cut: angle between lead jet and met
            if(met_Pt != 0 && JetTrueContainer.size() > 0) {
                double diff = delta_phi(JetTrueContainer[0].Phi(), met_Phi);
                MetJetPhi->Fill(diff, wgt);
                if(met_Pt > 30) {
                    MetJetPhi_MetCut->Fill(diff, wgt);
                }
                if (diff < M_PI/8) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet1->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < M_PI/4) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet2->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < 3*M_PI/8) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet3->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < M_PI/2) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet4->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < 5*M_PI/8) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet5->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < 3*M_PI/4) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet6->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < 7*M_PI/8) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet7->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if (diff < M_PI) {
                    for (int i = 0; i < MuonTrueContainer.size(); i++) {
                        MetJet8->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else {
                    cout << "error: phi out of range" << endl;
                }
            }

            // Muon cut: delta r between any muon and leading jet
            if(JetTrueContainer.size() > 0 && MuonTrueContainer.size() > 0) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    double diff = delta_r(MuonTrueContainer[i].Phi(), JetTrueContainer[0].Phi(), MuonTrueContainer[i].Eta(), JetTrueContainer[0].Eta());
                    JetMuonR->Fill(diff, wgt);
                    if(met_Pt > 30) {
                        JetMuonR_MetCut->Fill(diff, wgt);
                    }
                    bool pass_jm[8] = {false, false, false, false, false, false, false, false};
                    if(diff < 0.25 && pass_jm[0] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR1->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[0] = true;
                        }
                        pass_jm[0] = true;
                    } else if (diff < 0.5 && pass_jm[1] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR2->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[1] = true;
                        }
                    } else if (diff < 1 && pass_jm[2] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR3->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[2] = true;
                        }
                    } else if (diff < 2 && pass_jm[3] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR4->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[3] = true;
                        }
                    } else if (diff < 3 && pass_jm[4] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR5->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[4] = true;
                        }
                    } else if (diff < 4 && pass_jm[5] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR6->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[5] = true;
                        }
                    } else if (diff < 5 && pass_jm[6] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR7->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[6] = true;
                        }
                    } else if (pass_jm[7] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            JetMuonR8->Fill(MuonTrueContainer[i].Pt(), wgt);
                            pass_jm[7] = true;
                        }
                    }
                }
            }

            // Muon cut: angle between leading muon and leading jet
            if(JetTrueContainer.size() > 0 && MuonTrueContainer.size() > 0) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    double diff = delta_phi(MuonTrueContainer[i].Phi(), JetTrueContainer[0].Phi());
                    JetMuonPhi->Fill(diff, wgt);
                }
            //     bool passcutJM = false;
            //     int nMuon = MuonTrueContainer.size();
            //     while(nMuon > 0 && passcut == false) {
            //         double diff = delta_phi(MuonTrueContainer[nMuon - 1].Phi(), JetTrueContainer[0].Phi());
            //         JetMuonPhi->Fill(diff, wgt);
            //         if(met_Pt > 30) {
            //             JetMuonPhi_MetCut->Fill(diff, wgt);
            //         }
            //         if (diff < M_PI/8) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon1->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < M_PI/4) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon2->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < 3*M_PI/8) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon3->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < M_PI/2) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon4->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < 5*M_PI/8) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon5->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < 3*M_PI/4) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon6->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < 7*M_PI/8) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon7->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else if (diff < M_PI) {
            //             for(int i = 0; i < MuonTrueContainer.size(); i++) {
            //                 JetMuon8->Fill(MuonTrueContainer[i].Pt(), wgt);
            //             }
            //             passcut = true;
            //         } else {
            //             cout << "error: phi out of range " << endl;
            //         }
            //         nMuon --;
            //     }
            }

            // Muon isolation
            if(muonisolation_pt.GetSize() > 0) {
                double LeadIsoPt = muonisolation_pt[0];
                for(int i = 1; i < muonisolation_pt.GetSize(); i ++) {
                    // if((muonisolation_eta[i] > -2.5 && muonisolation_eta[i] < -1) || (muonisolation_eta[i] > 1 && muonisolation_eta[i] < 2.5) ) {
                        if(muonisolation_pt[i] > LeadIsoPt) {
                            LeadIsoPt = muonisolation_pt[i];
                        }
                        MuonIsolation->Fill(muonisolation_pt[i], wgt);
                        if(met_Pt > 30) {
                            MuonIsolation_MetCut->Fill(muonisolation_pt[i], wgt);
                        }
                    // }
                    
                }
                if(LeadIsoPt > 70) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso1->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 70) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso2->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 50) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso3->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 40) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso4->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 30) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso5->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 20) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso6->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
                if(LeadIsoPt < 10) {
                    for(int j = 0; j < MuonTrueContainer.size(); j++) {
                        Iso7->Fill(MuonTrueContainer[j].Pt(), wgt);
                    }
                } 
            }


            // Angle between muon and Met 
            if(met_Pt != 0 && MuonTrueContainer.size() > 0) {
                bool passcut[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                int nMuon = MuonTrueContainer.size();
                while(nMuon > 0) {
                    double diff = delta_phi(MuonTrueContainer[nMuon - 1].Phi(), met_Phi);
                    MetMuonPhi->Fill(diff, wgt);
                    if (diff < M_PI/8 && passcut[0] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon1->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[0] = true;
                    } else if (diff < M_PI/4 && passcut[1] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon2->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[1] = true;
                    } else if (diff < 3*M_PI/8 && passcut[2] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon3->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[2] = true;
                    } else if (diff < M_PI/2 && passcut[3] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon4->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[3] = true;
                    } else if (diff < 5*M_PI/8 && passcut[4] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon5->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[4] = true;
                    } else if (diff < 3*M_PI/4 && passcut[5] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon6->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[5] = true;
                    } else if (diff < 7*M_PI/8 && passcut[6] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon7->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[6] = true;
                    } else if (diff < M_PI && passcut[7] == false) {
                        for(int i = 0; i < MuonTrueContainer.size(); i++) {
                            MetMuon8->Fill(MuonTrueContainer[i].Pt(), wgt);
                        }
                        passcut[7] = true;
                    }
                    nMuon --;
                }
            }

            // Met
            if(met_Pt != 0) {
                if(met_Pt < 5) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met1->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if(met_Pt < 10) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met2->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if(met_Pt < 15) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met3->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if(met_Pt < 20) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met4->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if(met_Pt < 25) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met5->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                } else if(met_Pt < 30) {
                    for(int i = 0; i < MuonTrueContainer.size(); i++) {
                        Met6->Fill(MuonTrueContainer[i].Pt(), wgt);
                    }
                }
            }

            // Sum of MET, all Jet pT
            double sumPt = 0;
            if (met_Pt != 0) {
                sumPt = met_Pt;
                if (sumPt < 0) {
                    cout << "zero " << endl;
                }
            }
            for (int i = 0; i < JetTrueContainer.size(); i++) {
                sumPt += JetTrueContainer[i].Pt();
            }
            MetJetPt->Fill(sumPt, wgt);
            if(met_Pt > 30) {
                MetJetPt_MetCut->Fill(sumPt, wgt);
            }
            for (int i = 0; i < MuonTrueContainer.size(); i++) {
                if (sumPt < 20) {
                    MetJetPt1->Fill(MuonTrueContainer[i].Pt(), wgt);
                } else if (sumPt < 22) {
                    MetJetPt2->Fill(MuonTrueContainer[i].Pt(), wgt);
                } else if (sumPt < 25) {
                    MetJetPt3->Fill(MuonTrueContainer[i].Pt(), wgt);
                } else if (sumPt < 28) {
                    MetJetPt4->Fill(MuonTrueContainer[i].Pt(), wgt);
                } else if (sumPt < 30) {
                    MetJetPt5->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }

            // Combination cuts
            if(MuonContainer_NoCut.size() == 1 && met_Pt > 5) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    ComboCuts1->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            } 
            if(MuonContainer_NoCut.size() == 1 && met_Pt > 10) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    ComboCuts2->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            }
            if(MuonContainer_NoCut.size() == 1 && met_Pt > 20) {
                for(int i = 0; i < MuonTrueContainer.size(); i++) {
                    ComboCuts3->Fill(MuonTrueContainer[i].Pt(), wgt);
                }
            } 

            // Apply cuts on other variables and fill histograms
            // ==============================
            
            for(int i = 0; i < JetTrueContainer.size(); i++) {
                JetPt->Fill(JetTrueContainer[i].Pt(), wgt);
                JetEta->Fill(JetTrueContainer[i].Eta(), wgt);
            }
            nJets->Fill(JetTrueContainer.size(), wgt);
            nMuons->Fill(MuonTrueContainer.size(), wgt);
            MetPt->Fill(met_Pt, wgt);

            // Count number of events that have muons
            if(combined_efficiency > 0) {
                WeightedMuons->Fill(combined_efficiency);
            }
        }
        //Variables: 2d histograms
        if(JetTrueContainer.size() > 0) {
            for (int i = 0; i < MuonTrueContainer.size(); i++) {
                double tempr = delta_r(MuonTrueContainer[i].Phi(), JetTrueContainer[0].Phi(), MuonTrueContainer[i].Eta(), JetTrueContainer[0].Eta());
                TH2_MuonJetR->Fill(MuonTrueContainer[i].Pt(), tempr);
                double temp_phi = delta_phi(MuonTrueContainer[i].Phi(), JetTrueContainer[0].Phi());
                TH2_MuonJetPhi->Fill(MuonTrueContainer[i].Pt(), temp_phi);
                TH2_JetpT->Fill(MuonTrueContainer[i].Pt(), JetTrueContainer[0].Pt());
            }
        }
        // add in muon isolation (so broken rn)
        for(int i = 0; i < MuonTrueContainer.size(); i++) {
            double tempphi = delta_phi(MuonTrueContainer[i].Phi(), met_Phi);
            TH2_MetMuonPhi->Fill(MuonTrueContainer[i].Pt(), tempphi);
        }
        
        // if(muonisolation_pt.GetSize() > 0) {
        //     for(int i = 0; i < MuonTrueContainer.size(); i++) {

        //     }
        // }
    } // End loop on events



    return 0;
}


//================================================================================//
//=============================== Main Function ==================================//
//================================================================================//

int LowMetAna()
{

    // two options:
    // -----------

    // give a list of files
    std::vector<string> samples = {"/eos/user/a/atimoney/pythia/ttbar-dilep.root", 
                                    "/eos/user/a/atimoney/pythia/ttbar-semilep.root", 
                                    "/eos/user/a/atimoney/pythia/wbos.root", 
                                    "/eos/user/a/atimoney/pythia/zbos.root", 
                                    "/eos/user/a/atimoney/pythia/gamma.root",
                                    "/eos/user/a/atimoney/pythia/bot2.root",
                                    "/eos/user/a/atimoney/pythia/bot20.root",
                                    "/eos/user/a/atimoney/pythia/bot40.root",
                                    "/eos/user/a/atimoney/pythia/bot60.root",
                                    "/eos/user/a/atimoney/pythia/bot120.root",
                                    "/eos/user/a/atimoney/pythia/ch2.root",
                                    "/eos/user/a/atimoney/pythia/ch10.root",
                                    "/eos/user/a/atimoney/pythia/ch20.root",
                                    "/eos/user/a/atimoney/pythia/ch40.root",
                                    "/eos/user/a/atimoney/pythia/ch60.root",
                                    "/eos/user/a/atimoney/pythia/ch120.root",
                                    "/eos/user/a/atimoney/pythia/bb2.root",
                                    "/eos/user/a/atimoney/pythia/bb20.root",
                                    "/eos/user/a/atimoney/pythia/bb40.root",
                                    "/eos/user/a/atimoney/pythia/bb60.root",
                                    "/eos/user/a/atimoney/pythia/bb120.root",
                                    "/eos/user/a/atimoney/pythia/bb200.root",
                                    "/eos/user/a/atimoney/pythia/cc2.root",
                                    "/eos/user/a/atimoney/pythia/cc20.root",
                                    "/eos/user/a/atimoney/pythia/cc40.root",
                                    "/eos/user/a/atimoney/pythia/cc60.root",
                                    "/eos/user/a/atimoney/pythia/cc120.root",
                                    "/eos/user/a/atimoney/pythia/cc200.root"}; 
    TFile infile[28] = {"/eos/user/a/atimoney/pythia/ttbar-dilep.root", 
                        "/eos/user/a/atimoney/pythia/ttbar-semilep.root", 
                        "/eos/user/a/atimoney/pythia/wbos.root", 
                        "/eos/user/a/atimoney/pythia/zbos.root", 
                        "/eos/user/a/atimoney/pythia/gamma.root",
                        "/eos/user/a/atimoney/pythia/bot2.root",
                        "/eos/user/a/atimoney/pythia/bot20.root",
                        "/eos/user/a/atimoney/pythia/bot40.root",
                        "/eos/user/a/atimoney/pythia/bot60.root",
                        "/eos/user/a/atimoney/pythia/bot120.root",
                        "/eos/user/a/atimoney/pythia/ch2.root",
                        "/eos/user/a/atimoney/pythia/ch10.root",
                        "/eos/user/a/atimoney/pythia/ch20.root",
                        "/eos/user/a/atimoney/pythia/ch40.root",
                        "/eos/user/a/atimoney/pythia/ch60.root", 
                        "/eos/user/a/atimoney/pythia/ch120.root",
                        "/eos/user/a/atimoney/pythia/bb2.root",
                        "/eos/user/a/atimoney/pythia/bb20.root",
                        "/eos/user/a/atimoney/pythia/bb40.root",
                        "/eos/user/a/atimoney/pythia/bb60.root",
                        "/eos/user/a/atimoney/pythia/bb120.root",
                        "/eos/user/a/atimoney/pythia/bb200.root",
                        "/eos/user/a/atimoney/pythia/cc2.root",
                        "/eos/user/a/atimoney/pythia/cc20.root",
                        "/eos/user/a/atimoney/pythia/cc40.root",
                        "/eos/user/a/atimoney/pythia/cc60.root",
                        "/eos/user/a/atimoney/pythia/cc120.root",
                        "/eos/user/a/atimoney/pythia/cc200.root"};
    string outname[28] = {"histograms/ttbar-dilep.root", "histograms/ttbar-semilep.root",
                        "histograms/wbos.root", "histograms/zbos.root", "histograms/gamma.root", 
                        "histograms/bottom2.root", "histograms/bottom20.root", "histograms/bottom40.root", "histograms/bottom60.root", "histograms/bottom120.root",
                        "histograms/charm2.root", "histograms/charm10.root", "histograms/charm20.root", "histograms/charm40.root", "histograms/charm60.root", "histograms/charm120.root", 
                        "histograms/bb2.root", "histograms/bb20.root", "histograms/bb40.root", "histograms/bb60.root", "histograms/bb120.root", "histograms/bb200.root", 
                        "histograms/cc2.root", "histograms/cc20.root", "histograms/cc40.root", "histograms/cc60.root", "histograms/cc120.root", "histograms/cc200.root"};
    // Cross section values [mb]
    double crosssec[28] = {
                        7.580e-09, 4.758e-08, 1.5985e-05, 1.594e-06, 5.223e-06, // dilep ttbar, semilep ttbar, wbos, zbos, gamma 
                        1.528e-02, 8.029e-05, 4.985e-06, 1.09e-06, 5.306e-08, // bot2, bot20, bot40, bot60, bot120
                        9.205e-01, 3.140e-03, 1.749e-04, 8.574e-06, 1.76e-06, 8.302e-08, // ch2, ch10, ch20, ch40, ch60, ch120
                        3.874e-01, 3.226e-03, 2.157e-04, 5.069e-05, 2.519e-06, 2.655e-07, // bb2, bb20, bb40, bb60, bb120, bb200
                        2.681e+00, 3.436e-03, 2.195e-04, 5.102e-05, 2.523e-06, 2.655e-07 // cc2, cc20, cc40, cc60, cc120, cc200
                        };

    double nEvents[28] = {100000, 100000, 1000000, 1000000, 100000, // dilep ttbar, semilep ttbar, wbos, zbos, gamma 
                          1000000, 1000000, 1000000, 1000000, 1000000, // bot2, bot40, bot60, bot120
                          1000000, 1000000, 1000000, 500000, 1000000, 1000000, // ch2, ch20, ch40, ch60
                          1000000, 1000000, 1000000, 1000000, 1000000, 1000000, // bb2, bb40, bb60, bb120
                          1000000, 1000000, 1000000, 1000000, 1000000, 1000000 // cc2, cc40, cc60, cc120
                          };

    // or run over all files in pythia-output/ directory
    // std::vector<string> samples;
    // DIR *dir_ptr;
    // struct dirent *diread;
    // if ((dir_ptr = opendir("../pythia-outputs")) != nullptr) {
    //     while ((diread = readdir(dir_ptr)) != nullptr) {
    //         string sample = diread->d_name;
    //         if (sample.find(".root") != string::npos){
    //             samples.push_back(sample);
    //         }
    //     }
    //     closedir(dir_ptr);
    // }

    // print output file name
    // std::cout << "Output file name: " << outname << std::endl;

    // Create new file for histograms of analyzed data
    // TFile *outFile = TFile::Open(outname.c_str(), "recreate");

    // loop over list of files and fill histograms with RunAnalysis
    int option = 0;
    for (int i = 0; i < samples.size(); i++)
    {
        double num_events = nEvents[i];
        double cross = crosssec[i];

        std::cout << "Output file name: " << outname[i] << std::endl;
        TFile *outFile = TFile::Open(outname[i].c_str(), "recreate");
        cout << "Analysing " << samples[i] << " ..." << endl << endl;
        RunAnalysis(samples[i]);

        // cout << "Normalizing to " << outname[i] << " cross-section" << endl << endl;

        //  Write histograms
        // ----------------

        // Scale each to cross-section
        
        double eventsum = BareMuon_pT_norm1->GetSumOfWeights();
        BareMuon_pT_norm1->Scale(1/eventsum);

        BareMuon_pT->Scale(cross*(lumi/num_events));
        Muon_P->Scale(cross*(lumi/num_events));

        MuonIsolation->Scale(cross*(lumi/num_events));

        JetPt->Scale(cross*(lumi/num_events));
        JetEta->Scale(cross*(lumi/num_events));
        nJets->Scale(cross*(lumi/num_events));
        nMuons->Scale(cross*(lumi/num_events));
        JetMuonPhi->Scale(cross*(lumi/num_events));
        JetMuonR->Scale(cross*(lumi/num_events));
        MetJetPhi->Scale(cross*(lumi/num_events));
        MetMuonPhi->Scale(cross*(lumi/num_events));
        MetPt->Scale(cross*(lumi/num_events));
        MetJetPt->Scale(cross*(lumi/num_events));
        MetJetPt_MetCut->Scale(cross*(lumi/num_events));

        JetPt_MetCut->Scale(cross*(lumi/num_events));
        JetEta_MetCut->Scale(cross*(lumi/num_events));
        nJets_MetCut->Scale(cross*(lumi/num_events));
        nMuons_MetCut->Scale(cross*(lumi/num_events));
        JetMuonPhi_MetCut->Scale(cross*(lumi/num_events));
        JetMuonR_MetCut->Scale(cross*(lumi/num_events));
        MetJetPhi_MetCut->Scale(cross*(lumi/num_events));
        MetMuonPhi_MetCut->Scale(cross*(lumi/num_events));
        MuonIsolation_MetCut->Scale(cross*(lumi/num_events));

        OneMuon->Scale(cross*(lumi/num_events));
        TwoMuon->Scale(cross*(lumi/num_events));
        ThreeMuon->Scale(cross*(lumi/num_events));

        Met1->Scale(cross*(lumi/num_events));
        Met2->Scale(cross*(lumi/num_events));
        Met3->Scale(cross*(lumi/num_events));
        Met4->Scale(cross*(lumi/num_events));
        Met5->Scale(cross*(lumi/num_events));
        Met6->Scale(cross*(lumi/num_events));
        Met7->Scale(cross*(lumi/num_events));
        Met8->Scale(cross*(lumi/num_events));

        Iso1->Scale(cross*(lumi/num_events));
        Iso2->Scale(cross*(lumi/num_events));
        Iso3->Scale(cross*(lumi/num_events));
        Iso4->Scale(cross*(lumi/num_events));
        Iso5->Scale(cross*(lumi/num_events));
        Iso6->Scale(cross*(lumi/num_events));
        Iso7->Scale(cross*(lumi/num_events));

        No_Jet->Scale(cross*(lumi/num_events));
        One_Jet->Scale(cross*(lumi/num_events));
        Two_Jet->Scale(cross*(lumi/num_events));
        Mult_Jet->Scale(cross*(lumi/num_events));

        Jet30GeV->Scale(cross*(lumi/num_events));
        Jet40GeV->Scale(cross*(lumi/num_events));
        Jet50GeV->Scale(cross*(lumi/num_events));
        Jet60GeV->Scale(cross*(lumi/num_events));
        Jet70GeV->Scale(cross*(lumi/num_events));
        Jet80GeV->Scale(cross*(lumi/num_events));
        Jet90GeV->Scale(cross*(lumi/num_events));

        JetEta1->Scale(cross*(lumi/num_events));
        JetEta2->Scale(cross*(lumi/num_events));
        JetEta3->Scale(cross*(lumi/num_events));
        JetEta4->Scale(cross*(lumi/num_events));
        JetEta5->Scale(cross*(lumi/num_events));
        JetEta6->Scale(cross*(lumi/num_events));
        JetEta7->Scale(cross*(lumi/num_events));
        JetEta8->Scale(cross*(lumi/num_events));

        MetJet1->Scale(cross*(lumi/num_events));
        MetJet2->Scale(cross*(lumi/num_events));
        MetJet3->Scale(cross*(lumi/num_events));
        MetJet4->Scale(cross*(lumi/num_events));
        MetJet5->Scale(cross*(lumi/num_events));
        MetJet6->Scale(cross*(lumi/num_events));
        MetJet7->Scale(cross*(lumi/num_events));
        MetJet8->Scale(cross*(lumi/num_events));

        MetMuon1->Scale(cross*(lumi/num_events));
        MetMuon2->Scale(cross*(lumi/num_events));
        MetMuon3->Scale(cross*(lumi/num_events));
        MetMuon4->Scale(cross*(lumi/num_events));
        MetMuon5->Scale(cross*(lumi/num_events));
        MetMuon6->Scale(cross*(lumi/num_events));
        MetMuon7->Scale(cross*(lumi/num_events));
        MetMuon8->Scale(cross*(lumi/num_events));

        JetMuon1->Scale(cross*(lumi/num_events));
        JetMuon2->Scale(cross*(lumi/num_events));
        JetMuon3->Scale(cross*(lumi/num_events));
        JetMuon4->Scale(cross*(lumi/num_events));
        JetMuon5->Scale(cross*(lumi/num_events));
        JetMuon6->Scale(cross*(lumi/num_events));
        JetMuon7->Scale(cross*(lumi/num_events));
        JetMuon8->Scale(cross*(lumi/num_events));

        JetMuonR1->Scale(cross*(lumi/num_events));
        JetMuonR2->Scale(cross*(lumi/num_events));
        JetMuonR3->Scale(cross*(lumi/num_events));
        JetMuonR4->Scale(cross*(lumi/num_events));
        JetMuonR5->Scale(cross*(lumi/num_events));
        JetMuonR6->Scale(cross*(lumi/num_events));
        JetMuonR7->Scale(cross*(lumi/num_events));
        JetMuonR8->Scale(cross*(lumi/num_events));

        MetJetPt1->Scale(cross*(lumi/num_events));
        MetJetPt2->Scale(cross*(lumi/num_events));
        MetJetPt3->Scale(cross*(lumi/num_events));
        MetJetPt4->Scale(cross*(lumi/num_events));
        MetJetPt5->Scale(cross*(lumi/num_events));
        MetJetPt6->Scale(cross*(lumi/num_events));
        MetJetPt7->Scale(cross*(lumi/num_events));
        MetJetPt8->Scale(cross*(lumi/num_events));

        ComboCuts1->Scale(cross*(lumi/num_events));
        ComboCuts2->Scale(cross*(lumi/num_events));
        ComboCuts3->Scale(cross*(lumi/num_events));
        ComboCuts4->Scale(cross*(lumi/num_events));
        ComboCuts5->Scale(cross*(lumi/num_events));

        TH2_MuonJetR->Scale(cross*(lumi/num_events));
        TH2_Isolation->Scale(cross*(lumi/num_events));
        TH2_MuonJetR->Scale(cross*(lumi/num_events));
        TH2_MuonJetPhi->Scale(cross*(lumi/num_events));
        TH2_MetMuonPhi->Scale(cross*(lumi/num_events));
        TH2_JetpT->Scale(cross*(lumi/num_events));

        WeightedMuons->Scale(cross*(lumi/num_events));

        // Write out muon graphs
        BareMuon_pT->Write();
        BareMuon_pT_norm1->Write();
        BareMuon_pT_no_norm->Write();

        MuonIsolation->Write();
        Muon_P->Write();
        Muon_P_no_norm->Write();
        WeightedMuons->Write();

        JetPt->Write();
        JetEta->Write();
        nJets->Write();
        nMuons->Write();
        JetMuonPhi->Write();
        JetMuonR->Write();
        MetJetPhi->Write();
        MetMuonPhi->Write();
        MetPt->Write();
        MetJetPt->Write();
        MetJetPt_MetCut->Write();

        JetPt_MetCut->Write();
        JetEta_MetCut->Write();
        nJets_MetCut->Write();
        nMuons_MetCut->Write();
        JetMuonPhi_MetCut->Write();
        JetMuonR_MetCut->Write();
        MetJetPhi_MetCut->Write();
        MetMuonPhi_MetCut->Write();
        MuonIsolation_MetCut->Write();

        OneMuon->Write();
        TwoMuon->Write();
        ThreeMuon->Write();

        No_Jet->Write();
        One_Jet->Write();
        Two_Jet->Write();
        Mult_Jet->Write();

        Jet30GeV->Write();
        Jet40GeV->Write();
        Jet50GeV->Write();
        Jet60GeV->Write();
        Jet70GeV->Write();
        Jet80GeV->Write();
        Jet90GeV->Write();

        Met1->Write();
        Met2->Write();
        Met3->Write();
        Met4->Write();
        Met5->Write();
        Met6->Write();
        Met7->Write();
        Met8->Write();

        Iso1->Write();
        Iso2->Write();
        Iso3->Write();
        Iso4->Write();
        Iso5->Write();
        Iso6->Write();
        Iso7->Write();

        JetEta1->Write();
        JetEta2->Write();
        JetEta3->Write();
        JetEta4->Write();
        JetEta5->Write();
        JetEta6->Write();
        JetEta7->Write();
        JetEta8->Write();

        MetJet1->Write();
        MetJet2->Write();
        MetJet3->Write();
        MetJet4->Write();
        MetJet5->Write();
        MetJet6->Write();
        MetJet7->Write();
        MetJet8->Write();

        MetMuon1->Write();
        MetMuon2->Write();
        MetMuon3->Write();
        MetMuon4->Write();
        MetMuon5->Write();
        MetMuon6->Write();
        MetMuon7->Write();
        MetMuon8->Write();

        JetMuon1->Write();
        JetMuon2->Write();
        JetMuon3->Write();
        JetMuon4->Write();
        JetMuon5->Write();
        JetMuon6->Write();
        JetMuon7->Write();
        JetMuon8->Write();

        JetMuonR1->Write();
        JetMuonR2->Write();
        JetMuonR3->Write();
        JetMuonR4->Write();
        JetMuonR5->Write();
        JetMuonR6->Write();
        JetMuonR7->Write();
        JetMuonR8->Write();

        MetJetPt1->Write();
        MetJetPt2->Write();
        MetJetPt3->Write();
        MetJetPt4->Write();
        MetJetPt5->Write();
        MetJetPt6->Write();
        MetJetPt7->Write();
        MetJetPt8->Write();

        ComboCuts1->Write();
        ComboCuts2->Write();
        ComboCuts3->Write();
        ComboCuts4->Write();
        ComboCuts5->Write();

        TH2_MuonJetR->Write();
        TH2_Isolation->Write();
        TH2_MuonJetR->Write();
        TH2_MuonJetPhi->Write();
        TH2_MetMuonPhi->Write();
        TH2_JetpT->Write();

        //Reset histograms for next file
        BareMuon_pT->Reset();
        BareMuon_pT_norm1->Reset();
        BareMuon_pT_no_norm->Reset();

        MuonIsolation->Reset();
        Muon_P->Reset();
        Muon_P_no_norm->Reset();

        JetPt->Reset();
        JetEta->Reset();
        nJets->Reset();
        nMuons->Reset();
        JetMuonPhi->Reset();
        JetMuonR->Reset();
        MetJetPhi->Reset();
        MetMuonPhi->Reset();
        MetPt->Reset();
        MetJetPt->Reset();
        MetJetPt_MetCut->Reset();

        JetPt_MetCut->Reset();
        JetEta_MetCut->Reset();
        nJets_MetCut->Reset();
        nMuons_MetCut->Reset();
        JetMuonPhi_MetCut->Reset();
        JetMuonR_MetCut->Reset();
        MetJetPhi_MetCut->Reset();
        MetMuonPhi_MetCut->Reset();
        MuonIsolation_MetCut->Reset();

        OneMuon->Reset();
        TwoMuon->Reset();
        ThreeMuon->Reset();

        No_Jet->Reset();
        One_Jet->Reset();
        Two_Jet->Reset();
        Mult_Jet->Reset();

        Jet30GeV->Reset();
        Jet40GeV->Reset();
        Jet50GeV->Reset();
        Jet60GeV->Reset();
        Jet70GeV->Reset();
        Jet80GeV->Reset();
        Jet90GeV->Reset();

        Met1->Reset();
        Met2->Reset();
        Met3->Reset();
        Met4->Reset();
        Met5->Reset();
        Met6->Reset();
        Met7->Reset();
        Met8->Reset();

        Iso1->Reset();
        Iso2->Reset();
        Iso3->Reset();
        Iso4->Reset();
        Iso5->Reset();
        Iso6->Reset();
        Iso7->Reset();

        JetEta1->Reset();
        JetEta2->Reset();
        JetEta3->Reset();
        JetEta4->Reset();
        JetEta5->Reset();
        JetEta6->Reset();
        JetEta7->Reset();
        JetEta8->Reset();

        MetJet1->Reset();
        MetJet2->Reset();
        MetJet3->Reset();
        MetJet4->Reset();
        MetJet5->Reset();
        MetJet6->Reset();
        MetJet7->Reset();
        MetJet8->Reset();

        MetMuon1->Reset();
        MetMuon2->Reset();
        MetMuon3->Reset();
        MetMuon4->Reset();
        MetMuon5->Reset();
        MetMuon6->Reset();
        MetMuon7->Reset();
        MetMuon8->Reset();

        JetMuon1->Reset();
        JetMuon2->Reset();
        JetMuon3->Reset();
        JetMuon4->Reset();
        JetMuon5->Reset();
        JetMuon6->Reset();
        JetMuon7->Reset();
        JetMuon8->Reset();

        JetMuonR1->Reset();
        JetMuonR2->Reset();
        JetMuonR3->Reset();
        JetMuonR4->Reset();
        JetMuonR5->Reset();
        JetMuonR6->Reset();
        JetMuonR7->Reset();
        JetMuonR8->Reset();

        MetJetPt1->Reset();
        MetJetPt2->Reset();
        MetJetPt3->Reset();
        MetJetPt4->Reset();
        MetJetPt5->Reset();
        MetJetPt6->Reset();
        MetJetPt7->Reset();
        MetJetPt8->Reset();

        ComboCuts1->Reset();
        ComboCuts2->Reset();
        ComboCuts3->Reset();
        ComboCuts4->Reset();
        ComboCuts5->Reset();

        WeightedMuons->Reset();

        TH2_MuonJetR->Reset();
        TH2_Isolation->Reset();
        TH2_MuonJetR->Reset();
        TH2_MuonJetPhi->Reset();
        TH2_MetMuonPhi->Reset();
        TH2_JetpT->Reset();

        // Close output file
        outFile->Close();
    }
    return 0;
}