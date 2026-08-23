#include "data.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct data_s 
{
    char           label[DATA_LABEL_LEN]; /**< Label of the data. */
    data_value_t   val;                   /**< Value of the data. */
} data_t;

/**
 * \brief A node of the data linked list.
 */
typedef struct data_node_s
{
    data_t              data; /**< Data of the node. */
    struct data_node_s *prev; /**< Previous data node in the linked list. */
    struct data_node_s *next; /**< Next data node in the linked list. */
} data_node_t;

/**
 * \brief Linked list containing the pointer to the main nodes & meta information about the list.
 */
typedef struct data_list_s
{
    data_node_t       *first; /**< First data node of the list. */
    data_node_t       *last;  /**< Last data node of the list. */
    size_t             count; /**< Count of nodes in the list. */
} data_list_t;


typedef struct data_group_s
{
    char label[DATA_GROUP_LABEL_LEN];
} data_group_t;

/**
 * \brief A node of the data group linked list.
 */
typedef struct data_group_node_s
{
    data_group_t              group; /**< Group information. */
    data_list_t               nodes; /**< Linked list of the data in the group. */
    struct data_group_node_s *prev;  /**< Previous group node in the linked list. */
    struct data_group_node_s *next;  /**< Next group node in the linked list. */
} data_group_node_t;

/**
 * \brief Linked list containing the pointer to the main nodes & meta information about the list.
 */
typedef struct data_group_list_s
{
    data_group_node_t *first; /**< First node of the list. */
    data_group_node_t *last;  /**< Last node of the list. */
    size_t             count; /**< Count of nodes in the list. */
} data_group_list_t;



static data_group_list_t s_group_list; /**< Storage of all data in the libdata*/
static bool s_init = false;

/**
 * \brief Get a const pointer on the data group node. 
 */
data_ret_t _get_const_data_group_node(const char *group_label, const data_group_t **group)
{
    assert( group != NULL );

    *group = NULL;
    data_group_node_t *g = s_group_list.first;

    while( g )
    {
        data_group_node_t *g_next = g->next;

        if( strcmp(g->group.label, group_label) == 0 )
        {
            *group = &g->group;
            return DATA_RET_OK;
        }
        g = g_next;
    }

    return DATA_RET_GROUP_NOT_FOUND;
}

/**
 * \brief Get a const pointer on the data node. 
 */
data_ret_t _get_const_data_node(const char *group_label, const char *label, const data_t **data)
{
    assert( data != NULL );

    *data = NULL;
    data_group_node_t *g = s_group_list.first;

    while ( g )
    {
        data_group_node_t *g_next = g->next;

        if ( strcmp(g->group.label, group_label) == 0 )
        {
            data_node_t *d = g->nodes.first;

            while( d )
            {
                data_node_t *d_next = d->next;
                
                if ( strcmp(d->data.label, label) == 0)
                {
                    *data = &d->data;
                    return DATA_RET_OK;
                }
            }
            return DATA_RET_DATA_NOT_FOUND;
        }
        g = g_next;
    }
    return DATA_RET_GROUP_NOT_FOUND;
}


data_ret_t lib_data_init()
{
    s_group_list.count = 0;
    s_group_list.first = NULL;
    s_group_list.last  = NULL;

    s_init = true;
    
    return DATA_RET_OK;
}

data_ret_t lib_data_destroy()
{
    data_group_node_t *g      = s_group_list.first;
    data_group_node_t *g_next = (g != NULL ? g->next : NULL);
    while ( g )
    {
        free(g);
        g->nodes.count      = 0;
        data_node_t *d      = g->nodes.first;

        while ( d )
        {
            data_node_t *d_next = d->next;
            free(d);
            d = d_next;
        }

        g = g_next;
    }

    s_group_list.count = 0;
    s_group_list.first = NULL;
    s_group_list.last  = NULL;
    
    s_init = false;

    return DATA_RET_OK;
}

data_ret_t add_group(const char *group_label)
{
    assert( group_label != NULL );

    return DATA_RET_OK;
}

data_ret_t add_data_to_group(char *group_label, const char *label, data_value_t *val)
{
    assert( group_label != NULL );
    assert( label != NULL );

    return DATA_RET_OK;
}

size_t get_data_group_count()
{
    return s_group_list.count;
}

size_t get_data_count_in_group(const char *group_label)
{
    
}

bool is_init()
{
    return false;
}
