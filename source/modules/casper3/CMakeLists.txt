
add_library(casper3 SHARED)
target_sources(casper3 PRIVATE interface.c)

set_target_properties(casper3 PROPERTIES PREFIX "")
set_target_properties(casper3 PROPERTIES OUTPUT_NAME casper3)
set_target_properties(casper3 PROPERTIES SUFFIX .mod)


