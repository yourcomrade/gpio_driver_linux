#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main(){
    
    int fdr, fdw;
    int err;
    
    char res[3];
    int r;
    char rc;
    for(int i = 0; i < 10; i++){
        printf("write %d to device driver\n", i);
        fdw = open("/sys/class/sev_leds/myleds",O_RDWR,0666);
        if(fdw == -1){
            perror("Error cannot open");   
        }
        char m = (char)(i + '0');
        if(write(fdw, &m , 1)== -1){
            perror("Error cannot write");
        }
        close(fdw);
        fdr = open("/sys/class/sev_leds/myleds",O_RDWR,0666);
        if(fdr == -1){
            perror("Error cannot open");
            
        }
        sleep(1);
        if(read(fdr, res, 3)!=-1)
        printf("read res = %s\n",res);
        else
        {
            perror("Error open to write");
        }
        

        close(fdr);
        
    }
   
    return 0;
}