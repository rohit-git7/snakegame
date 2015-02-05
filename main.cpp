/*
main.cpp

*/
#include "snake.h"

int main()
{

 	char buff[10];
 	int i=0,n;
	long long int sum=0;
	int fd=open("high.txt",O_RDONLY);// reading top score from file high.txt
	n=read(fd,buff,1024);
	while(i < n-1)
	{
 		sum= sum*10 +buff[i]-'0';
 		i++;
 	}
 	
 	close(fd);
  	//create object of class snakeclass and pass two arguments i.e initial score and top score
  	//This will initialise all variables and curses library
 	snakeclass s(0,sum);
 	s.start();// call start function
 	return 0;
}
