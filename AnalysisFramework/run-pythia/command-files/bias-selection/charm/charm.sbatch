#!/bin/bash

#SBATCH --job-name=simul-charm-4     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=charm-out/charm-4.out     # file to collect standard output
#SBATCH --error=charm-out/charm-4.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp044,p1cmp045,p1cmp028,p1cmp043

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/bias-selection/charm/ch-4.cmnd -outroot charm-4