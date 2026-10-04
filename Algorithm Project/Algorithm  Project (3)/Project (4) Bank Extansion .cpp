#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);

		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}

}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();

	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients()
{
	char AddMore = 'Y';

	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

void FindClient(string AccountNumber, vector <sClient> vClients, sClient& Client) {

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
	}

	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
	}


}

void GoBackToMenu(vector <sClient> vClients)
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	system("cls"); // دي اللي بتمسح القديم وتروق الشاشة
}

void TransactionsScreen(vector <sClient>& vClients);

void GoBackToTransactionsMenue(vector <sClient>& vClients)
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	TransactionsScreen(vClients);
}

void DepositScreen(vector <sClient>& vClients)
{
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	sClient Client;
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") does not exist!\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientRecord(Client);

	double DepositAmount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> DepositAmount;

	char Answer = 'n';
	cout << "\nAre you sure you want perform this transaction? y/n? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += DepositAmount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nAmount Deposited Successfully. New Balance is: " << C.AccountBalance;
				break;
			}
		}
	}
}

void WithdrawScreen(vector <sClient>& vClients)
{
	system("cls");
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";

	sClient Client;
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") does not exist!\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientRecord(Client);

	double WithdrawAmount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> WithdrawAmount;

	while (WithdrawAmount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << "\n";
		cout << "Please enter another amount? ";
		cin >> WithdrawAmount;
	}

	char Answer = 'n';
	cout << "\nAre you sure you want perform this transaction? y/n? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance -= WithdrawAmount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nAmount Withdrawn Successfully. New Balance is: " << C.AccountBalance;
				break;
			}
		}
	}
}

void ShowTotalBalancesScreen(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (sClient Client : vClients)
		{
			cout << "| " << setw(15) << left << Client.AccountNumber;
			cout << "| " << setw(40) << left << Client.Name;
			cout << "| " << setw(12) << left << Client.AccountBalance << endl;
			TotalBalances += Client.AccountBalance;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
}

void MainMenuScreen();

void TransactionsScreen(vector <sClient>& vClients)
{
	system("cls");
	cout << "\n\t    ==========================\n\n"
		<< "      Transactions Menu Screen     "
		<< "\n\n==========================\n\n";

	cout << "\t[1] Deposit.\n"
		<< "\t[2] Withdraw.\n"
		<< "\t[3] Total Balances.\n"
		<< "\t[4] Main Menu.\n";

	cout << "\n======================================\n\n"
		<< "             ***     BANK    ***        "
		<< "\n\n\t    ==========================\n\n";

	char YourChoice;
	cout << "\nChoose what do you want to do ? [1 to 4] ? ";
	cin >> YourChoice;

	switch (YourChoice)
	{
	case '1':
		system("cls");
		DepositScreen(vClients);
		GoBackToTransactionsMenue(vClients);
		break;

	case '2':
		system("cls");
		WithdrawScreen(vClients);
		GoBackToTransactionsMenue(vClients);
		break;

	case '3':
		system("cls");
		ShowTotalBalancesScreen(vClients);
		GoBackToTransactionsMenue(vClients);
		break;

	case '4':
		system("cls");
		MainMenuScreen();
		break;
	}
}

void MainMenuScreen() {

	sClient Client;

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	char YourChoice;

	cout << "\n\t    ==========================\n\n"
		<< "        Main Menue Screen     "
		<< "\t\n\n==========================\n\n";

	cout
		<< "\t[1] Show Client List.\n"
		<< "\t[2] Add New Client.\n"
		<< "\t[3] Delete Client.\n"
		<< "\t[4] Update Client Info.\n"
		<< "\t[5] Find Client.\n"
		<< "\t[6] Transactions Client.\n"
		<< "\t[7] Exit.\n";

	cout << "\n======================================\n\n"
		<< "             ***     BANK    ***        "
		<< "\n\n\t    ==========================\n\n";

	cout << "\nChoose what do you want to do ? [1 to 6] ?\n";
	cin >> YourChoice;

	system("cls");

	switch (YourChoice)
	{
	case '1':
		PrintAllClientsData(vClients);
		GoBackToMenu(vClients);
		MainMenuScreen();
		break;

	case '2':
		AddClients();
		GoBackToMenu(vClients);
		MainMenuScreen();
		break;

	case '3':
	{
		string AccountNumber = ReadClientAccountNumber();
		DeleteClientByAccountNumber(AccountNumber, vClients);
		GoBackToMenu(vClients);
		MainMenuScreen();
		break;
	}
	case '4':
	{
		string AccountNumber = ReadClientAccountNumber();
		UpdateClientByAccountNumber(AccountNumber, vClients);
		GoBackToMenu(vClients);
		MainMenuScreen();
		break;
	}

	case '5':
	{
		string AccountNumber = ReadClientAccountNumber();
		FindClient(AccountNumber, vClients, Client);
		GoBackToMenu(vClients);
		MainMenuScreen();
		break;
	}

	case '6':
	{

		TransactionsScreen(vClients);
		break;
	}

	case '7':
		exit(0); // اتصلحت وبقت تمام
		break;
	}

}


int main()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	MainMenuScreen();

	system("pause>0");
	return 0;
}