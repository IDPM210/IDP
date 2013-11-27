void action() { //Takes current location & parcels, decides next route to take
	samstate.index = 0;
	switch(samstate.location) {
		case 1: //START
		if (samstate.Delivered < 4) { //To conveyor
			//int route[] = {1, 0, 0, 0, -1, 1, 5, 0};
			samstate.route = {1, 0, 0, 0, -1, 1, 5, 0};
			samstate.location = 2;
		}
		else { //END case
			samstate.location = 5;
		}
		break;
		
		case 2: //CONVEYOR
		if ((samstate.Parcel1 == 0) && (samstate.Parcel2 == 0)) { //If no parcels, park
			int samstate.route[] = {5};
			samstate.location = 2;
		}
		else if (samstate.Parcel1 == 1) || (samstate.Parcel1 == 2) || (samstate.Parcel2 == 1) || (samstate.Parcel2 == 2) { //A or B to SL1
			samstate.route = [-1, 1, 5];
			samstate.location = 3;
		}
		else if (samstate.Parcel1 == 3) || (samstate.Parcel2 == 3) { //C to SL3
			samstate.route = [-1, 0, 1, 5];
			samstate.location = 4;
		}
		break;
		
		case 3: //SLEIGH 1
		if (samstate.Parcel1 == 0) && (samstate.Parcel2 == 0) && (samstate.Delivered < 4) { //If no parcels, to conveyor
			samstate.route = [1, -1, 5];
			samstate.location = 2;
		}
		else if (samstate.Delivered >= 4) { //Return to start if 4 or more delivered
			samstate.route = [-1, 0, 0, -1, 5];
			samstate.location = 1;
		}
		else if (samstate.Parcel1 == 3) || (samstate.Parcel2 == 3) { //C to SL3
			samstate.route = [-1, 1, 5];
			samstate.location = 4;
		}
		break;
		
		case 4: //SLEIGH 2
		if (samstate.Parcel1 == 0) && (samstate.Parcel2 == 0) && (samstate.Delivered < 4) { //If no parels, to conveyor
			samstate.route = [1, -1, 5];
			samstate.location = 2;
		}
		else if (samstate.Delivered >= 4) { //Return to start if 4 or more delivered
			samstate.route = [-1, 0, -1, 5];
			samstate.location = 1;
		}
		else if (samstate.Parcel1 == 1) || (samstate.Parcel1 == 2) || (samstate.Parcel2 == 1) || (samstate.Parcel2 == 2) { //A or B to SL1
			samstate.route = [-1, 1, 5];
			samstate.location = 3;
		}
		break;
		
		case 5: //END
		break;
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
}

void pickup() {
	// signal parcel with LED
	// scan barcode of first
	// identify and store as parcel1
	// scan barcode of second
	// identify and store as parcel2
	// sweep in parcel2
	// sweep in parcel1
}

void dropoff() {
	//check location and parcel types
	//if parcel1 = location parcel, sweep off
	//ditto for parcel2
}
