#include<pthread.h>
#include <ncurses.h>
#include<iostream>
#include<unistd.h>
#include<random>
#include<vector>
using namespace std;

//TODO
// - poprawic losowe punkty startowe DONE
// - dodawac z lsoowym czasem samochody na drugi tor
// - sprawdzac czy pole jest zajete
// - wspolrzedne maja zalezec od szerokosci okna DONE

//unsigned long seed = (unsigned long)(time(nullptr)); //ziarno do losowania
std::random_device seed;                          //ziarno do losowania
std::mt19937_64 rng(seed());                      //generator liczb losowych
std::uniform_int_distribution<int> randX(31,49);  //losowa pozycja [31,49] - sprawdzic
std::uniform_int_distribution<int> randY(3,21);   //losowa pozycja [3,21]
std::uniform_int_distribution<int> randY_2(1,2);  //niezuzywane
//std::vector<Car> cars;                            //wektor samochodow na drugim torze 
//std::vector<pthread_t> cars_threads;              //wektor watkow
int numberOfCars=10;                              //liczba samochodow

struct points
{
    int x;
    int y;
};
typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
    int a, b, c,  d;
    int tab_y[4];
    int tab_x[4];
	WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win,int height, int width);
void print_win_params(WIN *p_win);
void create_box1(WIN *win, bool flag);
void create_box2(WIN *win, bool flag);
points random_position(int index);
    WIN win1;
    WIN win2;
    WIN win3;
    WIN win4;

class Car{
public:
    Car(points points,char sign,int sp){XY=points;index=sign;speed=sp;}
    ~Car(){};
    points getPoints(){return XY;};
    int getX(){return XY.x;};
    int getY(){return XY.y;};
    char getIndex(){return index;}
    int getCounter(){return loop_counter;}
    void setCounter(int counter){change_loop=counter;}
    int getSpeed(){return speed;}

private:
    points XY;
    char index;
    int loop_counter=3;
    bool change_loop;
    int speed; //todo
};

void *thread_function(void *arg){

    Car *incoming=(Car *)arg;
    int x = incoming->getX();
    int y=incoming->getY();
    char index = incoming->getIndex();
    chtype next_char = mvinch(y,x);
    while(true)
	{	usleep(80000);
       mvaddch(y,x,' ');
        if(y==win1.tab_y[0] && x<win1.tab_x[1]){
        //right
       ++x;
       next_char = mvinch(y,x);
       if(next_char!=' '){--x;}
   }else if(x==win1.tab_x[1] && y<win1.tab_y[2]){
       // down
       ++y;
       next_char = mvinch(y,x);
       if(next_char!=' '){--y;}
   }else if(y==win1.tab_y[2] && x>win1.tab_x[3]){
       // left
       --x;
       next_char = mvinch(y,x);
       if(next_char!=' '){++x;}
   }else if(x==win1.tab_x[3] && y>win1.tab_y[0]){
       // up
       --y;
       next_char = mvinch(y,x);
       if(next_char!=' '){++y;}
   }
   mvaddch(y,x,index);
    refresh(); 
   }

   return NULL;
}

void *random_car(void *arg){

    Car *incoming=(Car *)arg;
    int x = incoming->getX();
    int y=incoming->getY();
    char index = incoming->getIndex();
    int loop = incoming->getCounter();
    chtype next_char = mvinch(y,x);
    int speed = incoming->getSpeed();
    
    while(loop>0)
	{	usleep(speed);
       mvaddch(y,x,' ');
        if(y==win2.tab_y[0] && x<win2.tab_x[1]){
        //right
       ++x;
       next_char = mvinch(y,x);
       if(next_char!=' '){--x;}
       //--loop;
   }else if(x==win2.tab_x[1] && y<win2.tab_y[2]){
       // down
       ++y;
       next_char = mvinch(y,x);
       if(next_char!=' '){--y;}
   }else if(y==win2.tab_y[2] && x>win2.tab_x[3]){
       // left
       --x;
       next_char = mvinch(y,x);
       if(next_char!=' '){++x;}
   }else if(x==win2.tab_x[3] && y>win2.tab_y[0]){
       // up
       --y;
       next_char = mvinch(y,x);
       if(next_char!=' '){++y;}
   }
   if(x==win2.tab_x[3] && y==win2.tab_y[3]){--loop;}
   //if(x==20 && y==16 && loop==1){break;}
   mvaddch(y,x,index);
    refresh(); 
   }
   mvaddch(y,x,' ');
   refresh(); 

   return NULL;
}

int main(void){

    

    initscr();			/* Start curses mode 		*/
	start_color();			/* Start the color functionality */
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
    curs_set(0);

	/* Initialize the window parameters */
	init_win_params(&win1,20,20);
    init_win_params(&win2,10,42);
    init_win_params(&win3,16,16);
    init_win_params(&win4,6,38);
	print_win_params(&win1);
    
	attron(COLOR_PAIR(1));
	printw("Press F1 to exit");
	refresh();
	attroff(COLOR_PAIR(1));
	
	create_box1(&win1, TRUE);
    create_box2(&win2,TRUE);
    create_box1(&win3, TRUE);
    create_box1(&win4,TRUE);


    for(int i=win2.tab_x[0];i<win2.tab_x[1];i++){mvaddch(win2.tab_y[0],i,' ');}
    for(int i=win2.tab_x[0];i<win2.tab_x[1];i++){mvaddch(win2.tab_y[2],i,' ');}
    for(int i=win1.tab_y[0];i<win1.tab_y[3];i++){mvaddch(i,win1.tab_x[0],' ');}
    for(int i=win1.tab_y[1];i<win1.tab_y[2];i++){mvaddch(i,win1.tab_x[1],' ');}
    refresh();
    

    

    std::uniform_int_distribution<int> randXX(win1.tab_x[0],win1.tab_x[1]);  //losowa pozycja [31,49] - sprawdzic
    std::uniform_int_distribution<int> randYY(win1.tab_y[0],win1.tab_y[2]); 
    std::uniform_int_distribution<int> randomSpeed(40000,100000);   //losowa pozycja [3,21]
    std::uniform_int_distribution<int> randomSleep(1,10);
    randX=randXX;
    randY=randYY;
//     mvaddch(16,20,'8');
//     mvaddch(16,31,'7');
//     mvaddch(16,49,'6');
//     mvaddch(16,60,'5');
//     mvaddch(8,60,'4');
//     mvaddch(8,49,'3');
//     mvaddch(8,31,'2');
//     mvaddch(8,20,'1');
//    // mvaddch(3,31,'A');
//     mvaddch(3,49,'B');
//     mvaddch(21,49,'C');
//     mvaddch(21,31,'D');
//     mvaddch(12,40,'Y');
    //   mvaddch(win2.starty+1,win2.startx+1,'1');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+1,'4');
    //   mvaddch(win2.starty+1,win2.startx+win2.width-1,'2');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+win2.width-1,'3');
    //  mvaddch(win2.tab_y[0],win2.tab_x[0],'1');
    //  mvaddch(win2.tab_y[1],win2.tab_x[1],'2');
    //  mvaddch(win2.tab_y[2],win2.tab_x[2],'3');
    //  mvaddch(win2.tab_y[3],win2.tab_x[3],'4');
    //  mvaddch(win2.tab_y[1],win2.tab_x[3],'Z');
    pthread_t car1_t;
    pthread_t car2_t;
    pthread_t car3_t;
    pthread_t car4_t;
    void *thread_result;
    int value,value2;
    value=42;
    value2=30;
    points start1,start2,start3,start4;
    // start.x=31;
    // start.y=3;
    // start2.x=49;
    // start2.y=3;
    start1.x=random_position(1).x;
    start1.y=random_position(1).y;
    //printw("X:%d Y:%d",start1.x,start1.y);
    //mvprintw(1,0,"X:%d Y:%d",start1.x,start1.y);
    start2.x=random_position(2).x;
    start2.y=random_position(2).y;
    //printw("X:%d Y:%d",start2.x,start2.y);
    //mvprintw(2,0,"X:%d Y:%d",start2.x,start2.y);
    start3.x=random_position(3).x;
    start3.y=random_position(3).y;
    //printw("X:%d Y:%d",start3.x,start3.y);
    //mvprintw(3,0,"X:%d Y:%d",start3.x,start3.y);
    //refresh();
    start4.x=win2.tab_x[0];
    start4.y=win2.tab_y[0];
    //start1.x=win1.tab_x[0];
    //start1.y=win1.tab_y[0];
    

    int speed =80000;
    Car car1(start1,'A',speed);
    Car car2(start2,'B',speed);
    Car car3(start3,'C',speed);
    Car car4(start4,'1',speed);

std::vector<Car> cars; 
std::vector<pthread_t> cars_threads; 

for(int i=0;i<10;i++){
        pthread_t car_n_thread;
        points start_n;
        char j = i+'0';
        start_n.x=win2.tab_x[0];
        start_n.y=win2.tab_y[0];  
        //Car car_new(start_n,j);
        cars.emplace_back(Car(start_n,j,randomSpeed(rng)));
        cars_threads.emplace_back(car_n_thread);
}

    
     pthread_create(&car1_t,NULL,thread_function,&car1);
     //sleep(1);
     pthread_create(&car2_t,NULL,thread_function,&car2);
     //sleep(1);
     pthread_create(&car3_t,NULL,thread_function,&car3);
     //sleep(1);
    //pthread_create(&car4_t,NULL,random_car,&car4);
    //sleep(1);
     //pthread_join(car1_t,&thread_result);
    // sleep(1);
     //pthread_join(car2_t,&thread_result);
    // sleep(1);
     //pthread_join(car3_t,&thread_result);
    // sleep(1);
    //pthread_join(car4_t,&thread_result);
    // sleep(1);

    for(int i=0;i<cars.size();i++){
        //mvprintw(4,0,"Rozmiar: %d",cars.size());
        if(i==9){i=0;}
        pthread_create(&(cars_threads.at(i)),NULL,random_car,&(cars.at(i)));
        //pthread_join(cars_threads.at(i),&thread_result);
        //usleep(100000);
        sleep(randomSleep(rng));
    }
    pthread_join(car1_t,&thread_result);
    // sleep(1);
     pthread_join(car2_t,&thread_result);
    // sleep(1);
     pthread_join(car3_t,&thread_result);
    // sleep(1);
    

    //int numb=1;
    // while(true){
        
    //     //if(numb<10)
    //     //numb++;
    //     //else numb=0;
    //     p
    //     pthread_create(&car_n_thread,NULL,random_car,&car_new);
    //     //cars_threads.emplace_back()
    //     //cars.emplace_back(new Car())
    //     pthread_join(car_n_thread,&thread_result);
    //     usleep(100000);
    // }
    endwin();
    return 0;
}

void init_win_params(WIN *p_win,int height, int width)
{
	p_win->height = height;
	p_win->width = width;
	p_win->starty = (LINES - p_win->height)/2;	
	p_win->startx = (COLS - p_win->width)/2;
   // p_win->a=
    //mvprintw(4,0,"X:%d Y:%d",p_win->startx,p_win->starty);

	p_win->border.ls = '|';
	p_win->border.rs = '|';
	p_win->border.ts = '-';
	p_win->border.bs = '-';
	p_win->border.tl = '+';
	p_win->border.tr = '+';
	p_win->border.bl = '+';
	p_win->border.br = '+';
    
    

}
void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
				p_win->width, p_win->height);
	refresh();
#endif
}

void create_box1(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;
    p_win->tab_y[0]=y+1; //ok
    p_win->tab_y[3]=y+w-1;
    p_win->tab_y[1]=y+1; //ok
    p_win->tab_y[2]=y+w-1; 
    p_win->tab_x[0]=x+1; //ok
    p_win->tab_x[3]=x+1;
    p_win->tab_x[1]=x+h-1; 
    p_win->tab_x[2]=x+h-1; 
    // mvaddch(win2.starty+1,win2.startx+1,'1');
    //    mvaddch(win2.starty+win2.width-1,win2.startx+1,'4');
    //   mvaddch(win2.starty+1,win2.startx+win2.height-1,'2');
    //   mvaddch(win2.starty+win2.width-1,win2.startx+win2.height-1,'3');
    // mvaddch(win2.starty+1,win2.startx+1,'1');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+1,'4');
    //   mvaddch(win2.starty+1,win2.startx+win2.width-1,'2');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+win2.width-1,'3');


	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

void create_box2(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;
    p_win->tab_y[0]=y+1; 
    p_win->tab_y[1]=y+1;
    p_win->tab_y[2]=y+h-1; 
    p_win->tab_y[3]=y+h-1; 
    p_win->tab_x[0]=x+1; 
    p_win->tab_x[1]=x+w-1;
    p_win->tab_x[2]=x+w-1; 
    p_win->tab_x[3]=x+1; 
    // mvaddch(win2.starty+1,win2.startx+1,'1');
    //    mvaddch(win2.starty+win2.width-1,win2.startx+1,'4');
    //   mvaddch(win2.starty+1,win2.startx+win2.height-1,'2');
    //   mvaddch(win2.starty+win2.width-1,win2.startx+win2.height-1,'3');
    // mvaddch(win2.starty+1,win2.startx+1,'1');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+1,'4');
    //   mvaddch(win2.starty+1,win2.startx+win2.width-1,'2');
    //   mvaddch(win2.starty+win2.height-1,win2.startx+win2.width-1,'3');


	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

points random_position(int index){

    points pos;
    pos.x=0;
    pos.y=0;
    pos.x=randX(rng);
    do
    {
        pos.y=randY(rng);
        pos.x=randX(rng);
        //if(pos.x==win1.tab_x[1] || pos.x==win1.tab_x[0]){break;}
        
        //usleep(500000);
        mvprintw(index,0,"%d: X:%d Y:%d",index,pos.x,pos.y);
        refresh();
    
    }while(pos.x!=win1.tab_x[1] && pos.x!=win1.tab_x[0] );//&& pos.y!=win1.tab_y[0] && pos.y!=win1.tab_y[2]);

    return pos;
}