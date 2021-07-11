//
// Created by arina
//

#include <iostream>

using namespace std;

class message {
public:
    static void print_message(const string& message){
        if (message == "-h") {
            cout << "Sorting command line tool.\n"
                    "\n"
                    "Sorting is command line tool for sorting objects of any data type.\n"
                    "It reads input data from the file(input.txt) and returns sorted data to the file(output.txt) for each word on separate line from smallest to largest from top to bottom.\n"
                    "\n"
                    "Usage: sorting [input file] [data type] \n"
                    "Write sorted concatenation of all FILE(s) to output FILE(s).\n"
                    "\n"
                    "Mandatory arguments to long options are mandatory for short options too.\n"
                    "Ordering options:\n"
                    "\n"
                    "      -h, --help: display this help and exit\n"
                    "      -i, --input: set input file to sort [filename] (ex. -i input.txt)\n"
                    "      -o, --output: set output file [filename] (ex. -o output.txt)\n"
                    "      -p, --parallel: parallel sorting, running all types of sorts at the same time [input_data type] (ex. -p int)\n"
                    "      -g, --generate: generate input_data to input file [input_data type] [count] (ex. -g string -co 1000)\n"
                    "      -co, --count: count of objects to generate (use ONLY with generate) [count] (ex. -co 1000)\n"
                    "       All types of sorting can be used by specifying an input file and output file (ex. -b string -i input.txt -o output.txt)"
                    "      -b, --bubble-sort: use bubble sort [input_data type] (ex. -b string)\n"
                    "      -q, --quick-sort: use quick sort [input_data type] (ex. -q string)\n"
                    "      -m, --merge-sort: use merge sort [input_data type] (ex. -m string)\n"
                    "      -s, --selection-sort: use selection sort [input_data type] (ex. -s string)\n"
                    "      -in, --insertion-sort: use insertion sort [input_data type] (ex. -in string)\n"
                    "      -c, --counting-sort: use counting sort [input_data type(ONLY INT OR CHAR)] (ex. -c int)\n"
                    "\n"
                    "Other options:\n"
                    "\n"
                    "      -ch, --check-sorting: checks the output file for correct sorting [filename] [input_data type] (ex. -ch bubble_output.txt int)\n"
                    "      -cf, --comparison-files: compares input_data in two files [filename1] [filename2] [input_data type] (ex. -cf bubble_output.txt quick_output.txt int)\n"
                    "      -r, --reverse:  reverse the output_data of comparisons and write the output_data in the new file reverse.txt [filename] [input_data type] (ex. -r bubble_output.txt int) \n"
                    "      -si, --show-input: show input file [input file] [input_data type] (ex. -si input.txt int)\n"
                    "      -so, --show-output: show output file [output file] [input_data type] (ex. -so output.txt int)\n"
                    "      -cnt, --count-file: shows the number of objects in the file [filename] [input_data type] (ex. -cnt bubble_output.txt int)\n";
        }
    }
};