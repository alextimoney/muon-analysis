#!/bin/bash

#SBATCH --job-name=cc200-2     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=outfiles/ccbar/cc200-2.out     # file to collect standard output
#SBATCH --error=outfiles/ccbar/cc200-2.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp045

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/pTmin/cc-ptmin.cmnd -outroot cc200-2
