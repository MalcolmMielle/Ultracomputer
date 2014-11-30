#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define PORT "/dev/ttyUSB0"

int main(int argc, char* argv[]){
	
	std::cout<<"Debut du prog"<<std::endl;
	
	LibSerial::SerialStream ardu;
	ardu.Open(PORT);
	ardu.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_115200);
	ardu.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
	
	pid_t pid;
	int* status=NULL;
	const char* s="1"; //strcpy(&s,"1");
	char so;
	int flag=0;
	printf("noow : \n");
	while(true){
		ardu.get(so);
		printf("now : %c\n",so);
		if(strcmp(s,&so)==0)
		{
			std::cout<<"FORK\n";
			pid=fork();
			if(pid==-1)
			{
				std::cout<<"Erreur\n";
			}
			if(pid==0)
			{
				std::cout<<"Go";
				char* hud;
				if(flag==0){
					hud="wmctrl -s 1";
					//hud="rhythmbox";
					//hud="vlc ~/Vidéos/dmt-shaun.avi.flv";
				}
				else{
					hud="wmctrl -s 0";
					//hud="rhythmbox";
					//hud="vlc ~/Vidéos/dmt-shaun.avi.flv";
				}
				//char* hud="cheese";
				std::cout << "JFQJHGQSFJHGQSF " << hud << "parce que flag "<< flag << std::endl;
				system(hud);
				std::cout<<"ENDFUCcccck\n";
				exit(0);
			}
			else
			{
				wait(&status);
				std::cout<<"DAMN\n";
				//sleep(5); Lis les instructions quand même, attend juste >>
				for(int i=0;i<30;i++)
				{
					ardu.get(so);
				}
				//On change le flag dans le pere.
				if (flag==1){
					flag=0;
				}
				else{
					flag=1;
				}
				
				
				so='1';
			}
		}
		else{
			std::cout << "RIIIIEEN "<< s << " "<< so << std::endl;
		 }
	}
	return 0;
}
