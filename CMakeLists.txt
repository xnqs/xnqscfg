cmake_minimum_required(VERSION 3.10)

project("xnqscfg")
add_library("xnqscfg" MODULE "src/xnqscfg.cxx" "src/lexer.cxx")
install(TARGETS xnqscfg DESTINATION ${CMAKE_INSTALL_PREFIX}/lib PERMISSIONS ${permissions})
install(FILES "src/xnqscfg.hxx" "src/lexer.hxx" DESTINATION ${CMAKE_INSTALL_PREFIX}/include/xnqscfg PERMISSIONS ${permissions})
