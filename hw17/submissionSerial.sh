#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 16
#SBATCH -t 00:02:00
#SBATCH -p p100_dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o serialMandelbrotRun.out
#SBATCH --gres=gpu:1

# Go to the directory where the job was submitted
cd $SLURM_SUBMIT_DIR

echo "Core distribution on nodes:"
echo $SLURM_TASKS_PER_NODE

# Unload all except default modules
module reset

# Load the modules you need
module load gcc
module load libpng/1.6.37-GCCcore-8.3.0
# Build the executable (if you haven't already)
make clean
make serial

./serialMandelbrot

# The script will exit whether we give the "exit" command or not.
exit

