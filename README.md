list
====

A simple, minimalistic linked list in C. Just scapped bits from here and there, nothing special and probably not any good after all.

See examples for a view of functionality. Use at your own risk.

Example
=======

Using list_extract, you can do something like this (this is the output of slicex.c):

list[] == [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 ]                        
list[3:14] == [ 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 ]                                                                                                 
list[] == [ 0, 1, 2, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 ]                                                             
list[12:] == [ 23, 24, 25, 26, 27, 28, 29, 30 ]                                                                                                       
list[] == [ 0, 1, 2, 14, 15, 16, 17, 18, 19, 20, 21, 22 ] 
