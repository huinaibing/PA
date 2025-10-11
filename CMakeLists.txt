cmake_minimum_required(VERSION 3.5)


project (particalDecayAnalysis LANGUAGES CXX)


# 以下两行为需要用root的时候添加，下面link lib同理
find_package(ROOT REQUIRED COMPONENTS Core Tree RIO Net Hist MathCore Graf)
include(${ROOT_USE_FILE})
# end

# 1. 查找 MySQL 头文件目录（包含 mysql/mysql.h）
find_path(MYSQL_INCLUDE_DIR
    NAMES mysql/mysql.h
    PATHS /usr/include/mysql /usr/local/include/mysql  # 默认安装路径
)

# 2. 查找 MySQL 链接库（libmysqlclient.so）
find_library(MYSQL_LIBRARY
    NAMES mysqlclient
    PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib  # Ubuntu 下的默认库路径
)

# 3. 添加头文件路径（让编译器能找到 mysql.h）
include_directories(${MYSQL_INCLUDE_DIR})

# 检查是否找到 MySQL 头文件和库
if(NOT MYSQL_INCLUDE_DIR)
    message(FATAL_ERROR "MySQL 头文件未找到，请安装 libmysqlclient-dev")
endif()
if(NOT MYSQL_LIBRARY)
    message(FATAL_ERROR "MySQL 库文件未找到，请安装 libmysqlclient-dev")
endif()

set(SOURCES
    main.cpp
    src/BaseDrawGraph.cpp
    src/BaseDoubleParticalChannelManager.cpp
    src/DoubleParticleReconstructManager.cpp
    src/BaseCSVManager.cpp
    src/DrawTH2DHelper.cpp
    src/DrawTGraphErrorHelper.cpp
    src/DataBaseManager.cpp
    src/HitsFOCManager.cpp
    src/AliRootHitsFITManager.cpp
    src/AliRootHitsFOCALManager.cpp
    src/AliRootFOCALEventLooper.cpp
    instance/MixEvents.cpp
    config_class/PPbCollision8_16ProtonPositive.cpp
    config_class/PPbCollision8_16Config.cpp
)

add_executable(particalDecayAnalysis ${SOURCES})

target_include_directories(particalDecayAnalysis
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/instance_header
        ${PROJECT_SOURCE_DIR}/config_header
        ${PROJECT_SOURCE_DIR}/external
)

# 需要root的时候添加
target_link_libraries(particalDecayAnalysis
    PRIVATE
        ROOT::Core
        ROOT::Tree
        ROOT::RIO
        ROOT::Net
        ROOT::Hist
        ROOT::MathCore
        ROOT::Graf
        ROOT::Gpad
        ${MYSQL_LIBRARY}
)
# end