#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>


void login();
void forgot_password();
void registration();
void reattemptLogin();

using std::string;

int main() {

	int choice; // Menu choice

	// Formatting the login page
	std::cout << "\t\t\t_______________________________________" << '\n';
	std::cout << "\t\t\t					          " << '\n';
	std::cout << "\t\t\t_____________  Main Menu  _____________" << '\n';
	std::cout << "                  \n";
	std::cout << "\t\t\t|* Select 1 for Login               \t|\n";
	std::cout << "\t\t\t|* Select 2 to Register             \t|\n";
	std::cout << "\t\t\t|* Select 3 if you Forgot Password  \t|\n";
	std::cout << "\t\t\t|* Select 4 to Exit Menu.           \t| \n";

	std::cin >> choice;

	// Switch cases depending on users input
	switch (choice)
	{
	case 1: login();
			break;

	/* case 2: registration();
			break;

	case 3: forgot_password();
			break; */

	case 4: std::cout << "See you soon!";

	default: // If invalid option, recall main() and try again.
		system("cls");
		std::cout << "Invalid option, please try again";
		std::cout << '\n';
		main();
		break;
	}
	
}

void login() {

	system("cls");
	bool successLogin = false; // current status is false until username and password match the record

	string username, password, userID,passID;

	std::cout << "\t\t\t Please enter your username: " << std::endl;
	std::cin >> username;

	std::cout << "\t\t\t Now enter your password: " << std::endl;
	std::cin >> password;

	std::ifstream record("records.txt"); // file which stores the user details
	while (record >> userID >> passID) {
		
		// checking the user input against the record details
		if (userID == username && passID == password) {
			successLogin = true; 
			system("cls");
		}
	}
	record.close();

	// if login was successful then...
	if (successLogin == true) {
		std::cout << username << " has successfully logged in!" << std::endl;
		main();
	}
	else {
		// call function to reattempt login
		reattemptLogin();
	}
}

void reattemptLogin() {

	// give the user the choice of whether they want to attempt login again or return to main menu.
	string reattempt;
	std::cout << "Unsuccessful login, would you like to try again? (yes/no)" << std::endl;
	std::cin >> reattempt;
	if (reattempt == "Yes" || reattempt == "yes")
		login();
	else if (reattempt == "no" || reattempt == "No") {
		system("cls");
		main();
	}
	else {
		system("cls");
		std::cout << "Please enter yes or no." << std::endl;
		reattemptLogin();
	}
	

}

void registration() {

	system("cls");
	string regUsername, regPassword, regUser, regPass;
	std::cout << "Welcome to the registration page!" << '\n';
	std::cout << "Please enter a username: " << '\n';
	std::cin >> regUsername;
	std::cout << "Enter a password that is atleast 8 characters long, with an uppercase, \n";
	std::cout << " lowercase and special character";
	std::cin >> regPassword;
	

}