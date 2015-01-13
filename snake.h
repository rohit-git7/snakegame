#include<iostream>
#include<ncurses.h>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cstring>
#include<fcntl.h>
struct food_val
{
int x,y;
food_val();
food_val(int,int);
};

class snakeclass
{
  int points,temp,coll,del,maxwidth,maxheight,high_score;
  char direction,snake_char,obst_char,food_char,low_bound;
  bool get;
  food_val food;
  std::vector<std::pair<int,int> > snake;
  void putfood();
  std::vector<std::pair<int,int> > obst;
  bool collision();
  void movesnake();
 
 
 public:
 static int stage;
  snakeclass(int,int);
  snakeclass(int);
  ~snakeclass();
  void start();
  void stage1();  
  void stage2();  

};
