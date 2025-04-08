#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string clientsFile = "clients.txt";

void showMainMenu();
void showNormalWithdrawScreen();
void showQuickWithdrawMenu();

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

enum enMenu {quickWithdraw = 1, normalWithdraw = 2, deposit = 3, checkBalance = 4, logout = 5};
enum enQuickWithdrawMenu {twenty = 1, fifty = 2, oneHundred = 3, twoHundred = 4, fourHundred = 5, sixHundred = 6, eightHundred = 7, oneThousand = 8, exitMenu = 9};

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
	showMainMenu();
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

short readMenuChoice(string message, short min, short max) {
	short choice;
	do {
		cout << message;
		cin >> choice;
	} while (choice > max || choice < min);
	return choice;
}


void showCheckBalanceScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tCheck Balance Screen";
	cout << "\n-----------------------------------\n";
	cout << "Your balance is " << currentClient.AccountBalance;
}

void goBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	system("cls");
	showMainMenu();
}

string convertRecordToStringWithDelim(stClient clientInfo, string delim) {
	string clientRecord = "";
	clientRecord += clientInfo.AccountNumber + delim;
	clientRecord += clientInfo.PinCode + delim;
	clientRecord += clientInfo.Name + delim;
	clientRecord += clientInfo.Phone + delim;
	clientRecord += to_string(clientInfo.AccountBalance);
	return clientRecord;
}

void saveVectorToFile(string fileName, vector<stClient> vStClient) {
	fstream myFile;
	string line;
	myFile.open(fileName, ios::out); //overwrite
	if (myFile.is_open()) {
		for (stClient& client : vStClient) {
			if (client.isMarkedToDelete == false) {
				line = convertRecordToStringWithDelim(client, "#//#");
				myFile << line << endl;
			}
		}
		myFile.close();
	}
}

void performQuickWithdraw(short withdrawAmount) {
	char answer;
	vector<stClient> vStClients = readFileContent(clientsFile);

	while (currentClient.AccountBalance < withdrawAmount) {
		cout << "\nThe amount exceeds available balance, make another choice.\n";
		system("pause");
		system("cls");
		showQuickWithdrawMenu();
	}

	cout << "\nAre you sure you want to perform this transaction? (y/n) ";
	cin >> answer;


	if (tolower(answer == 'y') && currentClient.AccountBalance >= withdrawAmount) {
		currentClient.AccountBalance -= withdrawAmount;

		for (stClient& client : vStClients) {
			if (client.AccountNumber == currentClient.AccountNumber) {
				client.AccountBalance = currentClient.AccountBalance;  // Update the client in the vector
				break;
			}
		}

		saveVectorToFile(clientsFile, vStClients);
		cout << "Done successfully, the new balance is : " << currentClient.AccountBalance;
	}
	else {
		cout << "No changes were made\n";
	}
}

void performQuickWithdrawMenuOptions(enQuickWithdrawMenu choice) {
	switch (choice) {
	case ::twenty:
		performQuickWithdraw(20);
		goBackToMainMenu();
		break;
	case ::fifty:
		performQuickWithdraw(50);
		goBackToMainMenu();
		break;
	case ::oneHundred:
		performQuickWithdraw(100);
		goBackToMainMenu();
		break;
	case ::twoHundred:
		performQuickWithdraw(200);
		goBackToMainMenu();
		break;
	case ::fourHundred:
		performQuickWithdraw(400);
		goBackToMainMenu();
		break;
	case ::sixHundred:
		performQuickWithdraw(600);
		goBackToMainMenu();
		break;
	case ::eightHundred:
		performQuickWithdraw(800);
		goBackToMainMenu();
		break;
	case ::oneThousand:
		performQuickWithdraw(1000);
		goBackToMainMenu();
		break;
	case ::exitMenu:
		system("cls");
		showMainMenu();
		break;
	}
}

void showQuickWithdrawMenu() {
	cout << "=========================================================\n";
	cout << "\t\tQuick Withdraw Menu\n";
	cout << "=========================================================\n";
	cout << "\t[1] 20.";
	cout << "\t\t[2] 50.\n";
	cout << "\t[3] 100.";
	cout << "\t[4] 200.\n";
	cout << "\t[5] 400.";
	cout << "\t[6] 600.\n";
	cout << "\t[7] 800.";
	cout << "\t[8] 1000.\n";
	cout << "\t[9] Exit.\n";
	cout << "=========================================================\n";
	cout << "\nYour balance is : " << currentClient.AccountBalance << endl;
	performQuickWithdrawMenuOptions((enQuickWithdrawMenu)readMenuChoice("Please select an option from the menu above (1-9): ", 1, 9));
}




int getClientWithdrawInfo() {
	int withdrawAmount = 0;
	do{
		system("cls");
		showNormalWithdrawScreen();
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> withdrawAmount;
	} while (withdrawAmount % 5 != 0);
	while (withdrawAmount > currentClient.AccountBalance) {
	     cout << "Amount exceeds the balance, you can withdraw up to :" << currentClient.AccountBalance;
		 cout << "Please enter another amount ? ";
		 cin >> withdrawAmount;
		}
	return withdrawAmount;
}


void performNormalWithdraw() {
	char answer;
	int withdrawAmount = getClientWithdrawInfo();
	vector<stClient> vStClients = readFileContent(clientsFile);

	cout << "\nAre you sure you want to perform this transaction? (y/n) ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y') {
		currentClient.AccountBalance -= withdrawAmount;

		for (stClient& client : vStClients) {
			if (client.AccountNumber == currentClient.AccountNumber) {
				client.AccountBalance = currentClient.AccountBalance;  // Update the client in the vector
				break;
			}
		}
		saveVectorToFile(clientsFile, vStClients);
		cout << "Done successfully, the new balance is : " << currentClient.AccountBalance;
	}
	else {
		cout << "No changes were made\n";
	}
}


void showNormalWithdrawScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tNormal Withdraw Screen";
	cout << "\n-----------------------------------\n";
}

void showDepositScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";
}


void performDeposit() {
	int depositAmount = 0;
	char answer;
	vector<stClient> vStClients = readFileContent(clientsFile);

	do {
		system("cls");
		showDepositScreen();
		cout << "\nPlease enter a positive deposit amount : ";
		cin >> depositAmount;
	} while (depositAmount < 0);

	cout << "\nAre you sure you want to perform this transaction? (y/n) ";
	cin >> answer;

	if (answer == 'y' || answer == 'Y') {
		currentClient.AccountBalance += depositAmount;

		for (stClient& client : vStClients) {
			if (client.AccountNumber == currentClient.AccountNumber) {
				client.AccountBalance = currentClient.AccountBalance;  // Update the client in the vector
				break;
			}
		}
		saveVectorToFile(clientsFile, vStClients);
		cout << "Done successfully, the new balance is : " << currentClient.AccountBalance;
	}
	else {
		cout << "No changes were made\n";
	}

}

void performMainMenuOptions(enMenu choice) {
	switch (choice) {
	case enMenu::quickWithdraw:
		system("cls");
		showQuickWithdrawMenu();
		break;
	case enMenu::normalWithdraw:
		system("cls");
		performNormalWithdraw();
		goBackToMainMenu();
		break;
	case enMenu::deposit:
		system("cls");
		performDeposit();
	case enMenu::checkBalance:
		system("cls");
		showCheckBalanceScreen();
		goBackToMainMenu();
		break;
	case enMenu::logout:
		system("cls");
		Login();
		break;
	}
}

void showMainMenu() {
	cout << "=========================================================\n";
	cout << "\t\tATM Main Menu Screen\n";
	cout << "=========================================================\n";
	cout << "\t[1] Quick withdraw.\n";
	cout << "\t[2] Normal withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "=========================================================\n";
	performMainMenuOptions((enMenu)readMenuChoice("Please select an option from the menu above (1-5): ", 1, 5));

}

int main()
{
	Login();
}
