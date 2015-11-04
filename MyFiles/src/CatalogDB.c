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
 * $Id: CatalogDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

 /** The structure which represents an opened catalog database */
// typedef struct _CatalogDB {
//     FILE * file; *< The FILE pointer for the associated file 
//     int recordCount; /**< The number of record in the database */
// } CatalogDB;



#include <CatalogDB.h>
#include <CatalogRecord.h>
#include <CatalogRecordEditor.h>

/** The catalog file name */
const char * CATALOGDB_FILENAME = BASEPATH "/data/Catalog.db";

/** Create a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_create)(const char * filename) {
    //return provided_CatalogDB_create(filename);


    CatalogDB * catalogDB;
    catalogDB = (CatalogDB *)malloc(sizeof(CatalogDB));
    if(catalogDB == NULL) {
        fatalError("Malloc failed in CatalogDB_create()!");
    }

    catalogDB->recordCount = 0;
    //must allow read for after use.
    catalogDB->file = fopen(filename, "w+");
    if(catalogDB->file == NULL) {
        fatalError("Faile to open the datebase in CatalogDB_create()!");
        free(catalogDB);
        return NULL;
    } 

    if(fwrite(&(catalogDB->recordCount), sizeof(int), 1, catalogDB->file) != 1) {
        fatalError("Failed to set recordcount in CatalogDB_create()!");
        free(catalogDB);
        return NULL;
    }

    return catalogDB;
}

/** Open an existing database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_open)(const char * filename) {
    //return provided_CatalogDB_open(filename);
    CatalogDB * catalogDB;
    catalogDB = (CatalogDB *)malloc(sizeof(CatalogDB));
    if(catalogDB == NULL) {
        fatalError("Malloc failed in CatalogDB_open()!");
    }

    catalogDB->file = fopen(filename, "r+");
    if(catalogDB->file == NULL) {
        //fatalError("Faile to open the datebase in CatalogDB_open()!"); //no use!!!
        //free(catalogDB); 
        return NULL;
    } 

    if(fread(&(catalogDB->recordCount), sizeof(int), 1, catalogDB->file) != 1) {
        fatalError("Failed to set recordcount in CatalogDB_open()!");
        free(catalogDB);
        return NULL;
    }

    return catalogDB;
}

/** Open if exists or create otherwise a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_openOrCreate)(const char * filename) {
    //return provided_CatalogDB_openOrCreate(filename);

    CatalogDB * catalogDB;
    catalogDB = CatalogDB_open(filename);

    if(catalogDB == NULL) {
        catalogDB = CatalogDB_create(filename);
    } 

    return catalogDB;
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param catalogDB a pointer on a CatalogDB representing the opened database
 */
void IMPLEMENT(CatalogDB_close)(CatalogDB * catalogDB) {
    //provided_CatalogDB_close(catalogDB);
    fseek(catalogDB->file, 0, 0);
    if(fwrite(&(catalogDB->recordCount), sizeof(int), 1, catalogDB->file) != 1) {
        fatalError("Failed to write recordcount in CatalogDB_close()!");
    }
    fclose(catalogDB->file);
}

/** Get the number of records of the database
 * @param catalogDB the database
 * @return the number of records
 */
int IMPLEMENT(CatalogDB_getRecordCount)(CatalogDB * catalogDB) {
    //return provided_CatalogDB_getRecordCount(catalogDB);
    return catalogDB->recordCount;

}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param catalogDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogDB_getFieldValueAsString(CatalogDB * catalogDB, int recordIndex, int field) {
    char * content = NULL;
    if (catalogDB != NULL) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(field);
        CatalogRecord record;
        CatalogRecord_init(&record);
        CatalogDB_readRecord(catalogDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CatalogRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param catalogDB the database
 * @param record the record
 */
void IMPLEMENT(CatalogDB_appendRecord)(CatalogDB * catalogDB, CatalogRecord *record) {
    //provided_CatalogDB_appendRecord(catalogDB, record);
    fseek(catalogDB->file, 0, 2);
    CatalogRecord_write(record, catalogDB->file);
    ++(catalogDB->recordCount);
}

/** Insert the specified record at the given position in the database
 * @param catalogDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void IMPLEMENT(CatalogDB_insertRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    //provided_CatalogDB_insertRecord(catalogDB, recordIndex, record);
    int i;
    CatalogRecord temprecord;
    CatalogRecord_init(&temprecord);
    if(recordIndex >= 0 && recordIndex < catalogDB->recordCount) {
        i = catalogDB->recordCount - 1;
        while(i >= recordIndex) {
            CatalogDB_readRecord(catalogDB, i, &temprecord);
            CatalogDB_writeRecord(catalogDB, i+1, &temprecord);
            --i;
        }
        CatalogDB_writeRecord(catalogDB, recordIndex, record);
        CatalogRecord_finalize(&temprecord);
        ++(catalogDB->recordCount);
    } else {
        fatalError("recordIndex is illegal!");
    }
}

/** Remove a record at a given position from the database
 * @param catalogDB the database
 * @param recordIndex the removal position
 */
void IMPLEMENT(CatalogDB_removeRecord)(CatalogDB * catalogDB, int recordIndex) {
    //provided_CatalogDB_removeRecord(catalogDB, recordIndex);
    CatalogDB  record;

    if(recordIndex >= 0 && recordIndex < catalogDB->recordCount) {
        while(recordIndex < catalogDB->recordCount - 1) {
            CatalogDB_readRecord(catalogDB, recordIndex + 1, &record);
            CatalogDB_writeRecord(catalogDB, recordIndex, &record);
            ++recordIndex;
        }
        --catalogDB->recordCount;
    } else {
        fatalError("recordIndex is illegal!");
    }
}

/** Read a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void IMPLEMENT(CatalogDB_readRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    //provided_CatalogDB_readRecord(catalogDB, recordIndex, record);
    if(recordIndex >= 0 && recordIndex < catalogDB->recordCount) {
        fseek(catalogDB->file, (long) sizeof(int) + (long) recordIndex * (long) CATALOGRECORD_SIZE, 0);
        CatalogRecord_read(record, catalogDB->file);
    } else {
        fatalError("recordIndex is illegal!");
    }
}

/** Write a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void IMPLEMENT(CatalogDB_writeRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    //provided_CatalogDB_writeRecord(catalogDB, recordIndex, record);
    if(recordIndex >= 0 && recordIndex < catalogDB->recordCount) {
        fseek(catalogDB->file, (long) sizeof(int) + (long) recordIndex * (long) CATALOGRECORD_SIZE, 0);
        CatalogRecord_write(record, catalogDB->file);
    } else if(recordIndex == catalogDB->recordCount) {
        CatalogDB_appendRecord(catalogDB, record);
    } else {
        fatalError("recordIndex is illegal!");
    }
}

