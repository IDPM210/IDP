void action() { //Takes current location & parcels, decides next route to take
		samstate.index = 0;
	switch(samstate.location) {
		case 1: //START
		if (samstate.Delivered < 4) { //To conveyor
			int route[] = {1, 0, 0, 0, -1, 1, 5, 5};
			samstate.location = 2;
		}
		else { //END case
			int route[] = {5, 5, 5, 5, 5, 5, 5, 5};
			samstate.location = 5;
		}
		break;
		
		case 2: //CONVEYOR
		if ((samstate.Parcel1 == 0) && (samstate.Parcel2 == 0)) { //If no parcels, park
			int route[] = {5, 5, 5, 5, 5, 5, 5, 5};
			samstate.location = 2;
		}
		else if (samstate.Parcel1 == 1) || (samstate.Parcel1 == 2) || (samstate.Parcel2 == 1) || (samstate.Parcel2 == 2) { //A or B to SL1
			int route[] = {-1, 1, 5, 5, 5, 5, 5, 5};
			samstate.location = 3;
		}
		else if (samstate.Parcel1 == 3) || (samstate.Parcel2 == 3) { //C to SL3
			int route[] = {-1, 0, 1, 5, 5, 5, 5, 5};
			samstate.location = 4;
		}
		break;
		
		case 3: //SLEIGH 1
		if (samstate.Parcel1 == 0) && (samstate.Parcel2 == 0) && (samstate.Delivered < 4) { //If no parcels, to conveyor
			int route[] = {1, -1, 5, 5, 5, 5, 5, 5};
			samstate.location = 2;
		}
		else if (samstate.Delivered >= 4) { //Return to start if 4 or more delivered
			int route[] = {-1, 0, 0, -1, 5, 5, 5, 5};
			samstate.location = 1;
		}
		else if (samstate.Parcel1 == 3) || (samstate.Parcel2 == 3) { //C to SL3
			int route[] = {-1, 1, 5, 5, 5, 5, 5, 5};
			samstate.location = 4;
		}
		break;
		
		case 4: //SLEIGH 2
		if (samstate.Parcel1 == 0) && (samstate.Parcel2 == 0) && (samstate.Delivered < 4) { //If no parels, to conveyor
			int route[] = {1, -1, 5, 5, 5, 5, 5, 5};
			samstate.location = 2;
		}
		else if (samstate.Delivered >= 4) { //Return to start if 4 or more delivered
			int route[] = {-1, 0, -1, 5, 5, 5, 5, 5};
			samstate.location = 1;
		}
		else if (samstate.Parcel1 == 1) || (samstate.Parcel1 == 2) || (samstate.Parcel2 == 1) || (samstate.Parcel2 == 2) { //A or B to SL1
			int route[] = {-1, 1, 5, 5, 5, 5, 5, 5};
			samstate.location = 3;
		}
		break;
		
		case 5: //END
		break;
	}
	for(int i=0; i<8; i++) {
		if (route[i] >= -1) && (route[i] <= 1) {
			samstate.location[i] = route[i];
		}
		else {
			samstate.location[i] = 5;
		}
	}
	return;
}
	return;
}

void transit() {
	nextturn = samstate.route[samstate.index];
	while (nextturn != 5) {
		follow();
	}
	if (samstate.location != 1) {
		park();
	}
	action();
}

void park() {
	// use slow version of follow?
	// step one follow, check distance sensor, step again, until distance sensor is all like 'nah mate'
	// port 0, pin 7 is distance sensor
	// park then leads to pickup/dropoff?
	// then deparks by reversing until line follow is all 'YO A LINE'
	int nextturn = 0;
	while (DISTANCE_SENSOR < VALUE) {
		follow();
		delay(10);
	}
	if (samstate.location == 2) {
		pickup();
	}
	else if (samstate.location == 3) || (samstate.location == 4) {
		dropoff();
	}
}

void pickup() {
	// signal parcel with LED
	LED();
	// scan barcode of first
	// identify and store as parcel1
	// scan barcode of second
	// identify and store as parcel2
	scan();
	// sweep in parcel2
	// sweep in parcel1
}

void dropoff() {
	if ((samstate.Parcel1 == 1) || (samstate.Parcel1 == 2)) && (samstate.location == 3) {
		PUSH_OUT_PARCEL_1;
	}
	else if ((samstate.Parcel2 == 1) || (samstate.Parcel2 == 2)) && (samstate.location == 3) {
		PUSH_OUT_PARCEL_2;
	}
	else if (samstate.Parcel1 == 3) && (samstate.location == 4) {
		PUSH_OUT_PARCEL_1;
	}
	else if (samstate.Parcel2 == 3) && (samstate.location == 3) {
		PUSH_OUT_PARCEL_2;
	}
}
