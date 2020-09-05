# recover - recovers lost jpegs from raw file
Hello. recover accepts a image file as a cmd line argument. It then scans the file in 512 byte chunks for .jpeg headers. If a jpeg header is found, a new file is created and all succeeding blocks are written until a new jpeg is found. It is assumed that jpegs contiguously span the input file.
