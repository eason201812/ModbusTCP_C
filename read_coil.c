#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>
#include "mod_profile.h"

int main(int argc,char *argv[]){
	if(argc != 3){
		printf("Please type: ./read_coil intAddr intCount\n");
		return -1;
	}
	
	// 1.Define variable
	int rc;
	int i;				//for-loop variable
	int addr = atoi(argv[1]);	//coil address
	int count = atoi(argv[2]);	//how many coil status from (address ~ address+count)
	uint8_t tab_reg[count];

	// 2.Define Modbus
        modbus_t *mb1;
        mb1 = modbus_new_tcp(IP,PORT);
        modbus_set_slave(mb1,SLAVE_ID); //default slave id is 0xff,so must be set to int slave
  
        // 3.Try to Connect
        if(modbus_connect(mb1) == -1){
                fprintf(stderr,"Connection failed: %s \n",modbus_strerror(errno));
                modbus_free(mb1);
                return -1;
        }

	// 4.Read coil register(function 0x01)
	rc = modbus_read_bits(mb1,addr,count,tab_reg);
	if(rc == -1){
		fprintf(stderr,"%s\n",modbus_strerror(errno));
		return -1;
	}

	// 5.Display register value     
        for(i = 0;i < rc;i++){
                if(i % 4 == 0){
                        printf("\n");
                }
                printf("Coil[%d] = %d\t",i,tab_reg[i]);
        }

        getchar();      //wait for end
        modbus_close(mb1);
        modbus_free(mb1);
}
