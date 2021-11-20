# CDCG
CDCG is a library containing various data structures.
Currently I am targeting C++20 but because of the early stage of development nothing is set in stone yet.




## SmallVector
SmallVector is a std::vector like container with small buffer optimization.
It is meant to limit the number of allocations for containers with only a handful of elements.
Design of this class was inspired by 
[this talk by Chandler Carruth](https://www.youtube.com/watch?v=vElZc6zSIXM)

## LazyArray
LazyArray is a container with static capacity and dynamic size. This class is not using any dynamic allocations but new items can be added only up to the capacity.

## Range
Range is providing utility similiar to range function from python3 and 1..n constructs known from other languages





## Goals
* Implement missing methods for SmallVector and LazyArray so that they can be used as a drop in replacement for std::vector
* Get sanitizer to work with the build system
* Write more tests
* Implement more data structures
* Migrate project to modules when possible
* Benchmark data structures
* Write documentation
* Get a single star Sadge