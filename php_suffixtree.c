#include "php_suffixtree.h"
#include "php_suffixtree.h"

zend_class_entry* g_ClassEntry;
zend_object_handlers g_ClassHandlers;

static
	ZEND_BEGIN_ARG_INFO(php_string_arginfo, 0)
        ZEND_ARG_INFO(0, "string")
    ZEND_END_ARG_INFO()

PHP_METHOD(SuffixTree, __construct)
{
	char *str;
	int str_len;

	if (
		zend_parse_parameters(
			ZEND_NUM_ARGS() TSRMLS_CC,
			"s",
			&str,
			&str_len
		) == FAILURE
	) {
		WRONG_PARAM_COUNT;
	}

	php_printf("Hello %s%d ", str,str_len);
	
	SuffixTree_t* ExThis = (SuffixTree_t*) zend_object_store_get_object(getThis() TSRMLS_CC);
	
	ExThis->tree = ST_CreateTree(str, str_len);
}

PHP_METHOD(SuffixTree, find)
{
	char *str;
	int str_len;

	if (
		zend_parse_parameters(
			ZEND_NUM_ARGS() TSRMLS_CC,
			"s",
			&str,
			&str_len
		) == FAILURE
	) {
		WRONG_PARAM_COUNT;
	}

	SuffixTree_t* ExThis = (SuffixTree_t*) zend_object_store_get_object(getThis() TSRMLS_CC);

	DBL_WORD pos;

	pos = ST_FindSubstring(ExThis->tree, str, str_len);

	ZVAL_LONG(return_value, pos);

	return;
}

PHP_METHOD(SuffixTree, print)
{
	SuffixTree_t* ExThis = (SuffixTree_t*) zend_object_store_get_object(getThis() TSRMLS_CC);

	ST_PrintTree(ExThis->tree);
}

zend_function_entry class_methods[] = {
	PHP_ME(SuffixTree, __construct, php_string_arginfo, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(SuffixTree, find, php_string_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(SuffixTree, print, NULL, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(suffixtree)
{
	zend_class_entry stubClassEntry;

	INIT_CLASS_ENTRY(stubClassEntry, "SuffixTree", class_methods);

	stubClassEntry.create_object = SuffixTree_New;

	g_ClassEntry = zend_register_internal_class(&stubClassEntry TSRMLS_CC);

	memcpy(&g_ClassHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	return SUCCESS;
}

zend_object_value SuffixTree_New(zend_class_entry *class_type TSRMLS_DC)
{
	SuffixTree_t *object;
	zend_object_value retval;
	zval tmp;

	object = emalloc(sizeof(SuffixTree_t));

	zend_object_std_init(&object->classInstance, class_type TSRMLS_CC);

	zend_hash_copy(
		object->classInstance.properties,
		&class_type->default_properties,
		(copy_ctor_func_t) zval_add_ref,
		(void *) &tmp,
		sizeof(zval *)
	);

	retval.handle =
		zend_objects_store_put(
			object,
			(zend_objects_store_dtor_t) zend_objects_destroy_object,
			(zend_objects_free_object_storage_t)
			SuffixTree_destructor,
			NULL TSRMLS_CC
		);

	retval.handlers = &((g_ClassHandlers));

	return retval;
}

void SuffixTree_destructor(void *object TSRMLS_DC)
{
	SuffixTree_t *object_ = (SuffixTree_t *)object;

	ST_DeleteTree(object_->tree);

	zend_object_std_dtor(&object_->classInstance TSRMLS_CC);

	efree(object);
}

PHP_MINFO_FUNCTION(suffixtree)
{
	php_info_print_table_start();
	php_info_print_table_header(2, EXT_NAME, "loaded");
	php_info_print_table_row(2, "Version", EXT_VERSION);
	php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}


zend_module_entry suffixtree_module_entry =
{
	STANDARD_MODULE_HEADER_EX,
    NULL,
	NULL,
    "SuffixTree",
    NULL,
    PHP_MINIT(suffixtree),
    NULL,
    NULL,
    NULL,
    PHP_MINFO(suffixtree),
    EXT_VERSION,
    NULL,
    NULL,
    NULL,
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};

ZEND_GET_MODULE(suffixtree)
