#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>

using std::string;

void login();
void forgot_password();
void registration();
void reattemptLogin();
void mainmenu();
void testPassword(string password);

class PasswordConstraint {
private:
	int minLength = 8;  // Default value for minLength
	int maxLength = 20; // Default value for maxLength
	bool requireLowercase = false; // Default value for requireLowercase
	bool requireUppercase = false; // Default value for requireUppercase
	bool requireNumbers = false;   // Default value for requireNumbers
	bool requireSpecialChars = false; // Default value for requireSpecialChars

public:
	int getMinLength() const {
		return minLength;
	}

	void setMinLength(int length) {
		minLength = length;
	}

	int getMaxLength() const {
		return maxLength;
	}

	void setMaxLength(int length) {
		maxLength = length;
	}

	bool isRequireLowercase() const {
		return requireLowercase;
	}

	void setRequireLowercase(bool value) {
		requireLowercase = value;
	}

	bool isRequireUppercase() const {
		return requireUppercase;
	}

	void setRequireUppercase(bool value) {
		requireUppercase = value;
	}

	bool isRequireNumbers() const {
		return requireNumbers;
	}

	void setRequireNumbers(bool value) {
		requireNumbers = value;
	}

	bool isRequireSpecialChars() const {
		return requireSpecialChars;
	}

	void setRequireSpecialChars(bool value) {
		requireSpecialChars = value;
	}

	bool isLengthValid(const std::string& value) const {
		return value.length() >= minLength && value.length() <= maxLength;
	}

	bool hasLowercase(const std::string& value) const {
		return std::regex_search(value, std::regex("[a-z]"));
	}

	bool hasUppercase(const std::string& value) const {
		return std::regex_search(value, std::regex("[A-Z]"));
	}

	bool hasNumbers(const std::string& value) const {
		return std::regex_search(value, std::regex("[0-9]"));
	}

	bool hasSpecialChars(const std::string& value) const {
		return std::regex_search(value, std::regex("[!@#%^&*(),.?\":{}|<>]"));
	}
};

bool validatePassword(std::string& value, PasswordConstraint& constraint) {

	if (!constraint.isLengthValid(value)) {
		std::cout << "Error: Password should have a minimum length of " << constraint.getMinLength()
			<< " and a maximum length of " << constraint.getMaxLength() << std::endl;
	}

	if (constraint.isRequireLowercase() && !constraint.hasLowercase(value)) {
		std::cout << "Error: Password should contain at least one lowercase letter" << std::endl;
	}

	if (constraint.isRequireUppercase() && !constraint.hasUppercase(value)) {
		std::cout << "Error: Password should contain at least one uppercase letter" << std::endl;
	}

	if (constraint.isRequireNumbers() && !constraint.hasNumbers(value)) {
		std::cout << "Error: Password should contain at least one number" << std::endl;
	}

	if (constraint.isRequireSpecialChars() && !constraint.hasSpecialChars(value)) {
		std::cout << "Error: Password should contain at least one special character" << std::endl;
	}
	return 0;
}

int main() {

	mainmenu();


	return 0;
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
		mainmenu();
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
		mainmenu();
	}
	else {
		system("cls");
		std::cout << "Please enter yes or no." << std::endl;
		reattemptLogin();
	}
	

}

void registration() {

	
	bool valid = false;
	int minLength = 8;
	int maxLength = 20;



	string regUsername, regPassword, regUser, regPass;

	std::cout << "Welcome to the registration page!" << '\n';
	std::cout << "Please enter a username: " << '\n';
	std::cin >> regUsername;
	std::cout << "Enter a password that is 8-20 characters long\n";
	std::cin >> regPassword;

	if (regPassword.length() >= 8 && regPassword.length() <= 20) {
		std::ofstream registerUser("records.txt", std::ios::app); // open records.txt to write username and password inside.
		registerUser << regUsername << " " << regPassword << std::endl;


		system("cls");
		int choice;
		std::cout << "Welcome aboard " << regUsername << ", your registration has been successful!" << '\n' << std::endl;
		std::cout << "Press 1 if you would like to login, and 2 if you would like to return to the main menu." << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1: login();
			break;
		case 2: mainmenu();
			break;
		default:
			std::cout << "Invalid input, returning to main menu." << std::endl;
			mainmenu();
			break;
		}
	}
	else {
		std::cout << "Invalid password, please try again" << std::endl;
		registration();

	}
	
}
	


void mainmenu() {
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

	case 2: registration();
		break;

		/* case 3: forgot_password();
				break; */

	case 4: std::cout << "See you soon!";

	default: // If invalid option, recall main() and try again.
		system("cls");
		std::cout << "Invalid option, please try again" << '\n';
		main();
		break;
	}
	return;
}






/* void testPassword(string password) {

	bool valid = false;


	std::cin >> password;

		PasswordConstraint constraint;
		constraint.setMinLength(8);
		constraint.setMaxLength(20);
		constraint.setRequireLowercase(true);
		constraint.setRequireUppercase(true);
		constraint.setRequireNumbers(true);
		constraint.setRequireSpecialChars(true);

		validatePassword(password, constraint);

		valid = true;
	
		
	
}

/* bool testPass(string password) {

	valid = false;
	
	int minLength = 8;
	int maxLength = 20;

	if (password.length() >= 8 && password.length() <= 20) {

		for (int k = 0; k < password.length(); k++)
		{
			if (isupper(password[k]))
			{
				return valid = true;



			}

		}
	}

	
} */