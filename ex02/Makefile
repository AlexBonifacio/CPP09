
NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP -O3

SRCS = main.cpp PmergeMe.cpp
OBJ_DIR = obj
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEP = $(OBJS:.o=.d)

all : $(NAME)

$(NAME) : $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re

test:
	@i=0; \
	while [ $$i -lt 100 ]; do \
		ARGS=$$(shuf -i 0-20) ; \
		./PmergeMe $$ARGS; \
		i=$$((i + 1)); \
	done; \
	echo "Done $$i tests"

-include $(DEP)