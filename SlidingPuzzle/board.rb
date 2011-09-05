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
		@adjacent = []
		(0...@height).each do |y|
			(0...@width).each do |x|
				#u = (y - 1) * @width + x
				#d = (y + 1) * @width + x
				#l = y * @width + (x - 1)
				#r = y * @width + (x + 1)
				a = []
				#a << u if 0 <= u and u < @size
				#a << d if 0 <= d and d < @size
				#a << l if 0 <= l and l < @size
				#a << r if 0 <= r and r < @size
				@adjacent << a
			end
		end
	end

	def solve
	end
end

if __FILE__ == $0 then
	#server = DRbObject.new_with_uri('druby://localhost:12345')
	#p server.board(1)
	b = SlidingPuzzle::Board.new(5, 6, '12=E4D9HIF8=GN576LOABMTPKQSR0J')
	p b
end
