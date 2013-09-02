#include "skp_parser.h"
#include <boost/program_options.hpp> //used to parse command lne arguments
namespace po = boost::program_options;

using namespace std;

int main(int argc, char** argv) {

    string input_path, output_path;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("input,i", po::value<string>(), "Input skp file")
            ("output,o", po::value<string>(), "Output tri file")
            //("tri", "Export to a tri file instead of a pcd file")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

     if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    if (vm.count("input")) {
        input_path = vm["input"].as<string>();
    } else {
        cout << "Input file unknown or invalid." << endl;
        cout << desc << endl;
        return 1;
    }

    if (vm.count("output")) {
        output_path = vm["output"].as<string>();
    } else {
        //default value is <file>.tri
        int lastindex = input_path.find_last_of(".");
        output_path = input_path.substr(0, lastindex) + ".tri";
    }

    SUInitialize();
    SUModelRef model = SU_INVALID;
    SUResult res = SUModelCreateFromFile(&model, input_path.c_str());
    // Check file opening
    if (res != SU_ERROR_NONE) {
        std::cerr << "Error : file " << input_path << " impossible to open" << "\n";
        return 1;
    }

    // Get the entity container of the model.
    SUEntitiesRef entities = SU_INVALID;
    SUModelGetEntities(model, &entities);

    std::ofstream myfile(output_path.c_str());
    myfile << entities;
    myfile.close();

    //std::cout << entities << "\n";
    return 0;
}
