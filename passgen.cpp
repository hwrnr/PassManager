#include <iostream>
#include <fstream>
#include "base64.h"
#include "crypt.h"

#include <cstdlib>
#include <ctime>



#define PATH "/PassFold/"

using namespace std;

void getUsernameAndPassword(string &username, string &password, const string &key){
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter password or g to autogenerate: ";
	cin >> password;
	if (password == "g"){
		cout << "Generating password" << endl;
		char temp;
		srand (time(NULL));
		for (int i = 0; i < 30; ++i){
			password += (char)(rand() % 94 + 33);
			while (password [i] == '\''){
				password[i] = (char)(rand() % 94 + 33);
			}
		}
	}
	crypt(password, key);
	password = base64_encode(reinterpret_cast<const unsigned char*>(password.c_str()), password.length());
}

int main(int argc, char const *argv[]){

	string homePath, filePath, username, password, key;
        homePath = getenv("HOME");
        filePath = homePath;
        filePath += PATH;
	
	if (argc == 2) filePath += argv[1];
	else {
		string temp;
		cout << "Enter service name: ";
		cin >> temp;
		filePath += temp;
	}

	cout << "Enter encryption key: ";
        cin >> key;
	

	ofstream file;
        file.open(filePath);

	getUsernameAndPassword(username, password, key);

	file << username << "\n" << password;

	file.close();

	return 0;
}
