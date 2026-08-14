# Computer and System Architecture Project
## Project context

This project implements a client/server process system that provides services
to users.

One constraint is to use the inter-process communication systems available on
UNIX systems. These include named or unnamed pipes, message queues, and
semaphores.

The project also considers the performance of each service through fork and
thread mechanisms.

After a service finishes, the system reports the resources that its computation
used. It obtains this information from the /proc virtual file system. This file
system provides information about the system and running processes.

## Build and execution

To build the project, run this command in the project directory:

```bash
make clean all
```

This creates two executables named `serveur` and `client` in the `bin/`
directory. Then start the server:

```bash
./bin/serveur
```

After the server starts, run clients in another terminal to request the
available services. Use these commands:

- List available services:

  ```bash
  ./bin/client services
  ```

- Basic calculation

  ```bash
  ./bin/client calcul-simple + 5 3.14 6 [...]
  ./bin/client calcul-simple - 8 4 2 [...]
  ./bin/client calcul-simple "*" 6.25 35  [...] ( ou calcul-simple \* [...] )
  ./bin/client calcul-simple / 2 3.25 [...]
  ./bin/client calcul-simple "**" 2 6 [...]
  ```

- Character counter

  ```bash
  ./bin/client compteur-char text ceci est une phrase
  ./bin/client compteur-char text "une phrase" "voici autre une phrase"
  ./bin/client compteur-char file ./ceci_est_un_fic.txt
  ./bin/client compteur-char file "./ceci_est_un_fic.txt"
  ./bin/client compteur-char file "/home/user/fic.txt"
  ```

- Word counter

  ```bash
  ./bin/client compteur-mots text ceci est une phrase
  ./bin/client compteur-mots text "une phrase" "voici une autre phrase"
  ./bin/client compteur-mots file ./ceci_est_un_fic.txt
  ./bin/client compteur-mots file "./ceci_est_un_fic.txt"
  ./bin/client compteur-mots file "/home/user/fic.txt"
  ```

- Probability that one character follows another character

  ```bash
  ./bin/client proba-char text ceci est une phrase
  ./bin/client proba-char text "une phrase" "voici une autre phrase"
  ./bin/client proba-char file ./ceci_est_un_fic.txt
  ./bin/client proba-char file "./ceci_est_un_fic.txt"
  ./bin/client proba-char file "/home/user/fic.txt"
  ```

- Probability that one word follows another word

  ```bash
  ./bin/client proba-mots text ceci est une phrase
  ./bin/client proba-mots text "une phrase" "voici une autre phrase"
  ./bin/client proba-mots file ./ceci_est_un_fic.txt
  ./bin/client proba-mots file "./ceci_est_un_fic.txt"
  ./bin/client proba-mots file "/home/user/fic.txt"
  ```

  The result appears on **standard output**.

## Test script

A test script is included. By default, it starts 100 clients:

```bash
./test.sh
```

It accepts the number of clients to start as an argument:

```bash
./test.sh 10000
```

This starts 10000 clients.
