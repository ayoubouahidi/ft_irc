# ft_irc
A custom IRC server implemented in C++98.


## Architecture & Command Dispatcher

Our IRC server uses a simple and scalable architecture to handle incoming commands. Instead of using a long chain of `if-else` statements, we use a **Command Dispatcher**.

### 1. The Parser
When a client sends a raw string like `PING :123`, the `parseMessage` function breaks it down into a structured `Message` object:
- **Prefix**: Optional sender info (starts with `:`).
- **Command**: The main action (e.g., `PING`, `JOIN`).
- **Parameters**: The arguments for the command (e.g., `123`).

### 2. The Dispatcher
We use a dictionary-like structure (`std::map`) to link command names directly to their specific functions. 

```cpp
// Example: Registering a command inside the constructor
_commands_map["PING"] = &myPingCommand;
```

When a parsed `Message` arrives, the `executeCommand` function looks up the command name in the `std::map`. If it finds a match, it executes the correct function and passes the required data (`Client`, `Parameters`, and `Server`). If not, it handles the unknown command smoothly.
