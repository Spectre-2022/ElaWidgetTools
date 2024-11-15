#@NOTE:Debug模式下生成dll
install(TARGETS ${EXPORT_NAME}
    CONFIGURATIONS Debug
    DESTINATION ${EXPORT_NAME}/Debug/lib/
    PUBLIC_HEADER DESTINATION ${EXPORT_NAME}/Debug/include/ElaWidgetTools/
)
#@NOTE:Release模式下生成dll
install(TARGETS ${EXPORT_NAME}
    CONFIGURATIONS Release
    DESTINATION ${EXPORT_NAME}/Release/lib/
    PUBLIC_HEADER DESTINATION ${EXPORT_NAME}/Release/include/ElaWidgetTools/
)


#@NOTE:Debug模式下生成PDB文件
install(FILES $<TARGET_PDB_FILE:${EXPORT_NAME}>
    CONFIGURATIONS Debug
    DESTINATION ${EXPORT_NAME}/Debug/lib OPTIONAL
)
#@NOTE:Release模式下生成PDB文件
install(FILES $<TARGET_PDB_FILE:${EXPORT_NAME}>
    CONFIGURATIONS Release
    DESTINATION ${EXPORT_NAME}/Release/lib OPTIONAL
)
#@NOTE:导出所有header
install(FILES ${EXPORT_HEADERS} DESTINATION ${EXPORT_NAME}/Release/include/ElaWidgetTools/)
