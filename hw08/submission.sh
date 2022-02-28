#!/bin/bash
#SBATCH -n 1
#SBATCH -t 00:00:30
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh

# Submit this file as a job request with
# sbatch submission.sh

# Change to the directory from which the job was submitted
cd $SLURM_SUBMIT_DIR

# Unload all except default modules
module reset

# Load the modules you need
module load gcc

# Compile (this may not be necessary if the program is already built)
gcc -o pi.out pi.c -lm

# Find out the number of threads from SLURM
export OMP_NUM_THREADS=$SLURM_NTASKS

# Print the number of threads for future reference
echo "Monte Carlo pi estimate with $OMP_NUM_THREADS threads"

# Run the program. Don't forget arguments!
./pi.out 6000

# The script will exit whether we give the "exit" command or not.
exit

