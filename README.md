# intal-library

A C-library of an integer of arbitrary length, let us call it as “intal” in short. The functionalities to be implemented in the library are declared in the header file.

Library "intal", short for integer of arbitray length, a library of nonnegative integers of arbitrary length. The given header file "intal.h" declares the functionalities the library is expected to provide except that there is no definition of the "intal" itself. That is left to the implementation file, which should declare the structure of the intal along with defining
the functionalities declared in intal.h. Compile the implementation with intal.h and a client file to test the functionalities.

Client treats an intal (an integer of arbitrary length) as an object pointed by a pointer "void*". An intal can be created by intal_create() by providing a char string of a nonnegative integer provided in decimal digits. Some intals are created out of some functionalities like intal_add(), which creates a new intal. A new intal created must have allocated a dynamic memory (may be by a malloc() call). Responsibility of destroying the intals created lies with the client by calling intal_destroy(), which will free whatever memory allocated during the creation of intal. Client sees an intal as a "void*". There is no theoretical limit to the size of the integer, but memory limitations of the process (Operating System).

Refer the intal.h file for the description of the functions.

---

#### Sample client file:

Expected output for a sample client:

First intal: 4999<br />
Second intal: 2001<br />
Two intals after increment and decrement:<br />
5000<br />
2000<br />
Max of two intals: 5000<br />
Sum: 7000<br />
Diff: 3000<br />
Product: 10000000<br />
Quotient: 2<br />
5000 ^ 2: 25000000<br />

