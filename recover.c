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

    FILE *inptr = fopen(argv[1], "r");
    fseek(inptr, 0L, SEEK_END);
    long size = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);

    //Check if image file is readable
    if(inptr == NULL)
    {
        printf("Unreadable file.\n");
        return 1;
    }

    //READING IMAGES AND WRITING THEM INTO FILES

    //Allocating buffer memory to read the image into
    int jpegno = 0;
    long last_position = 0;

    //Read chunks of 512 bytes
    for (long i = 0; i <= size; i += 512)
    {
        BYTE *chunk = malloc(512);

        fwrite(chunk, 512, 1, inptr + i);

        // Read first four bytes
        BYTE *bytes[4];
        for(int j = 0; j <= 3; j++)
        {
            bytes[j] = &chunk[j];
        }

        //Condition for jpeg image
        if (*bytes[0] == 0xff && *bytes[1] == 0xd8 && *bytes[2] == 0xff && (*bytes[3] & 0xf0) == 0xe0)
        {
            char *filename = "";
            sprintf(filename, "%03i.jpg", jpegno);
            jpegno++;
            FILE *img = fopen(filename, "w");
            fwrite(inptr + i - last_position, 512, (i - last_position) / 512, img);
            last_position = i - 1;
        }
        free(chunk);
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