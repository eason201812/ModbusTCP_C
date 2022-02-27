#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>
#include "mod_profile.h"

int main(int argc,char *argv[]){
	if(argc != 3){
		printf("Please type: ./write_coil intAddr intState\n");
		return -1;
	}

	// 1.Read arguments
	int addr = atoi(argv[1]);
        int value = atoi(argv[2]);
        printf("Write to addr:%xH,value = %d\n",addr,value);
	
	// 2.Define variable
	modbus_t *mb;
        mb = modbus_new_tcp(IP,PORT);
        modbus_set_slave(mb,SLAVE_ID);
        
	// 3.Try to connect
        if(modbus_connect(mb) == -1){
                fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
                modbus_free(mb);
                return -1; 
        }

	if(modbus_write_bit(mb,addr,value) == -1){
                fprintf(stderr,"Write to Coil failed:%s\n",modbus_strerror(errno));
                modbus_free(mb);
                return -1; 
	}
	modbus_close(mb);
	modbus_free(mb);	
}
