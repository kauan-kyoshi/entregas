# Minimal Makefile for philo (no libft dependency per subject)

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

SRCS	= main.c args.c init.c time_utils.c cleanup.c log.c routine.c monitor.c
OBJDIR	= objs
OBJS	= $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re