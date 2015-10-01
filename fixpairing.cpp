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
    long line = 1;

    while (getline(left, left_header)) {
      getline(left, left_seq);
      getline(left, left_quals);
      getline(left, left_quals);

      getline(right, right_header);
      getline(right, right_seq);
      getline(right, right_quals);
      getline(right, right_quals);

      left_header = left_header.substr(0, left_header.length()-2);
      right_header = right_header.substr(0, right_header.length()-2);

      if (left_header.compare(right_header) != 0) {
        cout << "headers mismatched at line " << line << endl;
        break;
      }
      line += 4;

    }


}

// fixpairing left right output
int main (int argc, char* argv[]) {
  if (argc == 3) {
    FixPairing checker;
    checker.check(argv[1], argv[2]);
    //
  } else if (argc == 4) {
    FixPairing fixer;
    // store left file
    fixer.load_right(argv[2]);
    // load right file
    fixer.scan_left(argv[1], argv[3]);

    return 0;
  } else {
    cout << "fixpairing version 0.2 - Author Chris Boursnell\n"
         << "Usage:\n"
         << "Check pairing:\n"
         << "fixpairing <left> <right>\n"
         << "Fix Pairing:\n"
         << "fixpairing <left> <right> <fixed_right>"
         << endl;
    return 1;

  }
}
