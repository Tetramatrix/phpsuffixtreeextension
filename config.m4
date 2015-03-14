PHP_ARG_ENABLE(
	suffixtree, enable SuffixTree class,
	[ --enable-suffixtree Enable support for SuffixTree]
)

if test "$PHP_SUFFIXTREE" = "yes"; then 
	AC_DEFINE(HAVE_SUFFIXTREE,1,[ ]) 
	PHP_NEW_EXTENSION(suffixtree, php_suffixtree.c suffix_tree.c, $ext_shared) 
fi