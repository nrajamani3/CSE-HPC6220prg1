# CSE-HPC6220prg1
This repository contains .cpp codes for the Sequential polynomial algorithm (evaluator.cpp), the broadcast (broadcast.cpp), scatter(scatter.cpp) the paralell prefix function (parprefix.cpp). Ran successfully with 4 processors locally. TODO: Create PBS script, and combine all the functions into the poly evaluator. Perform analysis. 
Compile as mpicxx -o output-file-name input-file-name.cpp
Run as mpirun -np $p ./output-file-name
