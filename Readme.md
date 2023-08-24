# Quadratka
This project is simple quadratic and linear equation solver with some big project features
**This program only works on linux os**

## Setuping program
To download, compile and run this program you need [make](https://www.gnu.org/software/make/manual/make.html), [g++](https://gcc.gnu.org/install/) and [git](https://git-scm.com/) to be installed

### Downloading program
`cd` to folder you want to install application and run git clone program:
```
$ cd quadratka
$ git clone https://github.com/Iprime111/QuadraticEquation
```

### Compiling program
To compile program `cd` to it's folder and run `make` command:
```
$ cd QuadraticEquation
$ make
```

## Running program
To run program simply `cd` to build folder and enter `./SquareSolver`:
```
$ cd build
$ ./SquareSolver
Enter a, b and c coefficients (a * x^2 + b * x^2 + c = 0) or q to exit:
```

## Testing program
### Running program in test mode
To run program in test mode enter path to test file after it's name:
```
$ ./SquareSolver testfile.txt
Starting test #1...
```
### Test file format
A line of the test file must have format of
```
...
COEFFS [a] [b] [c] STATUS [status] ROOTS [x1] [x2]
...
```
Where:<br>
`a,b,c` are floating point numbers presenting coefficients <br>
`x1,x2` are floating point numbers presenting roots<br>
`status` is integer number presenting answer form: `0` is no roots, `1` is one root, `2` is two roots and `3` is infinitely many roots

## Generating docs
To generate docs for program [doxygen](https://www.doxygen.nl/) must be installed on your computer

Enter this command to build docs:
```
$ make build_docs
...
```
Docs will be available in `latex` and `html` folders



