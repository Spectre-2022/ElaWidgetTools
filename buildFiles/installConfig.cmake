if(NOT DEFINED ${RunWithAMS})
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../install/)
endif()
#@NOTE:Debug模式下生成PDB文件
install(FILES $<TARGET_PDB_FILE:${lib_alias_name}>
    CONFIGURATIONS Debug
    DESTINATION lib/${lib_alias_name}/Debug/lib OPTIONAL
)
#@NOTE:Release模式下生成PDB文件
install(FILES $<TARGET_PDB_FILE:${lib_alias_name}>
    CONFIGURATIONS Release
    DESTINATION lib/${lib_alias_name}/Release/lib OPTIONAL
)
#@NOTE:Debug模式下生成dll
install(TARGETS ${lib_alias_name}
    CONFIGURATIONS Debug
    DESTINATION lib/${lib_alias_name}/Debug/lib/
    PUBLIC_HEADER DESTINATION lib/${lib_alias_name}/Debug/include/
)
#@NOTE:Release模式下生成dll
install(TARGETS ${lib_alias_name}
    CONFIGURATIONS Release
    DESTINATION lib/${lib_alias_name}/Release/lib/
    PUBLIC_HEADER DESTINATION lib/${lib_alias_name}/Release/include/
)
