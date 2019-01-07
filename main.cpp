#include<iostream>
#include"building.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc,char* argv[]){
	const int N=atoi(argv[1]);
	cout<<"Building capacity is: "<<N<<endl;
	const int Nf=atoi(argv[2]);
	if(Nf >= N/3){
		cout<<"Invalid capacities.Please try again";
		return -1;	
	}
	cout<<"Floor capacity is: "<<Nf<<endl;
	const int Ng=atoi(argv[3]);
	if(Ng>=N/2){
		cout<<"Invalid capacities.Please try again";
		return -1;	
	}
	cout<<"Ground floor capacity is: "<<Ng<<endl;
	const int No=atoi(argv[4]);
	if(No >= Nf){
		cout<<"Invalid capacities.Please try again";
		return -1;	
	}
	cout<<"Office capacity is: "<<No<<endl;
	const int Nl=atoi(argv[5]);
	if(Nl <= No||Nl>Ng){
		cout<<"Invalid capacities.Please try again";
		return -1;	
	}
	cout<<"Elevator capacity is: "<<Nl<<endl;
	const int K=atoi(argv[6]);
	cout<<"There are "<<K<<" visitors"<<endl;
	const int L=atoi(argv[7]);
	cout<<"The elevator will make "<<L<<" cycle(s)"<<endl<<endl;;
	
	visitor** varray=new visitor*[K];
	
	int i;
	srand(time(0));
	for(i=0;i<K;i++){
		int fl_num=rand()%4+1;
		int of_num=rand()%10+1;
		varray[i]=new visitor(fl_num,of_num);
	
	}
	cout<<endl;
	
	Building building(N,Ng,Nl,Nf,No);		//a building is created
	
	building.operate(K,L,varray);        //the simulation starts

	cout<<endl;

	for(i=0;i<K;i++){
		delete varray[i];
	}
	delete[] varray;
	cout<<endl;
}
