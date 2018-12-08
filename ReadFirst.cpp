#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int fd1,fd2;
    int arr1[4][4], arr2[4][4],i=0,j=0;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    fd1 = open(myfifo,O_RDONLY);  
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            read(fd1, &arr1[i][j], sizeof(int));
            arr2[i][j] = arr1[i][j];
            printf("\nReading from write first: %d",arr2[i][j]);
        }
    }
    close(fd1);
    fd2 = open(myfifo,O_WRONLY);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            write(fd2, &arr2[i][j], sizeof(int));
        }
    }
    close(fd2);
}
