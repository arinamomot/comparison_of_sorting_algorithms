#include "vector"
#include "map"
#include "helpers.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    map<string, string> options;
    options["input"] = "../input_data/input.txt";
    options["output"] = "../output_data/output.txt";
    options["type"];
    options["count"];
    options["file"];
    vector<string> arguments(argv, argv + argc);
    arguments = helpers::shortenArguments(arguments);
    bool fail = helpers::arguments_checking(arguments);
    if (fail) return 0;
    options["type"] = helpers::get_type(arguments);
    helpers::launch_program(arguments, options);

    return 0;
}
