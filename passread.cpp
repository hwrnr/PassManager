#define UNICODE

#include <iostream>
#include <fstream>
#include "base64.h"
#include "crypt.h"

#define PATH "/PassFold/"

using namespace std;


void printUsernameAndPassword(const string& username, const string& password){
	string command = "echo -n \'";
	cout << "Username: " << username << endl;
	cout << "Password: * * *" << endl;
	command += password;
	command += "\' | xclip -l 1";
	system(reinterpret_cast<const char*>(command.c_str()));
}


int main(int argc, char const *argv[]){

	if(argc != 2){
		cout << "Error. You need to enter exactly one argument" << endl;
		return 0;
	}

	string homePath, filePath, username, password, key, usernameSalt, passwordSalt;
	homePath = getenv("HOME");
	filePath = homePath;
	filePath += PATH;
	filePath += argv[1];

	cout << "Enter encryption key: ";
  system("stty -echo");
	cin >> key;
  system("stty echo");
  cout << endl;

	ifstream file;
	file.open(filePath);

	file >> usernameSalt;
	file >> username;
	file >> passwordSalt;
	file >> password;
	username = base64_decode(username);
	password = base64_decode(password);
	crypt(username, key, usernameSalt);
	crypt(password, key, passwordSalt);


	printUsernameAndPassword(username, password);
	file.close();



	return 0;
}
