/*
 * balde-utils: A general purpose utility library for C.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <balde-utils/trie.h>


b_trie_t*
b_trie_new(void (*free_func)(void *ptr))
{
    b_trie_t *trie = malloc(sizeof(b_trie_t));
    trie->root = NULL;
    trie->free_func = free_func;
    return trie;
}


static void
b_trie_free_node(b_trie_t *trie, b_trie_node_t *node)
{
    if (node == NULL)
        return;
    if (node->data != NULL)
        trie->free_func(node->data);
    b_trie_free_node(trie, node->next);
    b_trie_free_node(trie, node->child);
    free(node);
}


void
b_trie_free(b_trie_t *trie)
{
    b_trie_free_node(trie, trie->root);
    free(trie);
}


void
b_trie_insert(b_trie_t *trie, const char *key, void *data)
{
    if (data == NULL || key == NULL)
        return;

    b_trie_node_t *parent = NULL;
    b_trie_node_t *previous;
    b_trie_node_t *current;
    b_trie_node_t *tmp;

    while (1) {

        if (trie->root == NULL || (parent != NULL && parent->child == NULL)) {
            current = malloc(sizeof(b_trie_node_t));
            current->key = *key;
            current->data = NULL;
            current->next = NULL;
            current->child = NULL;
            if (parent == NULL)
                trie->root = current;
            else
                parent->child = current;
            parent = current;
            goto clean;
        }

        tmp = parent == NULL ? trie->root : parent->child;
        previous = NULL;

        while (tmp != NULL && tmp->key != *key) {
            previous = tmp;
            tmp = tmp->next;
        }

        if (previous == NULL) {
            parent = tmp;
            goto clean;
        }

        current = malloc(sizeof(b_trie_node_t));
        current->key = *key;
        current->data = NULL;
        current->next = NULL;
        current->child = NULL;
        previous->next = current;
        parent = current;

clean:
        if (*key == '\0') {
            parent->data = data;
            break;
        }
        key++;
    }
}
