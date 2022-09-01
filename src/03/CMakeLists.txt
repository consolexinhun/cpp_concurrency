set(CURRENT ${CMAKE_CURRENT_SOURCE_DIR})

# message(${CURRENT})

# file(GLOB_RECURSE mains RELATIVE ${CURRENT} ${CURRENT}/*.cpp)
# FOREACH (mainfile IN LISTS mains)
#     get_filename_component(mainname ${mainfile} NAME_WE)
#     add_executable(${mainname} ${mainfile})
#     target_link_libraries(${mainname} pthread)
# ENDFOREACH()

aux_source_directory(${CURRENT} CPP_LIST)
FOREACH (subcpp ${CPP_LIST})
    GET_FILENAME_COMPONENT(mainname ${subcpp} NAME_WE)
    ADD_EXECUTABLE(${mainname} ${subcpp})
    TARGET_LINK_LIBRARIES(${mainname} pthread)
ENDFOREACH()


# add_executable(hello ${CURRENT}/hello.cpp)
# target_link_libraries(hello pthread) 