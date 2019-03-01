#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BLOCK_SIZE (1024*2)//must be same with decode size

#include "fastlz.h"

typedef struct
{
    unsigned short compressed : 1;
    unsigned short last_package : 1;
    unsigned short reserved : 1;
    unsigned short len : 13;
}nuzip_t;



unsigned char buffer[BLOCK_SIZE];
unsigned char result[BLOCK_SIZE*2];

static const char magic[]={'n','z','i','p'};

int main(int argc, char** argv)
{

    size_t bytes_read=0 ;
    int chunk_size;
    int compress_size=0;

    
    if(argc<3)
    {
        printf("usage: encode.exe input_file output_file\r\n");
        exit(-1);
    }

    FILE* in=fopen(argv[1], "rb");
    FILE* out=fopen(argv[2], "wb");
    if(!in || !out)
    {
        printf("file does not exist\r\n");
        exit(-1);
    }
    
    fseek(in, 0, SEEK_END);
    unsigned long fsize = ftell(in);
    fseek(in, 0, SEEK_SET);
    fwrite(&magic,1,sizeof(magic),out);

    do
    {
        
        size_t rsize= fread(buffer, 1, BLOCK_SIZE, in);
        chunk_size=fastlz_compress_level(1, buffer, rsize, result);
        bool need_compress=(chunk_size<rsize);
        nuzip_t header;
        header.compressed=need_compress;
        header.len=need_compress?chunk_size:rsize;
        header.last_package=(bytes_read+rsize)>=fsize?1:0;
        fwrite(&header,1,2,out);
        fwrite(need_compress?result:buffer,1,header.len,out);
        printf("need_compress=%d, in size=%d, out size=%d, last=%d, sizeof=%d\r\n", need_compress,rsize,chunk_size,header.last_package, sizeof(nuzip_t) );
        compress_size+=header.len;
        bytes_read+=rsize;
    }while(bytes_read<fsize);
    
    fclose(in);
    fclose(out);
    
    
    printf("compressed size %d, rate=%f\r\n", compress_size, (double)compress_size/fsize);

    
    
    
}