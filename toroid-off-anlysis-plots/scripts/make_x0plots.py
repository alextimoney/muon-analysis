#!/usr/bin/env python
# -*- coding: utf-8 -*-

import faulthandler
faulthandler.enable()

import pandas as pd
import argparse
import numpy as np

import ROOT
import matplotlib.pyplot as plt
import matplotlib.ticker as tck

plt.rcParams.update({'font.size': 22, "legend.frameon":False, "ytick.minor.size": 4.0, "ytick.major.size": 10, "xtick.minor.size": 4.0, "xtick.major.size": 10, "ytick.right":True, "xtick.top":True, "ytick.direction": "in", "xtick.direction": "in"})


def create_plot_m_vs_p(df, name):
    fig, ax = plt.subplots(figsize=(20,10)) 
    df.plot("p","m", ax=ax, label="HWFM[mm]",  xticks=df["p"])

    ax2 = df.plot("p","sigma_x0", ax=ax, secondary_y = True, label="$\sigma$ x0[mm]", xticks=df["p"])

    ax_x2 = ax.twiny()
    ax_x2.set_xlim(ax.get_xlim())
    ax_x2.set_xticks(df["p"])
    ax_x2.set_xticklabels(df["Nentries"])
    ax_x2.set_xlabel("N tracks")

    ax.set_xlabel("Momentum[GeV]")
    ax.set_ylabel("HWHM[mm]")
    ax2.set_ylabel("$\sigma$ sagitta[mm]")

    plt.savefig("{name}.pdf".format(name=name))
    plt.clf()
    plt.close()


def create_plot_x_vs_p(df, name):
    fig, ax = plt.subplots(figsize=(20,10)) 
    df.plot("p","x0", ax=ax, label="x0[mm]",  xticks=df["p"])
    ax.set_xlabel("Momentum[GeV]", fontname="Helvetica")
    ax.set_ylabel("sagitta[mm]", fontname="Helvetica")
    ax.set_ylim(-1,1)

    plt.savefig("{name}.pdf".format(name=name))
    plt.clf()
    plt.close()


def add_atlas_label(x=1.,y=0.4):
    plt.text(x, y, "ATLAS,")
    plt.text(x + 1.15, y, "internal", fontstyle="italic")
    

if __name__ == "__main__":
 segments = ["","mm1_","mm2_","stgc1_","stgc2_","mm1_t1_","mm2_t1_","stgc1_t1_","stgc2_t1_","mm1_t2_","mm2_t2_","stgc1_t2_","stgc2_t2_","stgc1_t3_","stgc2_t3_"]
 for seg in segments:
    path_to_csv = "csv/"
    # path_to_csv = "csv/22_data"

    sag_df_a_list = []
    sag_df_c_list = []
    momentums=[0,5,10,15,20,25,30,35,40,45,50]
    sectors = np.arange(1, 17)

    x0_per_sector_a_0 = []
    x0_per_sector_a_10 = []
    x0_per_sector_a_20 = []
    x0_per_sector_a_30 = []
    x0_per_sector_a_40 = []
    x0_per_sector_a_50 = []
    x0_per_sector_c_0 = []
    x0_per_sector_c_10 = []
    x0_per_sector_c_20 = []
    x0_per_sector_c_30 = []
    x0_per_sector_c_40 = []
    x0_per_sector_c_50 = []

    x0_error_sector_a_0 = []
    x0_error_sector_a_10 = []
    x0_error_sector_a_20 = []
    x0_error_sector_a_30 = []
    x0_error_sector_a_40 = []
    x0_error_sector_a_50 = []
    x0_error_sector_c_0 = []
    x0_error_sector_c_10 = []
    x0_error_sector_c_20 = []
    x0_error_sector_c_30 = []
    x0_error_sector_c_40 = []
    x0_error_sector_c_50 = []
    
    

    for i in range(16):
        #sagittas_t223_a_improved_sector1_improved_hist
        filename_a = "sagittas_a_sector_{sector}_{segl}hist.csv".format(sector=i+1,segl=seg)
        filename_c = "sagittas_c_sector_{sector}_{segl}hist.csv".format(sector=i+1,segl=seg)



        # Fill data frames and lists needed to construct plots

        sag_df_a = pd.read_csv(path_to_csv+filename_a,sep=";", usecols=[0,1,2,3,4] )
        sag_df_a["p"] = momentums
        sag_df_a_list.append(sag_df_a)
        x0_per_sector_a_0.append(sag_df_a["x0"].iloc[0])
        x0_per_sector_a_10.append(sag_df_a["x0"].iloc[2])
        x0_per_sector_a_20.append(sag_df_a["x0"].iloc[4])
        x0_per_sector_a_30.append(sag_df_a["x0"].iloc[6])
        x0_per_sector_a_40.append(sag_df_a["x0"].iloc[8])
        x0_per_sector_a_50.append(sag_df_a["x0"].iloc[10])

        x0_error_sector_a_0.append(sag_df_a["sigma_x0"].iloc[0])
        x0_error_sector_a_10.append(sag_df_a["sigma_x0"].iloc[2])
        x0_error_sector_a_20.append(sag_df_a["sigma_x0"].iloc[4])
        x0_error_sector_a_30.append(sag_df_a["sigma_x0"].iloc[6])
        x0_error_sector_a_40.append(sag_df_a["sigma_x0"].iloc[8])
        x0_error_sector_a_50.append(sag_df_a["sigma_x0"].iloc[10])




        sag_df_c = pd.read_csv(path_to_csv+filename_c,sep=";", usecols=[0,1,2,3,4] )
        sag_df_c["p"] = momentums
        sag_df_c_list.append(sag_df_c)
        x0_per_sector_c_0.append(sag_df_c["x0"].iloc[0])
        x0_per_sector_c_10.append(sag_df_c["x0"].iloc[2])
        x0_per_sector_c_20.append(sag_df_c["x0"].iloc[4])
        x0_per_sector_c_30.append(sag_df_c["x0"].iloc[6])
        x0_per_sector_c_40.append(sag_df_c["x0"].iloc[8])
        x0_per_sector_c_50.append(sag_df_c["x0"].iloc[10])

        x0_error_sector_c_0.append(sag_df_c["sigma_x0"].iloc[0])
        x0_error_sector_c_10.append(sag_df_c["sigma_x0"].iloc[2])
        x0_error_sector_c_20.append(sag_df_c["sigma_x0"].iloc[4])
        x0_error_sector_c_30.append(sag_df_c["sigma_x0"].iloc[6])
        x0_error_sector_c_40.append(sag_df_c["sigma_x0"].iloc[8])
        x0_error_sector_c_50.append(sag_df_c["sigma_x0"].iloc[10])





        # Some plots

        create_plot_m_vs_p(sag_df_a, "Plots/m_vs_p_sector_{sector}_{segl}a".format(sector=i+1,segl=seg))
        create_plot_x_vs_p(sag_df_a, "Plots/x_vs_p_sector_{sector}_{segl}a".format(sector=i+1,segl=seg))
        create_plot_m_vs_p(sag_df_c, "Plots/m_vs_p_sector_{sector}_{segl}c".format(sector=i+1,segl=seg))
        create_plot_x_vs_p(sag_df_c, "Plots/x_vs_p_sector_{sector}_{segl}c".format(sector=i+1,segl=seg))
    


    # Make x0 per sector plots 

    fig, ax = plt.subplots(figsize=(20,10))
    plt.axhline(y=0., linestyle='-',  color="black")
    #plt.scatter(sectors, x0_per_sector_a_30, c="blue", label="x0 side A, p > 30GeV", edgecolors='none')
    plt.errorbar(sectors, x0_per_sector_a_30, yerr=x0_error_sector_a_30, fmt="o", label="x0 side A, p > 30GeV", color="blue")
    ax.set_xticks(sectors)
    ax.yaxis.set_minor_locator(tck.AutoMinorLocator()) 
    ax.set_ylim(-0.4,0.4)
    ax.set_xlabel("sector", fontname="Helvetica")
    ax.set_ylabel("sagitta [mm]", fontname="Helvetica")
    #add_atlas_label()

    plt.savefig("{name}_{segl}.pdf".format(name="Plots/x0_per_sector_aside",segl=seg))
    plt.clf()
    plt.close()

    fig, ax = plt.subplots(figsize=(20,10))
    plt.axhline(y=0., linestyle='-',  color="black")
    #plt.scatter(sectors, x0_per_sector_c_30, c="red", label="x0 side C, p > 30GeV", edgecolors='none')
    plt.errorbar(sectors, x0_per_sector_c_30, yerr=x0_error_sector_c_30, fmt="o", label="x0 side C, p > 30GeV", color="red")
    ax.set_ylim(-0.4,0.4)
    ax.yaxis.set_minor_locator(tck.AutoMinorLocator()) 
    ax.set_xlabel("sector", fontname="Helvetica")
    ax.set_ylabel("sagitta[mm]", fontname="Helvetica")
    ax.set_xticks(sectors)
    #add_atlas_label()

    plt.savefig("{name}_{segl}.pdf".format(name="Plots/x0_per_sector_cside",segl=seg))
    plt.clf()
    plt.close()

    fig, ax = plt.subplots(figsize=(20,10))
    plt.axhline(y=0., linestyle='-',  color="black")
    ax.axhspan(-0.1, 0.1, color="#fee08b")

    #plt.scatter(sectors, x0_per_sector_a_30, c="blue", label="x0 side A, p > 30GeV", edgecolors='none')
    #plt.scatter(sectors, x0_per_sector_c_30, c="red", label="x0 side C, p > 30GeV", edgecolors='none')
    plt.errorbar(sectors-0.075, x0_per_sector_a_30, yerr=x0_error_sector_a_30, fmt="o", label="x0 side A, p > 30GeV", color="blue")
    plt.errorbar(sectors+0.075, x0_per_sector_c_30, yerr=x0_error_sector_c_30, fmt="o", label="x0 side C, p > 30GeV", color="red")
    ax.set_ylim(-0.4,0.4)
    ax.set_xlabel("sector", fontname="Helvetica")
    ax.set_ylabel("sagitta[mm]", fontname="Helvetica")
    ax.set_xticks(sectors)
    ax.yaxis.set_minor_locator(tck.AutoMinorLocator()) 
    plt.legend()
    #add_atlas_label()
    #plt.text(1, 0.35, "run-3, 13.6 TeV, toroid-off run") # i want to mention that it is run-3 without mentioning it is atlas
    plt.savefig("{name}_{segl}.pdf".format(name="Plots/x0_per_sector",segl=seg))
    plt.clf()
    plt.close()


    # A-side, with scatter plot pre every second momentum cut
    fig, ax = plt.subplots(figsize=(20,10))
    plt.axhline(y=0., linestyle='-',  color="black")
    plt.errorbar(sectors-0.15, x0_per_sector_a_0, yerr=x0_error_sector_a_0, label="x0 side A, no cut",fmt="o", color="black")
    plt.errorbar(sectors-0.075, x0_per_sector_a_20, yerr=x0_error_sector_a_20, label="x0 side A, p > 20", fmt="o", color="blue")
    plt.errorbar(sectors, x0_per_sector_a_30, yerr=x0_error_sector_a_30, label="x0 side A, p > 30", fmt="o",  color="green")
    plt.errorbar(sectors+0.075, x0_per_sector_a_40, yerr=x0_error_sector_a_40, label="x0 side A, p > 40", fmt="o",  color="orange")
    plt.errorbar(sectors+0.15, x0_per_sector_a_50, yerr=x0_error_sector_a_50, label="x0 side A, p > 50", fmt="o",  color="red")
    ax.set_ylim(-0.4,0.4)
    ax.set_xlabel("sector", fontname="Helvetica")
    ax.set_ylabel("sagitta[mm]", fontname="Helvetica")
    ax.set_xticks(sectors)
    ax.yaxis.set_minor_locator(tck.AutoMinorLocator()) 
    plt.legend()
    #add_atlas_label()
    plt.savefig("{name}_{segl}.pdf".format(name="Plots/x0_per_sector_aside_p_cuts",segl=seg))
    plt.clf()
    plt.close()

    fig, ax = plt.subplots(figsize=(20,10))
    plt.axhline(y=0., linestyle='-',  color="black")
    plt.errorbar(sectors-0.15, x0_per_sector_c_0, yerr=x0_error_sector_c_0, label="x0 side C, no cut",fmt="o", color="black")
    plt.errorbar(sectors-0.075, x0_per_sector_c_20, yerr=x0_error_sector_c_20, label="x0 side C, p > 20", fmt="o", color="blue")
    plt.errorbar(sectors, x0_per_sector_c_30, yerr=x0_error_sector_c_30, label="x0 side C, p > 30", fmt="o", color="green")
    plt.errorbar(sectors+0.075, x0_per_sector_c_40, yerr=x0_error_sector_c_40, label="x0 side C, p > 40", fmt="o", color="orange")
    plt.errorbar(sectors+0.15, x0_per_sector_c_50, yerr=x0_error_sector_c_50, label="x0 side C, p > 50", fmt="o", color="red")
    ax.set_ylim(-0.4,0.4)
    ax.set_xlabel("sector", fontname="Helvetica")
    ax.set_ylabel("sagitta[mm]", fontname="Helvetica")
    ax.set_xticks(sectors)
    ax.yaxis.set_minor_locator(tck.AutoMinorLocator()) 
    plt.legend()
    #add_atlas_label()
    plt.savefig("{name}_{segl}.pdf".format(name="Plots/x0_per_sector_cside_p_cuts",segl=seg))
    plt.clf()
    plt.close()



        
