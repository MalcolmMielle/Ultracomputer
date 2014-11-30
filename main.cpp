#include <SerialStream.h>
#include <iostream>

#define PORT "/dev/ttyACM1"

int main(int argc, char* argv[]){
	
	LibSerial::SerialStream ardu;
	
	ardu.Open(PORT);
	ardu.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);
	ardu.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
	
	char str[100], choix, test='o';
	while(true){
		std::cin >> choix;
		ardu << choix;
		//ardu >> str;
		while(test != '~'){
			ardu.get(test);
			std::cout<<test;
		}
		test = 'o';
	}
	return 0;
}
