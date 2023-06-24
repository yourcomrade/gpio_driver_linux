#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd;
    fd = open("/sys/class/sev_leds/myleds",O_RDWR, 0666);
    char res;
    for(int i = 0; i < 10; i++){
        printf("write %d to device driver\n", i);
        char m = (char)(i + '0');
        if(write(fd, &m , 1)!= 1){
            printf("Error cannot write \n");
            close(fd);
            return -1;
        }
        sleep(1);
        read(fd, &res, 1);
        printf("read res = %d\n",res);
    }
    close(fd);
    return 0;
}