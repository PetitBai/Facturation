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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>

 /*
 *Écrire la fonction BaseB2Dec qui admet trois arguments 
 *(la base B, le nombre de chiffres N du tableau, et un tableau de N chiffres) et qui retourne l'entier long n associé. 
 *On prendra soin de préciser la convention de représentation utilisée (i.e. dans quel ordre sont les "bits" dans le tableau).
*/
long BaseB2Dec (int base_B, int num_N, const  int *tableau) {
	
/*	//en supposant que les "bits" sont décrit du plus faible au plus fort)
	long value = 0;
	//int i = num_N -1;
 	for (int i = num_N -1; i >= 0; --i) {
		//long = tableau[i] * base_B +tableau[i-1];
		value = value * base_B + tableau[i];

*/

	//en supposant que les "bits" sont décrit du plus fort au plus faible)
	// it's more easier to users,but harder to computers!!
	long value = 0;
	//int i = num_N -1;
 	for (int i = 0; i < num_N ; ++i) {
		//long = tableau[i] * base_B +tableau[i-1];
		value = value * base_B + tableau[i];
	}

	return value;
 }

/*Écrire la fonction Bin2Dec, utilisant BaseB2Dec, 
 *qui retourne la valeur décimale signée correspondant 
 *à la représentation binaire sur 16 bits fournie en paramètre. 
 *Pour cela, on utilisera la formule ci-dessous et on considèrera 
 *que le "bit" de poids fort indique le signe du nombre sous la forme 0/1.
*/

 long Bin2Dec (const int * bin_tab) {
 	
 	int bin_tab_14[15] = {};

 	for (int i = 0; i <= 14; ++i)
 	{
 		bin_tab_14[i] = bin_tab[i+1];
 	//	printf ("Line %d , %d -- %d \n",i,bin_tab_14[i],bin_tab[i+1]);
 	}

 	long value_14 = BaseB2Dec (2, 15, bin_tab_14);
 	//calc pow(2,15)
 	long value_max = 2;
 	for (int i = 0; i < 14; ++i)
 	{
 		value_max *= 2;
 	}
 	
 	if (bin_tab[0] == 0){
 		return value_14;
 	} else if (bin_tab[0] == 1) {
 		return (value_14 - value_max);
 	} else {
 		printf ("source value is not binary based!!! \n");
 		return 0;
 	}

 }

/* 
 *Conversion d'un entier en une chaîne de caractères
 *
 *Écrire une fonction qui admet deux paramètres (un entier n et un tableau s de caractères suffisamment grand), 
 *et qui écrit dans s la représentation de n sous forme d'une chaîne de caractères.
 *
 *Ecrire la fonction main associée. Lorsque le nombre n est négatif, 
 *le signe '-' doit précéder les nombres dans la chaîne s. Les fonctions de MyString.h peuvent être utilisées.
 */

void ent2car (int n, char * tab_car) {
	int i_tab = 0;
	if (n < 0) {
		tab_car[i_tab] = '-';
		n = n * (-1);
		//printf("%d. n = %10d, remainder = %c .\n",i_tab,n,tab_car[i_tab]);
		++i_tab;

	}

	for (; n > 0; n = n/10, ++i_tab) {
		// convert num to char
		tab_car[i_tab] = n % 10 + 48;
		//printf("%d. n = %10d, remainder = %c .\n",i_tab,n,tab_car[i_tab]);
	}
	//add '\0' to combine chars to string
	tab_car[i_tab] = '\0'; 
}


/*Conversion d'une chaîne de caractères héxadécimale en un entier

On considère la chaîne de caractères s qui représente un entier non signé sous forme hexadécimale. 
La chaîne s se présente sous une des formes suivantes : "0X1AB97", "0x1AB97", "0x1aB97" ou "0X1Ab97".

Écrire la fonction admettant comme argument un pointeur sur la chaîne s et qui renvoie l'entier représenté par la chaîne s. 
Ecrire la fonction main associée.
*/
/*way of thought:
 *string of hex -> int ,first turn to UpperCase,then find 'X', behind 'X' , it's four chars in forme hex.
 *turn char to int ,then call BaseBtoDec(16,4,XXXX),it's done . Attention！:the from High to Low
 */

 long hex_str2ent (char * tab_string_hex) {

 	//makeUpperCaseString (tab_string_hex);// defined in <string.h>
 	int i_tab_string_hex = 0;
 	while (tab_string_hex[i_tab_string_hex] != 'X') {
 		++i_tab_string_hex;
 	}

 	int count_hex_char = 0;//count how many hex_chars are
 	int num_hex_char[5] = {}; // store num 0-15 converted from hex_char 
 	while (tab_string_hex[i_tab_string_hex + 1] != '\0') {
 		++i_tab_string_hex;
 		// convert hex_char to dec_num, 'A'-65 <-> A-10 ,'0'-48<->0-0 
 		num_hex_char[count_hex_char] = (tab_string_hex[i_tab_string_hex] < 60? tab_string_hex[i_tab_string_hex] -48 : tab_string_hex[i_tab_string_hex] -55);
 		++count_hex_char;
 	}

 	long value_hexstr2ent =  BaseB2Dec(16,count_hex_char,num_hex_char);

	return value_hexstr2ent;	
 }


/*
 Écrire la fonction Dec2Bin qui admet deux paramètres 
 (un nombre entier de type short et un tableau de 16 entiers) 
 et qui stocke dans ce tableau la représentation binaire signée de l'entier 
 calculé grâce au schéma de Horner. 
 Vous prendrez soin de définir l'ordre des bits dans le tableau.
*/
/* 
 *way of thinking 
 *first, turn n to positive ,define tab[0] = 0 or 1
 *then ,mod 2,reminder -> tableau,divided by 2,mod 2 ...until n==0 
 */

void Dec2Bin (short n, int * tab_dec) {

	

	if (n  < 0) {
		int  pow_2_14 = 2;
 		for (int i = 0; i < 14; ++i) {
 		pow_2_14 *= 2;
 		}
 		n = n + pow_2_14;
 		tab_dec[0] = 1;
	} 

	// else {
	// 	tab_dec[0] = 0;
	// }

	int i_tab_dec = 15;
	for (; n > 0; n = n/2, --i_tab_dec) {
		// convert dec to bin
		tab_dec[i_tab_dec] = n % 2 ;
		//printf("%d. n = %10d, remainder = %d .\n",i_tab_dec,n,tab_dec[i_tab_dec]);
	} 

	for (int j = 0;j <= 15;++j) {
		printf("%d, -> %d .\n",j,tab_dec[j]);
	}
	
 }

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(computeDocumentNumber)(long id) {
    //return provided_computeDocumentNumber(id);

    char * idString;
    int remainder;
    char temp[16];
    int i = 0, j = 0;

    while(id != 0) {
    	remainder = (char)(id%36);
    	if (remainder < 10) {
    		temp[i] = (char)(remainder + '0');
    	} else {
    		temp[i] = (char)(remainder - 10 + 'A');
    	}

    	id = id/36;
    	++i;
    }
    --i;

    idString = (char *)malloc(sizeof(char) * (size_t)(i + 1));
    if(idString == NULL) {
    	fatalError("Malloc failed in computeDocumentNumber()!");
    }
    while(i >= 0) {
    	idString[j] = temp[i];
    	++j;
    	--i;
    }
    idString[j] = '\0';
    return idString;
}

/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(formatDate)(int day, int month, int year) {
    //return provided_formatDate(day, month, year);
    char *formatdate =  (char *)malloc(11 * sizeof(char));
    if(formatdate == NULL) {
        fatalError("malloc failed in formatDate()!");
    }
    sprintf(formatdate, "%02d/%02d/%04d", day, month, year);
    return formatdate;
}



/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */

void IMPLEMENT(writeString)(const char * str, FILE * file) {
    /*provided_writeString(str,file);*/

    size_t len = stringLength(str);

    if(fwrite(&len, sizeof(size_t), 1, file) != 1) {
    	fatalError("Failed to write length of str in writeString()!");
    }

    if(fwrite(str, sizeof(char), len, file) != len) {
    	fatalError("Failed to write str to file in writeString()!");
    }
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * IMPLEMENT(readString)(FILE * file) {
    //return provided_readString(file);
    size_t len;
    char * result;
    int n;
    if((n = fread(&len, sizeof(size_t), 1, file) != 1)) {
        fprintf(stderr, "Erreur de lecture dans le fichier! %d \n ", n);
        return NULL;
    }
    result = (char *)malloc((len + 1) * sizeof(char));
    if(result == NULL) {
        fprintf(stderr, "Erreur d'allocation!\n");
        exit(-1);
    }
    if(fread(result, sizeof(char), len, file) != len) {
        fprintf(stderr, "Erreur de lecture dans le fichier!\n");
        return NULL;
    }
    result[len] = '\0';
    return result;

    char * str;
    size_t len;

    if(fread(&len, sizeof(size_t), 1, file) != 1) {
    	fatalError("Failed to read length of str in readString!");
    }

    str = (char *)malloc((len+1) * sizeof(char));
    if(str == NULL) {
    	fatalError("malloc failed in readString()!");
    }

    if(fread(str, sizeof(char), len, file) != len) {
    	fatalError("failed to read string of file in readString()!");
    }

    str[len] = '\0';
    return str;
}
