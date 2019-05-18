#include <iostream>
#include <vector>
#include "namespaces.hpp"

#ifndef MODEMS_H_INCLUDED
#define MODEMS_H_INCLUDED

class Modem {
	void extract_modem_information();

	std::string index;
	std::string e_id;
	std::string sigqual;
	std::string operator_name;

	public:
		Modem(std::string modem_index);
		Modem();

		static std::vector<Modem> get_all_modems();

		std::string get_operator_name();
		std::string get_id();
		std::string get_signal_quality();
		std::string get_index();


		std::bool send_sms(std::string message, std::string phonenumber);
};

#endif


//using namespace std;

Modem::Modem(std::string modem_index) {
	this->index = modem_index;

	this->extract_modem_information();
}



std::bool send_sms(std::string message, std::string phonenumber) {

}

void Modem::extract_modem_information() {
	std::string extract_eid = "scripts/modem_information_extraction.sh extract e_id " + this->index;
	std::string extract_sigqual = "scripts/modem_information_extraction.sh extract sig_qual " + this->index;
	std::string extract_operator_name = "scripts/modem_information_extraction.sh extract op_name " + this->index;

	std::string e_id = modem::parse::trim( modem::terminal::run(extract_eid) );
	std::string sigqual = modem::parse::trim( modem::terminal::run(extract_sigqual) );
	std::string operator_name = modem::parse::trim( modem::terminal::run(extract_operator_name) );

	this->e_id = e_id;
	this->sigqual = sigqual;
	this->operator_name = operator_name;
}


vector<Modem> Modem::get_all_modems() {
	vector<Modem> list_of_modems;

	std::string terminal_output = modem::terminal::run("scripts/modem_information_extraction.sh list");

	vector<std::string> index_of_modems = modem::parse::split(terminal_output, '\n');

	for(auto modem_index : index_of_modems) {
		Modem modem(modem_index);
		list_of_modems.push_back(modem);
	}

	return list_of_modems;
}

std::string Modem::get_operator_name() {
	return this->operator_name;
}

std::string Modem::get_id() {
	return this->e_id;
}

std::string Modem::get_signal_quality() {
	return this->sigqual;
}

std::string Modem::get_index() {
	return this->index;
}
