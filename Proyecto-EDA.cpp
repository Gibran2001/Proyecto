#include<stdio.h>
#include<ctype.h>
#include<locale.h>
#include<stdlib.h>

//Estas son nuestras estructuras
typedef struct fecha{
	short dia,anio;
	char *mes;
}fecha;
typedef struct datosBoleto{
	char *calidad,*artista;
	int precio,sub;
	short numeroBoletos;
	fecha f;
}datosBoleto;

//Estas son las variables globales, se van a usar tanto en la funcion principal como en las funciones secundarias
datosBoleto boletos[5];//Un arreglo de estructuras, pero que también va a funcionar como nuestra pila de 5 espacios
short x=0,*tope=NULL;//El tope de la pila apunta a NULL porque está vacia
int total=0;//El total almacena la suma de todos los subtotales parciales de la compra
FILE *ticket;//Apuntador al archivo

//Funciones secundarias
int proceso();//Esta es la que va a hacer todo el proceso de calcular el precio de los boletos con base a su calidad y la cantidad
void imprimirTicket();//Esta es la funcion que imprimira los datos en el ticket


//Funcion principal
int main(){
	short opcionArtista;
	char inc1;
	setlocale(LC_ALL, "");
	printf("\t\t\t\t\tBienvenido a Boletos_Garrett.com\n\n");
	system("pause");
	ticket=fopen("ticket.txt","w");//Abrimos el archivo en el que se va a imprimir el ticket
	fprintf(ticket,"\t\t\tBoletos Garrett\n\n\n");
	//Este ciclo repite el menu principal las veces que el usuario decida o en caso de que ingrese opcion invalida
	do{
		printf("\n\nPor favor selecciona un artista para tu próximo concierto (puedes hacer sólo 5 compras distintas)\n\n");
		printf("1.Roger Waters - 02 de Octubre de 2020\n2.Harry Styles - 5 de Noviembre de 2020\n3.Coldplay - 1 de Enero de 2021\n4.Maroon 5 - 5 de Mayo de 2021\n5.Rammstein - 26 de Septiembre de 2020\n\n");
		scanf("%d",&opcionArtista);
		//Se despliega el menu principal
		switch(opcionArtista){
			case 1://Roger Waters
				tope=&x;//El tope de nuestra pila ya apunta a un valor porque no está vacia
				boletos[x].f.dia=2;
				boletos[x].f.mes="Octubre";
				boletos[x].f.anio=2020;
				boletos[x].sub=proceso();//Invocamos a nuestra funcion secundaria
				boletos[x].artista="Roger Waters";
				total+=boletos[x].sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1=='s')
					x++;
				else{
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
				}
				break;
			case 2://Harry Styles
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].f.dia=5;
				boletos[x].f.mes="Noviembre";
				boletos[x].f.anio=2020;
				boletos[x].sub=proceso();
				boletos[x].artista="Harry Styles";
				total+=boletos[x].sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1=='s')
					x++;
				else{
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
				}
				break;
			case 3://Coldplay
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].f.dia=1;
				boletos[x].f.mes="Enero";
				boletos[x].f.anio=2021;
				boletos[x].sub=proceso();
				boletos[x].artista="Coldplay";
				total+=boletos[x].sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1=='s')
					x++;
				else{
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
				}
				break;
			case 4://Maroon 5
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].f.dia=5;
				boletos[x].f.mes="Mayo";
				boletos[x].f.anio=2021;
				boletos[x].sub=proceso();
				boletos[x].artista="Maroon 5";
				total+=boletos[x].sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1=='s')
					x++;
				else{
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
				}
				break;
			case 5://Rammstein
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].f.dia=26;
				boletos[x].f.mes="Septiembre";
				boletos[x].f.anio=2020;
				boletos[x].sub=proceso();
				boletos[x].artista="Rammstein";
				total+=boletos[x].sub;
				printf("\nDeseas comprar mas boletos?(s/n) ");
				scanf("%s",&inc1);
				inc1=tolower(inc1);
				if(inc1=='s')
					x++;
				else{
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
				}
				break;
			default:
				//Si el usuario ingresa opcion incorrecta, sale el defecto para redireccionarlo al menu principal
				printf("Opcion incorrecta. Por favor presiona 's' para volver aelegir un artista ");
				scanf("%c",&inc1);
				inc1=tolower(inc1);
				break;
		}
	}
	while((inc1=='s')and(x<=4));//Condicional, si el usuario quiere comprar de nuevo y que a la vez aún tenga menos de 5 compras realizadas
	//Mensaje en caso ed que el usuario haya exedido el número de compras permitidas
	if(x>4){
		*tope=4;//El tope ya no aumenta, se queda en la pocison 5
		puts("Has rebasado el limite de 5 compras");
		printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...",total);
	}
	imprimirTicket();//Invocamos a la función para imprimir el ticket
	fprintf(ticket,"Total:  %d",total);
	fclose(ticket);//Cerramos el archivo
	return 0;
}


//Aquí empieza nuestra función secundaria
int proceso(){
	short tipoBoletos;
	int subtotal;
	char inc2;
	subtotal=0;//Siempre que se abre la funcion se inicializa en 0
	//Igualmente se repite las veces necesarias en caso de que el usuario ingrese opcion invalida
	do{
		printf("\n\nSelecciona el tipo de boleto\n");
		printf("1.Premium ($3,000)\n2.Regular ($2000)\n3.Economico ($700)\n");
		scanf("%d",&tipoBoletos);
		switch(tipoBoletos){
			case 1:
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Premium";
				boletos[x].precio=3000;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';//Se inicializa en 'n' para que esta parte no se repita ya que la opcion es valida
				break;
			case 2:
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Regular";
				boletos[x].precio=2000;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';
				break;
			case 3:
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Economico";
				boletos[x].precio=700;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				printf("Tu subtotal es: %d",subtotal);
				inc2='n';
				break;
			default:
				printf("Opcion incorrecta. Por favor presiona s para volver aelegir tu tipo de boleto ");
				scanf("%c",&inc2);
				inc2=tolower(inc2);
		}
	}
	while(inc2=='s');
	return subtotal;//Retorna el valor del subtotal de la compra
}

//Esta es la funcion que imprime los datos del boleto, excepto por el total de toda la compra
void imprimirTicket(){
	/*Imprime los datos de las compras desde el tope, por si el usuario no usó sus 5 compras
	Siguiendo el principio FILO, muestra primero la última compra realizada*/
	for(x=*tope; x>=0; x--){
		fprintf(ticket,boletos[x].artista);
		fprintf(ticket,"\n\nFecha: %d / %s / %d\n",boletos[x].f.dia,boletos[x].f.mes,boletos[x].f.anio);
		fprintf(ticket,"Calidad del boleto: %s\n\n",boletos[x].calidad);
		fprintf(ticket,"Cant Precio\n");
		fprintf(ticket,"%d    %d\n",boletos[x].numeroBoletos,boletos[x].precio);
		fprintf(ticket,"Subtotal: %d\n\n",boletos[x].sub);
	}
}
