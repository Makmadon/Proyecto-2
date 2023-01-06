#include "Xor.h"

Nodo *XOR(Nodo *a, Nodo *b){
    return ((Nodo*)((uintptr_t)(a) ^(uintptr_t)(b)) );
}

Lista *crearLista(){
    return (Lista*)malloc(sizeof(Lista));
}

void inicializar(Lista *list){
    if(list==NULL){
        list=crearLista();
        return;
    }
    list->ultimo=NULL;
    Nodo *prev=NULL,*curr;
    while(list->primer){
        curr=list->primer;
        list->primer=XOR(list->primer->AA,prev);
        prev=curr;
        free(curr);
    }
}

Nodo *crearNodo(int val){
    Nodo *newp=(Nodo*)malloc(sizeof(Nodo));
    newp->elemento=val;
    return newp;
}

bool esVacia(Lista *list){
    if (list->primer==NULL && list->ultimo==NULL)
        return true;
    return false;
}

bool insertarPrincipio(Lista *list,int val){
    Nodo *newp=crearNodo(val);
        if(newp==NULL)
            return false;
    if (esVacia(list)){
        list->primer=newp;
        list->ultimo=newp;
        return true;
    }
    list->primer->AA=XOR(list->primer->AA,newp);
    newp->AA=list->primer;
    list->primer=newp;
    return true;
}

bool insertarFinal(Lista *list, int val){
    Nodo *newp=crearNodo(val);
    if(newp==NULL)
        return false;
    if (esVacia(list)){
        list->primer=newp;
        list->ultimo=newp;
        return true;
    }
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