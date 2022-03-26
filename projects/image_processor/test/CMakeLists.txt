add_executable(test
        ../matrix.cpp
        ../BMP.cpp
        ../negative_filter.cpp
        ../grayscale_filter.cpp
        ../crop_filter.cpp
        ../sharpening_filter.cpp
        ../edge_detection_filter.cpp
        ../gaussian_blur_filter.cpp
        ../hexagonal_pixel.cpp
        ../image.cpp
        ../threshold.cpp
        test.cpp)
target_link_libraries(test contrib_catch_main)