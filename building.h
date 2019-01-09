#include<iostream>

/*###############VISITOR###################*/

class visitor {
private:
	int fl_num;
	const int of_num;
	int pr_num;
	bool isServed;
public:
	visitor(const int fl, const int of) ;
	~visitor() ;
	int getpriority() ;
	void setpriority(int pr);
	void gotserved();
	bool getisServed() ;
	int getfloor();
	const int getoffice();
};

/*########################################*/

/*#################QUEUE##################*/

class Queue
{
private:
	const int size;  
	visitor** visitqueue;
	int front, back; 
public:
	Queue(const int s);
	~Queue();
	bool IsEmpty();
	bool IsFull();
	void Push(visitor* v);
	visitor* Pop();
};

/*########################################*/

/*###############SPACE###################*/

class Space{
protected: 
	const int capacity;
public:
	Space(int cap);	
	~Space();
	virtual void enter(visitor* v)=0;
};



/*########################################*/

/*###############OFFICE###################*/

class office:public Space {
private:
	const int fl_num;
	const int of_num;
	int ocounter;
	Queue* customers;
public:
	office(const int fl, const int of,const int no);
	~office() ;
	void enter(visitor* v);
	visitor* exit();
	bool isFull();
	int getocounter();
};

/*########################################*/



class Entrance{
	protected:
	 const int max_cap;
	public:
		Entrance(int mcap);
		virtual ~Entrance();
		virtual void enter(visitor* v);
		virtual void enter(visitor** varray,int& voutside,int&gfcounter,bool grfull,int &bcounter);
		virtual visitor* exit();
		virtual visitor* exit(int f);
		virtual	bool is_arr_empty(int f);
};

class Level:public Space{
	protected:
		int vcounter;
		Entrance* entr;
	public:
		Level(int cap);
		virtual ~Level();
		virtual int getcounter();
		virtual bool isLvLFull();
		virtual void enter(visitor* v);
		virtual void enter(visitor** varray,int& voutside,int &bcounter);
		virtual visitor* exit();
		virtual void exit(visitor* v);
		virtual	visitor* exit(int f);
};




/*###############WAITINGLOBBY###################*/

class wlobby: public Entrance {
private:
	const int fl_num;
	Queue** wait_array;
public:
	wlobby(const int fl,const int nf) ;
	~wlobby();
	void enter(visitor* v);
	visitor* exit(int f);
	bool is_arr_empty(int f);
};

/*############################################*/
class groundlobby: public Entrance{
	private: 
		int priority;
		Queue* gf_queue;
	public:
		groundlobby(const int ng);
		~groundlobby();
		void enter(visitor** varray,int& voutside,int&gfcounter,bool grfull,int &bcounter);
		void wait(visitor*);
		visitor* exit();
};
/*###############GROUNDFLOOR###################*/

class Groundfloor:public Level{
	private:
		int priority;
		visitor* served;
	public:
		Groundfloor(const int ng);
		~Groundfloor();
		void enter(visitor** varray,int& voutside,int &bcounter);
		void exit(visitor* v);
		visitor* exit();
};

/*########################################*/

/*###############FLOOR###################*/
 
class floor: public Level {
private:
	const int No;
	const int fl_num;
	office** ofarray;
public:
	floor(const int fl,const int Nf,const int No);
	~floor();
	void floor_operate(int rem);
	void enter(visitor* v);
	void office_enter(visitor* v,int i);
	visitor* exit(int f);
	bool get_warray_isempty(int f);
};

/*########################################*/

/*###############ELEVATOR###################*/

class Elevator:public Space{
	private:
		int elcounter;
		Queue** stoparray;
	public:
		Elevator(int Nel);
		~Elevator();
		int getelcounter();
		bool checkelfull();
		void enter(visitor* v);
		visitor* el_exit(int stop);
		void stop_up(floor** flarray);
		void stop_down(floor** flarray);
		int operate(floor** flarray,Groundfloor* groundfloor);
};

/*########################################*/

/*###############BUILDING###################*/

class Building:public Space{
	private:
		const int Ng;
		const int Nl;
		const int Nf;
		const int No;
		int voutside;
		int bcounter;
		floor** flarray;
		Groundfloor* groundfloor;
		Elevator* elevator;
	public:
		Building(const int n,const int ng,const int nl,const int nf,const int no);
		~Building();
		int enter(visitor **varray,int voutside,int &bcounter);
		void enter(visitor* v);
		bool isFull();
		int getgfcounter();
		int getelcounter();
		void exit();
		void el_enter();
		void operate(int K,int L,visitor** varray);
};

/*########################################*/


		
