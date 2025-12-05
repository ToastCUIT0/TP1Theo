/* ==================================== Include    =================================== */
#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

/* ==================================== Functions and procedures =================================== */
// creation liste vide
T_liste creer_liste(){
    return NULL;
}

// ajout en tete de liste de element avec modification de la liste
void ajout_entete_liste(T_liste* l,int element){
    if(element >= 0){
    T_liste t = malloc(sizeof(T_liste));
    t->val = element;
    t->next = (*l);
    *l = t;
}
}


// ajout en tete selon une approche fonctionnelle sans modification de la liste
T_liste ajouter_entete_fonc(T_liste l, int element){
    if(element >= 0){
    T_liste t = malloc(sizeof(T_liste));
    t->val = element;
    t->next = l;
    return t;
    }
    else{return l;}
}

// affichages
// itératif
void afficher_liste(T_liste l){
    T_liste courant = l;
    while (courant != NULL){
        printf("%d->",courant->val);
        courant = courant ->next;
    }
    printf("NULL\n");
}
// récursif dans l ordre de la liste
void fafficher_dir_liste(T_liste l){
    if (l != NULL){
    printf("%d->",l->val);
    fafficher_dir_liste(l->next);
    }
    else{
        printf("NULL\n");
    }
}
// récursif dans l ordre inverse de la liste
void fafficher_inv_liste(T_liste l){
    if (l != NULL){
    fafficher_inv_liste(l->next);
    printf("<-%d",l->val);
    }
    else{
        printf("NULL");
    }
}

// inversion iterative d'une liste selon une approche MIS
void inv_mis_liste(T_liste* l){
    T_liste courant = (*l)->next;
    T_liste precedent = *l;
    while(courant != NULL){
        T_liste tmp = courant;
        courant = courant->next;
        tmp->next =  precedent;
        precedent = tmp;
    }
    (*l)->next = NULL;
    *l = precedent;

}
// inversion iterative d'une liste selon une approche fonctionnelle
T_liste inv_fonc_liste(T_liste l){
    T_liste courant = l->next;
    T_liste precedent = l;
    while(courant != NULL){
        T_liste tmp = courant;
        courant = courant->next;
        tmp->next =  precedent;
        precedent = tmp;
    }
    l->next = NULL;
    T_liste t = creer_liste();
    while(precedent != NULL){
        ajout_entete_liste(&t,precedent->val);
        precedent = precedent->next;
    }
    return t;
}

// comptage du nombre d'elements d'une liste
// selon une approche recursive enveloppee
int long_env(T_liste l){
    if (l == NULL){
        return(0);
    }
    else{
    return (long_env(l->next) + 1);
    }
}
// selon une approche recursive terminale
int long_ter(T_liste liste, int aux){
    if (liste == NULL){
        return(aux);
    }
    else{
        return(long_ter(liste->next,aux+1));
    }
}

int max_env(T_liste l,int aux){
    if (l == NULL){
        return(aux);
    }
    else{
        if (aux >= l->val){
        return(max_env(l->next,aux));
        }
        else{return(max_env(l->next,l->val));}
    }
}

// selon une approche recursive terminale
int max_ter(T_liste l, int aux){
    if (l == NULL){
        return(aux);
    }
    else{
        if (aux >= l->val){
        return(max_ter(l->next,aux));
        }
        else{
            return(max_ter(l->next,l->val));}
    }
}

// inversion recursive enveloppee d'une liste
T_liste inversion_rec_env(T_liste l){
    if (l == NULL){
        return NULL;
    }
    else if (l->next == NULL){
        return l;
    }
    else {
        T_liste tmp = inversion_rec_env(l->next);
        l->next->next = l;
        l->next = NULL;
        return tmp;
    }
}

// inversion recursive terminale d'une liste
T_liste inversion_aux_rec_term(T_liste courant, T_liste precedent,int i){
    if(courant == NULL){
        return precedent;
    }
    else{
        T_liste tmp = courant;
        courant = courant->next;
        tmp->next = precedent;
        if (i ==0){
            precedent->next = NULL;
        }
        return(inversion_aux_rec_term(courant,tmp,i+1));
    }
}

T_liste inversion_rec_term(T_liste l){
    if (l == NULL){
        return NULL;
    }
    else{
        return(inversion_aux_rec_term(l->next,l,0));
    }
}

// liberation de la mémoire
void liberer_liste(T_liste l){
    if (l != NULL){
        T_liste tmp = l->next;
        free(l);
        liberer_liste(tmp);
    }
}


int main(){
    T_liste l = creer_liste();
    ajout_entete_liste(&l,2);
    ajout_entete_liste(&l,8);
    ajout_entete_liste(&l,9);
    ajout_entete_liste(&l,4);
    afficher_liste(l);
    fafficher_dir_liste(l);
    fafficher_inv_liste(l);
    printf("\n");
    inv_mis_liste(&l);
    afficher_liste(l);
    l = inv_fonc_liste(l);
    afficher_liste(l);
    int x1 = long_env(l);
    printf("%d \n",x1);
    int x2 = long_ter(l,0);
    printf("%d \n",x2);
    x1 = max_env(l,-1);
    printf("%d \n",x1);
    x2 = max_ter(l,-1);
    printf("%d \n",x2);
    l = inversion_rec_env(l);
    afficher_liste(l);
    l = inversion_rec_term(l);
    afficher_liste(l);
}
