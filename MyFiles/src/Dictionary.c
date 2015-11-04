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
 * $Id: Dictionary.c 247 2010-09-10 10:23:07Z sebtic $
 */


// /** Enumeration defining the type of the doctionary entries */
// typedef enum {
//     UNDEFINED_ENTRY /* It's undefined */,
//     NUMBER_ENTRY /** It's a number */,
//     STRING_ENTRY /** It's a string */
// } DictionaryEntryType;
 
// /** Structure representing an entry in the dictionary */
// typedef struct {
//     /** The type of entry */
//     DictionaryEntryType type;
//     /** The name of the entry */
//     char * name;
//     /** The union which store the value of the entry */
//     union {
//         /** The value of the entry when it's a string */
//         char * stringValue;
//         /** The value of the entry when it's a real number */
//         double numberValue;
//     } value;
// } DictionaryEntry;

//  /** Structure representing a dictionary */
// typedef struct _Dictionary {
//     * The number of entries of the dictionary 
//     int count;
//     /** The table of entries */
//     DictionaryEntry * entries;
// } Dictionary;

#include <Dictionary.h>

/** Create an empty dictionary on the heap
 * @return a new dictionary
 * @warning the dictionary should be destroyed using Dictionary_destroy()
 */
// attentinon!! a.b and a->b,wen wangchenhao ,sangexiefa
//.对应 struct成员，－>对应指针。

Dictionary * IMPLEMENT(Dictionary_create)(void)
{
  /*return provided_Dictionary_create();*/
	Dictionary *dict =(Dictionary *)malloc(sizeof(Dictionary*));
	if (dict == NULL) {
		fprintf(stderr, "Maclloc() failed in Dictionary_create(). \n");
		exit(-1);
	}

	dict->count = 0;
	dict->entries = NULL;

	return dict;
}

/** Destroy a dictionary
 * @param dictionary the dictionary
 */
void IMPLEMENT(Dictionary_destroy)(Dictionary * dictionary)
{
  /*provided_Dictionary_destroy(dictionary);*/
	dictionary->entries = NULL;//it's necessary? cas i don't know details
	free(dictionary);
	dictionary = NULL;
}

/** Get a pointer on the entry associated with the given entry name
 * @param dictionary the dictionary
 * @param name the name of the entry
 * @return a pointer on the entry or NULL if the entry was not found
 */
DictionaryEntry * IMPLEMENT(Dictionary_getEntry)(*Dictionary * dictionary, const char * name)
{
  /*return provided_Dictionary_getEntry(dictionary, name);*/
	// if (writeString(*(dictionary->entries[1]),name) == 0)
	// {
		
	// 	return &dictionary->entries;//(why? address and )
	// } else {
	// 	return NULL;
	// }

	//Wrong:totlay didn't understand the meaning of this part. Keyword:Looking for
	// if (diction->entries == NULL) {
	// 	return NULL;
	// } else {
	// 	dictionary->entries->name = name;
	// 	return dictionary->entries;
	// }

	//Wrong: so many errors
// 	int i = 0
// 	while((i < dictionary->count) && (dictionary.entries[i].name != name) {
// 		++i;
// 	}

// 	if(dictionary.entries[i].name == name) {
// 		return dictionary->entries;
// 	} else {
// 		return NULL;
// 	}

// }

	int i = 0;
	while((i < dictionary->count) && icaseCompareString(dictionary->entries[i].name, name) != 0) {
		++i;
	}

	if(i < dictionary->count) {
		return &dictionary->entries[i];
	} else {
		return NULL;
	}




/** Define or change a dictionary entry as a string
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
 //这里的饿问题主要是各种指来指去的指针和严格组织的成员，要会画图，然后不懂的问王称号。
void IMPLEMENT(Dictionary_setStringEntry)(Dictionary * dictionary, const char * name, const char * value)
{
  /*provided_Dictionary_setStringEntry(dictionary, name, value);*/

	//Think too naive!!!
	// DictionaryEntry * entry = Dictionary_getEntry(Dictionary,name);
	// if(entry == NULL) {
	// 	fprintf(stderr, "setSringEntry() Failed!\n", );
	// } else {
	// 	entry->type = STRING_ENTRY;
	// 	entry->value.stringValue = value;
	// }

//always there are so many errors that makes you seem like a Shit!
	// DictionaryEntry * entry = Dictionary_getEntry(dictionary,name);

 //    if(entry == NULL) {
 //    	++dictionary->count;
 //    	dictionary->entries = (Dictionary *)realloc(dictionary->entries, sizeof(DictionaryEntry) * sizeof(dictionary->count));
 //    	if (dictionary->entries == NULL) {
 //    		fprintf(stderr, "Realloc() failed in Dictionary_setStringEntry(). \n" );
 //    		exit(-1);
 //    	}

 //    	dictionary->entries[dictionary->count - 1].type = STRING_ENTRY;
 //    	dictionary->entries[dictionary->count - 1].name = name;
 //    	dictionary->entries[dictionary->count - 1].value.stringValue = duplicateString(value);
 //    } else {
 //    	entry.type = STRING_ENTRY;
 //    	entry.value.stringValue = duplicateString(value);
 //    }



    DictionaryEntry * entry = Dictionary_getEntry(dictionary,name);

    if(entry == NULL) {
    	++dictionary->count;
    	dictionary->entries = (DictionaryEntry *)realloc(dictionary->entries, sizeof(DictionaryEntry) * (size_t)(dictionary->count));
    	if (dictionary->entries == NULL) {
    		fprintf(stderr, "Realloc() failed in Dictionary_setStringEntry(). \n" );
    		exit(-1);
    	} else {
    	dictionary->entries[dictionary->count - 1].type = STRING_ENTRY;
    	dictionary->entries[dictionary->count - 1].name = duplicateString(name);
    	dictionary->entries[dictionary->count - 1].value.stringValue = duplicateString(value);
    	}
    } else {
    	//上面用的是.这里却必须用->，这是因为
    	//.是一般结构体变量访问结构体成员的操作符；而->是结构体指针变量对结构体成员访问的操作符。
    	//所以，一般第一个都是->，紧随其后就是好多.了
    	entry->type = STRING_ENTRY;
    	entry->value.stringValue = duplicateString(value);
    }

}

/** Define or change a dictionary entry as a number
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setNumberEntry)(Dictionary * dictionary, const char * name, double value)
{
  /*provided_Dictionary_setNumberEntry(dictionary, name, value);*/
	DictionaryEntry * entry = Dictionary_getEntry(dictionary, name);

	if (entry == NULL) {
		++dictionary->count;
		dictionary->entries = (DictionaryEntry *)realloc(dictionary->entries, sizeof(DictionaryEntry) * (size_t)(dictionary->count));
		if(dictionary->entries == NULL) {
			fprintf(stderr, "realloc() failed in Dictionary_setNumberEntry(). \n" );
			exit(-1);
		} else {
		dictionary->entries[dictionary->count - 1].type = NUMBER_ENTRY;
		dictionary->entries[dictionary->count - 1].name = duplicateString(name);
    	dictionary->entries[dictionary->count - 1].value.numberValue = value
		}
	} else {	
		entry->type = NUMBER_ENTRY;
		entry->value.numberValue = value;
	}
}

/** Create a new string on the heap which is the result of the formatting of format according to the dictionary content
 * @param dictionary the dictionary
 * @param format the string to format
 * @return a new string created on the heap
 * @warning the user is responsible for freeing the returned string
 */
 //use founction fgets() to read lines ,or will be much more complex
char * IMPLEMENT(Dictionary_format)(Dictionary * dictionary, const char * format)
{
  return provided_Dictionary_format(dictionary, format);
}
