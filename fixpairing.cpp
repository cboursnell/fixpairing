#include "fixpairing.h"

int FixPairing::load_right(char* infile) {
    cout << "loading right..." << endl;
    std::ifstream right(infile);
    string header;
    string seq;
    string quals;
    while (getline(right, header)) {
      getline(right, seq);
      getline(right, quals);
      getline(right, quals);

      entry e;
      header = header.substr(0, header.length()-2);
      e.seq = seq;
      e.quals = quals;
      store[header] = e;
    }
    cout << "done..." << endl;
}

int FixPairing::scan_left(char* infile, char* outfile) {
    cout << "scanning left..." << endl;
    std::ifstream left(infile);
    string header;
    string seq;
    string quals;

    std::ofstream output;
    output.open (outfile);

    while (getline(left, header)) {
      getline(left, seq);
      getline(left, quals);
      getline(left, quals);
      // store fastq entry

      header = header.substr(0, header.length()-2);

      entry l = store[header];
      if (l.seq.length()>1) {
        output << header << "/2" << endl;
        output << l.seq << endl;
        output << "+" << endl;
        output << l.quals << endl;
      } else {
        cout << "can't find " << header << endl;
      }
    }
    cout << "done..." << endl;
}

// fixpairing left right output
int main (int argc, char* argv[]) {
  if (argc == 4) {
    FixPairing fixer;
    // store left file
    fixer.load_right(argv[2]);
    // load right file
    fixer.scan_left(argv[1], argv[3]);

    return 0;
  } else {
    cout << "fixpairing version 0.1\n"
         << "Usage:\n"
         << "fixpairing <left> <right> <fixed_right>"
         << endl;
    return 1;

  }
}
