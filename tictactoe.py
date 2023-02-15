#!/usr/bin/env python3

def print_board(board):
	print(board[0] + "|" + board[1] + "|" + board[2])
	print("-+-+-")
	print(board[3] + "|" + board[4] + "|" + board[5])
	print("-+-+-")
	print(board[6] + "|" + board[7] + "|" + board[8])
	
def check_win(board):
	win_combinations = [(0, 1, 2), (3, 4, 5), (6, 7, 8), (0, 3, 6), (1, 4, 7), (2, 5, 8), (0, 4, 8), (2, 4, 6)]
	for combo in win_combinations:
		if board[combo[0]] == board[combo[1]] == board[combo[2]] != " ":
			return True
	return False

def tic_tac_toe():
	board = [" ", " ", " ", " ", " ", " ", " ", " ", " "]
	current_player = "X"
	winner = False
	while not winner and " " in board:
		print_board(board)
		print("It's " + current_player + "'s turn.")
		choice = int(input("Enter a number from 1 to 9: ")) - 1
		if board[choice] == " ":
			board[choice] = current_player
			winner = check_win(board)
			if current_player == "X":
				current_player = "O"
			else:
				current_player = "X"
		else:
			print("That space is already taken. Try again.")
	print_board(board)
	if winner:
		print("Congratulations, " + current_player + "! You have won!")
	else:
		print("It's a tie!")
		
tic_tac_toe()
