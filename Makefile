# Compiler to use
CC = gcc

# Compiler flags to use
CFLAGS = -Wall

# Argument to build static library
AR = ar rcs

# Define the source directory
SRCS_DIR = src

# Define the include directory
INCL_DIR = HCC

# Define the source file
SRCS = $(SRCS_DIR)/object.c $(SRCS_DIR)/array.c $(SRCS_DIR)/list.c $(SRCS_DIR)/config.c

# Define the object file
OBJS = $(SRCS:.c=.o)

# Name of the executable
TARGET = libhcc.a

# Default rule
$(TARGET):$(OBJS)
	$(AR) -o $(TARGET) $(OBJS)

# Build the object file
$(SRCS_DIR)/%.o:$(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(TARGET) $(OBJS)
