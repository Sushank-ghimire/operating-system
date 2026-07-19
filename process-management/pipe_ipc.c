#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
  int fd[2];
  pid_t pid;
  char message[] = "Hello, Sushank from Parent Process!";
  char buffer[100];

  // creating a pipe
  pipe(fd);

  // creating a child process
  pid = fork();

  if(pid < 0) {
    printf("Failed to create child process.\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    close(fd[1]); // close write end of the pipe

    read(fd[0], buffer, sizeof(buffer));
    printf("Child Process received: %s\n", buffer);
    close(fd[0]); // close read end
  } else {
    // Parent process
    close(fd[0]); // close read end of the pipe

    write(fd[1], message, strlen(message) + 1);
    printf("Parent Process sent: %s\n", message);
    close(fd[1]); // close write end
  }
  return 0;
}
