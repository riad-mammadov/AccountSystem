#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
// #include <regex>

using std::string;

// function declarations
void login();
void forgotPassword();
void registration();
void reattemptLogin();
void mainmenu();
void checkPassword(string password);
void successfulLogin(string user);
// void testPassword(string password);



int main() {

	mainmenu();


	return 0;
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

	case 3: forgotPassword();
		break;

	case 4: std::cout << "See you soon!" << '\n';

	default: // If invalid option, recall main menu and try again.
		system("cls");
		std::cout << "Invalid option, please try again" << '\n';
		mainmenu();
		break;
	}
	return;
}


void login() {

	system("cls");
	bool successLogin = false; // current status is false until username and password match the record

	string username, password, userID,passID;

	std::cout << "\t\t\t Please enter your username: " << std::endl;
	std::cin >> username;

	std::cout << "\t\t\t Now enter your password: " << std::endl;
	std::cin >> password;

	std::ifstream read("records.txt");    //searches for the record.txt file in userData folder(read is object name)
	read >> userID >> passID;
	
		
		// checking the user input against the record details
		if (userID == username && passID == password) {
			successLogin = true; 
			system("cls");
		}
	
	read.close();

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

	
	int minLength = 8;
	int maxLength = 20;



	string regUsername, regPassword, securityQ;

	std::cout << "Welcome to the registration page!" << '\n';
	std::cout << "Please enter a username: " << '\n';
	std::cin >> regUsername;
	std::cout << "Enter a password that is 8-20 characters long\n";
	std::cin >> regPassword;
	std::cout << "As a security measure, please answer the following question: " << '\n';
	std::cout << "What was your first school name? " << '\n';
	std::cin >> securityQ;
	

	checkPassword(regPassword); // checks if password is 8-20 characters long and only then will it write into the file.

	std::ofstream file;
	file.open("records.txt");
	file << regUsername << std::endl << regPassword << std::endl << securityQ; //store user credentials in records
	file.close();

	successfulLogin(regUsername); // display successful registration screen

	}

void forgotPassword() {

	bool found = false;
	string username, u, p, sA, securityQ;

	std::cout << "You forgot your password? Let me help you." << std::endl;
	std::cout << "Please provide your username: " << '\n';
	std::cin >> username;
	

	std::ifstream file;
	file.open("records.txt");
	if (file) {                                                  
		std::cout << "Answer the Question correctly to recover your password.";
		std::cout << "What was the name of your first school: ";
		std::cin >> securityQ;
		file >> u >> p >> sA;
		if (sA == securityQ) {
			std::cout << "Correct answer! Your Password is: " << '\n' << p; // checks if security answer is correct
			mainmenu();
		}
		else {
			std::cout << "Wrong Answer. Try again later." << '\n';
			exit(0);
		}
	}
	else { 
		std::cout << "Username not found, try again later." << '\n';
		exit(0);
	}





}

	
void successfulLogin(string user) {

	string regUsername = user;

	int choice;
	std::cout << "Welcome aboard " << regUsername << ", your registration has been successful!" << '\n' << std::endl;
	std::cout << "Press 1 if you would like to login, and 2 if you would like to return to the main menu." << '\n' << std::endl;
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

void checkPassword(string password) {

	string regPassword = password;

	if (regPassword.length() >= 8 && regPassword.length() <= 20) {
		std::cout << "Valid password." << '\n';
	}
	else {
		std::cout << "Invalid password, please try again" << '\n';
		registration();
	}


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

	
}

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

*/