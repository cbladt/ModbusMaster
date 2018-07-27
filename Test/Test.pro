include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG *= -O0
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS += -Werror -Wvla -Wall

INCLUDEPATH += $$PWD/../ModbusMaster

HEADERS += \
    ../ModbusMaster/FrameLayer.hpp \
    ../ModbusMaster/ModbusMaster.hpp \
    ../ModbusMaster/IDataLink.hpp \
    ../ModbusMaster/FrameRouter.hpp \
    ../ModbusMaster/RequestModel.hpp \
    ../ModbusMaster/Strategies/ReadInputStratety.hpp \
    ../ModbusMaster/Framework/TransmitBase.hpp \    
    ../ModbusMaster/Framework/IReceive.hpp \
    ../ModbusMaster/Framework/FunctionCode.hpp \
    ../ModbusMaster/Framework/Parameter.hpp \
    ../ModbusMaster/Framework/ParameterType.hpp \
    ../ModbusMaster/Framework/Frame/Frame.hpp

SOURCES += \
    main.cpp \
    Test_Framework_Parameter.cpp \
    ../ModbusMaster/ModbusMaster.cpp \
    ../ModbusMaster/FrameRouter.cpp \
    ../ModbusMaster/RequestModel.cpp \
    ../ModbusMaster/FrameLayer.cpp \
    ../ModbusMaster/Strategies/ReadInputStratety.cpp \    
    ../ModbusMaster/Framework/Parameter.cpp \
    Test_Framework_TransmitReceive.cpp \
    ../ModbusMaster/Framework/Frame/Frame.cpp \
    Test_FrameRouter.cpp
