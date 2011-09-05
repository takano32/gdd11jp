#!/usr/bin/env ruby1.9
# vim: set noet ts=4 sts=4 sw=4 ft=ruby :
# author: takano32 <tak at no32.tk>
#
require './server'

module SlidingPuzzle; end

class SlidingPuzzle::Board
	def initialize(width, height, board)
		@width = width
		@height = height
		@size = @width * @height
		@board = board.scan(%r!(.{#{width}})!).flatten(1)
		@all_boards = [@board]
		@boards = [@board]
		@adjacent = []
		(0...@height).each do |y|
			(0...@width).each do |x|
				u = [x, y - 1]
				d = [x, y + 1]
				l = [x - 1, y]
				r = [x + 1, y]
				a = []
				a << pos2ord(u) if on_board?(u)
				a << pos2ord(d) if on_board?(d)
				a << pos2ord(l) if on_board?(l)
				a << pos2ord(r) if on_board?(r)
				@adjacent << a
			end
		end
	end

	def on_board?(pos)
		x, y = pos
		return false if x < 0
		return false if y < 0
		return false if @width - 1 < x
		return false if @height - 1 < y
		return true
	end

	def pos2ord(pos)
		x, y = pos
		return y * @width + x
	end

	def swap!(board, pos1, pos2)
		x1, y1 = pos1
		x2, y2 = pos2
		tmp = board[y1][x1]
		board[y1][x1] = board[y2][x2]
		board[y2][x2] = tmp
	end

	def goal?(board = @board)
		ch = '0'
		(0...@height).each do |y|
			(0...@width).each do |x|
				ch.succ!
				ch = 'A' if ch == '10'
				return false unless (ch == board[y][x] or '=' == board[y][x])
			end
		end
		return true
	end

	def solve(boards = @boards)
		succBoards = boards.map do |board|
			succ(board)
		end.flatten(1)
		succBoards.each do |board|
			return board if goal?(board)
		end
		solve(succBoards)
	end

	def succ(board)
		spaces = []
		boards = []
		(0...@height).each do |y|
			(0...@width).each do |x|
				spaces << [x, y] if board[y][x] == '='
			end
		end
		spaces.each do |space|
			@adjacent[pos2ord(space)].map do |adj|
				x = adj % @width
				y = adj / @width
				succBoard = board.map do |row|
					row.dup
				end
				swap!(succBoard, space, [x, y])
				begin
					@all_boards.each do |b|
						raise if b == succBoard
					end
					boards << succBoard
				rescue
				end
			end
		end
		@all_boards += boards
		boards
	end
end

if __FILE__ == $0 then
	#server = DRbObject.new_with_uri('druby://localhost:12345')
	#p server.board(1)
	#b = SlidingPuzzle::Board.new(5, 6, '12=E4D9HIF8=GN576LOABMTPKQSR0J')
	#b = SlidingPuzzle::Board.new(3, 3, '86725431=')
	b = SlidingPuzzle::Board.new(3, 3, '1234567=8')
	p b.solve
end

