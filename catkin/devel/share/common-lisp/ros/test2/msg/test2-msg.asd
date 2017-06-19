
(cl:in-package :asdf)

(defsystem "test2-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "hello" :depends-on ("_package_hello"))
    (:file "_package_hello" :depends-on ("_package"))
    (:file "robot_dispatch" :depends-on ("_package_robot_dispatch"))
    (:file "_package_robot_dispatch" :depends-on ("_package"))
    (:file "robot_info" :depends-on ("_package_robot_info"))
    (:file "_package_robot_info" :depends-on ("_package"))
    (:file "server" :depends-on ("_package_server"))
    (:file "_package_server" :depends-on ("_package"))
  ))