/*motors: 1red, 2green, 3blue, 4yellow
ports:	5 is (line0)(line1)(line2)(barcode)(blue yes/no)111
		0 is (LED1)(LED2)(LED3)(LED4)(actuator1)(actuator2)(distance)1
*/	

#include <robot_instr.h>
#include <robot_link.h>
#include <iostream>
#include <stopwatch.h>
#include <robot_delay.h>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

extern robot_link rlink;
extern int nextturn;

class State{
	public: 
		int route[8]; //series of turns
		int Parcel1; //0 = empty, 1 = A, 2 = B, 3 = C
		int Parcel2;
		int Delivered; //Delivery counter
		int mem[5]; //storage of 5 most recent "turns" from the line follower
		int location; //STA = 1; CON = 2; SL1 = 3; SL2 = 4; END = 5;
		int index; //current instruction no.
};

extern State samstate;

void linktorobot();
void write(int a, int b, int c, int d, int e, int f, int g, int h);
void read(int (&v)[8]);
void print(int v[8]);
void follow();
int align();
void turn(int t);
int speed(float s);
void junction();
void pivot(int p);
void scan();
void lost();
void LED();
void action();
void transit();
void park();
void pickup();
void dropoff();
