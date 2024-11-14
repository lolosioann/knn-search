# Serial k-NN

## Summary
This project implements a version of the k-Nearest Neighbors (k-NN) algorithm in C, along with a Matlab interface, in order to read data from .mat files and write the output to them. This repo contains a serial implementation of the algorithm in the main branch, as well as different approximate parallel implementations, each in its own branch. The parallelization aims to improve the performance and efficiency of the k-NN algorithm, making it suitable for large datasets.

## Requirements
- Any Linux installation
- Matlab v.R2024b
- OpenBLAS

## Instructions
### Building the Project
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/parallel-knn.git
    or
    git clone git@github.com:lolosioann/parallel-knn.git
    ```

2. Run Make to build the project:
    ```sh
    make

    # depending on your Matlab installation you might need to change some paths in the Makefile. Open the Makefile and replace the suggested lines with the Path to your own Matlab installation.
    ```

### Running the Program
After building the project, you have to link the dynamic libraries and then you can run the executable:
```sh
export LD_LIBRARY_PATH=/usr/local/MATLAB/R2024b/bin/glnxa64:$LD_LIBRARY_PATH

./build/parallel_knn <corpus_file> <query_file> <k> 
```

### Program Description
The program reads the corpus and query matrices from a corresponding .mat file. For this you will need to provide a .mat file containing the two matrices. You will also need to specify the names of the matrix variables inside the file (e.g. if C = [1 2 3 ...] you will also need to input C to the program). The results will be output to a .mat file, the name of which you will need to specify, under the variable names idx, dst.