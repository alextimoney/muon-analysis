#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string> 
#include <math.h>
#include <vector>
// #include "Math/GenVector/Cartesian3D.h"
// #include <Cartesian3D.h>



void tree::Loop()
{
   int nbins = 50;
   double x_min = -14000;
   double x_max = 14000;
   double y_min = -14000;
   double y_max = 14000;

   // double x_min = -2000;
   // double x_max = 2000;
   // double y_min = -2000;
   // double y_max = 2000;

   double sag_min = -50;
   double sag_max = 50;





   // A-side plots

   TH2F *seg1_xy_aside_hist = new TH2F("seg1_xy_aside_hist","seg1 x vs seg1 y for A-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *seg2_xy_aside_hist = new TH2F("seg2_xy_aside_hist","seg2 x vs seg2 y for A-side",nbins,-10000,10000,nbins,-10000,10000);
   TH2F *seg3_xy_aside_hist = new TH2F("seg3_xy_aside_hist","seg3 x vs seg3 y for A-side",nbins,x_min,x_max,nbins,y_min,y_max);


   TH2F *seg1x_seg2x_aside_hist = new TH2F("seg1x_seg2x_aside_hist","seg1 x vs seg2 x for A-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg1x_seg3x_aside_hist = new TH2F("seg1x_seg3x_aside_hist","seg1 x vs seg3 x for A-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg2x_seg3x_aside_hist = new TH2F("seg2x_seg3x_aside_hist","seg2 x vs seg3 x for A-side",nbins,x_min,x_max,nbins,y_min,y_max);

   TH2F *seg1y_seg2y_aside_hist = new TH2F("seg1y_seg2y_aside_hist","seg1 y vs seg2 y for A-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg1y_seg3y_aside_hist = new TH2F("seg1y_seg3y_aside_hist","seg1 y vs seg3 y for A-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg2y_seg3y_aside_hist = new TH2F("seg2y_seg3y_aside_hist","seg2 y vs seg3 y for A-side",nbins,x_min,x_max,nbins,y_min,y_max);

   TH2F *seg1z_seg2z_aside_hist = new TH2F("seg1z_seg2z_aside_hist","seg1 z vs seg2 z for A-side",nbins,-25000,25000,nbins,-25000,25000);
   TH2F *seg1z_seg3z_aside_hist = new TH2F("seg1z_seg3z_aside_hist","seg1 z vs seg3 z for A-side",nbins,-25000,25000,nbins,-25000,25000);
   TH2F *seg2z_seg3z_aside_hist = new TH2F("seg2z_seg3z_aside_hist","seg2 z vs seg3 z for A-side",nbins,-25000,25000,nbins,-25000,25000);


   TH1F *seg1_nhits_aside_hist = new TH1F("seg1_nhits_aside_hist","inner wheel nhits for A-side",20,0,20);
   TH1F *seg2_nhits_aside_hist = new TH1F("seg2_nhits_aside_hist","middle wheel nhits for A-side",20,0,20);
   TH1F *seg3_nhits_aside_hist = new TH1F("seg3_nhits_aside_hist","outer wheel nhits for A-side",20,0,20);


   char *a_hist_name = new char[10];
   TH1F *seg1_nhits_hist_per_sector_aside_hists[16];
   TH1F *seg2_nhits_hist_per_sector_aside_hists[16];
   TH1F *seg3_nhits_hist_per_sector_aside_hists[16];

   TH1F *stgc1_sagitta_per_sector_aside_hists[16];
   TH1F *stgc2_sagitta_per_sector_aside_hists[16];
   TH1F *mm1_sagitta_per_sector_aside_hists[16];
   TH1F *mm2_sagitta_per_sector_aside_hists[16];

   for(int i = 0; i < 16; i++){
      sprintf(a_hist_name,"seg1 sector%d nhits for A-side",i+1); 
      seg1_nhits_hist_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,20,0,20);

      sprintf(a_hist_name,"seg2 sector%d nhits for A-side",i+1); 
      seg2_nhits_hist_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,20,0,20);

      sprintf(a_hist_name,"seg3 sector%d nhits for A-side",i+1); 
      seg3_nhits_hist_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,20,0,20);

      sprintf(a_hist_name,"stgc1 sector%d xy for A-side",i+1); 
      stgc1_sagitta_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,80,sag_min,sag_max);
      sprintf(a_hist_name,"stgc2 sector%d xy for A-side",i+1); 
      stgc2_sagitta_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,80,sag_min,sag_max);
      sprintf(a_hist_name,"mm1 sector%d xy for A-side",i+1); 
      mm1_sagitta_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,80,sag_min,sag_max);
      sprintf(a_hist_name,"mm2 sector%d xy for A-side",i+1); 
      mm2_sagitta_per_sector_aside_hists[i] = new TH1F(a_hist_name,a_hist_name,80,sag_min,sag_max);
   }

   // C-side plots

   TH2F *seg1_xy_cside_hist = new TH2F("seg1_xy_cside_hist","seg1 x vs seg1 y for C-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *seg2_xy_cside_hist = new TH2F("seg2_xy_cside_hist","seg2 x vs seg2 y for C-side",nbins,-10000,10000,nbins,-10000,10000);
   TH2F *seg3_xy_cside_hist = new TH2F("seg3_xy_cside_hist","seg3 x vs seg3 y for C-side",nbins,x_min,x_max,nbins,y_min,y_max);


   TH2F *seg1x_seg2x_cside_hist = new TH2F("seg1x_seg2x_cside_hist","seg1 x vs seg2 x for C-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg1x_seg3x_cside_hist = new TH2F("seg1x_seg3x_cside_hist","seg1 x vs seg3 x for C-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg2x_seg3x_cside_hist = new TH2F("seg2x_seg3x_cside_hist","seg2 x vs seg3 x for C-side",nbins,x_min,x_max,nbins,y_min,y_max);

   TH2F *seg1y_seg2y_cside_hist = new TH2F("seg1y_seg2y_cside_hist","seg1 y vs seg2 y for C-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg1y_seg3y_cside_hist = new TH2F("seg1y_seg3y_cside_hist","seg1 y vs seg3 y for C-side",nbins,x_min,x_max,nbins,y_min,y_max);
   TH2F *seg2y_seg3y_cside_hist = new TH2F("seg2y_seg3y_cside_hist","seg2 y vs seg3 y for C-side",nbins,x_min,x_max,nbins,y_min,y_max);

   TH2F *seg1z_seg2z_cside_hist = new TH2F("seg1z_seg2z_cside_hist","seg1 z vs seg2 z for C-side",nbins,-25000,25000,nbins,-25000,25000);
   TH2F *seg1z_seg3z_cside_hist = new TH2F("seg1z_seg3z_cside_hist","seg1 z vs seg3 z for C-side",nbins,-25000,25000,nbins,-25000,25000);
   TH2F *seg2z_seg3z_cside_hist = new TH2F("seg2z_seg3z_cside_hist","seg2 z vs seg3 z for C-side",nbins,-25000,25000,nbins,-25000,25000);


   TH1F *seg1_nhits_cside_hist = new TH1F("seg1_nhits_cside_hist","inner wheel nhits for C-side",20,0,20);
   TH1F *seg2_nhits_cside_hist = new TH1F("seg2_nhits_cside_hist","middle wheel nhits for C-side",20,0,20);
   TH1F *seg3_nhits_cside_hist = new TH1F("seg3_nhits_cside_hist","outer wheel nhits for C-side",20,0,20);


   char *c_hist_name = new char[10];
   TH1F *seg1_nhits_hist_per_sector_cside_hists[16];
   TH1F *seg2_nhits_hist_per_sector_cside_hists[16];
   TH1F *seg3_nhits_hist_per_sector_cside_hists[16];

   TH1F *stgc1_sagitta_per_sector_cside_hists[16];
   TH1F *stgc2_sagitta_per_sector_cside_hists[16];
   TH1F *mm1_sagitta_per_sector_cside_hists[16];
   TH1F *mm2_sagitta_per_sector_cside_hists[16];

   for(int i = 0; i < 16; i++){
      sprintf(c_hist_name,"seg1 sector%d nhits for C-side",i+1); 
      seg1_nhits_hist_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,20,0,20);

      sprintf(c_hist_name,"seg2 sector%d nhits for C-side",i+1); 
      seg2_nhits_hist_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,20,0,20);

      sprintf(c_hist_name,"seg3 sector%d nhits for C-side",i+1); 
      seg3_nhits_hist_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,20,0,20);

      sprintf(c_hist_name,"stgc1 sector%d xy for C-side",i+1); 
      stgc1_sagitta_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,80,sag_min,sag_max);
      sprintf(c_hist_name,"stgc2 sector%d xy for C-side",i+1); 
      stgc2_sagitta_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,80,sag_min,sag_max);
      sprintf(c_hist_name,"mm1 sector%d xy for C-side",i+1); 
      mm1_sagitta_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,80,sag_min,sag_max);
      sprintf(c_hist_name,"mm2 sector%d xy for C-side",i+1); 
      mm2_sagitta_per_sector_cside_hists[i] = new TH1F(c_hist_name,c_hist_name,80,sag_min,sag_max);
   }



   TH2F *seg1_eta_hist = new TH2F("seg1_eta_hist","seg1 eta vs muon eta",60,-3,3,60,-3,3);
   TH2F *seg2_eta_hist = new TH2F("seg2_eta_hist","seg2 eta vs muon eta",60,-3,3,60,-3,3);
   TH2F *seg3_eta_hist = new TH2F("seg3_eta_hist","seg3 eta vs muon eta",60,-3,3,60,-3,3);

   TH2F *seg1_phi_hist = new TH2F("seg1_phi_hist","seg1 phi vs muon phi",60,-3.5,3.5,60,-3.5,3.5);
   TH2F *seg2_phi_hist = new TH2F("seg2_phi_hist","seg2 phi vs muon phi",60,-3.5,3.5,60,-3.5,3.5);
   TH2F *seg3_phi_hist = new TH2F("seg3_phi_hist","seg3 phi vs muon phi",60,-3.5,3.5,60,-3.5,3.5);

   TH2F *seg1_seg2_eta_hist = new TH2F("seg1_seg2_eta_hist","seg1 eta vs seg2 eta",60,-3,3,60,-3,3);
   TH2F *seg1_seg3_eta_hist = new TH2F("seg1_seg3_eta_hist","seg1 eta vs seg3 eta",60,-3,3,60,-3,3);
   TH2F *seg2_seg3_eta_hist = new TH2F("seg2_seg3_eta_hist","seg2 eta vs seg3 eta",60,-3,3,60,-3,3);

   TH2F *seg1_seg2_phi_hist = new TH2F("seg1_seg2_phi_hist","seg1 phi vs seg2 phi",60,-3.5,3.5,60,-3.5,3.5);
   TH2F *seg1_seg3_phi_hist = new TH2F("seg1_seg3_phi_hist","seg1 phi vs seg3 phi",60,-3.5,3.5,60,-3.5,3.5);
   TH2F *seg2_seg3_phi_hist = new TH2F("seg2_seg3_phi_hist","seg2 phi vs seg3 phi",60,-3.5,3.5,60,-3.5,3.5);



   TH1F *sagitta_0pt_hist = new TH1F("sagitta_0pt_hist","Sagitta constructed from segment positions: mu pT > 0",80,sag_min,sag_max);
   TH1F *sagitta_3pt_hist = new TH1F("sagitta_3pt_hist","Sagitta constructed from segment positions: mu pT > 3",80,sag_min,sag_max);
   TH1F *sagitta_5pt_hist = new TH1F("sagitta_5pt_hist","Sagitta constructed from segment positions: mu pT > 5",80,sag_min,sag_max);
   TH1F *sagitta_10pt_hist = new TH1F("sagitta_10pt_hist","Sagitta constructed from segment positions: mu pT > 10",80,sag_min,sag_max);
   TH1F *sagitta_15pt_hist = new TH1F("sagitta_15pt_hist","Sagitta constructed from segment positions: mu pT > 15",80,sag_min,sag_max);

   TH2F *stgc1_xy_aside_hist = new TH2F("stgc1_xy_aside_hist","sTGC1 x vs y for A-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *stgc2_xy_aside_hist = new TH2F("stgc2_xy_aside_hist","sTGC2 x vs y for A-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *mm1_xy_aside_hist = new TH2F("mm1_xy_aside_hist","MM1 x vs y for A-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *mm2_xy_aside_hist = new TH2F("mm2_xy_aside_hist","MM2 x vs y for A-side",nbins,-5500,5500,nbins,-5500,5500);

   TH2F *stgc1_xy_cside_hist = new TH2F("stgc1_xy_cside_hist","sTGC1 x vs y for C-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *stgc2_xy_cside_hist = new TH2F("stgc2_xy_cside_hist","sTGC2 x vs y for C-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *mm1_xy_cside_hist = new TH2F("mm1_xy_cside_hist","MM1 x vs y for C-side",nbins,-5500,5500,nbins,-5500,5500);
   TH2F *mm2_xy_cside_hist = new TH2F("mm2_xy_cside_hist","MM2 x vs y for C-side",nbins,-5500,5500,nbins,-5500,5500);




   vector<TVector3> wire_vec
   {
      {0.,1.,0.},
      {-0.38268343236,0.92387953251,0.},
      {-0.70710678118,0.70710678118,0.},
      {-0.92387953251,0.38268343236,0.},
      {-1.,0.,0.},
      {-0.92387953251,-0.38268343236,0.},
      {-0.70710678118,-0.70710678118,0.},
      {-0.38268343236,-0.92387953251,0.},
      {0.,-1.,0.},
      {0.38268343236,-0.92387953251,0.},
      {0.70710678118,-0.70710678118,0.},
      {0.92387953251,-0.38268343236,0.},
      {1.,0.,0.},
      {0.92387953251,0.38268343236,0.},
      {0.70710678118,0.70710678118,0.},
      {0.38268343236,0.92387953251,0.},
   };





   if (fChain == 0) return;

   int nentries = fChain->GetEntriesFast();
   // int nentries = 1000;
   std::cout << "Looping over " << nentries << " events" << std::endl;


   int passed = 0;
   int failed = 0;
   for (int i=0; i<nentries; i++) {
      fChain->GetEntry(i);

      // Need to define comb_id first. This should all be in a function defined in a header somewhere
       int comb_id;
       string s1 = *seg1_name_short;
       string s2 = *seg2_name_short;
       string s3 = *seg3_name_short;
       string name = s1+s2+s3;
       if (name == "eiemeo") {
           comb_id = 1;
       }
       else if (name == "eieeem") {
           comb_id = 2;
       }
       else if (name == "eibeem") {
           comb_id = 3;
       }
       else if (name == "csemeo") {
           comb_id = 4;
       }

      // Calculate values

      TVector3 seg1_vec(seg1_global_x, seg1_global_y, seg1_global_z);
      TVector3 seg2_vec(seg2_global_x, seg2_global_y, seg2_global_z);
      TVector3 seg3_vec(seg3_global_x, seg3_global_y, seg3_global_z);

      double seg1_eta = seg1_vec.Eta();
      double seg2_eta = seg2_vec.Eta();
      double seg3_eta = seg3_vec.Eta();

      double seg1_phi = seg1_vec.Phi();
      double seg2_phi = seg2_vec.Phi();
      double seg3_phi = seg3_vec.Phi();

      // Sagitta

      TVector3 IM_vec = seg2_vec - seg1_vec;
      TVector3 IO_vec = seg3_vec - seg1_vec;
      
      // double sagitta = (IM_vec - ((IM_vec * IO_vec)/(IO_vec * IO_vec)*IO_vec)).Mag(); // * will do a dot product
      TVector3 w = wire_vec[comb_sector-1];
      // double sagitta = IM_vec * ( w.Cross(IO_vec) / (w.Cross(IO_vec)).Mag() );
      double sagitta = IM_vec * ( w.Cross(IO_vec) * (1/(w.Cross(IO_vec)).Mag()) );



      // substitute out NSW segs 
      // seg1_global_x = stgc1_global_x;
      // seg1_global_y = stgc1_global_y;
      // seg1_global_z = stgc1_global_z;

      // seg1_global_x = stgc2_global_x;
      // seg1_global_y = stgc2_global_y;
      // seg1_global_z = stgc2_global_z;

      // seg1_global_x = mm1_global_x;
      // seg1_global_y = mm1_global_y;
      // seg1_global_z = mm1_global_z;

      // seg1_global_x = mm2_global_x;
      // seg1_global_y = mm2_global_y;
      // seg1_global_z = mm2_global_z;





      // Cuts
      bool pass_cuts = true;
      // pass_cuts = false;

      // Fit quality cuts
      if (seg1_chisquare/seg1_nDOF > 10. && seg2_chisquare/seg2_nDOF > 10. && seg3_chisquare/seg3_nDOF > 10.) {
         pass_cuts = false;
      }

      // Precision cuts
      if (comb_id == 1 || comb_id == 3) {
         if (!seg1_hitreq || !seg2_hitreq || !seg3_hitreq) { // this will not work because in code jordy has set seg 1 hit req to 0
         // if (seg1_nPrecisionHits < 2  || !seg2_hitreq || !seg3_hitreq) {
            pass_cuts = false;
         }
      }
      else if (comb_id == 2) {
         if (!seg1_hitreq || seg2_nPrecisionHits < 5 || !seg3_hitreq) {
            pass_cuts = false;
         }
      } 
      else if (comb_id == 4) {
         if (seg1_nPrecisionHits < 2 || !seg2_hitreq || !seg3_hitreq) {
            pass_cuts = false;
         }
      }

      // TGC phi hit cuts:
      if (comb_id==1 || comb_id==4) {
         if (seg2_nTrigPhiLayers < 0) {
            pass_cuts = false;
         }
      }
      else if (comb_id==2 || comb_id==3) {
         if (seg3_nTrigPhiLayers < 0) {
            pass_cuts = false;
         }
      }

      // Track hit pointing
      if ( (segger1_muon_pt == -999999) || (segger2_muon_pt == -999999) || (segger3_muon_pt == -999999) ) {
         pass_cuts = false;
      }
      else if ( (segger1_muon_pt!=segger2_muon_pt) || (segger1_muon_eta!=segger2_muon_eta) || (segger1_muon_phi!=segger2_muon_phi)  ) {
         pass_cuts = false;
      }
      else if ( (segger1_muon_pt!=segger3_muon_pt) || (segger1_muon_eta!=segger3_muon_eta) || (segger1_muon_phi!=segger3_muon_phi)  ) {
         pass_cuts = false;
      }


      // Track hit share
      if ( (segger1_track_hitshare < 4)  ||  (segger1_track_hitshare < segger1_nhits - 1) ) {
         pass_cuts = false;
      }
      if ( (segger2_track_hitshare < 4)  ||  (segger2_track_hitshare < segger2_nhits - 1) ) {
         pass_cuts = false;
      }
      if ( (segger3_track_hitshare < 4)  ||  (segger3_track_hitshare < segger3_nhits - 1) ) {
         pass_cuts = false;
      }


      // Segment pointing 

      double seg1_seg2_deta = seg1_eta - seg2_eta;
      double seg1_seg3_deta = seg1_eta - seg3_eta;
      double seg2_seg3_deta = seg2_eta - seg3_eta;

      double seg1_seg2_dphi = seg1_vec.DeltaPhi(seg2_vec);
      double seg1_seg3_dphi = seg1_vec.DeltaPhi(seg2_vec);
      double seg2_seg3_dphi = seg2_vec.DeltaPhi(seg2_vec);

      if ( fabs(seg1_seg2_deta) > 0.05 || fabs(seg1_seg2_dphi) > 0.5 ) {
         pass_cuts = false;
      }
      if ( fabs(seg1_seg3_deta) > 0.05 || fabs(seg1_seg3_dphi) > 0.5 ) {
         pass_cuts = false;
      }
      if ( fabs(seg2_seg3_deta) > 0.05 || fabs(seg2_seg3_dphi) > 0.5 ) {
         pass_cuts = false;
      }

      // Segment hit sharing
      // If the hitshare is non-zero then it fail, unless the hitshare count is 1 for seg 1, 2 and 3.

      int s1_count = 0;
      int s2_count = 0;
      int s3_count = 0;
      bool pass_hitshare = true;

      for (int track = 0; track < segger1_hitshare->size(); ++track) {
         if (track > 0) {
            pass_hitshare = false;
            s1_count+=1;
         }
      }
      for (int track = 0; track < segger2_hitshare->size(); ++track) {
         if (track > 0) {
            pass_hitshare = false;
            s2_count+=1;
         }
      }
      for (int track = 0; track < segger3_hitshare->size(); ++track) {
         if (track > 0) {
            pass_hitshare = false;
            s3_count+=1;
         }
      }

      if (!pass_hitshare && s1_count==1 && s2_count==1 && s3_count==1) {
         pass_hitshare = true;
      }
        
      if (pass_hitshare == false) {
         pass_cuts = false;
      }



      // Muon author
      if ( (segger1_muon_author == -999999) || (segger1_muon_author != segger2_muon_author) || (segger1_muon_author != segger3_muon_author) ) {
         pass_cuts = false;
      }

      // High pt / forward
      if ( (segger1_muon_pt < 0) and segger1_muon_pt*std::cosh(segger1_muon_eta) > 40000. ) {
         pass_cuts = false;
      }

      // Segs bounded within chambers
      // big stuff
      
      // pass_cuts = true;

      // just look at NSW for now 
      if (comb_id !=1) {
         pass_cuts = false;
      }


      // Fill hists
      // pass_cuts = true;
      if (pass_cuts == true) {passed++;}
      if (pass_cuts == false) {failed++;}
      if (pass_cuts) 
      {

         // if (seg1_global_x > 0) 
         // {

         if (seg1_eta_index > 0) 
         {
            seg1_xy_aside_hist->Fill(seg1_global_x,seg1_global_y);
            seg2_xy_aside_hist->Fill(seg2_global_x,seg2_global_y);
            seg3_xy_aside_hist->Fill(seg3_global_x,seg3_global_y);

            seg1x_seg2x_aside_hist->Fill(seg1_global_x,seg2_global_x);
            seg1x_seg3x_aside_hist->Fill(seg1_global_x,seg3_global_x);
            seg2x_seg3x_aside_hist->Fill(seg2_global_x,seg3_global_x);

            seg1y_seg2y_aside_hist->Fill(seg1_global_y,seg2_global_y);
            seg1y_seg3y_aside_hist->Fill(seg1_global_y,seg3_global_y);
            seg2y_seg3y_aside_hist->Fill(seg2_global_y,seg3_global_y);

            seg1z_seg2z_aside_hist->Fill(seg1_global_z,seg2_global_z);
            seg1z_seg3z_aside_hist->Fill(seg1_global_z,seg3_global_z);
            seg2z_seg3z_aside_hist->Fill(seg2_global_z,seg3_global_z);

            seg1_nhits_hist_per_sector_aside_hists[comb_sector-1]->Fill(seg1_nPrecisionHits);
            seg2_nhits_hist_per_sector_aside_hists[comb_sector-1]->Fill(seg2_nPrecisionHits);
            seg3_nhits_hist_per_sector_aside_hists[comb_sector-1]->Fill(seg3_nPrecisionHits);

            stgc1_xy_aside_hist->Fill(stgc1_global_x,stgc1_global_y);
            stgc2_xy_aside_hist->Fill(stgc2_global_x,stgc2_global_y);
            mm1_xy_aside_hist->Fill(mm1_global_x,mm1_global_y);
            mm2_xy_aside_hist->Fill(mm2_global_x,mm2_global_y);

            stgc1_sagitta_per_sector_aside_hists[comb_sector-1]->Fill(sagitta);
            stgc2_sagitta_per_sector_aside_hists[comb_sector-1]->Fill(sagitta);
            mm1_sagitta_per_sector_aside_hists[comb_sector-1]->Fill(sagitta);
            mm2_sagitta_per_sector_aside_hists[comb_sector-1]->Fill(sagitta);
         }

         if (seg1_eta_index < 0) 
         {
            seg1_xy_cside_hist->Fill(seg1_global_x,seg1_global_y);
            seg2_xy_cside_hist->Fill(seg2_global_x,seg2_global_y);
            seg3_xy_cside_hist->Fill(seg3_global_x,seg3_global_y);

            seg1x_seg2x_cside_hist->Fill(seg1_global_x,seg2_global_x);
            seg1x_seg3x_cside_hist->Fill(seg1_global_x,seg3_global_x);
            seg2x_seg3x_cside_hist->Fill(seg2_global_x,seg3_global_x);

            seg1y_seg2y_cside_hist->Fill(seg1_global_y,seg2_global_y);
            seg1y_seg3y_cside_hist->Fill(seg1_global_y,seg3_global_y);
            seg2y_seg3y_cside_hist->Fill(seg2_global_y,seg3_global_y);

            seg1z_seg2z_cside_hist->Fill(seg1_global_z,seg2_global_z);
            seg1z_seg3z_cside_hist->Fill(seg1_global_z,seg3_global_z);
            seg2z_seg3z_cside_hist->Fill(seg2_global_z,seg3_global_z);

            seg1_nhits_hist_per_sector_cside_hists[comb_sector-1]->Fill(seg1_nPrecisionHits);
            seg2_nhits_hist_per_sector_cside_hists[comb_sector-1]->Fill(seg2_nPrecisionHits);
            seg3_nhits_hist_per_sector_cside_hists[comb_sector-1]->Fill(seg3_nPrecisionHits);

            stgc1_xy_cside_hist->Fill(stgc1_global_x,stgc1_global_y);
            stgc2_xy_cside_hist->Fill(stgc2_global_x,stgc2_global_y);
            mm1_xy_cside_hist->Fill(mm1_global_x,mm1_global_y);
            mm2_xy_cside_hist->Fill(mm2_global_x,mm2_global_y);

            stgc1_sagitta_per_sector_cside_hists[comb_sector-1]->Fill(sagitta);
            stgc2_sagitta_per_sector_cside_hists[comb_sector-1]->Fill(sagitta);
            mm1_sagitta_per_sector_cside_hists[comb_sector-1]->Fill(sagitta);
            mm2_sagitta_per_sector_cside_hists[comb_sector-1]->Fill(sagitta);
         }
      // }


         // Eta phi plots 

         seg1_eta_hist->Fill(seg1_eta,segger1_muon_eta);
         seg2_eta_hist->Fill(seg2_eta,segger2_muon_eta);
         seg3_eta_hist->Fill(seg3_eta,segger3_muon_eta);

         seg1_phi_hist->Fill(seg1_phi,segger1_muon_phi);
         seg2_phi_hist->Fill(seg2_phi,segger2_muon_phi);
         seg3_phi_hist->Fill(seg3_phi,segger3_muon_phi);

         seg1_seg2_eta_hist->Fill(seg1_eta,seg2_eta);
         seg1_seg3_eta_hist->Fill(seg1_eta,seg3_eta);
         seg2_seg3_eta_hist->Fill(seg2_eta,seg3_eta);

         seg1_seg2_phi_hist->Fill(seg1_phi,seg2_phi);
         seg1_seg3_phi_hist->Fill(seg1_phi,seg3_phi);
         seg2_seg3_phi_hist->Fill(seg2_phi,seg3_phi);

         // std::cout << segger1_muon_pt << std::endl;
         // if (comb_id == 1) {
            if (segger1_muon_pt > 0.) {
               // std::cout << "0 - sag: " << sagitta << std::endl;
               sagitta_0pt_hist->Fill(sagitta);
            }
            if (segger1_muon_pt > 3000.) {
               // std::cout << "3 - sag: " << sagitta << std::endl;
               sagitta_3pt_hist->Fill(sagitta);
            }
            if (segger1_muon_pt > 5000.) {
               // std::cout << "5 - sag: " << sagitta << std::endl;
               sagitta_5pt_hist->Fill(sagitta);
            }
            if (segger1_muon_pt > 10000.) {
               // std::cout << "10 - sag: " << sagitta << std::endl;
               sagitta_10pt_hist->Fill(sagitta);
            }
            if (segger1_muon_pt > 15000.) {
               // std::cout << "10 - sag: " << sagitta << std::endl;
               sagitta_15pt_hist->Fill(sagitta);
            }
         // }
      

      }





   }

   std::cout << "Passed: " << passed << "   Failed: " << failed << std::endl;


   // Cauchy distribution

   TF1 *f1 = new TF1("f1","[0]*TMath::CauchyDist(x,[1],[2])+[3]",-10,10);
   f1->SetParameters(sagitta_15pt_hist->GetMaximum(), 0, 1, 0);
   f1->SetParNames( "Normalization","b", "m" ,"Constant1");


   int canvas_x = 850;
   int canvas_y = 850;

   TCanvas *c1 = new TCanvas("c1","x vs y A-side",canvas_x,canvas_y);
   // TCanvas *c2 = new TCanvas("c2","x comparisons A-side",canvas_x,canvas_y);
   // TCanvas *c3 = new TCanvas("c3","y comparisons A-side",canvas_x,canvas_y);
   // TCanvas *c4 = new TCanvas("c4","z comparisons A-side",canvas_x,canvas_y);
   // TCanvas *c5 = new TCanvas("c5","seg1 nhits per sector A-side",canvas_x,canvas_y);
   // TCanvas *c6 = new TCanvas("c6","seg2 nhits per sector A-side",canvas_x,canvas_y);
   // TCanvas *c7 = new TCanvas("c7","seg3 nhits per sector A-side",canvas_x,canvas_y);

   TCanvas *c8 = new TCanvas("c8","x vs y C-side",canvas_x,canvas_y);
   // TCanvas *c9 = new TCanvas("c9","x comparisons C-side",canvas_x,canvas_y);
   // TCanvas *c10 = new TCanvas("c10","y comparisons C-side",canvas_x,canvas_y);
   // TCanvas *c11 = new TCanvas("c11","z comparisons C-side",canvas_x,canvas_y);
   // TCanvas *c12 = new TCanvas("c12","seg1 nhits per sector C-side",canvas_x,canvas_y);
   // TCanvas *c13 = new TCanvas("c13","seg2 nhits per sector C-side",canvas_x,canvas_y);
   // TCanvas *c14 = new TCanvas("c14","seg3 nhits per sector C-side",canvas_x,canvas_y);

   // TCanvas *c15 = new TCanvas("c15","seg eta vs muon eta",canvas_x,canvas_y);
   // TCanvas *c16 = new TCanvas("c16","seg phi vs muon phi",canvas_x,canvas_y);
   // TCanvas *c17 = new TCanvas("c17","segs eta",canvas_x,canvas_y);
   // TCanvas *c18 = new TCanvas("c18","segs phi",canvas_x,canvas_y);
   TCanvas *c19 = new TCanvas("c19","sagitta 0mev",canvas_x,canvas_y);
   TCanvas *c20 = new TCanvas("c20","sagitta 3mev",canvas_x,canvas_y);
   TCanvas *c21 = new TCanvas("c21","sagitta 5mev",canvas_x,canvas_y);
   TCanvas *c22 = new TCanvas("c22","sagitta 10mev",canvas_x,canvas_y);
   TCanvas *c23 = new TCanvas("c23","sagitta 15mev",canvas_x,canvas_y);
   TCanvas *c24 = new TCanvas("c24","sagitta cut comparison",canvas_x,canvas_y);

   TCanvas *c25 = new TCanvas("c25","stgc1 x vs y A-side",canvas_x,canvas_y);
   TCanvas *c26 = new TCanvas("c26","stgc2 x vs y A-side",canvas_x,canvas_y);
   TCanvas *c27 = new TCanvas("c27","mm1 x vs y A-side",canvas_x,canvas_y);
   TCanvas *c28 = new TCanvas("c28","mm2 x vs y A-side",canvas_x,canvas_y);
   TCanvas *c29 = new TCanvas("c29","stgc1 x vs y C-side",canvas_x,canvas_y);
   TCanvas *c30 = new TCanvas("c30","stgc2 x vs y C-side",canvas_x,canvas_y);
   TCanvas *c31 = new TCanvas("c31","mm1 x vs y C-side",canvas_x,canvas_y);
   TCanvas *c32 = new TCanvas("c32","mm2 x vs y C-side",canvas_x,canvas_y);

   TCanvas *c33 = new TCanvas("c33","stgc1 sagitta A-side",canvas_x,canvas_y);
   TCanvas *c34 = new TCanvas("c34","stgc2 sagitta A-side",canvas_x,canvas_y);
   TCanvas *c35 = new TCanvas("c35","mm1 sagitta A-side",canvas_x,canvas_y);
   TCanvas *c36 = new TCanvas("c36","mm2 sagitta A-side",canvas_x,canvas_y);

   TCanvas *c37 = new TCanvas("c37","stgc1 sagitta C-side",canvas_x,canvas_y);
   TCanvas *c38 = new TCanvas("c38","stgc2 sagitta C-side",canvas_x,canvas_y);
   TCanvas *c39 = new TCanvas("c39","mm1 sagitta C-side",canvas_x,canvas_y);
   TCanvas *c40 = new TCanvas("c40","mm2 sagitta C-side",canvas_x,canvas_y);

   

   c1->Divide(2,2);
   // c2->Divide(2,2);
   // c3->Divide(2,2);
   // c4->Divide(2,2);
   // c5->Divide(4,4);
   // c6->Divide(4,4);
   // c7->Divide(4,4);
   c8->Divide(2,2);
   // c9->Divide(2,2);
   // c10->Divide(2,2);
   // c11->Divide(2,2);
   // c12->Divide(4,4);
   // c13->Divide(4,4);
   // c14->Divide(4,4);
   // c15->Divide(2,2);
   // c16->Divide(2,2);
   // c17->Divide(2,2);
   // c18->Divide(2,2);
   c33->Divide(4,4);
   c34->Divide(4,4);
   c35->Divide(4,4);
   c36->Divide(4,4);
   c37->Divide(4,4);
   c38->Divide(4,4);
   c39->Divide(4,4);
   c40->Divide(4,4);
   gStyle->SetOptStat(0);


   c1->cd(1);
   seg1_xy_aside_hist->Draw("COLZ");
   seg1_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg1_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c1->cd(2);
   seg2_xy_aside_hist->Draw("COLZ");
   seg2_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg2_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c1->cd(3);
   seg3_xy_aside_hist->Draw("COLZ");
   seg3_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg3_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   // c2->cd(1);
   // seg1x_seg2x_aside_hist->Draw("COLZ");
   // seg1x_seg2x_aside_hist->GetXaxis()->SetTitle("seg1 x  (mm)");
   // seg1x_seg2x_aside_hist->GetYaxis()->SetTitle("seg2 x  (mm)");

   // c2->cd(2);
   // seg1x_seg3x_aside_hist->Draw("COLZ");
   // seg1x_seg3x_aside_hist->GetXaxis()->SetTitle("seg1 x  (mm)");
   // seg1x_seg3x_aside_hist->GetYaxis()->SetTitle("seg3 x  (mm)");

   // c2->cd(3);
   // seg2x_seg3x_aside_hist->Draw("COLZ");
   // seg2x_seg3x_aside_hist->GetXaxis()->SetTitle("seg2 x  (mm)");
   // seg2x_seg3x_aside_hist->GetYaxis()->SetTitle("seg3 x  (mm)");

   // c3->cd(1);
   // seg1y_seg2y_aside_hist->Draw("COLZ");
   // seg1y_seg2y_aside_hist->GetXaxis()->SetTitle("seg1 y  (mm)");
   // seg1y_seg2y_aside_hist->GetYaxis()->SetTitle("seg2 y  (mm)");

   // c3->cd(2);
   // seg1y_seg3y_aside_hist->Draw("COLZ");
   // seg1y_seg3y_aside_hist->GetXaxis()->SetTitle("seg1 y  (mm)");
   // seg1y_seg3y_aside_hist->GetYaxis()->SetTitle("seg3 y  (mm)");

   // c3->cd(3);
   // seg2y_seg3y_aside_hist->Draw("COLZ");
   // seg2y_seg3y_aside_hist->GetXaxis()->SetTitle("seg2 y  (mm)");
   // seg2y_seg3y_aside_hist->GetYaxis()->SetTitle("seg3 y  (mm)");

   // c4->cd(1);
   // seg1z_seg2z_aside_hist->Draw("COLZ");
   // seg1z_seg2z_aside_hist->GetXaxis()->SetTitle("seg1 z  (mm)");
   // seg1z_seg2z_aside_hist->GetYaxis()->SetTitle("seg2 z  (mm)");

   // c4->cd(2);
   // seg1z_seg3z_aside_hist->Draw("COLZ");
   // seg1z_seg3z_aside_hist->GetXaxis()->SetTitle("seg1 z  (mm)");
   // seg1z_seg3z_aside_hist->GetYaxis()->SetTitle("seg3 z  (mm)");

   // c4->cd(3);
   // seg2z_seg3z_aside_hist->Draw("COLZ");
   // seg2z_seg3z_aside_hist->GetXaxis()->SetTitle("seg2 z  (mm)");
   // seg2z_seg3z_aside_hist->GetYaxis()->SetTitle("seg3 z  (mm)");

   // for(int i = 0; i < 16; i++){
   //    c5->cd(i+1);
   //    seg1_nhits_hist_per_sector_aside_hists[i]->Draw("HIST");
   //    seg1_nhits_hist_per_sector_aside_hists[i]->GetXaxis()->SetTitle("nhits per segment");
   //    seg1_nhits_hist_per_sector_aside_hists[i]->GetYaxis()->SetTitle("counts");
   // }
   // for(int i = 0; i < 16; i++){
   //    c6->cd(i+1);
   //    seg2_nhits_hist_per_sector_aside_hists[i]->Draw("HIST");
   //    seg2_nhits_hist_per_sector_aside_hists[i]->GetXaxis()->SetTitle("nhits per segment");
   //    seg2_nhits_hist_per_sector_aside_hists[i]->GetYaxis()->SetTitle("counts");
   // }
   // for(int i = 0; i < 16; i++){
   //    c7->cd(i+1);
   //    seg3_nhits_hist_per_sector_aside_hists[i]->Draw("HIST");
   //    seg3_nhits_hist_per_sector_aside_hists[i]->GetXaxis()->SetTitle("nhits per segment");
   //    seg3_nhits_hist_per_sector_aside_hists[i]->GetYaxis()->SetTitle("counts");
   // }


   c8->cd(1);
   seg1_xy_cside_hist->Draw("COLZ");
   seg1_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg1_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   c8->cd(2);
   seg2_xy_cside_hist->Draw("COLZ");
   seg2_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg2_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   c8->cd(3);
   seg3_xy_cside_hist->Draw("COLZ");
   seg3_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   seg3_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   // c9->cd(1);
   // seg1x_seg2x_cside_hist->Draw("COLZ");
   // seg1x_seg2x_cside_hist->GetXaxis()->SetTitle("seg1 x (mm)");
   // seg1x_seg2x_cside_hist->GetYaxis()->SetTitle("seg2 x (mm)");

   // c9->cd(2);
   // seg1x_seg3x_cside_hist->Draw("COLZ");
   // seg1x_seg3x_cside_hist->GetXaxis()->SetTitle("seg1 x (mm)");
   // seg1x_seg3x_cside_hist->GetYaxis()->SetTitle("seg3 x (mm)");

   // c9->cd(3);
   // seg2x_seg3x_cside_hist->Draw("COLZ");
   // seg2x_seg3x_cside_hist->GetXaxis()->SetTitle("seg2 x (mm)");
   // seg2x_seg3x_cside_hist->GetYaxis()->SetTitle("seg3 x (mm)");

   // c10->cd(1);
   // seg1y_seg2y_cside_hist->Draw("COLZ");
   // seg1y_seg2y_cside_hist->GetXaxis()->SetTitle("seg1 y (mm)");
   // seg1y_seg2y_cside_hist->GetYaxis()->SetTitle("seg2 y (mm)");

   // c10->cd(2);
   // seg1y_seg3y_cside_hist->Draw("COLZ");
   // seg1y_seg3y_cside_hist->GetXaxis()->SetTitle("seg1 y (mm)");
   // seg1y_seg3y_cside_hist->GetYaxis()->SetTitle("seg3 y (mm)");

   // c10->cd(3);
   // seg2y_seg3y_cside_hist->Draw("COLZ");
   // seg2y_seg3y_cside_hist->GetXaxis()->SetTitle("seg2 y (mm)");
   // seg2y_seg3y_cside_hist->GetYaxis()->SetTitle("seg3 y (mm)");

   // c11->cd(1);
   // seg1z_seg2z_cside_hist->Draw("COLZ");
   // seg1z_seg2z_cside_hist->GetXaxis()->SetTitle("seg1 z (mm)");
   // seg1z_seg2z_cside_hist->GetYaxis()->SetTitle("seg2 z (mm)");

   // c11->cd(2);
   // seg1z_seg3z_cside_hist->Draw("COLZ");
   // seg1z_seg3z_cside_hist->GetXaxis()->SetTitle("seg1 z (mm)");
   // seg1z_seg3z_cside_hist->GetYaxis()->SetTitle("seg3 z (mm)");

   // c11->cd(3);
   // seg2z_seg3z_cside_hist->Draw("COLZ");
   // seg2z_seg3z_cside_hist->GetXaxis()->SetTitle("seg2 z (mm)");
   // seg2z_seg3z_cside_hist->GetYaxis()->SetTitle("seg3 z (mm)");

   // for(int i = 0; i < 16; i++){
   //    c12->cd(i+1);
   //    seg1_nhits_hist_per_sector_cside_hists[i]->Draw("HIST");
   //    seg1_nhits_hist_per_sector_cside_hists[i]->GetXaxis()->SetTitle("nhits per segment");
   //    seg1_nhits_hist_per_sector_cside_hists[i]->GetYaxis()->SetTitle("counts");
   // }
   // for(int i = 0; i < 16; i++){
   //    c13->cd(i+1);
   //    seg2_nhits_hist_per_sector_cside_hists[i]->Draw("HIST");
   //    seg2_nhits_hist_per_sector_cside_hists[i]->GetXaxis()->SetTitle("number of hits");
   //    seg2_nhits_hist_per_sector_cside_hists[i]->GetYaxis()->SetTitle("counts");
   // }
   // for(int i = 0; i < 16; i++){
   //    c14->cd(i+1);
   //    seg3_nhits_hist_per_sector_cside_hists[i]->Draw("HIST");
   //    seg3_nhits_hist_per_sector_cside_hists[i]->GetXaxis()->SetTitle("number of hits");
   //    seg3_nhits_hist_per_sector_cside_hists[i]->GetYaxis()->SetTitle("counts");
   // }



   // c15->cd(1);
   // seg1_eta_hist->Draw("COLZ");
   // seg1_eta_hist->GetXaxis()->SetTitle("seg1 eta");
   // seg1_eta_hist->GetYaxis()->SetTitle("muon eta");

   // c15->cd(2);
   // seg2_eta_hist->Draw("COLZ");
   // seg2_eta_hist->GetXaxis()->SetTitle("seg2 eta");
   // seg2_eta_hist->GetYaxis()->SetTitle("muon eta");

   // c15->cd(3);
   // seg3_eta_hist->Draw("COLZ");
   // seg3_eta_hist->GetXaxis()->SetTitle("seg3 eta");
   // seg3_eta_hist->GetYaxis()->SetTitle("muon eta");

   // c16->cd(1);
   // seg1_phi_hist->Draw("COLZ");
   // seg1_phi_hist->GetXaxis()->SetTitle("seg1 phi");
   // seg1_phi_hist->GetYaxis()->SetTitle("muon phi");

   // c16->cd(2);
   // seg2_phi_hist->Draw("COLZ");
   // seg2_phi_hist->GetXaxis()->SetTitle("seg2 phi");
   // seg2_phi_hist->GetYaxis()->SetTitle("muon phi");

   // c16->cd(3);
   // seg3_phi_hist->Draw("COLZ");
   // seg3_phi_hist->GetXaxis()->SetTitle("seg3 phi");
   // seg3_phi_hist->GetYaxis()->SetTitle("muon phi");

   // c17->cd(1);
   // seg1_seg2_eta_hist->Draw("COLZ");
   // seg1_seg2_eta_hist->GetXaxis()->SetTitle("seg1 eta");
   // seg1_seg2_eta_hist->GetYaxis()->SetTitle("seg2 eta");

   // c17->cd(2);
   // seg1_seg3_eta_hist->Draw("COLZ");
   // seg1_seg3_eta_hist->GetXaxis()->SetTitle("seg1 eta");
   // seg1_seg3_eta_hist->GetYaxis()->SetTitle("seg3 eta");

   // c17->cd(3);
   // seg2_seg3_eta_hist->Draw("COLZ");
   // seg2_seg3_eta_hist->GetXaxis()->SetTitle("seg2 eta");
   // seg2_seg3_eta_hist->GetYaxis()->SetTitle("seg3 eta");

   // c18->cd(1);
   // seg1_seg2_phi_hist->Draw("COLZ");
   // seg1_seg2_phi_hist->GetXaxis()->SetTitle("seg1 phi");
   // seg1_seg2_phi_hist->GetYaxis()->SetTitle("seg2 phi");

   // c18->cd(2);
   // seg1_seg3_phi_hist->Draw("COLZ");
   // seg1_seg3_phi_hist->GetXaxis()->SetTitle("seg1 phi");
   // seg1_seg3_phi_hist->GetYaxis()->SetTitle("seg3 phi");

   // c18->cd(3);
   // seg2_seg3_phi_hist->Draw("COLZ");
   // seg2_seg3_phi_hist->GetXaxis()->SetTitle("seg2 phi");
   // seg2_seg3_phi_hist->GetYaxis()->SetTitle("seg3 phi");


   c19->cd();
   sagitta_0pt_hist->Draw("HIST");
   sagitta_0pt_hist->GetXaxis()->SetTitle("sagitta (mm)");

   c20->cd();
   sagitta_3pt_hist->Draw("HIST");
   sagitta_3pt_hist->GetXaxis()->SetTitle("Sagitta (mm)");

   c21->cd();
   sagitta_5pt_hist->Draw("HIST");
   sagitta_5pt_hist->GetXaxis()->SetTitle("Sagitta (mm)");

   c22->cd();
   sagitta_10pt_hist->Draw("HIST");
   sagitta_10pt_hist->GetXaxis()->SetTitle("Sagitta (mm)");

   c23->cd();
   sagitta_15pt_hist->Draw("HIST");
   sagitta_15pt_hist->GetXaxis()->SetTitle("Sagitta (mm)");
   sagitta_15pt_hist->Fit(f1);
   f1->Draw("SAME");

   c24->cd();
   TH1F *sag0_clone = (TH1F*)sagitta_0pt_hist->Clone("sag0_clone");
   TH1F *sag5_clone = (TH1F*)sagitta_5pt_hist->Clone("sag5_clone");
   TH1F *sag10_clone = (TH1F*)sagitta_10pt_hist->Clone("sag10_clone");
   TH1F *sag15_clone = (TH1F*)sagitta_15pt_hist->Clone("sag15_clone");

   sag0_clone->SetLineColor(kBlack);
   sag5_clone->SetLineColor(kBlue);
   sag10_clone->SetLineColor(kGreen);
   sag15_clone->SetLineColor(kRed);

   // Normalising hists
   sag0_clone->Scale(1/sag0_clone->Integral());
   sag5_clone->Scale(1/sag5_clone->Integral());
   sag10_clone->Scale(1/sag10_clone->Integral());
   sag15_clone->Scale(1/sag15_clone->Integral());

   sag10_clone->SetTitle("Sagitta Cut Comparison");   
   sag10_clone->GetXaxis()->SetTitle("Sagitta (mm)");
   sag10_clone->SetMaximum(sag10_clone->GetMaximum()*1.2);

   sag15_clone->Draw("HIST");
   sag0_clone->Draw("HIST SAME");
   sag5_clone->Draw("HIST SAME");
   sag10_clone->Draw("HIST SAME");


   auto legend = new TLegend(0.65,0.7,0.85,0.85);
   legend->AddEntry(sag0_clone,"Sagitta: no muon pT cut");
   legend->AddEntry(sag5_clone,"Sagitta: muon pT > 5 GeV");
   legend->AddEntry(sag10_clone,"Sagitta: muon pT > 10 GeV");
   legend->AddEntry(sag15_clone,"Sagitta: muon pT > 15 GeV");

   legend->Draw();


   c25->cd();
   stgc1_xy_aside_hist->Draw("COLZ");
   stgc1_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   stgc1_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c26->cd();
   stgc2_xy_aside_hist->Draw("COLZ");
   stgc2_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   stgc2_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c27->cd();
   mm1_xy_aside_hist->Draw("COLZ");
   mm1_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   mm1_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c28->cd();
   mm2_xy_aside_hist->Draw("COLZ");
   mm2_xy_aside_hist->GetXaxis()->SetTitle("x  (mm)");
   mm2_xy_aside_hist->GetYaxis()->SetTitle("y  (mm)");

   c29->cd();
   stgc1_xy_cside_hist->Draw("COLZ");
   stgc1_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   stgc1_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   c30->cd();
   stgc2_xy_cside_hist->Draw("COLZ");
   stgc2_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   stgc2_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   c31->cd();
   mm1_xy_cside_hist->Draw("COLZ");
   mm1_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   mm1_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   c32->cd();
   mm2_xy_cside_hist->Draw("COLZ");
   mm2_xy_cside_hist->GetXaxis()->SetTitle("x  (mm)");
   mm2_xy_cside_hist->GetYaxis()->SetTitle("y  (mm)");

   for(int i = 0; i < 16; i++){
      c33->cd(i+1);
      stgc1_sagitta_per_sector_aside_hists[i]->Draw("HIST");
      stgc1_sagitta_per_sector_aside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      stgc1_sagitta_per_sector_aside_hists[i]->GetYaxis()->SetTitle("Counts");
      stgc1_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c34->cd(i+1);
      stgc2_sagitta_per_sector_aside_hists[i]->Draw("HIST");
      stgc2_sagitta_per_sector_aside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      stgc2_sagitta_per_sector_aside_hists[i]->GetYaxis()->SetTitle("Counts");
      stgc2_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c35->cd(i+1);
      mm1_sagitta_per_sector_aside_hists[i]->Draw("HIST");
      mm1_sagitta_per_sector_aside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      mm1_sagitta_per_sector_aside_hists[i]->GetYaxis()->SetTitle("Counts");
      mm1_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c36->cd(i+1);
      mm2_sagitta_per_sector_aside_hists[i]->Draw("HIST");
      mm2_sagitta_per_sector_aside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      mm2_sagitta_per_sector_aside_hists[i]->GetYaxis()->SetTitle("Counts");
      mm2_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c37->cd(i+1);
      stgc1_sagitta_per_sector_cside_hists[i]->Draw("HIST");
      stgc1_sagitta_per_sector_cside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      stgc1_sagitta_per_sector_cside_hists[i]->GetYaxis()->SetTitle("Counts");
      stgc1_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c38->cd(i+1);
      stgc2_sagitta_per_sector_cside_hists[i]->Draw("HIST");
      stgc2_sagitta_per_sector_cside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      stgc2_sagitta_per_sector_cside_hists[i]->GetYaxis()->SetTitle("Counts");
      stgc2_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c39->cd(i+1);
      mm1_sagitta_per_sector_cside_hists[i]->Draw("HIST");
      mm1_sagitta_per_sector_cside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      mm1_sagitta_per_sector_cside_hists[i]->GetYaxis()->SetTitle("Counts");
      mm1_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }
   for(int i = 0; i < 16; i++){
      c40->cd(i+1);
      mm2_sagitta_per_sector_cside_hists[i]->Draw("HIST");
      mm2_sagitta_per_sector_cside_hists[i]->GetXaxis()->SetTitle("Sagitta (mm)");
      mm2_sagitta_per_sector_cside_hists[i]->GetYaxis()->SetTitle("Counts");
      mm2_sagitta_per_sector_aside_hists[i]->SetMaximum(2500);
   }

}
