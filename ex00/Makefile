
NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP

SRCS = main.cpp BitcoinExchange.cpp
OBJ_DIR = obj
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEP = $(OBJS:.o=.d)

all : $(NAME)

$(NAME) : $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) -lcurl

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME) $(NAMEB)

re : fclean all

.PHONY: all clean fclean re


SRCSB = main_bonus.cpp BitcoinExchange.cpp BitcoinValue.cpp
OBJSB = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCSB))
DEP = $(OBJSB:.o=.d)


NAMEB = btc_bonus

SRCSB = main_bonus.cpp BitcoinExchange.cpp BitcoinValue.cpp

allbonus: $(NAMEB)

$(NAMEB) : $(OBJSB) Makefile
	$(CXX) $(CXXFLAGS) $(OBJSB) -o $(NAMEB) -lcurl

.PHONY : allbonus
-include $(DEP)