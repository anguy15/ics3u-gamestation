main.o main.d : main.c users/users.h users/encryption/simple_crypt.h \
  users/users_info.h users/stats.h games/games.h \
  games/math_quiz/math_quiz.h games/tic-tac-toe/tic-tac-toe.h \
  games/hangman/hangman.h input_handler.h menu.h
