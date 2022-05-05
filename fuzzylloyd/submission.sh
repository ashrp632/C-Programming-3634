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
module load mpich/ge/gcc/64

# Build the executable (if you haven't already)
make clean
make 

echo "nranks=1"
mpiexec -n 1   ./main.out 5000 20 0
echo "nranks=2"
mpiexec -n 2   ./main.out 5000 20 0
echo "nranks=4"
mpiexec -n 4   ./main.out 5000 20 0
echo "nranks=8"
mpiexec -n 8   ./main.out 5000 20 0
echo "nranks=16"
mpiexec -n 16  ./main.out 5000 20 0
echo "nranks=32"
mpiexec -n 32  ./main.out 5000 20 0
echo "nranks=64"
mpiexec -n 64  ./main.out 5000 20 0
echo "nranks=128"
mpiexec -n 128 ./main.out 5000 20 0

# The script will exit whether we give the "exit" command or not.
exit
