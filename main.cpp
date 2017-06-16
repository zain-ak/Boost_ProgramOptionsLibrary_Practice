#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options; //use namespace more easily

/*Add --info or --help into the command line argument in order to bring up the description
  For Netbeans: Project Properties --> Run --> Run Command --> Enter commands separated by spaces
*/

int main (int argc, char* argv[]) {
    po::options_description desc("Program options");
    desc.add_options()
            ("info", "This is a test for program options")
            ("help", "Use this command to view help")
            ("filename", po::value<string>()->default_value("default.txt"), "file to process");

    po::variables_map vm;
    auto parsed = po::parse_command_line(argc, argv, desc);
    po::store(parsed, vm);
    po::notify(vm);
    
    if (vm.count("info")) {
        cout << desc << endl;
        return 1;
    }
    
    if (vm.count("filename")) {
        cout << "File found: " << vm["filename"].as<string>() << endl;
        return 1;
    }
    
    cout << "File found: default.txt" << endl;
    
    return 0;
}