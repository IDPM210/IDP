#include "idp.h"
#define ROBOT_NUM 13
robot_link rlink;
int nextturn;
State samstate;

int main(){
	linktorobot();
	//cout<<rlink.initialise(ROBOT_NUM);
	stopwatch watch;
	watch.start();
	rlink.command(WRITE_PORT_0, 7);
	int v[8];
	read(v);
	print(v);
	nextturn=0;
	for(int j=0;j<100;j--){
		follow();
	}
	cout<<"time per follow is "<<watch.read()/1000<<endl;
	samstate.Parcel1 = 0;
	samstate.Parcel2 = 0;
	samstate.Delivered = 0;
	samstate.location = 1;
	samstate.index = 0;
	action();
	while (samstate.location != 5) {
		transit();
	}
}

void read(int (&v)[8]){
	v[0]=rlink.request (READ_PORT_0);
	v[1]=rlink.request (READ_PORT_1);
	v[2]=rlink.request (READ_PORT_2);
	v[3]=rlink.request (READ_PORT_3);
	v[4]=rlink.request (READ_PORT_4);
	v[5]=rlink.request (READ_PORT_5);
	v[6]=rlink.request (READ_PORT_6);
	v[7]=rlink.request (READ_PORT_7);
}

void print(int v[8]){
	for(int i=0;i<8;i++){
		setfill(' ');
		cout<<setw(8)<<v[i];
	}
	cout<<endl;
}
	
void linktorobot(){
int val;                              // data from microprocessor
if (!rlink.initialise (ROBOT_NUM)) { // setup the link
  cout << "Cannot initialise link" << endl;
  rlink.print_errs("  ");
  //return -1;
}
val = rlink.request (TEST_INSTRUCTION); // send test instruction
if (val == TEST_INSTRUCTION_RESULT) {   // check result
  cout << "Test passed" << endl;
  //return 0;                            // all OK, finish
}
else if (val == REQUEST_ERROR) {
  cout << "Fatal errors on link:" << endl;
  rlink.print_errs();
}
else
  cout << "Test failed (bad value returned)" << endl;
//return -1;                          // error, finish
}


