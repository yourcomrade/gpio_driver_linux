#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(){
    int fd;
    fd = open("/dev/seven_seg_disp",O_RDWR, 0666);
    char res;
    for(int i = 0; i < 10; i++){
        printf("write %d to device driver\n", i);
        char m = (char)(i + '0');
        if(write(fd, &m , 1) == -1){
            perror("Error cannot write");
            close(fd);
            return -1;
        }
        sleep(1);
        if(read(fd, &res, 1) == -1){
            perror("Error cannot read");
        }
        printf("read res = %c\n",res);
    }
    close(fd);
    return 0;
}