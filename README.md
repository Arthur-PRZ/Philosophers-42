# 🍝 Philosophers

A 42 project implementing the classic **Dining Philosophers Problem** using threads and mutexes in C.

---

## Introduction

The **Dining Philosophers Problem** is a classic concurrency problem.

A set of philosophers sit at a round table with a fork between each of them. To eat, a philosopher needs **two forks** — the one on their left and the one on their right. The challenge is to make every philosopher eat without any of them **starving** or causing a **deadlock**.

### Key Concepts

- **Threads** — each philosopher runs as an independent thread
- **Mutex** — forks are protected by mutexes to prevent data races
- **Time management** — using `gettimeofday` for precise timing
- **Deadlock** — situation where all threads block each other indefinitely
- **Data race** — unprotected concurrent access to a shared resource

---

## Usage

### Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and binary
make re     # Full recompilation
```

### Running

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Type | Description |
|---|---|---|
| `number_of_philosophers` | required | Number of philosophers (and forks) |
| `time_to_die` | required | Time in ms before a philosopher dies if they haven't started eating |
| `time_to_eat` | required | Time in ms a meal takes (requires 2 forks) |
| `time_to_sleep` | required | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | optional | If set, simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# Classic simulation — stops when a philosopher dies
./philo 5 800 200 200

# Finite simulation — stops after 7 meals per philosopher
./philo 5 800 200 200 7

# Edge case — only 1 philosopher, will always die
./philo 1 800 200 200
```

---

## Log Format

Each event is displayed as follows:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

---

## Author

Made by [Arthur-PRZ](https://github.com/Arthur-PRZ)
