%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oguz.ozbal-hw3.h"

extern int lineCount;
int currentCalcLine = 1;

int lastLPARLine = 1;
int lastRPARLine = 1; 
int firstMissingFuncLine = 0; 

void yyerror(const char *msg) {
    printf("Syntax Error on Line %d: %s\n", lineCount, msg);
}

int yylex();

/* Struct Defination */

typedef struct ArgPolyStore {
    ParseObj *arg;
    PolyNode *poly;
    char *str;
    struct ArgPolyStore *next;
} ArgPolyStore;

FuncNode *funcsHead = NULL;
ErrorNode *errsHead = NULL;
OutputNode *outHead = NULL;
OutputNode *outTail = NULL; 
int hasSemanticErrors = 0;

/* Prototip Dostlar */
void addError(int line, const char *msg);
void addOutput(char *lhs, PolyNode *rhs);
void addFunction(char *name, VarNode *params, PolyNode *body);
FuncNode* getFunction(char *name);
FuncNode* getFunctionWithArity(char *name, int arity);
int isFunctionRedefined(char *name);

Fraction makeFrac(int n, int d);
Fraction addFrac(Fraction a, Fraction b);
Fraction mulFrac(Fraction a, Fraction b);
Fraction simplifyFrac(Fraction f);
PolyNode* createPolyFromNum(int n);
PolyNode* createPolyFromVar(char *name, int line);
PolyNode* addPoly(PolyNode *p1, PolyNode *p2, int subtract);
PolyNode* mulPoly(PolyNode *p1, PolyNode *p2);
PolyNode* powerPoly(PolyNode *p, int pow);
PolyNode* copyPoly(PolyNode *p);
PolyNode* derivePoly(PolyNode *p, char var, int order);
PolyNode* integratePoly(PolyNode *p, char var, int order);

PolyNode* substituteFunc(FuncNode *fn, ArgPolyStore *args);
char* buildFuncCallString(char *funcName, ArgPolyStore *args);

PolyVar* copyVars(PolyVar *v);
PolyVar* mergeVars(PolyVar *v1, PolyVar *v2);
Term* copyTerm(Term *t);
VarNode* createVarNode(char *name);
VarNode* appendVarNode(VarNode *head, VarNode *node);
int countVars(VarNode *head);
char* concat(const char *s1, const char *s2, const char *s3);

PolyNode* simplifyPoly(PolyNode *p);
int compareTerms(Term *t1, Term *t2);
char* formatPoly(PolyNode *p);
char* formatTerm(Term *t);
char* removeWhitespace(const char *str);

void printSortedErrors();
void printReport();
%}

%union {
    int iVal;
    struct IdInfo idInfo; 
    struct VarNode *varList;
    struct ParseObj pObj;  
    struct ArgPolyStore *argList; 
}

%token <iVal> tNUMBER
%token <idInfo> tIDENT
%token tCALC tDERIV tINTEG tASSIGN tPLUS tMINUS tMULT tDIV tPOWER tCOMMA tLPAR tRPAR tSEMI

%token tIMPLICIT 
%token tUMINUS

%type <varList> param_list
%type <pObj> expr term factor power atom
%type <argList> func_args 

%left tPLUS tMINUS
%left tMULT tDIV
%left tIMPLICIT      
%right tPOWER        
%nonassoc tUMINUS    
%left tLPAR          

%%

program:
    def_block calc_block
    ;

def_block:
    /* empty */
    | def_block func_def
    ;

func_def:
    tIDENT tLPAR param_list tRPAR tASSIGN expr tSEMI
    {
        if (getFunction($1.name)) {
            char buf[100]; sprintf(buf, "REDEFINED_FUNCTION_(%s)", $1.name);
            addError($1.line, buf);
        }
        PolyNode *body = $6.poly;
        if (body) {
             Term *t = body->head;
             while(t) {
                 PolyVar *v = t->vars;
                 while(v) {
                     int found = 0;
                     VarNode *p = $3;
                     while(p) { if(p->name[0] == v->name) found=1; p=p->next; }
                     if(!found) {
                        char buf[100]; char n[2] = {v->name, 0};
                        sprintf(buf, "UNDEFINED_FUNCTION_PARAMETER_(%s)", n);
                        addError(v->line, buf); 
                     }
                     v = v->next;
                 }
                 t = t->next;
             }
        }
        addFunction($1.name, $3, body);
    }
    ;

param_list:
    /* empty */ { $$ = NULL; }
    | tIDENT { $$ = createVarNode($1.name); }
    | param_list tCOMMA tIDENT { $$ = appendVarNode($1, createVarNode($3.name)); }
    ;

calc_block:
    /* empty */
    | calc_block calc_stmt
    ;


calc_keyword:
    tCALC 
    { 
        currentCalcLine = lineCount; 
    }
    ;

calc_stmt:
    calc_keyword expr tSEMI
    {
        addOutput($2.str, $2.poly);
        firstMissingFuncLine = 0; 
    }
    ;

expr:
    term 
    { $$ = $1; }
    | expr tPLUS term 
    { 
        $$.poly = addPoly($1.poly, $3.poly, 0); 
        $$.str = concat($1.str, "+", $3.str);
    }
    | expr tMINUS term
    { 
        $$.poly = addPoly($1.poly, $3.poly, 1); 
        $$.str = concat($1.str, "-", $3.str);
    }
    ;

term:
    factor
    { $$ = $1; }
    | term tMULT factor
    { 
        $$.poly = mulPoly($1.poly, $3.poly); 
        $$.str = concat($1.str, "*", $3.str);
    }
    | term tDIV factor
    {
        $$.poly = NULL;
        $$.str = concat($1.str, "/", $3.str);
    }
    | term power %prec tIMPLICIT
    {
        $$.poly = mulPoly($1.poly, $2.poly);
        $$.str = concat($1.str, "", $2.str); 
    }
    ;

factor:
    power
    { $$ = $1; }
    | tMINUS factor %prec tUMINUS
    {
        PolyNode *neg1 = createPolyFromNum(-1);
        $$.poly = mulPoly(neg1, $2.poly);
        $$.str = concat("-", $2.str, "");
    }
    ;

power:
    atom
    { $$ = $1; }
    | atom tPOWER tNUMBER
    { 
        $$.poly = powerPoly($1.poly, $3); 
        char buf[32]; sprintf(buf, "^%d", $3);
        $$.str = concat($1.str, buf, "");
    }
    | atom tPOWER tMINUS tNUMBER
    {
        $$.poly = powerPoly($1.poly, -$4); 
        char buf[32]; sprintf(buf, "^-%d", $4);
        $$.str = concat($1.str, buf, "");
    }
    ;

atom:
    tNUMBER
    { 
        $$.poly = createPolyFromNum($1); 
        char buf[32]; sprintf(buf, "%d", $1);
        $$.str = strdup(buf);
    }
    | tIDENT %prec tIMPLICIT
    { 
        $$.poly = createPolyFromVar($1.name, $1.line); 
        $$.str = strdup($1.name);
    }
    | tLPAR expr tRPAR
    { 
        $$.poly = $2.poly; 
        $$.str = concat("(", $2.str, ")");
    }
    | tIDENT tLPAR tRPAR
    {
        // Parametresiz fonksiyon çağrısı: g()
        FuncNode *f = getFunction($1.name);
        int cnt = 0;
        
        $$.str = NULL;
        
        if (!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_(%s)", $1.name);
            addError($1.line, buf);
            $$.poly = NULL;
            $$.str = concat($1.name, "()", "");
        } else {
            FuncNode *fExact = getFunctionWithArity($1.name, cnt);
            int redefined = isFunctionRedefined($1.name);
            
            if (!fExact || redefined) {
                char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", $1.name);
                addError($1.line, buf);
                $$.poly = NULL;
                $$.str = concat($1.name, "()", "");
            } else {
                // Parametresiz fonksiyon - body'yi direkt kopyala
                $$.poly = fExact->body ? copyPoly(fExact->body) : createPolyFromNum(0);
                $$.str = concat($1.name, "()", "");
            }
        }
        if ($$.str == NULL) $$.str = strdup("error");
    }
    | tIDENT tLPAR func_args tRPAR
    {
        FuncNode *f = getFunction($1.name);
        ArgPolyStore *args = $3; /* Argüman listesini al */
        
        /* Argüman sayısını listeden hesapla */
        int cnt = 0;
        ArgPolyStore *temp = args;
        while (temp) {
            cnt++;
            temp = temp->next;
        }

        $$.str = NULL;

        if (!f) {
            if (cnt == 1) {
                /* Implicit multiplication */
                PolyNode *identPoly = createPolyFromVar($1.name, $1.line);
                PolyNode *argPoly = args->poly; 
                $$.poly = mulPoly(identPoly, argPoly);
                $$.str = concat($1.name, "(", args->str);
                $$.str = concat($$.str, ")", "");
            } else {
                char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_(%s)", $1.name);
                addError($1.line, buf);
                $$.poly = NULL;
                $$.str = buildFuncCallString($1.name, args); /* Listeyi gönder */
            }
        } else {
            FuncNode *fExact = getFunctionWithArity($1.name, cnt);
            int redefined = isFunctionRedefined($1.name);
            
            if (redefined) {
                char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", $1.name);
                addError($1.line, buf); 
                $$.poly = NULL;
                $$.str = buildFuncCallString($1.name, args);
            } else if (!fExact) {
                if (cnt == 1) {
                    /* Implicit mult fallback */
                    PolyNode *identPoly = createPolyFromVar($1.name, $1.line);
                    PolyNode *argPoly = args->poly; 
                    $$.poly = mulPoly(identPoly, argPoly);
                    $$.str = concat($1.name, "(", args->str);
                    $$.str = concat($$.str, ")", "");
                } else {
                    char buf[100]; sprintf(buf, "ARITY_CONTRADICTION_(%s)", $1.name);
                    addError($1.line, buf); 
                    $$.poly = NULL;
                    $$.str = buildFuncCallString($1.name, args);
                }
            } else {
                /* Normal substitution - Listeyi gönder */
                PolyNode *substituted = substituteFunc(fExact, args);
                if (!substituted) {
                    $$.poly = createPolyFromNum(0);
                } else {
                    $$.poly = simplifyPoly(substituted);
                }
                $$.str = buildFuncCallString($1.name, args);
            }
        }
        if ($$.str == NULL) $$.str = strdup("error");
        
        /* Argüman listesini temizle */
        temp = args;
        while(temp) {
            ArgPolyStore *next = temp->next;
            /* Poly temizleme mantığı burada olmalı veya ayrı fonksiyonda */
            // free(temp->str); // vb...
            free(temp);
            temp = next;
        }
    }
    | tLPAR expr tCOMMA func_args tRPAR
    {
         addError(currentCalcLine, "MISSING_FUNCTION_NAME"); 
         $$.poly = NULL;
         $$.str = strdup("error");
         
         /* Global store yerine local listeyi ($4) temizle */
         ArgPolyStore *temp = $4;
         while(temp) {
            ArgPolyStore *next = temp->next;
            free(temp);
            temp = next;
         }
    }
    | tDERIV tLPAR tIDENT tCOMMA tIDENT tCOMMA tNUMBER tRPAR
    {
        FuncNode *f = getFunction($3.name);
        if(!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_FOR_DERIVATION_(%s)", $3.name);
            addError($3.line, buf);
            $$.poly = NULL;
        } else {
             int valid = 0; VarNode *v = f->params;
             while(v) { if(strcmp(v->name, $5.name)==0) valid=1; v=v->next; }
             if(!valid) {
                 char buf[100]; sprintf(buf, "UNDEFINED_VARIABLE_FOR_DERIVATION_(%s)", $5.name);
                 addError($5.line, buf);
                 $$.poly = NULL;
             } else {
                 $$.poly = derivePoly(f->body, $5.name[0], $7); 
             }
        }
        char buf[50]; sprintf(buf, "D(%s,%s,%d)", $3.name, $5.name, $7);
        $$.str = strdup(buf);
    }
    | tINTEG tLPAR tIDENT tCOMMA tIDENT tCOMMA tNUMBER tRPAR
    {
        FuncNode *f = getFunction($3.name);
        if(!f) {
            char buf[100]; sprintf(buf, "UNDEFINED_FUNCTION_FOR_INTEGRATION_(%s)", $3.name);
            addError($3.line, buf);
            $$.poly = NULL;
        } else {
             int valid = 0; VarNode *v = f->params;
             while(v) { if(strcmp(v->name, $5.name)==0) valid=1; v=v->next; }
             if(!valid) {
                 char buf[100]; sprintf(buf, "UNDEFINED_VARIABLE_FOR_INTEGRATION_(%s)", $5.name);
                 addError($5.line, buf);
                 $$.poly = NULL;
             } else {
                 $$.poly = integratePoly(f->body, $5.name[0], $7);
             }
        }
        char buf[50]; sprintf(buf, "I(%s,%s,%d)", $3.name, $5.name, $7);
        $$.str = strdup(buf);
    }
    ;

func_args:
    expr
    {
        ArgPolyStore *node = malloc(sizeof(ArgPolyStore));
        node->arg = NULL; /* ParseObj saklamaya gerek yok, direkt poly/str saklıyoruz */
        node->poly = copyPoly($1.poly);
        node->str = $1.str ? strdup($1.str) : NULL;
        node->next = NULL;
        
        $$ = node; 
    }
    | func_args tCOMMA expr
    {
        ArgPolyStore *node = malloc(sizeof(ArgPolyStore));
        node->arg = NULL;
        node->poly = copyPoly($3.poly);
        node->str = $3.str ? strdup($3.str) : NULL;
        node->next = NULL;
        
        ArgPolyStore *curr = $1;
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
        
        $$ = $1;
    }
    ;

%%

Fraction makeFrac(int n, int d) { Fraction f = {n, d}; return simplifyFrac(f); }
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
Fraction simplifyFrac(Fraction f) {
    if (f.den == 0) { f.den = 1; return f; }
    int common = gcd(abs(f.num), abs(f.den));
    if (common == 0) common = 1;
    f.num /= common; f.den /= common;
    if (f.den < 0) { f.num = -f.num; f.den = -f.den; }
    return f;
}
Fraction addFrac(Fraction a, Fraction b) {
    return simplifyFrac((Fraction){a.num*b.den + b.num*a.den, a.den*b.den});
}
Fraction mulFrac(Fraction a, Fraction b) {
    return simplifyFrac((Fraction){a.num*b.num, a.den*b.den});
}

PolyNode* createPolyFromNum(int n) {
    PolyNode *p = malloc(sizeof(PolyNode));
    Term *t = malloc(sizeof(Term));
    t->coeff = makeFrac(n, 1);
    t->vars = NULL; t->next = NULL;
    p->head = t;
    return p;
}

PolyNode* createPolyFromVar(char *name, int line) {
    if (!name || !name[0]) return createPolyFromNum(0);

    PolyNode *p = malloc(sizeof(PolyNode));
    Term *t = malloc(sizeof(Term));
    t->coeff = makeFrac(1, 1);
    
    PolyVar *v = malloc(sizeof(PolyVar));
    v->name = name[0]; 
    v->power = 1; 
    v->line = line; 
    v->next = NULL;
    
    t->vars = v; 
    t->next = NULL;
    p->head = t;
    return p;
}

PolyVar* copyVars(PolyVar *v) {
    if(!v) return NULL;
    PolyVar *n = malloc(sizeof(PolyVar));
    n->name = v->name; n->power = v->power; 
    n->line = v->line; 
    n->next = copyVars(v->next);
    return n;
}

Term* copyTerm(Term *t) {
    if(!t) return NULL;
    Term *nt = malloc(sizeof(Term));
    nt->coeff = t->coeff;
    nt->vars = copyVars(t->vars);
    nt->next = NULL;
    return nt;
}

PolyNode* copyPoly(PolyNode *p) {
    if(!p) return NULL;
    if(!p->head) return createPolyFromNum(0);
    
    PolyNode *n = malloc(sizeof(PolyNode));
    n->head = NULL;
    Term **tail = &n->head;
    
    for (Term *t = p->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        *tail = newTerm;
        tail = &newTerm->next;
    }
    return n;
}

PolyNode* addPoly(PolyNode *p1, PolyNode *p2, int subtract) {
    if(!p1 && !p2) return createPolyFromNum(0);
    if(!p1) return copyPoly(p2);
    if(!p2) return copyPoly(p1);
    
    PolyNode *res = malloc(sizeof(PolyNode));
    res->head = NULL;
    Term **tail = &res->head;
    
    // p1'in terimlerini ekle
    for (Term *t = p1->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    // p2'nin terimlerini ekle (çıkarma ise katsayıyı negatif yap)
    for (Term *t = p2->head; t; t = t->next) {
        Term *newTerm = copyTerm(t);
        if (subtract) {
            newTerm->coeff.num = -newTerm->coeff.num;
        }
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    return res;
}

PolyVar* mergeVars(PolyVar *v1, PolyVar *v2) {
    PolyVar *res = copyVars(v1);
    
    for (PolyVar *v2_curr = v2; v2_curr; v2_curr = v2_curr->next) {
        PolyVar *res_curr = res;
        PolyVar *prev = NULL;
        int found = 0;
        
        while (res_curr) {
            if (res_curr->name == v2_curr->name) {
                res_curr->power += v2_curr->power;
                found = 1;
                break;
            }
            prev = res_curr;
            res_curr = res_curr->next;
        }
        
        if (!found) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = v2_curr->name;
            newVar->power = v2_curr->power;
            newVar->line = v2_curr->line;
            newVar->next = NULL;
            
            if (prev) {
                prev->next = newVar;
            } else {
                res = newVar;
            }
        }
    }
    return res;
}

PolyNode* mulPoly(PolyNode *p1, PolyNode *p2) {
    if(!p1 || !p2) return createPolyFromNum(0);
    if(!p1->head || !p2->head) return createPolyFromNum(0);
    
    PolyNode *res = malloc(sizeof(PolyNode)); 
    res->head = NULL;
    Term **tail = &res->head;
    
    for(Term *t1 = p1->head; t1; t1 = t1->next) {
        for(Term *t2 = p2->head; t2; t2 = t2->next) {
            Term *nt = malloc(sizeof(Term));
            nt->coeff = mulFrac(t1->coeff, t2->coeff);
            nt->vars = mergeVars(t1->vars, t2->vars);
            nt->next = NULL;
            *tail = nt;
            tail = &nt->next;
        }
    }
    return res;
}

PolyNode* powerPoly(PolyNode *p, int pow) {
    if(!p || !p->head) return createPolyFromNum(0);
    if(pow == 0) return createPolyFromNum(1);
    if(pow < 0) return createPolyFromNum(0);
    
    PolyNode *res = copyPoly(p);
    for(int i = 1; i < pow; i++) {
        PolyNode *tmp = mulPoly(res, p);
        // Eski res'i temizle
        Term *t = res->head;
        while(t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while(v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(res);
        res = tmp;
    }
    return res;
}

PolyNode* derivePoly(PolyNode *p, char var, int order) {
    if (!p || !p->head) return createPolyFromNum(0);
    if (order <= 0) return copyPoly(p);
    
    // Bir kez türev al
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *t = p->head; t; t = t->next) {
        // Bu terimde 'var' değişkeninin üssünü bul
        int varPower = 0;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                varPower = v->power;
                break;
            }
        }
        
        // Eğer değişken yoksa veya üssü 0 ise atla
        if (varPower == 0) continue;
        
        // Yeni terim oluştur: coeff * varPower * var^(varPower-1) * diğerdeğişkenler
        Term *newTerm = malloc(sizeof(Term));
        newTerm->coeff = mulFrac(t->coeff, makeFrac(varPower, 1));
        newTerm->vars = NULL;
        newTerm->next = NULL;
        
        // türevi alınan değişkenin üssünü 1 azalt
        PolyVar **varTail = &newTerm->vars;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                // Üssü 1 azalt, 0 olursa ekleme
                if (v->power > 1) {
                    PolyVar *newVar = malloc(sizeof(PolyVar));
                    newVar->name = v->name;
                    newVar->power = v->power - 1;
                    newVar->line = v->line;
                    newVar->next = NULL;
                    *varTail = newVar;
                    varTail = &newVar->next;
                }
            } else {
                // Diğer değişkenleri aynen kopyala
                PolyVar *newVar = malloc(sizeof(PolyVar));
                newVar->name = v->name;
                newVar->power = v->power;
                newVar->line = v->line;
                newVar->next = NULL;
                *varTail = newVar;
                varTail = &newVar->next;
            }
        }
        
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    if (!result->head) {
        free(result);
        result = createPolyFromNum(0);
    }
    
    // Eğer order > 1 ise, recursive olarak devam et
    if (order > 1) {
        PolyNode *nextDeriv = derivePoly(result, var, order - 1);
        // result'u temizle
        Term *t = result->head;
        while (t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while (v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(result);
        return nextDeriv;
    }
    
    return result;
}

PolyNode* integratePoly(PolyNode *p, char var, int order) {
    if (!p || !p->head) return createPolyFromNum(0);
    if (order <= 0) return copyPoly(p);
    
    // Bir kez integral al
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;
    
    for (Term *t = p->head; t; t = t->next) {
        // Bu terimde 'var' değişkeninin üssünü bul
        int varPower = 0;
        int hasVar = 0;
        for (PolyVar *v = t->vars; v; v = v->next) {
            if (v->name == var) {
                varPower = v->power;
                hasVar = 1;
                break;
            }
        }
        
        // Yeni üs = varPower + 1
        int newPower = varPower + 1;
        
        // Yeni terim oluştur: coeff / newPower * var^newPower * diğer_değişkenler
        Term *newTerm = malloc(sizeof(Term));
        newTerm->coeff = mulFrac(t->coeff, makeFrac(1, newPower));
        newTerm->vars = NULL;
        newTerm->next = NULL;
        
    
        PolyVar **varTail = &newTerm->vars;
        int varAdded = 0;
        
        for (PolyVar *v = t->vars; v; v = v->next) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = v->name;
            newVar->line = v->line;
            newVar->next = NULL;
            
            if (v->name == var) {
                // Üssü 1 artır
                newVar->power = v->power + 1;
                varAdded = 1;
            } else {
                newVar->power = v->power;
            }
            
            *varTail = newVar;
            varTail = &newVar->next;
        }
        
        
        if (!hasVar) {
            PolyVar *newVar = malloc(sizeof(PolyVar));
            newVar->name = var;
            newVar->power = 1;
            newVar->line = 0;
            newVar->next = NULL;
            *varTail = newVar;
        }
        
        *tail = newTerm;
        tail = &newTerm->next;
    }
    
    if (!result->head) {
        free(result);
        result = createPolyFromNum(0);
    }
    
    if (order > 1) {
        PolyNode *nextInteg = integratePoly(result, var, order - 1);
        // result'u temizle
        Term *t = result->head;
        while (t) {
            Term *next = t->next;
            PolyVar *v = t->vars;
            while (v) {
                PolyVar *nextVar = v->next;
                free(v);
                v = nextVar;
            }
            free(t);
            t = next;
        }
        free(result);
        return nextInteg;
    }
    
    return result;
}

PolyNode* substituteFunc(FuncNode *fn, ArgPolyStore *args) {
    if (!fn || !fn->body || !fn->body->head) return createPolyFromNum(0);

    PolyNode *paramMap[256];
    for (int i = 0; i < 256; i++) paramMap[i] = NULL;

    VarNode *param = fn->params;
    ArgPolyStore *currArg = args;

    while (param && currArg) {
        if (param->name && strlen(param->name) > 0) {
            char paramChar = param->name[0];
            paramMap[(unsigned char)paramChar] = currArg->poly;
        }
        param = param->next;
        currArg = currArg->next;
    }

    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;
    Term **tail = &result->head;

    for (Term *origTerm = fn->body->head; origTerm; origTerm = origTerm->next) {
        if (!origTerm->vars) {
            Term *newTerm = malloc(sizeof(Term));
            newTerm->coeff = origTerm->coeff;
            newTerm->vars = NULL;
            newTerm->next = NULL;
            *tail = newTerm;
            tail = &newTerm->next;
            continue;
        }

        PolyNode *termResult = createPolyFromNum(origTerm->coeff.num);
        termResult->head->coeff.den = origTerm->coeff.den;

        for (PolyVar *v = origTerm->vars; v; v = v->next) {
            PolyNode *varPoly = NULL;

            if (paramMap[(unsigned char)v->name]) {
                PolyNode *argPolySource = paramMap[(unsigned char)v->name];
                PolyNode *argCopy = copyPoly(argPolySource);

                if (v->power == 1) {
                    varPoly = argCopy;
                } else {
                    varPoly = powerPoly(argCopy, v->power);

                    if (varPoly != argCopy) {
                         Term *t = argCopy->head;
                         while(t) {
                             Term *tn = t->next;
                             PolyVar *pv = t->vars;
                             while(pv) { PolyVar *pvn = pv->next; free(pv); pv = pvn; }
                             free(t);
                             t = tn;
                         }
                         free(argCopy);
                    }
                }
            } else {
                varPoly = malloc(sizeof(PolyNode));
                Term *varTerm = malloc(sizeof(Term));
                varTerm->coeff = makeFrac(1, 1);

                PolyVar *newVar = malloc(sizeof(PolyVar));
                newVar->name = v->name;
                newVar->power = v->power;
                newVar->line = v->line;
                newVar->next = NULL;

                varTerm->vars = newVar;
                varTerm->next = NULL;
                varPoly->head = varTerm;
            }

            if (!varPoly || !varPoly->head) {
                if(varPoly) free(varPoly);
                varPoly = createPolyFromNum(1);
            }

            PolyNode *temp = mulPoly(termResult, varPoly);

            if (termResult) {
                Term *t = termResult->head;
                while (t) {
                    Term *tn = t->next;
                    PolyVar *pv = t->vars;
                    while(pv) { PolyVar *pvn = pv->next; free(pv); pv = pvn; }
                    free(t);
                    t = tn;
                }
                free(termResult);
            }

            if (varPoly) {
                Term *t = varPoly->head;
                while (t) {
                    Term *tn = t->next;
                    PolyVar *pv = t->vars;
                    while(pv) { PolyVar *pvn = pv->next; free(pv); pv = pvn; }
                    free(t);
                    t = tn;
                }
                free(varPoly);
            }

            termResult = temp;
        }

        if (termResult && termResult->head) {
            for (Term *t = termResult->head; t; ) {
                Term *next = t->next;
                t->next = NULL;
                *tail = t;
                tail = &t->next;
                t = next;
            }
            free(termResult);
        }
    }

    if (!result->head) {
        free(result);
        return createPolyFromNum(0);
    }

    return result;
}

void addError(int line, const char *msg) {
    hasSemanticErrors = 1;
    ErrorNode *n = malloc(sizeof(ErrorNode));
    char b[128]; sprintf(b, "%d_%s", line, msg);
    n->msg = strdup(b);
    n->next = errsHead;
    errsHead = n;
}

void addOutput(char *lhs, PolyNode *rhs) {
    if(hasSemanticErrors) return;
    OutputNode *n = malloc(sizeof(OutputNode));
    n->lhs = lhs ? strdup(lhs) : strdup("expr");
    n->rhs = rhs;
    n->next = NULL;
    if(outTail) { outTail->next = n; outTail = n; }
    else { outHead = n; outTail = n; }
}

void printSortedErrors() {
    if(!errsHead) return;
    
    int count = 0;
    ErrorNode *curr = errsHead;
    while(curr) { count++; curr = curr->next; }
    
    char **msgs = malloc(sizeof(char*) * count);
    curr = errsHead;
    int i = 0;
    while(curr) { msgs[i++] = curr->msg; curr = curr->next; }
    
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            int line1 = 0, line2 = 0;
            sscanf(msgs[j], "%d", &line1);
            sscanf(msgs[j+1], "%d", &line2);
            
            if(line1 > line2 || (line1 == line2 && strcmp(msgs[j], msgs[j+1]) > 0)) {
                char *temp = msgs[j];
                msgs[j] = msgs[j+1];
                msgs[j+1] = temp;
            }
        }
    }
    
    for(int i = 0; i < count; i++) {
        if(i > 0 && strcmp(msgs[i], msgs[i-1]) == 0) {
            if(strstr(msgs[i], "MISSING_FUNCTION_NAME") != NULL) {
                printf("%s\n", msgs[i]);
            }
        } else {
            if(strstr(msgs[i], "UNDEFINED_FUNCTION_(") != NULL) {
                char funcName[100];
                sscanf(msgs[i], "%*d_UNDEFINED_FUNCTION_(%[^)])", funcName);
                int shouldPrint = 1;
                for(int j = 0; j < i; j++) {
                    if(strstr(msgs[j], "UNDEFINED_FUNCTION_(") != NULL) {
                        char earlierFuncName[100];
                        sscanf(msgs[j], "%*d_UNDEFINED_FUNCTION_(%[^)])", earlierFuncName);
                        if(strcmp(funcName, earlierFuncName) == 0) {
                            shouldPrint = 0;
                            break;
                        }
                    }
                }
                if(shouldPrint) {
                    printf("%s\n", msgs[i]);
                }
            } else {
                printf("%s\n", msgs[i]);
            }
        }
    }
    free(msgs);
}

void printReport() {
    OutputNode *curr = outHead;
    while(curr) {
        char *cleanLhs = removeWhitespace(curr->lhs);
        
        PolyNode *simplified = curr->rhs ? simplifyPoly(curr->rhs) : createPolyFromNum(0);
        char *formatted = formatPoly(simplified);
        
        printf("%s=%s\n", cleanLhs, formatted);
        
        free(cleanLhs);
        free(formatted);
        curr = curr->next;
    }
}

void addFunction(char *name, VarNode *params, PolyNode *body) {
    FuncNode *f = malloc(sizeof(FuncNode));
    f->name = strdup(name); 
    f->params = params; 
    f->body = body ? copyPoly(body) : NULL; 
    f->paramCount = countVars(params);
    f->next = funcsHead; funcsHead = f;
}

FuncNode* getFunction(char *name) {
    FuncNode *f = funcsHead;
    while(f) { if(strcmp(f->name, name)==0) return f; f = f->next; }
    return NULL;
}

FuncNode* getFunctionWithArity(char *name, int arity) {
    FuncNode *f = funcsHead;
    while(f) { 
        if(strcmp(f->name, name)==0 && f->paramCount == arity) return f; 
        f = f->next; 
    }
    return NULL;
}

int isFunctionRedefined(char *name) {
    FuncNode *f = funcsHead;
    int count = 0;
    while(f) { 
        if(strcmp(f->name, name)==0) count++; 
        f = f->next; 
    }
    return count > 1;
}

VarNode* createVarNode(char *name) { 
    VarNode* n = malloc(sizeof(VarNode)); 
    n->name = strdup(name); 
    n->next = NULL; 
    return n; 
}

VarNode* appendVarNode(VarNode *h, VarNode *n) { 
    if(!h) return n; 
    VarNode* c = h; 
    while(c->next) c = c->next; 
    c->next = n; 
    return h; 
}

int countVars(VarNode *h) { 
    int c = 0; 
    while(h) { c++; h = h->next; } 
    return c; 
}

char* concat(const char *s1, const char *s2, const char *s3) {
    if (!s1) s1 = "";
    if (!s2) s2 = "";
    if (!s3) s3 = "";
    char *res = malloc(strlen(s1)+strlen(s2)+strlen(s3)+1);
    sprintf(res, "%s%s%s", s1, s2, s3); 
    return res;
}

char* buildFuncCallString(char *funcName, ArgPolyStore *args) { // Parametre değişti
    if (!funcName) return strdup("error");
    
    if (!args) {
        return concat(funcName, "()", "");
    }
    
    // İlk argüman
    char *argStr = args->str ? strdup(args->str) : strdup("?");
    ArgPolyStore *curr = args->next;
    
    while (curr) {
        char *val = curr->str ? curr->str : "?";
        char *temp = concat(argStr, ",", val);
        free(argStr);
        argStr = temp;
        curr = curr->next;
    }
    
    char *result = concat(funcName, "(", "");
    char *result2 = concat(result, argStr, ")");
    free(result);
    free(argStr);
    return result2;
}

PolyVar* sortVars(PolyVar *vars) {
    if (!vars) return NULL;
    if (!vars->next) return copyVars(vars);
    
    PolyVar *arr[26];
    int count = 0;
    for (PolyVar *v = vars; v && count < 26; v = v->next) {
        arr[count++] = v;
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j]->name > arr[j+1]->name) {
                PolyVar *temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    PolyVar *result = NULL;
    PolyVar **tail = &result;
    for (int i = 0; i < count; i++) {
        PolyVar *newVar = malloc(sizeof(PolyVar));
        newVar->name = arr[i]->name;
        newVar->power = arr[i]->power;
        newVar->line = arr[i]->line;
        newVar->next = NULL;
        *tail = newVar;
        tail = &newVar->next;
    }
    
    return result;
}

int varsEqual(PolyVar *v1, PolyVar *v2) {
    while (v1 && v2) {
        if (v1->name != v2->name || v1->power != v2->power) return 0;
        v1 = v1->next;
        v2 = v2->next;
    }
    return (v1 == NULL && v2 == NULL);
}

PolyNode* simplifyPoly(PolyNode *p) {
    if (!p) return createPolyFromNum(0);
    if (!p->head) return createPolyFromNum(0);
    
    PolyNode *result = malloc(sizeof(PolyNode));
    result->head = NULL;

    
    for (Term *t = p->head; t; t = t->next) {
        if (t->coeff.num == 0) continue;
        
        PolyVar *sortedVars = sortVars(t->vars);
        
        Term *existing = result->head;
        Term *prev = NULL;
        int found = 0;
        
        while (existing) {
            if (varsEqual(sortedVars, existing->vars)) {
                existing->coeff = addFrac(existing->coeff, t->coeff);
                found = 1;
                
                // Katsayı 0 olursa terimi listeden çıkar
                if (existing->coeff.num == 0) {
                    if (prev) prev->next = existing->next;
                    else result->head = existing->next;
                }
                
                // sortedVars temizle
                PolyVar *v = sortedVars;
                while (v) { PolyVar *nv = v->next; free(v); v = nv; }
                break;
            }
            prev = existing;
            existing = existing->next;
        }
        
        if (!found) {
            Term *newTerm = malloc(sizeof(Term));
            newTerm->coeff = t->coeff;
            newTerm->vars = sortedVars;
            newTerm->next = NULL;
            
            // GÜVENLİ EKLEME: Her seferinde listenin sonunu bul
            if (result->head == NULL) {
                result->head = newTerm;
            } else {
                Term *last = result->head;
                while (last->next != NULL) {
                    last = last->next;
                }
                last->next = newTerm;
            }
        }
    }
    
    if (!result->head) {
        free(result);
        return createPolyFromNum(0);
    }
    
    return result;
}
int compareTerms(Term *t1, Term *t2) {
    int powers1[26] = {0}, powers2[26] = {0};
    
    for (PolyVar *v = t1->vars; v; v = v->next) {
        if (v->name >= 'a' && v->name <= 'z') {
            powers1[v->name - 'a'] += v->power;
        }
    }
    
    for (PolyVar *v = t2->vars; v; v = v->next) {
        if (v->name >= 'a' && v->name <= 'z') {
            powers2[v->name - 'a'] += v->power;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (powers1[i] > powers2[i]) return -1;
        if (powers1[i] < powers2[i]) return 1;
    }
    return 0;
}

char* formatTerm(Term *t) {
    if (!t || t->coeff.num == 0) return strdup("");
    
    char buf[1000] = "";
    
    if (t->coeff.den == 1) {
        // SABİT SAYI KONTROLÜ (vars == NULL)
        if (t->vars == NULL) {
            char num[32];
            sprintf(num, "%d", t->coeff.num);
            strcat(buf, num);
        } 
        else {
            if (t->coeff.num == -1) {
                strcat(buf, "-");
            } else if (t->coeff.num != 1) {
                char num[32];
                sprintf(num, "%d", t->coeff.num);
                strcat(buf, num);
            }
        }
    } else {
        char frac[32];
        sprintf(frac, "%d/%d", t->coeff.num, t->coeff.den);
        strcat(buf, frac);
    }
    
    for (PolyVar *v = t->vars; v; v = v->next) {
        if (v->power == 0) continue; 
        char var[10];
        if (v->power == 1) {
            sprintf(var, "%c", v->name);
        } else {
            sprintf(var, "%c^%d", v->name, v->power);
        }
        strcat(buf, var);
    }
    
    return strdup(buf);
}

char* formatPoly(PolyNode *p) {
    if (!p || !p->head) return strdup("0");
    
    int count = 0;
    Term *t = p->head;
    while (t) { count++; t = t->next; }
    
    if (count == 0) return strdup("0");

    Term **terms = malloc(sizeof(Term*) * count);
    int i = 0;
    for (t = p->head; t; t = t->next) {
        terms[i++] = t;
    }
    
    for (i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (compareTerms(terms[j], terms[j+1]) > 0) {
                Term *temp = terms[j];
                terms[j] = terms[j+1];
                terms[j+1] = temp;
            }
        }
    }
    
    char *result = strdup("");
    int first = 1;
    
    for (i = 0; i < count; i++) {
        if (terms[i]->coeff.num == 0) continue;
        
        char *termStr = formatTerm(terms[i]);
        if (strlen(termStr) == 0) {
            free(termStr);
            continue;
        }
        
        if (first) {
            free(result);
            result = termStr;
            first = 0;
        } else {
            if (terms[i]->coeff.num > 0) {
                char *temp = concat(result, "+", termStr);
                free(result);
                free(termStr);
                result = temp;
            } else {
                char *temp = concat(result, "", termStr);
                free(result);
                free(termStr);
                result = temp;
            }
        }
    }
    
    free(terms);
    if (strlen(result) == 0) {
        free(result);
        return strdup("0");
    }
    return result;
}

char* removeWhitespace(const char *str) {
    if (!str) return strdup("");
    int len = strlen(str);
    char *result = malloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    yyparse();
    if(hasSemanticErrors) {
        printSortedErrors();
    } else {
        printReport();
    }
    return 0;
}