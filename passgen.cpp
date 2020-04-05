#define UNICODE

#include <iostream>
#include <fstream>
#include "base64.h"
#include "crypt.h"
#include <unistd.h>

#include <cstdlib>
#include <ctime>



#define PATH "/PassFold/"

using namespace std;

void getUsernameAndPassword(string &username, string &password, const string &key, string &usernameSalt, string &passwordSalt){
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter password or g to autogenerate: ";
  system("stty -echo");
	cin >> password;
  system("stty echo");
	if (password == "g"){
		cout << "Generating password" << endl;
		char temp;
		srand (time(NULL) + getpid());
		password = "";
		for (int i = 0; i < 30; ++i){
			password += (char)(rand() % 94 + 33);
			while (password [i] == '\''){
				password[i] = (char)(rand() % 94 + 33);
			}
		}
	}
	//generate salts
	for (int i = 0; i < 10; ++i){
                usernameSalt += (char)(rand() % 94 + 33);
                passwordSalt += (char)(rand() % 94 + 33);
        }
	crypt(username, key, usernameSalt);
	crypt(password, key, passwordSalt);
	username = base64_encode(reinterpret_cast<const unsigned char*>(username.data()), username.length());
	password = base64_encode(reinterpret_cast<const unsigned char*>(password.c_str()), password.length());
}

int main(int argc, char const *argv[]){

	string homePath, filePath, username, password, key, passwordSalt, usernameSalt;
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
  system("stty -echo");
  cin >> key;
  system("stty echo");
  cout << endl;
	

	ofstream file;
  file.open(filePath);
	if (!file){
		system("mkdir ~/PassFold");
		file.open(filePath);
		if (!file){
			cout << "Error occurred while opening file" << endl;
			return 0;
		}
	}

	getUsernameAndPassword(username, password, key, usernameSalt, passwordSalt);

	file << usernameSalt << "\n" << username << "\n" << passwordSalt << "\n" << password;

	file.close();

	return 0;
}
