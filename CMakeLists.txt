cmake_minimum_required(VERSION 3.8)
project(HW4Monopoly)

set(CMAKE_CXX_STANDARD 14)
set(GPP_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")

set(SOURCE_FILES main.cpp Board.cpp Board.h CSVReader.cpp CSVReader.h DiceRoller.cpp DiceRoller.h GameState.cpp GameState.h Go.cpp Go.h MonopolyUtility.cpp MonopolyUtility.h Move.cpp Move.h Player.cpp Player.h Property.cpp Property.h PropertyManager.cpp PropertyManager.h PropertySet.cpp PropertySet.h Rules.cpp Rules.h Space.cpp Space.h Jail.cpp Jail.h FreeParking.cpp FreeParking.h PayToBank.cpp PayToBank.h GoToJail.cpp GoToJail.h Whiteboard.cpp Whiteboard.h)
add_executable(monopoly ${SOURCE_FILES})