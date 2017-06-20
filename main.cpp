#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options; //use namespace more easily

/*Add --info or --help into the command line argument in order to bring up the description
  For Netbeans: Project Properties --> Run --> Run Command --> Enter commands separated by spaces
*/

int main (int argc, char* argv[]) {
    
    int testVar;
    
    po::options_description desc("Program options");
    desc.add_options()
            ("filename,F", po::value<string>()->default_value("default.txt"), "file to process") //note how default value is assigned
            ("inttest,S", po::value<int>(&testVar)->default_value(7), "testing ints") //Make sure there's no space in first parameter string
            ("multiples,M", po::value<vector<string>>()->multitoken(), "Adding multiple parameters"); //Add multitoken here if you have multiple parameters after the command

    /*If you want to use positional options, i.e not add flags: specify additional descriptor
      Positional arguments go before flagged arguments in terminal
     */
    po::positional_options_description pos;
    pos.add("multiples", -1); //-1 indicates unlimited parameters
    
    
    po::variables_map vm;
    //auto parsed = po::parse_command_line(argc, argv, desc); //instead of this, with positional options descriptor you have to manually specify
    po::command_line_parser parser(argc, argv);
    auto parsed = parser.options(desc).positional(pos).run();
    po::store(parsed, vm); 
    po::notify(vm);
    
    if (vm.count("info")) {
        cout << desc << endl;
        return 1;
    }
    
    if (vm.count("filename") || vm.count("inttest")) { //This if will run since filename and inttest have been assigned a default value
        cout << "File found: " << vm["filename"].as<string>() << endl;
        cout << "Test Integer found: " << vm["inttest"].as<int>() << endl;
    }
    
    if (vm.count("multiples")) {
        cout << "\nMultiple filenames found:\n";
        auto files = vm["multiples"].as<vector<string>>();
        for (auto i : files) {
            cout << i << endl;
        }
    }
    else
        cout << "\nNo multiple files specified\n";
    
    return 0;
}