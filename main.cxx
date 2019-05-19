#include "src/modems.hpp"

using namespace std;



int main(int argc, char** argv) {
	//get a list of all modems
	vector<Modem> list_of_modems = Modem::get_all_modems();

	//get modem information
	for(auto modem: list_of_modems) {
		cout << "Modem_index: " << modem.get_index() << endl;
		cout << "Modem_operator_name: " << modem.get_operator_name() << endl;
		cout << "Modem_id: " << modem.get_id() << endl;
		cout << "Modem_signal_quality: " << modem.get_signal_quality() << endl;
		cout << "Sending SMS: " << boolalpha << modem.send_sms("hello world", "652156811") << endl << endl;
	}
	return 0;
}
