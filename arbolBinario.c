#include <stdio.h>
#include <stdlib.h>

#define NODO struct nodo

NODO{
    int dato;
    NODO *hijo_izquierdo, *hijo_derecho, *padre;
};

NODO *raiz = NULL;

void agregar_dato(void);
void buscar_dato(void);
void recorrer_arbol(void);
void eliminar_dato(void);
void acomodar(int, NODO **);
NODO *crear_nodo(int, NODO *);
NODO *buscar(int, NODO *);
void orden(NODO *);
void eliminar(NODO *);
NODO *encontrar_sucesor(NODO *);
void notificar_al_padre(NODO *);

int main(int argc, char **args){
    int opcion;
    do{
        printf("\tARBOL BINARIO\n\n");
        printf("1) Agregar elemento\n");
        printf("2) Buscar elemento\n");
        printf("3) Recorrer arbol\n");
        printf("4) Eliminar elemento\n");
        printf("5) Salir\n");
        printf("Tu opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                agregar_dato();
                break;
            case 2:
                buscar_dato();
                break;
            case 3:
                recorrer_arbol();
                break;
            case 4:
                eliminar_dato();
                break;
        }
    }while(opcion != 5);

    return 0;
}

void agregar_dato(void){
    printf("Dime cual dato vas a agregar al arbol: ");
    int dato;
    scanf("%d", &dato);
    acomodar(dato, &raiz);
}

void buscar_dato(void){
    printf("Dime cual dato quieres encontrar: ");
    int dato;
    scanf("%d", &dato);
    NODO *resultado = buscar(dato, raiz);
    if(resultado){
        printf("Tu dato se encontro en la direccion %p\n", resultado);
    }else{
        printf("Ese dato no se encuentra dentro del arbol");
    }
}

void recorrer_arbol(void){
    printf("Recorrido en orden\n");
    orden(raiz);
    printf("\n");
}

void eliminar_dato(void){
    printf("Dime cual dato quieres eliminar: ");
    int dato;
    scanf("%d", &dato);
    NODO *resultado = buscar(dato, raiz);
    if(resultado){
       eliminar(resultado);
    }else{
        printf("Ese dato no se encuentra dentro del arbol.\n");
    }
}

void acomodar(int dato, NODO **hoja){
    if(*hoja){
        if(dato > (*hoja)->dato){
            //Acomodar del lado derecho
            if((*hoja)->hijo_derecho){
                acomodar(dato, &((*hoja)->hijo_derecho));
            }else{
                (*hoja)->hijo_derecho = crear_nodo(dato, *hoja);
            }
        }else if(dato < (*hoja)->dato){
            //Acomodar del lado izquierdo
            if((*hoja)->hijo_izquierdo){
                acomodar(dato, &(*hoja)->hijo_izquierdo);
            }else{
                (*hoja)->hijo_izquierdo = crear_nodo(dato, *hoja);
            }
        }else{
            printf("Valor duplicado. No se agregara al arbol\n");
        }
    }else{
        *hoja = crear_nodo(dato, *hoja);
    }
}

NODO *crear_nodo(int dato, NODO *hoja){
    NODO *nuevo = malloc(sizeof(NODO));
    nuevo->dato = dato;
    nuevo->hijo_derecho = nuevo->hijo_izquierdo = NULL;
    nuevo->padre = hoja;
    return nuevo;
}

NODO *buscar(int dato, NODO *hoja){
    if(hoja){
        if(dato > hoja->dato){
            return buscar(dato, hoja -> hijo_derecho);
        }else if(dato < hoja -> dato){
            return buscar(dato, hoja -> hijo_izquierdo);
        }else{
            return hoja;
        }
    }else{
        return NULL;
    }
}

void orden(NODO *hoja){
    if(hoja){
        orden(hoja -> hijo_izquierdo);
        printf("%d\t", hoja -> dato);
        orden(hoja -> hijo_derecho);
    }
}

void eliminar(NODO *hoja){
    NODO *sucesor = encontrar_sucesor(hoja);
    if(sucesor){
        hoja->dato = sucesor->dato;
        eliminar(sucesor);
    }else{
        notificar_al_padre(hoja);
    }
}

NODO *encontrar_sucesor(NODO *hoja){
    NODO *p;
    if(hoja -> hijo_derecho){
        p = hoja->hijo_derecho;
        while(p->hijo_izquierdo) p = p->hijo_izquierdo;
        return p;
    }else if(hoja->hijo_izquierdo){
        p = hoja->hijo_izquierdo;
        while(p->hijo_derecho);
        return p;
    }else{
        return NULL;
    }
}

void notificar_al_padre(NODO *hoja){
    if(hoja->padre){
        NODO *padre = hoja->padre;
        if(hoja == padre->hijo_derecho){
            padre->hijo_derecho = NULL;
        }else{
            padre->hijo_izquierdo = NULL;
        }
    }else{
        raiz = NULL;
    }
    free(hoja);
}