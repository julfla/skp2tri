#include "skp_parser.h"

using namespace std;

void display_usage(int argc, char** argv) {
    cout << "Usage is :" << endl;
    cout << argv[0] << " <input-skp-file> [<output-tri-file>]" << endl;
}

int main(int argc, char** argv) {

    if(argc < 2 || argc > 3) {
        display_usage(argc,argv);
        return 1;
    }

    if( argv[1] == "-h" || argv[1] == "--help") {
        display_usage(argc,argv);
        return 0;
    }

    string input_path(argv[1]);
    string output_path;

    if(argc == 3) //output file has been provided
        output_path = string(argv[2]);
    else {
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
