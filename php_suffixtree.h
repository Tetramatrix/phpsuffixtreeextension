#ifndef PHP_SUFFIXTREE_EXT
#define PHP_SUFFIXTREE_EXT

#include "php.h"
#include "zend_API.h"
#include "php_ini.h"
#include "suffix_tree.h"

#define EXT_VERSION         "0.0.1"
#define EXT_NAME            "SuffixTree"
#define EXT_VERSION_STRING 	(EXT_NAME EXT_VERSION " (PHP " PHP_VERSION ")")
#define EXT_AUTHOR			"Denis M. Gabaidulin"
#define EXT_URL				"http://boo"
#define EXT_COPYRIGHT		"Sherman (c)"

typedef struct _SuffixTree_t {
	zend_object classInstance;
	int version;
	SUFFIX_TREE* tree;
} SuffixTree_t;


zend_object_value SuffixTree_New(zend_class_entry *class_type TSRMLS_DC);
void SuffixTree_destructor(void *object TSRMLS_DC);

#endif//PHP_SUFFIXTREE_EXT
