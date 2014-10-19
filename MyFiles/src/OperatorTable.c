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
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <EncryptDecrypt.h>

//  //La structure de données associées est la suivante :
//  /** The maximal length in characters of the name of an operator */
// #define OPERATORTABLE_MAXNAMESIZE 20UL
// /** The maximal length in characters of the password of an operator */
// #define OPERATORTABLE_MAXPASSWORDSIZE 20UL
 
// /** The dynamic table of operators */
// typedef struct {
//     * The number of operators in the table 
//     int recordCount;
//     /** The data about the operators. It's a 2D array of strings.
//      * Note: records[operatorId][0] is the name of the operatorId'th operator
//      * Note: records[operatorId][1] is the password of the operatorId'th operator
//      */
//     char *** records;
// } OperatorTable;

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_create)(void) {
    //return provided_OperatorTable_create();
    OperatorTable *newTable;
    
    newTable = (OperatorTable *) malloc (sizeof(OperatorTable));
    //newTable.recordCount = 0;// n+1
    //newTable.records[operatorId][0][OPERATORTABLE_MAXNAMESIZE] = {""};
    //wOp.records[operatorId][1][OPERATORTABLE_MAXPASSWORDSIZE] = {""};

    newTable -> recordCount = 0; 
    newTable -> records = NULL;

    //TODO: relate tables

    return newTable;
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_destroy)(OperatorTable * table) {
    //provided_OperatorTable_destroy(table);
    while (table) {
        //TODO: delete relations

        free (table);
    }
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
 /*
  *way of thinking :first Create a new table,then read filename,add [0],[1],recordCount +1
  *until *filename = 0;
 */ 
OperatorTable * IMPLEMENT(OperatorTable_loadFromFile)(const char * filename) {
    //return provided_OperatorTable_loadFromFile(filename);
    newTable = OperatorTable_create ();
    while (filename) {
        newTable->records[newTable->recordCount][0] = (*filename)++;
        newTable->records[newTable->recordCount][1] = (*filename)++;
        ++newTable->recordCount; //TODO:maybe need +1
    }

    return newTable;
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_saveToFile)(OperatorTable * table, const char * filename) {
    //provided_OperatorTable_saveToFile(table, filename);

}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_getRecordCount)(OperatorTable * table) {
    //return provided_OperatorTable_getRecordCount(table);
    if (table) {
        return table -> recordCount;
    } else {
        return NULL;
    }
}

/** Get the name of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getName)(OperatorTable * table, int recordIndex) {
    //return provided_OperatorTable_getName(table, recordIndex);
    if (recordIndex >= 0 && recordIndex <= table->recordCount ) {
        return table ->records[recordIndex][0];
    } else {
        return NULL;
    }
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the paswword of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getPassword)(OperatorTable * table, int recordIndex) {
    //return provided_OperatorTable_getPassword(table, recordIndex);
     if (recordIndex >= 0 && recordIndex <= table->recordCount ) {
        return table ->records[recordIndex][1];
    } else {
        return NULL;
    }
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
/*
 *way of thingking :
 *first for(index: 0- recordCount) in table ,pick every i_name and cmp with name given.
 *if match , return index, else return -1
*/
int IMPLEMENT(OperatorTable_findOperator)(OperatorTable * table, const char * name) {
    //return provided_OperatorTable_findOperator(table, name);
    for (int recordIndex = 0; recordIndex <= table->recordCount; ++recordIndex) {
        int flag = cmpSTR (table->records[recordIndex][0],name);
        while (flag = 1) {
            //TODO: return and break ,who is in front?
            //TODO: break while or for!!!!
            return recordIndex;
            break;
        }
    return -1;
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
/**
  *way of thinking 
  *first,call OperatorTable_findOperator(),get index ,then change password.
 **/
int IMPLEMENT(OperatorTable_setOperator)(OperatorTable * table, const char * name, const char * password) {
    //return provided_OperatorTable_setOperator(table, name, password);
    recordIndex = OperatorTable_findOperator (table, name);
    while (recordIndex != -1) {
        table->records[recordIndex][1] = password;    
    } 

    return recordIndex;
}

/** Remove an operator from the table.
 * @param table the table of operators
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
/*
 *way of thingking :
 *1.first,find the op and = 0;then behind index one by one +1,fin recordCount -1
 *2.find op, and roll left
 */
void IMPLEMENT(OperatorTable_removeRecord)(OperatorTable * table, int recordIndex) {
    //provided_OperatorTable_removeRecord(table, recordIndex);
    //Can chang [index] directly? 
    for (; recordIndex <= table->recordCount; ++recordIndex) {
        table->records[recordIndex][0] = table->records[recordIndex+1][0]; 
        table->records[recordIndex][1] = table->records[recordIndex+1][1]; 
    }
    --recordCount;
}

