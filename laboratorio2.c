#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wait(){// Función que espera enter
	printf("\nPara continuar, presione la tecla ENTER");
	char prev = 0;
	while(1){
		char c = getchar();
		if(c =='\n' && prev == c){
			break;
		}
		prev = c;
	}
}
struct dogType { //Estructura donde se agrupan los datos de cada registro
	char nombre[32];
	char tipo[32];
	int edad;
	char raza[16];
	int estatura;
	float peso;
	char sexo;
};
char check(char p){
	if (p=='H'||p=='h' || p == 'M' || p=='m'){
		return p;
	}else{
		printf("Por favor introduzca H (Hembra)o M (Macho)\n" );
		scanf("%s",&p);
		 return check(p);
	}
}

void record(){ //Función 1, donde se solicitan datos y almacenan


	struct dogType *p =(struct dogType*) malloc(sizeof(struct dogType));//Reserva espacio para estructura
	printf("Nombre: ");//Solicita los datos de la mascota
	scanf("%s", p -> nombre);
	printf("Tipo: ");
	scanf("%s",p -> tipo);
	printf("Edad: ");
	scanf("%i",&p -> edad);
	printf("Raza: ");
	scanf("%s",p -> raza);
	printf("Estatura: ");
	scanf("%i",&p -> estatura);
	printf("Peso: ");
	scanf("%f",&p -> peso);
	printf("Sexo: ");
	scanf("%s",p );
	char tmp = check(p);
	mempcpy((&p->sexo), &tmp, sizeof(char));
	printf("Se ha guardado su registro");
}






int main ()
{
	int flag = 1;
	while (flag == 1){
		int opc;
		printf("\n1. Ingresar registro");
		printf("\n2. Ver registro");
		printf("\n3. Borrar registro");
		printf("\n4. Buscar registro");
		printf("\n5. Salir\n");
		scanf("%i", &opc);
		if(opc==1){
			wait();
			record();
			wait();
		}else if(opc == 2){
			wait();
		}else if(opc == 3){
			wait();
		}else if(opc == 4){
			wait();
		}else if (opc == 5){
			wait();
			exit(0);
		}
	}

}
