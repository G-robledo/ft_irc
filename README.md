# ft_irc

## Description
`ft_irc` is a networking project at **42**.  
The goal is to implement an **IRC (Internet Relay Chat) server** in C++ following the **RFC 2812** specification.  
This project introduces concepts like **socket programming**, **asynchronous communication**, and **protocol implementation**.

## Features
- IRC server compliant with **RFC 2812**  
- Supports multiple clients simultaneously  
- Handles common IRC commands:
  - `NICK`, `USER`, `JOIN`, `PRIVMSG`, `KICK`, `INVITE`, `TOPIC`, `MODE`  
- Channel management with modes:
  - Invite-only, topic restriction, password-protected, operator privileges, user limits  
- Proper error handling and server responses  
- Extensible architecture for future commands  

## Tech Stack
- **Language:** C++  
- **Networking:** Sockets, non-blocking I/O, `poll`  
- **Build tool:** Makefile  

## Usage
Clone the repository and compile:  

```bash
git clone https://github.com/G-robledo/irc.git
cd irc
make
```

Run the server:

```bash
./irc_server <port> <password>
```

Connect with an IRC client (e.g., netcat...):

```bash
nc 127.0.0.1 <port>
```

## Learning Outcomes
- Learned socket programming and handling multiple clients concurrently
- Understood how to implement a text-based communication protocol
- Gained experience in parsing and validating client commands
- Practiced designing a modular and extensible server architecture