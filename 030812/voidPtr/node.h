#ifndef NODE_H
#define NODE_H

struct node
{

    void *data;
    node();
    ~node();

    node& operator=(void *dptr);

};

#endif // NODE_H
