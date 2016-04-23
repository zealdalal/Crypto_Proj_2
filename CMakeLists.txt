cmake_minimum_required(VERSION 3.5)
project(Crypto_Project_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(./Dropbox-C-master/crypto CRYPTO_LIB_DIR)
include_directories( ./Dropbox-C-master/crypto )
add_library(Cryptopp ${CRYPTO_LIB_DIR})

aux_source_directory(./Dropbox-C-master/Dropbox/src DROPBOX_LIB_DIR)
include_directories( ./Dropbox-C-master/Dropbox/include ./Dropbox-C-master/jansson-2.7/src ./Dropbox-C-master/liboauth-1.0.3/src ./Dropbox-C-master/memStream/include)
add_library(Dropbox ${DROPBOX_LIB_DIR})

set(SOURCE_FILES main.cpp Encrypt_and_Upload_to_Dropbox.cpp Decrypt_and_Download_from_Dropbox.cpp)
add_executable(Crypto_Project_2 ${SOURCE_FILES})
target_link_libraries(Crypto_Project_2 Cryptopp Dropbox)