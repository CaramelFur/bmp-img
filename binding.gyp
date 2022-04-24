{
    "targets": [
        {
            "target_name": "bmpxx_addon",
            "sources": ["lib/bmp.cpp", "lib/decode.cpp", "lib/encode.cpp", "lib/shared.cpp"],
            "cflags_cc": [
                "-std=c++2a -O3 -march=native -mtune=native -Wall -Wextra -pedantic-errors -fexceptions"
            ]
        }
    ]
}
