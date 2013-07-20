# Gaussian

This library was developed targeting `Arduino` applications. However, works just great with any C++.

The use of Gaussians is really hard because requires a deep understanding about complex math. **Not anymore.**  
We have done it for you, fell free to use the fully-implemented class of `Gaussian`.  
Do you want to do a [Moving Average](https://en.wikipedia.org/wiki/Moving_average)? `GaussianAverage` is just what you are looking for.

## Installation

1. [Download](https://github.com/ivanseidel/Gaussian/releases) the Latest release from gitHub.
2. Unzip and modify the Folder name to "Gaussian" (Remove the '-version')
3. Paste the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).

## Getting started

### `Gaussian` class

A class that contains a `mean` and a `variance` attribute.

Also contains methods to do sums with others `Gaussians`.

#### To declare a Gaussian object:
```c++
// Simple Gaussian initialization and instantiation
Gaussian myGaussian = Gaussian(mean, variance);

// This will declare a Gaussian with mean = 0 and variance = MAX_VARIANCE (A really big value)
Gaussian myGaussian = Gaussian();

// This will do the same as above
Gaussian myGaussian();
Gaussian myGaussian(0);
```

Dealing with `mean` is very easy. You can either access it direcly (attribute `mean`),
or change it with the methods `move` and `setMean`. Both methods returns the `self`
Gaussian object, allowing you to do actions consecutively in one single line.

```c++
// Set or Get the attribute direcly to the object
myGaussian.mean = 10;

// Increase the mean by `x`
myGaussian.move(10);

// Set to 10 and move by -10
myGaussian.setMean(10).move(-10);
```

When dealing with the `variance`, you can also do the same as the `mean`. Access it direcly from
the object, or use the methods `vary` and `setVariance` to change the `variance`.

```c++
// Set or Get the attribute direcly to the object
myGaussian.variance = 4;

// Increase the variance by `y`
myGaussian.vary(3);

// Set to 3 and then vary 10 more
myGaussian.setVariance(3).vary(10);
```

Ok, now that we can change both `mean` and `variance`, we can now go to the next step: Summing Gaussians.

It's already implemented all the math to do that, and it's nos so hard to understand it, after resuming
sum of Gaussians to 'sum of pondered values'.

The operators **+, +=, =** works just good with the class `Gaussian`.

```c++
Gaussian g1 = Gaussian(0, 10);
Gaussian g2(10, 10);

// Simply sum both of them (the + method is overloaded on the class)
Gaussian result = g1 + g2;

// Or do like this
result = g1;
result += g2;
```


## Library Reference

### You should know:

- `getAvailable()` - Get the first available Timer.

- `attachInterrupt(void (*isr)())` - Attach a interrupt (callback function) for the timer of the object.

- `detachInterrupt()` - Detach current callback of timer.

- `start(long microseconds = -1)` - Start the timer with an optional period parameter.

- `stop()` - Stop the timer

- `setFrequency(long frequency)` - Set the timer frequency

- `long getFrequency()` - Get the timer frequency

- `setPeriod(long microseconds)` - Set the timer period (in microseconds)

- `long getPeriod()` - Get the timer period (in microseconds)

### You don't need to know:

- `int timer` - Stores the object timer id (to acces Timers struct array).

- `DueTimer(int _timer)` - Instantiate a new DueTimer object for Timer _timer (NOTE: All objects are already instantiated!).

- `static const Timer Timers[]` - Stores all timers information

- `static void (*callbacks[])()` - Stores all callbacks for all timers


### Hardware Information

More information on the Timer Counter module of the µC on the Arduino Due
can be found in the documentation file [TimerCounter](TimerCounter.md).

### Version History

* `1.0 (2013-07-20)`: Original release
