# minitalk
A small data exchange program using UNIX signals for communication between processes. 
This project provided insights into low-level programming and inter-process communication.
 ## Processes : 
- A program in this state of execution is what we call a process.
- A program exists on a hard drive; a process exists in RAM.
- a signal is a message that is sent to a process to indicate a particular event has occurred or to request a particular action to be taken. A process is a program that is being executed by the computer.
- $ps -e : To see all the active processes on a Unix system.
- $pidof … : check any process’ PID
- $echo “PID=$$; PPID=$PPID” : check both the PID and PPID of the shell program in our terminal .
- Parent processes that create child processes.
- Child processes that are created by their parent process and can in turn create child processes of their own.
. PID 0: This is typically the scheduler process or the idle process in some systems.
. PID 1: This is often the init process, which is the parent of all other processes and is responsible for starting and managing system services.
. PID 2: This is often the kernel process..
. Kill: Terminating Child Processes
- We need to use the kill function of the <signal.h> library to send a signal to the child process that will force it to terminate immediately.
- $int kill(pid_t pid, int sig):
 . pid: the PID of the process that we want to kill.
  . sig: the signal that we want to send to the process in order to kill it. 
- There are many different possible signals for kill, each with its own nuances, but the most frequently used are perhaps SIGTERM (soft termination signal) and SIGKILL (hard kill signal).
- For each process, the kernel maintains two bit vectors: pending, to monitor pending signals, and blocked, to keep track of the blocked signals. When it sends a signal, the kernel simply sets the appropriate bit to 1 in the destination process’ pending bit vector
Processing Bits
- By shifting the bits of each character to the right, the send_signal function processes each bit one at a time, starting from the most significant bit (MSB) and moving towards the least significant bit (LSB). This ensures that each bit of the character is examined and transmitted individually.
Bitwise AND Operation:
- After shifting, the bitwise AND operation (& 1) is used to extract the LSB of the shifted value. This operation effectively isolates the rightmost bit of the character, which corresponds to the current bit being processed.

## Client Program (send_signal Function):
In the client program, the send_signal function is responsible for encoding the message into a series of signals and transmitting them to the server. It iterates over each character of the message and each bit of the character. Here's why right shifting (>>) is used:
- Encoding Bits for Transmission:
. The client needs to extract individual bits from each character of the message and transmit them as signals.
. Right shifting (>>) is used to extract the bits from left to right, starting with the most significant bit (MSB) and ending with the least significant bit (LSB).
. This allows the client to process each bit in the correct order, as the MSB is typically transmitted first in communication protocols.
- Transmitting Bits in Order:
. By shifting the bits to the right, the client ensures that the bits are transmitted in the correct order, consistent with the binary representation of the characters.
Example:
Suppose we have the character 'H', which has a binary representation of '01001000'.
By right shifting, the client starts with the MSB (0) and moves towards the LSB (0), transmitting each bit in the correct order.
## Server Program (signal_handler Function):
- In the server program, the signal_handler function is responsible for reconstructing the transmitted message from the received signals. It accumulates the received bits to reconstruct the characters. Here's why left shifting (<<) is used:
Reconstructing Characters:
- The server needs to accumulate the received bits to reconstruct the original characters transmitted by the client.
Left shifting (<<) is used to accumulate the received bits from left to right, starting with the most significant bit (MSB) and ending with the least significant bit (LSB).
This ensures that the received bits are correctly assembled into the original characters.
- Building Characters from Bits:
- - By left shifting, the server effectively moves each received bit to its correct position within the reconstructed character.
- - As the bits are received in the correct order (MSB to LSB), left shifting ensures that the bits are placed in the correct positions within the reconstructed characters.
Example:
- As the server receives each bit, it left shifts the accumulated bits and places the new bit in the least significant position.
This process ensures that the bits are assembled in the correct order to reconstruct the original characters.
## Conclusion:
The choice of shifting direction in each program is dictated by the specific requirements of encoding and decoding the message. In the client, right shifting allows for extracting and transmitting bits in the correct order, while in the server, left shifting facilitates the accumulation and reconstruction of characters from received bits. These choices ensure that the communication protocol between the client and server is consistent and that the transmitted message can be accurately reconstructed on the server side.





