# Philosopher_42

A C implementation of the Dining Philosophers problem.  
This project implements the classic concurrency/synchronization exercise commonly assigned at 42 (philosophers subject). It demonstrates safe use of threads/processes, mutexes/semaphores, and careful timing to model philosophers that think, eat and sleep without deadlocks or data races.

This repository is implemented in C (primary), with Makefiles and small shell helpers. 

(Also, 42PhilosophersHelper provides some good test scripts. 
https://github.com/AbdallahZerfaoui/42PhilosophersHelper.git). 

It aims to be simple, robust, and easy to test.

# To be noticed:

This version is changed after evaluation:
- add error handling for system functions;
- use ft_putstr_fd to print error msg to stderr;
- adjust files;
- not handle norminette

---

## Overview

The Dining Philosophers is an exercise used to teach concurrency concepts such as mutual exclusion, deadlock avoidance, starvation prevention, and correct use of synchronization primitives. This project simulates N philosophers sitting around a table where each philosopher alternates between thinking, picking up forks (resources) to eat, eating, and sleeping.

There are commonly two variants:
- Thread-based solution using pthreads, mutexes / condition variables.
- Process-based solution using processes and named semaphores (often referred to as the "bonus" variant).

This repo provides only first part (see the Makefile for available targets).

---

## Features

- Correct synchronization (mutexes/semaphores) to avoid data races.
- Deadlock avoidance strategies.
- Accurate timing for actions (think / eat / sleep / die).
- Clean shutdown when the simulation finishes or a philosopher dies.
- Small and portable C code with a Makefile for easy building.

---

## Requirements

- Unix-like OS (Linux, macOS with slight differences)
- A C compiler that supports C11 (gcc / clang)
- make
- pthreads (for thread-based solution)
- Optional: valgrind for memory checking

---


