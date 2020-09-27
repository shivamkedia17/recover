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
    int positions[50];
    //Stores pointer location of last jpeg header
    long last_position = 0;

    //Read chunks of 512 bytes from start till end of image file
    for (long i = 0; i < size; i += 512)
    {
        BYTE *bytes = malloc(512);

        //printf("intialised bytes\n");
        //Write Chunks of 512 bytes
        //Location of pointer is derived from (location of file pointer + 512*i)
        fread(bytes, 512, 1, inptr);
        //printf("read\n");

        //Condition for jpeg header
        //printf("%i %i %i %i\n", bytes[0], bytes[1], bytes[2], bytes[3]);
        if (*bytes == 0xff && *(bytes + 1) == 0xd8 && *(bytes + 2) == 0xff && ((*(bytes + 3) & 0xf0) == 0xe0))
        {
            positions[jpegno] = i;
            jpegno++;
        }
        free(bytes);
        fseek(inptr, 512L, SEEK_CUR);
        //printf("Iteration: %i Complete \n", i);
    }
    for (int i = 0; i < 50; i++)
    {
        printf("%i: %i\n", i, positions[i]);
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