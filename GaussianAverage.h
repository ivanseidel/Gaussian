/*
 	GaussianAverage.h - A moving average object with Gaussians

 	This class was made to simplify complex filters.

 	Applying moving average with Gaussians is now just a few lines.

	For instructions, go to https://github.com/ivanseidel/Gaussian

	Created by Ivan Seidel Gomes, July, 2013.
	Released into the public domain.
*/

#ifndef GaussianAverage_h
#define GaussianAverage_h

/*
	!!!!!!!!!!!!!!! ATENTION !!!!!!!!!!!!!!!!!!!
	This class REQUIRES LikedList Library.

	You also need to INCLUDE LinkedList on your code.

	For more information go to:
		https://github.com/ivanseidel/LinkedList
*/
#include "LinkedList.h"

class GaussianAverage: public Gaussian
{
protected:
	// Linked list that will hold past Gaussians
	LinkedList<Gaussian> *gaussians;

	// Number of gaussians to keep record of
	int n;

	// Flag that indicates if a process MUST be done
	bool isCached;

	// Only a temporary helper, to minimize memory usage
	Gaussian avg;

public:
	/*
		Creates a new Gaussian Moving Average that
		keeps track of _n last Gaussians
	*/
	GaussianAverage(int _n = 4): Gaussian(){
		gaussians = new LinkedList<Gaussian>();		
		n = _n;

		isCached = false;
	}

	/*
		Adds a new Gaussian to the FIFO
	*/
	virtual void add(Gaussian _gaus){
		// Notify that we have changed things
		isCached = false;

		while(gaussians->size() >= n)
			gaussians->shift();

		gaussians->add(_gaus);
	}
	
	/*
		Adds a new Gaussian to the FIFO with the overloaded '+='
	*/
	virtual void operator+=(Gaussian _gaus){
		add(_gaus);
	}

	/*
		Adds a new Gaussian to the FIFO with the overloaded '+='
	*/
	virtual void operator+=(double _mean){
		add(Gaussian(_mean));
	}

	/*
		Return the average of all current Gaussians
	*/
	virtual Gaussian process(){

		// Checks if the process is already cached
		if(!isCached){

			avg = gaussians->get(0);
			for(int i = 1; i < gaussians->size(); i++){
				Gaussian tmp = gaussians->get(i);

				// This will enable quadratic importance for newer samples
				// tmp.variance = tmp.variance / (i+1.0);

				avg = avg + tmp;
			}

			mean = avg.mean;
			variance = avg.variance;

			isCached = true;
		}

		return *this;
	}
};

#endif
