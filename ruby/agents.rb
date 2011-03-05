class Agents
	def initialize()
		@agents = []

		@best_percentage = START_BEST_PERCENTAGE
	end

	def new_percentage(percentage)
		if percentage < @best_percentage
			@best_percentage = percentage
		end
	end

	def best_percentage()
		return @best_percentage
	end

	def add(agent)
		@agents.push(agent)
	end

	def draw
		@agents.each { |a| a.draw() }
	end

	def each
		@agents.each { |a| yield a }
	end

	def get_active
		active_agents = []
		@agents.each do |a|
			active_agents.push a
		end

		return active_agents
	end

	def random_agent
		return @agents[rand(@agents.length)]
	end

	@@instance = Agents.new

	def self.instance
		return @@instance
	end
end
