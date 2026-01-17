#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define CHUNK_LENGTH 255

#define CHUNK_SIZE CHUNK_LENGTH*CHUNK_LENGTH

typedef void (*FreeFunc)(void*);

typedef struct Entry {
	char *key;
	void *value;
	FreeFunc free_val;
	struct Entry *next;
} Entry;

typedef struct {
	Entry *buckets[TABLE_SIZE];
} Dict;

typedef struct Entity {
	char *name;
} Entity;

Dict* create_dict(void);
void dict_set(Dict *dict, const char *key, void *value, FreeFunc free_val);
void* dict_get(Dict *dict, const char *key);
void free_dict(Dict *dict);
unsigned int hash(const char* key);
void free_entity(void *entity);

unsigned int hash(const char* key) {
	unsigned int hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + 5) + (unsigned int)c;
	return hash % TABLE_SIZE;
}

Dict* create_dict(void) {
    Dict *dict = calloc(1, sizeof(Dict));
    return dict;
}

void dict_set(Dict *dict, const char *key, void *value, FreeFunc free_val) {
	unsigned int slot = hash(key);
	Entry *entry = dict->buckets[slot];

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
            if (entry->free_val)
				entry->free_val(entry->value);
            entry->value = value;
			entry->free_val = free_val;
            return;
        }
        entry = entry->next;
	}

	Entry *new_entry = calloc(1, sizeof(Entry));
	new_entry->key = strdup(key);
    new_entry->value = value;
	new_entry->free_val = free_val;
    new_entry->next = dict->buckets[slot];
    dict->buckets[slot] = new_entry;
}

void* dict_get(Dict *dict, const char *key) {
	unsigned int slot = hash(key);
    Entry *entry = dict->buckets[slot];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL; // Key not found
}

void free_dict(Dict *dict) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = dict->buckets[i];
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            if (temp->free_val)
					temp->free_val(temp->value);
            free(temp);
        }
    }
    free(dict);
}

void free_entity(void *entity) {
	free((Entity*)entity);
}

int main(void) {
    Dict *entities = create_dict();
	
	Entity *slug = calloc(1, sizeof(Entity));
	slug->name = "Slug Guy";
	dict_set(entities, "(1, 1)", slug, free_entity);
	
	Entity *e = dict_get(entities, "(1, 2)");
	if (e != NULL) {
		printf("%s\n", e->name);
	} else {
		printf("Entity not found!\n");
	}

	char *chunk = malloc(CHUNK_SIZE);
	memset(chunk, '0', CHUNK_SIZE);
	chunk[0] = '1';
	printf("%c\n", chunk[0]);

    free_dict(entities);
    return 0;
}
