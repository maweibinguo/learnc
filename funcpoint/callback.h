/**
 * single node
 */
typedef struct callback_node_tag {
    int value;
    struct callback_node_tag * link;
} callback_node;

/**
 * search function
 */
int const search_node(  void const * root_pointer,
                        void const * search_value, 
                        int const (*compare_callback)(void const * pointer, void const * value) );
 
/**
 * compare callback for node
 */
int const callback_for_node(void const * now_value, void const * search_value);

/**
 * compare callback for string
 */
int const callback_for_string(void const * now_value, void const * search_value);
