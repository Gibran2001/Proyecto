#include<stdio.h>
#include<ctype.h>
#include<locale.h>
#include<stdlib.h>

//Estas son nuestras estructuras

typedef struct fecha{
	short dia,anio;
	char *mes;
}fecha;
typedef struct datosBoletoPila{
	char *calidad,*artista;
	int precio,sub;
	short numeroBoletos;
	fecha f;
}pila;


//Estas son las variables globales, se van a usar tanto en la funcion principal como en las funciones secundarias

pila boletos[5];//Un arreglo de estructuras que también va a funcionar como nuestra pila de 5 espacios
short x=0,y=5,*tope=NULL;//Contadores y el tope de la pila que apunta a NULL porque está vacia
int total=0,saldo;//El total almacena la suma de todos los subtotales parciales de la compra
char usuario[10];//El nombre que el usuario va a elegir
FILE *ticket;//Apuntador al archivo


//Funciones secundarias

char procesosGenerales();//Esta es nuestra función secundaria que hace todos los procesos de la compra
int procesoPrecio();//Esta es la que va a calcular el precio de los boletos con base a su calidad y la cantidad
void imprimir();//Esta es la funcion que imprimirá los datos en el ticket y llamará a la función para hacerlo en pantalla
void imprimirPantalla();//Imprime los mismos datos de la compra en la pantalla
void pop();//Esta quita los elementos de la pila

//Funcion principal
int main(){
	short opcion;
	char inc1;
	setlocale(LC_ALL, "");
	printf("\t\t\t\t\tBienvenido a Boletos_Garrett.com\n\n");
	system("pause");
	ticket=fopen("ticket.txt","w");//Abrimos el archivo en el que se va a imprimir el ticket
	system("cls");//Borramos patalla
	printf("\t\t\t\t\tBienvenido a Boletos_Garrett.com\n\n");//Imprimimos nuevamente el mensaje inicial porque tambien lo borramos
	printf("Ingresa tu nombre de usuario Boletos_Garrett ");
	scanf("%s",&usuario);
	printf("Ingresa el saldo con el que dispones para tus compras ");
	scanf("%d",&saldo);
	//Este ciclo repite el menu principal las veces que el usuario decida o en caso de que ingrese opcion invalida
	do{
		system("cls");//Borramos patalla nuevamente
		printf("\t\t\t\t\tBienvenido a Boletos_Garrett.com\n\n");//Nevamente mensaje inicial
		printf("Usuario: %s\t\t\tSaldo: $%d\t\t\tCompras restantes: %d\n",usuario,saldo,y);
		puts("\n||1.Roger Waters - 02 de Octubre de 2020  ||");
		puts("\n||2.Harry Styles - 5 de Noviembre de 2020 ||");
		puts("\n||3.Coldplay - 1 de Enero de 2021         ||");
		puts("\n||4.Maroon 5 - 5 de Mayo de 2021          ||");
		puts("\n||5.Rammstein - 26 de Septiembre de 2020  ||");
		puts("\n||6.Salir                                 ||");
		printf("\nPor favor selecciona un artista para tu próximo envento (puedes hacer sólo 5 compras distintas) ");
		scanf("%d",&opcion);
		//Se despliega el menu principal
		switch(opcion){
			case 1://Roger Waters
				tope=&x;//El tope de nuestra pila ya apunta a un valor porque no está vacia
				boletos[x].artista="Roger Waters";
				boletos[x].f.dia=2;
				boletos[x].f.mes="Octubre";
				boletos[x].f.anio=2020;
				inc1=procesosGenerales();//Invocamos a nuestra función secundaria
				break;
			case 2://Harry Styles
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].artista="Harry Styles";
				boletos[x].f.dia=5;
				boletos[x].f.mes="Noviembre";
				boletos[x].f.anio=2020;
				inc1=procesosGenerales();
				break;
			case 3://Coldplay
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].artista="Coldplay";
				boletos[x].f.dia=1;
				boletos[x].f.mes="Enero";
				boletos[x].f.anio=2021;
				inc1=procesosGenerales();
				break;
			case 4://Maroon 5
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].artista="Maroon 5";
				boletos[x].f.dia=5;
				boletos[x].f.mes="Mayo";
				boletos[x].f.anio=2021;
				inc1=procesosGenerales();
				break;
			case 5://Rammstein
				tope=&x;//El tope de nuestra pila ya apunta a un valor
				boletos[x].artista="Rammstein";
				boletos[x].f.dia=26;
				boletos[x].f.mes="Septiembre";
				boletos[x].f.anio=2020;
				inc1=procesosGenerales();
				break;
			case 6://Salir
				if((tope==NULL)or(x==0)){//Condicional, compara si la pila está vacía o en la primera compra decide cancelar y salir
					puts("Gracias por su visita");
					system("pause");
					tope=NULL;//Apuntamos el tope a NULL si es que ya apuntaba a al primer elemento y decidió cancelar
				}
				//En caso contrario, que ya tenga elementos y el usuario ya no quiera comprar
				else{
					x--;//Se regresa un espacio y por tanto tambien el tope	
					printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...\n\n",total);
				}
				inc1='n';//Para que no se repita el ciclo
				break;		
			default://Si el usuario ingresa opcion incorrecta, sale el defecto para redireccionarlo al menu principal
				printf("Opcion incorrecta. Por favor presiona 's' para volver al menú pruncipal ");
				scanf("%c",&inc1);
				inc1=tolower(inc1);
				break;
		}
	}
	while((inc1=='s')and(x<=4));//Condicional, si el usuario quiere comprar de nuevo y que a la vez aún tenga menos de 5 compras realizadas
	//Mensaje en caso de que el usuario haya exedido el número de compras permitidas
	if(x>4){
		x--;//El tope eregresa, se queda en la pocison 5
		puts("Has rebasado el limite de 5 compras");
		printf("Tu total es %d\nGracias por tu visita, su ticket será generado a la brevedad...\n",total);
		system("pause");
		imprimir();
	}
	else if(tope!=NULL){//Si la pila tiene elementos invocamos a la función para imprimir en el ticket y en pantalla
		imprimir();
	}
	fclose(ticket);//Cerramos el archivo
	return 0;
}


//Funcion para los procesos de la compra
char procesosGenerales(){
	char a;
	boletos[x].sub=procesoPrecio();//Invocamos a nuestra funcion que calcula los precios
	//En caso de que el subtotal no sea un valor nulo
	if(boletos[x].sub!=NULL){
		saldo-=boletos[x].sub;//Le restamos el precio al saldo del ususario
		//Si el subtotal de la compra es mayor al saldo
		if(saldo<0){
			puts("\nLo sentimos, tu saldo es insuficienta para esta compra, por favor regresa y elige del menú principal");
			saldo+=boletos[x].sub;//Establecemos nuevamente el saldo
			printf("Tu saldo disponible es: %d\n",saldo);
			pop();//Borramos los datos de la pila
			a='s';
			system("pause");
		}
		else{
			total+=boletos[x].sub;//Ahora lo sumamos al total
			printf("Tu subtotal es: %d",boletos[x].sub);
			printf("\nDeseas comprar mas boletos?(s/n) ");
			scanf("%s",&a);
			a=tolower(a);
			if(a=='s'){
				x++;//Aumenta el contador y por tanto el tope
				y--;//Disminuye en 1 las compras restantes
			}
			else
				printf("Tu total es %d\nGracias por tu compra, su ticket será generado a la brevedad...\n\n\n",total);			
		}
	}
	//En caso de que haya regresado un valor nulo
	else{
		pop();//Borra todos los datos previamenteestablecidos
		a='s';//Manda una 's' para que se repita el proceso del menú
	}
	return a;
}

//Aquí empieza nuestra función para calcular el precio
int procesoPrecio(){
	short tipoBoletos;
	int subtotal=0;//Siempre que se abre la funcion se inicializa en 0
	char inc2;
	//Igualmente se repite las veces necesarias en caso de que el usuario ingrese opcion invalida
	do{
		puts("\n||1.Premium ($3,000) ||");
		puts("\n||2.Regular ($1,800) ||");
		puts("\n||3.Económico ($700) ||");
		puts("\n||4.Regresar         ||");
		printf("\nSelecciona el tipo de boleto ");
		scanf("%d",&tipoBoletos);
		switch(tipoBoletos){
			case 1://Premium
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Premium";
				boletos[x].precio=3000;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				inc2='n';//Se inicializa en 'n' para que esta parte no se repita ya que la opcion es valida
				break;
			case 2://Regular
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Regular";
				boletos[x].precio=1800;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				inc2='n';
				break;
			case 3://Económico
				printf("Por favor selecciona la cantidad de boletos deseados ");
				scanf("%d",&boletos[x].numeroBoletos);
				boletos[x].calidad="Economico";
				boletos[x].precio=700;
				subtotal=subtotal+(boletos[x].precio*boletos[x].numeroBoletos);
				inc2='n';
				break;
			case 4://Regresar
				subtotal=NULL;//Va a regresar un valor nulo
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

//Esta es la función que imprime los datos de la compra
void imprimir(){
	fprintf(ticket,"\t\t\tBoletos Garrett\n\n\n\n\n");
	fprintf(ticket,"Usuario: %s\n",usuario);
	/*Imprime los datos de las compras desde el tope, por si el usuario no usó sus 5 compras y aún
	no está llena la pila. Siguiendo el principio FILO, muestra primero la última compra realizada*/
	for(x=*tope; x>=0; x--){
		//Empezamos imprimiendo en el ticket
		fprintf(ticket,"* %s",boletos[x].artista);
		fprintf(ticket,"\n\nFecha: %d / %s / %d\n",boletos[x].f.dia,boletos[x].f.mes,boletos[x].f.anio);
		fprintf(ticket,"Calidad del boleto: %s\n",boletos[x].calidad);
		fprintf(ticket,"Cant Precio\n");
		fprintf(ticket,"%d    %d\n",boletos[x].numeroBoletos,boletos[x].precio);
		fprintf(ticket,"Subtotal: %d\n\n",boletos[x].sub);
		puts("\t\t\tDatos de la compra\n\n");//Iniciamos la impresión en pantalla
		imprimirPantalla();//Invocamos a la función
		pop();//Eliminamos los elementos de la pila
	}
	fprintf(ticket,"Total:  %d",total);//Al final imprime el total
	tope=NULL;//La pila está vacia
}

//Esta es la función que imprime los datos en pantalla
void imprimirPantalla(){
	printf("* %s",boletos[x].artista);
	printf("\n\nFecha: %d / %s / %d\n",boletos[x].f.dia,boletos[x].f.mes,boletos[x].f.anio);
	printf("Calidad del boleto: %s\n",boletos[x].calidad);
	printf("Cant Precio\n");
	printf("%d    %d\n",boletos[x].numeroBoletos,boletos[x].precio);
	printf("Subtotal: %d\n\n",boletos[x].sub);
	printf("Total:  %d",total);//Al final imprime el total
}

//Hace la operación para quitar elementos de la pila
void pop(){
	boletos[x].artista=NULL;
	boletos[x].calidad=NULL;
	boletos[x].precio=NULL;
	boletos[x].numeroBoletos=NULL;
	boletos[x].sub=NULL;
	boletos[x].f.dia=NULL;
	boletos[x].f.mes=NULL;
	boletos[x].f.anio=NULL;
}
