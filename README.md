# How to use
If possible don't read/open the following files:
- cypher_pouet / cypher_pouet.c
- pouet_source / pouet_source.c
- gen_key.py  

Try reversing one of this binary (they are both the same, just different GLIBC version):
- pouet / pouet_2-28

If you want, source code is in `pouet_source.c`, an example of the keygen is `gen_key.py`.
`cypher_pouet` is a binary to cipher/uncipher a file with a key (hardcoded in the code).

Here is an historic of my commands to generate all the files:
```sh
gcc cypher_pouet.c -o cypher_pouet
gcc pouet_source.c -o pouet # or pouet_2-28
./cypher_pouet -f <file> -c # -> cipher the file
./cypher_pouet -f <file> -u # -> uncipher a file
```