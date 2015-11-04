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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */


//  /** The size in bytes of the code field of a CatalogRecord */
// #define CATALOGRECORD_CODE_SIZE 16UL
// /** The size in bytes of the designation field of a CatalogRecord */
// #define CATALOGRECORD_DESIGNATION_SIZE 128UL
// /** The size in bytes of the unity field of a CatalogRecord */
// #define CATALOGRECORD_UNITY_SIZE 20UL
// /** The size in bytes of the basePrice field of a CatalogRecord */
// #define CATALOGRECORD_BASEPRICE_SIZE ((unsigned long) sizeof(double))
// /** The size in bytes of the sellingPrice field of a CatalogRecord */
// #define CATALOGRECORD_SELLINGPRICE_SIZE ((unsigned long) sizeof(double))
// /** The size in bytes of the rateOfVAT field of a CatalogRecord */
// #define CATALOGRECORD_RATEOFVAT_SIZE ((unsigned long) sizeof(double))
 
// /** The size in bytes of all the packed fields of a CatalogRecord */
// #define CATALOGRECORD_SIZE (CATALOGRECORD_CODE_SIZE + \
//                             CATALOGRECORD_DESIGNATION_SIZE + \
//                             CATALOGRECORD_UNITY_SIZE + \
//                             CATALOGRECORD_BASEPRICE_SIZE + \
//                             CATALOGRECORD_SELLINGPRICE_SIZE + \
//                             CATALOGRECORD_RATEOFVAT_SIZE)
 
// /** The maximal length in characters of the string fields of a CatalogRecord */
// #define CATALOGRECORD_MAXSTRING_SIZE ( \
//                         MAXVALUE(CATALOGRECORD_CODE_SIZE, \
//                         MAXVALUE(CATALOGRECORD_DESIGNATION_SIZE,CATALOGRECORD_UNITY_SIZE)))
 
// /** A catalog record
//  */
// typedef struct {
//     char * code /** The code of the product */;
//     char * designation /** The designation of the product */;
//     char * unity /** The unity of the product */;
//     double basePrice /** The base price of the product (the product should not be sold at a lower price) */;
//     double sellingPrice /** The selling price of the product */;
//     double rateOfVAT /** The rate of the VAT of the product */;
// } CatalogRecord;


#include <CatalogRecord.h>

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_code)(const char * value)
{
  /*return provided_CatalogRecord_isValueValid_code(value);*/
  /*int flag = 1;
  int i = 0;

  for(; (*value != '\0') && flag; ++value) {
    //Hahahhah, it's a jok!!!
    //if (!('0' <= *value <= '9' || 'A' <= *value <= 'Z' || 'a' <= *value <= 'z' )
     // wrong in logic!!Be careful with parentheses
    //if (! ( ( *value >= '0' && *value <= '9') || *value >= 'A' && *value <= 'Z' || *value >= 'a' && *value <= 'Z' )

    // OK 
    if (!((*value >= '0' && *value <= '9') || (*value >= 'A' && *value <= 'Z') || (*value >= 'a' && *value <= 'z')))
    {
      flag = 0;
    }
  }

  return flag;*/

  int flag = 1;
  int i;

  for(i = 0; (*value != '\0' && flag; ++value) {
    if (!((*value >= '0' && *value <= '9') || (*value >= 'A' && *value <= 'Z') || (*value >= 'a' && *value <= 'z'))) {
      flag = 0;
    }
  }

  return flag;
}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_positiveNumber)(const char * value)
{
  //return provided_CatalogRecord_isValueValid_positiveNumber(value);
      char *endptr;
    double x;
    x = strtod(value, &endptr);
    if(*endptr == '\0' && x > 0) {
        return 1;
    } else {
        return 0;
    }
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_code)(CatalogRecord * record, const char * value)
{
  //provided_CatalogRecord_setValue_code(record, value);
      copyStringWithLength(record->code, value, CATALOGRECORD_CODE_SIZE);
}

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_designation)(CatalogRecord * record, const char * value)
{
  //provided_CatalogRecord_setValue_designation(record, value);
   copyStringWithLength(record->designation, value, CATALOGRECORD_DESIGNATION_SIZE);

}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_unity)(CatalogRecord * record, const char * value)
{
  //provided_CatalogRecord_setValue_unity(record, value);
    copyStringWithLength(record->unity, value, CATALOGRECORD_UNITY_SIZE);

}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_basePrice)(CatalogRecord * record, const char * value)
{
  //provided_CatalogRecord_setValue_basePrice(record, value);
    record->basePrice = strtod(value, NULL);
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_sellingPrice)(CatalogRecord * record, const char * value)
{
  provided_CatalogRecord_setValue_sellingPrice(record, value);
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_rateOfVAT)(CatalogRecord * record, const char * value)
{
  provided_CatalogRecord_setValue_rateOfVAT(record, value);
}

/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_code)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_code(record);
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_designation)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_designation(record);
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_unity)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_unity(record);
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_basePrice)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_basePrice(record);
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_sellingPrice)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_sellingPrice(record);
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_rateOfVAT)(CatalogRecord * record)
{
  return provided_CatalogRecord_getValue_rateOfVAT(record);
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void IMPLEMENT(CatalogRecord_init)(CatalogRecord * record)
{
  provided_CatalogRecord_init(record);
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void IMPLEMENT(CatalogRecord_finalize)(CatalogRecord * record)
{
  /*provided_CatalogRecord_finalize(record);*/

/*  free(record);
  record = NULL;*/

  // free the link.
  free(record -> code);
  free(record ->designation);
  free(record -> unity);

  //for multi-layer table, it's useful.But why?
  record -> code = NULL;
  record ->designation = NULL;
  record -> unity = NULL;

}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void IMPLEMENT(CatalogRecord_read)(CatalogRecord * record, FILE * file)
{
  /*provided_CatalogRecord_read(record, file);*/


    if(fread(record->code, CATALOGRECORD_CODE_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }
    if(fread(record->designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }
    if(fread(record->unity, CATALOGRECORD_UNITY_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }
    if(fread(&(record->basePrice), CATALOGRECORD_BASEPRICE_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }
    if(fread(&(record->sellingPrice), CATALOGRECORD_SELLINGPRICE_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }
    if(fread(&(record->rateOfVAT), CATALOGRECORD_RATEOFVAT_SIZE, 1, file) != 1) {
        fatalError("read info failed in CatalogRecord_read()!");
    }




}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void IMPLEMENT(CatalogRecord_write)(CatalogRecord * record, FILE * file)
{
  //provided_CatalogRecord_write(record, file);
    if(fwrite(record->code, CATALOGRECORD_CODE_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
    if(fwrite(record->designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
    if(fwrite(record->unity, CATALOGRECORD_UNITY_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
    if(fwrite(&(record->basePrice), CATALOGRECORD_BASEPRICE_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
    if(fwrite(&(record->sellingPrice), CATALOGRECORD_SELLINGPRICE_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
    if(fwrite(&(record->rateOfVAT), CATALOGRECORD_RATEOFVAT_SIZE, 1, file) != 1) {
        fatalError("write info failed in CatalogRecord_write()!");
    }
}

