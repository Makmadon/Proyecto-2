#include "Xor.h"

//Funcion auxiliar para hacer la operacion XOR
Nodo *XOR(Nodo *a, Nodo *b){
    return ((Nodo*)((uintptr_t)(a) ^(uintptr_t)(b)) );
}
//Funcion auxiliar para crear lista
Lista *crearLista(){
    return (Lista*)malloc(sizeof(Lista));
}
//Funcion para inicializar
void inicializar(Lista *list){
    //En caso de que no este inicializada solo se llama a crear lista
    if(list==NULL){
        list=crearLista();
        return;
    }
    //En caso contrario se recorre la lista haciendo free a cada uno de los nodos hasta que quede vacia
    list->ultimo=NULL;
    Nodo *prev=NULL,*curr;
    while(list->primer){
        curr=list->primer;
        list->primer=XOR(list->primer->AA,prev);
        prev=curr;
        free(curr);
    }
}
//funcion auxiliar crear nodo
Nodo *crearNodo(int val){
    Nodo *newp=(Nodo*)malloc(sizeof(Nodo));
    newp->elemento=val;
    return newp;
}
//Funcion que verifica si la lista esta vacia, esto solo pasa si el primer y ultimo elemento son NULL
bool esVacia(Lista *list){
    if (list->primer==NULL && list->ultimo==NULL)
        return true;
    return false;
}
//Funcion para insertar al inicio de una lista
bool insertarPrincipio(Lista *list,int val){
    //se crea el nuevo nodo, si hay un error en su creacion, se retorna falso
    Nodo *newp=crearNodo(val);
        if(newp==NULL)
            return false;
    //se verifica que la lista este vacia, si es verdadero, el nuevo nodo creado sera el primero y el ultimo
    if (esVacia(list)){
        list->primer=newp;
        list->ultimo=newp;
        return true;
    }
    /*Si no es vacia, el actual primer elemento tiene que apuntar a este, por lo que se hace Xor con el nuevo nodo
    no se hace XOR para retirar un NULL porque XOR con NULL es el mismo elemento, 
    el nuevo nodo solo apuntara al primero actual, y por ultimo el nuevo nodo pasa a ser el primero de la lista*/
    list->primer->AA=XOR(list->primer->AA,newp);
    newp->AA=list->primer;
    list->primer=newp;
    return true;
}
    //Funcion para insertar al final (Es muy parecido con insertar inicio)
bool insertarFinal(Lista *list, int val){
    //Las mismas operaciones que antes
    Nodo *newp=crearNodo(val);
    if(newp==NULL)
        return false;
    if (esVacia(list)){
        list->primer=newp;
        list->ultimo=newp;
        return true;
    }
    /*En vez de hacer las operaciones con el primer elemento, se hacen con el ultimo*/
    list->ultimo->AA=XOR(list->ultimo->AA,newp);
    newp->AA=list->ultimo;
    list->ultimo=newp;
    return true;
}

bool insertarOrden(Lista *list,int val){
    Nodo *prev=NULL;
    Nodo *curr=list->primer;
    Nodo *next=list->primer;
    Nodo *newp=crearNodo(val);
    if(newp==NULL)
        return false;
    if(val<=list->primer->elemento){ 
        insertarPrincipio(list,val);
        return true;
    }  

    if(list->ultimo->elemento<=val){
        insertarFinal(list,val);
        return true;
    }
    
    while (curr){
        next=XOR(prev,curr->AA);
        if(curr->elemento<=val && val < next->elemento){
            curr->AA=XOR(newp,XOR(curr->AA,next));
            next->AA=XOR(newp,XOR(next->AA,curr));
            newp->AA=XOR(curr,next);
            return true;
        }
        prev=curr;
        curr=next;
    }

    return false;
}

bool buscar(Lista *list, int val){
    Nodo *prev=NULL;
    Nodo *next;
    Nodo *curr=list->primer;

    while (curr){
        if(curr->elemento==val)
            return true;
        next=XOR(prev,curr->AA);
        prev=curr;
        curr=next;
    }
    return false;
}

bool sacarPrincipio(Lista *list, int *val){
    if (list->primer==NULL)
        return false;
    Nodo *prev=list->primer;
    *val=list->primer->elemento;
    list->primer=list->primer->AA;
    free(prev);
    list->primer->AA=XOR(prev,list->primer->AA);
    return true;
}

bool sacarFinal(Lista *list, int *val){
    if (list->ultimo==NULL)
        return false;
    Nodo *prev=list->ultimo;
    *val=list->ultimo->elemento;
    list->ultimo=list->ultimo->AA;
    free(prev);
    list->ultimo->AA=XOR(prev,list->ultimo->AA);
    return true;
}

bool sacarPrimeraOcurrencia(Lista *list, int val){
    Nodo *prev=NULL;
    Nodo *next;
    Nodo *curr=list->primer;
    while (curr){
        if(curr->elemento==val){
            if(prev==NULL)
                return sacarPrincipio(list,&val);
            next=XOR(prev,curr->AA);
            next->AA=XOR(prev,XOR(next->AA,curr));
            prev->AA=XOR(next,XOR(prev->AA,curr));
            free(curr);
            return true;
        }
        next=XOR(prev,curr->AA);
        prev=curr;
        curr=next;
    }
    return false;
}

void listarInicioAFinal(Lista *list){
    Nodo *prev=NULL;
    Nodo *next;
    Nodo *curr=list->primer;
    printf("NULL <-> ");
    while (curr){
        printf("%d <-> ",curr->elemento);
        next=XOR(prev,curr->AA);
        prev=curr;
        curr=next;
    }
    printf("NULL\n");
}

void listarFinalAInicio(Lista *list){
    Nodo *prev=NULL;
    Nodo *next;
    Nodo *curr=list->ultimo;
    printf("NULL <-> ");
    while (curr){
        printf("%d <->",curr->elemento);
        next=XOR(prev,curr->AA);
        prev=curr;
        curr=next;
    }
    printf("NULL\n");
}

int cantidadElementos(Lista *list){
int cant=0;
Nodo *prev=NULL;
    Nodo *next;
    Nodo *curr=list->ultimo;

    while (curr)
    {
        cant++;
        next=XOR(prev,curr->AA);
        prev=curr;
        curr=next;
    }
return cant;
}
