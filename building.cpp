#include <iostream>
#include "building.h"
#include <cstdlib>
#include <ctime>

using namespace std;

/*###############VISITOR###################*/

 visitor::visitor(int fl,const int of):fl_num(fl), of_num(of){
 	cout<<"visitor created with floor number "<<fl_num<<" ,office number "<<of_num<<endl;
 		pr_num=0;
		isServed=false;	
 }
 
 visitor::~visitor(){
 	if(!isServed){
 		cout<<"I was not served :( .Order number:"<<pr_num<<" destination:"<<fl_num<<"-"<<of_num<<endl;
	 }
 }
 	int visitor::getpriority() {
		return pr_num;
	}
	void visitor::setpriority(int pr){
		pr_num=pr;
	}
	void visitor::gotserved(){
		isServed=true;
	}
	bool visitor::getisServed() {
		return isServed;
	}
 	int visitor::getfloor(){
 		return fl_num;
	 }
 	const int visitor::getoffice(){
 		return of_num;
	 }
/*########################################*/

/*################QUEUE###################*/

Queue::Queue(const int s):size(s){
	visitqueue=new visitor*[size];
	front=-1;
	back=-1;
}
Queue::~Queue(){
	delete[] visitqueue;
}
bool Queue::IsEmpty()
	{
		return (front == -1 && back == -1); 
	}
	
bool Queue::IsFull()
	{
		return (back+1)%size == front;
	}

void Queue::Push(visitor* v)
	{
		if(IsFull())
		{
			cout<<"Error: Queue is Full\n";
			return;
		}
		if (IsEmpty())
		{ 
			front = back = 0; 
		}
		else
		{
		    back = (back+1)%size;
		}
		visitqueue[back] = v;
	}
	
	visitor* Queue::Pop()
	{
		cout<<"Poping visitor "<<visitqueue[front]->getfloor()<<"-"<<visitqueue[front]->getoffice()<<" \n";
		if(IsEmpty())
		{
			cout<<"Error: Queue is Empty\n";
			return NULL;
		}
		else if(front == back ) 
		{
			visitor* v=visitqueue[front];
			back = front = -1;
			return v;
		}
		else
		{
			visitor* v=visitqueue[front]; 
			front = (front+1)%size;
			return v;
		}
	}
	
/*########################################*/

/*###############SPACE###################*/

Space::Space(int cap):capacity(cap){
}

Space::~Space(){
}


/*########################################*/


/*###############OFFICE###################*/

	office::office(const int fl, const int of,const int no) :fl_num(fl), of_num(of),Space(no){
		customers=new Queue(capacity);
		ocounter=0;
		cout << "Office number " << fl_num << "-" << of_num << " has been created" << endl;
	}
	office::~office() {
		delete customers;
		cout << "Office number " << fl_num << "-" << of_num << " has been destroyed" << endl;
	}
	void office::enter(visitor* v){								//a visitor enters an office and the office counter increases
		customers->Push(v);
		cout<<"visitor with destination "<<v->getfloor()<<"-"<<v->getoffice()<<" has entered office number: "<<fl_num<<"-"<<of_num<<endl;
		ocounter++;
	}
	visitor* office::exit(){					//a visitor leaves an office and the office counter decreases
		ocounter--;
		return	customers->Pop();	
	}
	
	bool office::isFull(){
		return ocounter==capacity;
	}
	int office::getocounter(){			//returns office counter
		return ocounter;
	}
	
/*########################################*/

/*#################LEVEL##################*/

Level::Level(int cap):Space(cap){
	
}

Level::~Level(){
	
}

int Level::getcounter(){
	return vcounter;
}

bool Level::isLvLFull(){
	return vcounter==capacity;
}

void Level::enter(visitor* v){
	entr->enter(v);
}

visitor* Level::exit(){
	return entr->exit();
}

void Level::enter(visitor** varray,int& voutside,int &bcounter){
}

void Level::exit(visitor* v){
}

visitor* Level::exit(int f){
}

/*########################################*/

/*###############ENTRANCE#################*/
Entrance::Entrance(int mcap):max_cap(mcap){
}
Entrance::~Entrance(){
	
}
void Entrance::enter(visitor* v){
}
void Entrance::enter(visitor** varray,int& voutside,int&gfcounter,bool grfull,int &bcounter){
}

visitor* Entrance::exit(){
}

visitor* Entrance::exit(int f){
}

bool Entrance::is_arr_empty(int f){
}
	
/*########################################*/	
	
/*###############WAITINGLOBBY###################*/
	
	wlobby::wlobby(const int fl,const int nf) :fl_num(fl),Entrance(nf) {
		wait_array=new Queue*[11];
		for(int i=0;i<11;i++){
			wait_array[i]=new Queue(max_cap);
		}
		cout<<"waiting lobby on floor " <<fl_num<<" has been created"<<endl<<endl;	
	}
	wlobby::~wlobby(){
		for(int i=0;i<11;i++){
			delete wait_array[i];
		}
		delete[] wait_array;
		cout<<"waiting lobby on floor " <<fl_num<<" has been destroyed"<<endl<<endl;
	}
	void wlobby::enter(visitor* v){					//a visitor enters the waiting lobby of a floor
		if(!v->getisServed()){						//if he is not served he will be placed in a queue for the office he wants
		int f=v->getoffice();
		wait_array[f]->Push(v);
		cout<<"visitor with destination "<<v->getfloor()<<"-"<<v->getoffice()<<" has entered floor number: "<<fl_num<<endl;
		}else{										//if he is served he will be placed in a "special" queue to return to the elevator
			wait_array[0]->Push(v);
			cout<<"A customer from office "<<fl_num<<"-"<<v->getoffice()<<" has been served"<<endl;
		}
	}
	
	visitor* wlobby::exit(int f){
		return wait_array[f]->Pop();
	}
	bool wlobby::is_arr_empty(int f){
		return wait_array[f]->IsEmpty();
	}
/*###############W##############################*/

/*###############GROUNDLOBBY###################*/

	groundlobby::groundlobby(const int ng):Entrance(ng){
		cout<<"waiting lobby on ground floor has been created"<<endl;
		cout<<"A queue in the ground floor has been created with length "<<max_cap<<endl;
		gf_queue=new Queue(max_cap);
		priority=1;
	}
	
	groundlobby::~groundlobby(){
		delete gf_queue;
		cout<<"The waiting lobby on ground floor has been destroyed"<<endl;
	}
	
	void groundlobby::enter(visitor** varray,int& voutside,int& gfcounter,bool grfull,int &bcounter ){		//a visitor enters the queue in the ground floor waiting lobby
			int i=0;
		if(!grfull){			
				for( i=0;!gf_queue->IsFull()&&voutside;i++){
				
					gf_queue->Push(varray[i]);
					cout<<"visitor with destination "<<varray[i]->getfloor()<<"-"<<varray[i]->getoffice()<<" has entered the building"<<endl;
					wait(varray[i]);	
					gfcounter++;
					voutside--;
					bcounter++;
				}
		}else{
			cout<<"Please wait outside"<<endl;
		}

	}
	
	void groundlobby::wait(visitor* groundvisiti){			//a visitor gets a priority number
			groundvisiti->setpriority(priority);
					priority++;
	}
	
	visitor* groundlobby::exit(){			// a visitor leaves the ground floor waiting queue
		return	gf_queue->Pop();
	}

/*###############W##############################*/

/*###############FLOOR###################*/

	floor::floor(const int fl,const int nf,const int no) :fl_num(fl),No(no),Level(nf) {
		vcounter=0;
		cout << "Floor number: " << fl_num <<" has been created"<< endl;
		ofarray=new office*[10];
		for(int i=0;i<10;i++){
			ofarray[i]=new office(fl_num,i+1,No);
		}
		entr= new wlobby(fl_num,capacity);
	}

	floor::~floor() {
		for(int i=0;i<10;i++){
			delete(ofarray[i]);
		}
		delete[] ofarray;
		delete entr;
		cout<<"Floor number: "<<fl_num<<" has been destroyed"<<endl<<endl;
	}

	
	void floor::floor_operate(int rem){									//visitors enter the offices,they get served randomly and then they return to the waiting lobby
		for(int i=0;i<10;i++){
			while(!ofarray[i]->isFull()&&!entr->is_arr_empty(i+1)){
				office_enter(entr->exit(i+1),i);
			}

			if(ofarray[i]->isFull()){
				cout<<"Office "<<fl_num<<i<<"is full.Please wait"<<endl;
			}
		}
		srand(time(0));
		visitor* served;
		for(int i=0;i<10;i++){
			int r=rand()%(rem/10);
			if(r<ofarray[i]->getocounter()){

				for(int j=0;j<r;j++){
					served=ofarray[i]->exit();
					served->gotserved();
					entr->enter(served);
				}
			}else{
				for(int j=0;j<ofarray[i]->getocounter();j++){
					served=ofarray[i]->exit();
					served->gotserved();
					entr->enter(served);
				}
			}
		}
	}
	
	void floor::enter(visitor* v){			//a visitor enters a floor
		entr->enter(v);
		vcounter++;
	}
	
	void floor::office_enter(visitor* v,int i){		//a visitor enters the requested lobby
		ofarray[i]->enter(v);
	}
	
	visitor* floor::exit(int f){				//a visitor leaves the floor
		vcounter--;
		return entr->exit(f);
	}
	

	bool floor::get_warray_isempty(int f){   //see if a waiting queue is empty
		return entr->is_arr_empty(f);
	}
	
/*######################################*/

/*###############GROUNDFLOOR###################*/

	Groundfloor::Groundfloor(int ng):Level(ng){			
		vcounter=0;
		entr=new groundlobby(capacity);
		cout<<"Ground floor has been created"<<endl; 
	}
	
	Groundfloor::~Groundfloor(){					
		delete entr;
		cout<<"Ground floor has been destroyed"<<endl<<endl;
	}

	
	void Groundfloor::enter(visitor **varray,int& voutside,int &bcounter){						//sends visitor int the ground floor waiting lobby
			entr->enter(varray,voutside,vcounter,isLvLFull(),bcounter); 
	}
	
	visitor* Groundfloor::exit(){					//gets a visitor from the ground floor waiting lobby
		vcounter--;						
		return entr->exit();
	}
	void Groundfloor::exit(visitor* v){					//a visitor has been served
		cout<<"I finally finished!!! .Order number: "<<v->getpriority()<<endl;
	}
/*######################################*/

/*###############ELEVATOR###################*/

	Elevator::Elevator(int Nel):Space(Nel){
		cout<<"A lift has been created"<<endl<<endl;
		elcounter=0;
		stoparray=new Queue*[5];
		for(int i=0;i<5;i++){
			stoparray[i]=new Queue(capacity);
		}
	}
	Elevator::~Elevator(){
		cout<<"No more ups and downs"<<endl;
		for(int i=0;i<5;i++){
			delete stoparray[i];
		}
		delete[] stoparray;
	}
	bool Elevator::checkelfull(){
		return elcounter==capacity;
	}
	
	int Elevator::getelcounter(){
		return elcounter;
	}
	
	void Elevator::enter(visitor* v){			//a visitor enters the elevator
		if(!v->getisServed()){					//if he is not served he enters a queue for the floor he wants to go to
			int f=v->getfloor();
			stoparray[f]->Push(v);
			cout<<"visitor with destination "<<v->getfloor()<<"-"<<v->getoffice()<<" has entered the elevator\n";
		}else{									//if he is served he enters a queue to leave to building
			stoparray[0]->Push(v);
			cout<<"A served customer has entered the elevator"<<endl<<endl;
		}
	}
	visitor* Elevator::el_exit(int stop){			//a visitor exits the elavator
		elcounter--;
		return stoparray[stop]->Pop();
	}
	void Elevator::stop_up(floor** flarray){		//the elevator goes up,leaving visitor at each floor
		for(int i=0;i<4;i++){
			while(!flarray[i]->isLvLFull()&&!stoparray[i+1]->IsEmpty()){
				flarray[i]->enter(el_exit(i+1));
			}
		}
	}
	void Elevator::stop_down(floor** flarray){		//the elevator goes down and served visitors from each floor get aboard
		for(int i=3;i>=0;i--){
			while(!flarray[i]->get_warray_isempty(0)&&!stoparray[0]->IsFull()){
				enter(flarray[i]->exit(0));
			}
		}
	}
	int Elevator::operate(floor** flarray,Groundfloor* groundfloor){		//stop up - call to start the floor operations-stop down-served visitors exit
		stop_up(flarray);
		cout<<endl;
		for(int i=0;i<4;i++){
			flarray[i]->floor_operate(capacity-elcounter);
		}
		stop_down(flarray);
		int c=0;
		while(!stoparray[0]->IsEmpty()){
			groundfloor->exit(stoparray[0]->Pop());
			c++;
		}
		return c;					//number of served visitors
	}
/*###########################################*/
/*###############BUILDING###################*/

	Building::Building(const int n,const int ng,const int nl,const int nf,const int no):Space(n),Ng(ng),Nl(nl),Nf(nf),No(no){
		groundfloor=new Groundfloor(Ng);
		elevator=new Elevator(Nl);
		flarray=new floor*[4];
		for(int i=0;i<4;i++){
			flarray[i]=new floor(i+1,Nf,No);
		}
		cout<<"A new building is ready for serving citizens!"<<endl;
		bcounter=0;
	}
	Building::~Building(){
		for(int i=0;i<4;i++){
			delete flarray[i];
		}
		delete[] flarray;
		delete elevator;
		delete groundfloor;
		cout<<"Service not available any longer.Go elsewhere!"<<endl;
	}
	bool Building::isFull(){
		return bcounter==capacity;
	}
	int Building::enter(visitor** varray,int voutside,int &bcounter){		//a visitor enters the building and is guided to the ground floor waiting lobby
		groundfloor->enter(varray,voutside,bcounter);
		return voutside;
	}
	void Building::enter(visitor* v){
	}
	
	void Building::el_enter(){										//visitors enter the elevator
		while(!elevator->checkelfull()&&getgfcounter()){
			elevator->enter( groundfloor->exit());
		}	
	}
	int Building::getgfcounter(){
		return groundfloor->getcounter();
	}
	int Building::getelcounter(){
		return elevator->getelcounter();
	}
	void Building::operate(int K,int L,visitor** varray){
	int voutside=K;
	int x;
	visitor** tempvarray=varray;
	for(int l=0;l<L;l++){						//elevator cycles
		if(voutside&&!isFull()){				//if there are visitor outside they enter the building
			x=voutside;
			cout<<x<<" visitors are outside"<<endl;
			voutside=enter(tempvarray,voutside,bcounter);
			cout<<x-voutside<<" visitors have entered  the building"<<endl;
			cout<<voutside<<"  visitors are waiting outside"<<endl;
			cout<<"There are "<<bcounter<<" in the building"<<endl<<endl;
			if(x!=voutside){
			tempvarray=tempvarray+x-voutside;
			}
		}else if(isFull()){
			cout<<"Building is full.Please come tomorrow"<<endl;
		}
				el_enter();						//call to get visitors into the elevator
		cout<<endl<<endl;
			int t=elevator->operate(flarray,groundfloor);		
			bcounter=bcounter-t;				//served visitors leave the building and the building counter is decreased
		}

	}
