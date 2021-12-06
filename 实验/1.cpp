/*
    @author: 潘江明
    Copyright © 2021  潘江明
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct polynode {
    float coef;         //系数
    int expn;           //指数
    struct polynode* next;
} polynode, * polylist;

void poly_create(polylist& L);   //创建链表
void poly_display(polylist L);   //显示链表内容
void poly_add(polylist La, polylist Lb, polylist& Lc);       //多项式相加 
void poly_subtract(polylist La, polylist Lb, polylist& Lc);    //多项式相减

int main()
{
    polylist La, Lb, Lc, Ld;
    poly_create(La);
    printf("一元多项式1：");
    poly_display(La);
    poly_create(Lb);
    printf("一元多项式2：");
    poly_display(Lb);
    poly_add(La, Lb, Lc);
    printf("加的结果：");
    poly_display(Lc);
    poly_subtract(La, Lb, Ld);
    printf("减的结果：");
    poly_display(Ld);
}

void poly_create(polylist& L) {
    polylist p, s;
    int num;
    L = (polylist)malloc(sizeof(polynode));
    if (!L)
        exit(OVERFLOW);
    L->next = nullptr;

    p = L;
    scanf("%d", &num);
    while (num--) {
        s = (polylist)malloc(sizeof(polynode));
        scanf("%f %d", &s->coef, &s->expn);
        p->next = s;
        p = s;
    }
    p->next = nullptr;
}
void poly_display(polylist L) {
    polylist p = L->next;
    int cnt = 0;

    while (p) {
        if (p->coef > 0 && cnt)
            printf("+");
        printf("%.0fx(%d)", p->coef, p->expn);
        p = p->next;
        cnt++;
    }
    printf("\n");
}

void poly_add(polylist La, polylist Lb, polylist& Lc) {
    polylist la = La->next, lb = Lb->next, p, s;

    Lc = (polylist)malloc(sizeof(polynode));
    if (!Lc)
        exit(OVERFLOW);
    Lc->next = nullptr;

    p = Lc;
    while (la && lb) {
        s = (polylist)malloc(sizeof(polynode));
        if (la->expn == lb->expn) {
            s->coef = la->coef + lb->coef;
            s->expn = la->expn;
            la = la->next, lb = lb->next;
            if (s->coef == 0.0)
                continue;
        }
        else if (la->expn < lb->expn) {
            s->coef = la->coef;
            s->expn = la->expn;
            la = la->next;
        }
        else {
            s->coef = lb->coef;
            s->expn = lb->expn;
            lb = lb->next;
        }
        
        p->next = s;
        p = s;
    }
    while (la) {
        s = (polylist)malloc(sizeof(polynode));
        s->coef = la->coef, s->expn = la->expn;
        p->next = s;
        p = s;
        
        la = la->next;
    }
    while (lb) {
        s = (polylist)malloc(sizeof(polynode));
        s->coef = lb->coef, s->expn = lb->expn;
        p->next = s;
        p = s;

        lb = lb->next;
    }
    p->next = nullptr;
}

void poly_subtract(polylist La, polylist Lb, polylist& Lc) {
    polylist la = La->next, lb = Lb->next, p, s;

    Lc = (polylist)malloc(sizeof(polynode));
    if (!Lc)
        exit(OVERFLOW);
    Lc->next = nullptr;

    p = Lc;
    while (la && lb) {
        s = (polylist)malloc(sizeof(polynode));

        if (la->expn == lb->expn) {
            s->coef = la->coef - lb->coef;
            s->expn = la->coef;
            la = la->next, lb = lb->next;
            if (s->coef == 0.0)
                continue;
        }
        else if (la->expn < lb->expn) {
            s->coef = la->coef, s->expn = la->expn;
            la = la->next;
        }
        else {
            s->coef = -lb->coef, s->expn = lb->expn;
            lb = lb->next;
        }

        p->next = s;
        p = p->next;
    }
    while (la) {
        s = (polylist)malloc(sizeof(polynode));
        s->coef = la->coef, s->expn = la->expn;
        la = la->next;

        p->next = s;
        p = p->next;
    }
    while (lb) {
        s = (polylist)malloc(sizeof(polynode));
        s->coef = -lb->coef, s->expn = lb->expn;
        lb = lb->next;

        p->next = s;
        p = p->next;
    }
    p->next = nullptr;
}

/*
3
2 3
3 4
5 7
5
2 1
3 3
-3 4
4 6
5 7
*/