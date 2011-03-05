require 'socket'

socket = TCPSocket.new("localhost", 5010)

while agent = socket.gets
	puts agent
end
