// 这里很奇怪，如果tag的name同typedef的名字一致的话，最后用的还是tag
typedef struct single_node_tag {
    int value;
    struct single_node_tag * link;
} single_node;

single_node * insert_node(single_node ** direct_root, int insert_value);

typedef struct double_link_node_tag {
    int value;
    struct double_link_node * next;
    struct double_link_node * previous;
} double_link_node;

