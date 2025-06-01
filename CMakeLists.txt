cmake_minimum_required(VERSION 3.5)


project (particalDecayAnalysis LANGUAGES CXX)


# 以下两行为需要用root的时候添加，下面link lib同理
find_package(ROOT REQUIRED COMPONENTS Core Tree RIO Net Hist MathCore Graf)
include(${ROOT_USE_FILE})
# end

set(SOURCES
    main.cpp
    src/BaseDrawGraph.cpp
    src/BaseDoubleParticalChannelManager.cpp
    src/JpsiParticleAnalysis.cpp
    src/PPbCollision8_16Config.cpp
    src/PPbCollision8_16ProtonPositive.cpp
    src/BaseCSVManager.cpp
)

add_executable(particalDecayAnalysis ${SOURCES})

target_include_directories(particalDecayAnalysis
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
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
)
# end