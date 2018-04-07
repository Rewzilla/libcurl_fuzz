# libcurl_fuzz
Very simple grammer-based fuzzer for the libcurl URL parser

# Setup

Dowload the latest libcurl from https://curl.haxx.se/download.html
Untar it, and set the directory name in your Makefile

# Building
```make libcurl && make```

# Running
```./fuzzer```

# Crashes
Crashes will be stored in a directory called ```./crashes```.  Each file will contain one crashing URL.
