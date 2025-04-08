#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string clientsFile = "clients.txt";

//void showMainMenu();

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool isMarkedToDelete = false;
	bool isMarkedToUpdate = false;
};

stClient currentClient;

string readAccountNumber() {
	string accountNumber;
	cout << "\nEnter the account number : ";
	cin >> accountNumber;
	return accountNumber;
}

string readPinCode() {
	string pinCode;
	cout << "\nEnter the pin code : ";
	cin >> pinCode;
	return pinCode;
}


void showLoginScreen() {
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tLogin Screen";
	cout << "\n-----------------------------------\n";
}

bool isClientExists(vector<stClient> vStClient, stClient& clientToFind, string accountNumber, string pinCode) {
	for (stClient& client : vStClient) {
		if (client.AccountNumber == accountNumber && client.PinCode == pinCode) {
			clientToFind = client;
			return true;
		}
	}
	return false;
}



void findClientByCredentials(string accountNumber, string pinCode, vector<stClient> vStClients) {
	while (isClientExists(vStClients,currentClient, accountNumber, pinCode) == false) {
		showLoginScreen();
		cout << "\nInvalid account number/pin code";
		accountNumber = readAccountNumber();
		pinCode = readPinCode();
	}
	system("cls");
	//showMainMenu();
}

vector<string> splitString(string& clientRecord, string delim) {
	string word = "";
	vector<string> vString;
	short pos;
	while ((pos = clientRecord.find(delim)) != std::string::npos) {
		word = clientRecord.substr(0, pos);
		vString.push_back(word);
		clientRecord.erase(0, pos + delim.length());
	}
	if (clientRecord != "") {
		vString.push_back(clientRecord);
	}
	return vString;

}

stClient convertLineToRecord(string line, string delim) {
	stClient client;
	vector<string> vString;
	vString = splitString(line, "#//#");
	client.AccountNumber = vString[0];
	client.PinCode = vString[1];
	client.Name = vString[2];
	client.Phone = vString[3];
	client.AccountBalance = stod(vString[4]);
	return client;
}



vector<stClient> readFileContent(string fileName) {
	fstream myFile;
	short counter = 0;
	stClient client;
	vector<stClient> vStClient;
	myFile.open(fileName, ios::in);
	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			client = convertLineToRecord(line, "#//#");
			vStClient.push_back(client);
			counter++;
		}
		myFile.close();
	}
	return vStClient;
}


void Login() {
	showLoginScreen();
	vector<stClient> vStClients = readFileContent(clientsFile);
	string accountNumber = readAccountNumber();
	string pinCode = readPinCode();
	findClientByCredentials(accountNumber, pinCode, vStClients);
}

int main()
{
	Login();
}
