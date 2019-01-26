{
  "targets": [
    {
      "target_name": "lava_node",
      "type": 'loadable_module',
      "sources": [
        "src/core.c",
        "src/player.c"
        ],
      "conditions": [
        ['OS=="mac"', {
          "cflags" : [
            "-lz",
            "-I/usr/local/include/SDL2",
            "-D_THREAD_SAFE",
            "-L/usr/local/lib",
            "-lSDL2"
            ],
          "libraries" : [
              "-lavcodec",
              "-lavformat",
              "-lswscale",
              "-lavresample",
              "-lavutil",
              "-lSDL2"
          ]
        }],
        ['OS=="linux"', {
          "cflags" : [
            "-g",
            "-D__STDC_CONSTANT_MACROS",
            "-D_FILE_OFFSET_BITS=64",
            "-D_LARGEFILE_SOURCE",
            "-O3",
            "-Wall"],
          "libraries" : [
              "-lavcodec",
              "-lavformat",
              "-lswscale",
              "-lavresample",
              "-lavutil",
              "-lSDL2"
          ]
        }],
        ['OS=="win"', {
            "include_dirs": [
                "$(LIBAV_PATH)include"
                ],
            "libraries" : [
                  "-l$(LIBAV_PATH)avcodec",
                  "-l$(LIBAV_PATH)avformat",
                  "-l$(LIBAV_PATH)swscale",
                  "-l$(LIBAV_PATH)avresample",
                  "-l$(LIBAV_PATH)avutil",
                  "-l$(LIBAV_PATH)SDL2"
                ]
        }]
      ],
    }
  ]
}
