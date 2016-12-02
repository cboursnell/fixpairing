#include "fixpairing.h"

int FixPairing::load_right(char* infile) {
  cout << "loading right..." << infile << endl;
  std::ifstream right(infile);
  string header;
  string seq;
  string quals;
  size_t found1;
  while (getline(right, header)) {
    getline(right, seq);
    getline(right, quals);
    getline(right, quals);

    entry e;
    found1 = header.find_first_of(" /");
    header = header.substr(0, found1);
    e.seq = seq;
    e.quals = quals;
    store[header] = e;
  }
  cout << "done..." << endl;
}

int FixPairing::scan_left(char* leftin, char* leftout, char* rightout) {
  cout << "scanning left..."<< leftin << endl;
  std::ifstream left(leftin);
  string header;
  string seq;
  string quals;
  size_t found1;

  std::ofstream output;
  output.open (leftout);
  std::ofstream output2;
  output2.open (rightout);

  while (getline(left, header)) {
    getline(left, seq);
    getline(left, quals);
    getline(left, quals);
    // store fastq entry

    found1 = header.find_first_of(" /");
    header = header.substr(0, found1);

    entry l = store[header];
    if (l.seq.length()>1) {
      output << header << "/1" << endl;
      output << seq << endl;
      output << "+" << endl;
      output << quals << endl;
      output2 << header << "/2" << endl;
      output2 << l.seq << endl;
      output2 << "+" << endl;
      output2 << l.quals << endl;
    } else {
      // cout << "can't find " << header << endl;
    }
  }
  cout << "done..." << endl;
  output.close();
  output2.close();
}

int FixPairing::check(char* leftfile, char* rightfile) {
  cout << "checking left and right" << endl;
  std::ifstream left(leftfile);
  std::ifstream right(rightfile);
  string left_header;
  string left_seq;
  string left_quals;
  string right_header;
  string right_seq;
  string right_quals;
  size_t found1;
  size_t found2;
  long line = 1;

  while (getline(left, left_header)) {
    getline(left, left_seq);
    getline(left, left_quals);
    getline(left, left_quals);

    getline(right, right_header);
    getline(right, right_seq);
    getline(right, right_quals);
    getline(right, right_quals);

    found1 = left_header.find_first_of(" /");
    found2 = right_header.find_first_of(" /");
    left_header = left_header.substr(0, found1);
    right_header = right_header.substr(0, found2);
    if (left_header.compare(right_header) != 0) {
      cout << "headers mismatched at line " << line << endl;
      break;
    }
    line += 4;
  }

}

// int FixPairing::fix(char* leftfile, char* rightfile, char* outfile) {
//   // read lines from left and right.
//   // store the header names in order for the leftfile
//   // store the whole reads info for the rightfile
//   // if there are no mismatches then no output is produced
//   // when a mismatch is found the right reads are written out in order
//   // then check if the header from the left has been seen yet on the right
//   //   if so write out to output
//   //   if not store the right read


//   std::ifstream left(leftfile);
//   std::ifstream right(rightfile);
//   string left_header;
//   string left_seq;
//   string left_quals;
//   string right_header;
//   string right_seq;
//   string right_quals;

//   while (getline(left, left_header)) {
//     getline(left, left_seq);
//     getline(left, left_quals);
//     getline(left, left_quals);

//     getline(right, right_header);
//     getline(right, right_seq);
//     getline(right, right_quals);
//     getline(right, right_quals);

//     left_header = left_header.substr(0, left_header.length()-2);
//     right_header = right_header.substr(0, right_header.length()-2);

//   }

// }

// fixpairing left right output
int main (int argc, char* argv[]) {
  if (argc == 3) {
    FixPairing checker;
    checker.check(argv[1], argv[2]);
    //
  } else if (argc == 5) {
    FixPairing fixer;
    // store left file
    fixer.load_right(argv[2]);
    // load right file
    fixer.scan_left(argv[1], argv[3], argv[4]);
    //
    // fixer.fix (argv[1], argv[2], argv[3]);

    return 0;
  } else {
    cout << "fixpairing version 0.3 - Author: Chris Boursnell\n"
         << "Usage:\n"
         << "Check pairing:\n"
         << "fixpairing <left> <right>\n"
         << "Fix Pairing:\n"
         << "fixpairing <left> <right> <fixed_left> <fixed_right>"
         << endl;
    return 1;

  }
}
