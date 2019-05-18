#ifndef NAMESPACES_MODEM_H_INCLUDED_
#define NAMESPACES_MODEM_H_INCLUDED_

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

namespace modem {
	//Parses strings
	namespace parse {

		auto trim = [](auto input) {
			if(input.length() < 2)
				return input;
			// cout << input.length() << " --> " << input << endl;

			while(input[0] == ' ') {
				input.erase(0, 1);
			}
			// cout << "After first trim: " << input << endl;
			while(input[input.length() -1] == ' ') {
				input.pop_back();
			}
			while(input.find("\n")!=string::npos)
				input.erase(input.find("\n"), 1);

			return input;
		};

		//splits string using given delimeter!
		vector<string> split(string input, char search_delimeter = ' ') {
			auto start_parsing_index = 0;
			vector<string> single_parsed_contents;
			string last_string_after_parsing;

			for(auto char_position = input.find(search_delimeter, start_parsing_index); char_position != string::npos;) {
				single_parsed_contents.push_back(
					trim(
						input.substr(
							start_parsing_index,
							char_position
							- start_parsing_index
						)
					)
				);
				start_parsing_index = char_position +1;
				char_position = input.find(search_delimeter, start_parsing_index);
			}

			// cout << start_parsing_index << " -> " << input.length() << endl;
			if(start_parsing_index != input.length()) {
				last_string_after_parsing = trim(
					input.substr(
						start_parsing_index,
						input.length() -1
					)
				);
			}
			if(!last_string_after_parsing.empty())
				single_parsed_contents.size() > 0 ? single_parsed_contents.push_back(last_string_after_parsing) : single_parsed_contents.push_back(input);
			return single_parsed_contents;
		}
	}


	//console commands for mmcli responsive modems
	namespace mmcli_commands {
		string list_modems = "mmcli -L | grep Modem";
	  string list_specific_modem_by_name = "mmcli -L | grep "; //Modem name
	  string list_specific_modem_by_index = "mmcli -L | grep /"; //Modem index
		string get_modem_information_by_index = "mmcli -m ";
	  // string list_modems = "mmcli -L | grep Modem";
	  // string ussdCommand = "--3gpp-ussd-initiate=";
	  // string ussdCommandResponds = "--3gpp-ussd-respond=";
	  // string cancelUssdCommands = "--3gpp-ussd-cancel";
	}


	//logging
	namespace output {
	  //Outputs debug messages
		auto debug = [](auto input) {
			cout << "DEBUG:\t" << input << endl;
		};

	  //Outputs test messages
	  auto test = [](auto input) {
	    cout << "TEST:\t" << input << endl;
	  };

		//Outputs warning messages
		auto warning = [](auto input) {
			// https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
			cerr
			<< "\033[1;31m" //Red
			<< "WARNING:>>>\t"
			<< input
			<< "\033[0m"
			<< endl;
		};
	}

	//terminal tools
	namespace terminal {
  string run(string command) {
  	string data;
  	FILE * stream;
  	const int max_buffer = 1024;
  	char buffer[max_buffer];
  	command.append(" 2>&1");

  	stream = popen(command.c_str(), "r");
  	if (stream) {
  		while (!feof(stream)) if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
  		pclose(stream);
  	}
  	return data;
  }
}
}

#endif
