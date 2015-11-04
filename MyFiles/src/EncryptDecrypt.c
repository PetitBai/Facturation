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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>

 //Test1: in fact ,it's ok .but i choose to makeUppercase().

/* char keyroll(char charKey,char charStr) {
 	char newChar = (char)((charKey + charStr)%26 + 'A');
 	return newChar;
}

 void IMPLEMENT(encrypt)(const char * key, char * str) {
    //provided_encrypt(key,str);

    sizeKey = stringLength(key);
    int i = 0;
    int j = 0;

    char * keyUpper = duplicateString(key);
    makeUpperCaseString(keyUpper);
    makeUpperCaseString(str);

    for(;str[i] != '\0'; ++i, ++j)
    {
    	if ((str[i] >= 'A')&& (str[i] <= 'Z')
    	{
    		str[i] = keyroll(keyUpper[i % sizeKey],str[i]);
    	}
    }

    makeLowerCaseString(str);
}
*/

//Ok2: use lowcase, 
char keyroll(char charKey,char charStr) {
 	char newChar = (char)((charKey - 'a' + charStr - 'a')%26 + 'a');
 	return newChar;
}

 void IMPLEMENT(encrypt)(const char * key, char * str) {
    /*provided_encrypt(key,str);*/

    size_t  sizeKey = stringLength(key);
    int i = 0;
    int j = 0;

    char * keyLower = duplicateString(key);
    makeLowerCaseString(keyLower);
    makeLowerCaseString(str);

    for(;str[i] != '\0'; ++i, ++j)
    {
    	if ((str[i] >= 'a')&& (str[i] <= 'z'))
    	{
    		str[i] = keyroll(keyLower[i % (int)sizeKey],str[i]);
    	}
    }
}


char keybreak(char charKey,char charCrypt) {

	char newChar = (char)(charCrypt + 'a' -charKey);
	if (newChar < 'a' ) {

		newChar = (char)(newChar + 26);
	}
	
	return newChar;
}

void IMPLEMENT(decrypt)(const char * key, char * str) {
    /*provided_decrypt(key,str);*/

    size_t  sizeKey = stringLength(key);
    int i = 0;
    int j = 0;

    char * keyLower = duplicateString(key);
    makeLowerCaseString(keyLower);
    makeLowerCaseString(str);

    for(;str[i] != '\0'; ++i, ++j)
    {
    	if ((str[i] >= 'a')&& (str[i] <= 'z'))
    	{
    		str[i] = keybreak(keyLower[i % (int)sizeKey],str[i]);
    	}
    }
}

