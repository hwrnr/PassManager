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
	command += "\' | xclip";
	system(reinterpret_cast<const char*>(command.c_str()));
}


int main(int argc, char const *argv[]){

	if(argc != 2){
		cout << "Error. You need to enter exactly one argument" << endl;
		return 0;
	}

	string homePath, filePath, username, password, key;
	homePath = getenv("HOME");
	filePath = homePath;
	filePath += PATH;
	filePath += argv[1];

	cout << "Enter encryption key: ";
	cin >> key;

	ifstream file;
	file.open(filePath);

	file >> username;
	file >> password;
	password = base64_decode(password);
	crypt(password, key);


	printUsernameAndPassword(username, password);
	file.close();



	return 0;
}
