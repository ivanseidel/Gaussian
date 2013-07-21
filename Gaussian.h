/*
 	Gaussian.h - An Gaussian object

	This class was made to make it easy to understand and use
	Gaussians in real life applications.

	For instructions, go to https://github.com/ivanseidel/Gaussian

	Created by Ivan Seidel Gomes, July, 2013.
	Released into the public domain.
*/

#ifndef Gaussian_h
#define Gaussian_h

#include "Math.h"
#include "Arduino.h"

#define MAX_VARIANCE 2147483600

class Gaussian
{
protected:
	/*
		Return the result of the sum of a gaussian
		with _mean and _variance and This gaussian,
		in a NEW object;
	*/
	virtual Gaussian sum(double _mean, double _variance){
		double nMean = (variance * _mean + _variance * mean) / (_variance + variance);
		double nVariance = 1.0 / (1.0/variance + 1.0/_variance);

		return Gaussian(nMean, nVariance);
	}

	/*
		Return the result of the sum of _gaus and This
		gaussian, in a NEW object;
	*/
	virtual Gaussian sum(Gaussian _gaus){
		return sum(_gaus.mean, _gaus.variance);
	}

public:
	/*
		Leave it public, to make it easier
	*/
	double mean, variance;

	/*
		Constructor method
		Default variance is MAC_VARIANCE
	*/
	Gaussian(double _mean = 0.0, double _variance = MAX_VARIANCE){
		mean = _mean;
		variance = _variance;
	}

	/*
		Set the mean to _val
	*/
	virtual Gaussian setMean(double _val){
		mean = _val;

		return *this;
	}

	/*
		Move the mean by _val
	*/
	virtual Gaussian move(double _val){
		mean += _val;

		return *this;
	}

	/*
		Increase the variance by _val
	*/
	virtual Gaussian vary(double _val){
		variance += _val;

		return *this;
	}

	/*
		Increase the variance by _val
	*/
	virtual Gaussian setVariance(double _val){
		variance = _val;

		return *this;
	}


	/*
		Copies the same mean and variance to the current object
	*/
	virtual void operator=(Gaussian _gaus){
		mean = _gaus.mean;
		variance = _gaus.variance;
	}

	/*
		Overrides the + operator to be able to sum with gaussians like:
			Gaussian b = Gaussian(10, 20);
			Gaussian a = b + Gaussian(1,10);
	*/
	virtual Gaussian operator+(Gaussian _gaus){
		return sum(_gaus);
	}

	/*
		Overrides the += operator to be able to sum with gaussians like:
			Gaussian b = Gaussian(10, 20);
			Gaussian a += b;
	*/
	virtual void operator+=(Gaussian _gaus){
		*this = sum(_gaus);
	}

	/*
		Randomize a variable with Gaussian distribuition,
		using it's mean and variance
	*/
	virtual double random(){
		double R1, R2;
		R1 = ::random(MAX_VARIANCE)/(double)MAX_VARIANCE;
		R2 = ::random(MAX_VARIANCE)/(double)MAX_VARIANCE;
		return mean + variance * cos( 2 * M_PI * R1) * sqrt(-log(R2));
	}

	virtual double plot(double x){
		static const float inv_sqrt_2pi = 0.3989422804014327;
		double sigma = sqrt(variance);
	    double a = (x - mean) / sigma;

	    return inv_sqrt_2pi / sigma * exp(-0.5f * a * a);
	}

};


#endif