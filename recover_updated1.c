#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check for correct usage
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //Open supplied image file to read
    FILE *inptr = fopen(argv[1], "r");
    printf("%s\n", argv[1]);

    //Not too sure exactly how this works but, finds the size of the file input (in bytes)
    fseek(inptr, 0L, SEEK_END);
    long size = ftell(inptr);
    printf("%li\n", size);
    fseek(inptr, 0L, SEEK_SET);
    
    //Check if image file is readable
    if(inptr == NULL)
    {
        printf("Unreadable file.\n");
        return 1;
    }
    //READING IMAGES AND WRITING THEM INTO FILES

    //Allocating buffer memory to read the image into
    //jpegno counts the no. of jpegs found in the file
    int jpegno = 0;
    //Stores pointer location of last jpeg header
    int last_position = 0;
    
    /*
        The following few lines (before the for loop) are used by me to understand how fseek() really works
        I've tried a few different lines to test whether the FILE* stream pointer is actually moving.
    */

    
    BYTE bytes1[512];
    printf("%p\n", &inptr);
    fread(bytes1, 1, 512, inptr);
    printf("Intial: %i %i %i %i\n", bytes1[0], bytes1[1], bytes1[3], bytes1[4]);

    fseek(inptr, 512L, SEEK_CUR);//Check this
    printf("%p\n", &inptr);
    fread(bytes1, 1, 512, inptr);
    printf("After seeking 512 bytes1: %i %i %i %i\n", bytes1[0], bytes1[1], bytes1[3], bytes1[4]);

    printf("read\n");

    fseek(inptr, 0, -512);//Check this 
    printf("%p\n", &inptr);
    fread(bytes1, 1, 512, inptr);
    printf("Original: %i %i %i %i\n", bytes1[0], bytes1[1], bytes1[3], bytes1[4]);

    //Read chunks of 512 bytes from start till end of image file
    for (int i = 0; i < size; i += 512)
    {
        BYTE bytes[512];
        printf("intialised bytes\n");
        //Write Chunks of 512 bytes
        //Location of pointer is derived from (location of file pointer + 512*i)
        printf("%lu \n",fread(bytes, 1, 512, inptr + i));
        printf("read\n");


        /**
        for(int j = 0; j < 512; j++)
        {
            *bytes[j] = inptr + i + j;
        }


        // Read first four bytes
        BYTE *bytes[4];
        for(int j = 0; j <= 3; j++)
        {
            bytes[j] = chunk[j];
        }
        */

        //Condition for jpeg header
        printf("%i %i %i %i\n", bytes[0], bytes[1], bytes[3], bytes[4]);
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            printf("%i\n", i);
            /*
            If the first four bytes of the chunk resemble a jpeg header, a new file is opened for writing,
            So as to start writing all the previous chunks of 512 bytes from the location of the last header
            */
            char *filename = "";

            //Naming the jpeg file in the format: 000.jpg, 001.jpg, ...
            sprintf(filename, "%03i.jpg", jpegno);
            printf("%s\n", filename);
            //Increasing no. of jpegs found
            jpegno++;

            //Creating a new file with name as filename to write the image blocks
            FILE *img = fopen(filename, "w");

            //Writes the bytes into img* stream
            //No. of bytes that need to be written = current position(i) - last_position
            fwrite((inptr + last_position), 1, (i - last_position), img);
            if (i!=0)
            {
                last_position = i;
            }
        }
        printf("Iteration: %i Complete \n", i);
    }
    fclose(inptr);
}


//Open File and load it into memory

//Check chunks of 512 bytes for jpeg headers

//If the header matches write the jpeg into a new file
//Name should be in the form ###.jpg
//Use sprintf %03i

//Repeat until new jpeg is found

//TODO: Find a way to keep writing data into an output stream until a new jpeg is found
