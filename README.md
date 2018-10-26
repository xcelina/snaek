# Snake #
A small snake game for the terminal.

## Building ##
For a debug build, use:
```Bash
$ make
```

For a release build, use:
```Bash
$ make DEBUG=0
```

If you're feeling fancy, you can specify custom directories for sources, 
headers, object files, and/or binaries:

```Bash
$ make SRC_DIR=~/mysrc INC_DIR=~/myinc OBJ_DIR=~/myobj BIN_DIR=~/mybin
```

## Cleaning up ##
To clean up the default build, use:

```Bash
$ make clean
```

Note that you have to call clean with your custom configuration if you 
want to clean up your custom build.
