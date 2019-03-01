#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BLOCK_SIZE (1024*2)//must be same with encode size

#include "fastlz.h"

typedef struct
{
    unsigned short compressed : 1;
    unsigned short last_package : 1;
    unsigned short reserved : 1;
    unsigned short len : 13;
}nuzip_t;

unsigned char buffer[BLOCK_SIZE];
unsigned char result[BLOCK_SIZE];

static const char magic[]={'n','z','i','p'};

int main(int argc, char** argv)
{

    size_t bytes_read=0 ;
    int chunk_size;
    int compress_size=0;
    char mymagic[4];
    
    if(argc<3)
    {
        printf("usage: decode.exe input_file output_file\r\n");
        exit(-1);
    }

    FILE* in=fopen(argv[1], "rb");
    FILE* out=fopen(argv[2], "wb");
    if(!in || !out)
    {
        printf("file does not exist\r\n");
        exit(-1);
    }

    bytes_read=fread(&mymagic, 1, sizeof(mymagic), in);
    if(sizeof(mymagic)==bytes_read)
    {
        for(int i=0; i<bytes_read; i++)
        {
            if(mymagic[i]!=magic[i])
            {
                printf("file corrupted or not compressed by FastLZ\r\n");
                break;
            }
        }
    }
    
    

    size_t in_size=BLOCK_SIZE;
    nuzip_t header;
    do
    {
        
        bytes_read=fread(&header, 1, 2, in);
        printf("compress=%d, len=%d, last=%d\r\n", header.compressed,header.len,header.last_package);
        size_t rsize= fread(&buffer, 1, header.len, in);
        int remaining=header.len;
        if(header.compressed)
        {
            remaining= fastlz_decompress(buffer, header.len, result, BLOCK_SIZE);
            
        }
        else
        {
            memcpy(result,buffer, header.len);
        }

        fwrite(result,1,remaining,out);
        printf("compress=%d ,remaining =%d, len=%d, last=%d\r\n",header.compressed,remaining,header.len,header.last_package);

    }while(!header.last_package);
    
    fclose(in);
    fclose(out);
    
    

    
    
    
}