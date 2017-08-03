#include "../../common.h"

#include "../parameters.h"
#include "../arginfo.h"

#include "../iterators/php_pq_iterator.h"
#include "../handlers/php_pq_handlers.h"

#include "php_collection_ce.h"
#include "php_pq_ce.h"

#define METHOD(name) PHP_METHOD(PriorityQueue, name)

zend_class_entry *php_ds_pq_ce;

METHOD(__construct)
{
    PARSE_NONE;
}

METHOD(allocate)
{
    PARSE_LONG(capacity);
    ds_pq_allocate(THIS_DS_PQ(), capacity);
}

METHOD(capacity)
{
    PARSE_NONE;
    RETURN_LONG(ds_pq_capacity(THIS_DS_PQ()));
}

METHOD(copy)
{
    PARSE_NONE;
    RETURN_OBJ(php_ds_pq_create_clone(THIS_DS_PQ()));
}

METHOD(push)
{
    PARSE_ZVAL_LONG(value, priority);
    ds_pq_push(THIS_DS_PQ(), value, priority);
}

METHOD(pop)
{
    PARSE_NONE;
    ds_pq_pop(THIS_DS_PQ(), return_value);
}

METHOD(peek)
{
    PARSE_NONE;
    RETURN_ZVAL_COPY(ds_pq_peek(THIS_DS_PQ()));
}

METHOD(isEmpty)
{
    PARSE_NONE;
    RETURN_BOOL(DS_PQ_IS_EMPTY(THIS_DS_PQ()));
}

METHOD(toArray)
{
    PARSE_NONE;
    ds_pq_to_array(THIS_DS_PQ(), return_value);
}

METHOD(count)
{
    PARSE_NONE;
    RETURN_LONG(DS_PQ_SIZE(THIS_DS_PQ()));
}

METHOD(clear)
{
    PARSE_NONE;
    ds_pq_clear(THIS_DS_PQ());
}

METHOD(jsonSerialize)
{
    PARSE_NONE;
    ds_pq_to_array(THIS_DS_PQ(), return_value);
}

PHP_DS_ARRAY_ACCESS_FORWARDING_METHODS(php_ds_pq);

void php_ds_register_pq()
{
    zend_class_entry ce;

    zend_function_entry methods[] = {
        PHP_DS_ME(PriorityQueue, __construct)
        PHP_DS_ME(PriorityQueue, allocate)
        PHP_DS_ME(PriorityQueue, capacity)
        PHP_DS_ME(PriorityQueue, peek)
        PHP_DS_ME(PriorityQueue, pop)
        PHP_DS_ME(PriorityQueue, push)

        PHP_DS_COLLECTION_ME_LIST(PriorityQueue)
        PHP_FE_END
    };

    INIT_CLASS_ENTRY(ce, PHP_DS_NS(PriorityQueue), methods);

    php_ds_pq_ce = zend_register_internal_class(&ce);
    php_ds_pq_ce->ce_flags      |= ZEND_ACC_FINAL;
    php_ds_pq_ce->create_object  = php_ds_pq_create_object;
    php_ds_pq_ce->get_iterator   = php_ds_pq_get_iterator;
    php_ds_pq_ce->serialize      = php_ds_pq_serialize;
    php_ds_pq_ce->unserialize    = php_ds_pq_unserialize;

    zend_declare_class_constant_long(
        php_ds_pq_ce,
        STR_AND_LEN("MIN_CAPACITY"),
        DS_PQ_MIN_CAPACITY
    );

    zend_class_implements(php_ds_pq_ce, 1, php_ds_collection_ce);
    php_ds_register_pq_handlers();
}