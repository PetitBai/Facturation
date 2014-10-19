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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */


// /** The size of the name field */
// #define CUSTOMERRECORD_NAME_SIZE 70UL
// /** The size of the address field */
// #define CUSTOMERRECORD_ADDRESS_SIZE 130UL
// /** The size of the portalCode field */
// #define CUSTOMERRECORD_POSTALCODE_SIZE 20UL
// /** The size of the town field */
// #define CUSTOMERRECORD_TOWN_SIZE 90UL
 
// /** The size in bytes of all the packed fields of a CustomerRecord */
// #define CUSTOMERRECORD_SIZE (    CUSTOMERRECORD_NAME_SIZE + \
//                                  CUSTOMERRECORD_ADDRESS_SIZE + \
//                                  CUSTOMERRECORD_POSTALCODE_SIZE + \
//                                  CUSTOMERRECORD_TOWN_SIZE)
 
// /** A customer record */
// typedef struct {
//     /** The name */
//     char name[CUSTOMERRECORD_NAME_SIZE];
//     /** The address */
//     char address[CUSTOMERRECORD_ADDRESS_SIZE];
//     /** The postal code */
//     char postalCode[CUSTOMERRECORD_POSTALCODE_SIZE];
//     /** The Town */
//     char town[CUSTOMERRECORD_TOWN_SIZE];
// } CustomerRecord;


#include <CustomerRecord.h>

void IMPLEMENT(CustomerRecord_setValue_name)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_name(record, value);*/
  /*int i = 0;
  for (;*(value + i) != '\0'; ++i)
  {
    record->name[i] = *(value + i);
  }
  record->name[i] = '\0';*/
  copyStringWithLength(record->name, value, CUSTOMERRECORD_NAME_SIZE)

}

void IMPLEMENT(CustomerRecord_setValue_address)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_address(record, value);*/
  int i = 0;
  for (;*(value + i) != '\0'; ++i)
  {
    record->address[i] = *(value + i);
  }
  record->address[i] = '\0';
}

void IMPLEMENT(CustomerRecord_setValue_postalCode)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_postalCode(record, value);*/
      int i = 0;
    for (;*(value + i) != '\0'; ++i)
    {
      record->postalCode[i] = *(value + i);
    }

    record->postalCode[i] = '\0';
}

void IMPLEMENT(CustomerRecord_setValue_town)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_town(record, value);*/
      int i = 0;
    for (;*(value + i) != '\0'; ++i)
    {
      record->town[i] = *(value + i);
    }

    record->town[i] = '\0';
}

char * IMPLEMENT(CustomerRecord_getValue_name)(CustomerRecord * record)
{
  //return provided_CustomerRecord_getValue_name(record);
  /*char * tmps = record->name;
  return tmps;*/
  return duplicateString(record->name);

}

char * IMPLEMENT(CustomerRecord_getValue_address)(CustomerRecord * record)
{
  return provided_CustomerRecord_getValue_address(record);
}

char * IMPLEMENT(CustomerRecord_getValue_postalCode)(CustomerRecord * record)
{
  return provided_CustomerRecord_getValue_postalCode(record);
}

char * IMPLEMENT(CustomerRecord_getValue_town)(CustomerRecord * record)
{
  return provided_CustomerRecord_getValue_town(record);
}

void IMPLEMENT(CustomerRecord_init)(CustomerRecord * record)
{
  provided_CustomerRecord_init(record);
}

void IMPLEMENT(CustomerRecord_finalize)(CustomerRecord * record)
{
  provided_CustomerRecord_finalize(record);
}



































/*
Ecrire la fonction void CustomerRecord_read(CustomerRecord * record, FILE * file) qui permet de lire le contenu d'un enregistrement 
à partir du fichier binaire et qui stocke les informations dans l'enregistrement. 
Le fichier binaire contient que des enregistrements de taille fixe de CUSTOMERRECORD_SIZE octets. 
On prendra soin de ne pas écrire d'octets de padding dans la fichier.
*/
void IMPLEMENT(CustomerRecord_read)(CustomerRecord * record, FILE * file)
{
  //provided_CustomerRecord_read(record, file);
  file = record -> 
}

void IMPLEMENT(CustomerRecord_write)(CustomerRecord * record, FILE * file)
{
  provided_CustomerRecord_write(record, file);
}































