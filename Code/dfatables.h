#ifndef DFATABLES_H
#define DFATABLES_H

#define INITIALSTATE 1
#define REJECTSTATE 0


#define TYPECOLUMNS 11
#define TYPEROWS 11
#define TYPEACCEPT 10
#define TYPEALPHABET 'i', 'n', 't', 'c', 'h', 'a', 'r', 'v', 'o', 'd', "other"
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

#define IDENTIFIERCOLUMNS 63
#define IDENTIFIERROWS 3
#define IDENTIFIERACCEPT 2
#define IDENTIFIERALPHABET '0','1','2','3','4','5','6','7','8','9', \
                                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', \
                                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', "other"
#define IDENTIFIERTABLE 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       0, 0, 0, 0, 0, 0, 0, \
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 0, \
                            2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 0

#define KEYWORDCOLUMNS 14
#define KEYWORDROWS 19
#define KEYWORDACCEPT 18
#define KEYWORDALPHABET 'i','f','e','l','s','w','h','m','a','n','r','t','u',"other"
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

#define NUMBERCOLUMNS 11
#define NUMBERROWS  3
#define NUMBERACCEPT 2
#define NUMBERALPHABET '0','1','2','3','4','5','6','7','8','9',"other"
#define NUMBERTABLE 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, \
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0

#define SPECIALCOLUMNS 9
#define SPECIALROWS 3
#define SPECIALACCEPT 2
#define SPECIALALPHABET ',',';','(',')','[',']','{','}',"other"
#define SPECIALTABLE 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                        2, 2, 2, 2, 2, 2, 2, 2, 0, \
                        0, 0, 0, 0, 0, 0, 0, 0, 0

#define OPERATORCOLUMNS 5
#define OPERATORROWS 3
#define OPERATORACCEPT 2
#define OPERATORALPHABET '+','*','=','>',"other"
#define OPERATORTABLE 0, 0, 0, 0, 0, \
                        2, 2, 2, 2, 0, \
                        0, 0, 0, 0, 0\

#define LITERALCOLUMNS 2
#define LITERALROWS 4
#define LITERALACCEPT 3
#define LITERALALPHABET '"',"other"
#define LITERALTABLE 0, 0, \
                        2, 0, \
                        3, 2, \
                        0, 0

#endif // DFATABLES_H