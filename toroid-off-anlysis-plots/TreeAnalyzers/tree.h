//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  1 16:41:04 2023 by ROOT version 6.24/08
// from TTree tree/tree
// found on file: user.bcornish.32101026.ANOTHERSTREAM._000011.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include <TVector3.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "string"

#include "iostream"
#include <TF1.h>

#include "FitInfo.h"
#include "Plotter.h"

class tree {
public :
   TTree* fChain;  //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent;        //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        vx_x;
   Double_t        vx_y;
   Double_t        vx_z;
   Double_t        vx_chiSquared;
   Double_t        vx_nDOF;
   Int_t           seg1_index;
   Int_t           seg2_index;
   Int_t           seg3_index;
   Int_t           segger1_author;
   Int_t           segger1_muon_author;
   Bool_t          segger1_hitsOnTrack;
   Double_t        segger1_muon_pt;
   Double_t        segger1_muon_eta;
   Double_t        segger1_muon_phi;
   Int_t           segger2_author;
   Int_t           segger2_muon_author;
   Bool_t          segger2_hitsOnTrack;
   Double_t        segger2_muon_pt;
   Double_t        segger2_muon_eta;
   Double_t        segger2_muon_phi;
   Int_t           segger3_author;
   Int_t           segger3_muon_author;
   Bool_t          segger3_hitsOnTrack;
   Double_t        segger3_muon_pt;
   Double_t        segger3_muon_eta;
   Double_t        segger3_muon_phi;
   Int_t           segger1_nhits;
   Int_t           segger1_ntrackhits;
   Int_t           segger1_track_hitshare;
   std::vector<int>     *segger1_hitshare;
   Int_t           segger2_nhits;
   Int_t           segger2_ntrackhits;
   Int_t           segger2_track_hitshare;
   std::vector<int>     *segger2_hitshare;
   Int_t           segger3_nhits;
   Int_t           segger3_ntrackhits;
   Int_t           segger3_track_hitshare;
   std::vector<int>     *segger3_hitshare;
   UInt_t          cRunNumber;
   UInt_t          cEventNumber;
   UInt_t          cLumiBlock;
   Int_t           comb_muon_n;
   std::string          *comb_type;
   Int_t           comb_side;
   Int_t           comb_sector;
   Int_t           seg1_author;
   Int_t           seg1_eta_index;
   Int_t           seg1_tech;
   Int_t           seg1_cham_index;
   std::string          *seg1_name;
   std::string          *seg1_name_short;
   Double_t        seg1_x;
   Double_t        seg1_y;
   Double_t        seg1_z;
   Double_t        seg1_px;
   Double_t        seg1_py;
   Double_t        seg1_pz;
   Double_t        seg1_t0;
   Double_t        seg1_t0_error;
   Double_t        seg1_chisquare;
   Double_t        seg1_nDOF;
   Double_t        seg1_nPrecisionHits;
   Double_t        seg1_nTrigEtaLayers;
   Double_t        seg1_nTrigPhiLayers;
   Double_t        seg1_global_x;
   Double_t        seg1_global_y;
   Double_t        seg1_global_z;
   Double_t        seg1_global_px;
   Double_t        seg1_global_py;
   Double_t        seg1_global_pz;
   Double_t        seg1_local_x;
   Double_t        seg1_local_y;
   Double_t        seg1_local_z;
   Double_t        seg1_local_px;
   Double_t        seg1_local_py;
   Double_t        seg1_local_pz;
   Double_t        seg1_global_improved_x;
   Double_t        seg1_global_improved_y;
   Double_t        seg1_global_improved_z;
   Double_t        seg1_local_improved_x;
   Double_t        seg1_local_improved_y;
   Double_t        seg1_local_improved_z;
   Double_t        seg1_cham_x;
   Double_t        seg1_cham_y;
   Double_t        seg1_cham_z;
   Bool_t          seg1_hitreq;
   Bool_t          seg1_fitqual;
   Int_t           seg2_author;
   Int_t           seg2_eta_index;
   Int_t           seg2_tech;
   Int_t           seg2_cham_index;
   std::string          *seg2_name;
   std::string          *seg2_name_short;
   Double_t        seg2_x;
   Double_t        seg2_y;
   Double_t        seg2_z;
   Double_t        seg2_px;
   Double_t        seg2_py;
   Double_t        seg2_pz;
   Double_t        seg2_t0;
   Double_t        seg2_t0_error;
   Double_t        seg2_chisquare;
   Double_t        seg2_nDOF;
   Double_t        seg2_nPrecisionHits;
   Double_t        seg2_nTrigEtaLayers;
   Double_t        seg2_nTrigPhiLayers;
   Double_t        seg2_global_x;
   Double_t        seg2_global_y;
   Double_t        seg2_global_z;
   Double_t        seg2_global_px;
   Double_t        seg2_global_py;
   Double_t        seg2_global_pz;
   Double_t        seg2_local_x;
   Double_t        seg2_local_y;
   Double_t        seg2_local_z;
   Double_t        seg2_local_px;
   Double_t        seg2_local_py;
   Double_t        seg2_local_pz;
   Double_t        seg2_global_improved_x;
   Double_t        seg2_global_improved_y;
   Double_t        seg2_global_improved_z;
   Double_t        seg2_local_improved_x;
   Double_t        seg2_local_improved_y;
   Double_t        seg2_local_improved_z;
   Double_t        seg2_cham_x;
   Double_t        seg2_cham_y;
   Double_t        seg2_cham_z;
   Bool_t          seg2_hitreq;
   Bool_t          seg2_fitqual;
   Int_t           seg3_author;
   Int_t           seg3_eta_index;
   Int_t           seg3_tech;
   Int_t           seg3_cham_index;
   std::string          *seg3_name;
   std::string          *seg3_name_short;
   Double_t        seg3_x;
   Double_t        seg3_y;
   Double_t        seg3_z;
   Double_t        seg3_px;
   Double_t        seg3_py;
   Double_t        seg3_pz;
   Double_t        seg3_t0;
   Double_t        seg3_t0_error;
   Double_t        seg3_chisquare;
   Double_t        seg3_nDOF;
   Double_t        seg3_nPrecisionHits;
   Double_t        seg3_nTrigEtaLayers;
   Double_t        seg3_nTrigPhiLayers;
   Double_t        seg3_global_x;
   Double_t        seg3_global_y;
   Double_t        seg3_global_z;
   Double_t        seg3_global_px;
   Double_t        seg3_global_py;
   Double_t        seg3_global_pz;
   Double_t        seg3_local_x;
   Double_t        seg3_local_y;
   Double_t        seg3_local_z;
   Double_t        seg3_local_px;
   Double_t        seg3_local_py;
   Double_t        seg3_local_pz;
   Double_t        seg3_global_improved_x;
   Double_t        seg3_global_improved_y;
   Double_t        seg3_global_improved_z;
   Double_t        seg3_local_improved_x;
   Double_t        seg3_local_improved_y;
   Double_t        seg3_local_improved_z;
   Double_t        seg3_cham_x;
   Double_t        seg3_cham_y;
   Double_t        seg3_cham_z;
   Bool_t          seg3_hitreq;
   Bool_t          seg3_fitqual;
   Double_t        mm1_global_x;
   Double_t        mm1_global_y;
   Double_t        mm1_global_z;
   Double_t        mm1_global_px;
   Double_t        mm1_global_py;
   Double_t        mm1_global_pz;
   Double_t        mm1_local_x;
   Double_t        mm1_local_y;
   Double_t        mm1_local_z;
   Double_t        mm1_local_px;
   Double_t        mm1_local_py;
   Double_t        mm1_local_pz;
   Double_t        mm1_cham_x;
   Double_t        mm1_cham_y;
   Double_t        mm1_cham_z;
   Int_t           mm1_eta_index;
   Double_t        mm2_global_x;
   Double_t        mm2_global_y;
   Double_t        mm2_global_z;
   Double_t        mm2_global_px;
   Double_t        mm2_global_py;
   Double_t        mm2_global_pz;
   Double_t        mm2_local_x;
   Double_t        mm2_local_y;
   Double_t        mm2_local_z;
   Double_t        mm2_local_px;
   Double_t        mm2_local_py;
   Double_t        mm2_local_pz;
   Double_t        mm2_cham_x;
   Double_t        mm2_cham_y;
   Double_t        mm2_cham_z;
   Int_t           mm2_eta_index;
   Double_t        stgc1_global_x;
   Double_t        stgc1_global_y;
   Double_t        stgc1_global_z;
   Double_t        stgc1_global_px;
   Double_t        stgc1_global_py;
   Double_t        stgc1_global_pz;
   Double_t        stgc1_local_x;
   Double_t        stgc1_local_y;
   Double_t        stgc1_local_z;
   Double_t        stgc1_local_px;
   Double_t        stgc1_local_py;
   Double_t        stgc1_local_pz;
   Double_t        stgc1_cham_x;
   Double_t        stgc1_cham_y;
   Double_t        stgc1_cham_z;
   Int_t           stgc1_eta_index;
   Double_t        stgc2_global_x;
   Double_t        stgc2_global_y;
   Double_t        stgc2_global_z;
   Double_t        stgc2_global_px;
   Double_t        stgc2_global_py;
   Double_t        stgc2_global_pz;
   Double_t        stgc2_local_x;
   Double_t        stgc2_local_y;
   Double_t        stgc2_local_z;
   Double_t        stgc2_local_px;
   Double_t        stgc2_local_py;
   Double_t        stgc2_local_pz;
   Double_t        stgc2_cham_x;
   Double_t        stgc2_cham_y;
   Double_t        stgc2_cham_z;
   Int_t           stgc2_eta_index;
   Double_t        segger1_trk_match_id_count;
   Double_t        segger1_hitavg_global_x;
   Double_t        segger1_hitavg_global_y;
   Double_t        segger1_hitavg_global_z;
   Double_t        segger1_hitavg_local_x;
   Double_t        segger1_hitavg_local_y;
   Double_t        segger1_hitavg_local_z;
   Double_t        segger1_hitavg_global_px;
   Double_t        segger1_hitavg_global_py;
   Double_t        segger1_hitavg_global_pz;
   Double_t        segger1_hitavg_local_px;
   Double_t        segger1_hitavg_local_py;
   Double_t        segger1_hitavg_local_pz;
   Double_t        segger1_track_residual;
   Double_t        segger1_track_pull;
   Double_t        segger2_trk_match_id_count;
   Double_t        segger2_hitavg_global_x;
   Double_t        segger2_hitavg_global_y;
   Double_t        segger2_hitavg_global_z;
   Double_t        segger2_hitavg_local_x;
   Double_t        segger2_hitavg_local_y;
   Double_t        segger2_hitavg_local_z;
   Double_t        segger2_hitavg_global_px;
   Double_t        segger2_hitavg_global_py;
   Double_t        segger2_hitavg_global_pz;
   Double_t        segger2_hitavg_local_px;
   Double_t        segger2_hitavg_local_py;
   Double_t        segger2_hitavg_local_pz;
   Double_t        segger2_track_residual;
   Double_t        segger2_track_pull;
   Double_t        segger3_trk_match_id_count;
   Double_t        segger3_hitavg_global_x;
   Double_t        segger3_hitavg_global_y;
   Double_t        segger3_hitavg_global_z;
   Double_t        segger3_hitavg_local_x;
   Double_t        segger3_hitavg_local_y;
   Double_t        segger3_hitavg_local_z;
   Double_t        segger3_hitavg_global_px;
   Double_t        segger3_hitavg_global_py;
   Double_t        segger3_hitavg_global_pz;
   Double_t        segger3_hitavg_local_px;
   Double_t        segger3_hitavg_local_py;
   Double_t        segger3_hitavg_local_pz;
   Double_t        segger3_track_residual;
   Double_t        segger3_track_pull;

   // List of branches
   TBranch        *b_vx_x;   //!
   TBranch        *b_vx_y;   //!
   TBranch        *b_vx_z;   //!
   TBranch        *b_vx_chiSquared;   //!
   TBranch        *b_vx_nDOF;   //!
   TBranch        *b_seg1_index;   //!
   TBranch        *b_seg2_index;   //!
   TBranch        *b_seg3_index;   //!
   TBranch        *b_segger1_author;   //!
   TBranch        *b_segger1_muon_author;   //!
   TBranch        *b_segger1_hitsOnTrack;   //!
   TBranch        *b_segger1_muon_pt;   //!
   TBranch        *b_segger1_muon_eta;   //!
   TBranch        *b_segger1_muon_phi;   //!
   TBranch        *b_segger2_author;   //!
   TBranch        *b_segger2_muon_author;   //!
   TBranch        *b_segger2_hitsOnTrack;   //!
   TBranch        *b_segger2_muon_pt;   //!
   TBranch        *b_segger2_muon_eta;   //!
   TBranch        *b_segger2_muon_phi;   //!
   TBranch        *b_segger3_author;   //!
   TBranch        *b_segger3_muon_author;   //!
   TBranch        *b_segger3_hitsOnTrack;   //!
   TBranch        *b_segger3_muon_pt;   //!
   TBranch        *b_segger3_muon_eta;   //!
   TBranch        *b_segger3_muon_phi;   //!
   TBranch        *b_segger1_nhits;   //!
   TBranch        *b_segger1_ntrackhits;   //!
   TBranch        *b_segger1_track_hitshare;   //!
   TBranch        *b_segger1_hitshare;   //!
   TBranch        *b_segger2_nhits;   //!
   TBranch        *b_segger2_ntrackhits;   //!
   TBranch        *b_segger2_track_hitshare;   //!
   TBranch        *b_segger2_hitshare;   //!
   TBranch        *b_segger3_nhits;   //!
   TBranch        *b_segger3_ntrackhits;   //!
   TBranch        *b_segger3_track_hitshare;   //!
   TBranch        *b_segger3_hitshare;   //!
   TBranch        *b_cRunNumber;   //!
   TBranch        *b_cEventNumber;   //!
   TBranch        *b_cLumiBlock;   //!
   TBranch        *b_comb_muon_n;   //!
   TBranch        *b_comb_type;   //!
   TBranch        *b_comb_side;   //!
   TBranch        *b_comb_sector;   //!
   TBranch        *b_seg1_author;   //!
   TBranch        *b_seg1_eta_index;   //!
   TBranch        *b_seg1_tech;   //!
   TBranch        *b_seg1_cham_index;   //!
   TBranch        *b_seg1_name;   //!
   TBranch        *b_seg1_name_short;   //!
   TBranch        *b_seg1_x;   //!
   TBranch        *b_seg1_y;   //!
   TBranch        *b_seg1_z;   //!
   TBranch        *b_seg1_px;   //!
   TBranch        *b_seg1_py;   //!
   TBranch        *b_seg1_pz;   //!
   TBranch        *b_seg1_t0;   //!
   TBranch        *b_seg1_t0_error;   //!
   TBranch        *b_seg1_chisquare;   //!
   TBranch        *b_seg1_nDOF;   //!
   TBranch        *b_seg1_nPrecisionHits;   //!
   TBranch        *b_seg1_nTrigEtaLayers;   //!
   TBranch        *b_seg1_nTrigPhiLayers;   //!
   TBranch        *b_seg1_global_x;   //!
   TBranch        *b_seg1_global_y;   //!
   TBranch        *b_seg1_global_z;   //!
   TBranch        *b_seg1_global_px;   //!
   TBranch        *b_seg1_global_py;   //!
   TBranch        *b_seg1_global_pz;   //!
   TBranch        *b_seg1_local_x;   //!
   TBranch        *b_seg1_local_y;   //!
   TBranch        *b_seg1_local_z;   //!
   TBranch        *b_seg1_local_px;   //!
   TBranch        *b_seg1_local_py;   //!
   TBranch        *b_seg1_local_pz;   //!
   TBranch        *b_seg1_global_improved_x;
   TBranch        *b_seg1_global_improved_y;
   TBranch        *b_seg1_global_improved_z;
   TBranch        *b_seg1_local_improved_x;
   TBranch        *b_seg1_local_improved_y;
   TBranch        *b_seg1_local_improved_z;
   TBranch        *b_seg1_cham_x;   //!
   TBranch        *b_seg1_cham_y;   //!
   TBranch        *b_seg1_cham_z;   //!
   TBranch        *b_seg1_hitreq;   //!
   TBranch        *b_seg1_fitqual;   //!
   TBranch        *b_seg2_author;   //!
   TBranch        *b_seg2_eta_index;   //!
   TBranch        *b_seg2_tech;   //!
   TBranch        *b_seg2_cham_index;   //!
   TBranch        *b_seg2_name;   //!
   TBranch        *b_seg2_name_short;   //!
   TBranch        *b_seg2_x;   //!
   TBranch        *b_seg2_y;   //!
   TBranch        *b_seg2_z;   //!
   TBranch        *b_seg2_px;   //!
   TBranch        *b_seg2_py;   //!
   TBranch        *b_seg2_pz;   //!
   TBranch        *b_seg2_t0;   //!
   TBranch        *b_seg2_t0_error;   //!
   TBranch        *b_seg2_chisquare;   //!
   TBranch        *b_seg2_nDOF;   //!
   TBranch        *b_seg2_nPrecisionHits;   //!
   TBranch        *b_seg2_nTrigEtaLayers;   //!
   TBranch        *b_seg2_nTrigPhiLayers;   //!
   TBranch        *b_seg2_global_x;   //!
   TBranch        *b_seg2_global_y;   //!
   TBranch        *b_seg2_global_z;   //!
   TBranch        *b_seg2_global_px;   //!
   TBranch        *b_seg2_global_py;   //!
   TBranch        *b_seg2_global_pz;   //!
   TBranch        *b_seg2_local_x;   //!
   TBranch        *b_seg2_local_y;   //!
   TBranch        *b_seg2_local_z;   //!
   TBranch        *b_seg2_local_px;   //!
   TBranch        *b_seg2_local_py;   //!
   TBranch        *b_seg2_local_pz;   //!
   TBranch        *b_seg2_global_improved_x;
   TBranch        *b_seg2_global_improved_y;
   TBranch        *b_seg2_global_improved_z;
   TBranch        *b_seg2_local_improved_x;
   TBranch        *b_seg2_local_improved_y;
   TBranch        *b_seg2_local_improved_z;
   TBranch        *b_seg2_cham_x;   //!
   TBranch        *b_seg2_cham_y;   //!
   TBranch        *b_seg2_cham_z;   //!
   TBranch        *b_seg2_hitreq;   //!
   TBranch        *b_seg2_fitqual;   //!
   TBranch        *b_seg3_author;   //!
   TBranch        *b_seg3_eta_index;   //!
   TBranch        *b_seg3_tech;   //!
   TBranch        *b_seg3_cham_index;   //!
   TBranch        *b_seg3_name;   //!
   TBranch        *b_seg3_name_short;   //!
   TBranch        *b_seg3_x;   //!
   TBranch        *b_seg3_y;   //!
   TBranch        *b_seg3_z;   //!
   TBranch        *b_seg3_px;   //!
   TBranch        *b_seg3_py;   //!
   TBranch        *b_seg3_pz;   //!
   TBranch        *b_seg3_t0;   //!
   TBranch        *b_seg3_t0_error;   //!
   TBranch        *b_seg3_chisquare;   //!
   TBranch        *b_seg3_nDOF;   //!
   TBranch        *b_seg3_nPrecisionHits;   //!
   TBranch        *b_seg3_nTrigEtaLayers;   //!
   TBranch        *b_seg3_nTrigPhiLayers;   //!
   TBranch        *b_seg3_global_x;   //!
   TBranch        *b_seg3_global_y;   //!
   TBranch        *b_seg3_global_z;   //!
   TBranch        *b_seg3_global_px;   //!
   TBranch        *b_seg3_global_py;   //!
   TBranch        *b_seg3_global_pz;   //!
   TBranch        *b_seg3_local_x;   //!
   TBranch        *b_seg3_local_y;   //!
   TBranch        *b_seg3_local_z;   //!
   TBranch        *b_seg3_local_px;   //!
   TBranch        *b_seg3_local_py;   //!
   TBranch        *b_seg3_local_pz;   //!
   TBranch        *b_seg3_global_improved_x;
   TBranch        *b_seg3_global_improved_y;
   TBranch        *b_seg3_global_improved_z;
   TBranch        *b_seg3_local_improved_x;
   TBranch        *b_seg3_local_improved_y;
   TBranch        *b_seg3_local_improved_z;
   TBranch        *b_seg3_cham_x;   //!
   TBranch        *b_seg3_cham_y;   //!
   TBranch        *b_seg3_cham_z;   //!
   TBranch        *b_seg3_hitreq;   //!
   TBranch        *b_seg3_fitqual;   //!
   TBranch        *b_mm1_global_x;   //!
   TBranch        *b_mm1_global_y;   //!
   TBranch        *b_mm1_global_z;   //!
   TBranch        *b_mm1_global_px;   //!
   TBranch        *b_mm1_global_py;   //!
   TBranch        *b_mm1_global_pz;   //!
   TBranch        *b_mm1_local_x;   //!
   TBranch        *b_mm1_local_y;   //!
   TBranch        *b_mm1_local_z;   //!
   TBranch        *b_mm1_local_px;   //!
   TBranch        *b_mm1_local_py;   //!
   TBranch        *b_mm1_local_pz;   //!
   TBranch        *b_mm1_cham_x;   //!
   TBranch        *b_mm1_cham_y;   //!
   TBranch        *b_mm1_cham_z;   //!
   TBranch        *b_mm1_eta_index;   //!
   TBranch        *b_mm2_global_x;   //!
   TBranch        *b_mm2_global_y;   //!
   TBranch        *b_mm2_global_z;   //!
   TBranch        *b_mm2_global_px;   //!
   TBranch        *b_mm2_global_py;   //!
   TBranch        *b_mm2_global_pz;   //!
   TBranch        *b_mm2_local_x;   //!
   TBranch        *b_mm2_local_y;   //!
   TBranch        *b_mm2_local_z;   //!
   TBranch        *b_mm2_local_px;   //!
   TBranch        *b_mm2_local_py;   //!
   TBranch        *b_mm2_local_pz;   //!
   TBranch        *b_mm2_cham_x;   //!
   TBranch        *b_mm2_cham_y;   //!
   TBranch        *b_mm2_cham_z;   //!
   TBranch        *b_mm2_eta_index;   //!
   TBranch        *b_stgc1_global_x;   //!
   TBranch        *b_stgc1_global_y;   //!
   TBranch        *b_stgc1_global_z;   //!
   TBranch        *b_stgc1_global_px;   //!
   TBranch        *b_stgc1_global_py;   //!
   TBranch        *b_stgc1_global_pz;   //!
   TBranch        *b_stgc1_local_x;   //!
   TBranch        *b_stgc1_local_y;   //!
   TBranch        *b_stgc1_local_z;   //!
   TBranch        *b_stgc1_local_px;   //!
   TBranch        *b_stgc1_local_py;   //!
   TBranch        *b_stgc1_local_pz;   //!
   TBranch        *b_stgc1_cham_x;   //!
   TBranch        *b_stgc1_cham_y;   //!
   TBranch        *b_stgc1_cham_z;   //!
   TBranch        *b_stgc1_eta_index;   //!
   TBranch        *b_stgc2_global_x;   //!
   TBranch        *b_stgc2_global_y;   //!
   TBranch        *b_stgc2_global_z;   //!
   TBranch        *b_stgc2_global_px;   //!
   TBranch        *b_stgc2_global_py;   //!
   TBranch        *b_stgc2_global_pz;   //!
   TBranch        *b_stgc2_local_x;   //!
   TBranch        *b_stgc2_local_y;   //!
   TBranch        *b_stgc2_local_z;   //!
   TBranch        *b_stgc2_local_px;   //!
   TBranch        *b_stgc2_local_py;   //!
   TBranch        *b_stgc2_local_pz;   //!
   TBranch        *b_stgc2_cham_x;   //!
   TBranch        *b_stgc2_cham_y;   //!
   TBranch        *b_stgc2_cham_z;   //!
   TBranch        *b_stgc2_eta_index;   //!
   TBranch        *b_segger1_trk_match_id_count;   //!
   TBranch        *b_segger1_hitavg_global_x;   //!
   TBranch        *b_segger1_hitavg_global_y;   //!
   TBranch        *b_segger1_hitavg_global_z;   //!
   TBranch        *b_segger1_hitavg_local_x;   //!
   TBranch        *b_segger1_hitavg_local_y;   //!
   TBranch        *b_segger1_hitavg_local_z;   //!
   TBranch        *b_segger1_hitavg_global_px;   //!
   TBranch        *b_segger1_hitavg_global_py;   //!
   TBranch        *b_segger1_hitavg_global_pz;   //!
   TBranch        *b_segger1_hitavg_local_px;   //!
   TBranch        *b_segger1_hitavg_local_py;   //!
   TBranch        *b_segger1_hitavg_local_pz;   //!
   TBranch        *b_segger1_track_residual;   //!
   TBranch        *b_segger1_track_pull;   //!
   TBranch        *b_segger2_trk_match_id_count;   //!
   TBranch        *b_segger2_hitavg_global_x;   //!
   TBranch        *b_segger2_hitavg_global_y;   //!
   TBranch        *b_segger2_hitavg_global_z;   //!
   TBranch        *b_segger2_hitavg_local_x;   //!
   TBranch        *b_segger2_hitavg_local_y;   //!
   TBranch        *b_segger2_hitavg_local_z;   //!
   TBranch        *b_segger2_hitavg_global_px;   //!
   TBranch        *b_segger2_hitavg_global_py;   //!
   TBranch        *b_segger2_hitavg_global_pz;   //!
   TBranch        *b_segger2_hitavg_local_px;   //!
   TBranch        *b_segger2_hitavg_local_py;   //!
   TBranch        *b_segger2_hitavg_local_pz;   //!
   TBranch        *b_segger2_track_residual;   //!
   TBranch        *b_segger2_track_pull;   //!
   TBranch        *b_segger3_trk_match_id_count;   //!
   TBranch        *b_segger3_hitavg_global_x;   //!
   TBranch        *b_segger3_hitavg_global_y;   //!
   TBranch        *b_segger3_hitavg_global_z;   //!
   TBranch        *b_segger3_hitavg_local_x;   //!
   TBranch        *b_segger3_hitavg_local_y;   //!
   TBranch        *b_segger3_hitavg_local_z;   //!
   TBranch        *b_segger3_hitavg_global_px;   //!
   TBranch        *b_segger3_hitavg_global_py;   //!
   TBranch        *b_segger3_hitavg_global_pz;   //!
   TBranch        *b_segger3_hitavg_local_px;   //!
   TBranch        *b_segger3_hitavg_local_py;   //!
   TBranch        *b_segger3_hitavg_local_pz;   //!
   TBranch        *b_segger3_track_residual;   //!
   TBranch        *b_segger3_track_pull;   //!

   tree(TTree*);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree*);
   virtual void     Loop();
   void             Initialize();
   void             Plot();
   void             ReadHistsFromFile();
   void             WriteHistsToFile();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   private: 
   void CreateSagittaHist(std::vector< std::unique_ptr<TH1F> > &hist, int index, int momentum, std::string side);

   // this is hardcoded direction depending on which sector we are
   // As the chambers are installed/mounted such that the precision coordinate is precise within 2mrad this effect is small
   // and within precision this assumption is correct
   std::vector<TVector3> wire_vec{
       {0., 1., 0.},
       {-0.38268343236, 0.92387953251, 0.},
       {-0.70710678118, 0.70710678118, 0.},
       {-0.92387953251, 0.38268343236, 0.},
       {-1., 0., 0.},
       {-0.92387953251, -0.38268343236, 0.},
       {-0.70710678118, -0.70710678118, 0.},
       {-0.38268343236, -0.92387953251, 0.},
       {0., -1., 0.},
       {0.38268343236, -0.92387953251, 0.},
       {0.70710678118, -0.70710678118, 0.},
       {0.92387953251, -0.38268343236, 0.},
       {1., 0., 0.},
       {0.92387953251, 0.38268343236, 0.},
       {0.70710678118, 0.70710678118, 0.},
       {0.38268343236, 0.92387953251, 0.},
   };

   std::unique_ptr<Plotter> plotter;

   
   std::vector< std::unique_ptr<TH1F> > seg1_nhits_hist_per_sector_aside_hists;
   std::vector< std::unique_ptr<TH1F> > seg2_nhits_hist_per_sector_aside_hists;
   std::vector< std::unique_ptr<TH1F> > seg3_nhits_hist_per_sector_aside_hists;

   std::vector< std::unique_ptr<TH1F> > seg1_nhits_hist_per_sector_cside_hists;
   std::vector< std::unique_ptr<TH1F> > seg2_nhits_hist_per_sector_cside_hists;
   std::vector< std::unique_ptr<TH1F> > seg3_nhits_hist_per_sector_cside_hists;


   std::unique_ptr<TH2F> seg1_xy_aside_hist;
   std::unique_ptr<TH2F> seg2_xy_aside_hist;
   std::unique_ptr<TH2F> seg3_xy_aside_hist;

   std::unique_ptr<TH2F> seg1x_seg2x_aside_hist;
   std::unique_ptr<TH2F> seg1x_seg3x_aside_hist;
   std::unique_ptr<TH2F> seg2x_seg3x_aside_hist;

   std::unique_ptr<TH2F> seg1y_seg2y_aside_hist;
   std::unique_ptr<TH2F> seg1y_seg3y_aside_hist;
   std::unique_ptr<TH2F> seg2y_seg3y_aside_hist;

   std::unique_ptr<TH2F> seg1z_seg2z_aside_hist;
   std::unique_ptr<TH2F> seg1z_seg3z_aside_hist;
   std::unique_ptr<TH2F> seg2z_seg3z_aside_hist;

   // std::unique_ptr<TH1F> seg1_nhits_aside_hist;
   // std::unique_ptr<TH1F> seg2_nhits_aside_hist;
   // std::unique_ptr<TH1F> seg3_nhits_aside_hist;


   std::unique_ptr<TH2F> seg1_xy_cside_hist;
   std::unique_ptr<TH2F> seg2_xy_cside_hist;
   std::unique_ptr<TH2F> seg3_xy_cside_hist;

   std::unique_ptr<TH2F> seg1x_seg2x_cside_hist;
   std::unique_ptr<TH2F> seg1x_seg3x_cside_hist;
   std::unique_ptr<TH2F> seg2x_seg3x_cside_hist;

   std::unique_ptr<TH2F> seg1y_seg2y_cside_hist;
   std::unique_ptr<TH2F> seg1y_seg3y_cside_hist;
   std::unique_ptr<TH2F> seg2y_seg3y_cside_hist;

   std::unique_ptr<TH2F> seg1z_seg2z_cside_hist;
   std::unique_ptr<TH2F> seg1z_seg3z_cside_hist;
   std::unique_ptr<TH2F> seg2z_seg3z_cside_hist;


   // std::unique_ptr<TH1F> seg1_nhits_cside_hist;
   // std::unique_ptr<TH1F> seg2_nhits_cside_hist;
   // std::unique_ptr<TH1F> seg3_nhits_cside_hist;


   std::unique_ptr<TH2F> seg1_eta_hist;
   std::unique_ptr<TH2F> seg2_eta_hist;
   std::unique_ptr<TH2F> seg3_eta_hist;
   std::unique_ptr<TH2F> seg1_phi_hist;
   std::unique_ptr<TH2F> seg2_phi_hist;
   std::unique_ptr<TH2F> seg3_phi_hist;

   std::unique_ptr<TH2F> seg1_seg2_eta_hist;
   std::unique_ptr<TH2F> seg1_seg3_eta_hist;
   std::unique_ptr<TH2F> seg2_seg3_eta_hist;
   std::unique_ptr<TH2F> seg1_seg2_phi_hist;
   std::unique_ptr<TH2F> seg1_seg3_phi_hist;
   std::unique_ptr<TH2F> seg2_seg3_phi_hist;


   std::unique_ptr<TH1F> sagitta_0p_hist;
   std::unique_ptr<TH1F> sagitta_10p_hist;
   std::unique_ptr<TH1F> sagitta_15p_hist;
   std::unique_ptr<TH1F> sagitta_20p_hist;
   std::unique_ptr<TH1F> sagitta_30p_hist;
   std::unique_ptr<TH1F> sagitta_50p_hist;
   
   std::unique_ptr<TH1F> muon_p_hist;
   std::unique_ptr<TH1F> muon_p_selection_hist;
   std::unique_ptr<TH1F> muon_pT_hist;
   std::unique_ptr<TH1F> muon_pT_selection_hist;

   std::unique_ptr<TH2F> mm1_xy_aside_hist;
   std::unique_ptr<TH2F> mm2_xy_aside_hist;
   std::unique_ptr<TH2F> stgc1_xy_aside_hist;
   std::unique_ptr<TH2F> stgc2_xy_aside_hist;
   std::unique_ptr<TH2F> mm1_xy_cside_hist;
   std::unique_ptr<TH2F> mm2_xy_cside_hist;
   std::unique_ptr<TH2F> stgc1_xy_cside_hist;
   std::unique_ptr<TH2F> stgc2_xy_cside_hist;


   std::unique_ptr<TH1F> seg1_track_residual_hist;
   std::unique_ptr<TH1F> seg2_track_residual_hist;
   std::unique_ptr<TH1F> seg3_track_residual_hist;

   std::unique_ptr<TH1F> seg1_track_pull_hist;
   std::unique_ptr<TH1F> seg2_track_pull_hist;
   std::unique_ptr<TH1F> seg3_track_pull_hist;



   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_hist; 
   std::vector< std::unique_ptr<TH1F> > sagittas_a_5p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_15p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_25p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_35p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_45p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_hist; 
   std::vector< std::unique_ptr<TH1F> > sagittas_c_5p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_15p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_25p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_35p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_45p_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_hist;


   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_improved_hist; 
   std::vector< std::unique_ptr<TH1F> > sagittas_a_5p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_15p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_25p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_35p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_45p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_200p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_300p_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_mm1_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_mm2_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_stgc1_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_stgc2_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_mm1_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_mm2_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_stgc1_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_a_0p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_10p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_20p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_30p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_40p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_50p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_a_100p_stgc2_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_improved_hist; 
   std::vector< std::unique_ptr<TH1F> > sagittas_c_5p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_15p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_25p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_35p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_45p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_200p_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_300p_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_mm1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_mm1_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_mm2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_mm2_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_stgc1_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_stgc1_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_stgc2_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_stgc2_improved_hist;


   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_mm1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_mm1_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_mm2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_mm2_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_stgc1_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_stgc1_t_improved_hist;

   std::vector< std::unique_ptr<TH1F> > sagittas_c_0p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_10p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_20p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_30p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_40p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_50p_stgc2_t_improved_hist;
   std::vector< std::unique_ptr<TH1F> > sagittas_c_100p_stgc2_t_improved_hist;






   std::vector< std::unique_ptr<TH1F> > sagitta_a_2nd_coord_0p_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_a_2nd_coord_30p_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_c_2nd_coord_0p_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_c_2nd_coord_30p_hist; 

   std::vector< std::unique_ptr<TH1F> > sagitta_a_2nd_coord_0p_improved_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_a_2nd_coord_30p_improved_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_c_2nd_coord_0p_improved_hist; 
   std::vector< std::unique_ptr<TH1F> > sagitta_c_2nd_coord_30p_improved_hist; 


   std::vector< std::unique_ptr<TH1F> > sagitta_a_t223_30p_hist;





   int nbins = 70;
   double x_min = -14000;
   double x_max = 14000;
   double y_min = -14000;
   double y_max = 14000;

   // double x_min = -2000;
   // double x_max = 2000;
   // double y_min = -2000;
   // double y_max = 2000;

   int sag_bins = 80; 
   double sag_min = -50;
   double sag_max = 50;



};

#endif
