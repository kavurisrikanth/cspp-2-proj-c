Plagiarism detector project for CSPP-2.

16-September-2017.

By Srikanth Kavuri, 20176001.

This is basically a redo of the CSPP-1 project that was done in Python.
The functionality is essentially the same, save for a few differences. The differences are enumerated here.
For a description of the functionality, check the README for the CSPP-1 project.

The main differences are:
1. Execution: In this project, the directory containing the files to be examined must be provided as a command line argument.
2. Log file: Unlike the Python project, this project does not create a new log file for every execution. Rather, it uses only one file.
3. Hashing: Since there are no hash data structures in C, a hash function is written manually. It is the same hash function as the one used for fingerprinting in the Python project.


The main function is contained in the file testing.c
To test, use the command ./<binary_name> <file_name>