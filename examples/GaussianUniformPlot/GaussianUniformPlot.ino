#include <Gaussian.h>
void setup() {
	Serial.begin(9600);
	Serial.println("\n\nStarting Random Gaussian Distribuition...");
	delay(20);
	randomSeed(analogRead(0));
}

// The number of "slots" to record the hits of gaussian random
#define SIZE 26

// How many characters will have, in width?
#define BAR_SIZE 40

void loop() {
	Gaussian gaus = Gaussian(0, 15);
	long zero = SIZE/2 - gaus.mean;  
	long hits[SIZE] = {0};

	// Zero the array
	for(int i = 0; i < SIZE; i++)
		hits[i] = 0;

	// Print Header (0% ------------- 100%)
	Serial.print("0% ");

	for(int i = 3; i < BAR_SIZE - 5; i++)
		Serial.print("-");

	Serial.println(" 100%");

	// Process the gaussians and calculate the Y for each X
	int lastStep = 0, step;
	for(int i = 0; i < SIZE; i++){
		step = (double)(i+1)/SIZE*BAR_SIZE;
		if(step > lastStep){
			while(lastStep < step){
				Serial.print("=");
				lastStep++;
			}
		}

		hits[i] = gaus.plot(i-zero)*1000;

	}
	Serial.print(" END!\n");

	// Just to scale the plot on the Serial, to improve visualization
	long maxHit = 0;
	for(int i = 0; i < SIZE; i++){
	maxHit = max(maxHit, hits[i]);
		// Uncomment this line if you want to see the NUMBER of hits
		// Serial.println(hits[i]);
	}

	// This will print the bar graphic
	double scale = (double)maxHit/BAR_SIZE;
	Serial.print("Scale: ");
	Serial.print(scale);
	Serial.print("\tMaxHit: ");  
	Serial.println(maxHit);

	for(int i = 0; i < SIZE; i++){
		int len = hits[i]/scale;

		for(int x = 0; x < len; x++)
			Serial.print("=");

		Serial.print("\n");
	}

	// Wait until dinosaurs come back on earth
	while(1);
}