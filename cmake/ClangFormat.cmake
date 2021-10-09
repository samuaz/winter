function(format_with_clang file)
    find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    MESSAGE("${CLANG_FORMAT} -i -style=file ${file}")
    execute_process(
          COMMAND ${CLANG_FORMAT} -i -style=file ${file}
          WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
          RESULT_VARIABLE clang_format_result
          OUTPUT_VARIABLE clang_format_variable
          )
    MESSAGE(STATUS "CLANG_FORMAT_CMD_ERROR:" ${clang_format_result})
    MESSAGE(STATUS "CLANG_FORMAT_CMD_OUTPUT:" ${clang_format_variable})
endif()
endfunction()

function(format_with_clang_by_target target)
  get_target_property(target_sources ${target} SOURCES)
  foreach (file ${target_sources})
    format_with_clang(${target} ${file})
  endforeach()
endfunction()

function(format_with_clang_by_sources target_sources)
  foreach (file ${target_sources})
    format_with_clang(${file})
  endforeach()
endfunction()

