#include "snake.h"

int main()
{

 	char buff[10];
  int i=0,n;
  long long int sum=0;
  int fd=open("high.txt",O_RDONLY);
  n=read(fd,buff,1024);
  while(i < n-1)
  {
    sum= sum*10 +buff[i]-'0';
    i++;
  }
  close(fd);
  
  snakeclass s(sum);
  s.start();
  return 0;
}
