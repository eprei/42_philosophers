# Philosophers

## Overview
This project is an implementation of the classic Dining Philosophers problem, which illustrates challenges in resource sharing and deadlock avoidance in concurrent programming. The project follows the strict coding standards of 42 School's curriculum.

## The Problem
A number of philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately:
- Think
- Eat (requiring both the fork to their left and right)
- Sleep

The simulation stops when:
- A philosopher dies of starvation
- All philosophers have eaten the required number of times (if specified)

## Learning Objectives
- Understanding concurrent programming concepts
- Working with threads and mutexes
- Managing shared resources
- Preventing race conditions and deadlocks
- Implementing precise timing in a multithreaded environment

## Technical Stack
- Language: C
- Threading Library: pthread
- Compilation: Via Makefile
- OS: Unix-based systems

## Installation
clone the repo

## Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds until a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds it takes to eat
- `time_to_sleep`: Time in milliseconds spent sleeping
- `number_of_times_each_philosopher_must_eat`: [Optional] Number of times each philosopher must eat before simulation ends

### Example
```bash
./philo 5 800 200 200 5
```
This creates a simulation with:
- 5 philosophers
- Death occurs after 800ms without eating
- Eating takes 200ms
- Sleeping takes 200ms
- Simulation stops after each philosopher eats 5 times

## Implementation Details
- Each philosopher is represented by a thread
- Forks are represented by mutexes
- A separate monitoring thread checks for deaths and completion
- Timestamps are used for precise timing of actions
- Status messages are protected to prevent garbled output

## Project Structure
- `main.c`: Program entry point and initialization
- `actions.c`: Philosopher actions (eating, sleeping, thinking)
- `check_args.c`: Command-line argument validation
- `check_end.c`: Death and completion monitoring
- `philos.c`: Philosopher data structure management
- `threads.c`: Thread and mutex handling
- `utils.c`: Utility functions
- `print.c`: Output handling

## Code Standards
This project adheres to 42 School's strict coding standards ("The Norm"), which includes:
- Specific function and variable naming conventions
- Maximum function length of 25 lines
- Maximum of 5 functions per file
- Limited use of standard library functions
- Specific formatting and spacing rules

## Error Handling
The program includes comprehensive error checking for:
- Invalid arguments
- Memory allocation failures
- Thread creation/joining failures
- Mutex initialization/destruction failures

## Known Limitations
- Due to the school's coding standards, some modern optimizations are intentionally not implemented
- The program must be compiled with the flags: -Wall -Wextra -Werror
