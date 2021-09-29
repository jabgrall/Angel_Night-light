Import("env")

env.Append(
    CXXFLAGS=[
        "-fno-use-cxa-atexit"
    ]
)
