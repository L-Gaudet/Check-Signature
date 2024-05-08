# Check Signature

Check signature is a very simple program that will check if a file extension has been modified. It will see if there are any discrepencies between the file signature and supposed extension. 

## Usage
Compile using the makefile by running the `make`. Then use the following command to run the program:

```
./checksig <path> [--recursive]
```

- `<path>` Can any directory or file path
- Using the `--recursive` flag will traverse through all subdirectories. 