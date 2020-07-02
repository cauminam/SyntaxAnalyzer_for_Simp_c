//
//  Production.h
//  SyntaxAnal
//
//  Created by 양준식 on 2020/06/27.
//  Copyright © 2020 양준식. All rights reserved.
//

#ifndef Production_h
#define Production_h
#include<iostream>
using namespace std;
#include <string>
#include <vector>

int prodRHS[33]={1,2,2,0,3,3,3,9,3,0,4,0,2,0,1,2,8,7,11,4,0,1,1,3,1,3,1,3,1,1,1,3,3};
    //RHS가 몇개 토큰으로 이루어졌는지만 알면 됨^^
    
    


string prodLHS[33]={//얘는 LHS로 reduce된 input내용을 직접 바꿔줘야하므로 string으로 알고있어야 함!
   "S","CODE","CODE","CODE","VDECL","VDECL","ASSIGN","FDECL","ARG","ARG","MOREARGS","MOREARGS","BLOCK","BLOCK","STMT","STMT","STMT","STMT","STMT","ELSE","ELSE","RHS","RHS","EXPR","EXPR","TERM","TERM","FACTOR","FACTOR","FACTOR","FACTOR","COND","RETURN"};



map<string,int> inputSymbolMap={
    {"vtype",0},{"num",1},{"float",2},{"literal",3},{"id",4},{"if",5},{"else",6},{"while",7},{"for",8},{"return",9},{"addsub",10},{"multdiv",11},{"assign",12},{"comp",13},{"semi",14},{"comma",15},{"lparen",16},{"rparen",17},{"lbrace",18},{"rbrace",19},{"$",20},{"CODE",21},{"VDECL",22},{"ASSIGN",23},{"FDECL",24},{"ARG",25},{"MOREARGS",26},{"BLOCK",27},{"STMT",28},{"ELSE",29},{"RHS",30},{"EXPR",31},{"TERM",32},{"FACTOR",33},{"COND",34},{"RETURN",35}
    
};//CODE    VDECL    ASSIGN    FDECL    ARG    MOREARGS    BLOCK    STMT    ELSE    RHS    EXPR    TERM    FACTOR    COND    RETURN


/*
 00: S → CODE
 01: CODE → VDECL CODE | FDECL CODE | ε
02: VDECL → vtype id semi | vtype ASSIGN semi
03: ASSIGN → id assign RHS
04: FDECL → vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace
05: ARG → vtype id MOREARGS | ε
06: MOREARGS → comma vtype id MOREARGS | ε
07: BLOCK → STMT BLOCK | ε
08: STMT → VDECL | ASSIGN semi
09: STMT → if lparen COND rparen lbrace BLOCK rbrace ELSE
10: STMT → while lparen COND rparen lbrace BLOCK rbrace
11: STMT → for lparen ASSIGN semi COND semi ASSIGN rparen lbrace BLOCK rbrace
12: ELSE → else lbrace BLOCK rbrace | ε
13: RHS → EXPR | literal
14: EXPR → TERM addsub EXPR | TERM
15: TERM → FACTOR multdiv TERM | FACTOR
16: FACTOR → lparen EXPR rparen | id | num | float
17: COND → FACTOR comp FACTOR
18: RETURN → return FACTOR semi
 */



#endif /* Production_h */
