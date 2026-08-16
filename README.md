# Watopoly

A terminal-based, multiplayer implementation of **Watopoly**—a University of
Waterloo-themed adaptation of Monopoly—written in C++14.

This was a three-person final project for the University of Waterloo's CS246
course. Players move around a 40-square campus board, purchase and improve
academic buildings, collect tuition, trade assets, and try to remain the last
student who has not declared bankruptcy.

## Highlights

- Interactive ASCII board for two to six players
- Academic buildings, residences, gyms, and campus event squares
- Property purchases, auctions, improvements, mortgages, and player trading
- Saving and loading game state
- Deterministic testing controls for dice rolls, movement, and balances
- MVC-inspired separation between game logic, control flow, and display
- Observer-based display updates and polymorphic square/property types
- Stable `deque`-backed display storage for observer references

## Build and run

Requirements: GNU Make and a C++14-compatible compiler such as `g++`.

```bash
make
./watopoly
```

Additional modes:

```bash
# Supply dice values and use testing-only commands
./watopoly -testing

# Resume a previously saved game
./watopoly -load path/to/save-file
```

Run the program from the repository root so it can load
[`data/default.data`](data/default.data).

Common in-game commands include `roll`, `next`, `trade`, `improve`,
`mortgage`, `unmortgage`, `assets`, `all`, `save`, and `bankruptcy`.

## Project structure

```text
Watopoly/
├── src/       C++ implementations and program entry point
├── include/   Interfaces, domain models, and response types
├── data/      Board configuration
├── docs/      Original team design plan and UML diagram
├── Makefile   Reproducible debug build
└── README.md
```

The model represents the board, players, and square hierarchy. The controller
coordinates turns and commands, while the text display observes model changes
and renders the board. The design documents are available in
[`docs/design-plan.pdf`](docs/design-plan.pdf) and
[`docs/uml.pdf`](docs/uml.pdf).

## Team

- [Ryan Maxin](https://github.com/Ryanmaxin)
- [Isha Chaudhry](https://github.com/Ishac1)
- [Nandish Patel](https://github.com/nandishofficial)

The game specification and Watopoly concept were provided by the University of
Waterloo for CS246 (Winter 2023). This repository contains the team's
implementation and design artifacts.
