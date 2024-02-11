#ifndef DFATABLES_H
#define DFATABLES_H

// Defining starting state and rejecting state for all dfas
#define INITIALSTATE 1
#define REJECTSTATE 0
// Defining general alphabet
#define ALPHABET '"', '(', ')', '*', '+', ',', '0','1','2','3','4','5','6','7','8','9', ';', '=', '>', \
                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', '[', ']', \
                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', '{', '}'
#define ALPHABETLEN 75


#define TYPECOLUMNS 11
#define TYPEROWS 11
// Defining accepting state for type dfa
#define TYPEACCEPT 10
#define TYPEACCEPTLEN 1
// Defining mapping of alphabet to columns of type table (i,n,t,c,h,a,r,v,o,d,other)
#define TYPEMAPPING 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, \
                    10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, \
                    5,10,3,9,10,10,10,4,0,10,10,10,10,1,8,10,10,6,10,2,10,7,10,10,10,10,10,10
#define TYPETABLE 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                    2, 0, 0, 4, 0, 0, 0, 7, 0, 0, 0, \
                    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                    0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, \
                    0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, \
                    0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, \
                    0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, \
                    0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, \
                    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, \
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0


#define IDENTIFIERCOLUMNS 4
#define IDENTIFIERROWS 3
// Defining accepting state for identifier dfa
#define IDENTIFIERACCEPT 2
// Define mapping of alphabet to columns of identifier table (Number, Lowercase, Uppercase, other)
#define IDENTIFIERMAPPING   3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,3,3,3, \
                            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3, \
                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3
#define IDENTIFIERTABLE 0, 0, 0, 0, \
                        0, 2, 2, 0, \
                        2, 2, 2, 0


#define KEYWORDCOLUMNS 14
#define KEYWORDROWS 19
// Defining accepting state for keyword dfa
#define KEYWORDACCEPT 18
// Defining mapping of alphabet to columns of keyword table (i,f,e,l,s,w,h,m,a,n,r,t,u,other)
#define KEYWORDMAPPING 13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, \
                        13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, \
                        8,13,13,13,2,1,13,6,0,13,13,3,7,9,13,13,13,10,4,11,12,13,5,13,13,13,13,13
#define KEYWORDTABLE 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                        2, 0, 3, 0, 0, 6, 0, 10, 0, 0, 13, 0, 0, 0, \
                        0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  \
                        0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   \
                        0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,   \
                        0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0,   \
                        8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   \
                        0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   \
                        0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0,  \
                        12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0,  \
                        0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0,  \
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0


#define NUMBERCOLUMNS 2
#define NUMBERROWS  3
// Defining accepting state for number dfa
#define NUMBERACCEPT 2
// Defining mapping of alphabet to columns of number table (0,1,2,3,4,5,6,7,8,9,other)
#define NUMBERMAPPING 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
#define NUMBERTABLE 0, 0, \
                        2, 0, \
                        2, 0


#define SPECIALCOLUMNS 2
#define SPECIALROWS 3
// Defining accepting state for Special characters dfa
#define SPECIALACCEPT 2
// Defining mapping of alphabet to columns of special characters table(Special, other)
#define SPECIALMAPPING 1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0
#define SPECIALTABLE 0, 0, \
                        2, 0, \
                        2, 0


#define OPERATORCOLUMNS 2
#define OPERATORROWS 3
// Defining accepting state for operator dfa
#define OPERATORACCEPT 2
// Defining mapping of alphabet to columns of operator table (Operator, other)
#define OPERATORMAPPING 1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
#define OPERATORTABLE 0, 0, \
                        2, 0, \
                        2, 0


#define LITERALCOLUMNS 2
#define LITERALROWS 4
// Defining accepting state for literals dfa
#define LITERALACCEPT 3
// Defining mapping of alphabet to columns of literal table (", other)
#define LITERALMAPPING 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, \
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
#define LITERALTABLE 0, 0, \
                        2, 0, \
                        3, 2, \
                        0, 0

#endif // DFATABLES_H