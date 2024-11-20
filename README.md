# Charoln

A C String library built with safety in mind, and aims to have feature parity with Python string methods.

## Motivation
C lacks a modern string library in the standard library. Null-terminated strings along with string.h functions are far inferior to modern libraries and presents lots of footguns that trip up learners, especially those coming from (almost any) other language. This project makes it easier to start development in C, allowing the learner to focus on the important details rather than unnecessary complexity caused by a barebones string implementation.

A personal motivation is to make it easier to complete [Advent of Code](https://adventofcode.com/) challenges, reducing some of the burden as almost every challenge involves string manipulation in some way.

## Todo
- [x] Initialise
- [x] Destroy
- [x] Get
- [x] Get length 
- [x] Write
- [x] Append
- [ ] Append string
- [ ] Slice
- [ ] Index
- [ ] Split
- [ ] Find
- [ ] Replace
- [ ] Is number
- [ ] Is alpha
- [ ] Make uppercase
- [ ] Make lowercase
