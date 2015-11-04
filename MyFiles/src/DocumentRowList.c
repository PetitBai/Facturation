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
 * $Id: DocumentRowList.c 247 2010-09-10 10:23:07Z sebtic $
 */


 
// /** Structure representing a row in a document (as a cell in a simple linked list) */
// typedef struct _DocumentRow {
//     char * code /** The code */;
//     char * designation /** The designation */;
//     double quantity /** The quantity */;
//     char * unity * The unity ;
//     double basePrice /** The base price */;
//     double sellingPrice /** The selling price */;
//     double discount /** The discount */;
//     double rateOfVAT /** The rate of VAT */;
//     struct _DocumentRow * next /** The pointer to the next row */;
// } DocumentRow;



#include <DocumentRowList.h>
#include <DocumentUtil.h>

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
void IMPLEMENT(DocumentRow_init)(DocumentRow * row) {
    /*provided_DocumentRow_init(row);*/

    row->code = duplicateString("");
    row->designation = duplicateString("");
    row->quantity = 0;
    row->unity = duplicateString("");
    row->basePrice = 0;
    row->sellingPrice = 0;
    row->discount = 0;
    row->rateOfVAT = 0;
    row->next = NULL;
}

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
void IMPLEMENT(DocumentRow_finalize)(DocumentRow * row) {
    /*provided_DocumentRow_finalize(row);*/
    //TODO:need to clear to 0?or to NULL,before free?
    
    free(row->code);
    free(row->designation);
    free(row->unity);
    //dont free(next),cas it doesn't exist.
    /*free(row->next);*/

    row->code = NULL;
    row->designation = NULL;
    row->unity = NULL;
    row->next = NULL;
}

/** Create a new row on the heap and initialize it
 * @return the new row
 */
DocumentRow * IMPLEMENT(DocumentRow_create)(void) {
    /*return provided_DocumentRow_create();*/
    DocumentRow * newDocumentRow;
    newDocumentRow = (DocumentRow *)malloc(sizeof(DocumentRow));
    DocumentRow_init(newDocumentRow);

    return newDocumentRow;

    DocumentRow * row;
    row = (DocumentRow *)malloc(sizeof(DocumentRow));
    if(row == NULL) {
        fatalError("malloc failed in DocumentRow_create()!");
        return NULL;
    } else {
        DocumentRow_init(row);
        return row;
    }
}

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
void IMPLEMENT(DocumentRow_destroy)(DocumentRow * row) {
    /*provided_DocumentRow_destroy(row);*/
    DocumentRow_finalize(row);
    free(row);
}

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
 /*
  加深理解二星指针的意义，彻底搞懂。之前总不会想到，就一个语句。
  在程序结束后，list这个变量会自动clear。你想到了吗？
 */
void IMPLEMENT(DocumentRowList_init)(DocumentRow ** list) {
    /*provided_DocumentRowList_init(list);*/
    *list = NULL;
}

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */
void IMPLEMENT(DocumentRowList_finalize)(DocumentRow ** list) {
    /*provided_DocumentRowList_finalize(list);*/

    //!!!list is a pointer,(*list) is a row 
 /*   while(list != NULL) {
        DocumentRow_destroy(*list);
        list = *list->next;
    }
*/
    //it works?!!!
    // while(*list != NULL) {
    //     DocumentRow_destroy(*list);
    //     *list = (*list)->next;
    // }



    DocumentRow * temp;
    while(*list != NULL) {
        temp = *list;
        *list = temp->next;
        DocumentRow_destroy(temp);
    }

}

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */

 /*回去看桌面的图，了解row的各个部分到底是什么。怎么表示的。*/
DocumentRow * IMPLEMENT(DocumentRowList_get)(DocumentRow * list, int rowIndex) {
    /*return provided_DocumentRowList_get(list, rowIndex);*/
    DocumentRow *indexDocumentRow = list;//Don't use list directly,or will change the original list.
    int i = 0;
    while(indexDocumentRow != NULL && i < rowIndex) {
        indexDocumentRow = indexDocumentRow->next;
        ++i;
    }
    return indexDocumentRow;

    //directly!!so what?
    int i = 0;
    while(list != NULL && i < rowIndex) {
        list = list->next;
        ++i;
    }
    return list;
}

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
int IMPLEMENT(DocumentRowList_getRowCount)(DocumentRow * list) {
    /*return provided_DocumentRowList_getRowCount(list);*/

    int rowCount = 0;
    while(list != NULL) {
        list = list->next;
        rowCount++;
    }

    return rowCount; 
}

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
void IMPLEMENT(DocumentRowList_pushBack)(DocumentRow ** list, DocumentRow * row) {
    /*provided_DocumentRowList_pushBack(list, row);*/
    //NOTE:can't use (*list) directly,or will destory origin rows.
/*    while(*list != NULL) {
        list = (*list)->next;
    }
    row->next = NULL;
    (*list)->next = row;*/

    if ((*list) == NULL) {
        *list = row;
    } else {
        DocumentRow * outerRow = *list;
        while (outerRow->next != NULL) {
            outerRow = outerRow->next;
        }
        row->next = NULL;
        outerRow->next = row;
    }

}

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertBefore)(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    /*provided_DocumentRowList_insertBefore(list, position, row);*/
    if(*list == position) {
        *list = row;
        row->next = position;
    } else {
        DocumentRow * outerRow = *list;
        while (outerRow->next != position) {
            outerRow = outerRow->next;
        }
        row->next = outerRow->next;
        outerRow->next = row;
    }
}

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertAfter)(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    /*provided_DocumentRowList_insertAfter(list, position, row);*/

}

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
void IMPLEMENT(DocumentRowList_removeRow)(DocumentRow ** list, DocumentRow * position) {
    /*provided_DocumentRowList_removeRow(list, position);*/
    if(*list == position) {
        *list = position->next;
    } else {
        DocumentRow * outerRow = *list;
        while(outerRow->next != position) {
            outerRow = outerRow->next
        }
        outerRow->next = position->next;
    }
    DocumentRow_destroy(position);
}

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
void IMPLEMENT(DocumentRow_writeRow)(DocumentRow * row, FILE * file) {
    //provided_DocumentRow_writeRow(row, file);
    writeString(row->code, file);
    writeString(row->designation, file);
    writeString(row->unity, file);

    if(fwrite(&(row->quantity), sizeof(row->quantity), 1, file) != 1) {
        fatalError("failed to write file in DocumentRow_writeRow()!");
    }
    if(fwrite(&(row->basePrice), sizeof(row->basePrice), 1, file) != 1) {
       fatalError("failed to write file in DocumentRow_writeRow()!"); 
    }
    if(fwrite(&(row->sellingPrice), sizeof(row->sellingPrice), 1, file) != 1) {
       fatalError("failed to write file in DocumentRow_writeRow()!"); 
    }
    if(fwrite(&(row->discount), sizeof(row->discount), 1, file) != 1) {
       fatalError("failed to write file in DocumentRow_writeRow()!"); 
    }
    if(fwrite(&(row->rateOfVAT), sizeof(row->rateOfVAT), 1, file)  != 1) {
       fatalError("failed to write file in DocumentRow_writeRow()!"); 
    }

}

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
DocumentRow * IMPLEMENT(DocumentRow_readRow)(FILE * file) {
    //return provided_DocumentRow_readRow(file);
    DocumentRow * row;
    row = DocumentRow_create();
    DocumentRow_finalize(row);
    row->code = readString(file);
    row->designation = readString(file);
    row->unity = readString(file);
    if(fread(&(row->quantity), sizeof row->quantity, 1, file) != 1) {
        fatalError("failed to read file in DocumentRow_readRow()!");
    }
    if(fread(&(row->basePrice), sizeof row->basePrice, 1, file) != 1) {
        fatalError("failed to read file in DocumentRow_readRow()!");
    }
    if(fread(&(row->sellingPrice), sizeof row->sellingPrice, 1, file) != 1) {
        fatalError("failed to read file in DocumentRow_readRow()!");
    }
    if(fread(&(row->discount), sizeof row->discount, 1, file) != 1) {
        fatalError("failed to read file in DocumentRow_readRow()!");
    }
    if(fread(&(row->rateOfVAT), sizeof row->rateOfVAT, 1, file) != 1) {
        fatalError("failed to read file in DocumentRow_readRow()!");
    }

    return row;

}
