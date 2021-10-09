function(format_with_astyle file)
    find_program(ASTYLE "astyle")
if(ASTYLE)
    MESSAGE("${ASTYLE} --options=astyle.cfg ${file}")
    execute_process(
          COMMAND ${ASTYLE} --options=astyle.cfg ${file}
          WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
          RESULT_VARIABLE astyle_format_result
          OUTPUT_VARIABLE astyle_format_variable
          )
    MESSAGE(STATUS "ASTYLE_FORMAT_CMD_ERROR:" ${astyle_format_result})
    MESSAGE(STATUS "ASTYLE_FORMAT_CMD_OUTPUT:" ${astyle_format_variable})
endif()
endfunction()

function(format_with_astyle_by_target target)
  get_target_property(target_sources ${target} SOURCES)
  foreach (file ${target_sources})
    format_with_astyle(${target} ${file})
  endforeach()
endfunction()

function(format_with_astyle_by_sources target_sources)
  foreach (file ${target_sources})
    format_with_astyle(${file})
  endforeach()
endfunction()