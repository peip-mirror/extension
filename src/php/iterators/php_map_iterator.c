#include "../../common.h"

#include "../../ds/ds_map.h"
#include "../../ds/ds_htable.h"
#include "../objects/php_map.h"

#include "php_map_iterator.h"
#include "php_htable_iterator.h"

static void php_ds_map_iterator_ctor(zend_object_iterator *iterator)
{
    PHP_DS_INCR_ITERATOR((php_ds_map_t *) &iterator->std);
}

static void php_ds_map_iterator_dtor(zend_object_iterator *iterator)
{
    PHP_DS_DECR_ITERATOR((php_ds_map_t *) &iterator->std);
}

zend_object_iterator *php_ds_map_get_iterator(zend_class_entry *ce, zval *obj, int by_ref)
{
    ds_htable_t *table = Z_DS_MAP_P(obj)->table;
    return php_ds_htable_get_assoc_iterator_ex(ce, obj, by_ref, table, php_ds_map_iterator_ctor, php_ds_map_iterator_dtor);
}
