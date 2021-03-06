#ifndef DS_HTABLE_ITERATOR_H
#define DS_HTABLE_ITERATOR_H

#include "php.h"
#include "../../ds/ds_htable.h"

typedef void (*ds_htable_iterator_ctor)(zend_object_iterator *iterator);
typedef void (*ds_htable_iterator_dtor)(zend_object_iterator *iterator);

typedef struct ds_htable_iterator {

    zend_object_iterator     intern;
    uint32_t                 position;
    ds_htable_bucket_t      *bucket;
    ds_htable_t             *table;
    zend_object             *obj; // TODO this already exists on intern?
    ds_htable_iterator_ctor  ctor;
    ds_htable_iterator_dtor  dtor;

} ds_htable_iterator_t;

zend_object_iterator *php_ds_htable_get_value_iterator_ex(zend_class_entry *ce, zval *obj, int by_ref, ds_htable_t *h, ds_htable_iterator_ctor ctor, ds_htable_iterator_dtor dtor);
zend_object_iterator *php_ds_htable_get_key_iterator_ex  (zend_class_entry *ce, zval *obj, int by_ref, ds_htable_t *h, ds_htable_iterator_ctor ctor, ds_htable_iterator_dtor dtor);
zend_object_iterator *php_ds_htable_get_pair_iterator_ex (zend_class_entry *ce, zval *obj, int by_ref, ds_htable_t *h, ds_htable_iterator_ctor ctor, ds_htable_iterator_dtor dtor);
zend_object_iterator *php_ds_htable_get_assoc_iterator_ex(zend_class_entry *ce, zval *obj, int by_ref, ds_htable_t *h, ds_htable_iterator_ctor ctor, ds_htable_iterator_dtor dtor);

#endif
