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
 * $Id: Document.c 247 2010-09-10 10:23:07Z sebtic $
 */

 /** Enumeration defining the type of a document */
// typedef enum {
//     QUOTATION /**< It's a quotation */,
//     BILL /**< It's a bill */
// } TypeDocument;
 
// /** Structure representing a document */
// typedef struct {
//     CustomerRecord customer /** The customer */;
//     char * editDate /** The last edit data */;
//     char * expiryDate * The peremption date ;
//     char * docNumber /** The document number */;
//     char * object /** The object of the document */;
//     char * operator /** The last operator */;
//     DocumentRow * rows /** The rows */;
//     TypeDocument typeDocument /** The type of document */;
// } Document;

#include <Document.h>
#include <DocumentUtil.h>
#include <DocumentRowList.h>

/** Initialize a document
 * @param document a pointer to a document
 * @warning An initialized document must be finalized by Document_finalize() to free all resources
 */
void IMPLEMENT(Document_init)(Document * document) {
    //provided_Document_init(document);
    CustomerRecord_init(&(document->customer));
    document->editDate = duplicateString("");
    document->expiryDate = duplicateString("");
    document->docNumber = duplicateString("");
    document->object = duplicateString("");
    document->operator = duplicateString("");
    document->rows = NULL;
    document->typeDocument = QUOTATION;
}

/** Finalize a document
 * @param document the document to finalize
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_finalize)(Document * document) {
    //provided_Document_finalize(document);
    free(document->editDate);
    free(document->expiryDate);
    free(document->docNumber);
    free(document->object);
    free(document->operator);
}

/** Save the content of a document to a file
 * @param document the document
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_saveToFile)(Document * document, const char * filename) {
    //provided_Document_saveToFile(document,filename);
    DocumentRow * row;
    int rowCount;
    FILE * file;
    file = fopen(filename, "w");
    if(file == NULL){
        fatalError("Failed to open file in Document_saveToFile()!");
    }

    CustomerRecord_write(&(document->customer), file);
    writeString(document->editDate, file);
    writeString(document->expiryDate, file);
    writeString(document->docNumber, file);
    writeString(document->object, file);
    writeString(document->operator, file);

    if(fwrite(&(document->typeDocument), sizeof(TypeDocument), 1, file) != 1) {
    	fatalError("Failed to write typeDocument in Document_saveToFile()!");
    }

    rowCount = DocumentRowList_getRowCount(document->rows);
    if(fwrite(&(rowCount), sizeof(rowCount), 1, file) != 1) {
    	fatalError("Failed to write rowcount in Document_saveToFile()!");
    }
    row = document->rows;
    while(row != NULL){
        DocumentRow_writeRow(row, file);
        row = row->next;
    }
    fclose(file);
}

/** Load the content of a document from a file
 * @param document the document to fill
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_loadFromFile)(Document * document, const char * filename) {
    //provided_Document_loadFromFile(document,filename);
    int rowCount, i;
    FILE * file;
    file = fopen(filename, "r");
    if(file == NULL){
        fprintf(stderr, "Could not load document from file %s\n", filename);
        return;
    }

    Document_finalize(document);
    CustomerRecord_read(&(document->customer), file);
    document->editDate = readString(file);
    document->expiryDate = readString(file);
    document->docNumber = readString(file);
    document->object = readString(file);
    document->operator = readString(file);

    if(fread(&(document->typeDocument), sizeof(TypeDocument), 1, file) != 1) {
    	fatalError("Failed to read typeDocument in Document_loadFromFile()!");
    }
    if(fread(&(rowCount), sizeof rowCount, 1, file) != 1) {
    	fatalError("Failed to read rowcount in Document_loadFromFile()!");
    }
    
    i = 0;
    while(i < rowCount){
        DocumentRowList_pushBack(&(document->rows), DocumentRow_readRow(file));
        ++i;
    }
    fclose(file);
}

