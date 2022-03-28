#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 128
#SBATCH -t 00:05:00
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o slurm-timing.out

# Go to the directory where the job was submitted
cd $SLURM_SUBMIT_DIR

echo "Core distribution on nodes:"
echo $SLURM_TASKS_PER_NODE

# Unload all except default modules
module reset

# Load the modules you need
module load gcc

# Build the executable (if you haven't already)
make main.out

# Make sure OMP knows how many threads are available
export OMP_NUM_THREADS=$SLURM_NTASKS
# Prevent OMP from performing optimizations that would make results harder to predict
export OMP_PROC_BIND=true
export OMP_DYNAMIC=false

############################################
# PUT YOUR COMMANDS HERE TO RUN YOUR TESTS #
############################################

# The script will exit whether we give the "exit" command or not.
exit

