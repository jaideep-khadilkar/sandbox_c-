
cmake_minimum_required(VERSION 3.12)

file( GLOB APP_SOURCES "*.cpp" )
foreach( full_file_path ${APP_SOURCES} )
    get_filename_component(exe_name ${full_file_path} NAME_WE)
    message("add executable ${exe_name}")
    add_executable( ${exe_name} ${full_file_path} )
    # Make sure YourLib is linked to each app
    #target_link_libraries( ${exe_name} YourLib )
endforeach( full_file_path ${APP_SOURCES} )