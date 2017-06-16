#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

/*Add --info or --help into the command line argument in order to bring up the description
  For Netbeans: Project Properties --> Run --> Run Command --> Enter commands separated by spaces
*/

int main (int argc, char* argv[]) {
    po::options_description desc("Program options");
    desc.add_options()
            ("info", "This is a test for program options")
            ("help", "Use this command to view help");

    po::variables_map vm;
    auto parsed = po::parse_command_line(argc, argv, desc);
    po::store(parsed, vm);
    po::notify(vm);
    
    if (vm.count("info"))
        cout << desc << endl;
    
    
    return 0;
}