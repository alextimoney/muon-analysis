#!/bin/bash

#SBATCH --job-name=simul-cc-1     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=ccbar-out/cc-1.out     # file to collect standard output
#SBATCH --error=ccbar-out/cc-1.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp044

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/bias-selection/ccbar/cc-1.cmnd -outroot cc-1