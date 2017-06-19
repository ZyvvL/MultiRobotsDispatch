# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "test1: 5 messages, 0 services")

set(MSG_I_FLAGS "-Itest1:/home/zyvv/work/Rosprj/catkin/src/test1/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(test1_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_custom_target(_test1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test1" "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" ""
)

get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_custom_target(_test1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test1" "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" ""
)

get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_custom_target(_test1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test1" "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" ""
)

get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_custom_target(_test1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test1" "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" ""
)

get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_custom_target(_test1_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "test1" "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
)
_generate_msg_cpp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
)
_generate_msg_cpp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
)
_generate_msg_cpp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
)
_generate_msg_cpp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
)

### Generating Services

### Generating Module File
_generate_module_cpp(test1
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(test1_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(test1_generate_messages test1_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_dependencies(test1_generate_messages_cpp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_cpp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_cpp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_dependencies(test1_generate_messages_cpp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_dependencies(test1_generate_messages_cpp _test1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test1_gencpp)
add_dependencies(test1_gencpp test1_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test1_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
)
_generate_msg_eus(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
)
_generate_msg_eus(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
)
_generate_msg_eus(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
)
_generate_msg_eus(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
)

### Generating Services

### Generating Module File
_generate_module_eus(test1
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(test1_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(test1_generate_messages test1_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_dependencies(test1_generate_messages_eus _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_eus _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_eus _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_dependencies(test1_generate_messages_eus _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_dependencies(test1_generate_messages_eus _test1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test1_geneus)
add_dependencies(test1_geneus test1_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test1_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
)
_generate_msg_lisp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
)
_generate_msg_lisp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
)
_generate_msg_lisp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
)
_generate_msg_lisp(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
)

### Generating Services

### Generating Module File
_generate_module_lisp(test1
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(test1_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(test1_generate_messages test1_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_dependencies(test1_generate_messages_lisp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_lisp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_lisp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_dependencies(test1_generate_messages_lisp _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_dependencies(test1_generate_messages_lisp _test1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test1_genlisp)
add_dependencies(test1_genlisp test1_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test1_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
)
_generate_msg_nodejs(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
)
_generate_msg_nodejs(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
)
_generate_msg_nodejs(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
)
_generate_msg_nodejs(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
)

### Generating Services

### Generating Module File
_generate_module_nodejs(test1
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(test1_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(test1_generate_messages test1_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_dependencies(test1_generate_messages_nodejs _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_nodejs _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_nodejs _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_dependencies(test1_generate_messages_nodejs _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_dependencies(test1_generate_messages_nodejs _test1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test1_gennodejs)
add_dependencies(test1_gennodejs test1_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test1_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
)
_generate_msg_py(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
)
_generate_msg_py(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
)
_generate_msg_py(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
)
_generate_msg_py(test1
  "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
)

### Generating Services

### Generating Module File
_generate_module_py(test1
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(test1_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(test1_generate_messages test1_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/server.msg" NAME_WE)
add_dependencies(test1_generate_messages_py _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/client_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_py _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_info.msg" NAME_WE)
add_dependencies(test1_generate_messages_py _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/robot_dispatch.msg" NAME_WE)
add_dependencies(test1_generate_messages_py _test1_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/zyvv/work/Rosprj/catkin/src/test1/msg/hello.msg" NAME_WE)
add_dependencies(test1_generate_messages_py _test1_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(test1_genpy)
add_dependencies(test1_genpy test1_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS test1_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/test1
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(test1_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/test1
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(test1_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/test1
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(test1_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/test1
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(test1_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/test1
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(test1_generate_messages_py std_msgs_generate_messages_py)
endif()
