# Filter finder

## Origin

This is a repository developed for the bachelor thesis of [ikhovind](https:://github.com/ikhovind) and [erlinssl](https://github.com/erlinssl). It is an extension of an [machine learning article](https://arxiv.org/abs/2205.00920) written by our supervisor Ole Christian Eidheim. In connection to that article, Eidheim developed an algorithm in Python, and our thesis is about translating this algorithm into C++, and then optimize and GPU-parallelize it. The group then gathered data about the general calculations and attempted to draw conclusion about the potentials of multi-threading.

## Results

We have implemented several different versions of the original Python algorithm, which are all spread across the different branches in this project. These are the main ones:

| branch            | description                                                  |
| ----------------- | :----------------------------------------------------------- |
| main              | Single threaded implementation of the algorithm in plain C++. |
| threads-v1        | Multi-threaded implementation parallelizing part of the samples being run, offering the greatest CPU speed but sacrificing accuracy. |
| threads-v2        | Multi-threaded implementation parallelizing the calculation of filter values, sacrifices no accuracy |
| arrayfire-revised | Implementation using the open source library ArrayFire, let's you choose whether or not to run on the CPU or on the GPU with CUDA or OpenCL. |
| compute           | Implementation using Boost Compute, a thin wrapper over OpenCL. This is the fastest GPU-accelerated version. |

The actual scientific results of the research is contained within the thesis itself. It will be linked here as soon as it is made public by NTNU.

## Dependencies

The dependencies of the program depends on the version used. All versions are dependent on [matplotlib-cpp](https://github.com/lava/matplotlib-cpp) in order to display the final calculation. ArrayFire is dependent on [ArrayFire](https://github.com/arrayfire/arrayfire) and compute is dependent on [Boost Compute](https://github.com/boostorg/compute).



## Running

If you want to run the program on your own system you will need:

1. C++20. The program can likely be easily rewritten to at least C++17 if not C++11 or lower, but out of the box it relies on C++20 functionality.  

2. Secondly, you will need to download a copy of the [MNIST dataset](http://yann.lecun.com/exdb/mnist/), and place it a directory named data in the top level of this repository, see CMakeLists.txt for help
3. Thirdly you will have to make sure you have Python 3 installed
4. Install Numpy and matplotlib
5. If you want to run ArrayFire you will need to [install ArrayFire](https://arrayfire.org/docs/installing.htm)
6. If you want to run compute you will need to [install Boost Compute](http://boostorg.github.io/compute/boost_compute/getting_started.html)

A CMake file is provided, which should handle linking the given dependencies, as long as you have them installed on your system. 



In order to run the actual script, you can also use cmake, here is an example on a Linux system, starting from the top level of this repository:

```
mkdir build
cd build
cmake ..
make
./filter_finder
```

You can also set the parameters at through command line arguments, here is the standard example used in Eidheim's article:

```
./filter_finder 1 0.5 1000 4 1000 5 0.1
```

The parameters are as follows, all 7 need to be set, otherwise all of them revert back to their standard value:

```
./filter_finder sigma lambda num_batches grid_size batch_size resolution learning_rate
```

the number of samples are decided by num_batches and batch_size, grid size is the square root of how many filters you want to  find simultaneously, a value of 4 will find 4 ** 2 = 16, 5 will find 25 and so on. The rest of the parameters are described in [Eidheim's original article](https://arxiv.org/abs/2205.00920).
