#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 32
#SBATCH -t 00:5:00
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
module load mpich/ge/gcc/64

# Build the executable (if you haven't already)
make clean
make main.out

echo "nranks=4"
mpiexec -n 4   ./main.out  

# The script will exit whether we give the "exit" command or not.
exit
