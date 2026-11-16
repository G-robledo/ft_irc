# ft_irc

A C++98 IRC server developed as a collaborative École 42 project. It uses non-blocking TCP sockets and a `poll` event loop to manage multiple clients, registration, channels and messages.

## Features

- Password-based registration with `PASS`, `NICK` and `USER`.
- Channel joins and private or channel messages with `JOIN` and `PRIVMSG`.
- Channel management with `KICK`, `INVITE`, `TOPIC` and `MODE`.
- Invite-only channels, protected topics, channel keys, operator privileges and user limits.
- Command parsing and IRC-style numeric replies, based on RFC 2812.

This is a learning implementation focused on the project's command set, rather than a complete implementation of every IRC command.

## Build and run

Prerequisites: a Unix-like system with POSIX sockets, Make and a C++ compiler supporting C++98. Netcat (`nc`) is useful for a manual check.

```sh
git clone https://github.com/G-robledo/ft_irc.git
cd ft_irc
make
./irc 6667 local-demo
```

The binary produced by the [Makefile](Makefile) is **`irc`**. The server expects a port between `1024` and `65535` and a password of at most 30 characters. Run it from the repository root so it can read `motd.txt`.

## Try a conversation

Keep the server running. In another terminal:

```sh
nc 127.0.0.1 6667
```

Enter these IRC commands **one line at a time**, pressing Enter after each line:

```text
PASS local-demo
NICK reader1
USER reader1 0 * :First reader
JOIN #demo
```

Open a second Netcat session and register another client:

```text
PASS local-demo
NICK reader2
USER reader2 0 * :Second reader
JOIN #demo
```

Send this from either client; the other client should receive the message:

```text
PRIVMSG #demo :Hello from IRC
```

The current parser does not split multiple commands received in the same TCP read, so avoid pasting the whole registration block at once. This also limits compatibility with clients that batch commands.

Stop the server with **Ctrl+C**.

## Source layout

- [`inc/`](inc/): server, client and channel declarations, commands and reply definitions.
- [`srcs/`](srcs/): connection handling, event loop, parser and command handlers.
- [`main.cpp`](main.cpp): argument validation and server startup.

## Build commands

| Command | Action |
| --- | --- |
| `make` | Compile `irc` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the executable |
| `make re` | Rebuild from scratch |
