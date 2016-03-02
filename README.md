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

The last two characters of the header of the fastq entry are removed to be able
to match the entry from the left and right reads. If there are more characters
that need to be removed then the headers won't be matched and the output file
will be empty.

If there are reads in the left file that are not in the right then the output
won't be correctly paired. A warning will be given.
