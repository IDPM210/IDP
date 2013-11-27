#include "idp.h"

void follow(){
	int a = align();
	switch (a){
		case 0: cout<<"lost!";
			lost();
			break;
		case 1: cout<<"hard left";
			turn(-2);
			break;
		case 2: cout<<"all good";
			turn(0);
			break;
		case 3: cout<<"left";
			turn(-2);
			break;
		case 4: cout<<"hard right";
			turn(2);
			break;
		case 5: cout<<"what is even going on";
			break;
		case 6: cout<<"right";
			turn(1);
			break;
		case 7: cout<<"junction time! pivot "<<nextturn;
			pivot(nextturn);
			// samstate.index = samstate.index + 1;
			// nextturn = samstate.route[samstate.index];
			break;
		default: cout<<"'align' totally wrong";
			break;
	}
	for(int i=5; i>0; i--){
		samstate.mem[i]=samstate.mem[i-1];
	}
	samstate.mem[0]=a;
	cout<<endl;
}

int align(){
	return 7&rlink.request (READ_PORT_5);
}

void pivot(int p){
	if(p==0);
	else{
		rlink.command(BOTH_MOTORS_GO_OPPOSITE, speed(0.5));
		delay(3000);
		rlink.command(BOTH_MOTORS_GO_SAME, speed(0.5*p));
		delay(2000);
		while(align()==0){
			rlink.command(BOTH_MOTORS_GO_SAME, speed(0.5*p));
		}
	}
}

void turn(int t){
	float s=0.15*t; //coefficient is gain
	rlink.command(MOTOR_1_GO, speed(0.7+s)); //left
	rlink.command(MOTOR_2_GO, speed(-0.72+s)); //right
}

int speed(float sp){
	if(sp>=0 && sp<=1){
		return sp*127;
	}
	if(sp>1){
		return 127;
	}
	if(sp<0 && sp>=-1){
		return -sp*127+128;
	}
	if(sp<-1){
		return 255;
	}
}

void lost(){
	cout<<samstate.mem[0]<<samstate.mem[1]<<endl;
	rlink.command(BOTH_MOTORS_GO_SAME, 0);
	if(samstate.mem[0]==4){
		while(align()==0){
			rlink.command(BOTH_MOTORS_GO_SAME, speed(0.5));
			cout<<"lost turn right"<<endl;
		}
	}
	if(samstate.mem[0]==1){
		while(align()==0){
			rlink.command(BOTH_MOTORS_GO_SAME, speed(-0.5));
			cout<<"lost turn left"<<endl;
		}
	}
	delay(200);
}
