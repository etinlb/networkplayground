#include <vector>
#include <string>
#include <functional>

using ConsoleCallback = std::function<void()>;

void interactive_console();
void add_command(std::string full_command, ConsoleCallback);
void add_exit_command(std::string full_command, ConsoleCallback);
