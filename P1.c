//Rafael Delgado García-Valdecasas
//Pablo Rienda Sánchez
#include <dos.h>
#include <stdio.h>

#define BYTE unsigned char

BYTE MODOGRAFICO=4;
BYTE MODOTEXTO=3;
BYTE ctexto=1;
BYTE cfondo=0;
   
void pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

void gotoxy(int x, int y){
    union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor){
        case 0: //invisible
            inregs.h.ch = 010;
            inregs.h.cl = 000;
            break;
        case 1: //normal
            inregs.h.ch = 010;
            inregs.h.cl = 010;
            break;
        case 2: //grueso
            inregs.h.ch = 000;
            inregs.h.cl = 010;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

void setvideomode(BYTE modo){
   union REGS inregs, outregs;
   inregs.h.al = modo;
   inregs.h.ah = 0x00;
   int86(0x10, &inregs, &outregs);
}

BYTE getvideomode(){
   union REGS inregs, outregs;
   BYTE modo;
   int num_col;
   inregs.h.ah = 0x0F;
   int86(0x10, &inregs, &outregs);
   modo=outregs.h.al;
   return modo;
}

void textcolor(BYTE color_texto){
	ctexto=color_texto;
}

void textbackground(BYTE color_fondo){
	cfondo=color_fondo;
}

void clrscr(){
     union REGS inregs, outregs;
     inregs.h.al = 0;
     inregs.h.ah = 0x06;
     inregs.h.bh = 0x00;
     inregs.h.ch = 0x00;
     inregs.h.cl = 0x00;
     inregs.h.dh = 0x25;
     inregs.h.dl = 0x80;
     int86(0x10, &inregs, &outregs);
     pausa();
     setvideomode(MODOTEXTO);
}

void cputchar(char caracter){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = caracter;    
	inregs.h.bl = cfondo << 4 | ctexto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
}

void getche(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 printf("\n\n");
	 cputchar(caracter);
}

//Precondiciones, x1 debe ser menor que x2. y1 debe ser menor que y2.
void recuadro_texto(int x1, int y1, int x2, int y2, int color_texto, int color_fondo){
     int i=0;
     int j=0;
     textcolor(color_texto);
     textbackground(color_fondo);
     setvideomode(MODOTEXTO);
     gotoxy(x1,y1);
    // Dibujar el rectángulo
    for (i = y1; i < y2+1; i++) {
        for (j = x1; j < x2+1; j++) {
            gotoxy(j,i);
            if((i==y1)||(i==y2)){
                cputchar('-');                 
            }
            else if((j==x1)||(j==x2)){
                cputchar('|');          
            }
            else{
                cputchar(' ');       
            }
        }
    } 
}

void pixel(int x, int y, BYTE C){
   union REGS inregs, outregs;
   inregs.x.cx = x;
   inregs.x.dx = y;
   inregs.h.al = C;
   inregs.h.ah = 0x0C;
   int86(0x10, &inregs, &outregs);
}

void dibujografico(){
     int i=0;
     int j=0;
     setvideomode(MODOGRAFICO);
     //ojo izq
     for(i=20;i<60;i++){
         for(j=20;j<60;j++){
             pixel(i,j,1);                 
         }                  
     }
     //ojo der
     for(i=100;i<140;i++){
         for(j=20;j<60;j++){
             pixel(i,j,1);                 
         }                  
     }
     //comisura izq
     for(i=10;i<20;i++){
         for(j=100;j<120;j++){
             pixel(i,j,1);                 
         }                  
     }
     //comisura der
     for(i=150;i<160;i++){
         for(j=100;j<120;j++){
             pixel(i,j,1);                 
         }                  
     }
     //boca
     for(i=10;i<160;i++){
         for(j=110;j<120;j++){
             pixel(i,j,1);                 
         }                  
     }
     //lengua
     for(i=110;i<135;i++){
         for(j=120;j<155;j++){
             pixel(i,j,2);                 
         }                  
     }
}

int main(){
   BYTE modo;
   setvideomode(MODOGRAFICO);
   	printf("Pulsa una tecla... A continuacion gotoxy  ");
    pausa();
   gotoxy(7,7);
   printf("Pulsa una tecla...  ");
   pausa();
   modo=getvideomode();
   if((modo<=3&&modo>=0)||modo==7){
              printf("Modo texto");
   }
   else{
        printf("Modo grafico");
   }
   pausa();
   setvideomode(MODOTEXTO); 
   printf("Pulsa una tecla...  ");
   pausa();
   printf("\nCursor invisible: ");
   	setcursortype(0);
   	printf("Pulsa una tecla...  ");
   	pausa();
   	printf("\nCursor grueso: ");
   	setcursortype(2);
   	printf("Pulsa una tecla...  ");
   	pausa();
   	printf("\nCursor normal: ");
   	setcursortype(1);
   	printf("Pulsa una tecla para escribir una W  ");
   	pausa();
   	printf("\n");
	textbackground(3);
	textcolor(5);
	cputchar('W');
   printf("\n\nIntroduzca un caracter para mostrar");
   printf("\n");
   getche();
   printf("\n\nPulsa una tecla para borrar pantalla");
   pausa();
   clrscr();
   printf("Pulsa una tecla...  ");
   pausa();
   setvideomode(MODOGRAFICO);
   modo=getvideomode();
   if((modo<=3&&modo>=0)||modo==7){
              printf("Modo texto");
   }
   else{
        printf("Modo grafico");
   }
   printf("Pulsa una tecla...  ");
   pausa();
   setvideomode(MODOTEXTO);
   modo=getvideomode();
   if((modo<=3&&modo>=0)||modo==7){
              printf("Modo texto");
   }
   else{
        printf("Modo grafico");
   }
   printf("Pulsa una tecla...  ");
   pausa();
   recuadro_texto(6,6,15,15,3,4);
   printf("\n\nPulsa una tecla...  ");
   pausa();
   dibujografico();
	return 0;
}

