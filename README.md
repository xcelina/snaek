# snaek #
play snaek

## bild ##
for debug buld
```Bash
$ make
```

for reelase build
```Bash
$ make DEBUG=0
```

you can chaeng hte folders too

```Bash
$ make SRC_DIR=~/mysrc INC_DIR=~/myinc OBJ_DIR=~/myobj BIN_DIR=~/mybin
```

## cleen ##
maek clean

```Bash
$ make clean
```

Note that you have to call clean with your custom configuration if you 
want to clean up your custom build.
