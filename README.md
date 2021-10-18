
# Small multithreaded C++ http server

This is a project which I made to learn socket programming and multithreading

I used pthreads for this but threads.h can also be used to make this.






## Usage
To compile run:
```console
$ make server client
```

To remove the binaries 
```console
$ make clean
```

```test-server.sh``` is a script that runs the client 50 times to test the server's multithreading capability.