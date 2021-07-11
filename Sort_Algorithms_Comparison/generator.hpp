//
// Created by arina on 26.10.2020.
//

#include "iostream"
#include "fstream"
#include "string"
#include <random>
#include <ctime>
#include "ios"
#include "iomanip"

using namespace std;

class generator {
public:
    static void generate(const string &type, int count) {
        ofstream file;
        file.open("../input_data/input.txt");
        if (type == "string") {
            for (int i = 0; i < count-1; i++) {
                file << get_random_string((rand() % 100 + 1)) << endl;
            }
            file << get_random_string((rand() % 100 + 1));
        } else if (type == "int") {
            for (int i = 0; i < count-1; i++) {
                file << get_random_int() << endl;
            }
            file << get_random_int();
        } else if (type == "double") {
            for (int i = 0; i < count - 1; i++) {
                file << fixed << setprecision(5) << get_random_double() << endl;
            }
            file << fixed << setprecision(5) << get_random_double();
        } else if (type == "char") {
            for (int i = 0; i < count-1; i++) {
                file << get_random_char() << endl;
            }
            file << get_random_char();
        }
        file.close();
    }

    static int get_random_int() {
        random_device rd; // obtain a random number from hardware
        mt19937 gen(rd()); // seed the generator
        uniform_int_distribution<> distr(-1000000, 1000000); // define the range

        return distr(gen); // generate numbers
    }

    static double get_random_double() {
        static mt19937 mt{random_device{}()};
        static uniform_real_distribution<> dist(-1000000, 1000000);
        return dist(mt);
    }

    static char get_random_char() {
        const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!%:?*()_+=-&^%=$#@~{}[]':<>,.|";

        random_device random_device;
        mt19937 generator(random_device());
        uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        char random_char = CHARACTERS[distribution(generator)];
        return random_char;
    }

    static string get_random_string(size_t length) {
        const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        random_device random_device;
        mt19937 generator(random_device());
        uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

        string random_string;

        for (size_t i = 0; i < length; ++i) {
            random_string += CHARACTERS[distribution(generator)];
        }
        return random_string;
    }
};