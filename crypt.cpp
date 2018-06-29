#include "crypt.h"

void crypt(std::string &str, const std::string &key){
	for (int i = 0; i < 512; ++i){
		key = sha512(key);
	}
	for (int i = 0, j = 0; i < str.length(); ++i, ++j){
		str[i] = str[i] ^ key[j % key.length()];
	}
}
