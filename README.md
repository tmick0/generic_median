# generic_median
C++ library implementing a basic median filter. Also compatible with Arduino.

## Introduction

[Median filters](https://en.wikipedia.org/wiki/Median_filter) are useful for smoothing signals which are subject to 'spiky' noise. The basic idea is to maintain a window of *n* readings and return the median of those *n* when we want to know the "true" value of the signal.

I did not find any reasonably well-implemented median filter library for Arduino, so I decided to write this one. Along the way, I decided to get some practice with C++ templates since I had never really done anything serious with them before.

## Usage

Note that this "library" is not Arduino-exclusive; it is just basic C++ and does not use any libraries whatsoever. Copy it into your project and you will be able to use it, guaranteed.

The implementation is entirely contained in the header, `MedianFilter.h`. It consists of just one template class, `MedianFilter`.

To instantiate a filter, you need to know two things:

- The type of the value you want to filter (`int`, `float`, `uint32_t`, etc.)
- The size of the window you want to maintain.

These correspond to the two template parameters. For example to create a window of 5 `int`s, you would declare:

    MedianFilter<int, 5> mf;

To use your shiny new `MedianFilter` object, you will employ three simple methods:

- `void addSample(s)`: Adds the sample `s` to the window.
- `bool isReady()`: Returns `true` if we have read the necessary number of samples to compute the median.
- `T getMedian()`: Returns the median of the window. It will have been pre-computed on the last call to `addSample`, so it costs nothing to call this several times. Note that nothing useful will be returned if we haven't read enough data, so you should check `isReady()` first.

Sample code is provided in `test.cpp`. The sample program obtains 1000 random integers and prints out the median after each reading. Simply compile with `g++ test.cpp`.

## Implementation details

Readings are placed in a circular buffer. The buffer content is copied to a second array, where the median is computed using the quickselect algorithm.

The (average case) complexity is `O(n)`. This could be improved, but given that `n` is typically quite small I didn't bother. Most existing Arduino-compatible median filters I found were `O(n log n)`, using sorts rather than selects, so this is a small improvement at least in asymptotic complexity.

Note that quickselect does exhibit a pathological `O(n^2)` worst case. But again, it shouldn't really matter.

## License

The content of this repository is released under the MIT License; see accompanying LICENSE file for details.