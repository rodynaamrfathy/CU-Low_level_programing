#define size 10 

/**
 * struct hash_node_s - Node of a hash table
 *
 * @key: The key, string
 * The key is unique in the HashTable
 * @value: The value corresponding to a key
 * @next: A pointer to the next node of the List
 */
typedef struct hash_node_s
{
     char *key;
     char *value;
     struct hash_node_s *next;
} hash_node_t;

/**
 * struct hash_table_s - Hash table data structure
 *
 * @size: The size of the array
 * @array: An array of size @size
 * Each cell of this array is a pointer to the first node of a linked list,
 * because we want our HashTable to use a Chaining collision handling
 */
typedef struct hash_table_s
{
     unsigned long int size;
     hash_node_t **array;
} hash_table_t;


/**
 * hash_table_create - Creates a hash table.
 * @size: The size of the array.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new hash table.
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *ht;
	unsigned long int i;

	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
    // alocate memory for the array of pointers to hash_node_t nodes
	ht->array = malloc(sizeof(hash_node_t *) * size);
	if (ht->array == NULL)
		return (NULL);
    // set each pointer in the array to null
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}


/**
 * hash_djb2 - Hash function implementing the djb2 algorithm.
 * @str: The string to hash.
 *
 * Return: The calculated hash.
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
    /*hash << 5: This left-shifts the value of hash by 5 bits. 
    This operation is equivalent to multiplying hash by 32 
    (since shifting left by 5 bits is the same as multiplying by 2^5).*/
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash);
}



/**
 * key_index - Get the index at which a key/value
 *      pair should be stored in array of a hash table.
 * @key: The key to get the index of.
 * @size: The size of the array of the hash table.
 *
 * Return: The index of the key.
 * Description: Uses the djb2 algorithm.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size){
    return (hash_djb2(key) % size);
}

/**
 * hash_table_set - Add or update an element in a hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    char *value_copy;
    unsigned long int index, i; 

    if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	value_copy = strdup(value);
    if (value_copy == NULL)
		return (0);

    index = key_index((const unsigned char *)key, ht->size);
    // Create a new node and insert it into the hash table
    for (i = index; ht->array[i]; i++)
	{
		if (strcmp(ht->array[i]->key, key) == 0)
		{
            // Update value and free old value
			free(ht->array[i]->value);
			ht->array[i]->value = value_copy;
			return (1);
		}
	}
    // If we reached this point, then there is no existing entry for this key
    // Create a new node and insert it into the hash table
    hash_node_t *newnode = malloc(sizeof(hash_node_t));
    if (newnode == NULL)
    {
        free(value_copy);
        return (0);
    }

    newnode->key = strdup(key);
    if (newnode->key == NULL)
    {
        free(newnode);
        return (0);
    }

    newnode->value = value_copy;
    // if the index already had a value the newnode will point to it
    //  else  newnode->next = NULL
    newnode->next = ht->array[index];
    // in all cases array index will point to newnode
    ht->array[index] = newnode;

    return (1);
}

/**
 * hash_table_get - Retrieve the value associated with
 *                  a key in a hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to get the value of.
 *
 * Return: If the key cannot be matched - NULL.
 *         Otherwise - the value associated with key in ht.
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
    hash_node_t *curr;
    unsigned long int index;

    if(ht == NULL || key == NULL || *key == '\0')
        return (NULL);

    index = key_index((const unsigned char *)key, ht->size);
    if (index >= ht->size)
		return (NULL);

    curr = ht->array[index];
    while(curr != NULL)
    {
        if(strcmp(curr->key, key) == 0)
            return (curr->value);
        curr = curr->next;
    }

    return (NULL)
}

/**
 * hash_table_print - Prints a hash table.
 * @ht: A pointer to the hash table to print.
 *
 * Description: Key/value pairs are printed in the order
 *              they appear in the array of the hash table.
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *node;
	unsigned long int i;
	unsigned char comma_flag = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (i = 0; i < ht->size; i++)
	{
		if (ht->array[i] != NULL)
		{
			if (comma_flag == 1)
				printf(", ");

			node = ht->array[i];
			while (node != NULL)
			{
				printf("'%s': '%s'", node->key, node->value);
				node = node->next;
				if (node != NULL)
					printf(", ");
			}
			comma_flag = 1;
		}
	}
	printf("}\n");
}

void hash_node_delete(hash_node_s *node)
{
    free(node->key);
    free(node->value);
    free(node->next);
    free(node);
}

/**
 * hash_table_delete - Deletes a hash table.
 * @ht: A pointer to a hash table.
 */
void hash_table_delete(hash_table_t *ht)
{
    hash_node_t *node, *tmp;
	unsigned long int i;

	if (ht == NULL)
		return;

    for(i = 0; i < size; i++){
        node = ht->array[i];
        while(node != NULL)
        {
            tmp = node->next;
            hash_node_delete(node);
            node = tmp;
        }
    }
    free(ht->array);
    free(ht);
}


/*
backup function
unsigned long hash_function(char* str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % size;
}*/


/**
 * main - check the code
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
    hash_table_t *ht;

    ht = hash_table_create(1024);
    hash_table_print(ht);
    hash_table_set(ht, "c", "fun");
    hash_table_set(ht, "python", "awesome");
    hash_table_set(ht, "Bob", "and Kris love asm");
    hash_table_set(ht, "N", "queens");
    hash_table_set(ht, "Asterix", "Obelix");
    hash_table_set(ht, "Betty", "Cool");
    hash_table_set(ht, "98", "Battery Street");
    hash_table_print(ht);
    return (0);
}