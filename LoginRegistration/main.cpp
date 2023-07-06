#include <iostream>
#include <ostream>
#include <fstream>


void login();
void forgot_password();
void registration();

using std::string;

int main() {

	int choice; // Menu choice

	// Formatting the login page

	std::cout << "\t\t\t_______________________________" << '\n';
	std::cout << "\t\t\t          Login Page\n\n";
	std::cout << "\t\t\t_________  Main Menu  _________" << '\n';
	std::cout << "                  \n\n";
	std::cout << "\t\t\t* Select 1 for Login                 \n\n";
	std::cout << "\t\t\t* Select 2 to Register              \n\n";
	std::cout << "\t\t\t* Select 3 if you Forgot Password                \n\n";
	std::cout << "\t\t\t* Select 4 to Exit Menu.                 \n\n";

	std::cin >> choice;

	// Switch cases depending on users input
	switch (choice)
	{
	case 1: login();
			break;

	case 2: forgot_password();
			break;

	case 3: registration();
			break;

	case 4: std::cout << "See you soon!";

	default: // If invalid option, recall main() and try again.
		system("cls");
		std::cout << "Invalid option, please try again";
		main();
		break;
	}
	
}

void login() {

	system("cls");
	bool successLogin = false;
	string username, password, userID,passID;

	std::cout << "/t/t/t Please enter your username: " << std::endl;
	std::cin >> username;

	std::cout << "/t/t/t Now enter your password: " << std::endl;
	std::cin >> password;

	std::ifstream record("records.txt");
	while (record >> userID >> passID) {

		if (userID == username && passID == password) {
			successLogin == true;
			system("cls");
		}
	}
	record.close();

	if (successLogin == true) {

		std::cout << username << " has successfully logged in!" << std::endl;
	}
}