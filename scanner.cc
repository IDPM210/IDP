#include "idp.h"

void scan(){
	float D, v, t;
	float space=v*t;
	int msrs=D/(2*space);	
	msrs=2*msrs; //msrs is total number of reading taken
	int white[2]={0};
	bool blue[2]={0};
	for (int box=0; box<2; box++){
		for(int i=0; i<msrs/2; i++){
			white[box]=white[box]+8&rlink.request(READ_PORT_5);
			if(i==msrs/4){
				blue[box]=32&rlink.request(READ_PORT_5);
			}			
		}
	}
	if(white[0]>10){
		if(blue[0]){
			samstate.Parcel1=1;
		}
		else{
			samstate.Parcel1=3;
		}
	}
	else{
		samstate.Parcel1=2;
	}
	if(white[1]>10){
		if(blue[1]){
			samstate.Parcel1=1;
		}
		else{
			samstate.Parcel1=3;
		}
	}
	else{
		samstate.Parcel1=2;
	}
}

void LED(){
	int current = rlink.request(READ_PORT_0);
	rlink.command(WRITE_PORT_0, (samstate.Parcel1+4*samstate.Parcel2)|(current&240));
}
