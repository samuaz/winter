function(winter_create_sql_migration dir)
    # Create empty output file
    set(output ${CMAKE_BINARY_DIR}/generated/winter_db_migrations_sql.h)
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*.sql)
    # Iterate through input files
    file(APPEND ${output} "#include <vector>\n")
    file(APPEND ${output} "#include <wintercpp/data/sql/migration/winter_data_migration.h>\n")
    file(APPEND ${output} "namespace winter::data::sql_impl {\n")
    file(APPEND ${output} "std::vector<winter::data::sql_impl::Migration> winter_db_migrations(){\n")
    file(APPEND ${output} "std::vector<winter::data::sql_impl::Migration> migrations;\n")
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "migrations.emplace_back(std::string(\"${filename}\"), std::string({${filedata}}));\n")
    endforeach()
    file(APPEND ${output} "return migrations;\n")
    file(APPEND ${output} "}\n")
    file(APPEND ${output} "}\n")
    include_directories(${CMAKE_BINARY_DIR}/generated/)
endfunction()