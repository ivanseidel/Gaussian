#include <Gaussian.h>
void setup() {
	Serial.begin(9600);
	Serial.println("\n\nStarting Random Gaussian Distribuition...");
	delay(20);
	randomSeed(analogRead(0));
}

// The number of "slots" to record the hits of gaussian random
#define SIZE 36

// How many tests will be performed
#define TESTS 10000

// How many characters will have, in width?
#define BAR_SIZE 40

void loop() {
	Gaussian g1 = Gaussian(0, 10);
	long zero = SIZE/2 - g1.mean;  
	long hits[SIZE] = {0};

	// Zero the array
	for(int i = 0; i < SIZE; i++)
		hits[i] = 0;

	// Print Header (0% ------------- 100%)
	Serial.print("0% ");

	for(int i = 3; i < BAR_SIZE - 5; i++)
		Serial.print("-");

	Serial.println(" 100%");

	// Process the gaussians and randomize 'TESTS' times
	int lastStep = 0, step;
	Serial.print("=");
	for(int i = 0; i < TESTS; i++){
		step = (double)i/TESTS*BAR_SIZE;
		if(step > lastStep){
			Serial.print("=");
			lastStep = step;
		}

		double val = g1.random();
		int place = (int)val - g1.mean + zero;
		place = constrain(place, 0, SIZE);
		hits[place]++;
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