## Fix Pairing

Fix pairs of fastq files.

# Compile

Run

`./build`

or

`g++ -std=c++11 fixpairing.cpp -o fixpairing`

# Run

To check your files to see if they are correctly paired:

`fixpairing <left> <right>`

To fix the pairing

`fixpairing <left> <right> <fixed_right>`

# Known Issues

If there are reads in the left file that are not in the right then the output
won't be correctly paired. A warning will be given.
