/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: MyString.c 293 2011-10-02 15:05:44Z sebtic $
 */

#include <MyString.h>
#include <limits.h>

/** Like the tolower() function. It converts the letter c to lower case, if possible.
 * @param c the letter to convert
 * @return the lower case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toLowerChar)(char c) {
/*   return provided_toLowerChar(c);*/
   if (c<='Z' && c>='A')
   c = (char)(c + 'a' - 'A');
   return c ;
}

/** Like the toupper() function. It converts the letter c to upper case, if possible.
 * @param c the letter to convert
 * @return the upper case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toUpperChar)(char c) {
      /* return provided_toUpperChar(c);*/
     return ((c<='z' && c>='a')? (char)(c + 'A' - 'a' ) : c);
}

/** Like the strcmp() function. It compares the two strings str1 and str2.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(compareString)(const char * str1, const char * str2) {
/*    return provided_compareString(str1, str2); */
     int flag = 0;
    while (!(flag = *str1 - *str2) && *str1 && *str2){
        if (flag < 0) {
            flag = -1;
        } else if (flag > 0) {
            flag = 1;
        }
        ++str1;
        ++str2;
     }
     return flag;
}

/** Like the strcasecmp() function. It compares the two strings str1 and str2, ignoring the case of the characters.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(icaseCompareString)(const char * str1, const char * str2) {
    /*return provided_icaseCompareString(str1, str2);*/
 /*   size_t str1Size = stringLength (str1);
    size_t str2Size = stringLength (str2);*/

    char  str1Upper[10] = "abcdefghi";
    char  str2Upper[10] = "abcdefghi";

    copyString(str1Upper, str1);
    copyString(str2Upper, str2);


    makeUpperCaseString(str1Upper);
    makeUpperCaseString(str2Upper);

    return compareString(str1Upper, str2Upper);



}

/** Like the strlen() function. It calculates the length of the string str, not including the terminating '\\0' character.
 * @param str the string
 * @return the number of characters in str.
 */
size_t IMPLEMENT(stringLength)(const char * str) {
    /*return provided_stringLength(str);*/
    size_t len = 0;

    while(*(str+len)) {
        ++len;
    }
    return len;
}

/** Copy the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 *
 * @param dest the destination string
 * @param src the source string
 */
void IMPLEMENT(copyString)(char * dest, const char * src) {
   /*fprintf(stderr,
            "You should avoid strcpy and copyString. Use strncpy or copyStringWithLength instead\n");
    copyStringWithLength(dest, src, INT_MAX);*/
    size_t srcSize = stringLength (src);
    size_t destSize = stringLength (dest);

    if (srcSize > destSize) {
        fprintf(stderr,
            "You should avoid strcpy and copyString. Use strncpy or copyStringWithLength instead\n");
            /*copyStringWithLength (dest, src, srcSize);*/
    } else {
        copyStringWithLength (dest, src, destSize);
    }


}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize) {
    /*provided_copyStringWithLength(dest, src, destSize);*/
   
   //Success 1 : This func runs well,but there is a big problem!!!!the table pointer runs away!!!!
/*    size_t srcSize = stringLength (src);

    if (srcSize < destSize) {
        for (; *src != '\0'; ++dest, ++src) {
            *dest = *src;
        }
    } else {
        size_t i = 0;
        for (; i < destSize-1; ++dest, ++src, ++i) {
            *dest = *src;
        }
    }


    *dest = '\0';*/

    //Succeed 2 : Now, it's much better.How terrible the experence is !
    //SkillGet : treat (char *) pointer as array just like it is!!!!! 
    size_t srcSize = stringLength (src);
    size_t i = 0;

    if (srcSize < destSize) {
        for (i = 0; *(src + i) != '\0'; ++i) {
            *(dest + i) = *(src + i);
        }
    } else {
       
        for (i = 0; i < destSize-1;  ++i) {
            *(dest + i) = *(src + i);
        }
    }
    *(dest + i) = '\0';
}

/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * IMPLEMENT(duplicateString)(const char * str) {
    /*return provided_duplicateString(str);*/
    size_t sizeStr = stringLength(str);
    //char *dupStr = malloc(sizeStr * sizeof(size_t));
    char *dupStr = (char *)malloc(sizeStr * sizeof(char));

    int indexStr = 0;
    for (; *(str + indexStr) != '\0'; ++indexStr) {
        *(dupStr + indexStr) = *(str+indexStr);
    }
    *(dupStr + indexStr) = '\0';

    return dupStr;
}

/** Test if the string str begins by the string start, ignoring the case of the characters.
 * @param start the string which should be at the beginning of str
 * @param str the string to test
 * @return a non null number (true) if the str begins with the string start, false otherwise
 */
int IMPLEMENT(icaseStartWith)(const char * start, const char * str) {
    /*return provided_icaseStartWith(start, str);*/
    size_t sizeStart = stringLength (start) +1;
    int isMatch = 0;
    char copyStr[10];
    copyStringWithLength(copyStr, str, sizeStart);


    if (icaseCompareString(start,copyStr) == 0) {
        isMatch = 1;
    }

    return isMatch;
}

/** Test if the string str ends by the string start, ignoring the case of the characters.
 * @param end the string which should be at the end of str
 * @param str the string to test
 * @return a non null number (true) if the str ends with the string end, false otherwise
 */
int IMPLEMENT(icaseEndWith)(const char * end, const char * str) {
    /*return provided_icaseEndWith(end, str);*/
    size_t sizeEnd = stringLength (end) + 1;
    size_t sizeStr = stringLength (str) + 1;
    int isMatch = 0;
    char copyStr[10];
    copyStringWithLength(copyStr, str + sizeStr - sizeEnd, sizeEnd);


    if (icaseCompareString(end,copyStr) == 0) {
        isMatch = 1;
    }

    return isMatch;
}

/** Create a new string on the heap which is the result of the concatenation of the two strings.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str1 the first string
 * @param str2 the second string
 * @return the new string
 */
char * IMPLEMENT(concatenateString)(const char * str1, const char * str2) {
    //return provided_concatenateString(str1, str2);
/*    size_t sizeStr1 = stringLength(str1);
    size_t sizeStr2 = stringLength(str2);
    char * concatenation2Str = (char *) malloc ((sizeStr1 + sizeStr2 ＋1) * sizeof(size_t));

    copyStringWithLength(concatenation2Str, str1, sizeStr1);
    copyStringWithLength(concatenation2Str - 1, str2, sizeStr2);

    *concatenation2Str = '\0';
    return concatenation2Str;
*/
/*    size_t sizeStr1 = stringLength(str1);
    size_t sizeStr2 = stringLength(str2);
    char * concatenation2Str;

    if ((sizeStr1 == 0) && (sizeStr2 == 0))
    {
        //concatenation2Str = NULL;
        concatenation2Str = (char *) malloc (sizeof(char));
        *concatenation2Str = '\0';
    } else {   
    concatenation2Str = (char *) malloc ((sizeStr1 + sizeStr2 ＋1) * sizeof(char));

    copyStringWithLength(concatenation2Str, str1, sizeStr1);
    copyStringWithLength(concatenation2Str - 1, str2, sizeStr2);

    *concatenation2Str = '\0';
    }
    return concatenation2Str;
*/
/*    size_t sizeStr1 = stringLength(str1);
    size_t sizeStr2 = stringLength(str2);
    char * concatenation2Str;

    if ((str1 == NULL) && (str2 == NULL))
    {
        //concatenation2Str = NULL;
        concatenation2Str = (char *) malloc (1*sizeof(char));
        *concatenation2Str = '\0';
    } else {   
    concatenation2Str = (char *) malloc ((sizeStr1 + sizeStr2 ＋1) * sizeof(char));

  //  copyStringWithLength(concatenation2Str, str1, sizeStr1);
  //  copyStringWithLength(concatenation2Str - 1, str2, sizeStr2);

    while (* str1 != '\0')
    {
        *concatenation2Str++ = *str1++; 
    }
    while (*str2 != '\0')
    {
        *concatenation2Str ++ = *str2++;
    }
    *concatenation2Str = '\0';

    *concatenation2Str = '\0';
    }
    return concatenation2Str;

    if ((*str1 == '\0') && (*str2 == '\0')) {
        return NULL;
    } else {
        return 1;
    }*/

/*  // Succeed 1
    char * concatenation2Str;

    size_t sizeStr1 = stringLength(str1);
    size_t sizeStr2 = stringLength(str2);
    concatenation2Str = (char *) malloc ((sizeStr1 + sizeStr2 + 1) * sizeof(char));



    while (* str1 != '\0')
    {
        *concatenation2Str++ = *str1++;
    }
    while (*str2 != '\0')
    {
        *concatenation2Str ++ = *str2++;
    }
    *concatenation2Str = '\0';
 
        return concatenation2Str - sizeStr1 - sizeStr2;
    }*/
  
    //Succeed 2 : This is much better, cause I've rewritten the func copyStringWithLength();
    char * concatenation2Str;

    size_t sizeStr1 = stringLength(str1);
    size_t sizeStr2 = stringLength(str2);
    concatenation2Str = (char *) malloc ((sizeStr1 + sizeStr2 + 1) * sizeof(char));
    
    copyStringWithLength(concatenation2Str, str1,(sizeStr1 + sizeStr2 + 1) );
    copyStringWithLength(concatenation2Str + sizeStr1 , str2, (sizeStr1 + sizeStr2 + 1));

    return concatenation2Str;
/*    assert((strDes != NULL) && (strSrc != NULL));     
    char *address = strDes;     
    while (*strDes != '\0')     
        ++ strDes;     
    while ((*strDes ++ = *strSrc ++) != '\0')     
        NULL;     
    return address;  */
}

/** Like the index() function. It returns a pointer to the first occurrence of the character c in the string str.
 * @param str the string to search in
 * @param c the character to find
 * @return a pointer to the first occurrence of the character c in the string str if c is in str, NULL otherwise
 */
const char * IMPLEMENT(indexOfChar)(const char *str, char c) {
    return provided_indexOfChar(str, c);
     int i = 0;
    /*while (str[i] != '0') {*/
    while (str[i] != '\0') {    
        if (str[i] == c) {
            return &str[i] ;
        } else {
            ++i ;
        }
    }
    return NULL;
  
}

/** Create a copy on the heap of part of a string. The new string contains the characters pointed from start (inclusive) to end (exclusive).
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param start a pointer to the first character of the new string
 * @param end a pointer to the next character of the new string (the pointed character is not part of the new string)
 * @return the new string
 *
 * @code
 * char * str = "abcdef";
 * char * s1 = subString(str,str);
 * char * s2 = subString(str,str+strlen(str));
 * char * s3 = subString(str+1,str+2);
 *
 * We get:
 *    s1: "";
 *    s2: "abcdef";
 *    s3: "b";
 * @endcode
 */

 /*--WAY first calu size of start ,get sub = malloc() ;then find end in sub ,->'\0',fine.--*/
char * IMPLEMENT(subString)(const char * start, const char * end) {
    /*return provided_subString(start, end);*/
   
/*--WAY1 first calu size of start ,get sub = malloc() ;then find end in sub ,->'\0',fine.--*/
/*   

    size_t sizeStart = stringLength(start);
    char * subString = NULL;
    char * pEnd = NULL;
    subString = (char *) malloc(sizeStart * sizeof(char));
    subString = duplicateString(start);
    pEnd = indexOfString(subString, end);
    pEnd = '\0';

    return subString;
*/
//void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize)
/*--WAY2:first calu size of start ,src,get copyStr = malloc(); copy with len,fin !--*/

 /*   //OK1 :
    char * subStr;

    subStr= (char *)malloc((sizeSub +1 ) * sizeof(char));

    if (subStr == NULL)
    {
        return NULL;
    } else {
     size_t i = 0;
    for (;i < sizeSub ;++i){
        *(subStr+i) = *(start + i);

    }

    *(subStr + i ) = '\0';

    return subStr ;
    } */

/*    //Test1: wrong with copyStringWithLength(,,!*!);
    size_t sizeStart = stringLength(start);
    size_t sizeEnd = stringLength(end);
    size_t sizeSub = sizeStart - sizeEnd;

    char * subStr = (char *)malloc(sizeSub * sizeof(char));

    copyStringWithLength(subStr, start, sizeSub);

    return subStr;*/

    //OK2,much better!
    size_t sizeStart = stringLength(start);
    size_t sizeEnd = stringLength(end);
    size_t sizeSub = sizeStart - sizeEnd;

    char * subStr = (char *)malloc( (sizeSub+1) * sizeof(char));

    copyStringWithLength(subStr, start, sizeSub + 1);
    return subStr ;

}

/** Like the strstr() function. It returns a pointer to the first occurrence of the string aiguille in the string meule_de_foin.
 * @param meule_de_foin the string to search in
 * @param aiguille the string to find
 * @return a pointer to the first occurrence of the string aiguille in the string meule_de_foin if aiguille is in meule_de_foin, NULL otherwise
 */

 /*Way:
    first,find 1st,get length, compare,match return,not next.
 */
const char * IMPLEMENT(indexOfString)(const char *meule_de_foin, const char *aiguille) {
    /*return provided_indexOfString(meule_de_foin, aiguille);*/
/*    if ((meule_de_foin == NULL) || (aiguille == NULL)) 
    {
        return NULL;
    }

    size_t sizeMeuleDeFoin = stringLength(meule_de_foin);
    size_t sizeAiguille = stringLength(aiguille);

    if (sizeMeuleDeFoin < sizeAiguille)
    {
        return NULL;
    } 

    size_t sizeExplore = sizeMeuleDeFoin - sizeAiguille;
    int indexMeble = 0;
    int indexAiguille = 0;
    for (;indexMeble < sizeExplore; ++indexMeble)
    {
        for (; indexAiguille < sizeAiguille; ++indexAiguille)
        {
            if (meule_de_foin[indexMeble + indexAiguille] != aiguille[indexAiguille])
            {
                break;
            }
        }
        if (indexAiguille = sizeAiguille)
        {
            return meule_de_foin+indexMeble;
        }
    }
    return NULL;*/

    if ((meule_de_foin == NULL) || (aiguille == NULL))
    {
        return NULL;
    } else {

    size_t sizeMeuleDeFoin = stringLength(meule_de_foin);
    size_t sizeAiguille = stringLength(aiguille);

    if (sizeMeuleDeFoin < sizeAiguille)
    {
        return NULL;
    } else {

    size_t sizeExplore = sizeMeuleDeFoin - sizeAiguille;
    size_t indexMeble = 0;
    size_t indexAiguille = 0;
    for (;indexMeble <= sizeExplore; ++indexMeble)
    {
        for (; indexAiguille < sizeAiguille; ++indexAiguille)
        {
            if (meule_de_foin[indexMeble + indexAiguille] != aiguille[indexAiguille])
            {
                break;
            }
        }
        if (indexAiguille == sizeAiguille)
        {
            return meule_de_foin + indexMeble ;
        }
    }
    return NULL;
    }
    }

}

/** Convert a string to upper case.
 * @param str the string to convert
 */
void IMPLEMENT(makeUpperCaseString)(char * str) {
/*provided_makeUpperCaseString(str);*/
    while (*str) {
        *str = toUpperChar(*str);
        ++str;
    }

}

/** Convert a string to lower case.
 * @param str the string to convert
 */
void IMPLEMENT(makeLowerCaseString)(char * str) {
    /*provided_makeLowerCaseString(str);*/
        while (*str) {
        *str = toLowerChar(*str);
        ++str;
    }
}

/** Create a new string on the heap which contents is the result of the insertion in src of insertLength characters from  toBeInserted at position insertPosition.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param src the string in which the insertion is done
 * @param insertPosition the position where the insertion is done
 * @param toBeInserted a pointer on the first character to insert
 * @param insertLength the number of character to insert
 * @return the new string
 */
char * IMPLEMENT(insertString)(const char * src, int insertPosition, const char * toBeInserted,
        int insertLength) {
    //return provided_insertString(src, insertPosition, toBeInserted, insertLength);
   
/*    //Test1 : wrong with copyStringWithLength(), those paras are confused .
    size_t sizeSrc = stringLength(src);
    
    char * insertStr;
    
    insertStr = (char *)malloc((sizeSrc + insertLength + 1)*(sizeof(char)));//
    if (insertStr == NULL)
    {
        fprintf(stderr,
            "\n Malloc() Failed in insertString().\n");
        return NULL;
    } else {
        copyStringWithLength(insertStr, src, insertPosition);
        copyStringWithLength(insertStr+insertPosition, toBeInserted, insertLength + 1);
        copyStringWithLength(insertStr + insertPosition + insertLength, insertStr + insertPosition, sizeSrc);
    }

    return insertStr;*/

    //OK1 : olala
    size_t sizeSrc = stringLength(src);
    char * insertStr;

    insertStr = (char *)malloc((sizeSrc + (size_t)insertLength + 1)*(sizeof(char)));
    if (insertStr == NULL)
    {
        fprintf(stderr,
            "\n Malloc() Failed In insertString().\n");
        return NULL;
    } else {
        copyStringWithLength(insertStr, src, (size_t)insertPosition +1);
        copyStringWithLength(insertStr + insertPosition, toBeInserted, (size_t)insertLength + 1);
        copyStringWithLength(insertStr + insertPosition + insertLength, src + insertPosition, sizeSrc + 1);
    }

    return insertStr;


}
