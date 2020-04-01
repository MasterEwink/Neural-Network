# Neural-Network

Student project created during "TIPE" for "Classes Préparatoires aux Grandes Écoles". The development stopped.

## Goal

Creating a neural network in C++ from nothing, and applying it to image compression.

## Work achieved

The program is able to create a neural network, compute its output from an input, and apply backpropagation to train it for a desired output.
The idea was to create a kind of funnel shaped neural network which could recreate each part of a decomposed image, then cut the neural network in the middle, and use it as a compression / decompression device for this specific image. Thus, both half of the network and its input must be lighter than the original full image in order to be efficient.
