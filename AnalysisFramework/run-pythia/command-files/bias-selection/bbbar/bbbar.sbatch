#!/bin/bash

#SBATCH --job-name=simul-bb-8     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=bbbar-out/bb-8.out     # file to collect standard output
#SBATCH --error=bbbar-out/bb-8.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp044

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/bias-selection/bbbar/bb-8.cmnd -outroot bb-8
