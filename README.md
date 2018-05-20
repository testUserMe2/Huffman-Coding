# Huffman-Coding

This project uses the [Huffman coding algorithm](https://en.wikipedia.org/wiki/Huffman_coding).

The part of the algorithm that is implemented here is :
- extract the unique "words" (in my project words = sequance of two bytes, short) from the project
- the evaluation of the words variation 
- building the Huffman Three
- create a binary code for every unique word

I didn't use sequence of 4 or more bytes because the number of the unique words you can have there is 2^32 -1 which is a lot of RAM you should use and not every computer have it.
