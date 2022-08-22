#include <hidef.h> 
#include "derivative.h" 

#ifdef __cplusplus
extern "C"
#endif

void MCU_init(void); 

void main(void) {
	MCU_init();
	/* Configuro los pines del puerto B como salida */
			PTBDD = 0xff;
	/* Inicializo el registro de datos en 00000001 */
		PTBD = 0x1;
	for(;;) {
		/* Si llegó a 10000000, inicializo 00000001 */
			if (PTBD == 0x80){
				PTBD = 0x1;
	/* Sino, desplazo una posición los bits a izquierda */
			} else {
				PTBD = PTBD << 1;
			}
	}
}

/*------------------------------------------------------------------*/

#include <hidef.h> 
#include "derivative.h" 

#ifdef __cplusplus
extern "C"
#endif

void MCU_init(void); 
int delay(unsigned short t);

int delay(unsigned short t){
	unsigned short x;
	x = 0;
	while(x < t){
		x++;
	}
}

void main(void) {
	MCU_init();
	/* Configuro los pines del puerto B como salida */
			PTBDD = 0xff;
	/* Inicializo el registro de datos en 00000001 */
		PTBD = 0x1;
	for(;;) {
		/* Si llegó a 10000000, inicializo 00000001 */
			if (PTBD == 0x80){
				PTBD = 0x1;
	/* Sino, desplazo una posición los bits a izquierda */
			} else {
				PTBD = PTBD << 1;
			}
			delay(8191);
	}
}

/*------------------------------------------------------------------*/

#include <hidef.h> 
#include "derivative.h" 

#ifdef __cplusplus
extern "C"
#endif

void MCU_init(void); 
int delay(unsigned short t);

int delay(unsigned short t){
unsigned short x;
	x = 0;
	while(x < t){
		x++;
	}
}

void main(void) {
/* 
Declaro una variable “sentido”, la cual podrá valer 0 o 1, y 	su valor se invertirá cada vez que se presione el botón. 
A partir del valor de esta variable, se determinará la direc-
ción del desplazamiento.
*/
	unsigned char sentido;
	MCU_init();
	/* Configuro los pines del puerto B como salida */
    PTBDD = 0xff;
	/* Inicializo el registro de datos en 00000001 */
    PTBD = 0x1;
	/* Configuro el pin 0 del puerto C como entrada */
	PTCDD_PTCDD0 = 0;
	/* Habilito la resistencia pull-up del pin 0 del puerto C */
  	PTCPE_PTCPE0 = 1;
	/* Inicializo sentido = 0 para desplazar a izquierda */
	sentido = 0;
	for(;;) {
	/* 
	Si se detecta que el botón ha sido presionado, se in-
	vierte el valor de la variable sentido, determinando
	un cambio en la dirección del desplazamiento.
	*/
		if (PTCD_PTCD0 == 0){
			sentido = sentido ^ 0x1;
		/* Retardo para evitar detección de rebote */
			delay(65535);
	 	}
		switch(sentido){
		/* Si sentido = 0, desplazo a izquierda */
	 	case 0: 
			if (PTBD == 0x80){
				PTBD = 0x1;
		 	} else {
				PTBD = PTBD << 1;
		 	}
			break;
		/* Si sentido = 1, desplazo a derecha */
	 	case 1:
			if (PTBD == 0x1){
				PTBD = 0x80;
		 	} else {
				PTBD = PTBD >> 1;
		 	}
		 	break;
		}
		delay(8191);
	}
}



