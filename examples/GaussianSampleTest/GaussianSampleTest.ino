// https://wokwi.com/projects/360282019322936321
// for https://github.com/ivanseidel/Gaussian/issues/6

#include "Gaussian.h" 

const int sample_size = 10000;
const float var_set = 1.0;
const float mean_set = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nStarting Random Gaussian Distribution...");
  Serial.print("Gaussian(");
  Serial.print(mean_set);
  Serial.print(",");
  Serial.print(var_set);
  Serial.println(")");
  delay(20);
  randomSeed(20230326);
}


void loop() {
  Gaussian g1 = Gaussian(mean_set, var_set);
  float sum = 0, sumsq = 0, mean = 0, variance = 0;

  // Zero the array
  for (int i = 0; i < sample_size; i++) {
    double x = g1.random();
    sum += x;
    sumsq += x*x;
  }
  mean = sum/sample_size;
  variance = (sumsq-sample_size*mean*mean)/(sample_size-1);

  Serial.print("n:");
  Serial.print(sample_size);
  
  Serial.print(" sum:");
  Serial.print(sum);
  
  Serial.print(" ssq:");
  Serial.print(sumsq);
  
  Serial.print(" mean:");
  Serial.print(mean);
  
  Serial.print(" var:");
  Serial.print(variance);
  Serial.println();
}

