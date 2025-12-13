#ifndef __HW3_H
#define __HW3_H

typedef struct IdInfo {
    char *name;
    int line;
} IdInfo;

typedef struct Fraction {
    int num;
    int den;
} Fraction;

typedef struct PolyVar {
    char name;          
    int power;
    int line;
    struct PolyVar *next;
} PolyVar;

typedef struct Term {
    Fraction coeff;
    PolyVar *vars;
    struct Term *next;
} Term;

typedef struct PolyNode {
    Term *head;
} PolyNode;

typedef struct ParseObj {
    PolyNode *poly;
    char *str;          
} ParseObj;

typedef struct VarNode {
    char *name;
    struct VarNode *next;
} VarNode;

typedef struct FuncNode {
    char *name;
    int paramCount;
    VarNode *params;    
    PolyNode *body;     
    struct FuncNode *next;
} FuncNode;

typedef struct ErrorNode {
    char *msg;
    struct ErrorNode *next;
} ErrorNode;

typedef struct OutputNode {
    char *lhs;          
    PolyNode *rhs;      
    struct OutputNode *next;
} OutputNode;

#endif
