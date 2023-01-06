#include "Xor.h"

int val,accion=1;
Lista *list;


void main(){

list=crearLista();
for (int i=1;i<11;i++){
    insertarPrincipio(list,i);
}
listarInicioAFinal(list);
while (accion)
{
    printf("\nQue operacion desea realizar sobre la lista anterior?\n0.Salir\n1.Inicializar lista\n2. Verificar si esta vacia\n3.Insertar al principio\n4.Insetar al final\n5.Insertar Ordenado\n6.Buscar un elemento\n7.Sacar Principio\n8.Sacar Final\n9.Sacar primera ocurrencia\n10.Listar inicio a final\n11.Listar final a inicio\n12. imprimir cantidad de elementos\n");
    scanf("%d",&accion);
    system("clear");
    switch (accion)
    {
    case 0:
        break;
    case 1:
        inicializar(list);
        printf("Lista inicializada\n");
        break;
    case 2:
        if(esVacia(list)){
            printf("Lista vacia\n");
            break;
        }
        printf("Contiene elementos\n");
        break;
    case 3:
        printf("Introduzca valor a insertar\n");
        scanf("%d", &val);
        if(insertarPrincipio(list,val)){
            printf("Valor insertado\n");
            break;
        }
        printf("Error al insertar\n");
        break;
    case 4:
        printf("Introduzca valor a insertar\n");
        scanf("%d",&val);
        if(insertarFinal(list,val)){
            printf("Valor insertado\n");
            break;
        }
        printf("Error al insertar\n");
        break;
    case 5:
        printf("Introduzca valor a insertar\n");
        scanf("%d",&val);
        if(insertarOrden(list, val)){
            printf("Valor insertado\n");
            break;
        }
        printf("Error al insertar\n");
        break;
    case 6:
        printf("Introduzca valor a buscar: ");
        scanf("%d",&val);
        if(buscar(list, val)){
            printf("El elemento esta en la lista\n");
            break;
        }
        printf("El elemento no esta en la lista\n");
        break;
    case 7:
        if(sacarPrincipio(list,&val)){
            printf("El valor al principio de la lista era: %d\n", val);
            break;
        }
        printf("Lista vacia\n");
        break;
    case 8:
        if(sacarFinal(list,&val)){
            printf("El valor al final de la lista era: %d\n", val);
            break;
        }
        printf("Lista vacia\n");
    case 9:
        printf("Introduzca valor a sacar:");
        scanf("%d",&val);
        if(sacarPrimeraOcurrencia(list,val)){
            printf("Valor sacado\n");
            break;
        }
        printf("El valor no esta en la lista o lista vacia\n");
        break;
    case 10:
        listarInicioAFinal(list);
        break;
    case 11:
        listarFinalAInicio(list);
        break;
    case 12:
        printf("La lista es de %i elementos\n", cantidadElementos(list));
        break;
    default:
        printf("Accion invalida\n");
        break;
    }
    
}


}
