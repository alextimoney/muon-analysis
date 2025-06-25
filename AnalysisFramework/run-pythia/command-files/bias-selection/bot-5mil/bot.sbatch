#!/bin/bash

#SBATCH --job-name=simul-bot-10     # job name, "OMP_run"
#SBATCH -t 3-0:00              # time limit: (D-HH:MM) 
#SBATCH --output=bot-out/bot-10.out     # file to collect standard output
#SBATCH --error=bot-out/bot-10.err      # file to collect standard errors

source /cvmfs/sft.cern.ch/lcg/releases/LCG_98python3/ROOT/v6.22.00/x86_64-centos7-gcc8-opt/ROOT-env.sh

./MyPythia8Simul command-files/bias-selection/bot-5mil/bot-10.cmnd -outroot bot-10