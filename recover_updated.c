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
    long last_position = 0;

    //Read chunks of 512 bytes from start till end of image file
    for (long i = 0; i < size; i += 512)
    {
        BYTE *bytes[512];

        //Write Chunks of 512 bytes
        //Location of pointer is derived from (location of file pointer + 512*i)
        //fwrite(bytes, 512, 1, inptr + i);
        for(int j = 0; j < 512; j++)
        {
            *bytes[j] = inptr + i + j;
        }

        /**
        // Read first four bytes
        BYTE *bytes[4];
        for(int j = 0; j <= 3; j++)
        {
            bytes[j] = chunk[j];
        }
        */

        //Condition for jpeg header
        if (*bytes[0] == 0xff && *bytes[1] == 0xd8 && *bytes[2] == 0xff && (*bytes[3] & 0xf0) == 0xe0)
        {
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
