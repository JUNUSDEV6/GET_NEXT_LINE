# Get Next Line

A C function that reads a file line by line, one line at a time.

## Overview

**Get Next Line** is a function that reads and returns one line at a time from a file descriptor. This project is part of the 42 school curriculum and teaches important concepts like static variables, dynamic memory allocation, and file manipulation in C.

The function can handle multiple file descriptors simultaneously and efficiently manages memory using a linked list structure to buffer the data.

## Features

- ✅ Reads one line at a time from any file descriptor
- ✅ Handles multiple file descriptors simultaneously
- ✅ Configurable buffer size at compile time
- ✅ Memory efficient using linked list buffering
- ✅ Handles files with or without final newline
- ✅ Returns `NULL` when reaching end of file or on error

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: File descriptor to read from

### Return Value
- Returns the line read from the file descriptor (including the trailing `\n` if present)
- Returns `NULL` if there's nothing more to read or an error occurs

## Compilation

The project uses a configurable `BUFFER_SIZE` that can be set at compile time:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can change the `BUFFER_SIZE` value to optimize for different file sizes and reading patterns.

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Project Structure

```
.
├── get_next_line.c       # Main function implementation
├── get_next_line_utils.c # Utility functions (linked list operations)
├── get_next_line.h       # Header file with function prototypes
└── README.md            # This file
```

## Implementation Details

### Architecture

The function uses a **static linked list** to maintain a buffer across multiple calls. Each node in the list contains:
- A buffer of characters read from the file
- A pointer to the next buffer node

### Key Functions

- **`get_next_line(int fd)`**: Main function that returns the next line
- **`create_list(t_list **list, int fd)`**: Reads from file descriptor and builds the buffer list
- **`get_line(t_list *list)`**: Extracts and returns one line from the buffer
- **`polish_list(t_list **list)`**: Cleans up processed data and keeps remaining characters
- **`found_newline(t_list *list)`**: Checks if there's a newline character in the buffer
- **`dealloc(t_list **list, t_list *clean_node, char *buff)`**: Handles memory deallocation

### Memory Management

The function carefully manages memory by:
- Allocating buffers dynamically as needed
- Freeing processed buffer nodes after extracting lines
- Keeping unprocessed characters for the next function call
- Properly handling edge cases and error conditions

## Error Handling

The function handles various error conditions:
- Invalid file descriptor (`fd < 0`)
- Invalid buffer size (`BUFFER_SIZE <= 0`)
- Memory allocation failures
- File reading errors

## Performance Considerations

- **Buffer Size**: Larger buffer sizes reduce system calls but use more memory
- **Memory Usage**: Uses only the necessary memory for buffering unprocessed data
- **Multiple FDs**: Can handle multiple file descriptors efficiently using static variables

## Testing

To test the function thoroughly, consider:
- Empty files
- Files without final newline
- Very large files
- Files with very long lines
- Multiple file descriptors simultaneously
- Various buffer sizes

## Author

Created by **youneshanafi** as part of the 42 School curriculum.

## License

This project is part of the 42 School curriculum and follows their academic guidelines.
