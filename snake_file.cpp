/*
All the functions are defined in this file
*/
#include "snake.h"

int snakeclass::stage=0;// static object to keep a track of stage number. For each stage, a new object is being created

food_val::food_val()// to initialise default bait position
{
	x=0;
	y=0;
}

food_val::food_val(int p,int q)// to initialise bait position with given values 
{
	x=p;
	y=q;
}


snakeclass::snakeclass(int pre_point,int high)// snakeclass constructor with two arguments i.e initial points at the start of stage and top score
{
	initscr();
	nodelay(stdscr,true);  //getch will not wait until user presses a key
	keypad(stdscr,true);
	noecho();
	curs_set(0);
	getmaxyx(stdscr,maxheight,maxwidth);

	snake_char='x';
	obst_char=(char)219;
	food_char='*';
	low_bound='-';
	food.x=0;
	food.y=0;

	for(int i=0;i<5;i++)
  	{
       		snake.push_back(std::make_pair(40+i,10));
   	}

	points=pre_point;
	temp=0;
	coll=0;
	del=110000;
	get=false;
	direction='l';
	srand(time(0));
	high_score=high;
	stage++;
}

snakeclass::~snakeclass()
{
	nodelay(stdscr,false);
	getch();
	endwin();
}

void snakeclass::putfood()
{
	while(1)
  	{
		int tmpx=rand()%maxheight+1;
		int tmpy=rand()%maxwidth+1;
		for(int i=0;i<snake.size();i++)
		{ 
			if( snake[i].first==tmpy && snake[i].second==tmpx)
 				continue;
	  	}
      		
      		for(int i=0;i<obst.size();i++)
          	{
            		if(obst[i].second==tmpy && obst[i].first==tmpx)
                		continue;
          	}

		if(tmpy>maxwidth-1 || tmpx > maxheight-3)
			continue;
	
		if(stage==2)
	 	{
			if(tmpy>maxwidth-2 || tmpx > maxheight-4)
                		continue;
	   	}
		
		food.x=tmpy;
		food.y=tmpx;
        	break;
    	}
	
	move(food.y,food.x);
	addch(food_char);
	refresh();
  
}

bool snakeclass::collision()
{
 	if((snake[0].first==0 && direction=='l')||(snake[0].first==maxwidth-1 && direction=='r') || (snake[0].second==0 &&direction=='u') || (snake[0].second== maxheight-3 && direction=='d'))
   	{
		temp=1;
    	}
  
  	for(int i=2; i<snake.size();i++)
    	{
		if(snake[0].first==snake[i].first && snake[0].second==snake[i].second)
             		return true;
    	}

   	for(int i=0;i<obst.size();i++)
    	{
    		if(snake[0].first==obst[i].second && snake[0].second==obst[i].first)
             		return true; 
       	}
     
	if(points%10==0 && points!=0)
	 {
	 	get=false;
	  }

   	if(snake[0].first==food.x && snake[0].second==food.y)
   	{
		get=true;
		putfood();
		points+=10;
		
		attron(A_BOLD);
		move(maxheight-1,0);
		printw("Your Score:%d",points);
		if(points > high_score)
		{
   			high_score=points;
  		}

		move(maxheight-1,maxwidth-17);
		printw("Top Score:%d",high_score);
		move(maxheight-1,maxwidth/2-4);
		printw("Stage %d",stage);
		attroff(A_BOLD);
		refresh();
		
		if(points%50 == 0)
 		{
			del-=8000;  
		}
		
		if(points%10!=0)
		{
			get=false;
		}

    	}
 	return false;
}

void snakeclass::movesnake()
{
  	int tmp=getch();
  	switch(tmp)
  	{
		case KEY_LEFT: if(direction!='r')
		  		direction='l';
				break;
		case KEY_RIGHT: if(direction!='l')
        	                    direction='r';
                	        break;
		case KEY_UP: if(direction!='d')
                	           direction='u';
                        	  break;
		case KEY_DOWN: if(direction!='u')
        	                    direction='d';
                	          break;
		case KEY_BACKSPACE:
				direction='q';
				  break;
    	}
        
        if(collision())
        {
		clear();
		attron(A_BOLD);
        	move(9,33);
        	printw("Game Over");
		move(11,31);
		printw("Your Score:%d",points);
		move(13,31);
		printw("Top Score:%d",high_score);
		attroff(A_BOLD);
        	refresh();
	  	coll=1;
        }

	if(coll!=1)
{   		if(!get)
     		{
			move(snake[snake.size()-1].second,snake[snake.size()-1].first);
			addch(' ');
			refresh();
			snake.pop_back();
       		}
     		else
      		{
			move(snake[snake.size()-1].second,snake[snake.size()-1].first);
        		addch(' ');
        		refresh();
			get=true; 
       		}

	 if(temp!=1)
  	{
    		if(direction=='l')
			snake.insert(snake.begin(),std::make_pair(snake[0].first-1,snake[0].second));
    		else if(direction=='r')
			snake.insert(snake.begin(),std::make_pair(snake[0].first+1,snake[0].second));
    		else if(direction=='u')
			snake.insert(snake.begin(),std::make_pair(snake[0].first,snake[0].second-1));
    		else if(direction=='d')
			snake.insert(snake.begin(),std::make_pair(snake[0].first,snake[0].second+1));
  
  	}
 	else
 	{

    		if(direction=='l')
      		{
         		snake.insert(snake.begin(),std::make_pair(maxwidth-1,snake[0].second));
      		}
    		else if(direction=='r')
       		{
          		snake.insert(snake.begin(),std::make_pair(0,snake[0].second));
       		}
    		else if(direction=='u')
       		{
          		snake.insert(snake.begin(),std::make_pair(snake[0].first,maxheight-3));
        	}
    		else if(direction=='d')
        	{
           		snake.insert(snake.begin(),std::make_pair(snake[0].first,0));
         	}

		temp=0;
  	}


    	move(snake[0].second,snake[0].first);
    	addch(snake_char);
    	refresh();
  
  }
}

void snakeclass::start()
{

	clear();
	nodelay(stdscr,false);
	move(7,31);
	attron(A_BOLD);
	addstr("SNAKE GAME");
	attroff(A_BOLD);
	move(9,22);
	addstr("Start : Press Home key to start");
	move(11,22);
	addstr("Exit : Press any other key to exit");
	refresh();
	echo();
	int p=getch();
	switch(p)
	{
		case KEY_HOME: 
			clear();
			stage1();
			break;

		default: break;

	}
}


void snakeclass::stage1()
{
	clear();
	move(11,36);
	attron(A_BOLD);
	addstr("STAGE 1");
	attroff(A_BOLD);
	getch();
	refresh();
	clear();

	for(int i=1;i<=3;i++)
	{
		move(i,10);
		addch(obst_char);
		obst.push_back(std::make_pair(i,10));
	}

	for(int i=1;i<=10;i++)
	{
		move(20,i+20);
		addch(obst_char) ;
		obst.push_back(std::make_pair(20,i+20));
	}

	for(int i=1;i<=3;i++)
	{
		move(i+9,50);
		addch(obst_char); 
		obst.push_back(std::make_pair(i+9,50));
	}


	refresh();
	nodelay(stdscr,true);

	for(int i=0;i<snake.size();i++)
	{
		move(snake[i].second,snake[i].first);
		addch(snake_char);
	}
	
	putfood();
	attron(A_BOLD);
	move(maxheight-1,0);
	printw("Your Score:%d",points);
	if(points > high_score)
	{
		high_score=points;
	}
	
	move(maxheight-1,maxwidth-17);
	printw("Top Score:%d",high_score);
	move(maxheight-1,maxwidth/2-4);
	printw("Stage %d",stage);
	attroff(A_BOLD);
	move(food.y,food.x);
	addch(food_char);
	refresh();

	for(int i=0;i<maxwidth;i++)
	{
        	move(maxheight-2,i);
     		addch(low_bound);
  	}
	refresh();
  
 	while(1)
  	{

		 if(coll==1)
   		{  
   			char poin[100],script[1024];
			sprintf(poin,"%d",points);
			strcpy(script,"/bin/bash script.sh ");
			strcat(script,poin);
			system(script);
	 		break;
       		}
   	
   		if(points==100)
		{
			clear();
			nodelay(stdscr,false);
			attron(A_BOLD);
			move(8,32);
			printw("Stage Cleared");
			move(11,32);
			printw("Your score:%d",points);
			getch();
			attroff(A_BOLD);
			nodelay(stdscr,true);
			snakeclass s1(points,high_score);
			s1.stage2();
			break;
		}
     		
     		movesnake();
 
		if(direction=='q')
        		break;

      		usleep(del);
 
       }
  
}

void snakeclass::stage2()
{
	clear();
	move(11,36);
	attron(A_BOLD);
	nodelay(stdscr,false);
	addstr("STAGE 2");
	attroff(A_BOLD);
	getch();
	refresh();
	clear();
	nodelay(stdscr,true);
	
	while(!obst.empty())
	{
		obst.pop_back();
	}

	for(int i=1;i<=3;i++)
	{
		move(i+11,20-i);
		addch(obst_char);
		obst.push_back(std::make_pair(i+11,20-i));
	}

	for(int i=1;i<=3;i++)
	{
		move(i+11,60+i);
		addch(obst_char);
		obst.push_back(std::make_pair(i+11,60+i));
	}

	for(int i=0;i<maxwidth/2-4;i++)
	{
		move(0,i);
		addch(obst_char);
		move(maxheight-3,i);
		addch(obst_char);
		obst.push_back(std::make_pair(0,i));
		obst.push_back(std::make_pair(maxheight-3,i));

	}

	for(int i=maxwidth/2+5;i<maxwidth;i++)
	{
		move(0,i);
		addch(obst_char);
		move(maxheight-3,i);
		addch(obst_char);
		obst.push_back(std::make_pair(0,i));
		obst.push_back(std::make_pair(maxheight-3,i));
	} 

	for(int i=0;i<maxheight/2-4;i++)
	{
		move(i,0);
		addch(obst_char);
		move(i,maxwidth-1);
		addch(obst_char);
		obst.push_back(std::make_pair(i,0));
		obst.push_back(std::make_pair(i,maxwidth-1));
	
	}

	for(int i=maxheight/2+5;i<=maxheight-3;i++)
	{
		move(i,0);
		addch(obst_char);
		move(i,maxwidth-1);
		addch(obst_char);
		obst.push_back(std::make_pair(i,maxwidth-1));
		obst.push_back(std::make_pair(i,0));
	}

	refresh();

	for(int i=0;i<snake.size();i++)
	{
		move(snake[i].second,snake[i].first);
		addch(snake_char);
	}

	putfood();
	attron(A_BOLD);
	move(maxheight-1,0);
	printw("Your Score:%d",points);
	move(maxheight-1,maxwidth-17);
	printw("Top Score:%d",high_score);
	move(maxheight-1,maxwidth/2-4);
	printw("Stage %d",stage);
	attroff(A_BOLD);
	move(food.y,food.x);
	addch(food_char);
	refresh();


	for(int i=0;i<maxwidth;i++)
	{
		move(maxheight-2,i);
        	addch(low_bound);
  	}

	while(1)
	{
		if(coll==1)
   		{
   			char poin[100],script[1024];
        		sprintf(poin,"%d",points);
        		strcpy(script,"/bin/bash script.sh ");
        		strcat(script,poin);
        		system(script);
			break;
       		}
        	
        	movesnake();

 		if(direction=='q')
		        break;

	        usleep(del);

        }

}
