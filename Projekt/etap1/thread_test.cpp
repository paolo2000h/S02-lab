#include<pthread.h>
#include <ncurses.h>
#include<iostream>
#include<unistd.h>
#include<random>
#include<vector>
using namespace std;

//TODO
// - poprawic losowe punkty startowe
// - dodawac z lsoowym czasem samochody na drugi tor
// - sprawdzac czy pole jest zajete

//unsigned long seed = (unsigned long)(time(nullptr)); //ziarno do losowania
std::random_device seed;                          //ziarno do losowania
std::mt19937_64 rng(seed());                      //generator liczb losowych
std::uniform_int_distribution<int> randX(31,49);  //losowa pozycja [31,49] - sprawdzic
std::uniform_int_distribution<int> randY(3,21);   //losowa pozycja [3,21]
std::uniform_int_distribution<int> randY_2(1,2);  //niezuzywane
std::vector<Car> cars;                            //wektor samochodow na drugim torze 
std::vector<pthread_t> cars_threads;              //wektor watkow
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
	WIN_BORDER border;
}WIN;

void init_win_params(WIN *p_win,int height, int width);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);
points random_position();

class Car{
public:
    Car(points points,char sign){XY=points;index=sign;}
    ~Car(){};
    points getPoints(){return XY;};
    int getX(){return XY.x;};
    int getY(){return XY.y;};
    char getIndex(){return index;}
    int getCounter(){return loop_counter;}
    void setCounter(int counter){change_loop=counter;}
private:
    points XY;
    char index;
    int loop_counter=3;
    bool change_loop;
};

void *thread_function(void *arg){

    Car *incoming=(Car *)arg;
    int x = incoming->getX();
    int y=incoming->getY();
    char index = incoming->getIndex();
    while(true)
	{	usleep(50000);
       mvaddch(y,x,' ');
        if(y==3 && x<49){
        //right
       ++x;
   }else if(x==49 && y<21){
       // down
       ++y;
   }else if(y==21 && x>31){
       // left
       --x;
   }else if(x==31 && y>3){
       // up
       --y;
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
    while(loop>0)
	{	usleep(40000);
       mvaddch(y,x,' ');
        if(y==8 && x<60){
        //right
       ++x;
       //--loop;
   }else if(x==60 && y<16){
       // down
       ++y;
   }else if(y==16 && x>20){
       // left
       --x;
   }else if(x==20 && y>8){
       // up
       --y;
   }
   if(x==20 && y==8){--loop;}
   if(x==20 && y==16 && loop==1){break;}
   mvaddch(y,x,index);
    refresh(); 
   }

   return NULL;
}

int main(void){

    WIN win1;
    WIN win2;
    WIN win3;
    WIN win4;

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
	
	create_box(&win1, TRUE);
    create_box(&win2,TRUE);
    create_box(&win3, TRUE);
    create_box(&win4,TRUE);
    mvaddch(16,20,'8');
    mvaddch(16,31,'7');
    mvaddch(16,49,'6');
    mvaddch(16,60,'5');
    mvaddch(8,60,'4');
    mvaddch(8,49,'3');
    mvaddch(8,31,'2');
    mvaddch(8,20,'1');
   // mvaddch(3,31,'A');
    mvaddch(3,49,'B');
    mvaddch(21,49,'C');
    mvaddch(21,31,'D');
    

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
    start1.x=random_position().x;
    start1.y=random_position().y;
    //printw("X:%d Y:%d",start1.x,start1.y);
    mvprintw(1,0,"X:%d Y:%d",start1.x,start1.y);
    start2.x=random_position().x;
    start2.y=random_position().y;
    //printw("X:%d Y:%d",start2.x,start2.y);
    mvprintw(2,0,"X:%d Y:%d",start2.x,start2.y);
    start3.x=random_position().x;
    start3.y=random_position().y;
    //printw("X:%d Y:%d",start3.x,start3.y);
    mvprintw(3,0,"X:%d Y:%d",start3.x,start3.y);
    //refresh();
    start4.x=20;
    start4.y=8;
    


    Car car1(start1,'A');
    Car car2(start2,'B');
    Car car3(start3,'C');
    Car car4(start4,'1');
    pthread_create(&car1_t,NULL,thread_function,&car1);
    pthread_create(&car2_t,NULL,thread_function,&car2);
    pthread_create(&car3_t,NULL,thread_function,&car3);
    pthread_join(car1_t,&thread_result);
    pthread_join(car2_t,&thread_result);
    pthread_join(car3_t,&thread_result);

    // while(true){
    //     usleep(50000);
    //     cars.emplace_back(new Car)
    // }
    pthread_create(&car4_t,NULL,random_car,&car4);
    pthread_join(car4_t,&thread_result);
    endwin();
    return 0;
}

void init_win_params(WIN *p_win,int height, int width)
{
	p_win->height = height;
	p_win->width = width;
	p_win->starty = (LINES - p_win->height)/2;	
	p_win->startx = (COLS - p_win->width)/2;

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

void create_box(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

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

points random_position(){

    points pos;
    pos.x=0;
    pos.y=0;
    pos.x=randX(rng);
    while(pos.x!=49 && pos.x!=31 && pos.y!=3 && pos.y!=21 || pos.x==0 || pos.y==0)
    {
        pos.x=randX(rng);
        pos.y=randY(rng);
    }
    

    return pos;
}