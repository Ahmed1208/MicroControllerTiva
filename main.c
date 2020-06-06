#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "UART.h"
#include "KeyPad.h"
void SystemInit(){}
	
struct room{
    int room_number;
    int room_status;
    int room_password;
};


void Init(){
	
	keypad_init();
	UART_Init();
	pinMode( PortF, 1 , Output );
}


int main(){
	
	
		char total_rooms_str[3];
		struct room rooms_arr[100];
		int total_rooms;
		char pc_input_str[7];
		char roomNumber_str[3];
		int roomNumber;
		char statusNumber_str[2];
		int statusNumber;
		char passwordNumber_str[5];
		int passwordNumber;
		int x,enteredPass;
		char enteredPass_str[5];
		char input_room_number_string[2];
	  char keypad_permission_str[2];
	
		Init();
		//////////// Get Total number of rooms ///////////////////////
    
		UART_Receive_String(total_rooms_str);
    total_rooms = atoi(total_rooms_str);
    //////////   set rooms numbers        ///////////////////////
		
    for(x=0;x<total_rooms;x++){
				UART_Receive_String(input_room_number_string);
        rooms_arr[x].room_number = atoi(input_room_number_string);
        rooms_arr[x].room_status = 0;        //default room is LOCKED   0->locked,1->cleaned,2->used
				digitalWrite( PortF , 1 , 1 );
    }
	
	while(1){

				//pc enter string of data (roomNumber,passwordNumber,statusNumber)
				UART_Receive_String(pc_input_str);

				if(pc_input_str != NULL){
					//extract roomNumber
					memcpy( roomNumber_str , pc_input_str , 2);
					roomNumber = atoi(roomNumber_str);

					//extract statusNumber
					memcpy(statusNumber_str, pc_input_str+6, 1);
					statusNumber = atoi(statusNumber_str);

					//extract passwordNumber    
					memcpy( passwordNumber_str , pc_input_str+2 , 4);
					passwordNumber = atoi( passwordNumber_str );
	
				
				switch(statusNumber){	
					case 0:         //check-out mode where u can remove password to room
						if(rooms_arr[roomNumber].room_status == 2 || rooms_arr[roomNumber].room_status == 1){
							rooms_arr[roomNumber].room_password = NULL;
							rooms_arr[roomNumber].room_status = 0;
							digitalWrite( PortF , 1 , 1 );
						}
						break;

					case 1:
						if(rooms_arr[roomNumber].room_status == 2){
							if(rooms_arr[roomNumber].room_password == passwordNumber){
                rooms_arr[roomNumber].room_status = 1;
								digitalWrite( PortF , 1 , 0 );
							}
						}	
						break;

					case 2:
							if(rooms_arr[roomNumber].room_status == 0){
							rooms_arr[roomNumber].room_password = passwordNumber;
							rooms_arr[roomNumber].room_status = 2;
							digitalWrite( PortF , 1 , 1 );
						}
						break;
				}
			}


			///////////////////permission of keypad//////////////////////
		
		UART_Receive_String(keypad_permission_str);
		if(keypad_permission_str != NULL){
			
				UART_Receive_String(roomNumber_str);
				roomNumber = atoi(roomNumber_str);
			
				keypad_get_String(enteredPass_str);
				enteredPass = atoi(enteredPass_str);

				if(rooms_arr[roomNumber].room_status == 2 && rooms_arr[roomNumber].room_password == enteredPass){
						digitalWrite( PortF , 1 , 0 );
				}
	  }
			
	}
		
}