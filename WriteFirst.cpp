#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{

    int arr1[4][4] = { {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4}
    };

    int arr2[4][4] = { {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4}
    };

    int res[4][4], joy[4][4];
    int i, j, fd1, fd2, a, b, c;
    printf("\nPrint starts here!");
    for (a = 0; a < 4; a++)
    {
        for (b = 0; b < 4; b++)
        {
            res[a][b] = 0;
            for (c = 0; c < 4; c++)
                res[a][b] += arr1[a][c]*arr2[c][b];
        }
    }
    char* myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo,0666);         
    fd1 = open(myfifo, O_WRONLY);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            write(fd1, &res[i][j], sizeof(int));
        }
    }
    close(fd1);
    fd2 = open(myfifo, O_RDONLY);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            read(fd2, &joy[i][j], sizeof(int));
            printf("\Reading back: %d\n",joy[i][j]);
        }
    }
    close(fd2);
}
