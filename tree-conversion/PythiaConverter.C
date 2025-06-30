
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <filesystem>
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TDirectory.h"
#include "TTree.h"
#include "TString.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <TLorentzVector.h>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <cmath>
#include <math.h>
#include <TMath.h>
#include <fstream>

void convert_tree(TString fileIn)
{
  auto start_sample = std::chrono::high_resolution_clock::now();

  std::cout << "------------------------------------------------------------------------------------" << std::endl;


  // define output file name
  string fileOut = "data" + ".root";
  string outname = "../converted-outputs/" + fileOut;
  // check if file exists
  if (std::filesystem::exists(outname)) {
    std::cout << "File already exists: " << outname << std::endl;
    return;
  }

  // INSERT NEW TREE NAME HERE
  TString treeIn = "TreeAlgo/nominal";

  // create chain and load tree
  TChain fChain(treeIn);
  fChain.AddFile(fileIn);

  // make tree reader
  TTreeReader myReader(&fChain);
  TTreeReaderValue<float> weight_pileup(myReader, "weight_pileup");
  TTreeReaderValue<float> metFinalTrk(myReader, "metFinalTrk");
  TTreeReaderValue<float> metFinalTrkPhi(myReader, "metFinalTrkPhi");
  TTreeReaderArray<string> passedTriggers(myReader, "passedTriggers");

  TTreeReaderArray<float> el_m(myReader, "el_m");
  TTreeReaderArray<float> el_pt(myReader, "el_pt");
  TTreeReaderArray<float> el_phi(myReader, "el_phi");
  TTreeReaderArray<float> el_eta(myReader, "el_eta");
  TTreeReaderArray<float> el_charge(myReader, "el_charge"); 
  TTreeReaderArray<float> el_trkd0(myReader, "el_trkd0");
  TTreeReaderArray<float> el_trkz0(myReader, "el_trkz0");
  TTreeReaderArray<float> el_trkd0sig(myReader, "el_trkd0sig");
  TTreeReaderArray<float> el_trkz0sintheta(myReader, "el_trkz0sintheta");
  TTreeReaderArray<float> el_caloCluster_eta(myReader, "el_caloCluster_eta");
  TTreeReaderArray<char> el_passOR(myReader, "el_passOR");
  TTreeReaderArray<int> el_isIsolated_FCTight(myReader, "el_isIsolated_FCTight");
  TTreeReaderArray<int> el_isIsolated_FCLoose(myReader, "el_isIsolated_FCLoose");
  TTreeReaderArray<int> el_DFCommonElectronsLHTight(myReader, "el_DFCommonElectronsLHTight");
  TTreeReaderArray<int> el_DFCommonElectronsLHLooseBL(myReader, "el_DFCommonElectronsLHLooseBL");

  TTreeReaderArray<float> muon_m(myReader, "muon_m");
  TTreeReaderArray<float> muon_pt(myReader, "muon_pt");
  TTreeReaderArray<float> muon_phi(myReader, "muon_phi");
  TTreeReaderArray<float> muon_eta(myReader, "muon_eta");
  TTreeReaderArray<float> muon_trkd0(myReader, "muon_trkd0");
  TTreeReaderArray<float> muon_trkz0(myReader, "muon_trkz0");
  TTreeReaderArray<float> muon_trkd0sig(myReader, "muon_trkd0sig");
  TTreeReaderArray<float> muon_trkz0sintheta(myReader, "muon_trkz0sintheta");
  TTreeReaderArray<char> muon_passOR(myReader, "muon_passOR");
  TTreeReaderArray<int> muon_isIsolated_PflowTight_FixedRad(myReader, "muon_isIsolated_PflowTight_FixedRad");
  TTreeReaderArray<int> muon_isIsolated_PflowLoose_FixedRad(myReader, "muon_isIsolated_PflowLoose_FixedRad");

  TTreeReaderArray<float> jet_E(myReader, "jet_E");
  TTreeReaderArray<float> jet_pt(myReader, "jet_pt");
  TTreeReaderArray<float> jet_phi(myReader, "jet_phi");
  TTreeReaderArray<float> jet_eta(myReader, "jet_eta");
  TTreeReaderArray<char> jet_passOR(myReader, "jet_passOR");
  TTreeReaderArray<int> jet_JvtPass_Tight(myReader, "jet_JvtPass_Tight");
  TTreeReaderArray<int> jet_fJvtPass_Tight(myReader, "jet_fJvtPass_Tight");
  TTreeReaderArray<int> jet_is_DL1r_FixedCutBEff_85(myReader, "jet_is_DL1r_FixedCutBEff_85");

  // get the file name (not whole path)
  std::string fileIn_str = fileIn.Data();
  std::string fileIn_print = fileIn_str.substr(fileIn_str.find_last_of("/\\") + 1);

  // print input and output file names
  std::cout << "Input file: " << fileIn_print << std::endl;
  std::cout << "Output file: " << outname << std::endl;
  
  // open a new file to put the output 
  TFile *myfile = TFile::Open(outname.c_str(), "recreate");

  // init number of entries and percentage processed
  int nentries = fChain.GetEntries();
  int ientry = 0;
  int percent = 0;

  // ********** //
  // event loop //
  // ********** //

  TTree *outtree;
  outtree = new TTree("ObservableTree","Particle Data");

  float event_weights;

  int nMuonBare;
  int nNeutrino;   
  
  float muon_bare_pt;
  float muon_bare_eta;
  float muon_bare_phi;
  float muon_bare_E;
  float muon_bare_charge;

  float neutrino_pt;
  float neutrino_eta;
  float neutrino_phi;
  float neutrino_E;

  float lightjet_bare_pt;
  float lightjet_bare_eta;
  float lightjet_bare_phi;
  float lightjet_bare_E;

  double Met;
  double Met_phi;
  
  float muonisolation_pt;

  
  outtree->Branch("event_weights",&event_weights);

  outtree->Branch("nMuonBare",&nMuonBare);
  outtree->Branch("nNeutrino",&nNeutrino);

  outtree->Branch("muon_bare_pt",&muon_bare_pt);
  outtree->Branch("muon_bare_eta",&muon_bare_eta);
  outtree->Branch("muon_bare_phi",&muon_bare_phi);
  outtree->Branch("muon_bare_E",&muon_bare_E);
  outtree->Branch("muon_bare_charge",&muon_bare_charge);

  // Note that these variables are not provided by the original tree
  // Should be fine for the purpose of these analyses - if needed, can import them and transfer similarly to muon
  outtree->Branch("neutrino_pt",&neutrino_pt);
  outtree->Branch("neutrino_eta",&neutrino_eta);
  outtree->Branch("neutrino_phi",&neutrino_phi);
  outtree->Branch("neutrino_E",&neutrino_E);

  outtree->Branch("lightjet_bare_pt",&lightjet_bare_pt);
  outtree->Branch("lightjet_bare_eta",&lightjet_bare_eta);
  outtree->Branch("lightjet_bare_phi",&lightjet_bare_phi);
  outtree->Branch("lightjet_bare_E",&lightjet_bare_E);

  outtree->Branch("Met",&Met);
  outtree->Branch("Met_phi",&Met_phi);

  // See ANA_utils.cc on Alex's github for the changes that were implamented to create this variable in the pythia code
  outtree->Branch("muonisolation_pt",&muonisolation_pt);



  while (myReader.Next())
  {

    // Store muon variables in new tree.
    // TO DO: muon_E is not in the variables that Camilla imports, check how to import this (important for Analysis Code)
    //          This might be as simple as reading in from the tree muon_E but I don't have the original tree right now
    //        Same thing for muon_charge (less important)
    for (int itmuo = 0; itmuo<muon_pt.GetSize(); itmuo++) {
      nMuonBare ++;
      muon_bare_pt.push_back(muon_pt);
      muon_bare_eta.push_back(muon_eta);
      muon_bare_phi.push_back(muon_phi);
      // muon_bare_E.push_back(muon_E);
    }

    //Store jet variables in a new tree.
    for (int itjet = 0; itjet<jet_pt.GetSize(); itjet++) {
      lightjet_bare_pt.push_back(jet_pt);
      lightjet_bare_eta.push_back(jet_eta);
      lightjet_bare_phi.push_back(jet_phi);
      lightjet_bare_E.push_back(jet_E);
    }

    // Store MET
    Met.push_back(metFinalTrk);
    Met_phi.push_back(metFinalTrk_phi);

  }

  myfile->cd();

  // Fill histograms
  outtree.Write();

  // Close output file
  myfile->Write();
  myfile->Close();


  // Print summary
  std::cout << "Done: " << fileOut << std::endl;

  delete myfile;

  // Force cleanup of any remaining ROOT objects
  gROOT->GetListOfFiles()->Clear();
  gROOT->GetListOfCanvases()->Clear();
  gDirectory->Clear();
  
}




//================================================================================//
//=============================== Main Function ==================================//
//================================================================================//

void PythiaConverter(string channel, string year, string period)
{

  string sampleList = "dataList_" + year + ".csv";

  TString fileIn = "NULL";

  fstream fileStream;
  fileStream.open("./samples/" + sampleList);
  string line;
  while (getline(fileStream, line))
  {

    // Path to input files - UPDATE
    TString path = "/cluster/tufts/beaucheminlab/cpazos01/wjets-maker-outputs/data/data_trees/";

    string str;
    stringstream ss(line);

    path.Append(fileIn);
        
    convert_tree(path);

  }
  fileStream.close();
}