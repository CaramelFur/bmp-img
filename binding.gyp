{
    "targets": [
        {
            "target_name": "bmpxx_addon",
            "sources": ["lib/bmp.cpp", "lib/decode.cpp", "lib/encode.cpp", "lib/shared.cpp"],
            "cflags": [
                "-std=c++2a -O3 -Wall -Wextra -pedantic-errors -fexceptions -Wno-template-id-cdtor"
            ],
            "cflags_cc": [
                "-std=c++2a -O3 -Wall -Wextra -pedantic-errors -fexceptions -Wno-template-id-cdtor"
            ],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "CLANG_CXX_LANGUAGE_STANDARD": "c++2a"
            },
            "msvs_settings": {
                "VCCLCompilerTool": { 
                    "ExceptionHandling": 1, 
                    "AdditionalOptions": [ "-std:c++2a" ] 
                }
            }
        }
    ]
}
