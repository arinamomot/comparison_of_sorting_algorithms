//
// Created by arina
//

#include <iostream>
#include <thread>
#include <iomanip>
#include <algorithm>
#include "vector"
#include "map"
#include "sortings/quickSort.cpp"
#include "sortings/bubbleSort.cpp"
#include "sortings/mergeSort.cpp"
#include "sortings/selectionSort.cpp"
#include "sortings/countingSort.cpp"
#include "sortings/insertionSort.cpp"
#include "generator.hpp"
#include "message.hpp"

template<typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

using namespace std;

class helpers {
public:
    static bool arguments_checking(const vector<string> &arguments) {
        bool fail = false;
        vector<string> allowed_arguments = {"-h", "--help", "-i", "--input", "-o", "--output", "-p", "--parallel", "-g",
                                            "--generate", "-co", "--count", "-b", "--bubble-sort", "-q", "--quick-sort",
                                            "-m", "--merge-sort", "-s", "--selection-sort", "-in", "--insertion-sort",
                                            "-c", "--counting-sort", "-ch", "--check-sorting", "-cf",
                                            "--comparison-files", "-r", "--reverse", "-si", "--show-input", "-so",
                                            "--show-output", "-cnt", "--count-file", "string", "int", "double", "char"};
        for (int i = 1; i < arguments.size(); i++) {
            if ((arguments[i] == "-co") || (arguments[i] == "-i") || (arguments[i] == "-o")  || (arguments[i] == "-si") || (arguments[i] == "-so") || (arguments[i] == "-cnt") || (arguments[i] == "-ch") ) i++;
            else if (arguments[i]=="-cf" || (arguments[i] == "-r")) i = i+2;
            else if (!(find(allowed_arguments.begin(), allowed_arguments.end(), arguments[i]) !=
                       allowed_arguments.end())) {
                cerr << arguments[i] << ": command not found" << endl;
                fail = true;
            }
        }
        return fail;
    }

    /*
    * Converts long arguments to short ones to simplify further implementation
    */
    static vector<string> shortenArguments(vector<string> arguments) {
        for (auto &arg : arguments) {
            if (arg == "--help") arg = "-h";
            else if (arg == "--input") arg = "-i";
            else if (arg == "--output") arg = "-o";
            else if (arg == "--parallel") arg = "-p";
            else if (arg == "--generate") arg = "-g";
            else if (arg == "--count") arg = "-co";
            else if (arg == "--bubble-sort") arg = "-b";
            else if (arg == "--quick-sort") arg = "-q";
            else if (arg == "--merge-sort") arg = "-m";
            else if (arg == "--selection-sort") arg = "-s";
            else if (arg == "--insertion-sort") arg = "-in";
            else if (arg == "--counting-sort") arg = "-c";
            else if (arg == "--check-sorting") arg = "-ch";
            else if (arg == "--comparison-files") arg = "-cf";
            else if (arg == "--reverse") arg = "-r";
            else if (arg == "--show-input") arg = "-si";
            else if (arg == "--show-output") arg = "-so";
            else if (arg == "--count-input") arg = "-cnt";
        }
        return arguments;
    }

    static string get_type(const vector<string> &arguments) {
        string type;
        if (find(arguments.begin(), arguments.end(), "string") != arguments.end()) {
            type = "string";
        } else if (find(arguments.begin(), arguments.end(), "char") != arguments.end()) {
            type = "char";
        } else if (find(arguments.begin(), arguments.end(), "int") != arguments.end()) {
            type = "int";
        } else if (find(arguments.begin(), arguments.end(), "double") != arguments.end()) {
            type = "double";
        }
        return type;
    }

    static void launch_program(vector<string> arguments, map<string, string> &options) {
        //Count, input, output
        for (int i = 0; i < arguments.size(); i++) {
            if (arguments[i] == "-co") options["count"] = arguments[i + 1];
            else if (arguments[i] == "-i") options["input"] = arguments[i + 1];
            else if (arguments[i] == "-o") options["output"] = arguments[i + 1];
        }

        if (find(arguments.begin(), arguments.end(), "-h") != arguments.end()) {
            message::print_message("-h");
        } else if (find(arguments.begin(), arguments.end(), "-g") != arguments.end()) {
            generator::generate(options["type"], std::stoi(options["count"]));
        } else if (find(arguments.begin(), arguments.end(), "-b") != arguments.end()) {
            helpers::bubble_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-q") != arguments.end()) {
            helpers::quick_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-m") != arguments.end()) {
            helpers::merge_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-s") != arguments.end()) {
            helpers::selection_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-in") != arguments.end()) {
            helpers::insertion_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-c") != arguments.end()) {
            helpers::counting_sort(options["input"], options["type"], options["output"]);
        } else if (find(arguments.begin(), arguments.end(), "-p") != arguments.end()) {
            helpers::parallelSorting(options);
        } else if (find(arguments.begin(), arguments.end(), "-ch") != arguments.end()) {
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-ch") {
                    options["file"] = arguments[i + 1];
                }
            }
            helpers::check_sorting(options["file"], options["type"]);
        } else if (find(arguments.begin(), arguments.end(), "-si") != arguments.end()) {
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-si") {
                    options["file"] = arguments[i + 1];
                }
            }
            helpers::show_input_file(options["file"], options["type"]);
        } else if (find(arguments.begin(), arguments.end(), "-so") != arguments.end()) {
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-so") {
                    options["file"] = arguments[i + 1];
                }
            }
            helpers::show_output_file(options["file"], options["type"]);
        } else if (find(arguments.begin(), arguments.end(), "-cf") != arguments.end()) {
            string filename1;
            string filename2;
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-cf") {
                    filename1 = arguments[i + 1];
                    filename2 = arguments[i + 2];
                }
            }
            helpers::compare_files(filename1, filename2, options["type"]);
        } else if (find(arguments.begin(), arguments.end(), "-r") != arguments.end()) {
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-r") {
                    options["file"] = arguments[i + 1];
                }
            }
            helpers::reverse_file(options["file"], options["type"]);
        } else if (find(arguments.begin(), arguments.end(), "-cnt") != arguments.end()) {
            for (int i = 0; i < arguments.size(); i++) {
                if (arguments[i] == "-cnt") {
                    options["file"] = arguments[i + 1];
                }
            }
            helpers::count_objects_in_file(options["file"], options["type"]);
        }
    }

    static vector<string> &read_file_string(const string &filename) {
        auto *elements = new vector<string>;
        ifstream file;
        file.open(filename);
        while (!file.eof()) {
            string el;
            file >> el;
            if (!el.empty()) elements->push_back(el);
        }
        return *elements;
    }

    static vector<char> &read_file_char(const string &filename) {
        auto *elements = new vector<char>;
        ifstream file;
        file.open(filename);
        while (!file.eof()) {
            char sym;
            file >> sym;
            elements->push_back(sym);
        }
        elements->pop_back();
        return *elements;
    }

    static vector<int> &read_file_int(const string &filename) {
        auto *elements = new vector<int>;
        ifstream file;
        file.open(filename);
        while (!file.eof()) {
            int num;
            file >> num;
            if (num != 0) elements->push_back(num);
        }
        return *elements;
    }

    static vector<double> &read_file_double(const string &filename) {
        auto *elements = new vector<double>;
        ifstream file;
        file.open(filename);
        while (!file.eof()) {
            double num;
            file >> num;
            if (num != 0) elements->push_back(num);
        }
        return *elements;
    }

    template<typename T>
    static void write_to_file(vector<T> elements, const string &filename) {
        ofstream file;
        file.open(filename);
        for (int i = 0; i < elements.size() - 1; i++) {
            file << fixed << setprecision(5) << elements[i] << endl;
        }
        file << fixed << setprecision(5) << elements[elements.size() - 1];
        file.close();
    }

    static void parallelSorting(const map<string, string> &options) {
        std::thread quick_sort([](map<string, string> options) {
            if (options["type"] == "string") {
                quickSort<string> sort;
                cout << "quick sort started" << endl;
                vector<string> unsorted = read_file_string(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<string> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
                cout << "quick sort ended" << endl;
                write_to_file(sorted, "../output_data/quick_output.txt");
            } else if (options["type"] == "char") {
                quickSort<char> sort;
                cout << "quick sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
                cout << "quick sort ended" << endl;
                write_to_file(sorted, "../output_data/quick_output.txt");
            } else if (options["type"] == "int") {
                quickSort<int> sort;
                cout << "quick sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
                cout << "quick sort ended" << endl;
                write_to_file(sorted, "../output_data/quick_output.txt");
            } else if (options["type"] == "double") {
                quickSort<double> sort;
                cout << "quick sort started" << endl;
                vector<double> unsorted = read_file_double(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<double> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
                cout << "quick sort ended" << endl;
                write_to_file(sorted, "../output_data/quick_output.txt");
            }
        }, options);

        std::thread bubble_sort([](map<string, string> options) {
            if (options["type"] == "string") {
                bubbleSort<string> sort;
                cout << "bubble sort started" << endl;
                vector<string> unsorted = read_file_string(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<string> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
                cout << "bubble sort ended" << endl;
                write_to_file(sorted, "../output_data/bubble_output.txt");
            } else if (options["type"] == "char") {
                bubbleSort<char> sort;
                cout << "bubble sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
                cout << "bubble sort ended" << endl;
                write_to_file(sorted, "../output_data/bubble_output.txt");
            } else if (options["type"] == "int") {
                bubbleSort<int> sort;
                cout << "bubble sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
                cout << "bubble sort ended" << endl;
                write_to_file(sorted, "../output_data/bubble_output.txt");
            } else if (options["type"] == "double") {
                bubbleSort<double> sort;
                cout << "bubble sort started" << endl;
                vector<double> unsorted = read_file_double(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<double> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
                cout << "bubble sort ended" << endl;
                write_to_file(sorted, "../output_data/bubble_output.txt");
            }
        }, options);

        std::thread insertion_sort([](map<string, string> options) {
            if (options["type"] == "string") {
                insertionSort<string> sort;
                cout << "insertion sort started" << endl;
                vector<string> unsorted = read_file_string(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<string> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
                cout << "insertion sort ended" << endl;
                write_to_file(sorted, "../output_data/insertion_output.txt");
            } else if (options["type"] == "char") {
                insertionSort<char> sort;
                cout << "insertion sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
                cout << "insertion sort ended" << endl;
                write_to_file(sorted, "../output_data/insertion_output.txt");
            } else if (options["type"] == "int") {
                insertionSort<int> sort;
                cout << "insertion sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
                cout << "insertion sort ended" << endl;
                write_to_file(sorted, "../output_data/insertion_output.txt");
            } else if (options["type"] == "double") {
                insertionSort<double> sort;
                cout << "insertion sort started" << endl;
                vector<double> unsorted = read_file_double(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<double> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
                cout << "insertion sort ended" << endl;
                write_to_file(sorted, "../output_data/insertion_output.txt");
            }
        }, options);

        std::thread selection_sort([](map<string, string> options) {
            if (options["type"] == "string") {
                selectionSort<string> sort;
                cout << "selection sort started" << endl;
                vector<string> unsorted = read_file_string(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<string> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
                cout << "selection sort ended" << endl;
                write_to_file(sorted, "../output_data/selection_output.txt");
            } else if (options["type"] == "char") {
                selectionSort<char> sort;
                cout << "selection sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
                cout << "selection sort ended" << endl;
                write_to_file(sorted, "../output_data/selection_output.txt");
            } else if (options["type"] == "int") {
                selectionSort<int> sort;
                cout << "selection sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
                cout << "selection sort ended" << endl;
                write_to_file(sorted, "../output_data/selection_output.txt");
            } else if (options["type"] == "double") {
                selectionSort<double> sort;
                cout << "selection sort started" << endl;
                vector<double> unsorted = read_file_double(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<double> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
                cout << "selection sort ended" << endl;
                write_to_file(sorted, "../output_data/selection_output.txt");
            }
        }, options);

        std::thread merge_sort([](map<string, string> options) {
            if (options["type"] == "string") {
                mergeSort<string> sort;
                cout << "merge sort started" << endl;
                vector<string> unsorted = read_file_string(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<string> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
                cout << "merge sort ended" << endl;
                write_to_file(sorted, "../output_data/merge_output.txt");
            } else if (options["type"] == "char") {
                mergeSort<char> sort;
                cout << "merge sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
                cout << "merge sort ended" << endl;
                write_to_file(sorted, "../output_data/merge_output.txt");
            } else if (options["type"] == "int") {
                mergeSort<int> sort;
                cout << "merge sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
                cout << "merge sort ended" << endl;
                write_to_file(sorted, "../output_data/merge_output.txt");
            } else if (options["type"] == "double") {
                mergeSort<double> sort;
                cout << "merge sort started" << endl;
                vector<double> unsorted = read_file_double(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<double> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
                cout << "merge sort ended" << endl;
                write_to_file(sorted, "../output_data/merge_output.txt");
            }
        }, options);

        std::thread counting_sort([](map<string, string> options) {
            if (options["type"] == "char") {
                countingSort<char> sort;
                cout << "counting sort started" << endl;
                vector<char> unsorted = read_file_char(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<char> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish counting sort.\n";
                cout << "counting sort ended" << endl;
                write_to_file(sorted, "../output_data/counting_output.txt");
            } else if (options["type"] == "int") {
                countingSort<int> sort;
                cout << "counting sort started" << endl;
                vector<int> unsorted = read_file_int(options["input"]);
                auto start = std::chrono::high_resolution_clock::now();
                vector<int> sorted = sort.sort_elements(unsorted);
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end - start).count() << " ms to finish counting sort.\n";
                cout << "counting sort ended" << endl;
                write_to_file(sorted, "../output_data/counting_output.txt");
            }
        }, options);

        quick_sort.join();
        bubble_sort.join();
        insertion_sort.join();
        selection_sort.join();
        merge_sort.join();
        counting_sort.join();
    }

    static void quick_sort(const string &filename, const string &type, string &filename2) {
        if (type == "string") {
            quickSort<string> sort;
            cout << "quick sort started" << endl;
            vector<string> unsorted = read_file_string(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<string> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
            cout << "quick sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/quick_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "char") {
            quickSort<char> sort;
            cout << "quick sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
            cout << "quick sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/quick_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            quickSort<int> sort;
            cout << "quick sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
            cout << "quick sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/quick_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "double") {
            quickSort<double> sort;
            cout << "quick sort started" << endl;
            vector<double> unsorted = read_file_double(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<double> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish quick sort.\n";
            cout << "quick sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/quick_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void bubble_sort(const string &filename, const string &type, string &filename2) {
        if (type == "string") {
            bubbleSort<string> sort;
            cout << "bubble sort started" << endl;
            vector<string> unsorted = read_file_string(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<string> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
            cout << "bubble sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/bubble_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "char") {
            bubbleSort<char> sort;
            cout << "bubble sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
            cout << "bubble sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/bubble_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            bubbleSort<int> sort;
            cout << "bubble sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
            cout << "bubble sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/bubble_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "double") {
            bubbleSort<double> sort;
            cout << "bubble sort started" << endl;
            vector<double> unsorted = read_file_double(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<double> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish bubble sort.\n";
            cout << "bubble sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/bubble_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void insertion_sort(const string &filename, const string &type, string &filename2) {
        if (type == "string") {
            insertionSort<string> sort;
            cout << "insertion sort started" << endl;
            vector<string> unsorted = read_file_string(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<string> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
            cout << "insertion sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/insertion_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "char") {
            insertionSort<char> sort;
            cout << "insertion sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
            cout << "insertion sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/insertion_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            insertionSort<int> sort;
            cout << "insertion sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
            cout << "insertion sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/insertion_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "double") {
            insertionSort<double> sort;
            cout << "insertion sort started" << endl;
            vector<double> unsorted = read_file_double(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<double> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish insertion sort.\n";
            cout << "insertion sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/insertion_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void merge_sort(const string &filename, const string &type, string &filename2) {
        if (type == "string") {
            mergeSort<string> sort;
            cout << "merge sort started" << endl;
            vector<string> unsorted = read_file_string(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<string> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
            cout << "merge sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/merge_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "char") {
            mergeSort<char> sort;
            cout << "merge sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
            cout << "merge sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/merge_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            mergeSort<int> sort;
            cout << "merge sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
            cout << "merge sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/merge_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "double") {
            mergeSort<double> sort;
            cout << "merge sort started" << endl;
            vector<double> unsorted = read_file_double(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<double> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish merge sort.\n";
            cout << "merge sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/merge_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void selection_sort(const string &filename, const string &type, string &filename2) {
        if (type == "string") {
            selectionSort<string> sort;
            cout << "selection sort started" << endl;
            vector<string> unsorted = read_file_string(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<string> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
            cout << "selection sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/selection_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "char") {
            selectionSort<char> sort;
            cout << "selection sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
            cout << "selection sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/selection_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            selectionSort<int> sort;
            cout << "selection sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
            cout << "selection sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/selection_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "double") {
            selectionSort<double> sort;
            cout << "selection sort started" << endl;
            vector<double> unsorted = read_file_double(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<double> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish selection sort.\n";
            cout << "selection sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/selection_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void counting_sort(const string &filename, const string &type, string &filename2) {
        if (type == "char") {
            countingSort<char> sort;
            cout << "counting sort started" << endl;
            vector<char> unsorted = read_file_char(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<char> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish counting sort.\n";
            cout << "counting sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/counting_output.txt";
            write_to_file(sorted, filename2);
        } else if (type == "int") {
            countingSort<int> sort;
            cout << "counting sort started" << endl;
            vector<int> unsorted = read_file_int(filename);
            auto start = std::chrono::high_resolution_clock::now();
            vector<int> sorted = sort.sort_elements(unsorted);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Needed " << to_ms(end - start).count() << " ms to finish counting sort.\n";
            cout << "counting sort ended" << endl;
            if (filename2 == "../output_data/output.txt") filename2 = "../output_data/counting_output.txt";
            write_to_file(sorted, filename2);
        }
    }

    static void show_input_file(const string &filename, const string &type) {
        if (type == "string") {
            vector<string> elements = read_file_string(filename);
            for (const auto &el : elements) cout << el << endl;
        } else if (type == "char") {
            vector<char> elements = read_file_char(filename);
            for (auto el : elements) cout << el << endl;
        } else if (type == "int") {
            vector<int> elements = read_file_int(filename);
            for (auto el : elements) cout << el << endl;
        } else if (type == "double") {
            vector<double> elements = read_file_double(filename);
            for (auto el : elements) cout << el << endl;
        }
    }

    static void show_output_file(const string &filename, const string &type) {
        if (type == "string") {
            vector<string> elements = read_file_string(filename);
            for (const auto &el : elements) cout << el << endl;
        } else if (type == "char") {
            vector<char> elements = read_file_char(filename);
            for (auto el : elements) cout << el << endl;
        } else if (type == "int") {
            vector<int> elements = read_file_int(filename);
            for (auto el : elements) cout << el << endl;
        } else if (type == "double") {
            vector<double> elements = read_file_double(filename);
            for (auto el : elements) cout << el << endl;
        }
    }

    static void check_sorting(const string &filename, const string &type) {
        bool check = false;
        if (type == "string") {
            vector<string> elements = read_file_string(filename);
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i - 1] < elements[i]) check = true;
                else check = false;
            }
            if (check) cout << "Data in file " << filename << " is sorted correctly" << endl;
            else cout << "Data in file " << filename << " is sorted wrong" << endl;
        } else if (type == "char") {
            vector<char> elements = read_file_char(filename);
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i - 1] < elements[i]) check = true;
                else check = false;
            }
            if (check) cout << "Data in file " << filename << " is sorted correctly" << endl;
            else cout << "Data in file " << filename << " is sorted wrong" << endl;
        } else if (type == "int") {
            vector<int> elements = read_file_int(filename);
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i - 1] < elements[i]) check = true;
                else check = false;
            }
            if (check) cout << "Data in file " << filename << " is sorted correctly" << endl;
            else cout << "Data in file " << filename << " is sorted wrong" << endl;
        } else if (type == "double") {
            vector<double> elements = read_file_double(filename);
            for (int i = 1; i < elements.size(); i++) {
                if (elements[i - 1] < elements[i]) check = true;
                else check = false;
            }
            if (check) cout << "Data in file " << filename << " is sorted correctly" << endl;
            else cout << "Data in file " << filename << " is sorted wrong" << endl;
        }
    }

    /*
    * Compare data in two files
    */
    static void compare_files(const string &filename1, const string &filename2, const string &type) {
        bool same = false;
        if (type == "string") {
            vector<string> elements1 = read_file_string(filename1);
            vector<string> elements2 = read_file_string(filename2);
            for (auto &el1 : elements1) {
                for (auto &el2 : elements2) {
                    if (el1 == el2) same = true;
                    else same = false;
                }
            }
            if (same) cout << "File: " << filename1 << " and file: " << filename2 << " are the same." << endl;
            else cout << "File: " << filename1 << " and file: " << filename2 << " are not the same." << endl;
        } else if (type == "char") {
            vector<char> elements1 = read_file_char(filename1);
            vector<char> elements2 = read_file_char(filename2);
            for (auto &el1 : elements1) {
                for (auto &el2 : elements2) {
                    if (el1 == el2) same = true;
                    else same = false;
                }
            }
            if (same) cout << "File: " << filename1 << " and file: " << filename2 << " are the same." << endl;
            else cout << "File: " << filename1 << " and file: " << filename2 << " are not the same." << endl;
        } else if (type == "int") {
            vector<int> elements1 = read_file_int(filename1);
            vector<int> elements2 = read_file_int(filename2);
            for (auto &el1 : elements1) {
                for (auto &el2 : elements2) {
                    if (el1 == el2) same = true;
                    else same = false;
                }
            }
            if (same) cout << "File: " << filename1 << " and file: " << filename2 << " are the same." << endl;
            else cout << "File: " << filename1 << " and file: " << filename2 << " are not the same." << endl;
        } else if (type == "double") {
            vector<double> elements1 = read_file_double(filename1);
            vector<double> elements2 = read_file_double(filename2);
            for (auto &el1 : elements1) {
                for (auto &el2 : elements2) {
                    if (el1 == el2) same = true;
                    else same = false;
                }
            }
            if (same) cout << "File: " << filename1 << " and file: " << filename2 << " are the same." << endl;
            else cout << "File: " << filename1 << " and file: " << filename2 << " are not the same." << endl;
        }
    }

    /*
    * Reverse data in file
    */
    static void reverse_file(const string &filename, const string &type) {
        if (type == "string") {
            vector<string> elements = read_file_string(filename);
            std::reverse(elements.begin(), elements.end());
            write_to_file(elements, "../output_data/reverse.txt");
        } else if (type == "char") {
            vector<char> elements = read_file_char(filename);
            std::reverse(elements.begin(), elements.end());
            write_to_file(elements, "../output_data/reverse.txt");
        } else if (type == "int") {
            vector<int> elements = read_file_int(filename);
            std::reverse(elements.begin(), elements.end());
            write_to_file(elements, "../output_data/reverse.txt");
        } else if (type == "double") {
            vector<double> elements = read_file_double(filename);
            std::reverse(elements.begin(), elements.end());
            write_to_file(elements, "../output_data/reverse.txt");
        }
    }

    static void count_objects_in_file(const string &filename, const string &type) {
        if (type == "string") {
            vector<string> elements = read_file_string(filename);
            cout << "There are " << elements.size() << " objects in file: " << filename << endl;
        } else if (type == "char") {
            vector<char> elements = read_file_char(filename);
            cout << "There are " << elements.size() << " objects in file: " << filename << endl;
        } else if (type == "int") {
            vector<int> elements = read_file_int(filename);
            cout << "There are " << elements.size() << " objects in file: " << filename << endl;
        } else if (type == "double") {
            vector<double> elements = read_file_double(filename);
            cout << "There are " << elements.size() << " objects in file: " << filename << endl;
        }
    }
};