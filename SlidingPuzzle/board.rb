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
		@board = board.scan(%r!(.{#{@width}})!).flatten(1)
	end
end

if __FILE__ == $0 then
	server = DRbObject.new_with_uri('druby://localhost:12345')
	p server.board(5000)
end
