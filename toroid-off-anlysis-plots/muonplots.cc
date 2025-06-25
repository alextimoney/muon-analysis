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
#include <vector>
#include <math.h>
#include <dirent.h>
#include <muonplots.h>

string outname = "test.root";

// Declare root histograms
TH1F *L1MU20VFC_hist = new TH1F("L1MU20VFC_hist","L1MU20VFC and cumulative muon pt",8,0,8);
TH1F *muon_pt_mu5_hist   = new TH1F("muon_pt_mu5_hist","muon pt for mu5 trigger",60,0,60000);
TH1F *muon_pt_mu8_hist   = new TH1F("muon_pt_mu8_hist","muon pt for mu8 trigger",60,0,60000);
TH1F *muon_pt_mu10_hist   = new TH1F("muon_pt_mu10_hist","muon pt for mu10 trigger",60,0,60000);
TH1F *muon_pt_mu20_hist   = new TH1F("muon_pt_mu20_hist","muon pt for mu20 trigger",60,0,60000);
TH1F *muon_pt_mu25_hist   = new TH1F("muon_pt_mu25_hist","muon pt for mu25 trigger",60,0,60000);
TH1F *muon_pt_mu30_hist   = new TH1F("muon_pt_mu30_hist","muon pt for mu30 trigger",60,0,60000);
TH1F *muon_pt_mu50_hist   = new TH1F("muon_pt_mu50_hist","muon pt for mu50 trigger",60,0,60000);

void Init(TTree *tree);
void Loop(string outfile);

int main() {
    TTree *tree = 0;
    std::vector<string> samples;
    DIR *dir_ptr;
    struct dirent *diread;
    if ((dir_ptr = opendir("/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510137_EXT1")) != nullptr) {
        while ((diread = readdir(dir_ptr)) != nullptr) {
            string sample = diread->d_name;
            if (sample.find(".root") != string::npos){
                samples.push_back(sample);
            }
        }
        closedir(dir_ptr);
    }
    for(int i = 0; i < samples.size(); i++) {
        string inFile = "/eos/user/n/ngarelli/ToroidOffBlines/alignment_toroid_off/alignment_rel22_v3/user.ngarelli.Blines_Athena24029_4510137_EXT1/" + samples[i];
        string outfile = "./mtree_out/mtree_out" + samples[i];
        // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(inFile.c_str());
        // if (!f || !f->IsOpen() || f == nullptr) {
        TFile *f = new TFile(inFile.c_str());
        // }
        f->GetObject("mtree",tree);
        Init(tree);
        Loop(outfile);
    }
}

void Init(TTree *tree) {
    TTree *fChain = tree;
    // fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("mRunNumber", &mRunNumber, &b_mRunNumber);
    fChain->SetBranchAddress("mEventNumber", &mEventNumber, &b_mEventNumber);
    fChain->SetBranchAddress("mLumiBlock", &mLumiBlock, &b_mLumiBlock);
    fChain->SetBranchAddress("L1_Passed", &L1_Passed, &b_L1_Passed);
    fChain->SetBranchAddress("HLT_Passed", &HLT_Passed, &b_HLT_Passed);
    fChain->SetBranchAddress("HLT_mu5_mucombTag_L1MU20VFC_Passed", &HLT_mu5_mucombTag_L1MU20VFC_Passed, &b_HLT_mu5_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu8_mucombTag_L1MU20VFC_Passed", &HLT_mu8_mucombTag_L1MU20VFC_Passed, &b_HLT_mu8_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu10_mucombTag_L1MU20VFC_Passed", &HLT_mu10_mucombTag_L1MU20VFC_Passed, &b_HLT_mu10_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu15_mucombTag_L1MU20VFC_Passed", &HLT_mu15_mucombTag_L1MU20VFC_Passed, &b_HLT_mu15_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu20_mucombTag_L1MU20VFC_Passed", &HLT_mu20_mucombTag_L1MU20VFC_Passed, &b_HLT_mu20_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu25_mucombTag_L1MU20VFC_Passed", &HLT_mu25_mucombTag_L1MU20VFC_Passed, &b_HLT_mu25_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu30_mucombTag_L1MU20VFC_Passed", &HLT_mu30_mucombTag_L1MU20VFC_Passed, &b_HLT_mu30_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("HLT_mu50_mucombTag_L1MU20VFC_Passed", &HLT_mu50_mucombTag_L1MU20VFC_Passed, &b_HLT_mu50_mucombTag_L1MU20VFC_Passed);
    fChain->SetBranchAddress("muon_n", &muon_n, &b_muon_n);
    fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
    fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
    fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
    fChain->SetBranchAddress("muon_m", &muon_m, &b_muon_m);
    fChain->SetBranchAddress("muon_e", &muon_e, &b_muon_e);
    fChain->SetBranchAddress("muon_charge", &muon_charge, &b_muon_charge);
    fChain->SetBranchAddress("muon_type", &muon_type, &b_muon_type);
}

void Loop(string outfile) {
    TFile outputFile("./mtree_out/mtree_out.root","RECREATE");
}
// {
//     TFile infile = "anotherstream.root";

//    TH1F *L1MU20VFC_hist = new TH1F("L1MU20VFC_hist","L1MU20VFC and cumulative muon pt",8,0,8);
// }