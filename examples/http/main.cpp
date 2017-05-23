#include "SimpleHTTP.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	std::string str = HTTP::get("http://ipinfo.io/ip/");
	str = str.substr(str.find("\r\n\r\n") + 4);
	cout << "Your ip is: " << str.substr(0, str.find('\n')) << endl;
	system("pause");
}
