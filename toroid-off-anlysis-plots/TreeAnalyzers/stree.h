//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 25 15:00:35 2023 by ROOT version 6.26/08
// from TTree stree/stree
// found on file: /eos/user/b/bcornish/Documents/rucio_out/user.bcornish.data22_13p6TeV.00435751.00435777.physics_Main.recon.DESDM_MCP.r14640.v3_ANOTHERSTREAM/user.bcornish.33439099.ANOTHERSTREAM._000111.root
//////////////////////////////////////////////////////////

#ifndef stree_h
#define stree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TF1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include <TVector3.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "string"

#include "iostream"

#include "FitInfo.h"
#include "Plotter.h"

class stree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          sRunNumber;
   UInt_t          sEventNumber;
   UInt_t          sLumiBlock;
   Int_t           seg_muon_n;
   Int_t           seg_author;
   Int_t           seg_eta_index;
   Int_t           seg_tech;
   Int_t           seg_cham_index;
   std::string          *seg_name;
   std::string          *seg_name_short;
   Bool_t          seg_haveTrkSeg;
   Int_t           seg_identifier;
   Int_t           seg_index;
   Double_t        seg_x;
   Double_t        seg_y;
   Double_t        seg_z;
   Double_t        seg_px;
   Double_t        seg_py;
   Double_t        seg_pz;
   Double_t        seg_t0;
   Double_t        seg_t0_error;
   Double_t        seg_chisquare;
   Double_t        seg_nDOF;
   Double_t        seg_nPrecisionHits;
   Double_t        seg_nTrigEtaLayers;
   Double_t        seg_nTrigPhiLayers;
   Double_t        seg_global_x;
   Double_t        seg_global_y;
   Double_t        seg_global_z;
   Double_t        seg_global_px;
   Double_t        seg_global_py;
   Double_t        seg_global_pz;
   Double_t        seg_local_x;
   Double_t        seg_local_y;
   Double_t        seg_local_z;
   Double_t        seg_local_px;
   Double_t        seg_local_py;
   Double_t        seg_local_pz;
   Double_t        seg_cham_x;
   Double_t        seg_cham_y;
   Double_t        seg_cham_z;
   std::vector<double>  *seg_vMB_x;
   std::vector<double>  *seg_vMB_y;
   std::vector<double>  *seg_vMB_z;
   Int_t           seg_nhits;
   Int_t           seg_ntrackhits;
   Int_t           seg_track_hitshare;
   std::vector<int>     *seg_hitshare;
   Int_t           seg_hitreq;
   Bool_t          seg_fitqual;
   Float_t         seg_residual;
   Float_t         seg_pull;
   Double_t        seg_trk_match_id;
   Double_t        seg_trk_pos_global_x;
   Double_t        seg_trk_pos_global_y;
   Double_t        seg_trk_pos_global_z;
   Double_t        seg_trk_pos_local_x;
   Double_t        seg_trk_pos_local_y;
   Double_t        seg_trk_pos_local_z;
   Double_t        seg_trk_dir_global_x;
   Double_t        seg_trk_dir_global_y;
   Double_t        seg_trk_dir_global_z;
   Double_t        seg_trk_dir_local_x;
   Double_t        seg_trk_dir_local_y;
   Double_t        seg_trk_dir_local_z;
   UInt_t          sILumiBlock;

   // List of branches
   TBranch        *b_sRunNumber;   //!
   TBranch        *b_sEventNumber;   //!
   TBranch        *b_sLumiBlock;   //!
   TBranch        *b_seg_muon_n;   //!
   TBranch        *b_seg_author;   //!
   TBranch        *b_seg_eta_index;   //!
   TBranch        *b_seg_tech;   //!
   TBranch        *b_seg_cham_index;   //!
   TBranch        *b_seg_name;   //!
   TBranch        *b_seg_name_short;   //!
   TBranch        *b_seg_haveTrkSeg;   //!
   TBranch        *b_seg_identifier;   //!
   TBranch        *b_seg_index;   //!
   TBranch        *b_seg_x;   //!
   TBranch        *b_seg_y;   //!
   TBranch        *b_seg_z;   //!
   TBranch        *b_seg_px;   //!
   TBranch        *b_seg_py;   //!
   TBranch        *b_seg_pz;   //!
   TBranch        *b_seg_t0;   //!
   TBranch        *b_seg_t0_error;   //!
   TBranch        *b_seg_chisquare;   //!
   TBranch        *b_seg_nDOF;   //!
   TBranch        *b_seg_nPrecisionHits;   //!
   TBranch        *b_seg_nTrigEtaLayers;   //!
   TBranch        *b_seg_nTrigPhiLayers;   //!
   TBranch        *b_seg_global_x;   //!
   TBranch        *b_seg_global_y;   //!
   TBranch        *b_seg_global_z;   //!
   TBranch        *b_seg_global_px;   //!
   TBranch        *b_seg_global_py;   //!
   TBranch        *b_seg_global_pz;   //!
   TBranch        *b_seg_local_x;   //!
   TBranch        *b_seg_local_y;   //!
   TBranch        *b_seg_local_z;   //!
   TBranch        *b_seg_local_px;   //!
   TBranch        *b_seg_local_py;   //!
   TBranch        *b_seg_local_pz;   //!
   TBranch        *b_seg_cham_x;   //!
   TBranch        *b_seg_cham_y;   //!
   TBranch        *b_seg_cham_z;   //!
   TBranch        *b_seg_vMB_x;   //!
   TBranch        *b_seg_vMB_y;   //!
   TBranch        *b_seg_vMB_z;   //!
   TBranch        *b_seg_nhits;   //!
   TBranch        *b_seg_ntrackhits;   //!
   TBranch        *b_seg_track_hitshare;   //!
   TBranch        *b_seg_hitshare;   //!
   TBranch        *b_seg_hitreq;   //!
   TBranch        *b_seg_fitqual;   //!
   TBranch        *b_seg_residual;   //!
   TBranch        *b_seg_pull;   //!
   TBranch        *b_seg_trk_match_id;   //!
   TBranch        *b_seg_trk_pos_global_x;   //!
   TBranch        *b_seg_trk_pos_global_y;   //!
   TBranch        *b_seg_trk_pos_global_z;   //!
   TBranch        *b_seg_trk_pos_local_x;   //!
   TBranch        *b_seg_trk_pos_local_y;   //!
   TBranch        *b_seg_trk_pos_local_z;   //!
   TBranch        *b_seg_trk_dir_global_x;   //!
   TBranch        *b_seg_trk_dir_global_y;   //!
   TBranch        *b_seg_trk_dir_global_z;   //!
   TBranch        *b_seg_trk_dir_local_x;   //!
   TBranch        *b_seg_trk_dir_local_y;   //!
   TBranch        *b_seg_trk_dir_local_z;   //!
   TBranch        *b_sILumiBlock;   //!


   stree(TTree *tree=0);
   virtual ~stree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *stree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void             Initialize();
   // void             Plot();
   // void             ReadHistsFromFile();
   // void             WriteHistsToFile();


    std::unique_ptr<Plotter> plotter;



};

#endif
