#!/bin/bash

#SBATCH --job-name=bot120-2     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=outfiles/bottom/bot120-2.out     # file to collect standard output
#SBATCH --error=outfiles/bottom/bot120-2.err      # file to collect standard errors
#SBATCH --nodelist=p1cmp045

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/pTmin/bottom-ptmin.cmnd -outroot bot120-2
