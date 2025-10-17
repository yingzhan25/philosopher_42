# Philosopher_42

A C implementation of the Dining Philosophers problem.  

This project implements the classic concurrency/synchronization exercise commonly assigned at 42 (philosophers subject). It demonstrates safe use of threads/processes, mutexes/semaphores, and careful timing to model philosophers that think, eat and sleep without deadlocks or data races.

---

### Besides codes, also adding with some small practices and shell tester scripts. 

The pratices break down the complicated question, so that you can learn step by step, from easy to hard, without anxiety.

- single_philo
- two_philo_not_share
- two_philo_share_one_fork
- two_philo_both_fork_deadlock
- two_philo_both_fork_no_deadlock  

The tester scripts are convenient for testing multiple times (e.g.100 times) when the death of philosophers is unpredictable.

(Also, 42PhilosophersHelper provides some good test scripts. 
https://github.com/AbdallahZerfaoui/42PhilosophersHelper.git). 

# To be noticed:

This older version(8564e531ab11083bd7e1a9cb8e70e5bdce90afed) passed all the required tests with valgrind --tool=helgrind --tool=drd during evaluation.

<img width="831" height="368" alt="image" src="https://github.com/user-attachments/assets/03c4ac95-378c-46d3-95c4-9e30052fad94" />

But aiming to improve, the latest version is changed after evaluation:
- add error handling for system functions;
- use ft_putstr_fd to print error msg to stderr;
- adjust files;
- however, not handle norminette...

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


