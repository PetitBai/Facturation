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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

 /** The structure which represents an opened customer database */
// typedef struct {
//     FILE * file; /* The FILE pointer for the associated file */
//     int recordCount; /*< The number of record in the database */ 
// } CustomerDB;*/

#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <CustomerRecordEditor.h>

const char * CUSTOMERDB_FILENAME = BASEPATH "/data/Customer.db";

CustomerDB * IMPLEMENT(CustomerDB_create)(const char * filename) {
    //return provided_CustomerDB_create(filename);


    CustomerDB * db;
    db = (CustomerDB *)malloc(sizeof(CustomerDB));
    if (db == NULL) {
        fatalError("malloc failed in CustomerDB_create()!");
    }

    db->file = fopen(filename, "w+");
    if(db->file == NULL) {
        fprintf(stderr, "Failed to open the file in CustomerDB_create()!");
        free(db);
        return NULL;
    } 

    db->recordCount = 0;
    if(fwrite(&(db->recordCount), sizeof(int), 1, db->file) != 1) {
        fprintf(stderr, "Failed to write in the file in CustomerDB_create()! ");
        fclose(db->file);
        free(db);
        return NULL;
    }

    return db;

}



CustomerDB * IMPLEMENT(CustomerDB_open)(const char * filename) {
    /*return provided_CustomerDB_open(filename);*/
    CustomerDB * db;
    db = (CustomerDB *)malloc(sizeof(CustomerDB));
    if (db == NULL) {
        fatalError("malloc failed in CustomerDB_create()!");
    }

    db->file = fopen(filename, "w+");
    if(db->file == NULL) {
        fprintf(stderr, "Failed to open the file in CustomerDB_create()!");
        free(db);
        return NULL;
    } 

    db->recordCount = 0;
    if(fread(&(db->recordCount), sizeof(int), 1, db->file) != 1) {
        fprintf(stderr, "Failed to write in the file in CustomerDB_create()! ");
        fclose(db->file);
        free(db);
        return NULL;
    }

    return db;

}

CustomerDB * IMPLEMENT(CustomerDB_openOrCreate)(const char * filename) {
    //return provided_CustomerDB_openOrCreate(filename);
   
       
    CustomerDB *db;
    db = CustomerDB_open(filename);

    if(db == NULL) {
        db = CustomerDB_create(filename);
    } 

    return db;

}

void IMPLEMENT(CustomerDB_close)(CustomerDB * customerDB) {
    //provided_CustomerDB_close(customerDB);

    //fseek() to set file pointer to a special point.
    fseek(customerDB->file, 0, 0);
    //Before closing, write the count. 
    if(fwrite(&(customerDB->recordCount), sizeof(int), 1, customerDB->file) != 1) {
        fatalError("Failed to write recordCount in CustomerDB_close()!");
    }
    //finally, fclose
    fclose(customerDB->file);
}

int IMPLEMENT(CustomerDB_getRecordCount)(CustomerDB * customerDB) {
    //return provided_CustomerDB_getRecordCount(customerDB);

    //so direct, are you still familiar?
    return customerDB->recordCount;
}

char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}

void IMPLEMENT(CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record) {
    //provided_CustomerDB_appendRecord(customerDB, record);

    //fseek(customerDB->file, (long) sizeof(int)(long) + (customerDB->recordCount) * CUSTOMERRECORD_SIZE, 0);
    
    fseek(customerDB->file, 0, 2);
    if(fwrite(record, CUSTOMERRECORD_SIZE, 1, customerDB->file) != 1) {
        fatalError("Failed to appenRecord in CustomerDB_appendRecord()"!);
    } else {
        ++(customerDB->recordCount);
    }
}

void IMPLEMENT(CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    //provided_CustomerDB_insertRecord(customerDB, recordIndex, record);

    int i;
    CustomerRecord temprecord;

    if(recordIndex >= 0 && recordIndex < customerDB->recordCount) {
        i = customerDB->recordCount - 1;
        while(i >= recordIndex) {
            CustomerDB_readRecord(customerDB, i, &temprecord);
            CustomerDB_writeRecord(customerDB, i+1, &temprecord);
            --i;
        }
        CustomerDB_writeRecord(customerDB, recordIndex, record);
        ++(customerDB->recordCount);
    } else {
        fatalError("recordIndex is illegal!");
    }


}

void IMPLEMENT(CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex) {
    //provided_CustomerDB_removeRecord(customerDB, recordIndex);

   // if use CustomerRecord * record, then must malloc, intital, free ...it is waste of time 
    CustomerRecord  record;

    if(recordIndex >= 0 && recordIndex < customerDB->recordCount) {
        while(recordIndex < customerDB->recordCount - 1) {
            CustomerDB_readRecord(customerDB, recordIndex + 1, &record);
            CustomerDB_writeRecord(customerDB, recordIndex, &record);
            ++recordIndex;
        }

        --customerDB->recordCount;
    } else {
        fatalError("recordIndex is illegal!");
    }
}

void IMPLEMENT(CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    //provided_CustomerDB_readRecord(customerDB, recordIndex, record);
    if(recordIndex >= 0 && recordIndex < customerDB->recordCount) {

    //convertion to (long) to combine size_t and int 
        fseek(customerDB->file, (long) sizeof(int) + (long) recordIndex * (long) CUSTOMERRECORD_SIZE, 0);
        CustomerRecord_read(record, customerDB->file);
    } else {
        fatalError("recordIndex is illegal!");
    }
}

void IMPLEMENT(CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    //provided_CustomerDB_writeRecord(customerDB, recordIndex, record);

    if(recordIndex >= 0 && recordIndex < customerDB->recordCount) {
        fseek(customerDB->file, (long) sizeof(int) + (long) recordIndex * (long) CUSTOMERRECORD_SIZE, 0);
        CustomerRecord_write(record, customerDB->file);
    } else if(recordIndex == customerDB->recordCount) {
        CustomerDB_appendRecord(customerDB, record);
    } else {
        fatalError("recordIndex is illegal!");
    }
}
