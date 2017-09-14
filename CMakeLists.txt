link_directories(${LIB_DIR})

message(STATUS "LIB_DIR: " ${LIB_DIR})

link_libraries(tgcreator
                util
                sensors
                core    
                terrain 
                tgOpenGLSupport
		yaml-cpp
		TensegrityModel)

#   add_executable(TModelTester
#     #threeBarModel.cpp
#     LengthControllerYAML.cpp
#     YAMLSimulator.cpp
# ) 

  add_executable(cubeSim
    dataCollection.cpp
    cubeSim.cpp
) 

# UN-COMMENT these lines for 6.1
#add_executable(App3BarYAML
#    LengthControllerYAML.cpp
#    App3BarYAML.cpp
#) 
