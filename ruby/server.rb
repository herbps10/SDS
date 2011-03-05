require 'socket'

class Restaurant
	def initialize(id, fitness)
		@id = id
		@fitness = fitness
	end
end

class Agent
	def initialize(id, restaurant)
		@id = id
		@restaurant = restaurant
	end
end

NUM_RESTAURANTS = 10
NUM_AGENTS = 10
NUM_CLIENTS = 2

restaurants = []
agents = []

NUM_RESTAURANTS.times do |index|
	randomFitness = 1 + rand(10)
	restaurants.push(Restaurant.new(index, randomFitness))
end

NUM_AGENTS.times do |index|
	randomRestaurant = rand(NUM_RESTAURANTS)
	agents.push(Agent.new(index, randomRestaurant))
end

server = TCPServer.new("localhost", 5010)

clients = []
NUM_CLIENTS.times do 
	clients.push(server.accept)
end

clients.length.times do |clientIndex|
	clients[clientIndex].puts(restaurants.slice(clientIndex * (restaurants.length/2), restaurants.length/2))
end
