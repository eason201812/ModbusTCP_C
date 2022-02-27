#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <modbus.h>
#include <errno.h>
#include "mod_profile.h"

int main(int argc,char *argv[]){
	int addr = atoi(argv[1]);
	int value = atoi(argv[2]);
	printf("Write to addr:%xH,value = %d\n",addr,value);

	// 1.Define Modbus
	modbus_t *mb;
	mb = modbus_new_tcp(IP,PORT);
	modbus_set_slave(mb,SLAVE_ID);

	// 2.Try to connect
	if(modbus_connect(mb) == -1){
		fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
		modbus_free(mb);
		return -1;
	}

	// 3.Write to register
	int result = 0;
	result = modbus_write_register(mb,addr,value);
	printf("result: %d\n",result);	

	// 4.close
	modbus_close(mb);
	modbus_free(mb);	
}
