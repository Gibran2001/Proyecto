#include<stdio.h>
#include<ctype.h>
#include<locale.h>
#include<stdlib.h>

//Estas son nuestras estructuras, vemos que una estructura contiene una estructura adentro
typedef struct fechaBoleto{
	short dia;
	char *mes;
	short anio;
}fecha_b;

typedef struct datosBoleto{
	char *calidad;
	int precio;
	fecha_b fecha;
}datosBoleto;

//Estas son las variables globales, se van a usar tanto en la funcion principal como en las funciones secundarias
datosBoleto boletos[50];
short numeroBoletos, x=0;
int precioBoletos,sub;
//Apuntador al archivo
FILE *ticket;
int proceso();
//Esta es la que va a hacer todo el proceso de calcular el precio de los boletos con base a su calidad y la cantidad
void imprimirTicket();
//Esta es la funcion que imprimira los datos de la funcion


int main(){
	short opcionArtista;
	int total=0;//El total almacena la suma de todos los subtotales parciales de la compra
	char inc1;
	setlocale(LC_ALL, "");
	printf("\t\t\t\t\tBienvenido a Boletos_Garrett.com\n\n");
	system("pause");
	ticket=fopen("ticket.txt","w");
	fprintf(ticket,"\t\t\tBoletos Garrett\n\n\n");
	//Este ciclo repite el menu principal las veces que el usuario decida o en caso de que ingrese opcion invalida
	do{
		printf("Por favor selecciona un artista para tu próximo concierto\n\n");
		printf("1.Roger Waters - 02 de Octubre de 2020\n2.Harry Styles - 5 de Noviembre de 2020\n3.Coldplay - 1 de Enero de 2021\n4.Maroon 5 - 5 de Mayo de 2021\n5.Rammstein - 26 de Septiembre de 2020\n\n");
		scanf("%d",&opcionArtista);
		//Se despliega el menu principal
		switch(opcionArtista){
			case 1://Roger Waters
				boletos[x].fecha.dia=2;
				boletos[x].fecha.mes="Octubre";
				boletos[x].fecha.anio=2020;
				sub=proceso();//Invocamos a nuestra funcion secundaria
				fprintf(ticket,"Roger Waters\n");	
				imprimirTicket();
				total=total+sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1!='s'){
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
					fprintf(ticket,"Total:  %d",total);
					fclose(ticket);
				}
				else
					x++;
				break;
			case 2://Harry Styles
				boletos[x].fecha.dia=5;
				boletos[x].fecha.mes="Noviembre";
				boletos[x].fecha.anio=2020;
				sub=proceso();
				fprintf(ticket,"Harry Styles\n");
				imprimirTicket();
				total=total+sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1!='s'){
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
					fprintf(ticket,"Total:  %d",total);
					fclose(ticket);
				}
				else
					x++;
				break;
			case 3://Coldplay
				boletos[x].fecha.dia=1;
				boletos[x].fecha.mes="Enero";
				boletos[x].fecha.anio=2021;
				sub=proceso();
				fprintf(ticket,"Coldplay\n");
				imprimirTicket();
				total=total+sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1!='s'){
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
					fprintf(ticket,"Total:  %d",total);
					fclose(ticket);
				}
				else
					x++;
				break;
			case 4://Maroon 5
				boletos[x].fecha.dia=5;
				boletos[x].fecha.mes="Mayo";
				boletos[x].fecha.anio=2021;
				sub=proceso();
				fprintf(ticket,"Maroon 5\n");
				imprimirTicket();
				total=total+sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1!='s'){
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
					fprintf(ticket,"Total:  %d",total);
					fclose(ticket);
				}
				else
					x++;
				break;
			case 5://Rammstein
				boletos[x].fecha.dia=26;
				boletos[x].fecha.mes="Septiembre";
				boletos[x].fecha.anio=2020;
				sub=proceso();
				fprintf(ticket,"Rammstein\n");
				imprimirTicket();
				total=total+sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1!='s'){
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
					fprintf(ticket,"Total:  %d",total);
					fclose(ticket);
				}
				else
					x++;
				break;
			default:
				//Si el usuario ingresa opcion incorrecta, sale el defecto para redireccionarlo al menu principal
				printf("Opcion incorrecta. Por favor presiona 's' para volver aelegir un artista ");
				scanf("%c",&inc1);
				inc1=tolower(inc1);
				break;
		}
	}
	while(inc1=='s');
	return 0;
}


//Aquí empieza nuestra función secundaria
int proceso(){
	short tipoBoletos;
	int subtotal;
	char inc2;
	subtotal=0;//Aquí siempre que se abre la funcion, el subtotal se inicializa en 0
	//Igualmente se repite las veces necesarias
	do{
		printf("Por favor selecciona la cantidad de boletos deseados ");
		scanf("%d",&numeroBoletos);
		printf("\n\nSelecciona el tipo de boleto\n");
		printf("1.Premium ($3,000)\n2.Regular ($2000)\n3.Economico ($700)\n");
		scanf("%d",&tipoBoletos);
		switch(tipoBoletos){
			case 1:
				boletos[x].calidad="Premium";
				boletos[x].precio=3000;
				subtotal=subtotal+(boletos[x].precio*numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';
				break;
			case 2:
				boletos[x].calidad="Regular";
				boletos[x].precio=2000;
				subtotal=subtotal+(boletos[x].precio*numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';
				break;
			case 3:
				boletos[x].calidad="Economico";
				boletos[x].precio=700;
				subtotal=subtotal+(boletos[x].precio*numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';
				break;
			default:
				printf("Opcion incorrecta. Por favor presiona s para volver aelegir tu numero y tipo de boletos ");
				scanf("%c",&inc2);
				inc2=tolower(inc2);
		}
	}
	while(inc2=='s');
	return subtotal;//Retorna el valor del subtotal de la compra
}


//Esta es la funcion que imprime los datos del boleto, excepto por el nombre del artista y el total de toda la compra
void imprimirTicket(){
	fprintf(ticket,"\nFecha: %d / %s / %d\n",boletos[x].fecha.dia,boletos[x].fecha.mes,boletos[x].fecha.anio);
	fprintf(ticket,"Calidad del boleto: %s\n\n",boletos[x].calidad);
	fprintf(ticket,"Cant Precio\n");
	fprintf(ticket,"%d    %d\n",numeroBoletos,boletos[x].precio);
	fprintf(ticket,"Subtotal: %d\n\n",sub);
}
